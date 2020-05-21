#include maps\mp\_utility;
#include common_scripts\utility;

init_audio()
{
	if ( !IsDefined( level.audio ) )
	{
		level.audio = SpawnStruct();
	}

	init_reverb();
	init_whizby();

	level.onPlayerConnectAudioInit = ::OnPlayerConnectAudioInit;
}

OnPlayerConnectAudioInit()
{
	self apply_reverb( "default" );
//	self apply_whizby(); <-- Does not work yet... Looks like it overflows the server.
}

//---------------------------------------------------------
// Reverb Section
//---------------------------------------------------------
init_reverb()
{
	add_reverb( "default", "generic", 0.15, 0.9, 2 );
}

add_reverb( name, type, wetlevel, drylevel, fadetime )
{
	Assert( IsDefined( type ) );
	Assert( IsDefined( wetlevel ) );
	Assert( IsDefined( drylevel ) );
	
	reverb = [];

	is_roomtype_valid( type );

	reverb[ "roomtype" ] = type;
	reverb[ "wetlevel" ] = wetlevel;
	reverb[ "drylevel" ] = drylevel;
	reverb[ "fadetime" ] = fadetime;

	level.audio.reverb_settings[ name ] = reverb;
}

is_roomtype_valid( type )
{
/#
	switch ( type )
	{
		case "generic":
		case "paddedcell":
		case "room":
		case "bathroom":
		case "livingroom":
		case "stoneroom":
		case "auditorium":
		case "concerthall":
		case "cave":
		case "arena":
		case "hangar":
		case "carpetedhallway":
		case "hallway":
		case "stonecorridor":
		case "alley":
		case "forest":
		case "city":
		case "mountains":
		case "quarry":
		case "plain":
		case "parkinglot":
		case "sewerpipe":
		case "underwater":
		case "drugged":
		case "dizzy":
		case "psychotic":
			return;
		default:
			AssertMsg( type + " is an Invalid Roomtype" );
			break;
	}
#/
}

apply_reverb( name )
{
	if ( !IsDefined( level.audio.reverb_settings[ name ] ) )
	{
		reverb = level.audio.reverb_settings[ "default" ];
	}
	else
	{
		reverb = level.audio.reverb_settings[ name ];
	}

	self SetReverb( "snd_enveffectsprio_level", reverb[ "roomtype" ], reverb[ "drylevel" ], reverb[ "wetlevel" ], reverb[ "fadetime" ] );
//	self SetClientDvar( "cg_levelReverbRoomType", reverb[ "roomtype" ] );
//	self SetClientDvar( "cg_levelReverbDryLevel", reverb[ "drylevel" ] );
//	self SetClientDvar( "cg_levelReverbWetLevel", reverb[ "wetlevel" ] );
}

//---------------------------------------------------------
// whizBy Section
//---------------------------------------------------------

init_whizby()
{
	SetDevDvar( "snd_newwhizby", 1 );

	// Default settings -- Call wrappers in your level to overwrite.
	level.audio.whizby_settings = [];
	set_whizby_radius( 15.0, 30.0, 50.0 );
	set_whizby_spread( 150.0, 250.0, 350.0 );
}

set_whizby_radius( near, medium, far )
{
	level.audio.whizby_settings[ "radius" ] = [ near, medium, far ];
}

set_whizby_spread( near, medium, far )
{
	level.audio.whizby_settings[ "spread" ] = [ near, medium, far ];
}

apply_whizby()
{
	settings = level.audio.whizby_settings;

	spread 	= settings[ "spread" ];
	rad 	= settings[ "radius" ];
	
	self SetWhizbySpreads( spread[ 0 ], spread[ 1 ], spread[ 2 ] );
	self SetWhizbyRadii( rad[ 0 ], rad[ 1 ], rad[ 2 ] );
}
