#include maps\_utility;
#include common_scripts\utility;
#include maps\_vehicle;
#include maps\_sp_killstreaks;


// -------------------
// --- SP AIRDROPS ---
// -------------------
// TODO DOCUMENT
// airdrop global preloads
sp_airdrop_preload()
{
	PrecacheItem( "airdrop_marker_mp" );
	
	PrecacheModel( "com_plasticcase_friendly" );
	PrecacheModel( "com_plasticcase_enemy" );
	PrecacheModel( "com_plasticcase_taskforce141" );
	
	PrecacheShader( "compass_objpoint_ammo_friendly" );
}

// TODO DOCUMENT
// inits airdrop functionality
sp_airdrop_init()
{
	ASSERT( !sp_airdrop_init_done() );
	
	if( !IsDefined( level.startingKillstreakCrateObjID ) )
	{
		level.startingKillstreakCrateObjID = 24;
	}
	
	level.numAirdropCrates = 0;
	
	level.ad = SpawnStruct();
	//level.ad.mapCenter = sp_airdrop_set_map_center(); // not currently used
	
	sp_airdrop_setup_crate_collisions();
	
	level.ad.globalInitDone = true;
}

sp_airdrop_init_done()
{
	return( IsDefined( level.ad ) && IsDefined( level.ad.globalInitDone ) );
}

/* not currently used
sp_airdrop_set_map_center()
{
	level.mapCenter = ( 0, 0, 0 );
	
	mapCenterEnt = GetStruct( "map_center", "targetname" );
	if( IsDefined( mapCenterEnt ) )
	{
		level.mapCenter = mapCenterEnt.origin;
	}
	
	return level.mapCenter;
}
*/

sp_try_use_airdrop( crateType )
{
	result = undefined;

	if ( self isUsingRemote() )
	{
		return false;
	}
	
	result = self sp_begin_airdrop_via_marker( crateType );
	
	if ( (!isDefined( result ) || !result) && !isDefined( self.airDropMarker ) )
	{
		return false;
	}
	
	return true;
}

sp_begin_airdrop_via_marker( crateType )
{
	self endon ( "death" );
	self endon( "airdrop_marker_thrown" );
	self.airDropMarker = undefined;

	self thread sp_watch_airdrop_marker_usage( crateType );

	/* TODO need to add support for this? don't have this function in SP atm
	while( self isChangingWeapon() )
		wait ( 0.05 );
	*/

	currentWeapon = self getCurrentWeapon();
	
	if ( isAirdropMarker( currentWeapon ) )
		airdropMarkerWeapon = currentWeapon;
	else
		airdropMarkerWeapon = undefined;
		
	while( isAirdropMarker( currentWeapon ) )
	{
		self waittill( "weapon_change", currentWeapon );

		if ( isAirdropMarker( currentWeapon ) )
			airdropMarkerWeapon = currentWeapon;
	}
	
	self notify ( "stopWatchingAirDropMarker" );
	
	if ( !isDefined( airdropMarkerWeapon ) )
		return false;
	
	// having the weapon and ammo for it means we didn't succeed in using the weapon
	return( !(self getAmmoCount( airdropMarkerWeapon ) && self hasWeapon( airdropMarkerWeapon )) );
}

sp_watch_airdrop_marker_usage( crateType )
{
	self notify( "watchAirDropMarkerUsage" );
	
	self endon( "disconnect" );
	self endon( "watchAirDropMarkerUsage" );
	self endon( "stopWatchingAirDropMarker" );
	
	thread sp_watch_airdrop_marker( crateType );
	
	for ( ;; )
	{
		self waittill( "grenade_pullback", weaponName );

		if ( !isAirdropMarker( weaponName ) )
			continue;

		self _disableUsability();

		self beginAirDropMarkerTracking();
	}
}

sp_watch_airdrop_marker( crateType )
{
	self notify( "watchAirDropMarker" );
	
	self endon( "watchAirDropMarker" );
	self endon( "spawned_player" );
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "grenade_fire", airDropWeapon, weapname );
		
		if ( !isAirdropMarker( weapname ) )
		{
			continue;
		}
		
		self notify( "airdrop_marker_thrown" );

		airDropWeapon thread airdropDetonateOnStuck();
		
		airDropWeapon.owner = self;
		airDropWeapon.weaponName = weapname;
		self.airDropMarker = airDropWeapon;
		
		airDropWeapon thread sp_airdrop_marker_activate( crateType );
	}
}

sp_airdrop_marker_activate( crateType )
{
	self notify( "airDropMarkerActivate" );
	self endon( "airDropMarkerActivate" );
	self waittill( "explode", position );
	owner = self.owner;

	if ( !isDefined( owner ) )
		return;
	
	/*
	if ( owner isEMPed() )
		return;
	*/

	wait 0.05;
	
	level sp_airdrop_do_flyby( crateType, owner, position, randomFloat( 360 ) );
}

