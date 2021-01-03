// IW5 PC GSC
// Decompiled by https://github.com/xensik/gsc-tool

_ID19918( var0 )
{
    if ( !isdefined( var0 ) )
        var0 = 0;

    setdvarifuninitialized( "a10_strike_controls", "points" );
    setdvarifuninitialized( "airstrike_weapon", "a10" );
    setdvarifuninitialized( "a10_strike_debug", "0" );
    setdvarifuninitialized( "a10_strike_generate_path", "0" );
    level._ID19919 = 0;
    level._ID19920 = 2;
    level._ID19921 = 0.5;
    level._ID19922 = 0.15;
    level._ID19923 = 0;
    level._ID19924 = 1;
    level._ID19925 = 1;
    level._ID19926 = 3;
    level._ID19927 = ( 0, 0, 512 );
    level._ID19928 = 512;
    level._ID19929 = 512;
    level._ID19930 = 512;
    level._ID19931 = 256;
    level._ID19932 = 0;
    level._ID19933 = level._ID19920 + level._ID19921;
    level._ID19933 = getdvarint( "a10_strike_cooldown", level._ID19933 );

    if ( !isdefined( level._ID19934 ) )
    {
        level._ID19934 = _ID98::createFontString( "default", 2 );
        level._ID19934 _ID98::setPoint( "TOP", undefined, 0, 80 );
        level._ID19934.label = &"BERLIN_ACTIVATE_A10";
        level._ID19934.alpha = 1;
        level._ID19934.sort = 0.5;
        level._ID19934.foreground = 1;
    }

    if ( !isdefined( level._ID19935 ) )
    {
        level._ID19935 = _ID98::createFontString( "default", 2 );
        level._ID19935 _ID98::setPoint( "TOP", undefined, 0, 80 );
        level._ID19935.label = &"BERLIN_DIRECT_A10";
        level._ID19935.alpha = 0;
        level._ID19935.sort = 0.5;
    }

    level.player notifyonplayercommand( "toggle_airstrike", "+actionslot 4" );

    if ( !isdefined( level._ID19936 ) )
        level._ID19936 = [];

    thread _ID19939();
    wait 1;

    if ( !var0 )
        thread _ID20004();
}

_ID19937()
{
    level._ID19938 = 1;
    level.player notify( "turn_off_airstrike" );
    level.player notify( "airstrike_deactivated" );
    _ID19943();
    _ID20001( 0 );
    level.player setweaponhudiconoverride( "actionslot4", "none" );
}

_ID19939()
{
    level.player endon( "turn_off_airstrike" );
    level.player notify( "airstrike_available" );
    var_0 = getdvar( "a10_strike_controls" );
    level._ID19940 = 1;
    level.player setweaponhudiconoverride( "actionslot4", "dpad_soflam_static" );
    _ID20001( 0 );
    level.player waittill( "toggle_airstrike" );
    level.player _ID20032();
    level.player _ID20016( var_0 );

    if ( level.player getcurrentweapon() != level.player getcurrentprimaryweapon() )
    {
        level.player switchtoweapon( level.player getcurrentprimaryweapon() );
        wait 0.5;
    }

    if ( isdefined( level._ID19934 ) )
        level._ID19934.alpha = 0;

    if ( var_0 == "static" )
        level._ID19935.label = &"BERLIN_DIRECT_A10_STATIC";

    level._ID19935.alpha = 1;
    thread _ID20014();
    thread _ID20013();
    level.player notifyonplayercommand( "trigger_a10", "+attack" );
    thread _ID19941();
    thread _ID19942();
    thread _ID19949( 1 );
}

_ID19941()
{
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    level.player waittill( "toggle_airstrike" );
    level.player notify( "airstrike_deactivated" );
    _ID103::_ID5719( "a10_cancelled" );
    _ID20001( 0 );
    _ID19943();
    wait 0.5;
    thread _ID19939();
}

_ID19942()
{
    level.player endon( "airstrike_deactivated" );
    level.player endon( "turn_off_airstrike" );
    level.player waittill( "airstrike_called" );
    thread _ID20003();
    wait(level._ID19922);
    _ID20001( 0 );
    wait 0.7;
    _ID19943();
    level.player setweaponhudiconoverride( "actionslot4", "dpad_soflam_inactive" );
    level.player waittill( "a10_anim_complete" );
    wait(level._ID19933);
    thread _ID19939();
    wait 1;
    thread _ID20004();
}

_ID19943()
{
    var_0 = getdvar( "a10_strike_controls" );
    _ID20011();
    level.player _ID20048();

    if ( !isdefined( level._ID19938 ) || level._ID19938 == 0 )
        thread _ID19945();

    if ( isdefined( level._ID19944 ) )
    {
        var_1 = level.player getnormalizedmovement();

        if ( var_1 != ( 0, 0, 0 ) )
            wait 0.5;
        else
            wait 0.3;

        _ID20015();
    }
    else
        wait 0.3;

    level.player _ID20017( var_1 );
    level._ID19940 = 0;
}

_ID19945()
{
    level.player endon( "turn_off_airstrike" );
    level.player endon( "airstrike_available" );

    for (;;)
    {
        level.player waittill( "toggle_airstrike" );
        _ID20006();
    }
}

_ID19946()
{
    if ( !isdefined( level._ID19947 ) )
    {
        var_0 = getdvar( "a10_strike_controls" );
        level._ID19947 = spawn( "script_model", ( 0, 0, 0 ) );
        level._ID19947 setmodel( "tag_origin" );
        level._ID19947.angles = ( -90, 0, 0 );
        level._ID19948 = spawn( "script_model", ( 0, 0, 0 ) );
        level._ID19948 setmodel( "tag_origin" );

        if ( var_0 == "points" )
            playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19947, "tag_origin" );
        else if ( var_0 == "click" )
            playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19947, "tag_origin" );
        else
        {
            playfxontag( common_scripts\utility::getfx( "a10_target" ), level._ID19947, "tag_origin" );
            thread _ID19958();
            thread _ID19959();
        }
    }
}

_ID19949( var0 )
{
    self endon( "kill_draw_target_aim" );
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    var_1 = getdvar( "a10_strike_controls" );

    if ( var_1 == "points" )
        level.player endon( "airstrike_set_second_point" );

    if ( !var0 && isdefined( level._ID19925 ) && level._ID19925 > 0 )
        wait(level._ID19925);

    thread _ID19969();

    for (;;)
    {
        var_2 = _ID20000();

        if ( var_2["fraction"] < 1 )
        {
            _ID19946();
            level._ID19947.origin = var_2["pos"];
            level.player notify( "airstrike_first_point_confirmed" );
            var_1 = getdvar( "a10_strike_controls" );

            if ( var_1 == "ads" )
            {
                if ( level.player adsbuttonpressed() )
                {
                    if ( !isdefined( level._ID19944 ) )
                    {
                        level._ID19944 = spawn( "script_origin", level.player.origin );
                        level.player playerlinkto( level._ID19944 );
                    }

                    _ID19950();
                }
                else if ( isdefined( level._ID19944 ) )
                    _ID20015();
            }
            else if ( var_1 == "static" )
            {
                if ( !isdefined( level._ID19944 ) )
                {
                    level._ID19944 = spawn( "script_origin", level.player.origin );
                    level.player playerlinkto( level._ID19944 );
                }

                _ID19950();
            }
            else if ( var_1 == "points" )
            {

            }
        }
        else
        {
            level.player notify( "airstrike_first_point_failure" );
            thread _ID19967();
            wait 0.05;
            break;
        }

        wait 0.05;
    }
}

_ID19950()
{
    var_0 = level.player getnormalizedmovement();

    if ( var_0 != ( 0, 0, 0 ) )
    {
        var_1 = vectortoangles( var_0 );
        var_2 = combineangles( level.player.angles, -1 * var_1 );
        var_3 = ( level._ID19947.angles[0], var_2[1], var_2[2] );
        level._ID19947 rotateto( var_3, 0.2 );
    }
}

_ID19951()
{
    level._ID19953 = spawn( "script_model", level._ID19952.origin );
    level._ID19953 setmodel( "tag_origin" );
    level._ID19953.angles = level._ID19947.angles;
    level._ID19953._ID19954 = "green";
    playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );
}

_ID19955()
{
    if ( isdefined( level._ID19953 ) )
    {
        stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );
        stopfxontag( common_scripts\utility::getfx( "a10_point_active" ), level._ID19953, "tag_origin" );
        stopfxontag( common_scripts\utility::getfx( "a10_point_invalid" ), level._ID19953, "tag_origin" );
        level._ID19953 delete();
    }
}

