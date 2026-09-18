# CLAUDE.md

Knowledge base and working guidelines for this repo. Core code is in `include/xsk/` (public headers) and `src/` (implementation). Headers mirror the `src/` layout 1:1.

## What this is

`gsc-tool` compiles and decompiles Call of Duty game scripts (GSC/CSC). One CLI (`gsc-tool`) drives six modes across 15 games and several platforms.

Two independent engine families, same shape, separate code:

- **`xsk::gsc`** (`src/gsc/`, `include/xsk/gsc/`) — Infinity Ward / Sledgehammer / certain remasters: `iw5 iw6 iw7 iw8 iw9 s1 s2 s4 h1 h2`.
- **`xsk::arc`** (`src/arc/`, `include/xsk/arc/`) — Treyarch + Jupiter: `t6 t7 t8 t9 jup`.

They do **not** share a base class. They share a design, not code. A change in one usually needs the mirrored change in the other — check both. This duplication is deliberate: opcode models, AST node sets and bytecode formats genuinely diverge, and a forced CRTP/template base would cost more than the copy. Only byte-identical helpers are worth extracting.

Shared code is small and lives in two places:
- `xsk::utils` (`src/utils/`, `include/xsk/utils/`) — file I/O, endian-aware `reader`/`writer`, zlib wrappers, string helpers.
- `include/xsk/stdinc.hpp` (std umbrella + integer aliases) and `include/xsk/pool.hpp` (node allocator), both at the `xsk` root.

## Pipeline

```
source (.gsc/.csc)
  └─ lexer ──→ preprocessor ──→ parser (recursive descent) ──→ AST (program)
                                                                  └─ compiler ──→ assembly ──→ assembler ──→ bytecode (.gscbin)

bytecode (.gscbin)
  └─ disassembler ──→ assembly ──→ decompiler ──→ AST ──→ printer ──→ source
```

`context` (`include/xsk/{gsc,arc}/context.hpp`) owns six stages as direct members, reached via `ctx->parser()`, `ctx->compiler()`, `ctx->printer()`, `ctx->assembler()`, `ctx->disassembler()`, `ctx->decompiler()`.

The lexer and preprocessor are **not** context members — the chain is nested by ownership: `parser` holds a `preprocessor ppr_`, which holds a `std::stack<lexer>` (one frame per `#include`/`#inline` push). The parser drives it one token at a time with a single token of lookahead (`tok_` / `next_` / `has_next_`).

**The parser is hand-written recursive descent** (`src/gsc/parser.cpp`, `src/arc/parser.cpp`), one `parse_*` method per grammar rule, with `check`/`match`/`expect`/`peek`/`advance` over the preprocessed token stream. There is no Bison and no `gen/` directory. `GscLexer.g4` / `GscParser.g4` at the repo root are an **ANTLR reference grammar for documentation only** — not built, not the source of truth; the C++ in `parser.cpp` is.

The preprocessor is a full C-style one: `#if/#ifdef/#elif/#else/#endif` with its own integer expression evaluator (`eval_expr_*`), `#define` with function-like macro expansion, `#include`/`#inline`/`#using_animtree`, `__DATE__`/`__TIME__`. Directives live in `common/directive.hpp`; macros in `common/define.hpp`; inter-token whitespace is tracked as `spacing` (`common/space.hpp`) so the printer can round-trip layout.

## Engine model (no virtual dispatch)

An engine variant is a `context` subclass that fills in opcode tables, name/hash maps, feature flags, endianness, and platform. Examples: `iw5_pc`, `iw9`, `t6::ps3`, `jup`. Constructors do nothing but set flags and `reserve`+fill the maps from `extern` static arrays.

Per-engine metadata lives in split files under `src/<fam>/engine/`:

- `*_code.cpp` — opcode ↔ id tables (both families)
- `*_func.cpp` / `*_meth.cpp` / `*_token.cpp` — builtin function/method names and canonical string tables (**`gsc` only**)
- `*_hash.cpp` — hashed-id lookup tables (`iw9`, and **every** `arc` engine, which resolves names purely by hash)
- `*_path.cpp` — hashed script paths (`iw9`)

The base `context` reads these maps; it does not branch per engine. Behavior differences are driven by **feature flags**, not `if (engine == ...)`.

Feature flags are bitfields and the two families have **different** sets:
- `gsc::feature` (`include/xsk/gsc/common/types.hpp`): `str4 tok4 waitframe params boolfuncs boolnotand offs8 offs9 extension hash farcall foreach`.
- `arc::feature` (`include/xsk/arc/common/types.hpp`): `v2 v3 header64 header72 headerxx size64 hashids devstr spaces globals refvarg foreach`.