sp_airdrop_do_flyby( crateType, owner, dropSite, dropYaw, heightAdjustment )
{
	flyHeight = self getFlyHeightOffset( dropSite );
	if ( !isDefined(heightAdjustment) )
		heightAdjustment = 0;
	
	flyHeight += heightAdjustment;
	
	if ( !isDefined( owner ) ) 
		return;

	pathGoal = dropSite * ( 1, 1, 0 ) +  ( 0, 0, flyHeight );	
	pathStart = getPathStart( pathGoal, dropYaw );
	pathEnd = getPathEnd( pathGoal, dropYaw );		
	
	pathGoal = pathGoal + ( anglestoforward( (0,dropYaw,0) )* -50 );

	chopper = sp_airdrop_heli_setup( owner, pathStart, pathGoal );
	
	chopper endon( "death" );
	
	assert ( isDefined( chopper ) );
	
	chopper setVehGoalPos( pathGoal, 1 );
	
	chopper thread sp_airdrop_drop_the_crate( crateType, dropSite, flyHeight, false, undefined, pathStart );
	
	wait ( 2 );
	
	chopper Vehicle_SetSpeed( 75, 40 );
	chopper SetYawSpeed( 180, 180, 180, .3 );
	
	chopper waittill ( "goal" );
	wait( .10 );
	chopper notify( "drop_crate" );
	chopper setvehgoalpos( pathEnd, 1 );
	chopper Vehicle_SetSpeed( 300, 75 );
	chopper.leaving = true;
	chopper waittill ( "goal" );
	chopper notify( "leaving" );
	//chopper trimActiveBirdList();
	//level.littleBirds--;
	chopper notify( "delete" );
	chopper delete();
}

// spawn helicopter at a start node and monitors it
sp_airdrop_heli_setup( owner, pathStart, pathGoal )
{
	forward = vectorToAngles( pathGoal - pathStart );
	
	chopperSpawner = GetEnt( "airdrop_littlebird", "targetname" );
	ASSERT( IsDefined( chopperSpawner ) );
	chopperSpawner.origin = pathStart;
	chopperSpawner.angles = forward;
	// MP only - SP needs to have the chopper in the base map for it to work
	//chopper = spawnHelicopter( owner, pathStart, forward, "littlebird" , "vehicle_little_bird_armed" );
	chopper = maps\_vehicle::spawn_vehicle_from_targetname( "airdrop_littlebird" );
	chopper Hide();

	if ( !isDefined( chopper ) )
	{
		return;
	}
	
	// don't shoot at enemies
	if( IsDefined( self.mgturret ) )
	{
		self notify( "mg_off" );
		
		foreach( turret in self.mgturret )
		{
			turret TurretFireDisable();
			turret SetMode( "manual" );
		}
	}

	chopper.health = 500;
	chopper setCanDamage( false );  // TODO make the chopper shootable eventually
	chopper.owner = owner;
	chopper.team = owner.team;
	chopper thread heli_existence();
	//chopper thread heliDestroyed();
	chopper SetMaxPitchRoll( 45, 85 );	
	chopper Vehicle_SetSpeed( 250, 175 );
	chopper delaycall( 0.1, ::Show );
	//level.littlebird[level.littlebird.size] = chopper;
	
	return chopper;
}

heli_existence()
{
	self waittill_any( "crashing", "leaving" );
	//self trimActiveBirdList();
	
	self notify( "helicopter_gone" );
}

sp_airdrop_drop_the_crate( crateType, dropPoint, lbHeight, dropImmediately, crateOverride, startPos )
{
	dropCrate = [];
	self.owner endon ( "disconnect" );
		
	dropCrate = sp_create_airdrop_crate( self.owner, crateType, startPos );
	
	dropCrate LinkTo( self, "tag_ground" , (32,0,5) , (0,0,0) );

	dropCrate.angles = (0,0,0);
	dropCrate show();
	dropSpeed = self.veh_speed;
	
	self waittill ( "drop_crate" );
	
	dropCrate Unlink();
	dropCrate PhysicsLaunchServer( (0,0,0), (randomInt(5),randomInt(5),randomInt(5)) );		
	dropCrate thread sp_airdrop_crate_physics_waiter();
	dropCrate thread sp_airdrop_crate_damage_enemies_on_fall( dropPoint, 64 );
}

