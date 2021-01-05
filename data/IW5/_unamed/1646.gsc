// IW5 PC GSC
// Decompiled by https://github.com/xensik/gsc-tool
#using_animtree("vehicles");
#using_animtree("generic_human");

main( var0, var1, var2, var3, var4 )
{
    _ID95::_ID10946( "blackhawk_minigun", var0, var1, var2 );
    _ID95::_ID10962( ::_ID11037 );
    _ID95::_ID10945( %bh_rotors, undefined, 0 );

    if ( !isdefined( var3 ) )
    {
        var_5 = [];
        var_5["vehicle_blackhawk_minigun_low"] = "explosions/helicopter_explosion";
        var_5["vehicle_blackhawk_minigun_hero"] = "explosions/helicopter_explosion";
        var_5["vehicle_blackhawk_minigun_player"] = "explosions/helicopter_explosion";
        var_5["vehicle_blackhawk_minigun_player_so_ac130"] = "explosions/helicopter_explosion";
        var_5["vehicle_ny_blackhawk"] = "explosions/helicopter_explosion";
        _ID95::_ID10754( "explosions/helicopter_explosion_secondary_small", "tag_engine_left", "blackhawk_helicopter_hit", undefined, undefined, undefined, 0.2, 1 );
        _ID95::_ID10754( "explosions/helicopter_explosion_secondary_small", "elevator_jnt", "blackhawk_helicopter_secondary_exp", undefined, undefined, undefined, 0.5, 1 );
        _ID95::_ID10754( "fire/fire_smoke_trail_L", "elevator_jnt", "blackhawk_helicopter_dying_loop", 1, 0.05, 1, 0.5, 1 );
        _ID95::_ID10754( "explosions/helicopter_explosion_secondary_small", "tag_engine_right", "blackhawk_helicopter_secondary_exp", undefined, undefined, undefined, 2.5, 1 );
        _ID95::_ID10754( "explosions/helicopter_explosion_secondary_small", "tag_deathfx", "blackhawk_helicopter_secondary_exp", undefined, undefined, undefined, 4 );
        _ID95::_ID10754( var_5[var0], undefined, "blackhawk_helicopter_crash", undefined, undefined, undefined, -1, undefined, "stop_crash_loop_sound" );
        _ID95::_ID10756( "explosions/aerial_explosion_heli_large", "tag_deathfx", "blackhawk_helicopter_crash", undefined, undefined, undefined, undefined, 1, undefined, 0 );
    }

    _ID95::_ID10949();
    _ID95::_ID10958( 999, 500, 1500 );
    _ID95::_ID10950( "allies" );
    _ID95::_ID10954( ::_ID15005, ::_ID15004 );
    _ID95::_ID10956( ::_ID16004 );
    _ID95::_ID10957( ::_ID15960 );
    var_6 = randomfloatrange( 0, 1 );
    _ID95::_ID10925( var1, "cockpit_blue_cargo01", "tag_light_cargo01", "misc/aircraft_light_cockpit_red", "interior", 0 );
    _ID95::_ID10925( var1, "cockpit_blue_cockpit01", "tag_light_cockpit01", "misc/aircraft_light_cockpit_blue", "interior", 0 );
    _ID95::_ID10925( var1, "white_blink", "tag_light_belly", "misc/aircraft_light_white_blink", "running", var_6 );
    _ID95::_ID10925( var1, "white_blink_tail", "tag_light_tail", "misc/aircraft_light_white_blink", "running", var_6 );
    _ID95::_ID10925( var1, "wingtip_green", "tag_light_L_wing", "misc/aircraft_light_wingtip_green", "running", var_6 );
    _ID95::_ID10925( var1, "wingtip_red", "tag_light_R_wing", "misc/aircraft_light_wingtip_red", "running", var_6 );

    if ( isdefined( var_5 ) )
        _ID95::_ID10826( var_5, "tag_doorgun", "weapon_blackhawk_minigun", undefined, undefined, 0.2, 20, -14 );
}