_ID19956()
{
    if ( isdefined( level._ID19952 ) )
    {
        stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19952, "tag_origin" );
        stopfxontag( common_scripts\utility::getfx( "a10_point_active" ), level._ID19952, "tag_origin" );
        stopfxontag( common_scripts\utility::getfx( "a10_point_invalid" ), level._ID19952, "tag_origin" );
        level._ID19952 delete();
    }
}

_ID19957()
{
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    level.player endon( "airstrike_path_fail" );
    var_0 = 128;

    if ( !isdefined( level._ID19952 ) )
    {
        level._ID19952 = spawn( "script_model", ( 0, 0, 0 ) );
        level._ID19952 setmodel( "tag_origin" );
        level._ID19952.angles = level._ID19947.angles;
        level._ID19952.origin = level._ID19947.origin;
        stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19947, "tag_origin" );
        playfxontag( common_scripts\utility::getfx( "a10_point_active" ), level._ID19952, "tag_origin" );
    }

    _ID19951();
    thread _ID19959();
    var_1 = 0;

    for (;;)
    {
        var_2 = _ID20000();

        if ( var_2["fraction"] < 1 )
        {
            if ( var_1 )
            {
                _ID19951();
                thread _ID19959();
                var_1 = 0;
            }

            level._ID19953.origin = var_2["pos"];
            var_3 = level._ID19929 + level._ID19930;

            if ( distance( level._ID19952.origin, level._ID19953.origin ) > var_3 )
            {
                if ( level._ID19953._ID19954 == "green" )
                {
                    stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );
                    playfxontag( common_scripts\utility::getfx( "a10_point_invalid" ), level._ID19953, "tag_origin" );
                    level._ID19953._ID19954 = "red";
                }
            }
            else if ( level._ID19953._ID19954 == "red" )
            {
                stopfxontag( common_scripts\utility::getfx( "a10_point_invalid" ), level._ID19953, "tag_origin" );
                playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );
                level._ID19953._ID19954 = "green";
            }

            var_4 = getdvar( "a10_strike_controls" );

            if ( var_4 != "points" )
            {
                var_5 = vectortoangles( level._ID19953.origin - level._ID19952.origin );
                var_6 = anglestoforward( common_scripts\utility::flat_angle( var_5 ) );
                level._ID19947.origin = level._ID19952.origin + var_6 * level._ID19929 - var_0;
            }

            level.player notify( "airstrike_second_point_confirmed" );
        }
        else
        {
            level.player notify( "airstrike_second_point_failure" );
            _ID20002( 0 );
            _ID19955();
            var_5 = 1;
        }

        wait 0.05;
    }
}

_ID19958()
{
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    level.player endon( "airstrike_path_fail" );
    level._ID19952 = spawn( "script_model", ( 0, 0, 0 ) );
    level._ID19952 setmodel( "tag_origin" );
    level._ID19952.angles = level._ID19947.angles;
    playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19952, "tag_origin" );
    level._ID19953 = spawn( "script_model", ( 0, 0, 0 ) );
    level._ID19953 setmodel( "tag_origin" );
    level._ID19953.angles = level._ID19947.angles;
    playfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );

    for (;;)
    {
        var_0 = anglestoforward( common_scripts\utility::flat_angle( level._ID19947.angles ) );
        level._ID19952.origin = level._ID19947.origin - var_0 * level._ID19929;
        level._ID19953.origin = level._ID19947.origin + var_0 * level._ID19930;
        wait 0.05;
    }
}

_ID19959()
{
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    level.player endon( "airstrike_path_fail" );
    var_0 = getdvar( "a10_strike_controls" );

    if ( var_0 == "points" )
        level.player endon( "airstrike_second_point_failure" );

    var_1 = level._ID19929 + level._ID19930;
    var_2 = 64;

    if ( !isdefined( level._ID19960 ) )
        level._ID19960 = [];

    for (;;)
    {
        var_3 = 64;

        for ( var_4 = distance( level._ID19952.origin, level._ID19953.origin ); var_3 < var_4; var_6 = var_6 + var_5 )
        {
            var_5 = vectortoangles( level._ID19953.origin - level._ID19952.origin );
            var_6 = anglestoforward( var_5 );
            var_7 = var_5 * ( 0, 1, 1 ) + ( 270, 90, 0 );
            var_8 = level._ID19952.origin + ( 0, 0, 10 ) + var_6 * var_3;
            var_9 = 1;

            foreach ( var_11 in level._ID19960 )
            {
                if ( var_11._ID14507 == var_3 )
                {
                    if ( var_11.origin != var_8 || var_11.angles != var_7 )
                    {
                        var_11.origin = var_8;
                        var_11.angles = var_7;
                    }

                    var_9 = 0;
                }
            }

            if ( var_9 )
            {
                var_13 = common_scripts\utility::spawn_tag_origin();
                var_13.origin = var_8;
                var_13.angles = var_7;
                var_13._ID14507 = var_3;
                var_14 = var_3 / var_2;
                var_15 = int( var_14 ) % 2;
                var_13 _ID19965( var_3 < var_1, var_15 );
                var_13._ID19961 = 0.1 * var_14;

                if ( var_3 == var_2 )
                    level._ID19962 = gettime();

                var_13 thread _ID19963( var_14 );
                level._ID19960 = _ID65::_ID3011( level._ID19960, var_13 );
            }
        }

        foreach ( var_17 in level._ID19960 )
        {
            if ( var_17._ID14507 >= var_6 )
                thread _ID19966( var_17, 1 );
        }

        wait 0.1;
    }
}

_ID19963( var0 )
{
    var_1 = level._ID19925;
    var_2 = var_1 * 1000;
    var_3 = gettime();
    var_4 = var_3 - level._ID19962;
    var_5 = var_4 % var_2;

    if ( var_5 > 1000 * self._ID19961 )
        self._ID19961 = self._ID19961 + var_1;

    self._ID19961 = self._ID19961 - var_5 / 1000;
    var_6 = self._ID19961;

    if ( var_6 > 0 )
        wait(var_6);

    if ( isdefined( self ) )
    {
        playfxontag( common_scripts\utility::getfx( self._ID19964 ), self, "tag_origin" );

        if ( var0 == 2 )
            playfxontag( common_scripts\utility::getfx( "a10_distance_number_0" ), self, "tag_origin" );
        else if ( var0 == 6 )
            playfxontag( common_scripts\utility::getfx( "a10_distance_number_1" ), self, "tag_origin" );
        else if ( var0 == 10 )
            playfxontag( common_scripts\utility::getfx( "a10_distance_number_2" ), self, "tag_origin" );
        else if ( var0 == 14 )
            playfxontag( common_scripts\utility::getfx( "a10_distance_number_3" ), self, "tag_origin" );
    }
}

_ID19965( var0, var1 )
{
    if ( var0 )
    {
        self._ID19954 = "green";
        self._ID19964 = "a10_green_line";

        if ( var1 )
            self._ID19964 = "a10_green_line_short";
    }
    else
    {
        self._ID19954 = "red";
        self._ID19964 = "a10_red_line";

        if ( var1 )
            self._ID19964 = "a10_red_line_short";
    }
}

_ID19966( var0, var1 )
{
    level._ID19960 = common_scripts\utility::array_remove( level._ID19960, var0 );

    if ( level._ID19923 || var1 )
    {
        var0.origin = var0.origin + ( 0, 0, -10000 );
        wait 0.05;
    }

    if ( var0._ID19954 == "green" )
        stopfxontag( common_scripts\utility::getfx( "a10_green_line" ), var0, "tag_origin" );
    else
        stopfxontag( common_scripts\utility::getfx( "a10_red_line" ), var0, "tag_origin" );

    var0 delete();
}

_ID19967()
{
    self notify( "kill_draw_target_aim" );
    level.player endon( "toggle_airstrike" );
    wait 0.05;
    thread _ID19949( 0 );
}

_ID19968()
{
    level.player endon( "toggle_airstrike" );
    level.player endon( "turn_off_airstrike" );
    level.player endon( "airstrike_second_point_confirmed" );
    level.player waittill( "airstrike_second_point_failure" );
    self notify( "kill_airstrike_trigger" );
    thread _ID19969( 1 );
}