sp_create_airdrop_crate( owner, crateType, startPos )
{
	dropCrate = spawn( "script_model", startPos );
	
	// for when a player is capping the crate
	dropCrate.inUse = false;
	dropCrate.curProgress = 0;
	dropCrate.useTime = 0;
	dropCrate.useRate = 0;
	
	if ( isDefined( owner ) )
	{
		dropCrate.owner = owner;
	}
	else
	{
		dropCrate.owner = undefined;
	}
	
	dropCrate.crateType = crateType;
	//dropCrate.dropType = dropType;
	dropCrate.targetname = "care_package";
	
	// this model is just the faction-specific logos
	// ENHANCEMENT make this variable?
	dropCrate setModel( "com_plasticcase_taskforce141" );
	dropCrate sp_airdrop_crate_attach_collision();
	dropCrate.collision thread sp_airdrop_crate_unlink_collision( dropCrate );

	// this is the model that looks like a crate and not just decals arranged around a rectangular empty space
	// ENHANCEMENT make this variable?
	dropCrate.baseModel = spawn( "script_model", startPos );
	dropCrate.baseModel setModel( "com_plasticcase_friendly" );
	dropCrate.baseModel delaycall( 0.25, ::LinkTo, dropCrate, "tag_origin", (0,0,0), (0,0,0) );
	dropCrate thread sp_airdrop_crate_delete_on_owner_death( owner );
	
	level.numAirdropCrates++;
	
	return dropCrate;
}

sp_delete_airdrop_crate()
{
	if ( isDefined( self.objIdFriendly ) )
	{
		objective_delete( self.objIdFriendly );
	}

	//if ( isDefined( self.objIdEnemy ) )
	//	_objective_delete( self.objIdEnemy );
	
	if ( isdefined( level.crates_on_ground ) && level.crates_on_ground.size )
	{
		level.crates_on_ground = array_remove( level.crates_on_ground, self );
		level.numAirdropCrates--;
	}
	
	if( isdefined( self ) )
	{
		self.baseModel Delete();
		self Delete();
	}
}

sp_airdrop_setup_crate_collisions()
{
	colls = GetEntArray( "airdrop_crate_collision", "targetname" );
	ASSERTEX( colls.size, "Can't find any airdrop crate collision sbmodels in the level! Use the prefab to get them in there." );
	
	foreach( coll in colls )
	{
		ASSERTEX( coll.classname == "script_brushmodel", "Found an ent with targetname 'airdrop_crate_collision' that wasn't a script_brushmodel at origin " + coll.origin + ". All such ents should be script_brushmodels." );
		
		coll ConnectPaths();
		coll NotSolid();
	}
	
	level.airDropCrateCollisionBoxes = colls;
}

sp_airdrop_get_free_sbmodel_collision()
{
	coll = undefined;
	
	foreach( collision in level.airDropCrateCollisionBoxes )
	{
		if( !IsDefined( collision.isInUse ) )
		{
			coll = collision;
			break;
		}
	}
	
	ASSERTEX( IsDefined( coll ), "Couldn't find an unused level airdrop crate collision sbmodel!" );
	
	return coll;
}

sp_airdrop_crate_attach_collision()
{
	sbmodel = sp_airdrop_get_free_sbmodel_collision();
	
	sbmodel.origin = self.origin;
	sbmodel.angles = self.angles;
	
	sbmodel Solid();
	sbmodel LinkTo( self );
	sbmodel.isInUse = true;
	
	self.collision = sbmodel;
}

sp_airdrop_crate_damage_enemies_on_fall( dropPoint, damageRadius )
{
	ASSERT( IsDefined( dropPoint ) );
	ASSERT( IsDefined( damageRadius ) );
	
	for ( ; IsDefined( self ) && DistanceSquared( self.origin, dropPoint ) > 1024; wait 0.05 ){}
	
	if ( !IsDefined( self ) )
		return;
		
	enemies = GetAISpeciesArray( "axis", "all" );
	
	foreach ( guy in enemies )
	{
		if ( DistanceSquared( self.origin, guy.origin ) < ( damageRadius * damageRadius ) )
		{
			if ( IsDefined( self.owner ) )
			{
				guy DoDamage( 300, self.origin, self.owner, self );
			}
			else
			{
				guy DoDamage( 300, self.origin );
			}
		}
	}
}

sp_airdrop_crate_delete_on_owner_death( owner )
{
	owner waittill ( "death" );
	self sp_delete_airdrop_crate();
}

sp_airdrop_crate_unlink_collision( owner )
{
	owner waittill( "death" );
	self Unlink();
	self ConnectPaths();
	self NotSolid();
	self.isInUse = undefined;
}

