// IW5 PC GSC
// Decompiled by https://github.com/xensik/gsc-tool

main()
{
    level._ID15388 = ::_ID15388;
    level._ID15407 = ::_ID15407;
    level._ID15389 = ::_ID15389;

    if ( isdefined( level._ID18404 ) && level._ID18404 )
        level._ID15391 = ::_ID18436;

    precacheshader( "uav_predator2_dir" );
    precacheshader( "uav_predator2_dirbar" );
    precacheshader( "uav_predator2_xhair" );
    precacheshader( "uav_predator2_horz_bar1" );
    precacheshader( "uav_predator2_l_topleft" );
    precacheshader( "uav_predator2_l_topright" );
    precacheshader( "uav_predator2_l_bottomleft" );
    precacheshader( "uav_predator2_l_bottomright" );
    precacheshader( "uav_predator2_heading_frame" );
    precachestring( &"UAV_M" );
    precachestring( &"UAV_WTR_DVR_ON" );
    precachestring( &"UAV_NAR" );
    precachestring( &"UAV_BLK_WHT" );
    precachestring( &"UAV_KIAS" );
    precachestring( &"UAV_N2" );
    precachestring( &"UAV_W2" );
}

_ID15388()
{
    if ( issplitscreen() )
        self._ID18405 = 0.666667;
    else
        self._ID18405 = 1;

    self._ID18406 = [];
    self._ID18406["screen"] = _ID18413( 1, 1 );
    self._ID18406["text"] = _ID18419();
    self._ID18406["kias"] = _ID18426();
    self._ID18406["alt"] = _ID18429();
    self._ID18406["heading"] = _ID18433();
    self._ID18406["crosshair"] = _ID18435();
}

_ID18407( var0, var1, var2 )
{
    if ( isarray( var1 ) )
    {
        foreach ( var_4 in var1 )
        {
            if ( var0 )
                var_4 fadeovertime( var2 );

            var_4.alpha = 0;
        }
    }
    else
    {
        if ( var_3 )
            var_4 fadeovertime( var_5 );

        var_4.alpha = 0;
    }
}

_ID18408( var0 )
{
    self notify( "uav_cleanup_hud" );

    foreach ( var_2 in self._ID18406 )
    {
        if ( isdefined( var_2 ) )
            _ID18407( var0, var_2, 0.25 );
    }
}

_ID15407( var0 )
{
    if ( var0 == 0 )
        _ID18408( 1 );
    else
        _ID18409();
}

_ID15389( var0 )
{
    if ( var0 == 0 )
        _ID18408( 0 );
    else
        _ID18409();
}

_ID18409()
{
    self notify( "uav_cleanup_hud" );

    if ( isdefined( self._ID18406 ) )
    {
        foreach ( var_1 in self._ID18406 )
        {
            if ( isdefined( var_1 ) )
            {
                if ( isarray( var_1 ) )
                {
                    foreach ( var_3 in var_1 )
                        _ID18410( var_3 );

                    var_1 = undefined;
                    continue;
                }

                _ID18410( var_3 );
            }
        }

        self._ID18406 = undefined;
    }
}

_ID18410( var0 )
{
    if ( !isdefined( var0 ) )
        return;

    if ( isdefined( var0._ID17631 ) )
        var0._ID17631 destroy();

    if ( isdefined( var0._ID17632 ) )
        var0._ID17632 destroy();

    var0 destroy();
}

_ID18411( var0 )
{
    if ( issplitscreen() )
        return var0 * self._ID18405;
    else
        return var0;
}

_ID18412( var0, var1, var2, var3, var4, var5, var6, var7, var8 )
{
    var_9 = newclienthudelem( self );
    var_9.x = _ID18411( var0 );
    var_9.y = _ID18411( var1 );
    var_9.alignx = var7;
    var_9.aligny = var8;
    var_9.sort = var5;
    var_9.horzalign = "fullscreen";
    var_9.vertalign = "fullscreen";
    var_9.alpha = var6;
    var_9 setshader( var4, var2, var3 );
    return var_9;
}

