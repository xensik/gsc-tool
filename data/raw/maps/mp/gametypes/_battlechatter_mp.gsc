#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

init()
{
	level.isTeamSpeaking["allies"] = false;
	level.isTeamSpeaking["axis"] = false;
	
	level.speakers["allies"] = [];
	level.speakers["axis"] = [];
	
	level.bcSounds = [];
	level.bcSounds["reload"] = "inform_reloading_generic";
	level.bcSounds["frag_out"] = "inform_attack_grenade";
	level.bcSounds["flash_out"] = "inform_attack_flashbang";
	level.bcSounds["smoke_out"] = "inform_attack_smoke";
	level.bcSounds["conc_out"] = "inform_attack_stun";
	level.bcSounds["c4_plant"] = "inform_attack_thwc4";
	level.bcSounds["claymore_plant"] = "inform_plant_claymore";
	level.bcSounds["semtex_out"] = "semtex_use";
	level.bcSounds["kill"] = "inform_killfirm_infantry";
	level.bcSounds["casualty"] = "inform_casualty_generic";
	level.bcSounds["suppressing_fire"] = "cmd_suppressfire";
	
	level.bcSounds["semtex_incoming"] = "semtex_incoming";
	level.bcSounds["c4_incoming"] = "c4_incoming";
	level.bcSounds["flash_incoming"] = "flash_incoming";
	level.bcSounds["stun_incoming"] = "stun_incoming";
	level.bcSounds["grenade_incoming"] = "grenade_incoming";
	level.bcSounds["rpg_incoming"] = "rpg_incoming";
	
	level thread onPlayerConnect();
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill ( "connected", player );
		
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon( "disconnect" );

	for(;;)
	{
		self waittill( "spawned_player" );
		
		factionPrefix = maps\mp\gametypes\_teams::getTeamVoicePrefix( self.team );
		
		if ( !isDefined( self.pers["voiceIndex"] ) || factionPrefix != "RU_" && self.pers["voiceNum"] >= 3 )
		{
			if ( factionPrefix == "RU_" )
				self.pers["voiceNum"] = RandomIntRange( 0, 4 );
			else
				self.pers["voiceNum"] = RandomIntRange( 0, 2);
				
			self.pers["voicePrefix"] = factionPrefix + self.pers["voiceNum"] + "_";
		}
		
		// help players be stealthy in splitscreen by not announcing their intentions
		if ( level.splitscreen )
			continue;
			
		self thread claymoreTracking();
		self thread reloadTracking();
		self thread grenadeTracking();
		self thread grenadeProximityTracking();
		self thread suppressingFireTracking();
	}
}

/*Unreliable code notify
grenadeProximityTracking()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	for ( ;; )
	{
		self waittill( "grenade danger", grenade );
		println( "GrenadeDanger" );
		if ( SightTracePassed( grenade.origin, self.origin, false, self ) )
		{
			println( "GRENAAAADE!!!" );
			if ( cointoss() )
				continue;
			else if( grenade.model == "projectile_semtex_grenade" )
				level thread sayLocalSound( self, "semtex_incoming" );
			else
				level thread sayLocalSound( self, "grenade_incoming" );
		}
	}
}
*/

grenadeProximityTracking()
{
	self endon( "disconnect" );
	self endon ( "death" );
	
	position = self.origin;
	
	for( ;; )
	{
		if ( !isDefined( level.grenades ) || level.grenades.size < 1 || !isReallyAlive(self) )
		{
			wait( .05 );
			continue;
		}
		
		grenades = combineArrays ( level.grenades, level.missiles );
		
		foreach ( grenade in grenades )
		{
			wait( .05 );
			
			if ( !isDefined(grenade) )
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
			
			if ( isDefined( grenade.owner ) && level.teamBased && grenade.owner.team == self.team )
				continue;
			
			grenadeDistanceSquared = DistanceSquared( grenade.origin, self.origin );
			
			if ( grenadeDistanceSquared < 147456 )
			{
				if ( BulletTracePassed( grenade.origin, self.origin, false, self ) )
				{
					if ( cointoss() )
					{
						continue;
						wait 5;
					}
					else if( grenade.model == "projectile_concussion_grenade" )
					{
						level thread sayLocalSound( self, "stun_incoming" );
						wait 5;
					}
					else if( grenade.model == "projectile_m84_flashbang_grenade" )
					{
						level thread sayLocalSound( self, "flash_incoming" );
						wait 5;
					}
					else if( grenade.model == "projectile_rocket" )
					{
						level thread sayLocalSound( self, "rpg_incoming" );
						wait 5;
					}
					else if( grenade.model == "weapon_c4" )
					{
						level thread sayLocalSound( self, "c4_incoming" );
						wait 5;
					}
					else if( grenade.model == "projectile_m203grenade" )
					{
						level thread sayLocalSound( self, "rpg_incoming" );
						wait 5;
					}
					else if( grenade.model == "projectile_semtex_grenade" )
					{
						level thread sayLocalSound( self, "semtex_incoming" );
						wait 5;
					}
					else
					{
						println( "Grenade Incoming played" );
						level thread sayLocalSound( self, "grenade_incoming" );
						wait 5;
					}
				}
			}	
		}	
	}
	
}