_ID19969( var0 )
{
    level.player endon( "toggle_airstrike" );
    level.player endon( "turn_off_airstrike" );
    self endon( "kill_airstrike_trigger" );

    if ( !isdefined( var0 ) )
        var0 = 0;

    var_1 = getdvar( "a10_strike_controls" );

    if ( var_1 == "points" )
        level.player endon( "airstrike_first_point_failure" );

    if ( !var0 )
        level.player waittill( "trigger_a10" );

    if ( var_1 == "points" )
    {
        if ( !var0 )
            level.player waittill( "airstrike_first_point_confirmed" );

        _ID103::_ID5719( "a10_first_point_confirmed" );
        level.player notify( "airstrike_set_second_point" );
        thread _ID19957();
        thread _ID20010();
        level.player waittill( "trigger_a10" );

        if ( var_1 == "points" )
            thread _ID19968();

        level.player waittill( "airstrike_second_point_confirmed" );
    }

    _ID103::_ID5719( "a10_second_point_confirmed" );
    var_2 = getdvar( "airstrike_weapon", "a10" );

    if ( var_2 == "random" )
    {
        var_3 = [ "a10", "25mm", "40mm", "105mm", "hellfire", "artillery" ];
        var_2 = var_3[randomint( var_3.size )];
    }

    if ( _ID19973( var_3 ) )
    {
        level.player notify( "airstrike_called" );
        var_4 = level._ID19947.origin;
        var_5 = level._ID19947.angles;

        if ( var_2 == "points" )
        {
            var_4 = level._ID19952.origin;
            var_5 = vectortoangles( level._ID19953.origin - level._ID19952.origin );
        }

        if ( var_3 == "a10" )
        {
            thread _ID19987( var_4, var_5 );
            return;
        }

        if ( var_3 == "25mm" || var_3 == "40mm" || var_3 == "105mm" )
        {
            wait(level._ID19920);
            level.player notify( "airstrike_on_inbound" );
            var_6 = "ac130_" + var_3;
            var_7 = 300;
            var_8 = 12 + randomint( 4 );
            var_9 = 0.1;
            var_10 = 0;
            var_11 = [];
            var_12 = 1;

            if ( var_3 == "40mm" )
            {
                var_7 = 400;
                var_8 = 3;
                var_9 = 0.75;
                var_10 = 1;
                var_11 = [ 0.5, 0.4 ];
                var_12 = 0;
            }
            else if ( var_3 == "105mm" )
            {
                var_7 = 100;
                var_8 = 1;
                var_9 = 0.05;
                var_10 = 1;
                var_11 = [ 0.8, 0.6 ];
                var_12 = 0;
            }

            for ( var_13 = 0; var_13 < var_8; var_13 = var_13 + 1 )
            {
                var_14 = var_6;
                var_15 = randomint( 3 );

                if ( var_15 == 1 )
                    var_14 = var_14 + "_alt";
                else if ( var_15 == 2 )
                    var_14 = var_14 + "_alt2";

                var_16 = var_4 + ( 0, 0, 1000 );
                var_17 = var_4 + ( randomfloat( var_7 ) - var_7 / 2, randomfloat( var_7 ) - var_7 / 2, 0 );
                magicbullet( var_14, var_16, var_17, level.player );

                if ( var_10 )
                    thread _ID19971( var_11[0], var_11[1], var_17, 5000 );

                if ( var_12 )
                    thread _ID19972( var_17, 128, 500, 100, level.player );

                wait(var_9);
            }

            return;
        }

        if ( var_15 == "hellfire" )
        {
            wait(level._ID19920);
            level.player notify( "airstrike_on_inbound" );
            var_18 = 200;
            var_8 = randomint( 2 ) + 3;
            var_9 = 0.8;
            var_19 = "hellfire_missile_af_caves_end";
            var_20 = randomint( 360 );
            var_21 = ( cos( var_20 ), sin( var_20 ), 0 );

            for ( var_13 = 0; var_13 < var_8; var_13 = var_13 + 1 )
            {
                var_16 = var_16 + ( 0, 0, 1000 );
                var_17 = var_16 + ( var_21[0] * var_18 * var_13, var_21[1] * var_18 * var_13, 0 );
                magicbullet( var_19, var_16, var_17, level.player );
                radiusdamage( var_17, 512, 1000, 100, level.player );
                earthquake( 0.5, 0.5, var_17, 5000 );
                wait(var_9);
            }

            return;
        }

        if ( var_13 == "artillery" )
        {
            wait(level._ID19920);
            level.player notify( "airstrike_on_inbound" );
            var_7 = 400;
            var_8 = 3;
            var_9 = 1.15;
            var_22 = [ "artillery", "artillery_alt", "artillery_alt2", "artillery_alt3" ];

            for ( var_13 = 0; var_13 < var_8; var_13 = var_13 + 1 )
            {
                var_17 = var_16 + ( randomfloat( var_7 ) - var_7 / 2, randomfloat( var_7 ) - var_7 / 2, 0 );
                radiusdamage( var_17, 256, 1000, 100, level.player );
                var_23 = level._effect[var_22[randomint( var_22.size )]];
                playfx( var_23, var_17 );
                earthquake( 0.3, 0.7, var_17, 3000 );
                thread common_scripts\utility::play_sound_in_space( "exp_artillery_underground_low", var_17 );
                wait(var_9);
            }

            return;
        }

        return;
        return;
        return;
    }
    else
    {
        thread _ID20008();

        if ( var_17 == "points" )
        {
            level.player notify( "airstrike_path_fail" );

            if ( isdefined( level._ID19952 ) )
                playfxontag( common_scripts\utility::getfx( "a10_point_invalid_active" ), level._ID19952, "tag_origin" );

            if ( isdefined( level._ID19953 ) )
                playfxontag( common_scripts\utility::getfx( "a10_point_invalid_active" ), level._ID19953, "tag_origin" );

            if ( isdefined( level._ID19960 ) )
            {
                foreach ( var_25 in level._ID19960 )
                    playfx( common_scripts\utility::getfx( "a10_point_invalid_active" ), var_25.origin );
            }

            _ID20001( 1 );

            if ( isdefined( level._ID19970 ) )
                level._ID19970.alpha = 0;

            if ( isdefined( level._ID19935 ) )
                level._ID19935.alpha = 1;

            thread _ID19949( 0 );
        }
        else
            thread _ID19969();
    }
}

_ID19971( var0, var1, var2, var3 )
{
    wait 0.35;
    earthquake( var0, var1, var2, var3 );
}

_ID19972( var0, var1, var2, var3, var4 )
{
    wait 0.4;
    radiusdamage( var0, var1, var2, var3, var4 );
}

_ID19973( var0 )
{
    level.player endon( "toggle_airstrike" );
    var_1 = getdvar( "a10_strike_controls" );
    var_2 = level._ID19947.origin;

    if ( var_1 == "points" )
        var_2 = level._ID19952.origin;

    if ( var0 == "a10" )
    {
        var_3 = level._ID19926;
        var_4 = level._ID19947.angles;

        if ( var_1 == "points" )
            var_4 = vectortoangles( level._ID19953.origin - level._ID19952.origin );

        var_5 = 1;

        for ( var_6 = undefined; var_5 < 4; var_5++ )
        {
            var_7 = 0;
            var_8 = ( 0, 0, 0 );
            var_9 = 0;
            level._ID19974 = var_8;

            for ( level._ID19975 = var_9; var_7 < 4; var_9 = var_9 + level._ID19928 )
            {
                var_6 = _ID19979( var_2, var_4, var_8, var_9, var_5 );

                if ( _ID19984( var_6 ) )
                {
                    level._ID19976 = var_6;
                    level._ID19974 = var_8;
                    level._ID19975 = var_9;
                    break;
                }
                else if ( getdvarint( "a10_strike_debug", 0 ) == 4 )
                {

                }

                var_7++;
                var_6 = undefined;
                var_8 = var_8 + level._ID19927;
            }

            if ( isdefined( var_6 ) )
                break;
        }

        return isdefined( var_6 );
    }
    else if ( var_7 == "25mm" || var_7 == "40mm" || var_7 == "105mm" )
    {
        var_10 = bullettrace( var_9 + ( 0, 0, 1000 ), var_9 + ( 0, 0, 16 ), 0, undefined );
        return var_10["fraction"] > 0.8;
        return 1;
    }

    return 1;
}

_ID19977( var0, var1, var2 )
{
    level endon( "airstrike_second_point_confirmed" );
    var_3 = anglestoright( common_scripts\utility::flat_angle( var0 ) );
    var_4 = var_3 * 352;
    var_5 = -1 * var_3 * 352;
    var_6 = ( 0.8, 0.4, 0.2 );

    for (;;)
    {
        for ( var_7 = 0; var_7 < var1.size - 1; var_7++ )
        {

        }

        wait 0.05;
    }
}