_ID11037()
{
    if ( _ID65::_ID7717() )
    {
        self._ID10590 = distance( self gettagorigin( "tag_origin" ), self gettagorigin( "tag_ground" ) );
        self._ID10586 = 762;
    }
    else
        self._ID10586 = 762 + distance( self gettagorigin( "tag_origin" ), self gettagorigin( "tag_ground" ) );

    self._ID10561 = 0;
}

_ID15004( var0 )
{
    for ( var_1 = 0; var_1 < var0.size; var_1++ )
        var0[var_1]._ID9507 = %bh_idle;

    return var0;
}

_ID15005()
{
    var_0 = [];

    for ( var_1 = 0; var_1 < 8; var_1++ )
        var_0[var_1] = spawnstruct();

    var_0[0]._ID3929 = %bh_pilot_idle;
    var_0[1]._ID3929 = %bh_copilot_idle;
    var_0[2]._ID3929 = %bh_1_idle;
    var_0[3]._ID3929 = %bh_2_idle;
    var_0[4]._ID3929 = %bh_4_idle;
    var_0[5]._ID3929 = %bh_5_idle;
    var_0[6]._ID3929 = %bh_8_idle;
    var_0[7]._ID3929 = %bh_6_idle;
    var_0[0]._ID9458 = "tag_detach";
    var_0[1]._ID9458 = "tag_detach";
    var_0[2]._ID9458 = "tag_detach";
    var_0[3]._ID9458 = "tag_detach";
    var_0[4]._ID9458 = "tag_detach";
    var_0[5]._ID9458 = "tag_detach";
    var_0[6]._ID9458 = "tag_detach";
    var_0[7]._ID9458 = "tag_detach";
    var_0[2]._ID9596 = %bh_1_drop;
    var_0[3]._ID9596 = %bh_2_drop;
    var_0[4]._ID9596 = %bh_4_drop;
    var_0[5]._ID9596 = %bh_5_drop;
    var_0[6]._ID9596 = %bh_8_drop;
    var_0[7]._ID9596 = %bh_6_drop;
    var_0[2]._ID9626 = "crouch";
    var_0[3]._ID9626 = "crouch";
    var_0[4]._ID9626 = "crouch";
    var_0[5]._ID9626 = "crouch";
    var_0[6]._ID9626 = "crouch";
    var_0[7]._ID9626 = "crouch";
    var_0[2]._ID9585 = 1;
    var_0[3]._ID9585 = 1;
    var_0[4]._ID9585 = 1;
    var_0[5]._ID9585 = 1;
    var_0[6]._ID9585 = 1;
    var_0[7]._ID9585 = 1;
    var_0[2]._ID9618 = %fastrope_fall;
    var_0[3]._ID9618 = %fastrope_fall;
    var_0[4]._ID9618 = %fastrope_fall;
    var_0[5]._ID9618 = %fastrope_fall;
    var_0[6]._ID9618 = %fastrope_fall;
    var_0[7]._ID9618 = %fastrope_fall;
    var_0[1]._ID9616 = 1;
    var_0[2]._ID9616 = 1;
    var_0[3]._ID9616 = 1;
    var_0[4]._ID9616 = 1;
    var_0[5]._ID9616 = 1;
    var_0[6]._ID9616 = 1;
    var_0[7]._ID9616 = 1;
    var_0[2]._ID9613 = "fastrope_loop_npc";
    var_0[3]._ID9613 = "fastrope_loop_npc";
    var_0[4]._ID9613 = "fastrope_loop_npc";
    var_0[5]._ID9613 = "fastrope_loop_npc";
    var_0[6]._ID9613 = "fastrope_loop_npc";
    var_0[7]._ID9613 = "fastrope_loop_npc";
    var_0[2]._ID9578 = "TAG_FastRope_RI";
    var_0[3]._ID9578 = "TAG_FastRope_RI";
    var_0[4]._ID9578 = "TAG_FastRope_LE";
    var_0[5]._ID9578 = "TAG_FastRope_LE";
    var_0[6]._ID9578 = "TAG_FastRope_RI";
    var_0[7]._ID9578 = "TAG_FastRope_LE";
    return var_0;
}