_ID18413( var0, var1 )
{
    var_2[0] = _ID18412( 140, 135, 21, 32, "uav_predator2_l_topleft", var0, var1, "left", "top" );
    var_2[1] = _ID18412( 499, 135, 21, 32, "uav_predator2_l_topright", var0, var1, "right", "top" );
    var_2[2] = _ID18412( 140, 364, 21, 32, "uav_predator2_l_bottomleft", var0, var1, "left", "bottom" );
    var_2[3] = _ID18412( 499, 364, 21, 32, "uav_predator2_l_bottomright", var0, var1, "right", "bottom" );
    return var_2;
}

_ID18414( var0 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );
    var_1 = 37200000;

    while ( isdefined( var0 ) )
    {
        var_2 = gettime() + var_1;
        var_3 = int( var_2 / 1000 );
        var_4 = int( var_3 / 60 );
        var_3 = int( var_3 - 60 * var_4 );
        var_5 = int( var_4 / 60 );
        var_4 = int( var_4 - 60 * var_5 );
        var_5 = animscripts/utility::_ID3336( var_5, 24 );

        if ( var_5 < 10 )
            var_6 = "0" + var_5;
        else
            var_6 = "" + var_5;

        var0[0] settext( var_6 );

        if ( var_4 < 10 )
            var_6 = "0" + var_4;
        else
            var_6 = "" + var_4;

        var0[1] settext( var_6 );

        if ( var_3 < 10 )
            var_6 = "0" + var_3;
        else
            var_6 = "" + var_3;

        var0[2] settext( var_6 );
        wait 0.05;
    }
}

_ID18415()
{
    var_0[0] = _ID98::_ID2442( "default", 2 );
    var_0[0].x = _ID18411( 288 );
    var_0[0].y = _ID18411( 420 );
    var_0[0].sort = 1;
    var_0[0].horzalign = "fullscreen";
    var_0[0].vertalign = "fullscreen";
    var_0[0].alpha = 1;
    var_0[0].color = ( 0.56, 1, 0.52 );
    var_0[0] settext( "01" );
    var_0[1] = _ID98::_ID2442( "default", 2 );
    var_0[1].x = _ID18411( 304 );
    var_0[1].y = _ID18411( 420 );
    var_0[1].sort = 1;
    var_0[1].horzalign = "fullscreen";
    var_0[1].vertalign = "fullscreen";
    var_0[1].alpha = 1;
    var_0[1].color = ( 0.56, 1, 0.52 );
    var_0[1].label = ":";
    var_0[1] settext( "23" );
    var_0[2] = _ID98::_ID2442( "default", 2 );
    var_0[2].x = _ID18411( 328 );
    var_0[2].y = _ID18411( 420 );
    var_0[2].sort = 1;
    var_0[2].horzalign = "fullscreen";
    var_0[2].vertalign = "fullscreen";
    var_0[2].alpha = 1;
    var_0[2].color = ( 0.56, 1, 0.52 );
    var_0[2].label = ":";
    var_0[2] settext( "45" );
    thread _ID18414( var_0 );
    return var_0;
}

_ID18416( var0 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );

    while ( isdefined( var0 ) )
    {
        var_1 = _ID1555::_ID15403();

        if ( isdefined( var_1 ) )
        {
            var_2 = var_1.origin[2];
            var_2 = var_2 * 0.0254;
            var_2 = int( var_2 );
            var0[0] setvalue( var_2 );
            var_3 = 1;

            for ( var_2 = var_2 / 10; var_2 > 1; var_2 = var_2 / 10 )
                var_3++;

            var0[1].x = _ID18411( 480 + 8 * var_3 );
        }

        wait 0.05;
    }
}

_ID18417()
{
    var_0[0] = _ID98::_ID2442( "default", 2 );
    var_0[0].x = _ID18411( 480 );
    var_0[0].y = _ID18411( 70 );
    var_0[0].sort = 1;
    var_0[0].horzalign = "fullscreen";
    var_0[0].vertalign = "fullscreen";
    var_0[0].alpha = 1;
    var_0[0].color = ( 0.56, 1, 0.52 );
    var_0[0] setvalue( 16 );
    var_0[1] = _ID98::_ID2442( "default", 2 );
    var_0[1].x = _ID18411( 488 );
    var_0[1].y = _ID18411( 70 );
    var_0[1].sort = 1;
    var_0[1].horzalign = "fullscreen";
    var_0[1].vertalign = "fullscreen";
    var_0[1].alpha = 1;
    var_0[1].color = ( 0.56, 1, 0.52 );
    var_0[1] settext( &"UAV_MSL" );
    thread _ID18416( var_0 );
    return var_0;
}