_ID19978( var0, var1, var2, var3, var4 )
{
    var_5 = var2[0] - var3[0];
    var_6 = var2[1] - var3[1];
    var_7 = var1 - var4;
    var_8 = var_5 * cos( var_7[1] ) - var_6 * sin( var_7[1] ) + var2[0];
    var_9 = var_5 * sin( var_7[1] ) + var_6 * cos( var_7[1] ) + var2[1];
    var_10 = [];
    var_10[0] = var0[0] - var2[0] + var_8;
    var_10[1] = var0[1] - var2[1] + var_9;
    var_10[2] = var3[2];
    return var_10;
}

_ID19979( var0, var1, var2, var3, var4 )
{
    switch ( var4 )
    {
        case 1:
        var_5 = _ID19982();
        level._ID19980 = "berlin_a10_strafe_run_02";
        break;
        case 2:
        var_5 = _ID19983();
        level._ID19980 = "berlin_a10_strafe_run_03";
        break;
        case 3:
        var_5 = _ID19981();
        level._ID19980 = "berlin_a10_strafe_run_01";
        break;
        default:
        var_5 = _ID19981();
        level._ID19980 = "berlin_a10_strafe_run_01";
        break;
    }

    var_6 = vectortoangles( ( -1, 0, 0 ) );
    var_7 = anglestoforward( common_scripts\utility::flat_angle( var4 ) );

    foreach ( var_9 in var_5 )
    {
        if ( !isstring( var_9 ) )
        {
            var_10 = _ID19978( var3, var4, ( 0, 0, 0 ), var_9.origin, var_6 );
            var_9.origin = ( var_10[0], var_10[1], var_10[2] + var_5[2] ) + -1 * var_7 * var_5;
        }
    }

    return var_6;
}

_ID19981()
{
    var_0 = [];
    var_0[0] = spawnstruct();
    var_0[0].origin = ( -10056.9, 13.1325, 3909.61 );
    var_0[1] = spawnstruct();
    var_0[1].origin = ( -9288.56, 28.2926, 4284.37 );
    var_0[2] = spawnstruct();
    var_0[2].origin = ( -8548.17, 26.452, 4561.41 );
    var_0[3] = spawnstruct();
    var_0[3].origin = ( -7788.31, 18.3251, 4736.73 );
    var_0[4] = spawnstruct();
    var_0[4].origin = ( -6989.26, 14.8047, 4819.12 );
    var_0[5] = spawnstruct();
    var_0[5].origin = ( -6177.03, 23.9315, 4790.79 );
    var_0[6] = spawnstruct();
    var_0[6].origin = ( -5367.89, 34.9308, 4624.75 );
    var_0[7] = spawnstruct();
    var_0[7].origin = ( -4570.5, 34.8316, 4224.46 );
    var_0[8] = spawnstruct();
    var_0[8].origin = ( -3783.61, 21.0125, 3497.92 );
    var_0[9] = spawnstruct();
    var_0[9].origin = ( -2993.69, 7.80361, 2642.02 );
    var_0[10] = spawnstruct();
    var_0[10].origin = ( -2188.99, 5.64912, 1936.23 );
    var_0[11] = spawnstruct();
    var_0[11].origin = ( -1369.55, 5.40654, 1306.5 );
    var_0[12] = spawnstruct();
    var_0[12].origin = ( -532.087, 5.53242, 895.056 );
    var_0[13] = spawnstruct();
    var_0[13].origin = ( 327.03, 6.24819, 937.038 );
    var_0[14] = spawnstruct();
    var_0[14].origin = ( 1200.39, 6.99051, 1209.14 );
    var_0[15] = spawnstruct();
    var_0[15].origin = ( 2107.8, 6.3943, 1653.24 );
    var_0[16] = spawnstruct();
    var_0[16].origin = ( 3048.03, 6.18817, 2146.4 );
    var_0[17] = spawnstruct();
    var_0[17].origin = ( 4014.69, 7.72807, 2638.88 );
    var_0[18] = spawnstruct();
    var_0[18].origin = ( 4996.06, 6.71646, 3117.33 );
    var_0[19] = spawnstruct();
    var_0[19].origin = ( 5982, -3.48998, 3558.96 );
    var_0[20] = spawnstruct();
    var_0[20].origin = ( 6971.07, -26.779, 4002.91 );
    var_0[21] = spawnstruct();
    var_0[21].origin = ( 7961.54, -28.7748, 4397.24 );
    var_0[22] = spawnstruct();
    var_0[22].origin = ( 8949.47, -25.9104, 4602.09 );
    var_0[23] = spawnstruct();
    var_0[23].origin = ( 9911.91, -28.1551, 4504.06 );
    return var_0;
}

_ID19982()
{
    var_0 = [];
    var_0[0] = spawnstruct();
    var_0[0].origin = ( -9091.65, -23.2342, 2924.63 );
    var_0[1] = spawnstruct();
    var_0[1].origin = ( -8429.11, -29.6148, 2884.12 );
    var_0[2] = spawnstruct();
    var_0[2].origin = ( -7754.02, -32.7071, 2793.82 );
    var_0[3] = spawnstruct();
    var_0[3].origin = ( -7045.23, -32.8687, 2669.79 );
    var_0[4] = spawnstruct();
    var_0[4].origin = ( -6319.91, -28.1018, 2518.06 );
    var_0[5] = spawnstruct();
    var_0[5].origin = ( -5587.42, -19.8092, 2349.16 );
    var_0[6] = spawnstruct();
    var_0[6].origin = ( -4854.06, -10.8168, 2174.63 );
    var_0[7] = spawnstruct();
    var_0[7].origin = ( -4124.35, -3.30188, 1995.74 );
    var_0[8] = spawnstruct();
    var_0[8].origin = ( -3392.13, 2.82406, 1793.46 );
    var_0[9] = spawnstruct();
    var_0[9].origin = ( -2654.41, 5.53648, 1600.61 );
    var_0[10] = spawnstruct();
    var_0[10].origin = ( -1912.24, 5.42406, 1436 );
    var_0[11] = spawnstruct();
    var_0[11].origin = ( -1167.66, 6.08207, 1285.22 );
    var_0[12] = spawnstruct();
    var_0[12].origin = ( -421.469, 5.42027, 1161.46 );
    var_0[13] = spawnstruct();
    var_0[13].origin = ( 327.288, 6.19893, 1101.52 );
    var_0[14] = spawnstruct();
    var_0[14].origin = ( 1074.6, 7.23231, 1101.37 );
    var_0[15] = spawnstruct();
    var_0[15].origin = ( 1821.74, 5.79744, 1139.21 );
    var_0[16] = spawnstruct();
    var_0[16].origin = ( 2564.38, 8.6126, 1234.25 );
    var_0[17] = spawnstruct();
    var_0[17].origin = ( 3303.87, 18.014, 1399.4 );
    var_0[18] = spawnstruct();
    var_0[18].origin = ( 4043.36, 27.5554, 1619.29 );
    var_0[19] = spawnstruct();
    var_0[19].origin = ( 4785.79, 33.332, 1869.76 );
    var_0[20] = spawnstruct();
    var_0[20].origin = ( 5535.7, 36.2899, 2122.15 );
    var_0[21] = spawnstruct();
    var_0[21].origin = ( 6296.13, 37.8413, 2354.19 );
    var_0[22] = spawnstruct();
    var_0[22].origin = ( 7068.21, 38.9115, 2553.21 );
    var_0[23] = spawnstruct();
    var_0[23].origin = ( 7853.21, 41.6815, 2708.55 );
    var_0[24] = spawnstruct();
    var_0[24].origin = ( 8650.68, 55.0736, 2800.63 );
    return var_0;
}

