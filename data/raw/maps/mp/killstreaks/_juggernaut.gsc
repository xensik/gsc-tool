#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

init()
{
	level.juggSettings = [];

	level.juggSettings[ "juggernaut" ] = spawnStruct();
	level.juggSettings[ "juggernaut" ].splashUsedName =			"used_juggernaut";
	level.juggSettings[ "juggernaut" ].overlay =				"goggles_overlay";

	level.juggSettings[ "juggernaut_recon" ] = spawnStruct();
	level.juggSettings[ "juggernaut_recon" ].splashUsedName =	"used_juggernaut";
	level.juggSettings[ "juggernaut_recon" ].overlay =			"goggles_overlay";

	level.juggSettings[ "tjugg_juggernaut" ] = spawnStruct();
	level.juggSettings[ "tjugg_juggernaut" ].splashUsedName =	"callout_new_juggernaut";
	level.juggSettings[ "tjugg_juggernaut" ].overlay =			"goggles_overlay";

	level.juggSettings[ "jugg_juggernaut" ] = spawnStruct();
	level.juggSettings[ "jugg_juggernaut" ].splashUsedName =	"callout_new_juggernaut";
	level.juggSettings[ "jugg_juggernaut" ].overlay =			"goggles_overlay";

	foreach( jugg in level.juggSettings )
	{
		PreCacheShader( jugg.overlay );
	}
}

giveJuggernaut( juggType ) // self == player
{
	self endon( "death" );
	self endon( "disconnect" );

	// added this wait here because i think the disabling the weapons and re-enabling while getting the crate, 
	//	needs a little time or else we sometimes won't have a weapon in front of us after we get juggernaut
	wait(0.05); 

	//	remove light armor if equipped
	if ( isDefined( self.hasLightArmor ) && self.hasLightArmor == true )
		maps\mp\perks\_perkfunctions::removeLightArmor( self.previousMaxHealth );	

	//	remove explosive bullets if equipped
	if ( self _hasPerk( "specialty_explosivebullets" ) )
		self _unsetPerk( "specialty_explosivebullets" );

	//	not always on radar
	createObjectiveIcon = true;

	switch( juggType )
	{
	case "juggernaut":
		self.isJuggernaut = true;
		self maps\mp\gametypes\_class::giveLoadout( self.pers["team"], juggType, false, false );
		self.moveSpeedScaler = .65;
		break;
	case "juggernaut_recon":
		self.isJuggernautRecon = true;
		self maps\mp\gametypes\_class::giveLoadout( self.pers["team"], juggType, false, false );
		self.moveSpeedScaler = .75;	

		portable_radar = spawn( "script_model", self.origin );
		portable_radar.team = self.team;

		portable_radar makePortableRadar( self );
		self.personalRadar = portable_radar;

		self thread radarMover( portable_radar );
		break;
	case "tjugg_juggernaut":
		self.isJuggernaut = true;
		self maps\mp\gametypes\_class::giveLoadout( self.pers["team"], "gamemode", false, false );
		self.moveSpeedScaler = 0.7;	

		portable_radar = spawn( "script_model", self.origin );
		portable_radar.team = self.team;

		portable_radar makePortableRadar( self );
		self.personalRadar = portable_radar;

		self thread radarMover( portable_radar );			
		break;
	case "jugg_juggernaut":
		self.isJuggernaut = true;
		self maps\mp\gametypes\_class::giveLoadout( self.pers["team"], "gamemode", false, false );
		self.moveSpeedScaler = 0.7;
		if ( !level.matchRules_showJuggRadarIcon )
			createObjectiveIcon = false;
		break;
	}

	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();

	self disableWeaponPickup();

	if ( !getDvarInt( "camera_thirdPerson" ) )
	{
		self.juggernautOverlay = newClientHudElem( self );
		self.juggernautOverlay.x = 0;
		self.juggernautOverlay.y = 0;
		self.juggernautOverlay.alignX = "left";
		self.juggernautOverlay.alignY = "top";
		self.juggernautOverlay.horzAlign = "fullscreen";
		self.juggernautOverlay.vertAlign = "fullscreen";
		self.juggernautOverlay SetShader( level.juggSettings[ juggType ].overlay, 640, 480 );
		self.juggernautOverlay.sort = -10;
		self.juggernautOverlay.archived = true;
		self.juggernautOverlay.hidein3rdperson = true;
	}

	self thread juggernautSounds();

	self setPerk( "specialty_radarjuggernaut", true, false );

	self thread teamPlayerCardSplash( level.juggSettings[ juggType ].splashUsedName, self );	
	self PlaySoundToTeam( game[ "voice" ][ self.team ] + "use_juggernaut", self.team, self );
	self PlaySoundToTeam( game[ "voice" ][ level.otherTeam[ self.team ] ] + "enemy_juggernaut", level.otherTeam[ self.team ] );

	// if we are using the specialist strike package then we need to clear it, or else players will think they have the perks while jugg
	if( self.streakType == "specialist" )
	{
		self thread maps\mp\killstreaks\_killstreaks::clearKillstreaks();
	}
	//	- giveLoadout() nukes action slot 4 (killstreak weapon)
	//	- it's usually restored after activating a killstreak but 
	//	  equipping juggernaut out of a box isn't part of killstreak activation flow
	//	- restore action slot 4 by re-updating killstreaks
	else
	{
		self thread maps\mp\killstreaks\_killstreaks::updateKillstreaks( true );
	}

	self thread juggRemover();

	//	- model change happens at the end of giveLoadout(), removing any attached models
	//	- re-apply flag if we were carrying one
	if ( isDefined( self.carryFlag ) )
	{
		wait( 0.05 );
		self attach( self.carryFlag, "J_spine4", true );
	}

	level notify( "juggernaut_equipped", self );

	self maps\mp\_matchdata::logKillstreakEvent( "juggernaut", self.origin );
}

juggernautSounds()
{
	level endon ( "game_ended" );
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "jugg_removed" );

	for ( ;; )
	{
		wait ( 3.0 );
		self playSound( "juggernaut_breathing_sound" );
	}
}

radarMover( portableRadar )
{
	level endon("game_ended");
	self endon( "disconnect" );
	self endon( "jugg_removed" );
	self endon( "jugdar_removed" );

	for( ;; )
	{
		portableRadar MoveTo( self.origin, .05 );
		wait (0.05);
	}
}


juggRemover()
{
	level endon("game_ended");
	self endon( "disconnect" );
	self endon( "jugg_removed" );

	self thread juggRemoveOnGameEnded();
	self waittill_any( "death", "joined_team", "joined_spectators", "lost_juggernaut" );

	self enableWeaponPickup();
	self.isJuggernaut = false;
	self.isJuggernautDef = false;
	self.isJuggernautGL = false;
	self.isJuggernautRecon = false;
	if ( isDefined( self.juggernautOverlay ) )
		self.juggernautOverlay destroy();

	self unsetPerk( "specialty_radarjuggernaut", true );

	if ( isDefined( self.personalRadar ) )
	{
		self notify( "jugdar_removed" );
		level maps\mp\gametypes\_portable_radar::deletePortableRadar( self.personalRadar );
		self.personalRadar = undefined;	
	}

	self notify( "jugg_removed" );
}

juggRemoveOnGameEnded()
{
	self endon( "disconnect" );
	self endon( "jugg_removed" );

	level waittill( "game_ended" );

	if( IsDefined( self.juggernautOverlay ) )
		self.juggernautOverlay destroy();
}