_ID18418()
{
    var_0 = _ID98::_ID2442( "default", 1.2 );
    var_0.sort = 1;
    var_0.horzalign = "fullscreen";
    var_0.vertalign = "fullscreen";
    var_0.alpha = 1;
    var_0.color = ( 0.56, 1, 0.52 );
    return var_0;
}

_ID18419()
{
    var_0[0] = _ID18418();
    var_0[0].x = _ID18411( 50 );
    var_0[0].y = _ID18411( 109 );
    var_0[0] settext( &"UAV_WTR_DVR_ON" );
    var_0[1] = _ID18418();
    var_0[1].x = _ID18411( 50 );
    var_0[1].y = _ID18411( 121 );
    var_0[1] settext( &"UAV_NAR" );
    var_0[2] = _ID18418();
    var_0[2].x = _ID18411( 50 );
    var_0[2].y = _ID18411( 133 );
    var_0[2] settext( &"UAV_BLK_WHT" );
    var_0[3] = _ID18418();
    var_0[3].x = _ID18411( 50 );
    var_0[3].y = _ID18411( 147 );
    var_0[3] settext( &"UAV_KIAS" );
    var_0[4] = _ID18418();
    var_0[4].x = _ID18411( 510 );
    var_0[4].y = _ID18411( 380 );

    if ( isdefined( level._ID18420 ) )
        var_0[4] settext( level._ID18420 );
    else
        var_0[4] settext( &"UAV_N2" );

    var_0[5] = _ID18418();
    var_0[5].x = _ID18411( 508 );
    var_0[5].y = _ID18411( 400 );

    if ( isdefined( level._ID18421 ) )
        var_0[5] settext( level._ID18421 );
    else
        var_0[5] settext( &"UAV_W2" );

    var_0[6] = _ID18418();
    var_0[6].x = _ID18411( 491 );
    var_0[6].y = _ID18411( 420 );
    var_0[6] settext( &"UAV_ALT_MSL" );
    return var_0;
}

_ID18422( var0 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );

    while ( isdefined( var0 ) )
    {
        var_1 = _ID1554::_ID15385();

        if ( isdefined( var_1 ) )
        {
            if ( isdefined( self._ID15378 ) )
            {
                var_2 = self._ID15378.origin;
                var_3 = anglestoforward( self._ID15378.angles );
                var_4 = var_2 + 20000 * var_3;
                var_5 = bullettrace( var_2, var_4, 1, self._ID15378 );
                var_6 = distance( var_5["position"], self._ID15378.origin );
            }
            else
            {
                var_2 = var_6.origin;
                var_7 = self getplayerangles();
                var_3 = anglestoforward( var_7 );
                var_2 = var_2 + 500 * var_3;
                var_4 = var_2 + 20000 * var_3;
                var_5 = bullettrace( var_2, var_4, 1, self );
                var_6 = distance( var_5["position"], var_6.origin );
            }

            var_7 = var_7 * 0.0254;
            var_7 = int( var_7 );
            var_6[0] setvalue( var_7 );
            var_8 = 1;

            for ( var_7 = var_7 / 10; var_7 > 1; var_7 = var_7 / 10 )
                var_8++;

            var_6[0].x = _ID18411( 320 - 8 * var_8 + 1 / 2 );
            var_6[1].x = _ID18411( 320 - 8 * var_8 + 1 / 2 + 8 * var_8 );
            _ID103::_ID5719( "predator_dist_update", var_7 );
        }

        wait 0.05;
    }
}