sp_airdrop_crate_physics_waiter()
{
	self waittill( "physics_finished" );
	
	self.crate_num = gettime();
	
	if( !isdefined( level.crates_on_ground ) )
		level.crates_on_ground = [];
	level.crates_on_ground[level.crates_on_ground.size] = self;
	
	// remove oldest crate if more than 4 crates spawned
	if ( level.crates_on_ground.size > 4 )
	{
		level.crates_on_ground[ 0 ] sp_delete_airdrop_crate();
	}
	
	self thread sp_airdrop_crate_think();
	level thread sp_airdrop_crate_timeout( self, self.owner );
	
	/*  TODO reimplement for SP: delete if it's more than 3000 units below the lowest spawnpoint
	if ( abs(self.origin[2] - level.lowSpawn.origin[2]) > 3000 )
	{
		if ( isDefined( self.objIdFriendly ) )
			_objective_delete( self.objIdFriendly );

		if ( isDefined( self.objIdEnemy ) )
			_objective_delete( self.objIdEnemy );

		self delete();	
	}
	*/
}

//deletes if crate wasnt used after 90 seconds
sp_airdrop_crate_timeout( dropCrate, owner )
{
	//level endon ( "game_ended" );
	dropCrate endon( "death" );
	
	waitTime = 120;
	if( IsDefined( level.airdropCrateTimeout ) )
	{
		waitTime = level.airdropCrateTimeout;
	}
	
	if( waitTime <= 0 )
	{
		// the level doesn't want crates to time out at all
		return;
	}
	
	wait( waitTime );
	
	// wait while someone is using it
	while( dropCrate.curProgress != 0 )
	{
		wait( 1 );
	}
	
	dropCrate sp_delete_airdrop_crate();
}

sp_airdrop_crate_think()
{
	self endon( "death" );
	
	self sp_airdrop_crate_setup_for_use();
	
	self thread sp_airdrop_crate_owner_capture_think();
	self thread sp_airdrop_teammate_capture_think();
	
	// can be used for AI hijacking, etc
	if( IsDefined( level.sp_airdrop_crate_custom_thread ) )
	{
		self thread [[ level.sp_airdrop_crate_custom_thread ]]();
	}

	while( 1 )
	{
		self waittill ( "captured", capturedBy );
		
		// tell the owner if it got hijacked
		if ( isDefined( self.owner ) && capturedBy != self.owner )
		{
			self thread sp_airdrop_crate_hijack_notify( capturedBy );
		}
		
		if( IsPlayer( capturedBy ) )
		{
			player = capturedBy;
	
			player PlayLocalSound( "ammo_crate_use" );
			
			if( IsDefined( self.killstreakInfo.crateOpenFunc ) )
			{
				// perk crate open func requires perk reference
				if( issubstr( self.killstreakInfo.streaktype, "specialty_" ) )
					player thread [[self.killstreakInfo.crateOpenFunc]]( self.killstreakInfo.streaktype );
				else
					player thread [[self.killstreakInfo.crateOpenFunc]]();
			}
			else
			{
				player thread give_sp_killstreak( self.crateType );
			}
		}
		
		self sp_delete_airdrop_crate();
	}
}

sp_airdrop_crate_hijack_notify( capturedBy )
{
	self notify( "hijacked", capturedBy );
	
	if( !IsPlayer( self.owner ) )
	{
		return;
	}
	
	if( capturedBy.team == self.owner.team )
	{
		if( IsDefined( level.sp_airdrop_crate_friendly_hijack_thread ) )
		{
			self.owner thread [[level.sp_airdrop_crate_friendly_hijack_thread]]( capturedBy );
		}
	}
	else
	{
		if( IsDefined( level.sp_airdrop_crate_enemy_hijack_thread ) )
		{
			self.owner thread [[level.sp_airdrop_crate_enemy_hijack_thread]]( capturedBy );
		}
	}
}

sp_airdrop_crate_setup_for_use()
{
	self.collision DisconnectPaths();
	
	killstreakInfo = get_sp_killstreak_info( self.crateType );
	self.killstreakInfo = killstreakInfo;
	
	// compass icon
	curObjID = sp_airdrop_get_crate_obj_id();
	objective_add( curObjID, "invisible", ( 0, 0, 0 ) );
	objective_position( curObjID, self.origin );
	//objective_state( curObjID, "active" );
	objective_icon( curObjID, "compass_objpoint_ammo_friendly" );
	self.objIdFriendly = curObjID;
	
	// world icon
	self sp_crate_world_icon( killstreakInfo.crateIcon, ( 0, 0, 24 ), 14, 14 );
	
	self SetCursorHint( "HINT_NOICON" );
	self SetHintString( killstreakInfo.crateHint );
	self MakeUsable();
	if ( isdefined( level.airdropCrateUnstuck ) && level.airdropCrateUnstuck )
	{
		self thread sp_airdrop_unstuck_think();
	}
}