_ID19983()
{
    var_0 = [];
    var_0[0] = spawnstruct();
    var_0[0].origin = ( -9110.42, 29.6127, 4410.74 );
    var_0[1] = spawnstruct();
    var_0[1].origin = ( -8443.64, 24.4333, 4606.25 );
    var_0[2] = spawnstruct();
    var_0[2].origin = ( -7756.91, 18.272, 4606.93 );
    var_0[3] = spawnstruct();
    var_0[3].origin = ( -7037.71, 15.027, 4447.98 );
    var_0[4] = spawnstruct();
    var_0[4].origin = ( -6306.83, 21.478, 4158.94 );
    var_0[5] = spawnstruct();
    var_0[5].origin = ( -5577.11, 32.7816, 3770.47 );
    var_0[6] = spawnstruct();
    var_0[6].origin = ( -4856.11, 36.694, 3312.49 );
    var_0[7] = spawnstruct();
    var_0[7].origin = ( -4144.47, 27.9597, 2822.09 );
    var_0[8] = spawnstruct();
    var_0[8].origin = ( -3437.49, 14.1074, 2332.84 );
    var_0[9] = spawnstruct();
    var_0[9].origin = ( -2721.98, 6.54957, 1871.16 );
    var_0[10] = spawnstruct();
    var_0[10].origin = ( -1989.45, 5.55282, 1466.05 );
    var_0[11] = spawnstruct();
    var_0[11].origin = ( -1242.48, 5.18994, 1144.73 );
    var_0[12] = spawnstruct();
    var_0[12].origin = ( -489.53, 6.17668, 917.271 );
    var_0[13] = spawnstruct();
    var_0[13].origin = ( 275.15, 6.53617, 849.875 );
    var_0[14] = spawnstruct();
    var_0[14].origin = ( 1061.18, 7.11486, 936.346 );
    var_0[15] = spawnstruct();
    var_0[15].origin = ( 1887.17, 6.92493, 1097.46 );
    var_0[16] = spawnstruct();
    var_0[16].origin = ( 2753.27, 6.25139, 1303.29 );
    var_0[17] = spawnstruct();
    var_0[17].origin = ( 3649.27, 7.25302, 1584.16 );
    var_0[18] = spawnstruct();
    var_0[18].origin = ( 4564.32, 8.06856, 1930.43 );
    var_0[19] = spawnstruct();
    var_0[19].origin = ( 5488.54, 4.33213, 2304.48 );
    var_0[20] = spawnstruct();
    var_0[20].origin = ( 6409.78, -7.72615, 2700.24 );
    var_0[21] = spawnstruct();
    var_0[21].origin = ( 7315.35, -26.545, 3221.62 );
    var_0[22] = spawnstruct();
    var_0[22].origin = ( 8193.85, -29.4547, 3775.35 );
    var_0[23] = spawnstruct();
    var_0[23].origin = ( 9038.56, -22.9634, 4201.68 );
    var_0[24] = spawnstruct();
    var_0[24].origin = ( 9823.84, -25.876, 4347.68 );
    return var_0;
}

_ID19984( var0 )
{
    for ( var_1 = 0; var_1 < var0.size - 1; var_1++ )
    {
        if ( !_ID19985( var0[var_1].origin, var0[var_1 + 1].origin ) )
            return 0;
    }

    if ( !_ID19986( var0 ) )
        return 0;

    return 1;
}

_ID19985( var0, var1 )
{
    if ( !physicstrace( var0, var1, 0, 0 ) )
        return 0;

    return 1;
}

_ID19986( var0 )
{
    var_1 = anglestoright( common_scripts\utility::flat_angle( level._ID19947.angles ) );
    var_2 = var_1 * 352;
    var_3 = -1 * var_1 * 352;

    for ( var_4 = 0; var_4 < var0.size - 1; var_4++ )
    {
        var_5 = var0[var_4].origin;
        var_6 = var0[var_4 + 1].origin;

        if ( !_ID19985( var_5 + var_2, var_6 + var_2 ) )
            return 0;

        if ( !_ID19985( var_5 + var_3, var_6 + var_3 ) )
            return 0;
    }

    return 1;
}

_ID19987( var0, var1 )
{
    thread _ID103::_ID5719( "a10_airstrike_requested" );
    stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19953, "tag_origin" );
    stopfxontag( common_scripts\utility::getfx( "a10_point_invalid" ), level._ID19953, "tag_origin" );
    playfxontag( common_scripts\utility::getfx( "a10_point_active" ), level._ID19953, "tag_origin" );
    stopfxontag( common_scripts\utility::getfx( "a10_point" ), level._ID19952, "tag_origin" );
    playfxontag( common_scripts\utility::getfx( "a10_point_active" ), level._ID19952, "tag_origin" );

    if ( isdefined( level._ID19960 ) )
    {
        foreach ( var_3 in level._ID19960 )
        {
            stopfxontag( common_scripts\utility::getfx( "a10_green_line_active" ), var_3, "tag_origin" );
            stopfxontag( common_scripts\utility::getfx( "a10_red_line" ), var_3, "tag_origin" );
            playfxontag( common_scripts\utility::getfx( "a10_green_line_active" ), var_3, "tag_origin" );
        }
    }

    wait(level._ID19922);
    var_5 = var_4;
    var_6 = common_scripts\utility::flat_angle( var_5 );
    var_7 = anglestoforward( var_6 );
    var_8 = var_3 + -1 * var_7 * level._ID19929;
    var_9 = var_3 + var_7 * level._ID19930;
    var_10 = [ var_8, var_3, var_9 ];
    _ID19991( var_10, level._ID19920 + 4, "allies" );
    wait(level._ID19920);
    level.player notify( "airstrike_on_inbound" );
    var_11 = 15700;
    var_12 = 512;
    var_13 = spawn( "script_origin", var_3 + -1 * var_7 * var_11 + level._ID19975 + ( 0, 0, var_12 ) + level._ID19974 );

    if ( !isdefined( level._ID19988 ) )
        level._ID19988 = spawnstruct();

    level._ID19988.origin = var_8;

    if ( !isdefined( level._ID19989 ) )
        level._ID19989 = spawnstruct();

    level._ID19989.origin = var_9;
    var_13.angles = var_6;
    var_15 = getent( "a10_dynamic", "script_noteworthy" );
    level._ID19990 = var_15 _ID65::_ID8099();
    level._ID19990.angles = var_6;
    level._ID19990._ID4146 = "a10";
    level._ID19990 thread _ID19992();
    _ID65::_ID2556( 0.1, _ID68::_ID4731, level._ID19990, level._ID19980, 1.3 );
    _ID65::_ID2556( 3, ::_ID19991, var_10, 5, "axis" );
    _ID103::_ID5719( "a10_airstrike_start", level._ID19990 );
    var_13 _ID68::_ID4678( level._ID19990, level._ID19980 );
    level._ID19990 delete();
    var_13 delete();
    level.player notify( "a10_anim_complete" );
}

_ID19991( var0, var1, var2 )
{
    foreach ( var_4 in var0 )
        __builtin_func_1B( "", var1, var_4, level._ID19931, 64, var2 );
}

_ID19992()
{
    var_0 = self.classname;
    var_1 = undefined;

    if ( isdefined( self._ID10642 ) )
        var_1 = self._ID10642;
    else if ( isdefined( level._ID10643 ) && isdefined( level._ID10643[var_0] ) )
        var_1 = level._ID10643;
    else if ( isdefined( level._ID10644[var_0] ) )
        var_1 = level._ID10644[var_0];

    if ( !isdefined( var_1 ) )
        return;

    var_2 = var_1.radius * 2;
    var_3 = -1 * var_1.radius;
    var_4 = spawn( "trigger_radius", self.origin + ( 0, 0, var_3 ), 0, var_1.radius, var_2 );
    var_4 enablelinkto();
    var_4 linkto( self );
    self._ID10641 = var_4;
    self._ID10641 = var_4;
    self endon( "death" );
    level._ID19993 = self._ID10641;
    var_4.radius = self._ID10663;

    for (;;)
    {
        var_4 waittill( "trigger" );
        self playrumblelooponentity( var_1._ID5185 );

        while ( level.player istouching( var_4 ) )
        {
            earthquake( self._ID10678, self._ID10662, self.origin, self._ID10663 );
            wait(self._ID10661 + randomfloat( self._ID10677 ));
        }

        self stoprumble( var_1._ID5185 );
    }
}

_ID19994( var0 )
{
    var_1 = [];
    wait 0.25;

    while ( isdefined( var0 ) )
    {
        var_2 = var0 gettagorigin( "tag_gun" );
        var_1 = _ID65::_ID3011( var_1, var_2 );
        wait 0.25;
    }

    var_3 = 0;

    foreach ( var_5 in var_1 )
        var_3++;
}