_ID18423()
{
    var_0[0] = _ID98::_ID2442( "default", 2 );
    var_0[0].x = _ID18411( 304 );
    var_0[0].y = _ID18411( 60 );
    var_0[0].sort = 1;
    var_0[0].horzalign = "fullscreen";
    var_0[0].vertalign = "fullscreen";
    var_0[0].alpha = 1;
    var_0[0].color = ( 0.56, 1, 0.52 );
    var_0[0] setvalue( 215 );
    var_0[1] = _ID98::_ID2442( "default", 2 );
    var_0[1].x = _ID18411( 328 );
    var_0[1].y = _ID18411( 60 );
    var_0[1].sort = 1;
    var_0[1].horzalign = "fullscreen";
    var_0[1].vertalign = "fullscreen";
    var_0[1].alpha = 1;
    var_0[1].color = ( 0.56, 1, 0.52 );
    var_0[1] settext( &"UAV_M" );
    thread _ID18422( var_0 );
    return var_0;
}

_ID18424( var0 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );
    var_1 = _ID1555::_ID15403();
    var_2 = 0;
    var_3 = 0;
    var_4 = 200;

    if ( isdefined( var_1 ) )
    {
        if ( var_1.code_classname == "script_vehicle" )
            var_2 = var_1 vehicle_getspeed();

        var_3 = var_2 - 30;
        var_4 = var_2 + 30;
    }

    var_5 = 0;
    var_6 = 3;
    var_7 = var_6;
    var_8 = 0;
    var_9 = 0;
    var_10 = 25;
    var_11 = 55;
    var_12 = 245;

    while ( isdefined( var0 ) )
    {
        var_1 = _ID1555::_ID15403();

        if ( isdefined( var_1 ) )
        {
            if ( var_1.code_classname == "script_vehicle" )
                var_2 = var_1 vehicle_getspeed();

            var_13 = var_2 - var_3 / var_4 - var_3;
            var_13 = var_13 + var_8;

            if ( var_13 < 0 )
                var_13 = 0;

            if ( var_13 > 1 )
                var_13 = 1;

            var_2 = 80 + var_13 * 30;
            var_14 = var_11 / 2;
            var_15 = var_12 - var_11 * 2;
            var_16 = var_15 + var_14;
            var_17 = var_12 + var_11 * 2;
            var_18 = var_17 - var_14;
            var_19 = var_2 - int( var_2 / var_10 ) * var_10;
            var_20 = var_2 - var_19;
            var_21 = int( var_19 / var_10 * var_11 );
            var0[0] setvalue( var_20 + var_10 * 2 );
            var_22 = var_12 + var_21 - 2 * var_11;
            var0[0].y = _ID18411( var_22 );
            var0[0].alpha = clamp( var_22 - var_15 / var_14, 0, 1 );
            var0[1] setvalue( var_20 + var_10 );
            var0[1].y = _ID18411( var_12 + var_21 - var_11 );
            var0[2] setvalue( var_20 );
            var0[2].y = _ID18411( var_12 + var_21 );
            var0[3] setvalue( var_20 - var_10 );
            var_22 = var_12 + var_21 + var_11;
            var0[3].y = _ID18411( var_22 );
            var0[3].alpha = 1 - clamp( var_22 - var_18 / var_14, 0, 1 );
            var0[4] setvalue( int( var_2 ) );
            var_23 = 5;

            for ( var_24 = 0; var_24 < 25; var_24++ )
            {
                var_22 = var_24 * 11 + 135 + var_21 - var_11 + 4;
                var0[var_23 + var_24].y = int( _ID18411( var_22 ) );
                var0[var_23 + var_24].alpha = 1;

                if ( var_22 <= var_16 )
                    var0[var_23 + var_24].alpha = clamp( var_22 - var_15 / var_14, 0, 1 );

                if ( var_22 >= var_18 )
                    var0[var_23 + var_24].alpha = 1 - clamp( var_22 - var_18 / var_14, 0, 1 );
            }
        }

        var_19 = var_19 + 0.05;
        var_20 = var_20 + var_17;

        if ( var_19 >= var_18 )
        {
            var_19 = 0;
            var_25 = var_21;
            var_21 = randomfloatrange( -0.1, 0.1 );
            var_17 = var_21 - var_25 * 0.05 / var_18;
        }

        wait 0.05;
    }
}

