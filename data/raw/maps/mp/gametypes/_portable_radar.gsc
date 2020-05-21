#include maps\mp\_utility;
#include common_scripts\utility;

setPortableRadar()
{
	self SetOffhandSecondaryClass( "flash" );
	self _giveWeapon( "portable_radar_mp", 0 );
	self giveStartAmmo( "portable_radar_mp" );
	
	self thread monitorPortableRadarUse();
}

unsetPortableRadar()
{
	self notify( "end_monitorPortableRadarUse" );
}

deletePortableRadar( portable_radar )
{
	if ( !isDefined( portable_radar ) )
		return;
	
	foreach( player in level.players )
	{
		if( IsDefined( player ) )
			player.inPlayerPortableRadar = undefined;
	}

	portable_radar notify( "death" );
	portable_radar Delete();
	
	self.deployedPortableRadar = undefined;
}

monitorPortableRadarUse()
{
	self notify ( "end_monitorPortableRadarUse" );
	self endon ( "end_monitorPortableRadarUse" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		// grenade is the entity spawned by the G_FireGrenade() since we want this to be
		// script controlled, we won't actually use this entity
		self waittill( "grenade_fire", grenade, weapName );
		if ( weapname == "portabl_radar" || weapname == "portable_radar_mp" )
		{
			if( !IsAlive( self ) )
			{
				grenade delete();
				return;
			}

			if( isDefined( self.deployedPortableRadar ) )
				deletePortableRadar( self.deployedPortableRadar );

			grenade waittill( "missile_stuck" );

			GroundPosition = grenade.origin;

			if( IsDefined( grenade ) )
				grenade Delete();

			portable_radar = spawn( "script_model", GroundPosition );
			portable_radar.health = 100;
			portable_radar.team = self.team;
			portable_radar.owner = self;

			portable_radar setCanDamage( true );

			portable_radar makePortableRadar( self );
			portable_radar portableRadarSetup( self );
			portable_radar thread maps\mp\gametypes\_weapons::createBombSquadModel( "weapon_radar", "tag_origin", level.otherTeam[self.team], self );
			portable_radar thread portableRadarProximityTracker();

			self.deployedPortableRadar = portable_radar;
		}
	}
}

portableRadarSetup( owner )
{
	// JCC temp until we get our model
	self setModel( "weapon_radar" );
	
	// setup icons for item so friendlies see it
	if ( level.teamBased )
		self maps\mp\_entityheadIcons::setTeamHeadIcon( self.team , (0,0,20) );
	else
		self maps\mp\_entityheadicons::setPlayerHeadIcon( owner, (0,0,20) );

	self thread portableRadarDamageListener( owner );
	self thread portableRadarUseListener( owner );
	owner thread portableRadarWatchOwner( self );
	self thread portableRadarBeepSounds();
	self thread notUsableForJoiningPlayers( owner );
}

portableRadarWatchOwner( portable_radar )
{
	portable_radar endon( "death" );
	level endon ( "game_ended" );
	
	self waittill_any( "disconnect", "joined_team", "joined_spectators", "death" );
	
	level thread deletePortableRadar( portable_radar );
}

portableRadarBeepSounds()
{
	self endon( "death" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		wait ( 2.0 );
		self playSound( "sentry_gun_beep" );
	}
}

portableRadarDamageListener( owner )
{
	self endon ( "death" );
	
	// use a health buffer to prevent dying to friendly fire
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 100; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, iDFlags, weapon );

		// don't allow people to destroy equipment on their team if FF is off
		if ( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
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

		self.damageTaken += damage;
		
		if ( isDefined(weapon) && weapon == "emp_grenade_mp" )
		{
			self.damageTaken = self.maxhealth + 1;
		}

		if( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "portable_radar" );
		}

		if ( self.damageTaken >= self.maxHealth )
		{
			if ( isDefined( owner ) && attacker != owner )
			{
				// JCC commented out
				//attacker notify ( "destroyed_insertion", owner );
				attacker notify( "destroyed_explosive" ); // count towards SitRep Pro challenge
				
				// JCC commented out
				//owner thread leaderDialogOnPlayer( "ti_destroyed" );
			}
			
			// TODO: get sound and fx
			self playsound( "sentry_explode" );
			self.deathEffect = PlayFX( getfx( "equipment_explode" ), self.origin );
			attacker thread deletePortableRadar( self );
		}
	}
}

portableRadarUseListener( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	
	self setCursorHint( "HINT_NOICON" );
	self setHintString( &"MP_PICKUP_PORTABLE_RADAR" );
	self setSelfUsable( owner );

	for ( ;; )
	{
		self waittill ( "trigger", player );
		
		player playLocalSound( "scavenger_pack_pickup" );
		
		// give item to user (only if they haven't restocked from scavenger pickup since dropping)		
		if ( player getAmmoCount( "portable_radar_mp" ) == 0 )
			player setPortableRadar();
	
		player thread deletePortableRadar( self );
	}
}

portableRadarProximityTracker() // self == portable radar
{
	self endon( "death" );
	level endon( "game_ended" );

	portableRadarProximity = 512;

/#
	//maps\mp\killstreaks\_ac130::debug_circle( self.origin, portableRadarProximity, 5, ( 0, 0, 1 ) );
#/

	while( true )
	{
		foreach( player in level.players )
		{
			if( !IsDefined( player ) )
				continue;

			if( level.teambased && player.team == self.team )
				continue;

			proxDistance = DistanceSquared( self.origin, player.origin );

			if( DistanceSquared( player.origin, self.origin ) < portableRadarProximity * portableRadarProximity )
				player.inPlayerPortableRadar = self.owner;
			else
				player.inPlayerPortableRadar = undefined;
		}
	
		wait (0.05);
	}
}