_ID19995( var0 )
{
    var_1 = var0.angles;
    var_2 = common_scripts\utility::flat_angle( var_1 );
    var_3 = anglestoforward( var_2 );
    var_4 = distance( level._ID19988.origin, level._ID19989.origin );
    var0 thread maps/berlin_util::_ID19996( "a10_muzzle_vfx_stop" );
    _ID103::_ID5719( "a10_airstrike_fire", var0 );
    thread _ID19997();
    var_5 = [];
    var_5["water"] = common_scripts\utility::getfx( "a10_impact_water" );
    var_5["metal"] = common_scripts\utility::getfx( "a10_impact" );
    var_5["asphalt"] = common_scripts\utility::getfx( "a10_impact" );
    var_5["default"] = common_scripts\utility::getfx( "a10_impact" );
    var_6 = 64;
    var_7 = 0;
    var_8 = 0.07;
    var_9 = 0;
    level notify( "a10_muzzle_vfx_stop" );

    for (;;)
    {
        var_10 = level._ID19988.origin + var_3 * var_7;

        if ( var_9 == 3 )
        {
            var_11 = bullettrace( var_10 + ( 0, 0, 512 ), var_10 - ( 0, 0, 4096 ), 0 );
            var_12 = var_11["surfacetype"];
            var_13 = var_5["default"];

            if ( isdefined( var_5[var_12] ) )
                var_13 = var_5[var_12];

            var_14 = var_11["position"];
            radiusdamage( var_14, 256, 50000, 40000, level.player, "MOD_EXPLOSIVE", level.player._ID4101 );
            playfx( var_13, var_14 );
            _ID103::_ID5719( "a10_airstrike_ground_impact", var_14 );
            var_9 = 0;
        }

        wait(var_12);
        var_11 = var_11 + var_10;
        var_13++;

        if ( var_8 < var_11 )
            break;
    }

    level notify( "a10_gound_impacts_stop" );
}

_ID19997()
{
    if ( !isdefined( level._ID19998 ) )
        level._ID19998 = 0;

    level notify( "stop_a10_kill_watcher" );
    level endon( "stop_a10_kill_watcher" );
    common_scripts\utility::array_thread( __builtin_func_BE( "axis" ), ::_ID19999 );
    wait 2;
    level notify( "stop_a10_kill_watcher" );
}

_ID19999()
{
    level endon( "stop_a10_kill_watcher" );

    if ( !isalive( self ) )
        return;

    self waittill( "death",  var_2, var_1, var_0  );

    if ( isdefined( var_1 ) && var_1 == "MOD_EXPLOSIVE" )
    {
        level._ID19998++;

        if ( level._ID19998 == 9 )
            level.player thread _ID65::_ID7737( "NEIN" );
    }
}

_ID20000()
{
    var_0 = 128;
    var_1 = 6000;
    var_2 = level.player getplayerangles();
    var_3 = anglestoforward( var_2 );
    var_4 = level.player geteye();
    var_4 = var_4 + var_3 * var_0;
    var_5 = var_4 + var_3 * var_1;
    var_6 = bullettrace( var_4, var_5, 1, level.player );
    var_7 = [];
    var_7["normal"] = ( 0, 0, 1 );
    var_7["pos"] = var_5;
    var_7["fraction"] = var_6["fraction"];

    if ( var_5[2] > 3500 )
        var_7["fraction"] = 1;

    var_7["entity"] = var_6["entity"];

    if ( level._ID19932 )
    {
        if ( isdefined( var_7["entity"] ) && isdefined( var_7["entity"].team ) && var_7["entity"].team == "allies" )
            var_7["fraction"] = 1;
    }

    if ( var_6["fraction"] < 1 )
        var_7["pos"] = var_6["position"];

    return var_7;
}

_ID20001( var0 )
{
    if ( isdefined( level._ID19947 ) )
        level._ID19947 delete();

    if ( isdefined( level._ID19953 ) && level._ID19923 )
        level._ID19953.origin = level._ID19953.origin + ( 0, 0, -10000 );

    _ID65::_ID2556( 0.05, ::_ID19955 );

    if ( isdefined( level._ID19952 ) && level._ID19923 )
        level._ID19952.origin = level._ID19952.origin + ( 0, 0, -10000 );

    _ID65::_ID2556( 0.05, ::_ID19956 );
    _ID20002( var0 );
}

_ID20002( var0 )
{
    if ( isdefined( level._ID19960 ) )
    {
        foreach ( var_2 in level._ID19960 )
            thread _ID19966( var_2, var0 );
    }
}

_ID20003()
{
    level._ID19919 = 1;
    var_0 = randomintrange( 0, 5 );

    switch ( var_0 )
    {
        case 0:
        _ID65::_ID4596( "berlin_plt_targetaquired" );
        break;
        case 1:
        _ID65::_ID4596( "berlin_plt_tallytarget" );
        break;
        case 2:
        _ID65::_ID4596( "berlin_plt_contact" );
        break;
        case 3:
        _ID65::_ID4596( "berlin_plt_tallyontarget" );
        break;
    }

    level._ID19919 = 0;
}

_ID20004()
{
    if ( !isdefined( level._ID20005 ) || !level._ID20005 )
    {
        level._ID19919 = 1;
        var_0 = randomintrange( 0, 4 );

        switch ( var_0 )
        {
            case 0:
            _ID65::_ID4596( "berlin_plt_inposition2" );
            break;
            case 1:
            _ID65::_ID4596( "berlin_plt_standingby3" );
            break;
            case 2:
            _ID65::_ID4596( "berlin_plt_ready" );
            break;
            case 3:
            _ID65::_ID4596( "berlin_plt_standingby4" );
            break;
        }

        level._ID19919 = 0;
    }
}

_ID20006()
{
    if ( !isdefined( level._ID19919 ) || !level._ID19919 )
    {
        level._ID20007 = 1;
        level._ID19919 = 1;
        var_0 = randomintrange( 0, 5 );

        switch ( var_0 )
        {
            case 0:
            _ID65::_ID4596( "berlin_plt_notinposition2" );
            break;
            case 1:
            _ID65::_ID4596( "berlin_plt_negative" );
            break;
            case 2:
            _ID65::_ID4596( "berlin_plt_circleback" );
            break;
            case 3:
            _ID65::_ID4596( "berlin_plt_notinposition" );
            break;
            case 4:
            _ID65::_ID4596( "berlin_plt_holdfast" );
            break;
        }

        level._ID19919 = 0;
        level._ID20007 = 0;
    }
}

_ID20008()
{
    if ( !isdefined( level._ID20009 ) || !level._ID20009 )
    {
        level._ID20009 = 1;
        level._ID19919 = 1;
        var_0 = randomintrange( 0, 7 );

        switch ( var_0 )
        {
            case 0:
            _ID65::_ID4596( "berlin_plt_altattack" );
            break;
            case 1:
            _ID65::_ID4596( "berlin_plt_maxeffects" );
            break;
            case 2:
            _ID65::_ID4596( "berlin_plt_reciprocal" );
            break;
            case 3:
            _ID65::_ID4596( "berlin_plt_unable" );
            break;
            case 4:
            _ID65::_ID4596( "berlin_plt_newrunin" );
            break;
            case 5:
            _ID65::_ID4596( "berlin_plt_badapproach" );
            break;
            case 6:
            _ID65::_ID4596( "berlin_plt_direction" );
            break;
        }

        level._ID19919 = 0;
        level._ID20009 = 0;
    }
}

_ID20010()
{
    level._ID19935.alpha = 0;

    if ( !isdefined( level._ID19970 ) )
    {
        level._ID19970 = _ID98::createFontString( "default", 2 );
        level._ID19970 _ID98::setPoint( "TOP", undefined, 0, 80 );
        level._ID19970.label = &"BERLIN_DIRECT_A10_POINTS";
        level._ID19970.alpha = 1;
        level._ID19970.sort = 0.5;
    }
    else
        level._ID19970.alpha = 1;
}

_ID20011()
{
    if ( isdefined( level._ID19935 ) )
        level._ID19935.alpha = 0;

    if ( isdefined( level._ID19970 ) )
        level._ID19970.alpha = 0;

    if ( isdefined( level._ID19934 ) )
        level._ID19934.alpha = 0;
}

_ID20012()
{
    if ( isdefined( level._ID19934 ) && level._ID19935.alpha != 1 )
        level._ID19934.alpha = 1;
}

_ID20013()
{
    level.player endon( "turn_off_airstrike" );
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_deactivated" );
    level.player endon( "airstrike_called" );
    level.player notifyonplayercommand( "LISTEN_switch_weapons", "weapnext" );
    level.player waittill( "LISTEN_switch_weapons" );
    level.player notify( "toggle_airstrike" );
}

_ID20014()
{
    level.player endon( "airstrike_called" );
    level.player endon( "turn_off_airstrike" );
    level.player endon( "toggle_airstrike" );
    level.player endon( "airstrike_deactivated" );

    for (;;)
    {
        if ( level.player getcurrentweapon() != level.player getcurrentprimaryweapon() )
        {
            level.player notify( "toggle_airstrike" );
            break;
        }

        wait 0.05;
    }
}