_ID18425( var0, var1 )
{
    var_2 = _ID98::_ID2442( "default", 1 );
    var_2.x = _ID18411( var0 );
    var_2.y = _ID18411( var1 );
    var_2.alignx = "right";
    var_2.sort = 1;
    var_2.horzalign = "fullscreen";
    var_2.vertalign = "fullscreen";
    var_2.alpha = 1;
    var_2.color = ( 1, 1, 1 );
    var_2 setvalue( 0 );
    return var_2;
}

_ID18426()
{
    var_0[0] = _ID18425( 120, 100 );
    var_0[1] = _ID18425( 120, 120 );
    var_0[2] = _ID18425( 120, 140 );
    var_0[3] = _ID18425( 120, 160 );
    var_0[4] = _ID18418();
    var_0[4].x = _ID18411( 80 );
    var_0[4].y = _ID18411( 147 );
    var_0[4] setvalue( 100 );
    var_1 = 5;
    var_2 = 5;
    var_3 = 1;

    for ( var_4 = 0; var_4 < 25; var_4++ )
    {
        var_0[var_1 + var_4] = newclienthudelem( self );
        var_0[var_1 + var_4].x = _ID18411( 135 );
        var_0[var_1 + var_4].y = _ID18411( var_4 * 11 + 135 );
        var_0[var_1 + var_4].alignx = "right";
        var_0[var_1 + var_4].sort = 1;
        var_0[var_1 + var_4].horzalign = "fullscreen";
        var_0[var_1 + var_4].vertalign = "fullscreen";
        var_0[var_1 + var_4].alpha = 1;
        var_3 = var_3 - 1;

        if ( var_3 == 0 )
        {
            var_0[var_1 + var_4] setshader( "uav_predator2_horz_bar1", 8, 4 );
            var_3 = var_2;
            continue;
        }

        var_0[var_1 + var_4] setshader( "uav_predator2_horz_bar1", 6, 4 );
    }

    thread _ID18424( var_0 );
    return var_0;
}

_ID18427( var0 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );
    var_1 = _ID1555::_ID15403();
    var_2 = 0;
    var_3 = 0;
    var_4 = 1000;

    if ( isdefined( var_1 ) )
    {
        var_2 = var_1.origin[2];
        var_3 = var_2 - 100;
        var_4 = var_2 + 100;
    }

    var_5 = 0;
    var_6 = 0;
    var_7 = 0;
    var_8 = 0;
    var_9 = 4;
    var_5 = var_9;
    var_10 = 250;
    var_11 = 55;
    var_12 = 245;

    while ( isdefined( var0 ) )
    {
        var_1 = _ID1555::_ID15403();

        if ( isdefined( var_1 ) )
        {
            var_2 = var_1.origin[2];
            var_13 = var_2 - var_3 / var_4 - var_3;
            var_13 = var_13 + var_7;

            if ( var_13 < 0 )
                var_13 = 0;

            if ( var_13 > 1 )
                var_13 = 1;

            var_2 = var_3 + var_13 * var_4 - var_3;
            var_14 = var_11 / 2;
            var_15 = var_12 - var_11 * 2;
            var_16 = var_15 + var_14;
            var_17 = var_12 + var_11 * 2;
            var_18 = var_17 - var_14;
            var_19 = var_2 - int( var_2 / var_10 ) * var_10;
            var_20 = var_2 - var_19;
            var_21 = int( var_19 / var_10 * var_11 );
            var0[0] setvalue( var_20 + var_10 * 2 );
            var_22 = var_12 + var_21 - 2 * var_11;
            var0[0].y = _ID18411( var_22 );
            var0[0].alpha = clamp( var_22 - var_15 / var_16 - var_15, 0, 1 );
            var0[1] setvalue( var_20 + var_10 );
            var0[1].y = _ID18411( var_12 + var_21 - var_11 );
            var0[2] setvalue( var_20 );
            var0[2].y = _ID18411( var_12 + var_21 );
            var0[3] setvalue( var_20 - var_10 );
            var_22 = var_12 + var_21 + var_11;
            var0[3].y = _ID18411( var_22 );
            var0[3].alpha = 1 - clamp( var_22 - var_18 / var_17 - var_18, 0, 1 );
            var_23 = 4;

            for ( var_24 = 0; var_24 < 25; var_24++ )
            {
                var_22 = var_24 * 11 + 135 + var_21 - var_11 + 4;
                var0[var_23 + var_24].y = int( _ID18411( var_22 ) );
                var0[var_23 + var_24].alpha = 1;

                if ( var_22 <= var_16 )
                    var0[var_23 + var_24].alpha = clamp( var_22 - var_15 / var_14, 0, 1 );

                if ( var_22 >= var_18 )
                    var0[var_23 + var_24].alpha = 1 - clamp( var_22 - var_18 / var_14, 0, 1 );
            }
        }

        var_17 = var_17 + 0.05;
        var_19 = var_19 + var_18;

        if ( var_17 >= var_21 )
        {
            var_17 = 0;
            var_25 = var_20;
            var_20 = randomfloatrange( -0.1, 0.1 );
            var_18 = var_20 - var_25 * 0.05 / var_21;
        }

        wait 0.05;
    }
}

