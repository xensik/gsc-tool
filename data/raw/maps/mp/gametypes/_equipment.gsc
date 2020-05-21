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
			trophy thread maps\mp\gametypes\_weapons::createBombSquadModel( "mp_trophy_system", "tag_origin", level.otherTeam[self.team], self );
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
		
		// give item to user
		owner givePerk( "trophy_mp", false );
		owner.trophyRemainingAmmo = self.ammo;
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
	RadiusDamage( projPosition, 128, 105, 10, self );
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
