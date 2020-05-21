#include common_scripts\utility;
#include maps\mp\_utility;
#include common_scripts\_createFxMenu;
#include common_scripts\_createfx;
#include common_scripts\_fx;

createfx()
{
	level.func_position_player = ::void;
	level.func_position_player_get = ::func_position_player_get;
	level.func_loopfxthread = ::loopfxthread;
	level.func_oneshotfxthread = ::oneshotfxthread;
	level.func_create_loopsound = ::create_loopsound;
//	level.func_exploder_preload = ::exploder_before_load;;
//	level.func_exploder_postload = ::exploder_after_load;;
	level.func_updatefx = ::restart_fx_looper;
	level.func_process_fx_rotater = ::process_fx_rotater;

	level.mp_createfx = true;

	// MP only stuff
	level.callbackStartGameType = ::void;
	level.callbackPlayerConnect = ::void;
	level.callbackPlayerDisconnect = ::void;
	level.callbackPlayerDamage = ::void;
	level.callbackPlayerKilled = ::void;
	level.callbackCodeEndGame = ::void;
	level.callbackPlayerLastStand = ::void;
	level.callbackPlayerConnect = ::Callback_PlayerConnect;
	level.callbackPlayerMigrated = ::void;

	//wait(5);

	thread func_get_level_fx(); // start gettin these on start
	createfx_common();

	level waittill( "eternity" );
}

func_position_player_get( lastPlayerOrigin )
{
	return level.player.origin;
}

Callback_PlayerConnect()
{
	self waittill( "begin" );

	if ( !isdefined( level.player ) )
	{
		spawnpoints = getentarray( "mp_global_intermission", "classname" );
		self spawn( spawnpoints[0].origin, spawnpoints[0].angles );
		self maps\mp\gametypes\_playerlogic::updateSessionState( "playing", "" );
		self.maxhealth = 10000000;
		self.health = 10000000;
		level.player = self;
		
		thread createFxLogic();
		thread ufo_mode();
	}
	else
		kick( self GetEntityNumber() );
}

ufo_mode()
{
	level.player openpopupmenu( "painter_mp" );// painter.menu execs some console commands( ufo mode ).. sneaky hacks.
	level.player closepopupmenu( "painter_mp" );
}