_ID18428( var0, var1 )
{
    var_2 = _ID98::_ID2442( "default", 1 );
    var_2.x = _ID18411( var0 );
    var_2.y = _ID18411( var1 );
    var_2.alignx = "left";
    var_2.sort = 1;
    var_2.horzalign = "fullscreen";
    var_2.vertalign = "fullscreen";
    var_2.alpha = 1;
    var_2.color = ( 1, 1, 1 );
    var_2 setvalue( 0 );
    return var_2;
}

_ID18429()
{
    var_0[0] = _ID18428( 525, 100 );
    var_0[1] = _ID18428( 525, 120 );
    var_0[2] = _ID18428( 525, 140 );
    var_0[3] = _ID18428( 525, 160 );
    var_1 = 4;
    var_2 = 5;
    var_3 = 1;

    for ( var_4 = 0; var_4 < 25; var_4++ )
    {
        var_0[var_1 + var_4] = newclienthudelem( self );
        var_0[var_1 + var_4].x = _ID18411( 505 );
        var_0[var_1 + var_4].y = _ID18411( var_4 * 11 + 135 );
        var_0[var_1 + var_4].alignx = "left";
        var_0[var_1 + var_4].sort = 1;
        var_0[var_1 + var_4].horzalign = "fullscreen";
        var_0[var_1 + var_4].vertalign = "fullscreen";
        var_0[var_1 + var_4].alpha = 1;
        var_3 = var_3 - 1;

        if ( var_3 == 0 )
        {
            var_0[var_1 + var_4] setshader( "uav_predator2_horz_bar1", 8, 4 );
            var_3 = var_2;
            continue;
        }

        var_0[var_1 + var_4] setshader( "uav_predator2_horz_bar1", 6, 4 );
    }

    thread _ID18427( var_0 );
    return var_0;
}

_ID18430( var0, var1 )
{
    self endon( "uav_cleanup_hud" );
    self endon( "death" );
    var_2 = _ID1555::_ID15403();
    var_3 = 0;
    var_4 = 360;

    while ( isdefined( var0 ) )
    {
        var_2 = _ID1555::_ID15403();

        if ( isdefined( var_2 ) )
        {
            var_5 = var_2.angles[1];
            var_5 = animscripts/utility::_ID3336( var_5, 360 );
            var_6 = var_5 - var_3 / var_4 - var_3;

            if ( var_6 < 0 )
                var_6 = 0;

            if ( var_6 > 1 )
                var_6 = 1;

            var_7 = var0._ID18431 + var_6 * var0._ID18432 - var0._ID18431;
            var0.x = _ID18411( var_7 );
            var1 setvalue( var_5 );
        }

        wait 0.05;
    }
}

