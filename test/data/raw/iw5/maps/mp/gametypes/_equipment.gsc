/******************************************************************* 
//						_equipment.gsc  
//	
//	Holds all the IW5 equipment specific functions 
//	
//	Jordan Hirsh	Aug. 3rd 	2010
//
//	* function entrance via _weapons.gsc *
********************************************************************/


#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_weapons;

watchTrophyUsage()
{
	self endon( "spawned_player" );
	self endon( "disconnect" );

	self.trophyArray = [];
	while ( 1 )
	{
		self waittill( "grenade_fire", grenade, weapname );
		if ( weapname == "trophy" || weapname == "trophy_mp" )
		{
			if( !IsAlive( self ) )
			{
				grenade delete();
				return;
			}

			// need to see if this is being placed far away from the player and not let it do that
			// this will fix a legacy bug where you can stand on a ledge and plant a claymore down on the ground far below you
			grenade Hide();
			grenade waittill( "missile_stuck" );
			distanceZ = 40;
			if( distanceZ * distanceZ < DistanceSquared( grenade.origin, self.origin ) )
			{
				secTrace = bulletTrace( self.origin, self.origin - (0, 0, distanceZ), false, self );
				
				if( secTrace["fraction"] == 1 )
				{
					// there's nothing under us so don't place the grenade up in the air
					grenade delete();
					self SetWeaponAmmoStock( "trophy_mp", self GetWeaponAmmoStock( "trophy_mp" ) + 1 );
					continue;
				}
				
				grenade.origin = secTrace["position"];
			}
			grenade Show();

			self.trophyArray = array_removeUndefined( self.trophyArray );
			
			if( self.trophyArray.size >= level.maxPerPlayerExplosives )
				self.trophyArray[0] detonate();
			
			// need to spawn in a model and delete the "grenade" so we can damage it properly
			trophy = Spawn( "script_model", grenade.origin );
			assert( IsDefined( trophy ) );
			
			//trophy maketrophysystem( self );
			trophy SetModel( "mp_trophy_system" );
			trophy thread maps\mp\gametypes\_weapons::createBombSquadModel( "mp_trophy_system_bombsquad", "tag_origin", level.otherTeam[self.team], self );
			trophy.angles = grenade.angles;

			self.trophyArray[ self.trophyArray.size ] = trophy;
			trophy.owner = self;
			trophy.team = self.team;
			trophy.weaponName = weapname;
			
			if ( isDefined ( self.trophyRemainingAmmo ) && self.trophyRemainingAmmo > 0 )
				trophy.ammo = self.trophyRemainingAmmo;
			else
				trophy.ammo = 2;
			
			trophy.trigger = spawn( "script_origin", trophy.origin );
			
			trophy thread trophyDamage( self );
			trophy thread trophyActive( self );
			trophy thread trophyDisconnectWaiter( self );
			trophy thread trophyPlayerSpawnWaiter( self );
			trophy thread trophyUseListener( self );

			
			//trophy thread EMPDamage();
			trophy thread c4EMPKillstreakWait();
			
			if ( level.teamBased )
				trophy maps\mp\_entityheadicons::setTeamHeadIcon( trophy.team, (0,0,65) );
			else
				trophy maps\mp\_entityheadicons::setPlayerHeadIcon( trophy.owner, (0,0,65) );

			wait(0.05); // allows for the plant sound to play
			if( IsDefined( grenade ) )
				grenade Delete();
		}
	}
}

//waittillStopMoving( timeout )
//{
//	self endon( "death" );
//
//	prevOrigin = undefined;
//	while( true )
//	{
//		if( !IsDefined( prevOrigin ) )
//			prevOrigin = self.origin;
//		else if( prevOrigin == self.origin )
//			break;
//		else
//			prevOrigin = self.origin;
//
//		wait(0.05);
//		
//		timeout -= 0.05;
//		if( timeout <= 0 )
//			return false;
//	}
//
//	return true;
//}

