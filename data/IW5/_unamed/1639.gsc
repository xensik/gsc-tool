// IW5 PC GSC
// Decompiled by https://github.com/xensik/gsc-tool
#using_animtree("vehicles");
#using_animtree("generic_human");

main( var0, var1, var2 )
{
    _ID95::_ID10946( "gaz_tigr_turret", var0, var1, var2 );
    _ID95::_ID10962( ::_ID11037 );
    _ID95::_ID10957( ::_ID15960 );
    _ID95::_ID10945( %humvee_50cal_driving_idle_forward, %humvee_50cal_driving_idle_backward, 10 );
    _ID95::_ID10949();
    _ID95::_ID10958( 999, 500, 1500 );
    _ID95::_ID10950( "axis" );

    if ( issubstr( var2, "turret" ) )
    {
        _ID95::_ID10954( ::_ID17464, ::_ID15004 );
        _ID95::_ID10826( "dshk_gaz", "tag_turret", "weapon_dshk_turret", undefined, "auto_ai", 0.2, -20, -14 );
    }
    else
        _ID95::_ID10954( ::_ID15005, ::_ID15004 );

    _ID17462( var2 );
    var_3 = _ID95::_ID11034( var0, var2 );
    _ID95::_ID10925( var_3, "headlight_L", "TAG_HEADLIGHT_LEFT", "misc/spotlight_btr80_daytime", "running", 0 );
    _ID95::_ID10925( var_3, "headlight_R", "TAG_HEADLIGHT_RIGHT", "misc/spotlight_btr80_daytime", "running", 0 );
    _ID95::_ID10925( var_3, "brakelight_L", "TAG_BRAKELIGHT_LEFT", "misc/car_taillight_btr80_eye", "running", 0 );
    _ID95::_ID10925( var_3, "brakelight_R", "TAG_BRAKELIGHT_RIGHT", "misc/car_taillight_btr80_eye", "running", 0 );
}

_ID11037()
{

}

_ID15960()
{
    var_0 = [];
    var_1 = "passengers";
    var_0[var_1] = [];
    var_0[var_1][var_0[var_1].size] = 1;
    var_0[var_1][var_0[var_1].size] = 2;
    var_0[var_1][var_0[var_1].size] = 3;
    var_1 = "all_but_gunner";
    var_0[var_1] = [];
    var_0[var_1][var_0[var_1].size] = 0;
    var_0[var_1][var_0[var_1].size] = 1;
    var_0[var_1][var_0[var_1].size] = 2;
    var_1 = "rear_driver_side";
    var_0[var_1] = [];
    var_0[var_1][var_0[var_1].size] = 2;
    var_1 = "gunner";
    var_0[var_1] = [];
    var_0[var_1][var_0[var_1].size] = 3;
    var_1 = "all";
    var_0[var_1] = [];
    var_0[var_1][var_0[var_1].size] = 0;
    var_0[var_1][var_0[var_1].size] = 1;
    var_0[var_1][var_0[var_1].size] = 2;
    var_0[var_1][var_0[var_1].size] = 3;
    var_0["default"] = var_0["all"];
    return var_0;
}

_ID17462( var0 )
{
    level._effect["gazfire"] = loadfx( "fire/firelp_med_pm_nolight" );
    level._effect["gazexplode"] = loadfx( "explosions/vehicle_explosion_gaz" );
    level._effect["gazcookoff"] = loadfx( "explosions/ammo_cookoff" );
    level._effect["gazsmfire"] = loadfx( "fire/firelp_small_pm_a" );
    _ID95::_ID10942( "vehicle_gaz_tigr_base", "vehicle_gaz_tigr_harbor_destroyed" );
    _ID95::_ID10754( "explosions/vehicle_explosion_gaz", "tag_deathfx" );
    _ID95::_ID10754( "fire/firelp_med_pm_nolight", "tag_cab_fx", undefined, undefined, undefined, 1, 0 );
    _ID95::_ID10754( "fire/firelp_small_pm_a", "tag_trunk_fx", undefined, undefined, undefined, 1, 3 );
    _ID95::_ID10744( 1, 1.6, 500 );
    _ID95::_ID10739( ( 0, 0, 32 ), 300, 200, 0, 0 );
}

_ID15004( var0 )
{
    var0[0]._ID9507 = %gaz_dismount_frontl_door;
    var0[1]._ID9507 = %gaz_dismount_frontr_door;
    var0[2]._ID9507 = %gaz_dismount_backl_door;
    var0[3]._ID9507 = %gaz_dismount_backr_door;
    var0[0]._ID9506 = %gaz_mount_frontl_door;
    var0[1]._ID9506 = %gaz_mount_frontr_door;
    var0[2]._ID9506 = %gaz_enter_back_door;
    var0[3]._ID9506 = %gaz_enter_back_door;
    var0[0]._ID9601 = "gaz_door_open";
    var0[1]._ID9601 = "gaz_door_open";
    var0[2]._ID9601 = "gaz_door_open";
    var0[3]._ID9601 = "gaz_door_open";
    var0[0]._ID9511 = "gaz_door_close";
    var0[1]._ID9511 = "gaz_door_close";
    var0[2]._ID9511 = "gaz_door_close";
    var0[3]._ID9511 = "gaz_door_close";
    return var0;
}

_ID17463( var0 )
{
    var0[3]._ID9507 = %gaz_turret_getout_gaz;
    return var0;
}

_ID15005()
{
    var_0 = [];

    for ( var_1 = 0; var_1 < 4; var_1++ )
        var_0[var_1] = spawnstruct();

    var_0[0]._ID9458 = "tag_driver";
    var_0[1]._ID9458 = "tag_passenger";
    var_0[2]._ID9458 = "tag_guy0";
    var_0[3]._ID9458 = "tag_guy1";
    var_0[0]._ID9460 = 0;
    var_0[0]._ID4168 = %gaz_dismount_frontl;
    var_0[0]._ID9457 = 1;
    var_0[0]._ID3929 = %gaz_idle_frontl;
    var_0[1]._ID3929 = %gaz_idle_frontr;
    var_0[2]._ID3929 = %gaz_idle_backl;
    var_0[3]._ID3929 = %gaz_idle_backr;
    var_0[0]._ID9596 = %gaz_dismount_frontl;
    var_0[1]._ID9596 = %gaz_dismount_frontr;
    var_0[2]._ID9596 = %gaz_dismount_backl;
    var_0[3]._ID9596 = %gaz_dismount_backr;
    var_0[0]._ID9497 = %gaz_mount_frontl;
    var_0[1]._ID9497 = %gaz_mount_frontr;
    var_0[2]._ID9497 = %gaz_enter_backr;
    var_0[3]._ID9497 = %gaz_enter_backl;
    return var_0;
}

_ID17464()
{
    var_0 = _ID15005();
    var_0[3]._ID9469 = 0;
    var_0[3]._ID9659 = ::_ID17465;
    var_0[3]._ID9458 = "tag_guy_turret";
    var_0[3]._ID9596 = %gaz_turret_getout_guy1;
    var_0 = _ID17463( var_0 );
    return var_0;
}

_ID17465( var0, var1, var2, var3 )
{

}
