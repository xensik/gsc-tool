// Copyright 2026 xensik. All rights reserved.
//
// Use of this source code is governed by a GNU GPLv3 license
// that can be found in the LICENSE file.

#include <catch_amalgamated.hpp>
#include "common.hpp"
#include "xsk/utils/file.hpp"
#include "xsk/utils/zlib.hpp"

namespace xsk::test
{

namespace
{

namespace fs = std::filesystem;

// The corpus under test/data/<game> is original game source. Every file is put
// through the full pipeline and the bytecode has to survive the trip:
//
//   source -> compile -> assemble -> disassemble -> decompile -> print -> compile
//
// The two assemblies must come out byte for byte identical. Anything the parser
// cannot read, the decompiler cannot rebuild or the printer cannot round-trip
// shows up as a failing file here.

// test/data mirrors data/: 'raw' holds original source, 'bin' holds shipped bytecode.
auto corpus_root(std::string_view kind, std::string_view game) -> fs::path
{
    return fs::path{ XSK_TEST_DATA } / kind / game;
}

auto corpus(std::string_view kind, std::string_view game, std::string_view ext) -> std::vector<std::string>
{
    auto const root = corpus_root(kind, game);
    auto out = std::vector<std::string>{};

    for (auto const& entry : fs::recursive_directory_iterator{ root })
    {
        if (entry.is_regular_file() && entry.path().extension() == ext)
            out.push_back(fs::relative(entry.path(), root).generic_string());
    }

    std::sort(out.begin(), out.end());
    return out;
}

// Scripts '#include' each other and the compiler resolves those through the
// context, so reads are served straight out of the corpus directory.
template <typename Ctx>
auto make_engine_ctx(std::string_view game, typename fam<Ctx>::build build) -> Ctx*
{
    auto root = corpus_root("raw", game);
    auto* c = new Ctx(fam<Ctx>::instance::server);

    c->init(build, [root](auto const*, std::string const& name) {
        return std::pair<typename fam<Ctx>::buffer, std::vector<u8>>{ {}, utils::file::read(root / name) };
    });

    return c;
}

// Original source is written against the developer build, so the corpus is run both
// ways: '/# #/' blocks are stripped under prod and compiled under dev, which is two
// different programs out of the same file.
//
// ponytail: deliberate leak and statics keyed on nothing but the context type, same
// reasoning as ctx() in common.hpp. One game maps to one corpus directory, so a second
// root for the same context type is not a case that exists.
template <typename Ctx>
auto engine_ctx(std::string_view game, bool dev) -> Ctx*
{
    static Ctx* prod = make_engine_ctx<Ctx>(game, fam<Ctx>::build::prod);
    static Ctx* devel = make_engine_ctx<Ctx>(game, fam<Ctx>::build::dev);

    return dev ? devel : prod;
}

auto as_vector(auto const& buf) -> std::vector<u8>
{
    return std::vector<u8>{ buf.data, buf.data + buf.size };
}

// Catch2 would dump both buffers on a plain vector comparison, which for a
// 100 KB script is unreadable. Report where they part company instead.
auto diff(std::vector<u8> const& lhs, auto const& rhs) -> std::string
{
    if (lhs.size() != rhs.size)
        return std::format("size {} != {}", lhs.size(), rhs.size);

    for (auto i = usize{ 0 }; i < lhs.size(); i++)
    {
        if (lhs[i] != rhs.data[i])
            return std::format("byte {} of {}: {:02X} != {:02X}", i, lhs.size(), lhs[i], rhs.data[i]);
    }

    return {};
}

// One inserted instruction renames every label after it, so a raw line comparison reports
// the first jump rather than the insertion that moved it. Blank the labels out for the
// comparison and report the original lines.
auto blank_labels(std::string_view line) -> std::string
{
    auto out = std::string{};

    for (auto i = usize{ 0 }; i < line.size();)
    {
        if (line.compare(i, 4, "loc_") == 0)
        {
            i += 4;

            while (i < line.size() && std::isxdigit(static_cast<unsigned char>(line[i])))
                i++;

            out += "LOC";
        }
        else
        {
            out += line[i++];
        }
    }

    return out;
}

// Bytes decide, but "byte 3841 of 14337" says nothing about what went wrong. On a mismatch
// both buffers go back through the disassembler and the first differing line is reported.
template <typename Ctx>
auto asm_diff(Ctx* c, std::vector<u8> const& lscript, std::vector<u8> const& lstack, std::vector<u8> const& rscript, std::vector<u8> const& rstack) -> std::string
{
    try
    {
        auto const lhs = print_asm<Ctx>(*c->disassembler().disassemble(lscript, lstack), c);
        auto const rhs = print_asm<Ctx>(*c->disassembler().disassemble(rscript, rstack), c);

        auto li = usize{ 0 };
        auto ri = usize{ 0 };
        auto line = usize{ 1 };

        while (li < lhs.size() && ri < rhs.size())
        {
            auto const le = lhs.find('\n', li);
            auto const re = rhs.find('\n', ri);
            auto const l = lhs.substr(li, le - li);
            auto const r = rhs.substr(ri, re - ri);

            if (blank_labels(l) != blank_labels(r))
                return std::format("line {}: '{}' != '{}'", line, l, r);

            if (le == std::string::npos || re == std::string::npos)
                break;

            li = le + 1;
            ri = re + 1;
            line++;
        }

        return std::format("assembly agrees to line {}, so the difference is in the encoding", line);
    }
    catch (std::exception const& e)
    {
        return std::format("disassembly failed: {}", e.what());
    }
}

// Round trips that cannot be made to pass, with the cause. Every entry is analysed in
// plan/iw5-failures.md; the short forms are below. These are skipped rather than removed so
// the corpus keeps exercising the rest of the pipeline over them -- a file that throws, or
// that starts differing for a *new* reason, still fails.
//
// A listed file that round trips cleanly fails as a stale entry, so the list cannot rot
// behind a fix.
enum class cause
{
    dropped_stmt,   // assert family / dev block emits nothing but still takes the 'last' flag
    switch_strings, // IW orders string case tables by a build-wide string list id
    locals,         // local slot numbering and OP_RemoveLocalVariables placement
    vector_fold,    // vector built at runtime vs folded to OP_GetVector
    source_bug,     // bytecode built from source the parser is right to reject
    decompile_output, // the decompiler prints something that does not parse back -- open
};

auto describe(cause reason) -> std::string_view
{
    switch (reason)
    {
        case cause::dropped_stmt:
            return "dropped statement: a statement that compiles to nothing takes the 'last' flag off the if before it, and prod bytecode keeps no trace that it was ever there";
        case cause::switch_strings:
            return "switch string order: Infinity Ward orders string case tables by the engine string list id, which is build state the bytecode does not carry";
        case cause::locals:
            return "locals: local slot numbering / OP_RemoveLocalVariables placement";
        case cause::vector_fold:
            return "vector folding: a vector with a named-constant component is built at runtime, while the decompiled literal folds to OP_GetVector";
        case cause::source_bug:
            return "source bug: the original compiler swallowed a missing semicolon, and the bytecode cannot be expressed by source our parser should accept";
        case cause::decompile_output:
            return "OPEN BUG: the decompiler prints source that does not parse back -- see plan/iw5-failures.md";
    }

    return "";
}

// The binary corpus is walked three times, each stage a prefix of the one after it, so a
// failure says how far the file got rather than just that it did not come back identical.
enum class stage
{
    decompile, // shipped bytecode -> source
    recompile, // that source back to bytecode
    match,     // and the bytecode is identical
};

// The stage a cause first blocks. Everything that merely changes the bytes gets all the way
// to the comparison; source the parser rejects never gets past the recompile.
auto blocks_at(cause reason) -> stage
{
    switch (reason)
    {
        case cause::source_bug:
        case cause::decompile_output:
            return stage::recompile;
        default:
            return stage::match;
    }
}

enum mode : u8
{
    prod_only = 1,
    dev_only = 2,
    both_modes = 3,
};

struct known_failure
{
    std::string_view file;
    cause reason;
    u8 modes{ both_modes };
};

constexpr known_failure iw5_source_failures[]{
    { "animscripts/battlechatter_ai.gsc",    cause::locals },
    { "animscripts/combat_utility.gsc",      cause::dropped_stmt },
    { "animscripts/face.gsc",                cause::locals },
    { "animscripts/melee.gsc",               cause::locals },
    { "animscripts/squadmanager.gsc",        cause::dropped_stmt },
    { "common_scripts/_destructible.gsc",    cause::locals },
    { "common_scripts/utility.gsc",          cause::locals },
    { "maps/_air_support_strobe.gsc",        cause::locals },
    { "maps/_audio_dynamic_ambi.gsc",        cause::locals },
    { "maps/_audio_mix_manager.gsc",         cause::locals },
    { "maps/_audio_vehicles.gsc",            cause::locals },
    { "maps/_endmission.gsc",                cause::dropped_stmt, prod_only },
    { "maps/_gameevents.gsc",                cause::locals },
    { "maps/_gameskill.gsc",                 cause::locals },
    { "maps/_lights.gsc",                    cause::locals },
    { "maps/_remotemissile.gsc",             cause::dropped_stmt },
    { "maps/_shg_common.gsc",                cause::locals },
    { "maps/_squad_enemies.gsc",             cause::locals },
    { "maps/_utility.gsc",                   cause::dropped_stmt },
    { "maps/_vehicle_aianim.gsc",            cause::dropped_stmt },
    { "maps/berlin_a10.gsc",                 cause::locals },
    { "maps/hamburg_code.gsc",               cause::dropped_stmt },
    { "maps/hamburg_garage.gsc",             cause::locals },
    { "maps/intro_code.gsc",                 cause::locals },
    { "maps/mp/_defcon.gsc",                 cause::locals },
    { "maps/mp/_utility.gsc",                cause::locals },
    { "maps/mp/gametypes/_weapons.gsc",      cause::locals },
    { "maps/mp/gametypes/dd.gsc",            cause::locals },
    { "maps/mp/killstreaks/_a10.gsc",        cause::locals },
    { "maps/ny_harbor_code_sdv.gsc",         cause::vector_fold },
    { "maps/ny_harbor_code_sub.gsc",         cause::locals },
    { "maps/ny_harbor_code_zodiac.gsc",      cause::locals },
    { "maps/ny_hind.gsc",                    cause::locals },
    { "maps/ny_manhattan_fx.gsc",            cause::locals },
    { "maps/paris_shared.gsc",               cause::locals },
    { "maps/payback_env_code.gsc",           cause::locals },
    { "maps/so_infiltrate_intro_breach.gsc", cause::locals },
};

constexpr known_failure iw5_binary_failures[]{
    { "_unnamed/_id_0558.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_055c.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_055d.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_055e.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_0563.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_059f.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_5f9e.gscbin",                     cause::switch_strings },
    { "_unnamed/_id_7081.gscbin",                     cause::switch_strings },
    { "animscripts/corner.gscbin",                    cause::locals },
    { "animscripts/cover_arrival.gscbin",             cause::locals },
    { "animscripts/cover_behavior.gscbin",            cause::locals },
    { "animscripts/dog/dog_combat.gscbin",            cause::switch_strings },
    { "animscripts/dog/dog_move.gscbin",              cause::locals },
    { "animscripts/grenade_return_throw.gscbin",      cause::locals },
    { "animscripts/melee.gscbin",                     cause::locals },
    { "maps/_anim.gscbin",                            cause::switch_strings },
    { "maps/_art.gscbin",                             cause::locals },
    { "maps/_audio.gscbin",                           cause::switch_strings },
    { "maps/_audio_mix_manager.gscbin",               cause::locals },
    { "maps/_drone.gscbin",                           cause::switch_strings },
    { "maps/_endmission.gscbin",                      cause::dropped_stmt },
    { "maps/_gameskill.gscbin",                       cause::locals },
    { "maps/_vehicle.gscbin",                         cause::switch_strings },
    { "maps/_vehicle_aianim.gscbin",                  cause::dropped_stmt },
    { "maps/berlin_vo.gscbin",                        cause::switch_strings },
    { "maps/castle_courtyard_battle.gscbin",          cause::switch_strings },
    { "maps/dubai_code.gscbin",                       cause::locals },
    { "maps/intro_aud.gscbin",                        cause::switch_strings },
    { "maps/mp/gametypes/_gamescore.gscbin",          cause::dropped_stmt },
    { "maps/mp/gametypes/dom.gscbin",                 cause::locals },
    { "maps/mp/gametypes/tjugg.gscbin",               cause::dropped_stmt },
    { "maps/mp/killstreaks/_airdrop.gscbin",          cause::switch_strings },
    { "maps/mp/killstreaks/_deployablebox.gscbin",    cause::switch_strings },
    { "maps/mp/killstreaks/_helicopter.gscbin",       cause::switch_strings },
    { "maps/mp/killstreaks/_helicopter_flock.gscbin", cause::switch_strings },
    { "maps/mp/killstreaks/_helicopter_guard.gscbin", cause::switch_strings },
    { "maps/mp/killstreaks/_killstreaks.gscbin",      cause::switch_strings },
    { "maps/mp/killstreaks/_nuke.gscbin",             cause::locals },
    { "maps/mp/killstreaks/_remotemortar.gscbin",     cause::switch_strings },
    { "maps/mp/killstreaks/_uav.gscbin",              cause::switch_strings },
    { "maps/mp/perks/_perks.gscbin",                  cause::switch_strings },
    { "maps/paris_a.gscbin",                          cause::switch_strings },
    { "maps/payback_main.gscbin",                     cause::switch_strings },
    { "maps/payback_util.gscbin",                     cause::switch_strings },
    { "maps/rescue_2_code.gscbin",                    cause::switch_strings },
};

constexpr known_failure iw6_binary_failures[]{
    { "common_scripts/_bcs_location_trigs.gscbin",                        cause::locals },
    { "common_scripts/_createfx.gscbin",                                  cause::switch_strings },
    { "common_scripts/_createfxmenu.gscbin",                              cause::dropped_stmt },
    { "common_scripts/_csplines.gscbin",                                  cause::locals },
    { "common_scripts/_destructible.gscbin",                              cause::locals },
    { "common_scripts/_dynamic_world.gscbin",                             cause::locals },
    { "common_scripts/_exploder.gscbin",                                  cause::dropped_stmt },
    { "common_scripts/_fx.gscbin",                                        cause::switch_strings },
    { "common_scripts/_pipes.gscbin",                                     cause::locals },
    { "common_scripts/utility.gscbin",                                    cause::locals },
    { "maps/interactive_models/_birds_dlc.gscbin",                        cause::locals },
    { "maps/mp/_awards.gscbin",                                           cause::switch_strings },
    { "maps/mp/_breach.gscbin",                                           cause::switch_strings },
    { "maps/mp/_defcon.gscbin",                                           cause::locals },
    { "maps/mp/_events.gscbin",                                           cause::locals },
    { "maps/mp/_javelin.gscbin",                                          cause::locals },
    { "maps/mp/_laserguidedlauncher.gscbin",                              cause::locals },
    { "maps/mp/_movable_cover.gscbin",                                    cause::switch_strings },
    { "maps/mp/_movers.gscbin",                                           cause::switch_strings },
    { "maps/mp/_teleport.gscbin",                                         cause::locals },
    { "maps/mp/_utility.gscbin",                                          cause::locals },
    { "maps/mp/agents/alien/_alien_agents.gscbin",                        cause::switch_strings },
    { "maps/mp/agents/alien/_alien_bomber.gscbin",                        cause::switch_strings },
    { "maps/mp/agents/alien/_alien_gargoyle.gscbin",                      cause::switch_strings },
    { "maps/mp/agents/alien/_alien_jump.gscbin",                          cause::switch_strings },
    { "maps/mp/agents/alien/_alien_melee.gscbin",                         cause::switch_strings },
    { "maps/mp/agents/alien/_alien_move.gscbin",                          cause::switch_strings },
    { "maps/mp/agents/alien/_alien_seeder.gscbin",                        cause::switch_strings },
    { "maps/mp/agents/alien/_alien_spitter.gscbin",                       cause::switch_strings },
    { "maps/mp/agents/alien/_alien_think.gscbin",                         cause::switch_strings },
    { "maps/mp/agents/alien/_alien_traverse.gscbin",                      cause::locals },
    { "maps/mp/agents/alien/alien_ancestor/_alien_ancestor.gscbin",       cause::switch_strings },
    { "maps/mp/agents/alien/alien_ancestor/_alien_ancestor_melee.gscbin", cause::switch_strings },
    { "maps/mp/agents/alien/alien_ancestor/_alien_ancestor_move.gscbin",  cause::switch_strings },
    { "maps/mp/agents/alien/alien_ancestor/_alien_ancestor_think.gscbin", cause::switch_strings },
    { "maps/mp/agents/alien/alien_kraken/_alien_kraken_melee.gscbin",     cause::switch_strings },
    { "maps/mp/agents/alien/alien_kraken/_alien_tentacle_melee.gscbin",   cause::switch_strings },
    { "maps/mp/agents/alien/alien_spider/_alien_spider.gscbin",           cause::switch_strings },
    { "maps/mp/agents/alien/alien_spider/_alien_spider_melee.gscbin",     cause::switch_strings },
    { "maps/mp/agents/dog/_dog_idle.gscbin",                              cause::switch_strings },
    { "maps/mp/agents/dog/_dog_think.gscbin",                             cause::dropped_stmt },
    { "maps/mp/agents/dog/_dog_traverse.gscbin",                          cause::locals },
    { "maps/mp/alien/_achievement.gscbin",                                cause::switch_strings },
    { "maps/mp/alien/_achievement_dlc.gscbin",                            cause::switch_strings },
    { "maps/mp/alien/_achievement_dlc2.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_achievement_dlc3.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_achievement_dlc4.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_alien_matchdata.gscbin",                            cause::switch_strings },
    { "maps/mp/alien/_alien_vanguard.gscbin",                             cause::locals },
    { "maps/mp/alien/_autosentry_alien.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_beacon_weapon.gscbin",                              cause::switch_strings },
    { "maps/mp/alien/_challenge_function.gscbin",                         cause::switch_strings },
    { "maps/mp/alien/_chaos.gscbin",                                      cause::switch_strings },
    { "maps/mp/alien/_combat_resources.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_container_spawn.gscbin",                            cause::switch_strings },
    { "maps/mp/alien/_crafting.gscbin",                                   cause::locals },
    { "maps/mp/alien/_crafting_traps.gscbin",                             cause::switch_strings },
    { "maps/mp/alien/_death.gscbin",                                      cause::switch_strings },
    { "maps/mp/alien/_deployablebox.gscbin",                              cause::locals },
    { "maps/mp/alien/_deployablebox_functions.gscbin",                    cause::switch_strings },
    { "maps/mp/alien/_dlc3_weapon.gscbin",                                cause::switch_strings },
    { "maps/mp/alien/_drill.gscbin",                                      cause::locals },
    { "maps/mp/alien/_gamescore.gscbin",                                  cause::switch_strings },
    { "maps/mp/alien/_gamescore_armory.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_gamescore_beacon.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_gamescore_dlc3.gscbin",                             cause::switch_strings },
    { "maps/mp/alien/_gamescore_last.gscbin",                             cause::switch_strings },
    { "maps/mp/alien/_hive.gscbin",                                       cause::locals },
    { "maps/mp/alien/_music_and_dialog.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/_nuke.gscbin",                                       cause::locals },
    { "maps/mp/alien/_pillage.gscbin",                                    cause::switch_strings },
    { "maps/mp/alien/_pillage_intel.gscbin",                              cause::switch_strings },
    { "maps/mp/alien/_pillage_locker.gscbin",                             cause::switch_strings },
    { "maps/mp/alien/_progression.gscbin",                                cause::switch_strings },
    { "maps/mp/alien/_spawn_director.gscbin",                             cause::dropped_stmt },
    { "maps/mp/alien/_spawnlogic.gscbin",                                 cause::locals },
    { "maps/mp/alien/_trap.gscbin",                                       cause::switch_strings },
    { "maps/mp/alien/_utility.gscbin",                                    cause::switch_strings },
    { "maps/mp/alien/mp_alien_armory_challenges.gscbin",                  cause::switch_strings },
    { "maps/mp/alien/mp_alien_beacon_challenges.gscbin",                  cause::switch_strings },
    { "maps/mp/alien/mp_alien_dlc3_ark.gscbin",                           cause::switch_strings },
    { "maps/mp/alien/mp_alien_dlc3_challenges.gscbin",                    cause::switch_strings },
    { "maps/mp/alien/mp_alien_last_challenges.gscbin",                    cause::switch_strings },
    { "maps/mp/bots/_bots.gscbin",                                        cause::dropped_stmt },
    { "maps/mp/bots/_bots_fireteam_commander.gscbin",                     cause::switch_strings },
    { "maps/mp/bots/_bots_gametype_blitz.gscbin",                         cause::locals },
    { "maps/mp/bots/_bots_gametype_dom.gscbin",                           cause::switch_strings },
    { "maps/mp/bots/_bots_gametype_infect.gscbin",                        cause::locals },
    { "maps/mp/bots/_bots_gametype_sd.gscbin",                            cause::locals },
    { "maps/mp/bots/_bots_gametype_sotf.gscbin",                          cause::switch_strings },
    { "maps/mp/bots/_bots_gametype_war.gscbin",                           cause::switch_strings },
    { "maps/mp/bots/_bots_ks.gscbin",                                     cause::switch_strings },
    { "maps/mp/bots/_bots_ks_remote_vehicle.gscbin",                      cause::locals },
    { "maps/mp/bots/_bots_loadout.gscbin",                                cause::switch_strings },
    { "maps/mp/bots/_bots_personality.gscbin",                            cause::dropped_stmt },
    { "maps/mp/bots/_bots_strategy.gscbin",                               cause::locals },
    { "maps/mp/bots/_bots_util.gscbin",                                   cause::dropped_stmt },
    { "maps/mp/gametypes/_battlebuddy.gscbin",                            cause::locals },
    { "maps/mp/gametypes/_battlechatter_mp.gscbin",                       cause::locals },
    { "maps/mp/gametypes/_class.gscbin",                                  cause::switch_strings },
    { "maps/mp/gametypes/_damage.gscbin",                                 cause::dropped_stmt },
    { "maps/mp/gametypes/_damagefeedback.gscbin",                         cause::switch_strings },
    { "maps/mp/gametypes/_door.gscbin",                                   cause::locals },
    { "maps/mp/gametypes/_gamelogic.gscbin",                              cause::dropped_stmt },
    { "maps/mp/gametypes/_gameobjects.gscbin",                            cause::locals },
    { "maps/mp/gametypes/_gamescore.gscbin",                              cause::dropped_stmt },
    { "maps/mp/gametypes/_hud_message.gscbin",                            cause::switch_strings },
    { "maps/mp/gametypes/_hud_util.gscbin",                               cause::switch_strings },
    { "maps/mp/gametypes/_intelchallenges.gscbin",                        cause::switch_strings },
    { "maps/mp/gametypes/_killcam.gscbin",                                cause::locals },
    { "maps/mp/gametypes/_menus.gscbin",                                  cause::dropped_stmt },
    { "maps/mp/gametypes/_missions.gscbin",                               cause::switch_strings },
    { "maps/mp/gametypes/_outline.gscbin",                                cause::switch_strings },
    { "maps/mp/gametypes/_rank.gscbin",                                   cause::switch_strings },
    { "maps/mp/gametypes/_shellshock.gscbin",                             cause::locals },
    { "maps/mp/gametypes/_spawnfactor.gscbin",                            cause::locals },
    { "maps/mp/gametypes/_trophy_system.gscbin",                          cause::locals },
    { "maps/mp/gametypes/_tweakables.gscbin",                             cause::switch_strings },
    { "maps/mp/gametypes/_weapons.gscbin",                                cause::locals },
    { "maps/mp/gametypes/aliens.gscbin",                                  cause::switch_strings },
    { "maps/mp/gametypes/blitz.gscbin",                                   cause::locals },
    { "maps/mp/gametypes/dom.gscbin",                                     cause::dropped_stmt },
    { "maps/mp/gametypes/grind.gscbin",                                   cause::switch_strings },
    { "maps/mp/gametypes/gun.gscbin",                                     cause::locals },
    { "maps/mp/gametypes/horde.gscbin",                                   cause::switch_strings },
    { "maps/mp/gametypes/mugger.gscbin",                                  cause::locals },
    { "maps/mp/gametypes/siege.gscbin",                                   cause::switch_strings },
    { "maps/mp/gametypes/sotf.gscbin",                                    cause::locals },
    { "maps/mp/gametypes/sotf_ffa.gscbin",                                cause::locals },
    { "maps/mp/killstreaks/_ac130.gscbin",                                cause::switch_strings },
    { "maps/mp/killstreaks/_airdrop.gscbin",                              cause::switch_strings },
    { "maps/mp/killstreaks/_airstrike.gscbin",                            cause::switch_strings },
    { "maps/mp/killstreaks/_autosentry.gscbin",                           cause::switch_strings },
    { "maps/mp/killstreaks/_ball_drone.gscbin",                           cause::switch_strings },
    { "maps/mp/killstreaks/_deployablebox.gscbin",                        cause::locals },
    { "maps/mp/killstreaks/_escortairdrop.gscbin",                        cause::locals },
    { "maps/mp/killstreaks/_flares.gscbin",                               cause::locals },
    { "maps/mp/killstreaks/_harrier.gscbin",                              cause::switch_strings },
    { "maps/mp/killstreaks/_helicopter_flock.gscbin",                     cause::switch_strings },
    { "maps/mp/killstreaks/_helicopter_guard.gscbin",                     cause::switch_strings },
    { "maps/mp/killstreaks/_juggernaut.gscbin",                           cause::switch_strings },
    { "maps/mp/killstreaks/_juggernaut_predator.gscbin",                  cause::locals },
    { "maps/mp/killstreaks/_killstreaks.gscbin",                          cause::switch_strings },
    { "maps/mp/killstreaks/_lasedstrike.gscbin",                          cause::switch_strings },
    { "maps/mp/killstreaks/_odin.gscbin",                                 cause::switch_strings },
    { "maps/mp/killstreaks/_portableaoegenerator.gscbin",                 cause::locals },
    { "maps/mp/killstreaks/_remotemortar.gscbin",                         cause::switch_strings },
    { "maps/mp/killstreaks/_remotetank.gscbin",                           cause::switch_strings },
    { "maps/mp/killstreaks/_remoteturret.gscbin",                         cause::switch_strings },
    { "maps/mp/killstreaks/_remoteuav.gscbin",                            cause::switch_strings },
    { "maps/mp/killstreaks/_tank.gscbin",                                 cause::locals },
    { "maps/mp/killstreaks/_uav.gscbin",                                  cause::locals },
    { "maps/mp/killstreaks/mp_wolfpack_killstreak.gscbin",                cause::switch_strings },
    { "maps/mp/mp_alien_armory.gscbin",                                   cause::locals },
    { "maps/mp/mp_alien_armory_vignettes.gscbin",                         cause::locals },
    { "maps/mp/mp_alien_beacon.gscbin",                                   cause::switch_strings },
    { "maps/mp/mp_alien_beacon_vignettes.gscbin",                         cause::switch_strings },
    { "maps/mp/mp_alien_dlc3.gscbin",                                     cause::switch_strings },
    { "maps/mp/mp_alien_dlc3_escape.gscbin",                              cause::switch_strings },
    { "maps/mp/mp_alien_last.gscbin",                                     cause::locals },
    { "maps/mp/mp_alien_last_progression.gscbin",                         cause::switch_strings },
    { "maps/mp/mp_alien_last_weapon.gscbin",                              cause::locals },
    { "maps/mp/mp_alien_town.gscbin",                                     cause::switch_strings },
    { "maps/mp/mp_boneyard_ns.gscbin",                                    cause::switch_strings },
    { "maps/mp/mp_ca_killstreaks_a10.gscbin",                             cause::dropped_stmt },
    { "maps/mp/mp_dart_events.gscbin",                                    cause::switch_strings },
    { "maps/mp/mp_descent_new.gscbin",                                    cause::locals },
    { "maps/mp/mp_dig.gscbin",                                            cause::switch_strings },
    { "maps/mp/mp_dome_ns_alien_idle.gscbin",                             cause::switch_strings },
    { "maps/mp/mp_dome_ns_alien_think.gscbin",                            cause::switch_strings },
    { "maps/mp/mp_dome_ns_alien_traverse.gscbin",                         cause::locals },
    { "maps/mp/mp_hashima.gscbin",                                        cause::switch_strings },
    { "maps/mp/mp_lonestar.gscbin",                                       cause::switch_strings },
    { "maps/mp/mp_mine.gscbin",                                           cause::locals },
    { "maps/mp/mp_prisonbreak.gscbin",                                    cause::switch_strings },
    { "maps/mp/mp_shipment_ns.gscbin",                                    cause::switch_strings },
    { "maps/mp/mp_snow.gscbin",                                           cause::locals },
    { "maps/mp/mp_strikezone.gscbin",                                     cause::switch_strings },
    { "maps/mp/mp_warhawk_events.gscbin",                                 cause::locals },
    { "maps/mp/mp_zerosub.gscbin",                                        cause::switch_strings },
    { "maps/mp/perks/_perkfunctions.gscbin",                              cause::locals },
    { "maps/mp/perks/_perks.gscbin",                                      cause::switch_strings },
};

constexpr known_failure h1_binary_failures[]{
    { "animscripts/battlechatter.gscbin",             cause::switch_strings },
    { "animscripts/battlechatter_ai.gscbin",          cause::switch_strings },
    { "animscripts/combat_utility.gscbin",            cause::decompile_output },
    { "animscripts/corner.gscbin",                    cause::switch_strings },
    { "animscripts/cover_behavior.gscbin",            cause::locals },
    { "animscripts/cover_multi.gscbin",               cause::locals },
    { "animscripts/death.gscbin",                     cause::switch_strings },
    { "animscripts/dog/dog_combat.gscbin",            cause::switch_strings },
    { "animscripts/dog/dog_move.gscbin",              cause::locals },
    { "animscripts/face.gscbin",                      cause::switch_strings },
    { "animscripts/grenade_return_throw.gscbin",      cause::locals },
    { "animscripts/init.gscbin",                      cause::locals },
    { "animscripts/melee.gscbin",                     cause::locals },
    { "animscripts/notetracks.gscbin",                cause::switch_strings },
    { "animscripts/pain.gscbin",                      cause::switch_strings },
    { "animscripts/run.gscbin",                       cause::switch_strings },
    { "animscripts/setposemovement.gscbin",           cause::switch_strings },
    { "animscripts/shared.gscbin",                    cause::switch_strings },
    { "animscripts/squadmanager.gscbin",              cause::switch_strings },
    { "animscripts/stairs_utility.gscbin",            cause::decompile_output },
    { "animscripts/swim.gscbin",                      cause::switch_strings },
    { "animscripts/utility.gscbin",                   cause::switch_strings },
    { "animscripts/walk.gscbin",                      cause::switch_strings },
    { "common_scripts/_createfx.gscbin",              cause::switch_strings },
    { "common_scripts/_createfxmenu.gscbin",          cause::dropped_stmt },
    { "common_scripts/_destructible.gscbin",          cause::switch_strings },
    { "common_scripts/_destructible_types.gscbin",    cause::switch_strings },
    { "common_scripts/_dynamic_world.gscbin",         cause::locals },
    { "common_scripts/_exploder.gscbin",              cause::dropped_stmt },
    { "common_scripts/_fx.gscbin",                    cause::switch_strings },
    { "common_scripts/_pipes.gscbin",                 cause::switch_strings },
    { "common_scripts/utility.gscbin",                cause::locals },
    { "maps/_anim.gscbin",                            cause::locals },
    { "maps/_animatedmodels.gscbin",                  cause::locals },
    { "maps/_art.gscbin",                             cause::locals },
    { "maps/_breach.gscbin",                          cause::switch_strings },
    { "maps/_damagefeedback.gscbin",                  cause::dropped_stmt },
    { "maps/_debug.gscbin",                           cause::dropped_stmt },
    { "maps/_drone.gscbin",                           cause::locals },
    { "maps/_drone_base.gscbin",                      cause::switch_strings },
    { "maps/_equalizer.gscbin",                       cause::switch_strings },
    { "maps/_gameskill.gscbin",                       cause::switch_strings },
    { "maps/_helicopter_ai.gscbin",                   cause::switch_strings },
    { "maps/_helicopter_globals.gscbin",              cause::switch_strings },
    { "maps/_intelligence.gscbin",                    cause::locals },
    { "maps/_interactive_objects.gscbin",             cause::switch_strings },
    { "maps/_introscreen.gscbin",                     cause::switch_strings },
    { "maps/_leak.gscbin",                            cause::switch_strings },
    { "maps/_lighting.gscbin",                        cause::locals },
    { "maps/_lights.gscbin",                          cause::locals },
    { "maps/_load.gscbin",                            cause::locals },
    { "maps/_loadout_code.gscbin",                    cause::switch_strings },
    { "maps/_mgturret.gscbin",                        cause::switch_strings },
    { "maps/_names.gscbin",                           cause::switch_strings },
    { "maps/_nightvision.gscbin",                     cause::switch_strings },
    { "maps/_patrol.gscbin",                          cause::switch_strings },
    { "maps/_remotemissile.gscbin",                   cause::dropped_stmt },
    { "maps/_sea.gscbin",                             cause::switch_strings },
    { "maps/_shg_utility.gscbin",                     cause::switch_strings },
    { "maps/_spawner.gscbin",                         cause::switch_strings },
    { "maps/_stealth_behavior.gscbin",                cause::switch_strings },
    { "maps/_stealth_logic.gscbin",                   cause::switch_strings },
    { "maps/_treadfx.gscbin",                         cause::switch_strings },
    { "maps/_trigger.gscbin",                         cause::locals },
    { "maps/_utility.gscbin",                         cause::locals },
    { "maps/_utility_code.gscbin",                    cause::switch_strings },
    { "maps/_vehicle.gscbin",                         cause::switch_strings },
    { "maps/_vehicle_aianim.gscbin",                  cause::dropped_stmt },
    { "maps/_vehicle_code.gscbin",                    cause::switch_strings },
    { "maps/_vehicle_free_drive.gscbin",              cause::locals },
    { "maps/_weather.gscbin",                         cause::switch_strings },
    { "maps/_wibble.gscbin",                          cause::switch_strings },
    { "maps/_zpu.gscbin",                             cause::locals },
    { "maps/ac130_trees.gscbin",                      cause::locals },
    { "maps/aftermath_lighting.gscbin",               cause::locals },
    { "maps/airlift.gscbin",                          cause::switch_strings },
    { "maps/airlift_aud.gscbin",                      cause::switch_strings },
    { "maps/airlift_lighting.gscbin",                 cause::switch_strings },
    { "maps/airplane.gscbin",                         cause::switch_strings },
    { "maps/ambush.gscbin",                           cause::locals },
    { "maps/armada.gscbin",                           cause::switch_strings },
    { "maps/armada_lighting.gscbin",                  cause::switch_strings },
    { "maps/bog_a.gscbin",                            cause::locals },
    { "maps/bog_a_aud.gscbin",                        cause::switch_strings },
    { "maps/bog_a_backhalf.gscbin",                   cause::switch_strings },
    { "maps/bog_a_code.gscbin",                       cause::locals },
    { "maps/bog_b.gscbin",                            cause::switch_strings },
    { "maps/bog_b_aud.gscbin",                        cause::switch_strings },
    { "maps/cargoship.gscbin",                        cause::switch_strings },
    { "maps/cargoship_code.gscbin",                   cause::switch_strings },
    { "maps/cargoship_fx.gscbin",                     cause::switch_strings },
    { "maps/cargoship_lighting.gscbin",               cause::switch_strings },
    { "maps/coup.gscbin",                             cause::switch_strings },
    { "maps/coup_anim.gscbin",                        cause::switch_strings },
    { "maps/hunted.gscbin",                           cause::switch_strings },
    { "maps/hunted_lighting.gscbin",                  cause::switch_strings },
    { "maps/icbm_code.gscbin",                        cause::switch_strings },
    { "maps/icbm_lighting.gscbin",                    cause::switch_strings },
    { "maps/jake_tools.gscbin",                       cause::switch_strings },
    { "maps/jeepride.gscbin",                         cause::locals },
    { "maps/jeepride_aud.gscbin",                     cause::switch_strings },
    { "maps/jeepride_code.gscbin",                    cause::locals },
    { "maps/killhouse.gscbin",                        cause::switch_strings },
    { "maps/killhouse_code.gscbin",                   cause::switch_strings },
    { "maps/launchfacility_a.gscbin",                 cause::switch_strings },
    { "maps/launchfacility_b.gscbin",                 cause::switch_strings },
    { "maps/mo_fastrope.gscbin",                      cause::switch_strings },
    { "maps/mo_tools.gscbin",                         cause::switch_strings },
    { "maps/mp/_audio.gscbin",                        cause::locals },
    { "maps/mp/_awards.gscbin",                       cause::switch_strings },
    { "maps/mp/_events.gscbin",                       cause::switch_strings },
    { "maps/mp/_fx_trigger.gscbin",                   cause::locals },
    { "maps/mp/_matchdata.gscbin",                    cause::locals },
    { "maps/mp/_movers.gscbin",                       cause::switch_strings },
    { "maps/mp/_utility.gscbin",                      cause::dropped_stmt },
    { "maps/mp/_vl_avatar.gscbin",                    cause::locals },
    { "maps/mp/_vl_base.gscbin",                      cause::switch_strings },
    { "maps/mp/_vl_cac.gscbin",                       cause::dropped_stmt },
    { "maps/mp/_vl_camera.gscbin",                    cause::locals },
    { "maps/mp/_vl_depot.gscbin",                     cause::switch_strings },
    { "maps/mp/_water.gscbin",                        cause::locals },
    { "maps/mp/bots/_bots.gscbin",                    cause::locals },
    { "maps/mp/bots/_bots_gametype_common.gscbin",    cause::locals },
    { "maps/mp/bots/_bots_gametype_dd.gscbin",        cause::locals },
    { "maps/mp/bots/_bots_gametype_dom.gscbin",       cause::locals },
    { "maps/mp/bots/_bots_gametype_oldschool.gscbin", cause::locals },
    { "maps/mp/bots/_bots_gametype_sab.gscbin",       cause::locals },
    { "maps/mp/bots/_bots_gametype_sd.gscbin",        cause::locals },
    { "maps/mp/bots/_bots_ks.gscbin",                 cause::dropped_stmt },
    { "maps/mp/bots/_bots_loadout.gscbin",            cause::switch_strings },
    { "maps/mp/bots/_bots_personality.gscbin",        cause::dropped_stmt },
    { "maps/mp/bots/_bots_strategy.gscbin",           cause::locals },
    { "maps/mp/bots/_bots_util.gscbin",               cause::dropped_stmt },
    { "maps/mp/gametypes/_class.gscbin",              cause::locals },
    { "maps/mp/gametypes/_damage.gscbin",             cause::locals },
    { "maps/mp/gametypes/_damagefeedback.gscbin",     cause::switch_strings },
    { "maps/mp/gametypes/_gamelogic.gscbin",          cause::locals },
    { "maps/mp/gametypes/_gameobjects.gscbin",        cause::switch_strings },
    { "maps/mp/gametypes/_gamescores.gscbin",         cause::dropped_stmt },
    { "maps/mp/gametypes/_hardpoints.gscbin",         cause::locals },
    { "maps/mp/gametypes/_hodgepodge.gscbin",         cause::locals },
    { "maps/mp/gametypes/_hodgepodge_ph.gscbin",      cause::locals },
    { "maps/mp/gametypes/_hud_message.gscbin",        cause::dropped_stmt },
    { "maps/mp/gametypes/_hud_util.gscbin",           cause::switch_strings },
    { "maps/mp/gametypes/_legacyspawnlogic.gscbin",   cause::locals },
    { "maps/mp/gametypes/_menus.gscbin",              cause::locals },
    { "maps/mp/gametypes/_misions.gscbin",            cause::switch_strings },
    { "maps/mp/gametypes/_oldschool.gscbin",          cause::switch_strings },
    { "maps/mp/gametypes/_persistence.gscbin",        cause::locals },
    { "maps/mp/gametypes/_tweakables.gscbin",         cause::switch_strings },
    { "maps/mp/gametypes/_weapons.gscbin",            cause::locals },
    { "maps/mp/gametypes/common_sd_sr.gscbin",        cause::dropped_stmt },
    { "maps/mp/gametypes/dd.gscbin",                  cause::source_bug },
    { "maps/mp/gametypes/dom.gscbin",                 cause::locals },
    { "maps/mp/gametypes/hp.gscbin",                  cause::locals },
    { "maps/mp/gametypes/sab.gscbin",                 cause::switch_strings },
    { "maps/scoutsniper.gscbin",                      cause::switch_strings },
    { "maps/scoutsniper_code.gscbin",                 cause::switch_strings },
    { "maps/sniperescape_code.gscbin",                cause::locals },
    { "maps/village_assault_code.gscbin",             cause::switch_strings },
    { "soundscripts/_audio.gscbin",                   cause::switch_strings },
    { "soundscripts/_audio_dynamic_ambi.gscbin",      cause::locals },
    { "soundscripts/_audio_stream_manager.gscbin",    cause::locals },
    { "soundscripts/_audio_vehicle_manager.gscbin",   cause::decompile_output },
    { "soundscripts/_audio_whizby.gscbin",            cause::switch_strings },
    { "soundscripts/_audio_zone_manager.gscbin",      cause::switch_strings },
    { "soundscripts/_snd_common.gscbin",              cause::switch_strings },
    { "soundscripts/_snd_filters.gscbin",             cause::locals },
    { "soundscripts/_snd_playsound.gscbin",           cause::locals },
    { "soundscripts/_snd_timescale.gscbin",           cause::locals },
    { "vehicle_scripts/_attack_heli.gscbin",          cause::switch_strings },
};

// The lists are per game: iw5 and iw6 share plenty of script paths, so a flat table
// keyed on the file name alone would cross-match.
struct failure_list
{
    known_failure const* data;
    usize size;
    std::string_view name;
};

template <usize N>
constexpr auto list_of(known_failure const (&entries)[N], std::string_view name) -> failure_list
{
    return failure_list{ entries, N, name };
}

auto known(failure_list const& list, std::string_view file, u8 mode) -> known_failure const*
{
    for (auto i = usize{ 0 }; i < list.size; i++)
    {
        if (list.data[i].file == file && (list.data[i].modes & mode) != 0)
            return &list.data[i];
    }

    return nullptr;
}

// A known failure is skipped, anything else is reported. Split out because the source and
// binary round trips share the decision but not the comparison.
auto report(known_failure const* issue, bool matched, std::string_view list) -> bool
{
    if (issue == nullptr)
        return false;

    if (matched)
        FAIL(std::format("round trips cleanly but is still listed in {} -- remove it", list));

    SKIP(describe(issue->reason));
    return true;
}

template <typename Ctx>
auto round_trip(Ctx* c, std::string const& name, std::vector<u8> src, u8 mode, failure_list const& list) -> void
{
    auto data = c->assembler().assemble(*c->compiler().compile(name, src));

    // The assembler writes into members it reuses on the next call, so keep a
    // copy of the first result before compiling the printed source.
    auto script = as_vector(std::get<0>(data));
    auto stack = as_vector(std::get<1>(data));

    auto out = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(script, stack)));
    // Named apart from the source so a failure says which of the two compiles threw. The
    // name only feeds error locations, it never reaches the bytecode.
    auto redo = c->assembler().assemble(*c->compiler().compile(name + " (decompiled)", out));