_ID20015()
{
    level.player unlink();
    level._ID19944 delete();
    level._ID19944 = undefined;
}

_ID20016( var0 )
{
    if ( var0 == "ads" )
        self allowads( 0 );

    self __builtin_func_8117( 0 );
    self __builtin_func_8116( 0 );
}

_ID20017( var0 )
{
    self __builtin_func_8116( 1 );
    self __builtin_func_8117( 1 );

    if ( var0 == "ads" )
        self allowads( 1 );
}

_ID20018()
{
    level._ID20019 = 1.25;
    precacheshader( "uav_vertical_meter" );
    precacheshader( "uav_horizontal_meter" );
    precacheshader( "uav_arrow_up" );
    precacheshader( "uav_arrow_left" );
    precacheshader( "uav_vehicle_target" );
    precacheshader( "veh_hud_friendly" );
    precacheshader( "veh_hud_target" );
    precacheshader( "nightvision_overlay_goggles" );
    precacheshader( "laser_designator_overlay_lr" );
    precacheshader( "laser_designator_overlay_hr" );
    precacheshader( "remotemissile_infantry_target" );
    __builtin_func_BB( "thermalBlurFactorNoScope", 50 );
    common_scripts\utility::flag_init( "a10_interface_enabled" );
}

_ID20020()
{
    self endon( "death" );
    level endon( "a10_view_disabled" );
    var_0 = 0.2;
    var_1 = 51.5029;
    var_2 = 0.000250787;

    for (;;)
    {
        if ( common_scripts\utility::flag( "a10_interface_enabled" ) )
        {
            if ( isdefined( level._ID19947 ) )
                var_3 = level._ID19947.origin;
            else
                var_3 = ( 0, 0, 0 );
        }

        wait(var_2);
    }
}

_ID20021( var0 )
{
    var_1 = self getplayerangles();
    var_2 = self.angles[0] - var_1[0] * -1;
    var_3 = angleclamp180( self.angles[1] );
    _ID20039( "arrow_left", int( var_2 ) );
    _ID20039( "arrow_up", int( var_3 ) );
    var_4 = self._ID20022["vert_meter"];
    var_5 = self._ID20022["arrow_left"];
    var_2 = clamp( var_2, var_4._ID20024, var_4._ID20023 );
    var_6 = abs( var_2 / var_4._ID10639 );
    var_7 = var_4._ID20025 * var_6;
    var_8 = var_7 - var_4._ID20025 * 0.5;
    var_9 = var_4.y + var_8;
    var_5 moveovertime( 0.2 );
    var_5.y = var_9;
    var_5._ID17631 moveovertime( var0 );
    var_5._ID17631.y = var_9;
    var_10 = self._ID20022["horz_meter"];
    var_11 = self._ID20022["arrow_up"];
    var_6 = var_3 / var_10._ID10639;
    var_7 = var_10._ID20025 * var_6;
    var_12 = var_10.x + var_7;
    var_11 moveovertime( 0.2 );
    var_11.x = var_12;
    var_11._ID17631 moveovertime( var0 );
    var_11._ID17631.x = var_12;
}

_ID20026( var0 )
{
    if ( var0 == 0 )
        return 0;

    return var0 / 12;
}

_ID20027( var0 )
{
    return var0 * 0.0254;
}

_ID20028( var0 )
{
    return var0 * 0.000539957;
}

_ID20029( var0, var1 )
{
    var0 = int( var0 * var1 ) / var1;
    return var0;
}

_ID20030()
{
    __builtin_func_BB( "ammoCounterHide", "0" );
    __builtin_func_BB( "actionSlotsHide", "0" );
    __builtin_func_BB( "hud_showStance", "0" );
}

_ID20031()
{
    __builtin_func_BB( "hud_showStance", "1" );
    __builtin_func_BB( "actionSlotsHide", "1" );
    __builtin_func_BB( "ammoCounterHide", "1" );
}

_ID20032()
{
    _ID65::_ID2556( 0.9, _ID316::_ID7575, 0.1, 0.1, 0.1 );
    _ID20051();
    thread _ID20033();
    _ID20031();
    self._ID20022 = [];
    var_0 = "laser_designator_overlay_lr";

    if ( level._ID19924 )
    {
        __builtin_func_E5( 1 );
        var_0 = "laser_designator_overlay_hr";
    }

    self._ID20022["static_goggles"] = _ID20035( var_0, 1, 1 );
    self._ID20022["static_grain"] = _ID20035( "nightvision_overlay_goggles", 0, 0.2 );
    common_scripts\utility::flag_set( "a10_interface_enabled" );
    thread _ID20063();
    thread _ID20020();
}

_ID20033()
{
    self endon( "death" );
    level endon( "a10_view_disabled" );
    var_0 = 0.75;
    var_1 = 0.75;
    var_2 = 0.3;
    var_3 = 0.3;
    var_4 = 0.5;
    var_5 = 0.5;
    var_6 = 1;

    for (;;)
    {
        if ( level.player adsbuttonpressed() && var_6 == 0 )
        {
            __builtin_func_BB( "cg_playerFovScale0", var_0 );
            level.player __builtin_func_80E9( var_2, var_3 );
            var_6 = 1;
        }
        else if ( !level.player adsbuttonpressed() && var_6 == 1 )
        {
            __builtin_func_BB( "cg_playerFovScale0", var_1 );
            level.player __builtin_func_80E9( var_4, var_5 );
            var_6 = 0;
        }

        wait 0.05;
    }
}

_ID20034()
{
    __builtin_func_BB( "cg_playerFovScale0", 1 );
    level.player __builtin_func_80EA();
}

_ID20035( var0, var1, var2 )
{
    var_3 = newhudelem();
    var_3.x = 0;
    var_3.y = 0;
    var_3.sort = var1;
    var_3.horzalign = "fullscreen";
    var_3.vertalign = "fullscreen";
    var_3.alpha = var2;
    var_3 setshader( var0, 640, 480 );
    return var_3;
}

_ID20036()
{
    var_0 = newhudelem();
    var_0.x = 320;
    var_0.y = 80;
    var_0.sort = 0;
    var_0.alignx = "center";
    var_0.aligny = "bottom";
    var_0 setshader( "uav_horizontal_meter", 96, 16 );
    return var_0;
}

_ID20037()
{
    var_0 = newhudelem();
    var_0.x = 40;
    var_0.y = 240;
    var_0.sort = 0;
    var_0.alignx = "right";
    var_0.aligny = "middle";
    var_0 setshader( "uav_vertical_meter", 16, 96 );
    return var_0;
}

_ID18435()
{
    var_0 = newhudelem();
    var_0.x = 320;
    var_0.y = 240;
    var_0.sort = 0;
    var_0.alignx = "center";
    var_0.aligny = "middle";
    var_0 setshader( "uav_crosshair", 320, 240 );
    return var_0;
}

_ID20038( var0, var1 )
{
    self._ID20022["lower_right"][var0]._ID17631 setvalue( var1 );
}

_ID20039( var0, var1 )
{
    self._ID20022[var0]._ID17631 setvalue( var1 );
}

_ID20040()
{
    var_0 = [];
    var_0["nar"] = [ "NAR", "none" ];
    var_0["white"] = [ "WHT", "none" ];
    var_0["rate"] = [ "RATE", "none" ];
    var_0["angle"] = [ "ANGLE", "none" ];
    var_0["numbers"] = [ "NUM", "none" ];
    var_0["temp"] = [ "TEMP", "none" ];
    return _ID20043( var_0, 10, 80, "left" );
}

_ID20041()
{
    var_0 = [];
    var_0["acft"] = [ "ACFT", "none" ];
    var_0["long"] = [ "N", "none" ];
    var_0["lat"] = [ "W", "none" ];
    var_0["angle"] = [ "HAT", "none" ];
    return _ID20043( var_0, 510, 80, "left" );
}

_ID20042()
{
    var_0 = [];
    var_0["long"] = [ &"N", "none" ];
    var_0["lat"] = [ &"W", "none" ];
    var_1 = _ID20043( var_0, 500, 335, "left" );
    var_0 = [];
    var_0["brg"] = [ "BRG", "" ];
    var_0["rng_m"] = [ "RNG", "" ];
    var_0["rng_nm"] = [ "RNG", "" ];
    var_0["elv"] = [ "ELV", "" ];
    var_2 = _ID20043( var_0, 510, 360, "right" );

    foreach ( var_4 in var_2 )
        var_1[var_5] = var_4;

    return var_1;
}