sp_airdrop_unstuck_think()
{
	self endon( "death" );
	self endon( "captured" );

	// intentional wait for player to realize he/she is stuck in crate
	wait 2;
	
	stuck_owner			= undefined;
	other_stuck_players = [];
	
	foreach( player in level.players )
	{
		if ( isdefined( self.collision ) && self.collision istouching( player ) )
		{
			if ( isdefined( self.owner ) && self.owner == player )
				stuck_owner = player;
			else
				other_stuck_players[ other_stuck_players.size ] = player;
		}
	}
	
	// if more than one player is stuck, give it to owner
	if ( isdefined( stuck_owner ) )
	{
		self notify( "trigger", stuck_owner );
		return;
	}
	
	// if more than one player is stuck and owner isn't one of them, give to first player in array
	if ( other_stuck_players.size > 0 )
		self notify( "trigger", other_stuck_players[ 0 ] );
}

sp_airdrop_get_crate_obj_id()
{
	objID = undefined;
	
	if( !IsDefined( level.lastUsedKillstreakCrateObjID ) )
	{
		objID = level.startingKillstreakCrateObjID;
	}
	else
	{
		objID = level.lastUsedKillstreakCrateObjID + 1;
	}
	
	if( objID > ( level.startingKillstreakCrateObjID + 7 ) )
	{
		objID = level.startingKillstreakCrateObjID;
	}
	
	level.lastUsedKillstreakCrateObjID = objID;
	
	return objID;
}

sp_crate_world_icon( icon, offset, width, height )
{
	worldIcon = NewHudElem();
	
	worldIcon.archived = true;
	worldIcon.x = self.origin[0] + offset[0];
	worldIcon.y = self.origin[1] + offset[1];
	worldIcon.z = self.origin[2] + offset[2];
	worldIcon.alpha = 0.85;
	worldIcon SetShader( icon, width, height );
	
	worldIcon SetWaypoint( true, true, false );
	worldIcon thread keepPositioned( self, offset );
	
	self.crateWorldIcon = worldIcon;
	self thread destroyIconsOnDeath();
}

sp_airdrop_crate_owner_capture_think()
{
	while ( IsDefined( self ) )
	{
		self waittill( "trigger", player );

		//if ( !player isOnGround() )
		//	continue;

		if ( IsDefined( self.owner ) && player != self.owner )
		{
			continue;
		}
		
		if ( !sp_use_hold_think( player, 500 ) )
		{
			continue;
		}
		
		self notify( "captured", player );
		level notify( "crate_captured" );
	}
}

sp_airdrop_teammate_capture_think()
{
	while ( IsDefined( self ) )
	{
		self waittill ( "trigger", player );

		//if ( !player isOnGround() )
		//	continue;

		if ( IsDefined( self.owner ) && player == self.owner )
		{
			continue;
		}
		
		if ( !sp_use_hold_think( player ) )
		{
			continue;
		}
		
		self notify( "captured", player );
		level notify( "crate_captured" );
	}
}

sp_use_hold_think( player, useTime ) 
{
    player FreezeControls( true );
    
    player _disableWeapon();
    
    self.curProgress = 0;
    self.inUse = true;
    self.useRate = 0;
    
	if( IsDefined( level.airdropCrateUseTime ) )
    {
    	self.useTime = level.airdropCrateUseTime;
    }
    else
    {
	    if ( isDefined( useTime ) )
	    {
			self.useTime = useTime;
		}
		else
		{
			self.useTime = 3000;
		}
	}

	if ( self.useTime > 0 )
	{
	    player thread sp_personal_use_bar( self );
	    result = sp_use_hold_think_loop( player );
		assert ( isDefined( result ) );
	}
	else
	{
		result = true;
	}
	
    if ( isAlive( player ) )
    {
        player _enableWeapon();
        player FreezeControls( false );
    }
    
    if ( !isDefined( self ) )
    	return false;

    self.inUse = false;
	self.curProgress = 0;

	return ( result );
}

sp_use_hold_think_loop( player )
{
    while( IsDefined( self ) && IsAlive( player ) && player useButtonPressed() && self.curProgress < self.useTime )
    {
        self.curProgress += (50 * self.useRate);
       
       	if ( IsDefined(self.objectiveScaler) )
       	{
        	self.useRate = 1 * self.objectiveScaler;
        }
		else
		{
			self.useRate = 1;
		}

        if ( self.curProgress >= self.useTime )
        {
            return ( IsAlive( player ) );
        }
       
        wait 0.05;
    } 
    
    return false;
}