    auto const script_diff = diff(script, std::get<0>(redo));
    auto const stack_diff = diff(stack, std::get<1>(redo));

    if (report(known(list, name, mode), script_diff.empty() && stack_diff.empty(), list.name))
        return;

    CHECK(script_diff == "");
    CHECK(stack_diff == "");
}

// Shipped bytecode in, the same bytecode back out. Stronger than the source round trip
// above: that one only proves we agree with ourselves, this one is measured against what
// Infinity Ward's compiler actually emitted.
//
// The decompiler writes far calls fully qualified rather than emitting '#include', so the
// printed source resolves nothing externally and no read callback is involved.
// Runs the pipeline as far as 'upto' and returns whether it got there cleanly. Only the
// match stage can return false without throwing; the earlier two either work or raise.
template <typename Ctx>
auto binary_pipeline(Ctx* c, std::string const& name, std::vector<u8> const& file, stage upto, std::string& detail) -> bool
{
    auto script = typename fam<Ctx>::asset{};
    script.deserialize(file);

    auto const stack = utils::zlib::decompress(script.buffer, script.length);

    // The shipped bytes cannot be compared directly. OP_GetString and friends keep their
    // string reference in the script as a placeholder the game fills in at load time, and
    // the assembler writes a zero there; a shipped file carries whatever the engine baked
    // in. So the shipped instruction stream is put back through the assembler once to get
    // a baseline in our own placeholder convention, and the round trip is measured against
    // that. Everything else — opcodes, operands, offsets, the string table — still has to
    // match Infinity Ward's compiler byte for byte.
    auto base = c->assembler().assemble(*c->disassembler().disassemble(script.bytecode, stack));
    auto const base_script = as_vector(std::get<0>(base));
    auto const base_stack = as_vector(std::get<1>(base));

    // The decompiler writes far calls fully qualified rather than emitting '#include', so
    // the printed source resolves nothing externally and no read callback is involved.
    auto out = c->printer().print(*c->decompiler().decompile(*c->disassembler().disassemble(base_script, base_stack)));

    if (upto == stage::decompile)
        return true;

    auto redo = c->assembler().assemble(*c->compiler().compile(name, out));

    if (upto == stage::recompile)
        return true;

    auto const redo_script = as_vector(std::get<0>(redo));
    auto const redo_stack = as_vector(std::get<1>(redo));

    if (base_script == redo_script && base_stack == redo_stack)
        return true;

    // asm_diff disassembles both buffers again, so it stays on the failing path.
    detail = std::format("{}\nscript: {}\nstack: {}", asm_diff(c, base_script, base_stack, redo_script, redo_stack), diff(base_script, std::get<0>(redo)), diff(base_stack, std::get<1>(redo)));
    return false;
}