_ID20043( var0, var1, var2, var3 )
{
    var_4 = [];
    var_5 = 10 * level._ID20019;

    foreach ( var_7 in var0 )
    {
        var_8 = newhudelem();
        var_8.x = var1;
        var_8.y = var2;
        var_8.alignx = var3;
        var_8.aligny = "middle";
        var_8.color = ( 1, 1, 1 );
        var_8.fontScale = level._ID20019;
        var_8 settext( var_7[0] );

        if ( isdefined( var_7[1] ) )
        {
            if ( !_ID20044( var_7[1], "none" ) )
                var_8 _ID20045( var_7[1] );
        }
        else
            var_8 _ID20045();

        var_4[var_9] = var_8;
        var2 = var2 + var_5;
    }

    return var_4;
}

_ID20044( var0, var1 )
{
    if ( isstring( var0 ) )
    {
        if ( var0 == var1 )
            return 1;
    }

    return 0;
}

_ID20045( var0 )
{
    var_1 = 75;

    if ( isdefined( var0 ) && !_ID20044( var0, "" ) )
    {
        var_2 = newhudelem();
        var_2.x = self.x + var_1;
        var_2.y = self.y;
        var_2.alignx = "right";
        var_2.aligny = "middle";
        var_2.fontScale = level._ID20019;
        var_2 settext( var0 );
        self._ID17632 = var_2;
        var_3 = 1;

        if ( var0 == "UAV_NM" )
            var_3 = 2;

        var_1 = var_1 - 10 * var_3;
    }

    var_4 = newhudelem();
    var_4.x = self.x + var_3;
    var_4.y = self.y;
    var_4.alignx = "right";
    var_4.aligny = "middle";
    var_4.fontScale = level._ID20019;
    var_4 setvalue( 0 );
    self._ID17631 = var_4;
}

_ID20046( var0 )
{
    if ( var0 == "up" )
    {
        var_1 = "uav_arrow_up";
        var_2 = self._ID20022["horz_meter"];
        var_3 = 320;
        var_4 = var_2.y + 10;
        var_5 = "center";
        var_6 = "top";
    }
    else
    {
        var_1 = "uav_arrow_left";
        var_2 = self._ID20022["vert_meter"];
        var_3 = var_2.x + 10;
        var_4 = 240;
        var_5 = "left";
        var_6 = "middle";
    }

    var_7 = newhudelem();
    var_7.x = var_3;
    var_7.y = var_4;
    var_7.alignx = var_5;
    var_7.aligny = var_6;
    var_7 setshader( var_1, 16, 16 );
    var_7 _ID20047( var_6 );
    return var_7;
}

_ID20047( var0 )
{
    if ( var0 == "up" )
    {
        var_1 = self.x;
        var_2 = self.y + 16;
        var_3 = "center";
        var_4 = "top";
    }
    else
    {
        var_1 = self.x + 16;
        var_2 = self.y;
        var_3 = "left";
        var_4 = "middle";
    }

    var_5 = newhudelem();
    var_5.x = var_1;
    var_5.y = var_2;
    var_5.alignx = var_3;
    var_5.aligny = var_4;
    var_5 setvalue( 0 );
    self._ID17631 = var_5;
}

_ID20048()
{
    common_scripts\utility::flag_clear( "a10_interface_enabled" );
    level notify( "a10_view_disabled" );
    self __builtin_func_80EA();

    if ( self getcurrentweapon() == "a10_designator_ads" )
    {
        thread _ID316::_ID7575( 0.1, 0.1, 0.1 );
        wait 0.2;
    }

    _ID20062();
    _ID20030();

    if ( isdefined( self._ID20022 ) )
    {
        foreach ( var_1 in self._ID20022 )
        {
            if ( isdefined( var_1 ) )
            {
                if ( __builtin_func_B4( var_1 ) )
                {
                    foreach ( var_3 in var_1 )
                        _ID20049( var_3 );

                    var_1 = undefined;
                    continue;
                }

                _ID20049( var_3 );
            }
        }
    }

    __builtin_func_E5( 0 );
    _ID20034();
    _ID20052();
    _ID20050();
}

_ID20049( var0 )
{
    if ( !isdefined( var0 ) )
        return;

    if ( isdefined( var0._ID17631 ) )
        var0._ID17631 destroy();

    if ( isdefined( var0._ID17632 ) )
        var0._ID17632 destroy();

    var0 destroy();
}

_ID20050()
{
    self enableweapons();
    self enableoffhandweapons();
    self freezecontrols( 0 );
}

_ID20051()
{
    self._ID4101 = self getcurrentweapon();
    var_0 = "a10_designator_ads";
    level.player setactionslot( 4, "weapon", var_0 );
    level.player giveweapon( var_0 );
    level.player switchtoweapon( var_0 );
    level.player _ID65::_ID2595( 1 );
    _ID103::_ID5719( "goggles_on" );
    self disableoffhandweapons();
    wait 1.2;
}

_ID20052()
{
    var_0 = "a10_designator_ads";

    if ( self getcurrentweapon() == var_0 )
    {
        self switchtoweapon( self._ID4101 );
        level.player _ID65::_ID2595( 0 );
        _ID103::_ID5719( "goggles_off" );
        wait 1;
    }

    level.player takeweapon( var_0 );
}

_ID20053( var0, var1, var2 )
{
    self endon( "death" );
    self notify( "stop_a10_target_tracking" );
    self endon( "stop_a10_target_tracking" );
    var_3 = 0.94;
    var_4 = 0.1;

    if ( isdefined( var1 ) )
        var_3 = var1;

    for (;;)
    {
        var_5 = var0.origin + ( 0, 0, 60 );

        if ( isdefined( var2 ) )
        {
            var_6 = anglestoforward( var0.angles );
            var_5 = var0.origin + var_6 * var2;
        }

        var_6 = self._ID13935.origin * var_4 + var_7 * 1 - var_4;
        self._ID13935 moveto( var_6, var_5 );
        wait(var_5);
    }
}

_ID20054( var0 )
{

}

_ID20055( var0 )
{
    if ( !isdefined( self._ID20056 ) )
    {
        if ( !isdefined( level._ID20057 ) )
            level._ID20057 = 0;

        self._ID20056 = level._ID20057;
        level._ID20057++;
    }

    return self._ID20056;
}

_ID20058()
{
    level._ID19936[_ID20055( self )] = self;
}

_ID20059()
{
    self waittill( "death" );

    if ( isdefined( self ) )
        _ID20060();
}

_ID20060()
{
    _ID20061();
    level._ID19936[_ID20055( self )] = undefined;
}

_ID20061()
{
    if ( isdefined( self._ID15421 ) )
    {
        self._ID15421 = undefined;
        __builtin_func_84( self );
    }
}

_ID20062()
{
    level notify( "stop_draw_a10_targets" );

    foreach ( var_1 in level._ID19936 )
    {
        if ( !isdefined( var_1 ) )
            continue;

        var_1 _ID20061();
    }
}

_ID20063()
{
    level endon( "stop_draw_a10_targets" );
    var_0 = 4;
    var_1 = 0;
    var_2 = 0.05;

    for (;;)
    {
        foreach ( var_4 in level._ID19936 )
        {
            if ( !isdefined( var_4 ) )
                continue;

            var_4 _ID15420( level.player );
            var_1++;

            if ( var_1 >= var_0 )
            {
                var_1 = 0;
                wait(var_2);
            }
        }

        wait 0.05;
    }
}

_ID15420( var0 )
{
    if ( isdefined( self._ID15421 ) && self._ID15421 )
        return;

    self._ID15421 = 1;
    __builtin_func_83( self, ( 0, 0, 32 ) );

    if ( __builtin_func_B5( self ) || self.code_classname == "script_model" )
    {
        if ( self.team == "axis" )
            __builtin_func_85( self, "remotemissile_infantry_target" );
        else
            __builtin_func_85( self, "veh_hud_friendly" );
    }
    else if ( isplayer( self ) )
        __builtin_func_85( self, "hud_fofbox_self_sp" );
    else if ( self.code_classname == "script_vehicle" )
    {
        if ( self._ID9482 == "axis" )
            __builtin_func_85( self, "veh_hud_target" );
        else
            __builtin_func_85( self, "veh_hud_friendly" );
    }
    else
        __builtin_func_85( self, "veh_hud_target" );

    __builtin_func_90( self, var0 );
}

_ID20064()
{
    _ID20062();

    foreach ( var_1 in level._ID19936 )
    {
        if ( !isdefined( var_1 ) )
            continue;

        var_1 _ID20060();
    }

    level._ID19936 = [];
}