sp_personal_use_bar( object )
{
    self endon( "disconnect" );
    
    useBar = createPrimaryProgressBar( -25 );
    useBarText = createPrimaryProgressBarText( -25 );
    useBarText setText( &"SP_KILLSTREAKS_CAPTURING_CRATE" );

    lastRate = -1;
    while ( IsAlive( self ) && IsDefined( object ) && object.inUse )
    {
        if ( lastRate != object.useRate )
        {
            if( object.curProgress > object.useTime)
                object.curProgress = object.useTime;
               
            useBar updateBar( object.curProgress / object.useTime, (1000 / object.useTime) * object.useRate );

            if ( !object.useRate )
            {
                useBar hideElem();
                useBarText hideElem();
            }
            else
            {
                useBar showElem();
                useBarText showElem();
            }
        }    
        lastRate = object.useRate;
        wait ( 0.05 );
    }
    
    useBar destroyElem();
    useBarText destroyElem();
}



// --------------------
// --- DUPE SCRIPTS ---
// --------------------
getFlyHeightOffset( dropSite )
{
	lbFlyHeight = 850;
	
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	if ( !isDefined( heightEnt ) )//old system 
	{
		/#
		println( "NO DEFINED AIRSTRIKE HEIGHT SCRIPT_ORIGIN IN LEVEL" );
		#/
		if ( isDefined( level.airstrikeHeightScale ) )
		{	
			if ( level.airstrikeHeightScale > 2 )
			{
				lbFlyHeight = 1500;
				return( lbFlyHeight * (level.airStrikeHeightScale ) );
			}
			
			return( lbFlyHeight * level.airStrikeHeightScale + 256 + dropSite[2] );
		}
		else
			return ( lbFlyHeight + dropsite[2] );	
	}
	else
	{
		return heightEnt.origin[2];
	}
	
}

getPathStart( coord, yaw )
{
	pathRandomness = 100;
	lbHalfDistance = 15000;

	direction = (0,yaw,0);

	startPoint = coord + ( anglestoforward( direction )* ( -1 * lbHalfDistance ));
	startPoint += ( (randomfloat(2) - 1)*pathRandomness, (randomfloat(2) - 1)*pathRandomness, 0 );
	
	return startPoint;
}


getPathEnd( coord, yaw )
{
	pathRandomness = 150;
	lbHalfDistance = 15000;

	direction = (0,yaw,0);

	endPoint = coord + ( anglestoforward( direction + ( 0,90,0 ) )* lbHalfDistance );
	endPoint += ( (randomfloat(2) - 1)*pathRandomness  , (randomfloat(2) - 1)*pathRandomness  , 0 );
	
	return endPoint;
}

isAirdropMarker( weaponName )
{
	switch ( weaponName )
	{
		case "airdrop_marker_mp":
		case "airdrop_mega_marker_mp":
		case "airdrop_sentry_marker_mp":
			return true;
		default:
			return false;
	}
}

beginAirDropMarkerTracking()
{
	self notify( "beginAirDropMarkerTracking" );
	self endon( "beginAirDropMarkerTracking" );
	self endon( "death" );
	self endon( "disconnect" );

	self waittill_any( "grenade_fire", "weapon_change" );
	self _enableUsability();
}

airdropDetonateOnStuck()
{
	self endon ( "death" );
	
	self waittill( "missile_stuck" );
	
	self detonate();
}



// ---------------------------------
// --- MP _ENTITYHEADICONS DUPES ---
// ---------------------------------
destroyIconsOnDeath()
{
	self notify ( "destroyIconsOnDeath" );
	self endon ( "destroyIconsOnDeath" );
	
	self waittill ( "death" );
	
	self.crateWorldIcon Destroy();
}

keepPositioned( owner, offset )
{
	self endon ( "death" );
	owner endon ( "death" );
	
	pos = owner.origin;

	for ( ;; )
	{
		if ( pos != owner.origin ) 
		{
			pos = owner.origin;

			self.x = pos[0] + offset[0];
			self.y = pos[0] + offset[0];
			self.z = pos[0] + offset[0];
		}
		wait .05;
	}	
}

keepIconPositioned()
{
	self endon( "kill_entity_headicon_thread" );
	self endon( "death" );
	
	pos = self.origin;
	while(1)
	{
		if ( pos != self.origin ) 
		{
			self updateHeadIconOrigin();
			pos = self.origin;
		}
		wait .05;
	}
}

destroyHeadIconsOnDeath()
{
	self endon( "kill_entity_headicon_thread" );
	self waittill ( "death" );

	// TODO: remove and fix properly after ship
	if( !isDefined(self.entityHeadIcon) )
		return;

	self.entityHeadIcon destroy();
}


updateHeadIconOrigin()
{
	self.entityHeadIcon.x = self.origin[0] + self.entityHeadIconOffset[0];
	self.entityHeadIcon.y = self.origin[1] + self.entityHeadIconOffset[1];
	self.entityHeadIcon.z = self.origin[2] + self.entityHeadIconOffset[2];
}