template <typename Ctx>
auto run_binary_stage(Ctx* c, std::string const& name, std::vector<u8> const& file, stage upto, failure_list const& list) -> void
{
    auto const* issue = known(list, name, both_modes);
    auto const expected = issue != nullptr && blocks_at(issue->reason) <= upto;
    auto detail = std::string{};

    if (!expected)
    {
        // Getting this far is the whole point of the corpus, so record it rather than
        // leaving the file with no assertion at all.
        if (binary_pipeline(c, name, file, upto, detail))
        {
            SUCCEED();
            return;
        }

        FAIL(detail);
        return;
    }

    // A listed file may throw rather than merely differ -- source that does not parse back
    // never reaches the comparison -- so the whole run sits inside the guard.
    auto reached = false;

    try
    {
        reached = binary_pipeline(c, name, file, upto, detail);
    }
    catch (std::exception const&)
    {
    }

    if (reached)
        FAIL(std::format("gets past {} cleanly but is still listed in {} -- remove it", upto == stage::match ? "the comparison" : upto == stage::recompile ? "recompile" : "decompile", list.name));

    SKIP(describe(issue->reason));
}

template <typename Ctx>
auto round_trip_corpus(std::string_view game, bool dev, failure_list const& list) -> void
{
    auto const root = corpus_root("raw", game);
    auto* c = engine_ctx<Ctx>(game, dev);

    for (auto const& file : corpus("raw", game, ".gsc"))
    {
        DYNAMIC_SECTION(file)
        {
            round_trip(c, file, utils::file::read(root / file), dev ? dev_only : prod_only, list);
        }
    }
}