trophyUseListener( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	owner endon ( "death" );
	
	self.trigger setCursorHint( "HINT_NOICON" );
	self.trigger setHintString( &"MP_PICKUP_TROPHY" );
	self.trigger setSelfUsable( owner );
	self.trigger thread notUsableForJoiningPlayers( owner );

	for ( ;; )
	{
		self.trigger waittill ( "trigger", owner );
		
		owner playLocalSound( "scavenger_pack_pickup" );
		
		// give item to user if not juggernaut (switched class)
		if(	!owner isJuggernaut() )
		{
			owner givePerk( "trophy_mp", false );
			owner.trophyRemainingAmmo = self.ammo;
		}
		self.trigger delete();
		self delete();
		self notify( "death" );
	}
}

trophyPlayerSpawnWaiter( owner )
{
	self endon ( "disconnect" );
	self endon ( "death" );
	
	owner waittill( "spawned" );
	self thread trophyBreak();	
}

trophyDisconnectWaiter( owner )
{
	self endon ( "death" );
	
	owner waittill( "disconnect" );
	self thread trophyBreak();	
}

trophyActive( owner )
{
	owner endon( "disconnect" );
	self endon ( "death" );
	
	position = self.origin;
	
	for( ;; )
	{
		if ( !isDefined( level.grenades ) || ( level.grenades.size < 1 && level.missiles.size < 1 ) || isDefined( self.disabled ) )
		{
			wait( .05 );
			continue;
		}
		
		sentryTargets = combineArrays ( level.grenades, level.missiles );
		
		foreach ( grenade in sentryTargets )
		{
			wait( .05 );
			
			if ( !isDefined(grenade) )
				continue;
			
			if ( grenade == self )
				continue;
			
			if ( isDefined( grenade.weaponName) )
			{
				switch( grenade.weaponName )
				{
				case "claymore_mp":
					continue;
				}
			}

			switch( grenade.model )
			{
			case "mp_trophy_system":
			case "weapon_radar":
			case "weapon_jammer":
			case "weapon_parabolic_knife":
				continue;
			}
	
			if ( !isDefined( grenade.owner ) )
				grenade.owner = GetMissileOwner( grenade );
			
			//assertEx( isDefined( grenade.owner ), "grenade has no owner"  );
			//grenades owner may have disconnected by now if they do we should just assume enemy and detonate it.
			
			if ( isDefined( grenade.owner ) && level.teamBased && grenade.owner.team == owner.team )
				continue;
			
			//dont blow up owners grenades in FFA	
			if ( isDefined( grenade.owner ) && grenade.owner == owner )
				continue;
			
			grenadeDistanceSquared = DistanceSquared( grenade.origin, self.origin );
			
			if ( grenadeDistanceSquared < 147456 )
			{
				if ( BulletTracePassed( grenade.origin, self.origin, false, self ) )
				{
					playFX( level.sentry_fire, self.origin + (0,0,32) , ( grenade.origin - self.origin ), AnglesToUp( self.angles ) );
					self playSound( "trophy_detect_projectile" );

					// do a little extra if this was a predator missile or reaper missile
					if( ( IsDefined( grenade.classname ) && grenade.classname == "rocket" ) &&
						( IsDefined( grenade.type ) && ( grenade.type == "remote" || grenade.type == "remote_mortar" ) ) )
					{
						if( IsDefined( grenade.type ) && grenade.type == "remote" )
						{
							// show that you destroyed a killstreak and give the streak point
							level thread maps\mp\gametypes\_missions::vehicleKilled( grenade.owner, owner, undefined, owner, undefined, "MOD_EXPLOSIVE", "trophy_mp" );
							level thread teamPlayerCardSplash( "callout_destroyed_predator_missile", owner );
							owner thread maps\mp\gametypes\_rank::giveRankXP( "kill", 100, "trophy_mp", "MOD_EXPLOSIVE" );				
							owner notify( "destroyed_killstreak", "trophy_mp" );
						}

						// play fx and a sound
						if( IsDefined( level.chopper_fx["explode"]["medium"] ) )
							PlayFX( level.chopper_fx["explode"]["medium"], grenade.origin );
						if( IsDefined( level.barrelExpSound ) )
							grenade PlaySound( level.barrelExpSound );
					}

					owner thread projectileExplode( grenade, self );
					owner maps\mp\gametypes\_missions::processChallenge( "ch_noboomforyou" );			

					self.ammo--;
					
					if ( self.ammo <= 0 )
						self thread trophyBreak();
				}
			}	
		}	
	}
	
}

