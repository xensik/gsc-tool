// Utility rain functions:
#include maps\_utility;
#include common_scripts\utility;

/*
=============
///ScriptDocBegin
"Name: rainHard( <transition> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rainHard( transition )
{
	println( "Rain becomes Hard over " + transition + " seconds" );
	level notify( "rain_change", "hard", transition );
	level thread rainEffectChange( 10, transition );
	wait( transition * 0.5 );
	level.ambient_modifier[ "rain" ] = "";
	//	This is commented out until ambient weather sounds are added to the tree
	//maps\_ambient::activateAmbient( level.ambient );
	wait( transition * 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: rainMedium()"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rainMedium( transition )
{
	println( "Rain becomes Medium over " + transition + " seconds" );
	level notify( "rain_change", "hard", transition );
	level thread rainEffectChange( 8, transition );
	wait( transition * 0.5 );
	level.ambient_modifier[ "rain" ] = "";
	//	This is commented out until ambient weather sounds are added to the tree
	//maps\_ambient::activateAmbient( level.ambient );
	wait( transition * 0.5 );	
}

/*
=============
///ScriptDocBegin
"Name: rainLight( <transition> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rainLight( transition )
{
	println( "Rain becomes Light over " + transition + " seconds" );
	level notify( "rain_change", "light", transition );
	level thread rainEffectChange( 5, transition );
	wait( transition * 0.5 );
	level.ambient_modifier[ "rain" ] = "light";
	//	This is commented out until ambient weather sounds are added to the tree
	//maps\_ambient::activateAmbient( level.ambient );
	wait( transition * 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: rainNone( <transition> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rainNone( transition )
{
	println( "Rain fades out over " + transition + " seconds" );
	level notify( "rain_change", "none", transition );
	level thread rainEffectChange( 0, transition );
	wait( transition * 0.5 );
	level.ambient_modifier[ "rain" ] = "norain";
	//	This is commented out until ambient weather sounds are added to the tree
	//maps\_ambient::activateAmbient( level.ambient );
	wait( transition * 0.5 );
}

/*
=============
///ScriptDocBegin
"Name: rainInit( <lvl> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
rainInit( lvl )
{
	flag_init( "_weather_lightning_enabled" );
	flag_set( "_weather_lightning_enabled" );
	
	if ( lvl == "none" )
	{
		level.rainLevel = 0;// starting rain level
		level._effect[ "rain_drops" ] = level._effect[ "rain_" + level.rainLevel ];
		rainNone( 0.1 );
	}
	else
	if ( lvl == "light" )
	{
		level.rainLevel = 5;// starting rain level
		level._effect[ "rain_drops" ] = level._effect[ "rain_" + level.rainLevel ];
		rainLight( 0.1 );
	}
	else
	{
		level.rainLevel = 10;// starting rain level
		level._effect[ "rain_drops" ] = level._effect[ "rain_" + level.rainLevel ];
		rainHard( 0.1 );
	}
}


lightning( normal, flash )
{
	[[ normal ]]();
	waittillframeend;// so exploders get setup
	for ( ;; )
		lightningThink( normal, flash );
}

////// 
/*
	BELOW THIS LINE IS INTERNAL RAIN FUNCTIONS
*/
////// 

rainEffectChange( change, transition )
{
	level notify( "rain_level_change" );
	level endon( "rain_level_change" );
	if ( level.rainLevel > change )
	{
		dif = level.rainLevel - change;
		transition /= dif;
		for ( i = 0;i < dif;i++ )
		{
			wait( transition );
			level.rainLevel -- ;
			level._effect[ "rain_drops" ] = level._effect[ "rain_" + level.rainLevel ];
		}
		assert( level.rainLevel == change );
	}
	if ( level.rainLevel < change )
	{
		dif = change - level.rainLevel;
		transition /= dif;
		for ( i = 0;i < dif;i++ )
		{
			wait( transition );
			level.rainLevel++ ;
			level._effect[ "rain_drops" ] = level._effect[ "rain_" + level.rainLevel ];
		}
		assert( level.rainLevel == change );
	}
}


addLightningExploder( num )
{
	if ( !isdefined( level.lightningExploder ) )
	{
		level.lightningExploder = [];
		level.lightningExploderIndex = 0;
	}

	level.lightningExploder[ level.lightningExploder.size ] = num;
}

playerWeather()
{
	player = getentarray( "player", "classname" )[ 0 ];
	for ( ;; )
	{
		playfx( level._effect[ "rain_drops" ], player.origin + ( 0, 0, 650 ), player.origin + ( 0, 0, 680 ) );
		wait( 0.3 );
	}
}