template <typename Ctx>
auto binary_corpus(std::string_view game, stage upto, failure_list const& list) -> void
{
    auto const root = corpus_root("bin", game);
    auto* c = engine_ctx<Ctx>(game, false);

    for (auto const& file : corpus("bin", game, ".gscbin"))
    {
        DYNAMIC_SECTION(file)
        {
            run_binary_stage(c, file, utils::file::read(root / file), upto, list);
        }
    }
}

} // namespace

TEST_CASE("iw5 round trips its source (prod)", "[engine][gsc][iw5]")
{
    round_trip_corpus<gsc::iw5_pc::context>("iw5", false, list_of(iw5_source_failures, "iw5_source_failures"));
}

TEST_CASE("iw5 round trips its source (dev)", "[engine][gsc][iw5]")
{
    round_trip_corpus<gsc::iw5_pc::context>("iw5", true, list_of(iw5_source_failures, "iw5_source_failures"));
}

TEST_CASE("iw5 decompiles shipped bytecode", "[engine][gsc][iw5][binary]")
{
    binary_corpus<gsc::iw5_pc::context>("iw5", stage::decompile, list_of(iw5_binary_failures, "iw5_binary_failures"));
}

TEST_CASE("iw5 recompiles decompiled source", "[engine][gsc][iw5][binary]")
{
    binary_corpus<gsc::iw5_pc::context>("iw5", stage::recompile, list_of(iw5_binary_failures, "iw5_binary_failures"));
}