_ID18433()
{
    var_0[0] = newclienthudelem( self );
    var_0[0].x = _ID18411( 304 );
    var_0[0].y = _ID18411( 8 );
    var_0[0].sort = 1;
    var_0[0].horzalign = "fullscreen";
    var_0[0].vertalign = "fullscreen";
    var_0[0].alpha = 1;
    var_0[0] setshader( "uav_predator2_dir", 24, 16 );
    var_0[0]._ID18431 = 188;
    var_0[0]._ID18432 = 428;
    var_0[1] = newclienthudelem( self );
    var_0[1].x = _ID18411( 320 );
    var_0[1].y = _ID18411( 36 );
    var_0[1].alignx = "center";
    var_0[1].aligny = "middle";
    var_0[1].sort = 1;
    var_0[1].horzalign = "fullscreen";
    var_0[1].vertalign = "fullscreen";
    var_0[1].alpha = 1;
    var_0[1] setshader( "uav_predator2_dirbar", 256, 32 );
    var_0[2] = newclienthudelem( self );
    var_0[2].x = _ID18411( 320 );
    var_0[2].y = _ID18411( 55 );
    var_0[2].alignx = "center";
    var_0[2].aligny = "middle";
    var_0[2].sort = 1;
    var_0[2].horzalign = "fullscreen";
    var_0[2].vertalign = "fullscreen";
    var_0[2].alpha = 1;
    var_0[2] setshader( "uav_predator2_heading_frame", 21, 32 );
    var_0[3] = _ID98::_ID2442( "default", 1.2 );
    var_0[3].x = _ID18411( 320 );
    var_0[3].y = _ID18411( 55 );
    var_0[3].sort = 1;
    var_0[3].horzalign = "fullscreen";
    var_0[3].vertalign = "fullscreen";
    var_0[3].alignx = "center";
    var_0[3].aligny = "middle";
    var_0[3].alpha = 1;
    var_0[3].color = ( 0.56, 1, 0.52 );
    var_0[3] setvalue( 215 );
    thread _ID18430( var_0[0], var_0[3] );
    return var_0;
}

_ID18434()
{
    var_0 = newclienthudelem( self );
    var_0.x = _ID18411( 272 );
    var_0.y = _ID18411( 292 );
    var_0.sort = 1;
    var_0.horzalign = "fullscreen";
    var_0.vertalign = "fullscreen";
    var_0.alpha = 1;
    var_0 setshader( "uav_predator2_horz", 64, 64 );
    return var_0;
}

_ID18435()
{
    var_0 = newclienthudelem( self );
    var_0.x = _ID18411( 320 );
    var_0.y = _ID18411( 240 );
    var_0.alignx = "center";
    var_0.aligny = "middle";
    var_0.sort = 1;
    var_0.horzalign = "fullscreen";
    var_0.vertalign = "fullscreen";
    var_0.alpha = 1;
    var_0 setshader( "uav_predator2_xhair", 205, 205 );
    return var_0;
}

_ID18436( var0 )
{
    while ( isdefined( var0 ) )
    {
        if ( self adsbuttonpressed() )
            var0 thread _ID18437( self );

        wait 0.05;
    }
}

_ID18437( var0 )
{
    var0 dodamage( 1, var0.origin );
    var_1 = spawn( "script_origin", ( 0, 0, 0 ) );
    var_1.origin = self.origin;
    var_1.angles = self.angles;
    self delete();

    for ( var_2 = 0; var_2 < 6; var_2++ )
    {
        wait(randomfloatrange( 0.1, 0.3 ));
        var_3 = anglestoforward( var_1.angles );
        var_4 = anglestoright( var_1.angles );
        var_5 = anglestoup( var_1.angles );
        var_6 = randomintrange( -64, 64 );
        var_7 = randomintrange( -64, 64 );
        var_8 = randomintrange( -64, -63 );
        var_9 = magicgrenade( "m203", var_1.origin, var_1.origin + var_6 * var_3 + var_7 * var_4 + var_8 * var_5 );
        var_9 thread _ID18438();
    }

    var_1 delete();
}

_ID18438()
{
    var_0 = spawn( "script_origin", ( 0, 0, 0 ) );

    while ( isdefined( self ) )
    {
        var_0.origin = self.origin;
        wait 0.05;
    }

    playfx( level._effect["slamraam_explosion"], var_0.origin );
    radiusdamage( var_0.origin + ( 0, 0, 128 ), 512, 200, 200 );
    earthquake( 0.4, 1, var_0.origin, 1000 );
    var_0 playsound( "detpack_explo_main", "sound_done" );
    var_0 delete();
}