suppressingFireTracking()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	timeStartFired = undefined;
	
	for( ;; )
	{
		self waittill( "begin_firing" );
		
		self thread suppressWaiter();
		
		self waittill( "end_firing" );
		self notify( "stoppedFiring" );
	}
	
}


suppressWaiter()
{
	self notify( "suppressWaiter" );
	self endon ( "suppressWaiter" );
	
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "stoppedFiring" );
	
	wait( 2 );
	level thread sayLocalSound( self, "suppressing_fire" );
}


claymoreTracking()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	
	while(1)
	{
		self waittill( "begin_firing" );
		weaponName = self getCurrentWeapon();
		if ( weaponName == "claymore_mp" )
			level thread sayLocalSound( self, "claymore_plant" );
	}
}


reloadTracking()
{
	self endon ( "death" );
	self endon ( "disconnect" );

	for( ;; )
	{
		self waittill ( "reload_start" );
		level thread sayLocalSound( self, "reload" );
	}
}


grenadeTracking()
{
	self endon ( "death" );
	self endon ( "disconnect" );

	for( ;; )
	{
		self waittill ( "grenade_fire", grenade, weaponName );
		
		if ( weaponName == "frag_grenade_mp" )
			level thread sayLocalSound( self, "frag_out" );
		else if ( weaponName == "semtex_mp" )
			level thread sayLocalSound( self, "semtex_out" );
		else if ( weaponName == "flash_grenade_mp" )
			level thread sayLocalSound( self, "flash_out" );
		else if ( weaponName == "concussion_grenade_mp" )
			level thread sayLocalSound( self, "conc_out" );
		else if ( weaponName == "smoke_grenade_mp" )
			level thread sayLocalSound( self, "smoke_out" );
		else if ( weaponName == "c4_mp" )
			level thread sayLocalSound( self, "c4_plant" );
	}
}


sayLocalSoundDelayed( player, soundType, delay )
{
	player endon ( "death" );
	player endon ( "disconnect" );
	
	wait ( delay );
	
	sayLocalSound( player, soundType );
}


sayLocalSound( player, soundType )
{
	player endon ( "death" );
	player endon ( "disconnect" );

	if ( isSpeakerInRange( player ) )
		return;
		
	if( player.team != "spectator" )
	{	
		prefix = player.pers["voicePrefix"];
		
		soundAlias = prefix + level.bcSounds[soundType];
		player thread doSound( soundAlias );
	}
}


doSound( soundAlias )
{
	/#
	//println( "SOUND PLAYED: " + soundAlias );
	#/
	
	team = self.pers["team"];
	level addSpeaker( self, team );
	self playSoundToTeam( soundAlias, team, self );
	self thread timeHack( soundAlias ); // workaround because soundalias notify isn't happening
	self waittill_any( soundAlias, "death", "disconnect" );
	level removeSpeaker( self, team );
}


timeHack( soundAlias )
{
	self endon ( "death" );
	self endon ( "disconnect" );

	wait ( 2.0 );
	self notify ( soundAlias );
}


isSpeakerInRange( player )
{
	player endon ( "death" );
	player endon ( "disconnect" );

	distSq = 1000 * 1000;

	// to prevent player switch to spectator after throwing a granade causing damage to someone and result in attacker.pers["team"] = "spectator"
	if( isdefined( player ) && isdefined( player.pers["team"] ) && player.pers["team"] != "spectator" )
	{
		for ( index = 0; index < level.speakers[player.pers["team"]].size; index++ )
		{
			teammate = level.speakers[player.pers["team"]][index];
			if ( teammate == player )
				return true;
				
			if ( distancesquared( teammate.origin, player.origin ) < distSq )
				return true;
		}
	}

	return false;
}


addSpeaker( player, team )
{
	level.speakers[team][level.speakers[team].size] = player;
}


// this is lazy... fix up later by tracking ID's and doing array slot swapping
removeSpeaker( player, team )
{
	newSpeakers = [];
	for ( index = 0; index < level.speakers[team].size; index++ )
	{
		if ( level.speakers[team][index] == player )
			continue;
			
		newSpeakers[newSpeakers.size] = level.speakers[team][index]; 
	}
	
	level.speakers[team] = newSpeakers;
}