projectileExplode( projectile, trophy )
{
	self endon( "death" );
	
	projPosition = projectile.origin;
	projType = projectile.model;
	projAngles = projectile.angles;
	
	if ( projType == "weapon_light_marker" )
	{
		playFX( level.empGrenadeExplode, projPosition, AnglesToForward( projAngles ), AnglesToUp( projAngles ) );
		
		trophy thread trophyBreak();
		
		projectile delete();
		return;
	}
	
	projectile delete();
	trophy playSound( "trophy_fire" );
	playFX( level.mine_explode, projPosition, AnglesToForward( projAngles ), AnglesToUp( projAngles ) );
	
	trophy_attacker = self;
	
	// don't allow the trophy system to provide team kills with friendly fire
	if( level.teamBased && level.friendlyfire )
	{
		trophy_attacker = undefined;
	}

	RadiusDamage( projPosition, 128, 105, 10, trophy_attacker, "MOD_EXPLOSIVE", "trophy_mp" );
}

trophyDamage( owner )
{
	self endon( "death" );
	owner endon( "death" );

	self setcandamage( true );
	// use a health buffer to prevent dying to friendly fire
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 100; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, iDFlags, weapon );

		if ( !isPlayer( attacker ) )
			continue;

		// don't allow people to destroy equipment on their team if FF is off
		if ( !friendlyFireCheck( self.owner, attacker ) )
			continue;

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "concussion_grenade_mp":
			case "flash_grenade_mp":
			case "smoke_grenade_mp":
				continue;
			}
		}
			
		if ( !isdefined( self ) )
			return;

		if ( type == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;
		
		if ( isDefined(weapon) && weapon == "emp_grenade_mp" )
			self.damageTaken += self.maxHealth;

		self.damageTaken += damage;
		
		if( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "trophy" );
		}

		if ( self.damageTaken >= self.maxHealth )
		{
			if( IsDefined( owner ) && attacker != owner )
				attacker notify("destroyed_explosive");

			self thread trophyBreak();
		}
	}
}

trophyBreak()
{
	playfxOnTag( getfx( "sentry_explode_mp" ), self, "tag_origin" );
	playfxOnTag( getfx( "sentry_smoke_mp" ), self, "tag_origin" );
	self playsound( "sentry_explode" );
	
	self notify( "death" );
	
	placement = self.origin;
	
	self.trigger MakeUnusable();

	wait(3);//timer for trophy to self delete
	
	if( IsDefined( self.trigger ) )
		self.trigger delete();

	if( IsDefined( self ) )
		self delete();
}


