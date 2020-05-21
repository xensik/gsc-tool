//	Callback Setup
//	This script provides the hooks from code into script for the gametype callback functions.

//=============================================================================
// Code Callback functions

/*================
Called by code after the level's main script function has run.
================*/
CodeCallback_StartGameType()
{
	if( getDvar( "r_reflectionProbeGenerate" ) == "1" )
		level waittill( "eternity" );

	// If the gametype has not beed started, run the startup
	if(!isDefined(level.gametypestarted) || !level.gametypestarted)
	{
		[[level.callbackStartGameType]]();

		level.gametypestarted = true; // so we know that the gametype has been started up
	}
}


/*================
Called when a player begins connecting to the server.
Called again for every map change or tournement restart.

Return undefined if the client should be allowed, otherwise return
a string with the reason for denial.

Otherwise, the client will be sent the current gamestate
and will eventually get to ClientBegin.

firstTime will be qtrue the very first time a client connects
to the server machine, but qfalse on map changes and tournement
restarts.
================*/
CodeCallback_PlayerConnect()
{
	if( getDvar( "r_reflectionProbeGenerate" ) == "1" )
		level waittill( "eternity" );

	self endon("disconnect");
	[[level.callbackPlayerConnect]]();
}

/*================
Called when a player drops from the server.
Will not be called between levels.
self is the player that is disconnecting.
================*/
CodeCallback_PlayerDisconnect()
{
	self notify("disconnect");
	[[level.callbackPlayerDisconnect]]();
}

/*================
Called when a player has taken damage.
self is the player that took damage.
================*/
CodeCallback_PlayerDamage(eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, timeOffset)
{
	self endon("disconnect");
    [[level.callbackPlayerDamage]](eInflictor, eAttacker, iDamage, iDFlags, sMeansOfDeath, sWeapon, vPoint, vDir, sHitLoc, timeOffset);
}

/*================
Called when a player has been killed.
self is the player that was killed.
================*/
CodeCallback_PlayerKilled(eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, timeOffset, deathAnimDuration)
{
	self endon("disconnect");
	[[level.callbackPlayerKilled]](eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, timeOffset, deathAnimDuration);
}


/*================
Called when a vehicle has taken damage.
self is the vehicle that took damage.
================*/
CodeCallback_VehicleDamage( inflictor, attacker, damage, dFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	if ( isDefined( self.damageCallback ) )
		self [[self.damageCallback]]( inflictor, attacker, damage, dFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName );
	else
		self Vehicle_FinishDamage( inflictor, attacker, damage, dFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName );
}


/*================
Called when code is forcibly ending the game.
e.g. we suck as host.
================*/
CodeCallback_CodeEndGame()
{
	self endon("disconnect");
	[[level.callbackCodeEndGame]]();
}


/*================
Called when a player has been killed, but has last stand perk.
self is the player that was killed.
================*/
CodeCallback_PlayerLastStand(eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, timeOffset, deathAnimDuration )
{
	self endon("disconnect");
	[[level.callbackPlayerLastStand]](eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, vDir, sHitLoc, timeOffset, deathAnimDuration );
}


/*================
Called when a player reconnects to the server
following a host migration.
================*/
CodeCallback_PlayerMigrated()
{
	self endon("disconnect");
	[[level.callbackPlayerMigrated]]();
}


/*================
Called once when a host migration has occured.
================*/
CodeCallback_HostMigration()
{
	[[level.callbackHostMigration]]();
}



//=============================================================================

// Damage flags used in the playerDamage callback
SetupDamageFlags()
{
	// code-defined:
	level.iDFLAGS_RADIUS						= 1;	// damage was indirect
	level.iDFLAGS_NO_ARMOR						= 2;	// armor does not protect from this damage
	level.iDFLAGS_NO_KNOCKBACK					= 4;	// do not affect velocity, just view angles
	level.iDFLAGS_PENETRATION					= 8;	// damage occurred after one or more penetrations
	level.iDFLAGS_STUN							= 16;	// non-lethal
	level.iDFLAGS_SHIELD_EXPLOSIVE_IMPACT		= 32;	// missile impacted on the front of the victim's shield
	level.iDFLAGS_SHIELD_EXPLOSIVE_IMPACT_HUGE	= 64;	//   ...and was from a projectile with "Big Explosion" checked on.
	level.iDFLAGS_SHIELD_EXPLOSIVE_SPLASH		= 128;	// explosive splash, somewhat deflected by the victim's shield

	// script-defined:
	level.iDFLAGS_NO_TEAM_PROTECTION			= 256;
	level.iDFLAGS_NO_PROTECTION					= 512;
	level.iDFLAGS_PASSTHRU						= 1024;
}


/*================
Setup any misc callbacks stuff like defines and default callbacks
================*/
SetupCallbacks()
{
	SetDefaultCallbacks();
	SetupDamageFlags();
}


/*================
Called from the gametype script to store off the default callback functions.
This allows the callbacks to be overridden by level script, but not lost.
================*/
SetDefaultCallbacks()
{
	level.callbackStartGameType = maps\mp\gametypes\_gamelogic::Callback_StartGameType;
	level.callbackPlayerConnect = maps\mp\gametypes\_playerlogic::Callback_PlayerConnect;
	level.callbackPlayerDisconnect = maps\mp\gametypes\_playerlogic::Callback_PlayerDisconnect;
	level.callbackPlayerDamage = maps\mp\gametypes\_damage::Callback_PlayerDamage;
	level.callbackPlayerKilled = maps\mp\gametypes\_damage::Callback_PlayerKilled;
	level.callbackCodeEndGame = maps\mp\gametypes\_gamelogic::Callback_CodeEndGame;
	level.callbackPlayerLastStand = maps\mp\gametypes\_damage::Callback_PlayerLastStand;
	level.callbackPlayerMigrated = maps\mp\gametypes\_playerlogic::Callback_PlayerMigrated;
	level.callbackHostMigration = maps\mp\gametypes\_hostmigration::Callback_HostMigration;
}


/*================
Called when a gametype is not supported.
================*/
AbortLevel()
{
	println("Aborting level - gametype is not supported");

	level.callbackStartGameType = ::callbackVoid;
	level.callbackPlayerConnect = ::callbackVoid;
	level.callbackPlayerDisconnect = ::callbackVoid;
	level.callbackPlayerDamage = ::callbackVoid;
	level.callbackPlayerKilled = ::callbackVoid;
	level.callbackCodeEndGame = ::callbackVoid;
	level.callbackPlayerLastStand = ::callbackVoid;
	level.callbackPlayerMigrated = ::callbackVoid;
	level.callbackHostMigration = ::callbackVoid;

	setdvar("g_gametype", "dm");

	exitLevel(false);
}


/*================
================*/
callbackVoid()
{
}