When adding engine behavior, prefer a new feature flag checked in the shared stage over a per-engine branch.

## Runtime dispatch

`src/tool/main.cpp` (~1350 lines) is the CLI. It owns two parallel registries, one in `xsk::gsc` and one in `xsk::arc`:

```cpp
std::map<game, std::map<mach, std::unique_ptr<context>>> contexts;
std::map<mode, std::function<result(game, mach, fs::path, fs::path)>> funcs;
```

Contexts are lazily constructed in `init_<game>()` (16 near-identical switch clones) and selected at call sites with `contexts[game][mach]->stage()`. `game < game::t6` routes to `gsc`; `>= t6` routes to `arc`. Note `ps4/ps5/xb3/xb4` all collapse to `mach::pc` in `parse_system`. Each `*_file` function catches `std::exception` and returns `result::failure` so one bad file doesn't abort a directory walk.

## CLI

```
gsc-tool -m <mode> -g <game> -s <system> [opts] <path>
```
Modes: `asm disasm comp decomp parse rename`. Flags: `-i instance(server|client)`, `-w workdir`, `-y dry`, `-d dev`, `-z zonetool`, `--t6fixup`, `-h`, `-v`. Output goes to `assembled/ disassembled/ compiled/ decompiled/ parsed/ renamed/`, each under a `<game>/` subdir. `-d/dev` enables dev blocks and emits a `.gscmap` bytecode map into `compiled/developer_maps/`. `--t6fixup` sets `arc::context::fixup()` for scripts from broken third-party compilers.

## Build

```bash
scripts/generate.sh                       # submodules + premake5 gmake2  (scripts/generate.bat on Windows)
scripts/build_macos_arm64_release.sh      # or make -C build config=release_arm64 -j$(sysctl -n hw.ncpu)
```

Raw equivalent: `premake5 gmake2` (Linux/macOS) or `premake5 vs2022` (Windows), then `make -C build config=<cfg>`. Configs are `{debug,release}_{arm64,amd64}`; Windows adds `x86`/`x64`. Binaries land in `build/bin/<platform>/<config>/`.

