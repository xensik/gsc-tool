#include maps\mp\_utility;
#include common_scripts\utility;

setScrambler()
{
	self SetOffhandSecondaryClass( "flash" );
	self _giveWeapon( "scrambler_mp", 0 );
	self giveStartAmmo( "scrambler_mp" );
	
	self thread monitorScramblerUse();
}

unsetScrambler()
{
	self notify( "end_monitorScramblerUse" );
}

deleteScrambler( scrambler )
{
	if ( !isDefined( scrambler ) )
		return;
	
	foreach( player in level.players )
	{
		if( IsDefined( player ) )
			player.inPlayerScrambler = undefined;
	}

	scrambler notify( "death" );
	scrambler Delete();
	
	self.deployedScrambler = undefined;
	tempArray = [];
	
	tempArray = cleanArray( level.scramblers );
	level.scramblers = tempArray;
	
}

monitorScramblerUse()
{
	self notify ( "end_monitorScramblerUse" );
	self endon ( "end_monitorScramblerUse" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		// grenade is the entity spawned by the G_FireGrenade() since we want this to be
		// script controlled, we won't actually use this entity
		self waittill( "grenade_fire", grenade, weapName );
		if ( weapname == "scrambler" || weapname == "scrambler_mp" )
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
					self SetWeaponAmmoStock( "scrambler_mp", self GetWeaponAmmoStock( "trophy_mp" ) + 1 );
					continue;
				}
				
				grenade.origin = secTrace["position"];
			}
			
			grenade Show();

			if( isDefined( self.deployedScrambler ) )
				deleteScrambler( self.deployedScrambler );

			GroundPosition = grenade.origin;

			scrambler = spawn( "script_model", GroundPosition );
			scrambler.health = 100;
			scrambler.team = self.team;
			scrambler.owner = self;

			scrambler setCanDamage( true );

			scrambler makeScrambler( self );
			scrambler scramblerSetup( self );
			scrambler thread maps\mp\gametypes\_weapons::createBombSquadModel( "weapon_jammer", "tag_origin", level.otherTeam[self.team], self );
			
			level.scramblers[ level.scramblers.size ] = scrambler;
			self.deployedScrambler = scrambler;

			// need to clear the changing weapon because it'll get stuck on c4_mp and player will stop spawning because we get locked in isChangingWeapon() loop when a killstreak is earned
			self.changingWeapon = undefined;

			wait(0.05); // allows for the plant sound to play
			if( IsDefined( grenade ) )
				grenade Delete();
		}
	}
}

scramblerSetup( owner )
{
	// JCC temp until we get our model
	self setModel( "weapon_jammer" );
	
	// setup icons for item so friendlies see it
	if ( level.teamBased )
		self maps\mp\_entityheadIcons::setTeamHeadIcon( self.team , (0,0,20) );
	else
		self maps\mp\_entityheadicons::setPlayerHeadIcon( owner, (0,0,20) );

	self thread scramblerDamageListener( owner );
	self thread scramblerUseListener( owner );
	owner thread scramblerWatchOwner( self );
	self thread scramblerBeepSounds();
	self thread notUsableForJoiningPlayers( owner );
}

scramblerWatchOwner( scrambler )
{
	scrambler endon( "death" );
	level endon ( "game_ended" );
	
	self waittill_any( "disconnect", "joined_team", "joined_spectators", "death" );
	
	level thread deleteScrambler( scrambler );
}

scramblerBeepSounds()
{
	self endon( "death" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		wait ( 3.0 );
		self playSound( "scrambler_beep" );
	}
}

scramblerDamageListener( owner )
{
	self endon ( "death" );
	
	// use a health buffer to prevent dying to friendly fire
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 100; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	for ( ;; )
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

		if( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "scrambler" );
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
			attacker thread deleteScrambler( self );
		}
	}
}

scramblerUseListener( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	
	self setCursorHint( "HINT_NOICON" );
	self setHintString( &"MP_PICKUP_SCRAMBLER" );
	self setSelfUsable( owner );

	for ( ;; )
	{
		self waittill ( "trigger", player );
		
		player playLocalSound( "scavenger_pack_pickup" );
		
		// give item to user (only if they haven't restocked from scavenger pickup since dropping)		
		if ( player getAmmoCount( "scrambler_mp" ) == 0 )
			player setScrambler();
	
		player thread deleteScrambler( self );
	}
}

// called from _perks::onPlayerSpawned()
scramblerProximityTracker() // self == spawned player
{
	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );

	self.scramProxyActive = false;

	scramblerProximity = 512;

	for( ;; )
	{
		wait (0.05);

		self.scramProxyActive = false;
		foreach( scrambler in level.scramblers )
		{
			if ( !isDefined( scrambler ) )
				continue;

			if ( !isReallyAlive(self) )
				continue;

/#
			//maps\mp\killstreaks\_ac130::debug_circle( scrambler.origin, scramblerProximity, 0.05, ( 0, 0, 1 ) );
#/

			scramDistance = DistanceSquared( scrambler.origin, self.origin );

			if( ( level.teambased && scrambler.team != self.team ) ||
				( !level.teambased && IsDefined( scrambler.owner ) && scrambler.owner != self ) )
			{
				// this player is not on the same team but we still need to know if they are within the proximity
				if ( scramDistance < scramblerProximity * scramblerProximity )
					self.inPlayerScrambler = scrambler.owner;
				else
					self.inPlayerScrambler = undefined;

				// continue because everything below here is for teammates/owner
				continue;
			}

			if( scramDistance < scramblerProximity * scramblerProximity )
			{
				self.scramProxyActive = true;
				break;
			}
		}

		if ( self.scramProxyActive )
		{
			if( !self _hasPerk("specialty_blindeye" ) )
			{
				self givePerk( "specialty_blindeye", false );
				self.scramProxyPerk = true;
			}
		}
		else 
		{
			// did we get the perk from the scram proxy
			if( IsDefined( self.scramProxyPerk ) && self.scramProxyPerk )
			{
				// now make sure they didn't earn it using the specialist strike package
				if( !self maps\mp\killstreaks\_perkstreaks::isPerkStreakOn( "specialty_blindeye_ks" ) )
					self _unsetPerk( "specialty_blindeye" );

				self.scramProxyPerk = false;
			}
		}
	}

}