// --------------------------
// --- MP _HUD_UTIL DUPES ---
// --------------------------
createPrimaryProgressBarText( yOffset )
{
	if ( !isDefined( yOffset ) )
		yOffset = 0;
	
	text = maps\_hud_util::createClientFontString( "hudbig", level.primaryProgressBarFontSize );
	text.hidden = false;
	text setPoint("CENTER", undefined, level.primaryProgressBarTextX, level.primaryProgressBarTextY - yOffset );
	text.sort = -1;
	return text;
}

createPrimaryProgressBar( yOffset )
{
	if ( !isDefined( yOffset ) )
		yOffset = 0;
		
	bar = createBar( (1, 1, 1), level.primaryProgressBarWidth, level.primaryProgressBarHeight );
	bar setPoint("CENTER", undefined, level.primaryProgressBarX, level.primaryProgressBarY - yOffset );

	return bar;
}

createBar( color, width, height, flashFrac )
{
	barElem = newClientHudElem(	self );
	barElem.x = 0 ;
	barElem.y = 0;
	barElem.frac = 0;
	barElem.color = color;
	barElem.sort = -2;
	barElem.shader = "progress_bar_fill";
	barElem setShader( "progress_bar_fill", width, height );
	barElem.hidden = false;
	if ( isDefined( flashFrac ) )
	{
		barElem.flashFrac = flashFrac;
//		barElem thread flashThread();
	}
	
	barElemBG = newClientHudElem( self );
	barElemBG.elemType = "bar";
	barElemBG.width = width;
	barElemBG.height = height;
	barElemBG.xOffset = 0;
	barElemBG.yOffset = 0;
	barElemBG.bar = barElem;
	barElemBG.children = [];
	barElemBG.sort = -3;
	barElemBG.color = (0,0,0);
	barElemBG.alpha = 0.5;
	barElemBG.padding = 0;
	barElemBG maps\_hud_util::setParent( level.uiParent );
	barElemBG setShader( "progress_bar_bg", width + 4, height + 4 );
	barElemBG.hidden = false;
	
	return barElemBG;
}

setPoint( point, relativePoint, xOffset, yOffset, moveTime )
{
	if ( !isDefined( moveTime ) )
		moveTime = 0;

	element = self maps\_hud_util::getParent();

	if ( moveTime )
		self moveOverTime( moveTime );
	
	if ( !isDefined( xOffset ) )
		xOffset = 0;
	self.xOffset = xOffset;

	if ( !isDefined( yOffset ) )
		yOffset = 0;
	self.yOffset = yOffset;
		
	self.point = point;

	self.alignX = "center";
	self.alignY = "middle";

	if ( isSubStr( point, "TOP" ) )
		self.alignY = "top";
	if ( isSubStr( point, "BOTTOM" ) )
		self.alignY = "bottom";
	if ( isSubStr( point, "LEFT" ) )
		self.alignX = "left";
	if ( isSubStr( point, "RIGHT" ) )
		self.alignX = "right";

	if ( !isDefined( relativePoint ) )
		relativePoint = point;

	self.relativePoint = relativePoint;

	relativeX = "center_adjustable";
	relativeY = "middle";

	if ( isSubStr( relativePoint, "TOP" ) )
		relativeY = "top_adjustable";
	if ( isSubStr( relativePoint, "BOTTOM" ) )
		relativeY = "bottom_adjustable";
	if ( isSubStr( relativePoint, "LEFT" ) )
		relativeX = "left_adjustable";
	if ( isSubStr( relativePoint, "RIGHT" ) )
		relativeX = "right_adjustable";

	if ( element == level.uiParent )
	{
		self.horzAlign = relativeX;
		self.vertAlign = relativeY;
	}
	else
	{
		self.horzAlign = element.horzAlign;
		self.vertAlign = element.vertAlign;
	}


	if ( strip_suffix( relativeX, "_adjustable" ) == element.alignX )
	{
		offsetX = 0;
		xFactor = 0;
	}
	else if ( relativeX == "center" || element.alignX == "center" )
	{
		offsetX = int(element.width / 2);
		if ( relativeX == "left_adjustable" || element.alignX == "right" )
			xFactor = -1;
		else
			xFactor = 1;	
	}
	else
	{
		offsetX = element.width;
		if ( relativeX == "left_adjustable" )
			xFactor = -1;
		else
			xFactor = 1;
	}
	self.x = element.x + (offsetX * xFactor);

	if ( strip_suffix( relativeY, "_adjustable" ) == element.alignY )
	{
		offsetY = 0;
		yFactor = 0;
	}
	else if ( relativeY == "middle" || element.alignY == "middle" )
	{
		offsetY = int(element.height / 2);
		if ( relativeY == "top_adjustable" || element.alignY == "bottom" )
			yFactor = -1;
		else
			yFactor = 1;	
	}
	else
	{
		offsetY = element.height;
		if ( relativeY == "top_adjustable" )
			yFactor = -1;
		else
			yFactor = 1;
	}
	self.y = element.y + (offsetY * yFactor);
	
	self.x += self.xOffset;
	self.y += self.yOffset;
	
	switch ( self.elemType )
	{
		case "bar":
			setPointBar( point, relativePoint, xOffset, yOffset );
			break;
	}
	
	self maps\_hud_util::updateChildren();
}