rainlevelRandomwait()
{
	if ( level.rainLevel == 0 )
		return( randomfloat( 30 ) );
	else
	if ( level.rainLevel == 1 )
		return( randomfloat( 24 ) );
	else
	if ( level.rainLevel == 2 )
		return( randomfloat( 20 ) );
	else
	if ( level.rainLevel == 3 )
		return( randomfloat( 15 ) );
	else
	if ( level.rainLevel == 4 )
		return( randomfloat( 12 ) );
	else
	if ( level.rainLevel == 5 )
		return( randomfloat( 9 ) );
	else
	if ( level.rainLevel == 6 )
		return( randomfloat( 8 ) );
	else
	if ( level.rainLevel == 7 )
		return( randomfloat( 8 ) );
	else
	if ( level.rainLevel == 8 )
		return( randomfloat( 7 ) );
	else
	if ( level.rainLevel == 9 )
		return( randomfloat( 6 ) );
	else
	if ( level.rainLevel == 10 )
		return( randomfloat( 5 ) );
}

rainlevelwait()
{
	if ( level.rainLevel == 0 )
		return( 20 );
	else
	if ( level.rainLevel == 1 )
		return( 18 );
	else
	if ( level.rainLevel == 2 )
		return( 16 );
	else
	if ( level.rainLevel == 3 )
		return( 14 );
	else
	if ( level.rainLevel == 4 )
		return( 12 );
	else
	if ( level.rainLevel == 5 )
		return( 10 );
	else
	if ( level.rainLevel == 6 )
		return( 9 );
	else
	if ( level.rainLevel == 7 )
		return( 8 );
	else
	if ( level.rainLevel == 8 )
		return( 7 );
	else
	if ( level.rainLevel == 9 )
		return( 6 );
	else
	if ( level.rainLevel == 10 )
		return( 5 );
}

lightningThink( normal, flash )
{
	level endon( "rain_change" );
	
	// in case we get broken out, we may have lightning sooner than planned if we're getting rainier
	nextStrike = gettime() + ( ( rainlevelwait() + rainlevelRandomwait() ) * 1000 );
	if ( nextStrike < level.nextLightning )
		level.nextLightning = nextStrike;

	for ( ;; )
	{
		flag_wait( "_weather_lightning_enabled" );
		
		timer = ( level.nextLightning - gettime() ) * 0.001;
		if ( timer > 0 )
			wait( timer );
		
		if( !flag( "_weather_lightning_enabled" ) )
			continue;
		
		lightningFlash( normal, flash );
		level.nextLightning = gettime() + ( ( rainlevelwait() + rainlevelRandomwait() ) * 1000 );
	}
}

fogflash( flashfunc )
{
	if ( isdefined( level.lightningExploderIndex ) )
		exploder( level.lightningExploder[ level.lightningExploderIndex ] );

	[[ flashfunc ]]();
}

lightningFlash( normal, flashfunc, flashType )
{
	flash[ 0 ] = "quick";
	flash[ 1 ] = "double";
	flash[ 2 ] = "triple";

	//this is where the sound happens
	thread thunder();

	if( !isdefined( flashType ) )
		flashType = randomint( flash.size );

	lit_num = 0;
	if ( isdefined( level.lightningExploderIndex ) )
	{
		while ( lit_num == level.lightningExploderIndex )
			lit_num = randomint( level.lightningExploder.size );
		level.lightningExploderIndex = lit_num;
	}

	//this is where the visuals happen
	switch( flash[ flashType ] )
	{
		case "quick":
		{
			fogflash( flashfunc );
			break;
		}
		case "double":
		{
			fogflash( flashfunc );
			wait( 0.05 );
			fogflash( flashfunc );
			break;
		}
		case "triple":
		{
			fogflash( flashfunc );
			wait( 0.05 );
			fogflash( flashfunc );
			wait( 0.5 );
			fogflash( flashfunc );
			break;
		}
	}
}

thunder()
{
	if ( level.rainLevel == 0 )
		wait( 6 + randomfloat( 2 ) );
	else
	if ( level.rainLevel == 1 )
		wait( 5 + randomfloat( 1.8 ) );
	else
	if ( level.rainLevel == 2 )
		wait( 4.5 + randomfloat( 1.6 ) );
	else
	if ( level.rainLevel == 3 )
		wait( 4 + randomfloat( 1.6 ) );
	else
	if ( level.rainLevel == 4 )
		wait( 3.5 + randomfloat( 1.5 ) );
	else
	if ( level.rainLevel == 5 )
		wait( 3 + randomfloat( 1.5 ) );
	else
	if ( level.rainLevel == 6 )
		wait( 2.5 + randomfloat( 1.2 ) );
	else
	if ( level.rainLevel == 7 )
		wait( 2 + randomfloat( 1 ) );
	else
	if ( level.rainLevel == 8 )
		wait( 1.9 + randomfloat( 0.5 ) );
	else
	if ( level.rainLevel == 9 )
		wait( 1.5 );
	else
	if ( level.rainLevel == 10 )
		wait( 1 );

	ent = spawn( "script_origin", ( 0, 0, 0 ) );
	ent.origin = level.player.origin + ( 0, 0, 60 );
	ent linkto( level.player );
	if ( level.rainlevel <= 8 )
		ent playsound( "elm_thunder_distant", "sounddone" );
	else
	{
		ent playsound( "elm_thunder_distant", "sounddone" );
		ent thread play_sound_on_entity( "elm_thunder_strike" );
	}
//	iprintlnbold ("thunder!");	
	ent waittill( "sounddone" );
	ent delete();
}