//	temporary location for late patching
//	TODO: move to its own file for next project
createKillTriggers()
{
	switch( level.script )
	{
		case "mp_dome":
		{
			createKillTrigger( (65.2303, 284.217, -307.954), 20, 64 );
			createKillTrigger( (550.941, 1778.53, -108.78), 120, 64 );
			break;
		}
		case "mp_hardhat":
		{
			createKillTrigger( (916.224, -1911.95, 332.625), 230, 64 );
			createKillTrigger( (78.2076, 800.055, 498.384), 120, 32 );			
			createKillTrigger( (165.7, -208.641, 408.544), 90, 64 );			
			createKillTrigger( (647.502, -619.168, 318.386 ), 70, 64 );
			createKillTrigger( (1353.14, 1379.13, 500.502 ), 100, 64 );
			break;
		}
		case "mp_paris":
		{
			createKillTrigger( (442.346, -895.006, 128.819), 14, 32 );
			createKillTrigger( (277.62, -972.828, 129.303), 32, 64 );
			createKillTrigger( (1717.79, 549.294, 144.871), 20, 32 );
			createKillTrigger( (130.734, 2027.64, 95.1856), 32, 64 );
			createKillTrigger( (-2077.26, 602.075, 646.415), 300, 64 );
			break;
		}
		case "mp_plaza2":
		{
			createKillTrigger( (-1355.79, -56.389, 952.179), 50, 32 );
			createKillTrigger( (-1354.92, 147.436, 914.707), 40, 32 );			
			createKillTrigger( (-266.038, 976.432, 761.29), 30, 32 );
			createKillTrigger( (189.786, -472.274, 738.957), 60, 40 );
			createKillTrigger( (652.957, -398.834, 687.308), 60, 40 );
			createKillTrigger( (480.709, -1961.1, 742.611), 110, 40 );
			createKillTrigger( (-990.873, -140.348, 905.785), 45, 64 );
			createKillTrigger( (-1215.71, -140.041, 905.785), 45, 64 );		
			createKillTrigger( (-485.723, 559.951, 801.125), 50, 64 );
			createKillTrigger( (-350.711, 559.951, 801.125), 50, 64 );					
			createKillTrigger( (369.49, 912.654, 798.966), 200, 64 );
			createKillTrigger( (-738.525, 1698.84, 796.122), 100, 200 );
			break;
		}
		case "mp_seatown":
		{
			createKillTrigger( (-1965.25, -862.286, 273.747), 100, 120 );
			createKillTrigger( (-583.448, 582.223, 375.4), 20, 64 ); 
			createKillTrigger( (-1400.83, 1367.31, 391.082), 200, 100 );
			break;
		}
		case "mp_lambeth":
		{
			createKillTrigger( (202.69, 1447.83, -85.4053), 100, 64 );			
			createKillTrigger( (1487.4, 1713.4, -141.171), 20, 120 ); 
			createKillTrigger( (1375.03, 2067.73, 3.36294), 20, 64 );
			createKillTrigger( (333.856, 2020.39, 14.2658), 32, 64 );
			break;
		}
		case "mp_alpha":
		{
			createKillTrigger( (-768, 1277.92, 162.01), 8, 40 );
			createKillTrigger( (-768, 1151.35, 162.01), 8, 40 );
			createKillTrigger( (-768, 1024.97, 162.01), 8, 40 );
			createKillTrigger( (-768, 896.526, 162.01), 8, 40 );
			createKillTrigger( (-115.306, -423.98, 188.944), 50, 72 ); 
			break;
		}
		case "mp_underground":
		{
			createKillTrigger( (975.678, 1727.09, -121.848), 20, 72 ); 
			createKillTrigger( (273.891, 1933.97, -97.8215), 12, 72 );
			createKillTrigger( (-44.8348, 1878.63, -108.455), 30, 64 );
			createKillTrigger( (-287.736, 3014.45, 60.6556), 300, 200 );
			break;
		}
		case "mp_bootleg":
		{
			createKillTrigger( (-1353.36, 33.4733, 49.2629), 60, 32 );			
			createKillTrigger( (-1360.71, -37.7305, 49.2629), 60, 32 );
			createKillTrigger( (-1553.97, -744.555, 113.469), 14, 64 );
			createKillTrigger( (52.7655, -257.007, -48.4873), 40, 64 );
			createKillTrigger( (-952.634, 1634.85, -68.327), 50, 64 );
			createKillTrigger( (-894.218, 1518.04, -68.327), 55, 64 );
			createKillTrigger( (44.5985, -1871.56, 226.461), 200, 64 );
			createKillTrigger( (-1476.79, -730.554, 87.178), 30, 64 );
			createKillTrigger( (-1336.19, 141.716, 61.0992), 70, 64 );
			break;
		}
		case "mp_radar":
		{
			createKillTrigger( (-4213.97, 2374.97, 1287.35), 120, 64 );
			createKillTrigger( (-4340.14, 3693.87, 1299.49), 120, 64 );
			createKillTrigger( (-4832.37, 4363.34, 1365.7), 120, 64 );
			createKillTrigger( (-3837.91, 1665.4, 1256), 68, 64 );
			createKillTrigger( (-3841.18, 1537.42, 1267.05), 68, 64 );
			createKillTrigger( (-6917.44, 4752.67, 1498.9), 200, 64 );
			createKillTrigger( (-5801.42, 3119.02, 1638.7), 300, 300 );
			break;
		}
		case "mp_mogadishu":
		{
			createKillTrigger( (-87.1578, 483.38, 152.515), 24, 64 ); 
			createKillTrigger( (-140.927, 129.438, 84.5235), 16, 64 );
			createKillTrigger( (1514.97, 2500.66, 171.984), 32, 32 );
			createKillTrigger( (238.065, 249.291, 75.904), 100, 64 ); 
			createKillTrigger( (564.572, 1132.1, 65.043), 12, 64 );
			createKillTrigger( (-32.8942, 297.377, 88.8334), 52, 64 );	
			createKillTrigger( (219.136, 1207.01, 121.441), 130, 64 );			
			createKillTrigger( (722.165, 1210.59, 73.5508), 150, 64 ); 
			createKillTrigger( (98.2886, -869.883, 138.138), 100, 64 );
			break;
		}
		case "mp_carbon":
		{
			createKillTrigger( (-1933.36, -4337.14, 3890.75), 14, 90 ); 
			createKillTrigger( (-2676.72, -3496.48, 3694.44), 14, 14 );
			createKillTrigger( (-3377.57, -4567.52, 3785.84), 40, 80 );
			break;
		}
		case "mp_bravo":
		{
			createKillTrigger( (878.518, -539.478, 1171.53), 14, 64 );
			createKillTrigger( (-1275.65, 984.295, 1394.08), 200, 64 );
			break;
		}
		case "mp_interchange":
		{
			createKillTrigger( (-712.089, 1183.13, 192.016), 100, 64 ); 			
			break;
		}
		case "mp_exchange":
		{
			createKillTrigger( (76.163, -1513.53, 265.376), 600, 64 );
			createKillTrigger( (-1078.77, -1040.27, 196.185), 250, 64 );
			createKillTrigger( (1705.31, 1012.04, 238.247), 40, 64 );
			createKillTrigger( (1706.24, 881.525, 238.247), 40, 64 );
			createKillTrigger( (918.001, -1387.3, 192.754), 40, 64 );
			createKillTrigger( (1039.45, -1420.39, 192.754), 40, 64 );
			createKillTrigger( (-270.995, -691.246, 184.239), 40, 64 );
			createKillTrigger( (-511.649, -1104.71, 169.967), 40, 64 );
			createKillTrigger( (-841.228, -522.82, 147.096), 50, 64 );
			createKillTrigger( (445.223, 1552.75, 234.433), 40, 64 );
			createKillTrigger( (261.291, 814.016, 204.573), 50, 64 );
			break;
		}
	}
}


createKillTrigger( center, radius, height )
{
	thread killTrigger( center, radius, height );
	
	//drawKillTrigger( center, radius, height );		
}

/*
drawKillTrigger( center, radius, height )
{
	circle_sides = 16;
	angleFrac = 360 / circle_sides;
	
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + xAdd;
		y = center[ 1 ] + yAdd;
		z = center[ 2 ];
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread common_scripts\_destructible::debug_circle_drawlines( circlepoints, 500.0, ( 1, 0, 0 ), center );			
	
	center = center + (0,0,height);
	circlepoints = [];
	for ( i = 0; i < circle_sides; i++ )
	{
		angle = ( angleFrac * i );
		xAdd = Cos( angle ) * radius;
		yAdd = Sin( angle ) * radius;
		x = center[ 0 ] + xAdd;
		y = center[ 1 ] + yAdd;
		z = center[ 2 ];
		circlepoints[ circlepoints.size ] = ( x, y, z );
	}
	thread common_scripts\_destructible::debug_circle_drawlines( circlepoints, 500.0, ( 1, 0, 0 ), center );	
}
*/