_ID15960()
{
    var_0 = [];
    var_0["left"] = [];
    var_0["right"] = [];
    var_0["both"] = [];
    var_0["left"][var_0["left"].size] = 4;
    var_0["left"][var_0["left"].size] = 5;
    var_0["left"][var_0["left"].size] = 7;
    var_0["right"][var_0["right"].size] = 2;
    var_0["right"][var_0["right"].size] = 3;
    var_0["right"][var_0["right"].size] = 6;
    var_0["both"][var_0["both"].size] = 2;
    var_0["both"][var_0["both"].size] = 3;
    var_0["both"][var_0["both"].size] = 4;
    var_0["both"][var_0["both"].size] = 5;
    var_0["both"][var_0["both"].size] = 6;
    var_0["both"][var_0["both"].size] = 7;
    var_0["default"] = var_0["both"];
    return var_0;
}

_ID16004()
{
    var_0 = [];
    var_0["TAG_FastRope_LE"] = spawnstruct();
    var_0["TAG_FastRope_LE"].model = "rope_test";
    var_0["TAG_FastRope_LE"].tag = "TAG_FastRope_LE";
    var_0["TAG_FastRope_LE"]._ID8216 = %bh_rope_idle_le;
    var_0["TAG_FastRope_LE"]._ID9591 = %bh_rope_drop_le;
    var_0["TAG_FastRope_RI"] = spawnstruct();
    var_0["TAG_FastRope_RI"].model = "rope_test_ri";
    var_0["TAG_FastRope_RI"].tag = "TAG_FastRope_RI";
    var_0["TAG_FastRope_RI"]._ID8216 = %bh_rope_idle_ri;
    var_0["TAG_FastRope_RI"]._ID9591 = %bh_rope_drop_ri;
    var_1 = getarraykeys( var_0 );

    for ( var_2 = 0; var_2 < var_1.size; var_2++ )
        precachemodel( var_0[var_1[var_2]].model );

    return var_0;
}

_ID17819( var0, var1, var2 )
{
    if ( !isdefined( var1 ) )
        var1 = level.player;

    self._ID17746 = var1;

    if ( !isdefined( var2 ) )
        var2 = 1;

    thread _ID17813( var2 );
    var1 allowprone( 0 );
    var1 allowcrouch( 0 );

    if ( !isdefined( var0 ) )
    {
        var1 disableweapons();
        _ID65::_ID9994( var1, "tag_player", 1, 1, 30, 30, 30, 30 );
    }

    self useby( var1 );
    var_3 = self gettagangles( "tag_player" );
    var1 setplayerangles( var_3 + ( 0, 0, 0 ) );
    common_scripts\utility::flag_set( "player_on_minigun" );
    thread _ID1597::_ID17742();
}

_ID18564()
{
    self useby( self._ID17746 );
    self._ID17746 unlink();
    level notify( "player_off_blackhawk_gun" );
}

_ID17813( var0 )
{
    wait 0.05;

    if ( var0 )
    {
        setsaveddvar( "ui_hidemap", 1 );
        setsaveddvar( "hud_showStance", "0" );
        setsaveddvar( "compass", "0" );
        setdvar( "old_compass", "0" );
        setsaveddvar( "ammoCounterHide", "1" );
    }
    else
    {
        setsaveddvar( "ui_hidemap", 0 );
        setsaveddvar( "hud_drawhud", "1" );
        setsaveddvar( "hud_showStance", "1" );
        setsaveddvar( "compass", "1" );
        setdvar( "old_compass", "1" );
        setsaveddvar( "ammoCounterHide", "0" );
    }
}