- **C++20**, static runtime, `warnings "Extra"`, **release sets `fatalwarnings "All"`** — release must be warning-clean.
- Debug builds on non-Windows add `-Wglobal-constructors -Wexit-time-destructors` (`report_static_init()` in `premake5.lua`). **Keep static state constant-initialized** — no work before `main`, no destructors after `exit`. `pool`'s thread-locals are POD-and-zero for exactly this reason. Release skips the flags because cxxopts trips them.
- `premake5.lua` regenerates `include/xsk/version.hpp` from git tags/branch/rev-count on every run (gitignored; don't hand-edit).
- Five projects: apps `xsk-tool` (target `gsc-tool`) and `xsk-tests`; static libs `xsk-utils`, `xsk-gsc`, `xsk-arc`; vendored `zlib`. `cxxopts` and `catch2` are header-only/amalgamated. Deps are git submodules in `deps/` with a `.lua` module each.
- CI (`.github/workflows/main.yml`) builds release on Windows (x86/x64/arm64), macOS (amd64/arm64) and Linux (amd64/arm64, clang-18), runs `xsk-tests` on every arch it can, and on tag push drafts a GitHub release plus a multi-arch Docker image signed with cosign.

## Testing

There is a Catch2 test target (`test/`, built as `xsk-tests`) — `test/main.cpp` defines `main` explicitly because MSVC won't pull it from the amalgamated lib.

```bash
make -C build config=release_arm64 -j8 && ./build/bin/arm64/release/xsk-tests
./build/bin/arm64/release/xsk-tests "[lexer]"     # tags: [utils] [lexer] [ppr], plus [gsc] [arc] [feature]
```

Covered today: `utils` (reader/writer endianness, zlib), the **lexer** and the **preprocessor**. Nothing covers parser, compiler, assembler or decompiler.

`test/common.hpp` carries the shared scaffolding. The lexer and preprocessor are the same code in both families modulo feature flags, so generic cases are written once and instantiated for both with `TEMPLATE_TEST_CASE`; `fam<Ctx>` is the bridge that maps a context type to its family's `token`/`lexer`/`preprocessor`/error types. Helpers: `lex_all` / `lex_names` (kinds as text, so a failure reads `expected '+' got 'integer'`), `ppr_all` / `ppr_text`. Contexts come from `ctx<C>()` / `ctx_dev<C>()`, built once and deliberately leaked — construction costs 1–19 ms depending on engine (t7 loads 180k hashes) and a static with a destructor would trip the debug `-Wexit-time-destructors`.

Generic cases run on `iw5_pc` + `t6::pc`. Anything gated by a feature flag gets its own `[feature]` test naming both sides of the gate — `feature::size64` for `===`/`!==`/`->` and for `#using`/`#insert`/`#precache` (t7 yes, t6 no), `build::dev` for `/# #/`, and the engine-name macro the preprocessor predefines (`IW5`, `T6` — uppercase; lowercasing identifiers is the parser's job, not the preprocessor's).

**Preprocessor expectations are contrasted against `clang -E -P -std=c2x`.** It is a C-style preprocessor, so clang is the oracle for macro semantics — expansion, blue paint, `#`/`##`, variadics. Do that before assuming what the right answer is.

**Adding a test file requires re-running `premake5 gmake2`** — premake resolves the `./test/**.cpp` glob at generation time, so a new file is silently ignored by an existing makefile.

New unit-testable logic should get a `TEST_CASE`. For pipeline changes, the real check is still a **round-trip diff**:

```bash
./build/bin/arm64/release/gsc-tool -m decomp -g iw5 -s pc ./data/iw5/<file>.gscbin
```

`data/` and every output dir (`compiled/ decompiled/ disassembled/ assembled/ parsed/ renamed/`) are **gitignored** — there is no committed reference tree, so `git diff` won't tell you anything. Snapshot the output dir before your change (`cp -r decompiled decompiled.before`) and `diff -r` against it after. A non-empty diff is either your intended improvement or a regression — decide which and say so. Same idea for `comp`→`decomp` and `asm`→`disasm` round trips.

## Formatting & linting

```bash
scripts/format.sh            # clang-format dry-run check (--Werror)
scripts/format.sh --apply    # rewrite in place
scripts/tidy.sh              # clang-tidy; --fix to apply
```

- `.clang-format`: LLVM base, 4 spaces, **Allman braces**, `ColumnLimit: 0` (no auto-wrapping — break lines by hand), `PointerAlignment: Left`, `SortIncludes: Never` (include order is deliberate).
- `.clang-format-ignore` and both scripts skip `src/*/engine/*_{code,func,meth,token,hash,path}.cpp` — those are generated-style data tables, not hand-written code. Never reformat them.
- `.clang-tidy` runs `bugprone-* cppcoreguidelines-* modernize-* performance-* readability-*` with a long opt-out list; headers are diagnosed only under `include/ src/ test/`. `tidy.sh` needs `compile_commands.json` at the repo root: `bear --output compile_commands.json -- make -C build -j8` (gitignored).
- `.editorconfig`: UTF-8, LF, final newline, trim trailing whitespace; 4 spaces for C++, 2 for yaml/json/sh.

## Code conventions (match the existing style)

- **English only, everywhere in the repo.** Code comments, doc comments, commit messages, Markdown docs, config-file comments, test case and `SECTION` names, error message strings, and any other string literal. This holds regardless of the language the request was written in — a conversation in Spanish still produces English artifacts. Non-ASCII characters are allowed only where they carry meaning (e.g. `—` in prose); never as a side effect of writing in another language.
- Every file starts with the 4-line `// Copyright 2026 xensik.` GPLv3 header, then `#pragma once` for headers.
- Namespaces: `xsk`, `xsk::gsc`, `xsk::arc`, `xsk::utils`; engine variants nest (`xsk::gsc::iw5_pc`, `xsk::arc::t6::ps3`). Close with `} // namespace xsk::gsc`.
- `snake_case` for everything; private members suffixed `_` (`ctx_`, `tok_`, `next_`). `struct` over `class` throughout, with explicit `public:`/`private:` sections.
- **East const**, consistently: `std::string const&`, `auto const&`, `char const*`. Never `const std::string&`.
- Trailing return syntax everywhere: `auto f() -> T`. Match it, including for `void`.
- Type aliases from `xsk/stdinc.hpp`: `u8 u16 u32 u64`, `i8..i64`, `f32 f64`, `usize`. Use them, never the raw `std::uint32_t` spellings (older code in `main.cpp` still does; new code shouldn't).
- `#include "xsk/stdinc.hpp"` first (it pulls the whole std lib + aliases), then component headers. `common/*.hpp` headers rely on `types.hpp` having included `stdinc.hpp` and include nothing themselves — keep that order. Keep `.cpp` includes minimal.
- AST: every node has `using ptr = std::unique_ptr<T>` and a static `make()`; node kind via the `node::type` enum (`common/ast.hpp`); test/cast with the node's own `is<T>()`/`as<T>()` template helpers, never `dynamic_cast`.
- AST nodes and assembly instructions are **pool-allocated**: they declare `XSK_POOLED` (`include/xsk/pool.hpp`), a thread-local size-class free list. Only the *sized* `operator delete` is declared, on purpose, so any deletion path that can't supply the size fails to compile. New hot small types can opt in the same way; anything else uses the normal allocator.
- Ownership is `unique_ptr` end to end. The decompiler rebuilds the AST by simulating a stack of `node::ptr`.
- Binary I/O: always go through `utils::reader`/`utils::writer`; they handle endianness via a swap flag. Never raw-cast pointers into the byte buffer.
- Errors are exceptions, one identical set per family (`common/exception.hpp`): `comp_error`/`ppr_error` carry a `location`; `error`/`asm_error`/`disasm_error`/`decomp_error` are message-only. `main.cpp` catches `std::exception` per file and continues.
- Mark deliberate shortcuts with a `ponytail:` comment naming the ceiling and the upgrade path (see `pool.hpp` for the pattern).

## File formats

- `.gscbin` (IW): `"GSC\0"` magic + `compressedLen`/`len`/`bytecodeLen` (little-endian on PS3/Xbox360 too) + zlib buffer + bytecode. Serialized by the `asset` struct (`gsc/common/asset.hpp`).
- `.cgsc` + `.cgsc.stack` (zonetool mode, `-z`): separate bytecode and decompressed stack files.
- `arc` (T6): single `.gsc`/`.csc` buffer with a `\x80GSC` header; later Treyarch engines vary by the `header64`/`header72`/`headerxx` flags.
- Recognized input extensions are table-driven in `main.cpp` (`gsc_exts` / `arc_exts`).

## Current state

Actively in flux — don't treat surprising code there as a bug to "fix" without checking intent:

- **Parser rewrite** — the hand-written `lexer`/`preprocessor`/`parser` (landed in #276, replacing the ANTLR/Bison experiments) is the headline v3 work and still settling. Expect rough edges and incomplete rules.
- **New engines** — `t8 t9 jup` are stubs: their `*_code.cpp` tables are ~15 lines of placeholder and there's no decompiler support. `t7` has full hash/opcode tables and syntax support (#280) but is decompile-oriented. `include/xsk/gsc/engine/t4.hpp` and `t5.hpp` exist with opcode enums but **no `.cpp` and no `main.cpp` registration** — early scaffolding, not wired up.
- **Perf work** — pooled allocation and the inlined `lookahead::advance` (#088c1a4) are recent; `lookahead.hpp` deliberately defines `advance()` in the header so it inlines without LTO.

Stable enough to rely on: the IW `gsc` engines through `iw9`, `t6` in `arc`, the `utils` layer, and the `.gscbin`/`.cgsc` formats.

`plan/improvements.md` (gitignored scratch) holds a ranked backlog of known duplication and cleanup items — worth reading before proposing a refactor, since several "obvious" ones are marked *leave it* with a reason.

Git: feature branches off `dev`, PRs into `dev`; `prod` is the release branch. Branch before committing; don't push unless asked.

> Note: `.github/copilot-instructions.md` predates the parser rewrite and describes a Bison/`gen/` setup that no longer exists. Trust this file over it.

## Doing work here

- Editing grammar/syntax → edit `src/<fam>/parser.cpp` (and `lexer.cpp`/`preprocessor.cpp` as needed) directly. Update the `.g4` files only to keep the reference doc in sync; they don't affect the build.
- Adding/fixing an engine → touch its `engine/<name>.cpp` + the `*_code`/`_func`/`_meth`/`_token`/`_hash` tables, the header in `include/xsk/<fam>/engine/`, and register it in `main.cpp` (`init_<game>` + the `games`/`games_rev`/`machs` maps + the `-g` help string). Set feature flags in the context constructor.
- A behavior that differs by game is almost always a feature flag, not an `if`.
- Whatever you change in one family, check whether `gsc` and `arc` both need it.
- Before opening a PR: `scripts/format.sh`, a release build (warnings are fatal there), `xsk-tests`, and a round-trip diff for anything touching a pipeline stage.