setPointBar( point, relativePoint, xOffset, yOffset )
{
	self.bar.horzAlign = self.horzAlign;
	self.bar.vertAlign = self.vertAlign;
	
	self.bar.alignX = "left";
	self.bar.alignY = self.alignY;
	self.bar.y = self.y;
	
	if ( self.alignX == "left" )
		self.bar.x = self.x;
	else if ( self.alignX == "right" )
		self.bar.x = self.x - self.width;
	else
		self.bar.x = self.x - int(self.width / 2);
	
	if ( self.alignY == "top" )
		self.bar.y = self.y;
	else if ( self.alignY == "bottom" )
		self.bar.y = self.y;

	self updateBar( self.bar.frac );
}

updateBar( barFrac, rateOfChange )
{
	if ( self.elemType == "bar" )
		updateBarScale( barFrac, rateOfChange );
}

updateBarScale( barFrac, rateOfChange ) // rateOfChange is optional and is in "(entire bar lengths) per second"
{
	barWidth = int(self.width * barFrac + 0.5); // (+ 0.5 rounds)
	
	if ( !barWidth )
		barWidth = 1;
	
	self.bar.frac = barFrac;
	self.bar setShader( self.bar.shader, barWidth, self.height );
	
	assertEx( barWidth <= self.width, "barWidth <= self.width: " + barWidth + " <= " + self.width + " - barFrac was " + barFrac );
	
	//if barWidth is bigger than self.width then we are drawing more than 100%
	if ( isDefined( rateOfChange ) && barWidth < self.width ) 
	{
		if ( rateOfChange > 0 )
		{
			//printLn( "scaling from: " + barWidth + " to " + self.width + " at " + ((1 - barFrac) / rateOfChange) );
			assertex( ((1 - barFrac) / rateOfChange) > 0, "barFrac: " + barFrac + "rateOfChange: " + rateOfChange );
			self.bar scaleOverTime( (1 - barFrac) / rateOfChange, self.width, self.height );
		}
		else if ( rateOfChange < 0 )
		{
			//printLn( "scaling from: " + barWidth + " to " + 0 + " at " + (barFrac / (-1 * rateOfChange)) );
			assertex(  (barFrac / (-1 * rateOfChange)) > 0, "barFrac: " + barFrac + "rateOfChange: " + rateOfChange );
			self.bar scaleOverTime( barFrac / (-1 * rateOfChange), 1, self.height );
		}
	}
	self.bar.rateOfChange = rateOfChange;
	self.bar.lastUpdateTime = getTime();
}

hideElem()
{
	if ( self.hidden )
		return;
		
	self.hidden = true;

	if ( self.alpha != 0 )
		self.alpha = 0;
	
	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		self.bar.hidden = true;
		if ( self.bar.alpha != 0 )
			self.bar.alpha = 0;
	}
}

showElem()
{
	if ( !self.hidden )
		return;
		
	self.hidden = false;

	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		if ( self.alpha != .5 )
			self.alpha = .5;
		
		self.bar.hidden = false;
		if ( self.bar.alpha != 1 )
			self.bar.alpha = 1;

	}
	else
	{
		if ( self.alpha != 1 )
			self.alpha = 1;
	}
}

strip_suffix( lookupString, stripString )
{
	if ( lookupString.size <= stripString.size )
		return lookupString;

	if ( getSubStr( lookupString, lookupString.size - stripString.size, lookupString.size ) == stripString )
		return getSubStr( lookupString, 0, lookupString.size - stripString.size );

	return lookupString;
}

destroyElem()
{
	tempChildren = [];

	for ( index = 0; index < self.children.size; index++ )
	{
		if ( isDefined( self.children[index] ) )
			tempChildren[tempChildren.size] = self.children[index];
	}

	for ( index = 0; index < tempChildren.size; index++ )
		tempChildren[index] maps\_hud_util::setParent( self maps\_hud_util::getParent() );
		
	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		self.bar destroy();
	}
		
	self destroy();
}