TEST_CASE("iw5 round trips shipped bytecode", "[engine][gsc][iw5][binary]")
{
    binary_corpus<gsc::iw5_pc::context>("iw5", stage::match, list_of(iw5_binary_failures, "iw5_binary_failures"));
}

TEST_CASE("iw6 decompiles shipped bytecode", "[engine][gsc][iw6][binary]")
{
    binary_corpus<gsc::iw6_pc::context>("iw6", stage::decompile, list_of(iw6_binary_failures, "iw6_binary_failures"));
}

TEST_CASE("iw6 recompiles decompiled source", "[engine][gsc][iw6][binary]")
{
    binary_corpus<gsc::iw6_pc::context>("iw6", stage::recompile, list_of(iw6_binary_failures, "iw6_binary_failures"));
}

TEST_CASE("iw6 round trips shipped bytecode", "[engine][gsc][iw6][binary]")
{
    binary_corpus<gsc::iw6_pc::context>("iw6", stage::match, list_of(iw6_binary_failures, "iw6_binary_failures"));
}

TEST_CASE("h1 decompiles shipped bytecode", "[engine][gsc][h1][binary]")
{
    binary_corpus<gsc::h1::context>("h1", stage::decompile, list_of(h1_binary_failures, "h1_binary_failures"));
}

TEST_CASE("h1 recompiles decompiled source", "[engine][gsc][h1][binary]")
{
    binary_corpus<gsc::h1::context>("h1", stage::recompile, list_of(h1_binary_failures, "h1_binary_failures"));
}

TEST_CASE("h1 round trips shipped bytecode", "[engine][gsc][h1][binary]")
{
    binary_corpus<gsc::h1::context>("h1", stage::match, list_of(h1_binary_failures, "h1_binary_failures"));
}

} // namespace xsk::test
