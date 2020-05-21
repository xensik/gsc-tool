#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

KILLSTREAK_GIMME_SLOT = 0;
KILLSTREAK_SLOT_1 = 1;
KILLSTREAK_SLOT_2 = 2;
KILLSTREAK_SLOT_3 = 3;
KILLSTREAK_ALL_PERKS_SLOT = 4;
KILLSTREAK_STACKING_START_SLOT = 5;

MAX_VEHICLES = 8;

LIGHTWEIGHT_SCALAR = 1.10;

exploder_sound()
{
	if ( isdefined( self.script_delay ) )
		wait self.script_delay;

	self playSound( level.scr_sound[ self.script_sound ] );
}

_beginLocationSelection ( streakName, selectorType, directionality , size )
{
	
	self setClientDvar( "ui_selecting_location", "1");
	self BeginLocationSelection( selectorType, directionality, size );
	self.selectingLocation = true;
	self setblurforplayer( 10.3, 0.3 );
	
	self thread endSelectionOnAction( "cancel_location" );
	self thread endSelectionOnAction( "death" );
	self thread endSelectionOnAction( "disconnect" );
	self thread endSelectionOnAction( "used" );
	
	self endon( "stop_location_selection" );
	self thread endSelectionOnEndGame();
	self thread endSelectionOnEMP();
	
	if ( isDefined( streakName) && self.team != "spectator" )
	{
		if ( isDefined( self.streakMsg ) )
			self.streakMsg destroy();				
		self.streakMsg = self maps\mp\gametypes\_hud_util::createFontString( "bigfixed", .8 );
		self.streakMsg maps\mp\gametypes\_hud_util::setPoint( "CENTER", "CENTER", 0 , -190 );
		streakString = tableLookupIString( "mp/killstreakTable.csv", 1, streakName, 2 );
		self.streakMsg setText( streakString );
	}
}

stopLocationSelection( disconnected, reason )
{
	if ( !isDefined( reason ) )
		reason = "generic";
	
	if ( !disconnected )
	{
		self setblurforplayer( 0, 0.3 );
		self endLocationSelection();
		self.selectingLocation = undefined;
		
		if ( isDefined( self.streakMsg ) )
			self.streakMsg destroy();
	}
	self notify( "stop_location_selection", reason );
}

endSelectionOnEMP()
{
	self endon( "stop_location_selection" );
	for ( ;; )
	{
		level waittill( "emp_update" );
	
		if ( !self isEMPed() )
			continue;
			
		self thread stopLocationSelection( false, "emp" );
		return;
	}
}

endSelectionOnAction( waitfor )
{
	self endon( "stop_location_selection" );
	self waittill( waitfor );
	self thread stopLocationSelection( (waitfor == "disconnect"), waitfor );
}

endSelectionOnEndGame()
{
	self endon( "stop_location_selection" );
	level waittill( "game_ended" );
	self thread stopLocationSelection( false, "end_game" );
}

isAttachment( attachmentName )
{
	attachment = tableLookup( "mp/attachmentTable.csv", 4, attachmentName, 0 );
	
	if( isDefined( attachment ) && attachment != "" )
		return true;
	else
		return false;	
}

getAttachmentType( attachmentName )
{
	attachmentType = tableLookup( "mp/attachmentTable.csv", 4, attachmentName, 2 );

	return attachmentType;		
}

/*
saveModel()
{
	info["model"] = self.model;
	info["viewmodel"] = self getViewModel();
	attachSize = self getAttachSize();
	info["attach"] = [];
	
	assert(info["viewmodel"] != ""); // No viewmodel was associated with the player's model
	
	for(i = 0; i < attachSize; i++)
	{
		info["attach"][i]["model"] = self getAttachModelName(i);
		info["attach"][i]["tag"] = self getAttachTagName(i);
		info["attach"][i]["ignoreCollision"] = self getAttachIgnoreCollision(i);
	}
	
	return info;
}

loadModel(info)
{
	self detachAll();
	self setModel(info["model"]);
	self setViewModel(info["viewmodel"]);

	attachInfo = info["attach"];
	attachSize = attachInfo.size;
    
	for(i = 0; i < attachSize; i++)
		self attach(attachInfo[i]["model"], attachInfo[i]["tag"], attachInfo[i]["ignoreCollision"]);
}
*/

/* 
============= 
///ScriptDocBegin
"Name: delayThread( <delay>, <function>, <arg1>, <arg2>, <arg3>, <arg4> )"
"Summary: Delaythread is cool! It saves you from having to write extra script for once off commands. Note you don’t have to thread it off. Delaythread is that smart!"
"Module: Utility"
"MandatoryArg: <delay> : The delay before the function occurs"
"MandatoryArg: <delay> : The function to run."
"OptionalArg: <arg1> : parameter 1 to pass to the process"
"OptionalArg: <arg2> : parameter 2 to pass to the process"
"OptionalArg: <arg3> : parameter 3 to pass to the process"
"OptionalArg: <arg4> : parameter 4 to pass to the process"
"OptionalArg: <arg5> : parameter 5 to pass to the process"
"Example: delayThread( 3, ::flag_set, "player_can_rappel" );
"SPMP: both"
///ScriptDocEnd
============= 
*/ 
delayThread( timer, func, param1, param2, param3, param4, param5 )
{
	// to thread it off
	thread delayThread_proc( func, timer, param1, param2, param3, param4, param5 );
}


delayThread_proc( func, timer, param1, param2, param3, param4, param5 )
{
	wait( timer );
	if ( !IsDefined( param1 ) )
	{
		assertex( !isdefined( param2 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param3 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]();
	}
	else
	if ( !IsDefined( param2 ) )
	{
		assertex( !isdefined( param3 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1 );
	}
	else
	if ( !IsDefined( param3 ) )
	{
		assertex( !isdefined( param4 ), "Delaythread does not support vars after undefined." );
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1, param2 );
	}
	else
	if ( !IsDefined( param4 ) )	
	{
		assertex( !isdefined( param5 ), "Delaythread does not support vars after undefined." );
		thread [[ func ]]( param1, param2, param3 );
	}
	else
	if ( !IsDefined( param5 ) )	
	{
		thread [[ func ]]( param1, param2, param3, param4 );
	}
	else
	{
		thread [[ func ]]( param1, param2, param3, param4, param5 );
	}
}

getPlant()
{
	start = self.origin + ( 0, 0, 10 );

	range = 11;
	forward = anglesToForward( self.angles );
	forward = ( forward * range );

	traceorigins[ 0 ] = start + forward;
	traceorigins[ 1 ] = start;

	trace = bulletTrace( traceorigins[ 0 ], ( traceorigins[ 0 ] + ( 0, 0, -18 ) ), false, undefined );
	if ( trace[ "fraction" ] < 1 )
	{
		//println("^6Using traceorigins[0], tracefraction is", trace["fraction"]);

		temp = spawnstruct();
		temp.origin = trace[ "position" ];
		temp.angles = orientToNormal( trace[ "normal" ] );
		return temp;
	}

	trace = bulletTrace( traceorigins[ 1 ], ( traceorigins[ 1 ] + ( 0, 0, -18 ) ), false, undefined );
	if ( trace[ "fraction" ] < 1 )
	{
		//println("^6Using traceorigins[1], tracefraction is", trace["fraction"]);

		temp = spawnstruct();
		temp.origin = trace[ "position" ];
		temp.angles = orientToNormal( trace[ "normal" ] );
		return temp;
	}

	traceorigins[ 2 ] = start + ( 16, 16, 0 );
	traceorigins[ 3 ] = start + ( 16, -16, 0 );
	traceorigins[ 4 ] = start + ( -16, -16, 0 );
	traceorigins[ 5 ] = start + ( -16, 16, 0 );

	besttracefraction = undefined;
	besttraceposition = undefined;
	for ( i = 0; i < traceorigins.size; i++ )
	{
		trace = bulletTrace( traceorigins[ i ], ( traceorigins[ i ] + ( 0, 0, -1000 ) ), false, undefined );

		//ent[i] = spawn("script_model",(traceorigins[i]+(0, 0, -2)));
		//ent[i].angles = (0, 180, 180);
		//ent[i] setmodel("105");

		//println("^6trace ", i ," fraction is ", trace["fraction"]);

		if ( !isdefined( besttracefraction ) || ( trace[ "fraction" ] < besttracefraction ) )
		{
			besttracefraction = trace[ "fraction" ];
			besttraceposition = trace[ "position" ];

			//println("^6besttracefraction set to ", besttracefraction, " which is traceorigin[", i, "]");
		}
	}

	if ( besttracefraction == 1 )
		besttraceposition = self.origin;

	temp = spawnstruct();
	temp.origin = besttraceposition;
	temp.angles = orientToNormal( trace[ "normal" ] );
	return temp;
}

orientToNormal( normal )
{
	hor_normal = ( normal[ 0 ], normal[ 1 ], 0 );
	hor_length = length( hor_normal );

	if ( !hor_length )
		return( 0, 0, 0 );

	hor_dir = vectornormalize( hor_normal );
	neg_height = normal[ 2 ] * - 1;
	tangent = ( hor_dir[ 0 ] * neg_height, hor_dir[ 1 ] * neg_height, hor_length );
	plant_angle = vectortoangles( tangent );

	//println("^6hor_normal is ", hor_normal);
	//println("^6hor_length is ", hor_length);
	//println("^6hor_dir is ", hor_dir);
	//println("^6neg_height is ", neg_height);
	//println("^6tangent is ", tangent);
	//println("^6plant_angle is ", plant_angle);

	return plant_angle;
}

deletePlacedEntity( entity )
{
	entities = getentarray( entity, "classname" );
	for ( i = 0; i < entities.size; i++ )
	{
		//println("DELETED: ", entities[i].classname);
		entities[ i ] delete();
	}
}

playSoundOnPlayers( sound, team, excludeList )
{
	assert( isdefined( level.players ) );

	if ( level.splitscreen )
	{
		if ( isdefined( level.players[ 0 ] ) )
			level.players[ 0 ] playLocalSound( sound );
	}
	else
	{
		if ( isDefined( team ) )
		{
			if ( isdefined( excludeList ) )
			{
				for ( i = 0; i < level.players.size; i++ )
				{
					player = level.players[ i ];

					if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
						continue;

					if ( isdefined( player.pers[ "team" ] ) && ( player.pers[ "team" ] == team ) && !isExcluded( player, excludeList ) )
						player playLocalSound( sound );
				}
			}
			else
			{
				for ( i = 0; i < level.players.size; i++ )
				{
					player = level.players[ i ];

					if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
						continue;

					if ( isdefined( player.pers[ "team" ] ) && ( player.pers[ "team" ] == team ) )
						player playLocalSound( sound );
				}
			}
		}
		else
		{
			if ( isdefined( excludeList ) )
			{
				for ( i = 0; i < level.players.size; i++ )
				{
					if( level.players[ i ] isSplitscreenPlayer() && !level.players[ i ] isSplitscreenPlayerPrimary() )
						continue;

					if ( !isExcluded( level.players[ i ], excludeList ) )
						level.players[ i ] playLocalSound( sound );
				}
			}
			else
			{
				for ( i = 0; i < level.players.size; i++ )
				{
					if( level.players[ i ] isSplitscreenPlayer() && !level.players[ i ] isSplitscreenPlayerPrimary() )
						continue;

					level.players[ i ] playLocalSound( sound );
				}
			}
		}
	}
}


sortLowerMessages()
{
	for ( i = 1; i < self.lowerMessages.size; i++ )
	{
		message = self.lowerMessages[ i ];
		priority = message.priority;
		for ( j = i - 1; j >= 0 && priority > self.lowerMessages[ j ].priority; j -- )
			self.lowerMessages[ j + 1 ] = self.lowerMessages[ j ];
		self.lowerMessages[ j + 1 ] = message;
	}
}


addLowerMessage( name, text, time, priority, showTimer, shouldFade, fadeToAlpha, fadeToAlphaTime, hideWhenInDemo )
{
	newMessage = undefined;
	foreach ( message in self.lowerMessages )
	{
		if ( message.name == name )
		{
			if ( message.text == text && message.priority == priority )
				return;

			newMessage = message;
			break;
		}
	}

	if ( !isDefined( newMessage ) )
	{
		newMessage = spawnStruct();
		self.lowerMessages[ self.lowerMessages.size ] = newMessage;
	}

	newMessage.name = name;
	newMessage.text = text;
	newMessage.time = time;
	newMessage.addTime = getTime();
	newMessage.priority = priority;
	newMessage.showTimer = showTimer;
	newMessage.shouldFade = shouldFade;
	newMessage.fadeToAlpha = fadeToAlpha;
	newMessage.fadeToAlphaTime = fadeToAlphaTime;
	newMessage.hideWhenInDemo = hideWhenInDemo;

	sortLowerMessages();
}


removeLowerMessage( name )
{
	if( IsDefined( self.lowerMessages ) )
	{
		// since we're changing the array in the loop, we should iterate backwards
		for ( i = self.lowerMessages.size; i > 0; i-- )
		{
			if ( self.lowerMessages[ i - 1 ].name != name )
				continue;

			message = self.lowerMessages[ i - 1 ];
			
			// now move every message down one to fill the empty space
			for( j = i; j < self.lowerMessages.size; j++ )
			{
				if ( IsDefined( self.lowerMessages[ j ] ) )
					self.lowerMessages[ j - 1 ] = self.lowerMessages[ j ];
			}

			// make the last one undefined because we filled the space above
			self.lowerMessages[ self.lowerMessages.size - 1 ] = undefined;
		}

		sortLowerMessages();
	}
}


getLowerMessage()
{
	return self.lowerMessages[ 0 ];
}


/*
============= 
///ScriptDocBegin
"Name: setLowerMessage( <name>, <text>, <time>, <priority>, <showTimer>, <shouldFade>, <fadeToAlpha>, <fadeToAlphaTime> )"
"Summary: Creates a message to show on the lower half of the screen."
"Module: HUD"
"CallOn: A player"
"MandatoryArg: <name> The name of the message."
"MandatoryArg: <text> The text of the message to display."
"OptionalArg: <time> How long the message will display (default 0 - infinite)."
"OptionalArg: <priority> The priority of the message to display (default 1)."
"OptionalArg: <showTimer> If you pass in time do you want the timer text to show, if not then lower message will fade over time (default false)."
"OptionalArg: <shouldFade> If you want the message to fade to an alpha after coming up the first time (default false)."
"OptionalArg: <fadeToAlpha> If you want the message to fade to an alpha after coming up the first time, pass in the value (default 0.85)."
"OptionalArg: <fadeToAlphaTime> The time that this message will fade to the alpha value passed in before this (default 3.0)."
"OptionalArg: <hideWhenInDemo> Show hud when in demo playback (default false)."
"Example: self setLowerMessage( "last_stand", &"PLATFORM_COWARDS_WAY_OUT", undefined, 50 );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
setLowerMessage( name, text, time, priority, showTimer, shouldFade, fadeToAlpha, fadeToAlphaTime, hideWhenInDemo )
{
	if ( !isDefined( priority ) )
		priority = 1;

	if ( !isDefined( time ) )
		time = 0;

	if ( !isDefined( showTimer ) )
		showTimer = false;

	if ( !isDefined( shouldFade ) )
		shouldFade = false;

	if ( !isDefined( fadeToAlpha ) )
		fadeToAlpha = 0.85;

	if ( !isDefined( fadeToAlphaTime ) )
		fadeToAlphaTime = 3.0;
		
	if ( !isDefined( hideWhenInDemo ) )
		hideWhenInDemo = false;

	self addLowerMessage( name, text, time, priority, showTimer, shouldFade, fadeToAlpha, fadeToAlphaTime, hideWhenInDemo );
	self updateLowerMessage();
	//self notify( "lower_message_set" );
}


updateLowerMessage()
{
	message = self getLowerMessage();

	if ( !isDefined( message ) )
	{
		self.lowerMessage.alpha = 0;
		self.lowerTimer.alpha = 0;
		return;
	}

	self.lowerMessage setText( message.text );
	self.lowerMessage.alpha = 0.85;
	self.lowerTimer.alpha = 1;
	
	self.lowerMessage.hideWhenInDemo = message.hideWhenInDemo;

	if( message.shouldFade )
	{
		self.lowerMessage FadeOverTime( min( message.fadeToAlphaTime, 60 ) );
		self.lowerMessage.alpha = message.fadeToAlpha;
	}

	if ( message.time > 0 && message.showTimer )
	{
		self.lowerTimer setTimer( max( message.time - ( ( getTime() - message.addTime ) / 1000 ), 0.1 ) );
	}
	else if( message.time > 0 && !message.showTimer )
	{
		self.lowerTimer setText( "" );
		self.lowerMessage FadeOverTime( min( message.time, 60 ) );
		self.lowerMessage.alpha = 0;
		self thread clearOnDeath( message );
		self thread clearAfterFade( message );
	}
	else
	{
		self.lowerTimer setText( "" );
	}
}

clearOnDeath( message )
{
	self notify( "message_cleared" );
	self endon( "message_cleared" );
	self endon( "disconnect" );
	level endon( "game_ended" );
	
	self waittill( "death" );
	self clearLowerMessage( message.name );
}

clearAfterFade( message )
{
	wait( message.time );
	self clearLowerMessage( message.name );
	self notify( "message_cleared" );
}

/*
============= 
///ScriptDocBegin
"Name: clearLowerMessage( <name> )"
"Summary: Clears the message on the lower portion of the screen."
"Module: HUD"
"CallOn: A player"
"MandatoryArg: <name> The name of the message."
"Example: self clearLowerMessage( "last_stand" );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
clearLowerMessage( name )
{
	self removeLowerMessage( name );
	self updateLowerMessage();
}

clearLowerMessages()
{
	for ( i = 0; i < self.lowerMessages.size; i++ )
		self.lowerMessages[ i ] = undefined;

	if ( !isDefined( self.lowerMessage ) )
		return;

	self updateLowerMessage();
}

printOnTeam( printString, team )
{
	foreach ( player in level.players )
	{
		if ( player.team != team )
			continue;

		player iPrintLn( printString );
	}
}

printBoldOnTeam( text, team )
{
	assert( isdefined( level.players ) );
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[ i ];
		if ( ( isdefined( player.pers[ "team" ] ) ) && ( player.pers[ "team" ] == team ) )
			player iprintlnbold( text );
	}
}

printBoldOnTeamArg( text, team, arg )
{
	assert( isdefined( level.players ) );
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[ i ];
		if ( ( isdefined( player.pers[ "team" ] ) ) && ( player.pers[ "team" ] == team ) )
			player iprintlnbold( text, arg );
	}
}

printOnTeamArg( text, team, arg )
{
	assert( isdefined( level.players ) );
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[ i ];
		if ( ( isdefined( player.pers[ "team" ] ) ) && ( player.pers[ "team" ] == team ) )
			player iprintln( text, arg );
	}
}

printOnPlayers( text, team )
{
	players = level.players;
	for ( i = 0; i < players.size; i++ )
	{
		if ( isDefined( team ) )
		{
			if ( ( isdefined( players[ i ].pers[ "team" ] ) ) && ( players[ i ].pers[ "team" ] == team ) )
				players[ i ] iprintln( text );
		}
		else
		{
			players[ i ] iprintln( text );
		}
	}
}

printAndSoundOnEveryone( team, otherteam, printFriendly, printEnemy, soundFriendly, soundEnemy, printarg )
{
	shouldDoSounds = isDefined( soundFriendly );

	shouldDoEnemySounds = false;
	if ( isDefined( soundEnemy ) )
	{
		assert( shouldDoSounds );// can't have an enemy sound without a friendly sound
		shouldDoEnemySounds = true;
	}

	if ( level.splitscreen || !shouldDoSounds )
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			playerteam = player.pers[ "team" ];
			if ( isdefined( playerteam ) )
			{
				if ( playerteam == team && isdefined( printFriendly ) )
					player iprintln( printFriendly, printarg );
				else if ( playerteam == otherteam && isdefined( printEnemy )  )
					player iprintln( printEnemy, printarg );
			}
		}
		if ( shouldDoSounds )
		{
			assert( level.splitscreen );
			level.players[ 0 ] playLocalSound( soundFriendly );
		}
	}
	else
	{
		assert( shouldDoSounds );
		if ( shouldDoEnemySounds )
		{
			for ( i = 0; i < level.players.size; i++ )
			{
				player = level.players[ i ];
				playerteam = player.pers[ "team" ];
				if ( isdefined( playerteam ) )
				{
					if ( playerteam == team )
					{
						if ( isdefined( printFriendly ) )
							player iprintln( printFriendly, printarg );
						player playLocalSound( soundFriendly );
					}
					else if ( playerteam == otherteam )
					{
						if ( isdefined( printEnemy ) )
							player iprintln( printEnemy, printarg );
						player playLocalSound( soundEnemy );
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < level.players.size; i++ )
			{
				player = level.players[ i ];
				playerteam = player.pers[ "team" ];
				if ( isdefined( playerteam ) )
				{
					if ( playerteam == team )
					{
						if ( isdefined( printFriendly ) )
							player iprintln( printFriendly, printarg );
						player playLocalSound( soundFriendly );
					}
					else if ( playerteam == otherteam )
					{
						if ( isdefined( printEnemy ) )
							player iprintln( printEnemy, printarg );
					}
				}
			}
		}
	}
}

printAndSoundOnTeam( team, printString, soundAlias )
{
	foreach ( player in level.players )
	{
		if ( player.team != team )
			continue;

		player printAndSoundOnPlayer( printString, soundAlias );
	}
}

printAndSoundOnPlayer( printString, soundAlias )
{
	self iPrintLn( printString );
	self playLocalSound( soundAlias );
}

_playLocalSound( soundAlias )
{
	if ( level.splitscreen && self getEntityNumber() != 0 )
		return;

	self playLocalSound( soundAlias );
}

dvarIntValue( dVar, defVal, minVal, maxVal )
{
	dVar = "scr_" + level.gameType + "_" + dVar;
	if ( getDvar( dVar ) == "" )
	{
		setDvar( dVar, defVal );
		return defVal;
	}

	value = getDvarInt( dVar );

	if ( value > maxVal )
		value = maxVal;
	else if ( value < minVal )
		value = minVal;
	else
		return value;

	setDvar( dVar, value );
	return value;
}

dvarFloatValue( dVar, defVal, minVal, maxVal )
{
	dVar = "scr_" + level.gameType + "_" + dVar;
	if ( getDvar( dVar ) == "" )
	{
		setDvar( dVar, defVal );
		return defVal;
	}

	value = getDvarFloat( dVar );

	if ( value > maxVal )
		value = maxVal;
	else if ( value < minVal )
		value = minVal;
	else
		return value;

	setDvar( dVar, value );
	return value;
}

play_sound_on_tag( alias, tag )
{
	if ( isdefined( tag ) )
	{
		playsoundatpos( self getTagOrigin( tag ), alias );
	}
	else
	{
		playsoundatpos( self.origin, alias );
	}
}

getOtherTeam( team )
{
	if ( team == "allies" )
		return "axis";
	else if ( team == "axis" )
		return "allies";

	assertMsg( "getOtherTeam: invalid team " + team );
}

wait_endon( waitTime, endOnString, endonString2, endonString3 )
{
	self endon( endOnString );
	if ( isDefined( endonString2 ) )
		self endon( endonString2 );
	if ( isDefined( endonString3 ) )
		self endon( endonString3 );

	wait( waitTime );
}

initPersStat( dataName )
{
	if ( !isDefined( self.pers[ dataName ] ) )
		self.pers[ dataName ] = 0;
}

getPersStat( dataName )
{
	return self.pers[ dataName ];
}

incPersStat( dataName, increment )
{
	self.pers[ dataName ] += increment;
	self maps\mp\gametypes\_persistence::statAdd( dataName, increment );
}

setPersStat( dataName, value )
{
	assertEx( isDefined( dataName ), "Called setPersStat with no dataName defined." );
	assertEx( isDefined( value ), "Called setPersStat for " + dataName + " with no value defined." );
	
	self.pers[ dataName ] = value;
}

initPlayerStat( ref, defaultvalue )
{
	if ( !isDefined( self.stats["stats_" + ref ] ) )
	{
		if ( !isDefined( defaultvalue ) )
			defaultvalue = 0;
		
		self.stats["stats_" + ref ] = spawnstruct();
		self.stats["stats_" + ref ].value = defaultvalue;
	}
}

incPlayerStat( ref, increment )
{
	stat = self.stats["stats_" + ref ];
	stat.value += increment;
}

setPlayerStat( ref, value )
{
	stat = self.stats["stats_" + ref ];
	stat.value = value;
	stat.time = getTime();
}

getPlayerStat( ref )
{
	return self.stats["stats_" + ref ].value;
}

getPlayerStatTime( ref )
{
	return self.stats["stats_" + ref ].time;
}

setPlayerStatIfGreater( ref, newvalue )
{
	currentvalue = self getPlayerStat( ref );

	if ( newvalue > currentvalue )
		self setPlayerStat( ref, newvalue );
}

setPlayerStatIfLower( ref, newvalue )
{
	currentvalue = self getPlayerStat( ref );

	if ( newvalue < currentvalue )
		self setPlayerStat( ref, newvalue );
}

updatePersRatio( ratio, num, denom )
{
	numValue = self maps\mp\gametypes\_persistence::statGet( num );
	denomValue = self maps\mp\gametypes\_persistence::statGet( denom );
	if ( denomValue == 0 )
		denomValue = 1;

	self maps\mp\gametypes\_persistence::statSet( ratio, int( ( numValue * 1000 ) / denomValue ) );
}

updatePersRatioBuffered( ratio, num, denom )
{
	numValue = self maps\mp\gametypes\_persistence::statGetBuffered( num );
	denomValue = self maps\mp\gametypes\_persistence::statGetBuffered( denom );
	if ( denomValue == 0 )
		denomValue = 1;

	self maps\mp\gametypes\_persistence::statSetBuffered( ratio, int( ( numValue * 1000 ) / denomValue ) );
}


// to be used with things that are slow.
// unfortunately, it can only be used with things that aren't time critical.
WaitTillSlowProcessAllowed( allowLoop )
{
	// wait only a few frames if necessary
	// if we wait too long, we might get too many threads at once and run out of variables
	// i'm trying to avoid using a loop because i don't want any extra variables
	if ( level.lastSlowProcessFrame == gettime() )
	{
		if ( isDefined( allowLoop ) && allowLoop )
		{
			while ( level.lastSlowProcessFrame == getTime() )
				wait( 0.05 );
		}
		else
		{
			wait .05;
			if ( level.lastSlowProcessFrame == gettime() )
			{
				wait .05;
				if ( level.lastSlowProcessFrame == gettime() )
				{
					wait .05;
					if ( level.lastSlowProcessFrame == gettime() )
					{
						wait .05;
					}
				}
			}
		}
	}

	level.lastSlowProcessFrame = getTime();
}


waitForTimeOrNotify( time, notifyname )
{
	self endon( notifyname );
	wait time;
}


isExcluded( entity, entityList )
{
	for ( index = 0; index < entityList.size; index++ )
	{
		if ( entity == entityList[ index ] )
			return true;
	}
	return false;
}


leaderDialog( dialog, team, group, excludeList )
{
	assert( isdefined( level.players ) );

	if ( level.splitscreen )
		return;

	if ( dialog == "null" )
		return;

	if ( !isDefined( team ) )
	{
		leaderDialogBothTeams( dialog, "allies", dialog, "axis", group, excludeList );
		return;
	}

	if ( level.splitscreen )
	{
		if ( level.players.size )
			level.players[ 0 ] leaderDialogOnPlayer( dialog, group );
		return;
	}

	if ( isDefined( excludeList ) )
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			if ( ( isDefined( player.pers[ "team" ] ) && ( player.pers[ "team" ] == team ) ) && !isExcluded( player, excludeList ) )
			{
				if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
					continue;

				player leaderDialogOnPlayer( dialog, group );
			}
		}
	}
	else
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			if ( isDefined( player.pers[ "team" ] ) && ( player.pers[ "team" ] == team ) )
			{
				if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
					continue;

				player leaderDialogOnPlayer( dialog, group );
			}
		}
	}
}


leaderDialogBothTeams( dialog1, team1, dialog2, team2, group, excludeList )
{
	assert( isdefined( level.players ) );

	if ( level.splitscreen )
		return;

	if ( level.splitscreen )
	{
		if ( level.players.size )
			level.players[ 0 ] leaderDialogOnPlayer( dialog1, group );
		return;
	}

	if ( isDefined( excludeList ) )
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			team = player.pers[ "team" ];

			if ( !isDefined( team ) )
				continue;

			if ( isExcluded( player, excludeList ) )
				continue;

			if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
					continue;

			if ( team == team1 )
				player leaderDialogOnPlayer( dialog1, group );
			else if ( team == team2 )
				player leaderDialogOnPlayer( dialog2, group );
		}
	}
	else
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			team = player.pers[ "team" ];

			if ( !isDefined( team ) )
				continue;

			if( player isSplitscreenPlayer() && !player isSplitscreenPlayerPrimary() )
					continue;

			if ( team == team1 )
				player leaderDialogOnPlayer( dialog1, group );
			else if ( team == team2 )
				player leaderDialogOnPlayer( dialog2, group );
		}
	}
}


leaderDialogOnPlayers( dialog, players, group )
{
	foreach ( player in players )
		player leaderDialogOnPlayer( dialog, group );
}


leaderDialogOnPlayer( dialog, group, groupOverride )
{
	if ( !isDefined( groupOverride ) )
		groupOverride = false;
	
	team = self.pers[ "team" ];

	if ( level.splitscreen )
		return;

	if ( !isDefined( team ) )
		return;

	if ( team != "allies" && team != "axis" )
		return;

	if ( isDefined( group ) )
	{
		// ignore the message if one from the same group is already playing
		if ( self.leaderDialogGroup == group )
		{
			if ( groupOverride )
			{
				self stopLocalSound( self.leaderDialogActive );
				self thread playLeaderDialogOnPlayer( dialog, team );
			}
			
			return;
		}

		hadGroupDialog = isDefined( self.leaderDialogGroups[ group ] );

		self.leaderDialogGroups[ group ] = dialog;
		dialog = group;

		// exit because the "group" dialog call is already in the queue
		if ( hadGroupDialog )
			return;
	}

	if ( self.leaderDialogActive == "" )
		self thread playLeaderDialogOnPlayer( dialog, team );
	else
		self.leaderDialogQueue[ self.leaderDialogQueue.size ] = dialog;
}


playLeaderDialogOnPlayer( dialog, team )
{
	self endon( "disconnect" );

	self notify ( "playLeaderDialogOnPlayer" );
	self endon ( "playLeaderDialogOnPlayer" );

	if ( isDefined( self.leaderDialogGroups[ dialog ] ) )
	{
		group = dialog;
		dialog = self.leaderDialogGroups[ group ];
		self.leaderDialogGroups[ group ] = undefined;
		self.leaderDialogGroup = group;
	}
	
	assertEx( isDefined( game[ "dialog" ][ dialog ] ), "Dialog " + dialog + " was not defined in game[dialog] array." );

	if ( isSubStr( game[ "dialog" ][ dialog ], "null" ) )
		return;

	self.leaderDialogActive = game[ "voice" ][ team ] + game[ "dialog" ][ dialog ];
	self playLocalSound( game[ "voice" ][ team ] + game[ "dialog" ][ dialog ] );

	wait( 3.0 );
	self.leaderDialogLocalSound = "";
	
	self.leaderDialogActive = "";
	self.leaderDialogGroup = "";

	if ( self.leaderDialogQueue.size > 0 )
	{
		nextDialog = self.leaderDialogQueue[ 0 ];

		for ( i = 1; i < self.leaderDialogQueue.size; i++ )
			self.leaderDialogQueue[ i - 1 ] = self.leaderDialogQueue[ i ];
		self.leaderDialogQueue[ i - 1 ] = undefined;

		self thread playLeaderDialogOnPlayer( nextDialog, team );
	}
}


updateMainMenu()
{
	if (self.pers[ "team" ] == "spectator" )
	{
		self setClientDvar("g_scriptMainMenu", game["menu_team"]);
	}
	else
	{
		self setClientDvar( "g_scriptMainMenu", game[ "menu_class_" + self.pers["team"] ] );
	}
}


updateObjectiveText()
{
	if ( self.pers[ "team" ] == "spectator" )
	{
		self setClientDvar( "cg_objectiveText", "" );
		return;
	}

	if ( getWatchedDvar( "scorelimit" ) > 0 && !isObjectiveBased() )
	{
		if ( level.splitScreen )
			self setclientdvar( "cg_objectiveText", getObjectiveScoreText( self.pers[ "team" ] ) );
		else
			self setclientdvar( "cg_objectiveText", getObjectiveScoreText( self.pers[ "team" ] ), getWatchedDvar( "scorelimit" ) );
	}
	else
	{
		self setclientdvar( "cg_objectiveText", getObjectiveText( self.pers[ "team" ] ) );
	}
}


setObjectiveText( team, text )
{
	game[ "strings" ][ "objective_" + team ] = text;
	precacheString( text );
}

setObjectiveScoreText( team, text )
{
	game[ "strings" ][ "objective_score_" + team ] = text;
	precacheString( text );
}

setObjectiveHintText( team, text )
{
	game[ "strings" ][ "objective_hint_" + team ] = text;
	precacheString( text );
}

getObjectiveText( team )
{
	return game[ "strings" ][ "objective_" + team ];
}

getObjectiveScoreText( team )
{
	return game[ "strings" ][ "objective_score_" + team ];
}

getObjectiveHintText( team )
{
	return game[ "strings" ][ "objective_hint_" + team ];
}



getTimePassed()
{
	if ( !isDefined( level.startTime ) || !isDefined( level.discardTime ) )
		return 0;
	
	if ( level.timerStopped )
		return( level.timerPauseTime - level.startTime ) - level.discardTime;
	else
		return( gettime() - level.startTime ) - level.discardTime;

}

getSecondsPassed()
{
	return (getTimePassed() / 1000);
}

getMinutesPassed()
{
	return (getSecondsPassed() / 60);
}

ClearKillcamState()
{
	self.forcespectatorclient = -1;
	self.killcamentity = -1;
	self.archivetime = 0;
	self.psoffsettime = 0;
}

isInKillcam()
{
	return ( self.forcespectatorclient != -1 || self.killcamentity != -1 );
}

isValidClass( class )
{
	return isDefined( class ) && class != "";
}



getValueInRange( value, minValue, maxValue )
{
	if ( value > maxValue )
		return maxValue;
	else if ( value < minValue )
		return minValue;
	else
		return value;
}




waitForTimeOrNotifies( desiredDelay )
{
	startedWaiting = getTime();

	waitedTime = ( getTime() - startedWaiting ) / 1000;

	if ( waitedTime < desiredDelay )
	{
		wait desiredDelay - waitedTime;
		return desiredDelay;
	}
	else
	{
		return waitedTime;
	}
}

closeMenus()
{
	self closepopupMenu();
	self closeInGameMenu();
}


logXPGains()
{
	if ( !isDefined( self.xpGains ) )
		return;

	xpTypes = getArrayKeys( self.xpGains );
	for ( index = 0; index < xpTypes.size; index++ )
	{
		gain = self.xpGains[ xpTypes[ index ] ];
		if ( !gain )
			continue;

		self logString( "xp " + xpTypes[ index ] + ": " + gain );
	}
}


registerRoundSwitchDvar( dvarString, defaultValue, minValue, maxValue )
{
	registerWatchDvarInt( "roundswitch", defaultValue );

	dvarString = ( "scr_" + dvarString + "_roundswitch" );

	level.roundswitchDvar = dvarString;
	level.roundswitchMin = minValue;
	level.roundswitchMax = maxValue;
	level.roundswitch = getDvarInt( dvarString, defaultValue );
	
	if ( level.roundswitch < minValue )
		level.roundswitch = minValue;
	else if ( level.roundswitch > maxValue )
		level.roundswitch = maxValue;
}


registerRoundLimitDvar( dvarString, defaultValue )
{
	registerWatchDvarInt( "roundlimit", defaultValue );
}


registerWinLimitDvar( dvarString, defaultValue )
{
	registerWatchDvarInt( "winlimit", defaultValue );
}


registerScoreLimitDvar( dvarString, defaultValue )
{
	registerWatchDvarInt( "scorelimit", defaultValue );
}


registerTimeLimitDvar( dvarString, defaultValue )
{
	registerWatchDvarFloat( "timelimit", defaultValue );
	makeDvarServerInfo( "ui_timelimit", getTimeLimit() );
}

registerHalfTimeDvar( dvarString, defaultValue ) 
{
	registerWatchDvarInt( "halftime", defaultValue );
	makeDvarServerInfo( "ui_halftime", getHalfTime() );
}

registerNumLivesDvar( dvarString, defaultValue )
{
	registerWatchDvarInt( "numlives", defaultValue );
}

setOverTimeLimitDvar( value )
{
	makeDvarServerInfo( "overtimeTimeLimit", value );
}

get_damageable_player( player, playerpos )
{
	newent = spawnstruct();
	newent.isPlayer = true;
	newent.isADestructable = false;
	newent.entity = player;
	newent.damageCenter = playerpos;
	return newent;
}

get_damageable_sentry( sentry, sentryPos )
{
	newent = spawnstruct();
	newent.isPlayer = false;
	newent.isADestructable = false;
	newent.isSentry = true;
	newent.entity = sentry;
	newent.damageCenter = sentryPos;
	return newent;
}

get_damageable_grenade( grenade, entpos )
{
	newent = spawnstruct();
	newent.isPlayer = false;
	newent.isADestructable = false;
	newent.entity = grenade;
	newent.damageCenter = entpos;
	return newent;
}

get_damageable_mine( mine, entpos )
{
	newent = spawnstruct();
	newent.isPlayer = false;
	newent.isADestructable = false;
	newent.entity = mine;
	newent.damageCenter = entpos;
	return newent;
}

get_damageable_player_pos( player )
{
	return player.origin + ( 0, 0, 32 );
}

getStanceCenter()
{
	if ( self GetStance() == "crouch" )
		center = self.origin + ( 0, 0, 24 );
	else if ( self GetStance() == "prone" )
		center = self.origin + ( 0, 0, 10 );
	else
		center = self.origin + ( 0, 0, 32 );
	
	return center;
}

get_damageable_grenade_pos( grenade )
{
	return grenade.origin;
}

// this should be a code function.
getDvarVec( dvarName )
{
	dvarString = getDvar( dvarName );

	if ( dvarString == "" )
		return( 0, 0, 0 );

	dvarTokens = strTok( dvarString, " " );

	if ( dvarTokens.size < 3 )
		return( 0, 0, 0 );

	setDvar( "tempR", dvarTokens[ 0 ] );
	setDvar( "tempG", dvarTokens[ 1 ] );
	setDvar( "tempB", dvarTokens[ 2 ] );

	return( ( getDvarFloat( "tempR" ), getDvarFloat( "tempG" ), getDvarFloat( "tempB" ) ) );
}

strip_suffix( lookupString, stripString )
{
	if ( lookupString.size <= stripString.size )
		return lookupString;

	if ( getSubStr( lookupString, lookupString.size - stripString.size, lookupString.size ) == stripString )
		return getSubStr( lookupString, 0, lookupString.size - stripString.size );

	return lookupString;
}

_takeWeaponsExcept( saveWeapon )
{
	weaponsList = self GetWeaponsListAll();
	
	foreach ( weapon in weaponsList )
	{
		if ( weapon == saveWeapon )
		{
			continue;	
		}
		else
		{
			self takeWeapon( weapon );
		}
	}
}

saveData()
{
	saveData = spawnstruct();

	saveData.offhandClass = self getOffhandSecondaryClass();
	saveData.actionSlots = self.saved_actionSlotData;

	saveData.currentWeapon = self getCurrentWeapon();

	weaponsList = self GetWeaponsListAll();
	saveData.weapons = [];
	foreach ( weapon in weaponsList )
	{
		if ( weaponInventoryType( weapon ) == "exclusive" )
			continue;
			
		if ( weaponInventoryType( weapon ) == "altmode" )
			continue;

		saveWeapon = spawnStruct();
		saveWeapon.name = weapon;
		saveWeapon.clipAmmoR = self getWeaponAmmoClip( weapon, "right" );
		saveWeapon.clipAmmoL = self getWeaponAmmoClip( weapon, "left" );
		saveWeapon.stockAmmo = self getWeaponAmmoStock( weapon );		
		/* save camo? */
		
		if ( isDefined( self.throwingGrenade ) && self.throwingGrenade == weapon )
			saveWeapon.stockAmmo--;
		
		assert( saveWeapon.stockAmmo >= 0 );
		
		saveData.weapons[saveData.weapons.size] = saveWeapon;
	}
	
	self.script_saveData = saveData;
}


restoreData()
{
	saveData = self.script_saveData;

	self setOffhandSecondaryClass( saveData.offhandClass );

	foreach ( weapon in saveData.weapons )
	{		
		//if ( weapon.name == self.loadoutPrimary + "_mp" )
			self _giveWeapon( weapon.name, int(tableLookup( "mp/camoTable.csv", 1, self.loadoutPrimaryCamo, 0 )) );
		//else
		//self _giveWeapon( weapon.name );
			
		self setWeaponAmmoClip( weapon.name, weapon.clipAmmoR, "right" );
		if ( isSubStr( weapon.name, "akimbo" ) )
			self setWeaponAmmoClip( weapon.name, weapon.clipAmmoL, "left" );

		self setWeaponAmmoStock( weapon.name, weapon.stockAmmo );
	}

	foreach ( slotID, actionSlot in saveData.actionSlots )
		self _setActionSlot( slotID, actionSlot.type, actionSlot.item );

	if ( self getCurrentWeapon() == "none" )
	{
		weapon = saveData.currentWeapon;

		if ( weapon == "none" )
			weapon = self getLastWeapon();
		
		// Can remove this when "spawn" isn't used after final stand
		self setSpawnWeapon( weapon );
		self switchToWeapon( weapon );
	}
}


_setActionSlot( slotID, type, item )
{
	self.saved_actionSlotData[slotID].type = type;
	self.saved_actionSlotData[slotID].item = item;

	self setActionSlot( slotID, type, item );
}


isFloat( value )
{
	if ( int( value ) != value )
		return true;

	return false;
}

registerWatchDvarInt( nameString, defaultValue )
{
	dvarString = "scr_" + level.gameType + "_" + nameString;

	level.watchDvars[ dvarString ] = spawnStruct();
	level.watchDvars[ dvarString ].value = getDvarInt( dvarString, defaultValue );
	level.watchDvars[ dvarString ].type = "int";
	level.watchDvars[ dvarString ].notifyString = "update_" + nameString;
}


registerWatchDvarFloat( nameString, defaultValue )
{
	dvarString = "scr_" + level.gameType + "_" + nameString;

	level.watchDvars[ dvarString ] = spawnStruct();
	level.watchDvars[ dvarString ].value = getDvarFloat( dvarString, defaultValue );
	level.watchDvars[ dvarString ].type = "float";
	level.watchDvars[ dvarString ].notifyString = "update_" + nameString;
}


registerWatchDvar( nameString, defaultValue )
{
	dvarString = "scr_" + level.gameType + "_" + nameString;

	level.watchDvars[ dvarString ] = spawnStruct();
	level.watchDvars[ dvarString ].value = getDvar( dvarString, defaultValue );
	level.watchDvars[ dvarString ].type = "string";
	level.watchDvars[ dvarString ].notifyString = "update_" + nameString;
}


setOverrideWatchDvar( dvarString, value )
{
	dvarString = "scr_" + level.gameType + "_" + dvarString;
	level.overrideWatchDvars[dvarString] = value;
}


getWatchedDvar( dvarString )
{
	dvarString = "scr_" + level.gameType + "_" + dvarString;
	
	if ( isDefined( level.overrideWatchDvars ) && isDefined( level.overrideWatchDvars[dvarString] ) )
	{
		return level.overrideWatchDvars[dvarString];
	}	
	
	return( level.watchDvars[ dvarString ].value );
}


updateWatchedDvars()
{
	while ( game[ "state" ] == "playing" )
	{
		watchDvars = getArrayKeys( level.watchDvars );

		foreach ( dvarString in watchDvars )
		{
			if ( level.watchDvars[ dvarString ].type == "string" )
				dvarValue = getProperty( dvarString, level.watchDvars[ dvarString ].value );
			else if ( level.watchDvars[ dvarString ].type == "float" )
				dvarValue = getFloatProperty( dvarString, level.watchDvars[ dvarString ].value );
			else
				dvarValue = getIntProperty( dvarString, level.watchDvars[ dvarString ].value );

			if ( dvarValue != level.watchDvars[ dvarString ].value )
			{
				level.watchDvars[ dvarString ].value = dvarValue;
				level notify( level.watchDvars[ dvarString ].notifyString, dvarValue );
			}
		}

		wait( 1.0 );
	}
}


isRoundBased()
{
	if ( !level.teamBased )
		return false;

	if ( getWatchedDvar( "winlimit" ) != 1 && getWatchedDvar( "roundlimit" ) != 1 )
		return true;

	return false;
}


isLastRound()
{
	if ( !level.teamBased )
		return true;

	if ( getWatchedDvar( "roundlimit" ) > 1 && game[ "roundsPlayed" ] >= ( getWatchedDvar( "roundlimit" ) - 1 ) )
		return true;

	if ( getWatchedDvar( "winlimit" ) > 1 && game[ "roundsWon" ][ "allies" ] >= getWatchedDvar( "winlimit" ) - 1 && game[ "roundsWon" ][ "axis" ] >= getWatchedDvar( "winlimit" ) - 1 )
		return true;

	return false;
}


wasOnlyRound()
{
	if ( !level.teamBased )
		return true;
		
	if ( isDefined( level.onlyRoundOverride ) )
		return false;

	if ( getWatchedDvar( "winlimit" ) == 1 && hitWinLimit() )
		return true;

	if ( getWatchedDvar( "roundlimit" ) == 1 )
		return true;

	return false;
}


wasLastRound()
{
	if ( level.forcedEnd )
		return true;

	if ( !level.teamBased )
		return true;

	if ( hitRoundLimit() || hitWinLimit() )
		return true;

	return false;
}


hitRoundLimit()
{
	if ( getWatchedDvar( "roundlimit" ) <= 0 )
		return false;

	return( game[ "roundsPlayed" ] >= getWatchedDvar( "roundlimit" ) );
}


hitScoreLimit()
{
	if ( isObjectiveBased()	 )
		return false;

	if ( getWatchedDvar( "scorelimit" ) <= 0 )
		return false;

	if ( level.teamBased )
	{
		if ( game[ "teamScores" ][ "allies" ] >= getWatchedDvar( "scorelimit" ) || game[ "teamScores" ][ "axis" ] >= getWatchedDvar( "scorelimit" ) )
			return true;
	}
	else
	{
		for ( i = 0; i < level.players.size; i++ )
		{
			player = level.players[ i ];
			if ( isDefined( player.score ) && player.score >= getWatchedDvar( "scorelimit" ) )
				return true;
		}
	}
	return false;
}


hitWinLimit()
{
	if ( getWatchedDvar( "winlimit" ) <= 0 )
		return false;

	if ( !level.teamBased )
		return true;

	if ( getRoundsWon( "allies" ) >= getWatchedDvar( "winlimit" ) || getRoundsWon( "axis" ) >= getWatchedDvar( "winlimit" ) )
		return true;

	return false;
}


getScoreLimit()
{
	if ( isRoundBased() )
	{
		if ( getWatchedDvar( "roundlimit" ) )
			return ( getWatchedDvar( "roundlimit" ) );			
		else
			return ( getWatchedDvar( "winlimit" ) );
	}
	else
	{
		return ( getWatchedDvar( "scorelimit" ) );
	}	
}


getRoundsWon( team )
{
	return game[ "roundsWon" ][ team ];
}


isObjectiveBased()
{
	return level.objectiveBased;
}


getTimeLimit()
{
	if ( inOvertime() && ( !isDefined(game[ "inNukeOvertime" ]) || !game[ "inNukeOvertime" ] ) )
	{
		timeLimit = int( getDvar( "overtimeTimeLimit" ) );
		
		if ( isDefined( timeLimit ) )
			return timeLimit;
		else
			return 1;
	}
	else if ( isDefined(level.dd) && level.dd && isDefined( level.bombexploded ) && level.bombexploded > 0 ) //to handle extra time added by dd bombs
	{
		return ( getWatchedDvar( "timelimit" ) + ( level.bombexploded * level.ddTimeToAdd ) );
	}
	else
	{
		return getWatchedDvar( "timelimit" );
	}
}


getHalfTime()
{
	if ( inOvertime() )
		return false;
	else if ( isDefined( game[ "inNukeOvertime" ] ) && game[ "inNukeOvertime" ] )
		return false;
	else
		return getWatchedDvar( "halftime" );
}


inOvertime()
{
	return ( isDefined( game["status"] ) && game["status"] == "overtime" );
}


gameHasStarted()
{
	if ( level.teamBased )
		return( level.hasSpawned[ "axis" ] && level.hasSpawned[ "allies" ] );
	else
		return( level.maxPlayerCount > 1 );
}


getAverageOrigin( ent_array )
{
	avg_origin = ( 0, 0, 0 );

	if ( !ent_array.size )
		return undefined;

	foreach ( ent in ent_array )
		avg_origin += ent.origin;

	avg_x = int( avg_origin[ 0 ] / ent_array.size );
	avg_y = int( avg_origin[ 1 ] / ent_array.size );
	avg_z = int( avg_origin[ 2 ] / ent_array.size );

	avg_origin = ( avg_x, avg_y, avg_z );

	return avg_origin;
}


getLivingPlayers( team )
{
	player_array = [];

	foreach ( player in level.players )
	{
		if ( !isAlive( player ) )
			continue;

		if ( level.teambased && isdefined( team ) )
		{
			if ( team == player.pers[ "team" ] )
				player_array[ player_array.size ] = player;
		}
		else
		{
			player_array[ player_array.size ] = player;
		}
	}

	return player_array;
}


setUsingRemote( remoteName )
{
	if ( isDefined( self.carryIcon) )
		self.carryIcon.alpha = 0;
	
	assert( !self isUsingRemote() );
	self.usingRemote = remoteName;

	self _disableOffhandWeapons();
	self notify( "using_remote" );
}

getRemoteName()
{
	assert( self isUsingRemote() );
	
	return self.usingRemote;	
}

freezeControlsWrapper( frozen )
{
	if ( isDefined( level.hostMigrationTimer ) )
	{
		self freezeControls( true );
		return;
	}
	
	self freezeControls( frozen );
}


clearUsingRemote()
{
	//if ( !isWeaponEnabled() )
	//	self disableWeapons();

	if ( isDefined( self.carryIcon) )
		self.carryIcon.alpha = 1;

	self.usingRemote = undefined;
	self _enableOffhandWeapons();
	
	curWeapon = self getCurrentWeapon();
	
	if( curWeapon == "none" || isKillstreakWeapon( curWeapon ) )
		self switchToWeapon( self Getlastweapon() );
	
	self freezeControlsWrapper( false );
	
	self notify( "stopped_using_remote" );
}


isUsingRemote()
{
	return( isDefined( self.usingRemote ) );
}


queueCreate( queueName )
{
	if ( !isDefined( level.queues ) )
		level.queues = [];

	assert( !isDefined( level.queues[ queueName ] ) );

	level.queues[ queueName ] = [];
}


queueAdd( queueName, entity )
{
	assert( isDefined( level.queues[ queueName ] ) );
	level.queues[ queueName ][ level.queues[ queueName ].size ] = entity;
}


queueRemoveFirst( queueName )
{
	assert( isDefined( level.queues[ queueName ] ) );

	first = undefined;
	newQueue = [];
	foreach ( element in level.queues[ queueName ] )
	{
		if ( !isDefined( element ) )
			continue;

		if ( !isDefined( first ) )
			first = element;
		else
			newQueue[ newQueue.size ] = element;
	}

	level.queues[ queueName ] = newQueue;

	return first;
}


_giveWeapon( weapon, variant, dualWieldOverRide )
{
	if ( !isDefined(variant) )
		variant = -1;
	
	if ( isSubstr( weapon, "_akimbo" ) || isDefined(dualWieldOverRide) && dualWieldOverRide == true)
		self giveWeapon(weapon, variant, true);
	else
		self giveWeapon(weapon, variant, false);
}

_hasPerk( perkName )
{
	if ( isDefined( self.perks[perkName] ) )
		return true;
	
	return false;
}

/*
============= 
///ScriptDocBegin
"Name: givePerk( <perkName>, <useSlot> )"
"Summary: Gives the perk to the player."
"Module: Player"
"CallOn: A Player"
"MandatoryArg: <perkName> The of the perk from PerkTable.csv."
"MandatoryArg: <useSlot> Boolean, should we put this perk in a perk slot. This should be true if the perks are the CAC selected perks."
"Example: self givePerk( "specialty_pistoldeath", false );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
givePerk( perkName, useSlot )
{
	AssertEx( IsDefined( perkName ), "givePerk perkName not defined and should be" );
	AssertEx( IsDefined( useSlot ), "givePerk useSlot not defined and should be" );
	AssertEx( !IsSubStr( perkName, "specialty_null" ), "givePerk perkName shouldn't be specialty_null, use _clearPerks()s" );

	if ( IsSubStr( perkName, "_mp" ) )
	{
		switch( perkName )
		{
		case "frag_grenade_mp":
			self SetOffhandPrimaryClass( "frag" );
			break;
		case "throwingknife_mp":
			self SetOffhandPrimaryClass( "throwingknife" );
			break;
		case "trophy_mp":
			self SetOffhandSecondaryClass( "flash" );
			break;
		}

		self _giveWeapon( perkName, 0 );
		self giveStartAmmo( perkName );

		self _setPerk( perkName, useSlot );
		return;
	}

	if( IsSubStr( perkName, "specialty_weapon_" ) )
	{
		self _setPerk( perkName, useSlot );
		return;
	}

	self _setPerk( perkName, useSlot );

	self _setExtraPerks( perkName );
}

// please call givePerk
_setPerk( perkName, useSlot )
{
	AssertEx( IsDefined( perkName ), "_setPerk perkName not defined and should be" );
	AssertEx( IsDefined( useSlot ), "_setPerk useSlot not defined and should be" );

	self.perks[ perkName ] = true;

	if ( isDefined( level.perkSetFuncs[perkName] ) )
		self thread [[ level.perkSetFuncs[perkName] ]]();
	
	self setPerk( perkName, !isDefined( level.scriptPerks[perkName] ), useSlot );
}

_setExtraPerks( perkName )
{
	// steady aim will have accurate hip fire and accurate hip fire while moving as the base
	//if( perkName == "specialty_bulletaccuracy" )
	//	self givePerk( "specialty_steadyaimpro", false );
	// assassin will have immune to uav, thermal, and heartbeat sensors on the base
	if( perkName == "specialty_coldblooded" )
		self givePerk( "specialty_heartbreaker", false );
	// blindeye pro gives quicker lockon (perktable) and extra vehicle damage with bullets
	if( perkName == "specialty_fasterlockon" )
		self givePerk( "specialty_armorpiercing", false );
	// assassin pro gives immune to cuav and emp and no red name/crosshair when targeted
	if( perkName == "specialty_spygame" )
		self givePerk( "specialty_empimmune", false );
	// hardline pro gives every two assists count towards a killstreak kill
	if( perkName == "specialty_rollover" )
		self givePerk( "specialty_assists", false );
}

_unsetPerk( perkName )
{
	self.perks[perkName] = undefined;

	if ( isDefined( level.perkUnsetFuncs[perkName] ) )
		self thread [[level.perkUnsetFuncs[perkName]]]();

	self unsetPerk( perkName, !isDefined( level.scriptPerks[perkName] ) );
}

_unsetExtraPerks( perkName )
{
	// steady aim will have accurate hip fire and accurate hip fire while moving as the base
	if( perkName == "specialty_bulletaccuracy" )
		self _unsetPerk( "specialty_steadyaimpro" );
	// assassin will have immune to uav, thermal, and heartbeat sensors on the base
	if( perkName == "specialty_coldblooded" )
		self _unsetPerk( "specialty_heartbreaker" );
	// blindeye pro gives quicker lockon (perktable) and extra vehicle damage with bullets
	if( perkName == "specialty_fasterlockon" )
		self _unsetPerk( "specialty_armorpiercing" );
	// assassin pro gives immune to cuav and emp and no red name/crosshair when targeted
	if( perkName == "specialty_spygame" )
		self _unsetPerk( "specialty_empimmune" );
	// hardline pro gives every two assists count towards a killstreak kill
	if( perkName == "specialty_rollover" )
		self _unsetPerk( "specialty_assists" );
}

_clearPerks()
{
	foreach ( perkName, perkValue in self.perks )
	{
		if ( isDefined( level.perkUnsetFuncs[perkName] ) )
			self [[level.perkUnsetFuncs[perkName]]]();
	}
	
	self.perks = [];
	self clearPerks();
}


// Quick Sort - pass it an array it will come back sorted
quickSort(array) 
{
	return quickSortMid(array, 0, array.size -1 );     
}

quickSortMid(array, start, end)
{
	i = start;
	k = end;

	if (end - start >= 1)
    {
        pivot = array[start];  

        while (k > i)         
        {
	        while (array[i] <= pivot && i <= end && k > i)  
	        	i++;                                 
	        while (array[k] > pivot && k >= start && k >= i) 
	            k--;                                      
	        if (k > i)                                 
	           array = swap(array, i, k);                    
        }
        array = swap(array, start, k);                                               
        array = quickSortMid(array, start, k - 1); 
        array = quickSortMid(array, k + 1, end);   
    }
	else
    	return array;
    
    return array;
}

swap(array, index1, index2) 
{
	temp = array[index1];          
	array[index1] = array[index2];     
	array[index2] = temp;   
	return array;         
}

_suicide()
{
	if ( self isUsingRemote() && !isDefined( self.fauxDead ) )
		self thread maps\mp\gametypes\_damage::PlayerKilled_internal( self, self, self, 10000, "MOD_SUICIDE", "frag_grenade_mp", (0,0,0), "none", 0, 1116, true );
	else if( !self isUsingRemote() && !isDefined( self.fauxDead ) )
		self suicide();	
}

isReallyAlive( player )
{
	if ( isAlive( player ) && !isDefined( player.fauxDead ) )
		return true;
		
	return false;
}

playDeathSound()
{
	rand = RandomIntRange( 1,8 );
	
	if ( self.team == "axis" )
		self PlaySound( "generic_death_russian_"+ rand );	
	else
		self PlaySound( "generic_death_american_"+ rand );
	
}


rankingEnabled()
{
	assert( isPlayer( self ) );
	return ( level.rankedMatch && !self.usingOnlineDataOffline );
}

// only true for private match
privateMatch()
{
	return ( level.onlineGame && getDvarInt( "xblive_privatematch" ) );
}

// only true for playlist based LIVE and PSN games
matchMakingGame()
{
	return ( level.onlineGame && !getDvarInt( "xblive_privatematch" ) );
}

setAltSceneObj( object, tagName, fov, forceLink )
{
	/*
	if ( !isDefined( forceLink ) )
		forceLink = false;

	if ( !getDvarInt( "scr_pipmode" ) && !forceLink )
		return;
	
	self endon ( "disconnect" );

	if ( !isReallyAlive( self ) )
		return;

	if ( !forceLink && isDefined( self.altSceneObject ) )
		return;

	self notify ( "altscene" );
	
	self.altSceneObject = object;

	self AlternateSceneCameraLinkTo( object, tagName, fov );
	self setClientDvar( "ui_altscene", 1 );
	
	self thread endSceneOnDeath( object );
	self thread endSceneOnDeath( self );
	
	self waittill ( "end_altScene" );
	
	self.altSceneObject = undefined;
	self AlternateSceneCameraUnlink();
	
	if ( !forceLink )
	{
		self setClientDvar( "ui_altscene", 2 );
	
		self endon ( "altscene" );
		wait ( 2.0 );
	}
	self setClientDvar( "ui_altscene", 0 );	
	*/
}


endSceneOnDeath( object )
{
	self endon ( "altscene" );
	
	object waittill ( "death" );
	self notify ( "end_altScene" );
}


getGametypeNumLives()
{
	//commented out to allow diehardhard rules to support mulitiple life gametypes
	//if ( level.dieHardMode && !getWatchedDvar( "numlives" ) )
	//	return 1;
	//else
		return getWatchedDvar( "numlives" );
}


giveCombatHigh( combatHighName )
{
	self.combatHigh = combatHighName;
}


arrayInsertion( array, item, index )
{
	if ( array.size != 0 )
	{
		for ( i = array.size; i >= index; i-- )
		{
			array[i+1] = array[i];
		}
	}
	
	array[index] = item;
}


getProperty( dvar, defValue )
{
	value = defValue;
	/#
	setDevDvarIfUninitialized( dvar, defValue );
	#/

	value = getDvar( dvar, defValue );
	return value;
}


getIntProperty( dvar, defValue )
{
	value = defValue;

	/#
	setDevDvarIfUninitialized( dvar, defValue );
	#/

	value = getDvarInt( dvar, defValue );
	return value;
}


getFloatProperty( dvar, defValue )
{
	value = defValue;
	/#
	setDevDvarIfUninitialized( dvar, defValue );
	#/

	value = getDvarFloat( dvar, defValue );
	return value;
}



statusMenu( duration )
{
	self endon ( "disconnect" );
	
	if ( !isDefined( self._statusMenu ) )
		self.statusMenu = false;
		
	if ( self.statusMenu )
		return;

	self.statusMenu = true;

	self openpopupMenu( "status_update" );
	
	wait ( duration );

	self closepopupMenu( "status_update" );

	// debounce
	wait ( 10.0 );
	
	self.statusMenu = false;	
}

isChangingWeapon()
{
	return ( isDefined( self.changingWeapon ) );
}

killShouldAddToKillstreak( weapon )
{	
	if ( self _hasPerk( "specialty_explosivebullets" ) )	
		return false;	
		
	if ( IsDefined( self.isJuggernautRecon ) && self.isJuggernautRecon == true )
		return false;
		
	//	allow only these killstreaks
	if ( IsDefined( level.killstreakChainingWeapons[weapon] ) )	
	{
		//	only if it came from an earn slot (1-3, 0 is gimme slot, 4 or more is stacked in the gimme slot)
		for( i = KILLSTREAK_SLOT_1; i < KILLSTREAK_SLOT_3 + 1; i++ )
		{
			// only if it was earned this life
			if( IsDefined( self.pers["killstreaks"][i] ) && 
				IsDefined( self.pers["killstreaks"][i].streakName ) &&
				self.pers["killstreaks"][i].streakName == level.killstreakChainingWeapons[weapon] && 
				IsDefined( self.pers["killstreaks"][i].lifeId ) && 
				self.pers["killstreaks"][i].lifeId == self.pers["deaths"] )
			{
				return self streakShouldChain( level.killstreakChainingWeapons[weapon] );
			}
		}		
		return false;
	}
		
	return !isKillstreakWeapon( weapon );	
}


streakShouldChain( streakName )
{
	currentStreakCost = maps\mp\killstreaks\_killstreaks::getStreakCost( streakName );
	nextStreakName = maps\mp\killstreaks\_killstreaks::getNextStreakName();
	nextStreakCost = maps\mp\killstreaks\_killstreaks::getStreakCost( nextStreakName );
	
	return ( currentStreakCost < nextStreakCost ); 
}


/*
============= 
///ScriptDocBegin
"Name: isJuggernaut()"
"Summary: Returns if the player is a juggernaut or not."
"Module: Player"
"CallOn: player"
"Example: if( player isJuggernaut() )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isJuggernaut()
{
	if ( ( isDefined( self.isJuggernaut ) && self.isJuggernaut == true ) )
		return true;

	if ( ( isDefined( self.isJuggernautDef ) && self.isJuggernautDef == true ) )
		return true;
	
	if ( ( isDefined( self.isJuggernautGL ) && self.isJuggernautGL == true ) )
		return true;
		
	if ( ( isDefined( self.isJuggernautRecon ) && self.isJuggernautRecon == true ) )
		return true;	
	
	return false;	
}


/*
============= 
///ScriptDocBegin
"Name: isKillstreakWeapon( <weapon> )"
"Summary: Returns if this is a killstreak weapon or not."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapon> The name of the weapon to check."
"Example: if( isKillstreakWeapon( sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isKillstreakWeapon( weapon )
{
	if( !IsDefined( weapon ) )
	{
		AssertMsg( "isKillstreakWeapon called without a weapon name passed in" );
		return false;
	}

	if ( weapon == "none" )
		return false;
	
	tokens = strTok( weapon, "_" );
	foundSuffix = false;
	
	//this is necessary because of weapons potentially named "_mp(somthign)" like the mp5
	if( weapon != "destructible_car" && weapon != "barrel_mp" )
	{
		foreach(token in tokens)
		{
			if( token == "mp" )
			{
				foundSuffix = true;
				break;
			}
		}
		
		if ( !foundSuffix )
		{
			weapon += "_mp";
		}
	}
	
	/*UGLY HACK REMOVE THIS BEFORE SHIPPING AND PROPERLY CACHE AKIMBO WEAPONS
	if ( isSubstr( weapon, "akimbo" ) )
		return false;
	*/
	
	if ( isSubStr( weapon, "destructible" ) )
		return false;

	if ( isSubStr( weapon, "killstreak" ) )
		return true;
	
	if ( maps\mp\killstreaks\_airdrop::isAirdropMarker( weapon ) )
		return true;

	if ( isDefined( level.killstreakWeildWeapons[weapon] ) )
		return true;

	if ( IsDefined( weaponInventoryType( weapon ) ) && weaponInventoryType( weapon ) == "exclusive" && ( weapon != "destructible_car" && weapon != "barrel_mp" ) )
		return true;
			
	return false;
}

/*
============= 
///ScriptDocBegin
"Name: isEnvironmentWeapon( <weapon> )"
"Summary: Returns if this is an environment weapon or not, like a turret in the map."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapon> The name of the weapon to check."
"Example: if( isEnvironmentWeapon( sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isEnvironmentWeapon( weapon )
{
	if( !IsDefined( weapon ) )
	{
		AssertMsg( "isEnvironmentWeapon called without a weapon name passed in" );
		return false;
	}

	if( weapon == "turret_minigun_mp" )
		return true;

	if( isSubStr( weapon, "_bipod_" ) )
		return true;

	return false;
}

/*
============= 
///ScriptDocBegin
"Name: getWeaponClass( <weapon> )"
"Summary: Returns the class of the weapon passed in."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapon> The name of the weapon to check."
"Example: weaponClass = getWeaponClass( sWeapon );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
getWeaponClass( weapon )
{
	tokens = strTok( weapon, "_" );
	
	if ( tokens[0] == "iw5" )
	{
		concatName = tokens[0] + "_" + tokens[1];
		weaponClass = tablelookup( "mp/statstable.csv", 4, concatName, 2 );
	}
	else if ( tokens[0] == "alt" )
	{
		concatName = tokens[1] + "_" + tokens[2];
		weaponClass = tablelookup( "mp/statstable.csv", 4, concatName, 2 );
	}
	else
	{
		weaponClass = tablelookup( "mp/statstable.csv", 4, tokens[0], 2 );
	}
		
	// handle special case weapons like grenades, airdrop markers, etc...
	if ( weaponClass == "" )
	{
		weaponName = strip_suffix( weapon, "_mp" );
		weaponClass = tablelookup( "mp/statstable.csv", 4, weaponName, 2 );
	}
	
	if ( isEnvironmentWeapon( weapon ) )
		weaponClass = "weapon_mg";
	else if ( isKillstreakWeapon( weapon ) )
		weaponClass = "killstreak"; 
	else if ( isDeathStreakWeapon( weapon ) )
		weaponClass = "deathstreak";
	else if ( weapon == "none" ) //airdrop crates
		weaponClass = "other";
	else if ( weaponClass == "" )
		weaponClass = "other";
	
	assertEx( weaponClass != "", "ERROR: invalid weapon class for weapon " + weapon );
	
	return weaponClass;
}

/*
============= 
///ScriptDocBegin
"Name: isDeathStreakWeapon( <weapon> )"
"Summary: Returns if this is a deathstreak weapon or not."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapon> The name of the weapon to check."
"Example: if( isDeathStreakWeapon( sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isDeathStreakWeapon( weapon )
{
	if( weapon == "c4death_mp" || weapon == "frag_grenade_short_mp" )
		return true;
	else
		return false;
}

getBaseWeaponName( weaponName )
{
	tokens = strTok( weaponName, "_" );
	
	if ( tokens[0] == "iw5" )
		tokens[0] = tokens[0] + "_" + tokens[1];
	else if( tokens[0] == "alt" )
		tokens[0] = tokens[1] + "_" + tokens[2];
	
	return tokens[0];
}

fixAkimboString( weaponName, append )
{
	if( !isDefined( append ) )
		append = true;
	
	startIndex = 0;
	for( i = 0; i < weaponName.size; i++ )
	{
		if ( weaponName[i] == "a" && weaponName[i+1] == "k" && weaponName[i+2] == "i" && weaponName[i+3] == "m" && weaponName[i+4] == "b" && weaponName[i+5] == "o" )
		{
			startIndex = i;
			break;
		}
	}
	
	weaponName = GetSubStr( weaponName, 0, startIndex ) + GetSubStr( weaponName, startIndex+6, weaponName.size );
	
	if ( append )
		weaponName += "_akimbo";
	
	return weaponName;
}

playSoundinSpace( alias, origin )
{
	playSoundAtPos( origin, alias );
}

limitDecimalPlaces( value, places )
{
	modifier = 1;
	for ( i = 0; i < places; i++ )
		modifier *= 10;
	
	newvalue = value * modifier;
	newvalue = Int( newvalue );
	newvalue = newvalue / modifier;
	
	return newvalue;
}

roundDecimalPlaces( value, places, style )
{
	if ( !isdefined( style ) )
		style = "nearest";
	
	modifier = 1;
	for ( i = 0; i < places; i++ )
		modifier *= 10;
	
	newValue = value * modifier;
	
	if ( style == "up" )
		roundedValue = ceil( newValue );
	else if ( style == "down" )
		roundedValue = floor( newValue ); 	
	else
		roundedValue = newvalue + 0.5;	
		
	newvalue = Int( roundedValue );
	newvalue = newvalue / modifier;
	
	return newvalue;
}

playerForClientId( clientId )
{
	foreach ( player in level.players )
	{
		if ( player.clientId == clientId )
			return player;
	}
	
	return undefined;
}

isRested()
{
	if ( !self rankingEnabled() )
		return false;
		
	return ( self getPlayerData( "restXPGoal" ) > self getPlayerData( "experience" ) );
}

stringToFloat( stringVal )
{
	floatElements = strtok( stringVal, "." );
	
	floatVal = int( floatElements[0] );
	if ( isDefined( floatElements[1] ) )
	{
		modifier = 1;
		for ( i = 0; i < floatElements[1].size; i++ )
			modifier *= 0.1;
		
		floatVal += int ( floatElements[1] ) * modifier;
	}
	
	return floatVal;	
}

setSelfUsable(caller)
{
	self makeUsable();
	
	foreach (player in level.players)
	{
		if (player != caller )
			self disablePlayerUse( player );
		else
			self enablePlayerUse( player );
	}
}

makeTeamUsable( team )
{
	self makeUsable();
	self thread _updateTeamUsable( team );
}

_updateTeamUsable( team )
{
	self endon ( "death" );
	
	for ( ;; )
	{
		foreach (player in level.players)
		{
			if ( player.team == team )
				self enablePlayerUse( player );	
			else
				self disablePlayerUse( player );	
		}	

		level waittill ( "joined_team" );		
	}
}

// More general version of makeTeamUsable() which handles FFA
makeEnemyUsable( owner )
{
	self makeUsable();
	self thread _updateEnemyUsable( owner );
}

// Only used for Tactical Insertion for now
// If used for other things, handle owner disappearing or changing team
_updateEnemyUsable( owner )
{
	// check what happens if the owner leaves

	self endon ( "death" );

	team = owner.team;

	for ( ;; )
	{
		if ( level.teambased )
		{
			foreach (player in level.players)
			{
				if ( player.team != team )
					self enablePlayerUse( player );	
				else
					self disablePlayerUse( player );	
			}
		}
		else
		{
			foreach (player in level.players)
			{
				if ( player != owner )
					self enablePlayerUse( player );	
				else
					self disablePlayerUse( player );	
			}
		}

		level waittill ( "joined_team" );		
	}
}

getNextLifeId()
{
	lifeId = getMatchData( "lifeCount" );
	if ( lifeId < level.MaxLives )
		setMatchData( "lifeCount", lifeId+1 );
		
	return ( lifeId );
}

initGameFlags()
{
	if ( !isDefined( game["flags"] ) )
		game["flags"] = [];
}

gameFlagInit( flagName, isEnabled )
{
	assert( isDefined( game["flags"] ) );
	game["flags"][flagName] = isEnabled;
}

gameFlag( flagName )
{
	assertEx( isDefined( game["flags"][flagName] ), "gameFlag " + flagName + " referenced without being initialized; usegameFlagInit( <flagName>, <isEnabled> )" );
	return ( game["flags"][flagName] );
}

gameFlagSet( flagName )
{
	assertEx( isDefined( game["flags"][flagName] ), "gameFlag " + flagName + " referenced without being initialized; usegameFlagInit( <flagName>, <isEnabled> )" );
	game["flags"][flagName] = true;

	level notify ( flagName );
}

gameFlagClear( flagName )
{
	assertEx( isDefined( game["flags"][flagName] ), "gameFlag " + flagName + " referenced without being initialized; usegameFlagInit( <flagName>, <isEnabled> )" );
	game["flags"][flagName] = false;
}

gameFlagWait( flagName )
{
	assertEx( isDefined( game["flags"][flagName] ), "gameFlag " + flagName + " referenced without being initialized; usegameFlagInit( <flagName>, <isEnabled> )" );
	while ( !gameFlag( flagName ) )
		level waittill ( flagName );
}

// NOTE: this already exists in code IsExplosiveDamageMOD()
//// including grenade launcher, grenade, RPG, C4, claymore
//isExplosiveDamage( meansofdeath )
//{
//	explosivedamage = "MOD_GRENADE MOD_GRENADE_SPLASH MOD_PROJECTILE MOD_PROJECTILE_SPLASH MOD_EXPLOSIVE mod_explosive MOD_EXPLOSIVE_BULLET";
//	if( isSubstr( explosivedamage, meansofdeath ) )
//		return true;
//	return false;
//}

// if primary weapon damage
isPrimaryDamage( meansofdeath )
{
	// including pistols as well since sometimes they share ammo
	if( meansofdeath == "MOD_RIFLE_BULLET" || meansofdeath == "MOD_PISTOL_BULLET" )
		return true;
	return false;
}

// either this or primary need to go away, or primary do an extra check???
isBulletDamage( meansofdeath )
{
	bulletDamage = "MOD_RIFLE_BULLET MOD_PISTOL_BULLET MOD_HEAD_SHOT";
	if( isSubstr( bulletDamage, meansofdeath ) )
		return true;
	return false;
}

initLevelFlags()
{
	if ( !isDefined( level.levelFlags ) )
		level.levelFlags = [];
}

levelFlagInit( flagName, isEnabled )
{
	assert( isDefined( level.levelFlags ) );
	level.levelFlags[flagName] = isEnabled;
}

levelFlag( flagName )
{
	assertEx( isDefined( level.levelFlags[flagName] ), "levelFlag " + flagName + " referenced without being initialized; use levelFlagInit( <flagName>, <isEnabled> )" );
	return ( level.levelFlags[flagName] );
}

levelFlagSet( flagName )
{
	assertEx( isDefined( level.levelFlags[flagName] ), "levelFlag " + flagName + " referenced without being initialized; use levelFlagInit( <flagName>, <isEnabled> )" );
	level.levelFlags[flagName] = true;

	level notify ( flagName );
}

levelFlagClear( flagName )
{
	assertEx( isDefined( level.levelFlags[flagName] ), "levelFlag " + flagName + " referenced without being initialized; use levelFlagInit( <flagName>, <isEnabled> )" );
	level.levelFlags[flagName] = false;

	level notify ( flagName );
}

levelFlagWait( flagName )
{
	assertEx( isDefined( level.levelFlags[flagName] ), "levelFlag " + flagName + " referenced without being initialized; use levelFlagInit( <flagName>, <isEnabled> )" );
	while ( !levelFlag( flagName ) )
		level waittill ( flagName );
}

levelFlagWaitOpen( flagName )
{
	assertEx( isDefined( level.levelFlags[flagName] ), "levelFlag " + flagName + " referenced without being initialized; use levelFlagInit( <flagName>, <isEnabled> )" );
	while ( levelFlag( flagName ) )
		level waittill ( flagName );
}

getWeaponAttachments( weapon ) 
{
	tokenizedWeapon = strTok( weapon, "_" );
	attachmentArray = [];
	
	// right now weapon names are formatted like this iw5_baseweapon_mp_attachment1_attachment2 or alt_iw5_baseweapon_attachment1_attachment2
	foreach( token in tokenizedWeapon )
	{
		if ( isSubStr( token, "scopevz" ) )
			attachmentArray[ attachmentArray.size ] = "vzscope";
		
		if( maps\mp\gametypes\_class::isValidAttachment( token, false ) )
			attachmentArray[ attachmentArray.size ] = token;
	}

	return attachmentArray;
}

isEMPed()
{
	if ( self.team == "spectator" )
		return false;
		
	if ( level.teamBased )
    {
    	return ( level.teamEMPed[self.team] || ( isDefined( self.empGrenaded ) && self.empGrenaded ) || level.teamNukeEMPed[self.team] );
    }
    else
    {
    	return ( ( isDefined( level.empPlayer ) && level.empPlayer != self ) || ( isDefined( self.empGrenaded ) && self.empGrenaded ) || ( IsDefined( level.nukeInfo.player ) && self != level.nukeInfo.player && level.teamNukeEMPed[ self.team ] ) );
	}
}

isAirDenied()
{
	return false;

	// old aastrike stuff
	//if ( self.team == "spectator" )
	//	return false;
	//	
 //   if ( level.teamBased )
 //   	return ( level.teamAirDenied[self.team] );
 //   else
 //   	return ( isDefined( level.airDeniedPlayer ) && level.airDeniedPlayer != self );
}

isNuked()
{
	if ( self.team == "spectator" )
		return false;
		
    return ( isDefined( self.nuked ) );
}

getPlayerForGuid( guid )
{
	foreach ( player in level.players )
	{
		if ( player.guid == guid )
			return player;
	}
	
	return undefined;
}

/*
============= 
///ScriptDocBegin
"Name: teamPlayerCardSplash( <splash>, <owner>, <team> )"
"Summary: Shows the player card splash to the team."
"Module: Utility"
"CallOn: Level"
"MandatoryArg: <splash> The splash to show from splashtable.csv."
"MandatoryArg: <owner> The owner of the splash, or who called the killstreak."
"OptionalArg: <team> The team to show the splash to, if undefined then it shows to everyone."
"Example: thread teamPlayerCardSplash( "used_ac130", player, player.team );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
teamPlayerCardSplash( splash, owner, team )
{
	if ( level.hardCoreMode )
		return;
		
	foreach ( player in level.players )
	{
		if ( isDefined( team ) && player.team != team )
			continue;
			
		player thread maps\mp\gametypes\_hud_message::playerCardSplashNotify( splash, owner );
	}
}
	

/*
============= 
///ScriptDocBegin
"Name: isCACPrimaryWeapon( <weapName> )"
"Summary: Returns true if the passed in weapon name is in one of the primary weapon classes."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapName> The name of the weapon to check."
"Example: if( isCACPrimaryWeapon( sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isCACPrimaryWeapon( weapName )
{
	switch ( getWeaponClass( weapName ) )
	{
		case "weapon_smg":
		case "weapon_assault":
		case "weapon_riot":
		case "weapon_sniper":
		case "weapon_lmg":
		case "weapon_shotgun":
			return true;
		default:
			return false;
	}
}


/*
============= 
///ScriptDocBegin
"Name: isCACSecondaryWeapon( <weapName> )"
"Summary: Returns true if the passed in weapon name is in one of the secondary weapon classes."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <weapName> The name of the weapon to check."
"Example: if( isCACSecondaryWeapon( sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isCACSecondaryWeapon( weapName )
{
	switch ( getWeaponClass( weapName ) )
	{
		case "weapon_projectile":
		case "weapon_pistol":
		case "weapon_machine_pistol":
			return true;
		default:
			return false;
	}
}


getLastLivingPlayer( team )
{
	livePlayer = undefined;

	foreach ( player in level.players )
	{
		if ( isDefined( team ) && player.team != team )
			continue;

		if ( !isReallyAlive( player ) && !player maps\mp\gametypes\_playerlogic::maySpawn() )
			continue;
		
		assertEx( !isDefined( livePlayer ), "getLastLivingPlayer() found more than one live player on team." );
		
		livePlayer = player;				
	}

	return livePlayer;
}


getPotentialLivingPlayers()
{
	livePlayers = [];

	foreach ( player in level.players )
	{
		if ( !isReallyAlive( player ) && !player maps\mp\gametypes\_playerlogic::maySpawn() )
			continue;
		
		livePlayers[livePlayers.size] = player;
	}

	return livePlayers;
}


waitTillRecoveredHealth( time, interval )
{
	self endon("death");
	self endon("disconnect");

	fullHealthTime = 0;
	
	if( !isDefined( interval ) )
		interval = .066;

	if( !isDefined( time ) )
		time = 0;
	
	while(1)
	{
		if ( self.health != self.maxhealth )
			fullHealthTime = 0;
		else
			fullHealthTime += interval;
		
		wait interval;
		
		if ( self.health == self.maxhealth && fullHealthTime >= time )
			break;
	}

	return;
}

attachmentMap( attachmentName, weaponName )
{
	weaponClass = tablelookup( "mp/statstable.csv", 4, weaponName, 2 );
	switch( weaponClass )
	{
		case "weapon_smg":
			if ( attachmentName == "reflex" )
				return "reflexsmg";
			else if ( attachmentName == "eotech" )
				return "eotechsmg";
			else if ( attachmentName == "acog" )
				return "acogsmg";
			else if ( attachmentName == "thermal" )
				return "thermalsmg";
		case "weapon_lmg":
			if ( attachmentName == "reflex" )
				return "reflexlmg";
			else if ( attachmentName == "eotech" )
				return "eotechlmg";
		case "weapon_machine_pistol":
			if ( attachmentName == "reflex" )
				return "reflexsmg";
			else if ( attachmentName == "eotech" )
				return "eotechsmg";
		default:
			return attachmentName;
	}
}

validateAttachment( attachmentName )
{
	switch ( attachmentName )
	{
		case "silencer02":
		case "silencer03":
			return "silencer";
		case "gp25":
		case "m320":
			return "gl";
		case "reflexsmg":
		case "reflexlmg":
			return "reflex";
		case "eotechsmg":
		case "eotechlmg":
			return "eotech";
		case "acogsmg":
			return "acog";
		case "thermalsmg":
			return "thermal";
		default:
			return attachmentName;
	}
}

_objective_delete( objID )
{
	objective_delete( objID);
	
	if ( !isDefined( level.reclaimedReservedObjectives ) ) 
	{
		level.reclaimedReservedObjectives = [];
		level.reclaimedReservedObjectives[0] = objID;
	}
	else
	{
		level.reclaimedReservedObjectives[ level.reclaimedReservedObjectives.size ] = objID;		
	}
}


touchingBadTrigger()
{
	killTriggers = getEntArray( "trigger_hurt", "classname" );	
	foreach ( trigger in killTriggers )
	{
		if ( self isTouching( trigger ) )
			return true;
	}

	radTriggers = getEntArray( "radiation", "targetname" );	
	foreach ( trigger in radTriggers )
	{
		if ( self isTouching( trigger ) )
			return true;
	}
	
	return false;
}
	
setThirdPersonDOF( isEnabled )
{
	if ( isEnabled )
		self setDepthOfField( 0, 110, 512, 4096, 6, 1.8 );
	else
		self setDepthOfField( 0, 0, 512, 512, 4, 0 );
}



killTrigger( pos, radius, height )
{
	trig = spawn( "trigger_radius", pos, 0, radius, height );
	
	/#
	if ( getdvar( "scr_killtriggerdebug" ) == "1" )
		thread killTriggerDebug( pos, radius, height );
	#/
	
	for ( ;; )
	{
		/#
		if ( getdvar( "scr_killtriggerradius" ) != "" )
			radius = int(getdvar( "scr_killtriggerradius" ));
		#/
		
		trig waittill( "trigger", player );
		
		if ( !isPlayer( player ) )
			continue;
		
		player suicide();
	}
}

findIsFacing( ent1, ent2, tolerance )//finds if ent1 is facing ent2
{
	facingCosine = Cos( tolerance );
	//facingCosine = .90630778703664996324255265675432; //tolerance = 25;
		
	ent1ForwardVector = anglesToForward( ent1.angles );
	ent1ToTarget = ent2.origin - ent1.origin;
	ent1ForwardVector *= (1,1,0);
	ent1ToTarget *= (1,1,0 );
	
	ent1ToTarget = VectorNormalize( ent1ToTarget );
	ent1ForwardVector = VectorNormalize( ent1ForwardVector );
	
	targetCosine = VectorDot( ent1ToTarget, ent1ForwardVector );
	
	if ( targetCosine >= facingCosine )
		return true;
	else
		return false;
}

combineArrays( array1, array2 ) 
{
	assert( isDefined( array1 ) || isDefined( array2 ) );
	
	if ( !isDefined( array1 ) && isDefined(array2 ) )
		return array2;

	if ( !isDefined( array2 ) && isDefined(array1 ) )
		return array1;
		
	foreach ( elem in array2 )
	{
		array1[array1.size] = elem;
	}
	
	return array1;
}


/*setRecoilScale sets a relative recoil scaler 
  if you pass 20 it will be a 20% reduction in recoil 
  passing it no values will reset scale override to whatever
  value already exists in self.recoilScale or no override.
*/
setRecoilScale( scaler, scaleOverride )
{	
	if ( !isDefined( scaler ) )
		scaler = 0;
	
	if ( !isDefined( self.recoilScale ) )
		self.recoilScale = scaler;
	else
		self.recoilScale += scaler;
	
	//for scale override
	if ( isDefined( scaleOverride ) )
	{		
		//will not override a lower value.
		if ( isDefined( self.recoilScale) && scaleOverride < self.recoilScale )
			scaleOverride = self.recoilScale;	
		
		scale = 100 - scaleOverride;
	}
	else
		scale = 100 - self.recoilScale;
	
	if ( scale < 0 )
		scale = 0;
	
	if ( scale > 100 )
		scale = 100;	
	
	if ( scale == 100 )
	{
		self player_recoilScaleOff();
		return;
	}
	
	self player_recoilScaleOn( scale );
}

 
//Remove undefined and reorders elements
//preserves index
cleanArray( array )
{
	newArray = [];
	
	foreach ( key, elem in array )
	{
		if ( !isdefined( elem ) )
			continue;
			
		newArray[ newArray.size ] = array[ key ];
	}

	return newArray;
}

/#
killTriggerDebug( pos, radius, height )
{
	for ( ;; )
	{
		for ( i = 0; i < 20; i++ )
		{
			angle = i / 20 * 360;
			nextangle = (i+1) / 20 * 360;
			
			linepos = pos + (cos(angle) * radius, sin(angle) * radius, 0);
			nextlinepos = pos + (cos(nextangle) * radius, sin(nextangle) * radius, 0);
			
			line( linepos, nextlinepos );
			line( linepos + (0,0,height), nextlinepos + (0,0,height) );
			line( linepos, linepos + (0,0,height) );
		}
		wait .05;
	}
}
#/

/*
============= 
///ScriptDocBegin
"Name: notUsableForJoiningPlayers( <player> )"
"Summary:  Makes sure newly joining players can't use already deployed equipment."
"Module: Entity"
"CallOn: An Entity"
"MandatoryArg: <player> The owner of the device."
"Example: self thread notUsableForJoiningPlayers( owner );
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
notUsableForJoiningPlayers( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	owner endon ( "death" );

	// as players join they need to be set to not be able to use this
	while( true )
	{
		level waittill( "player_spawned", player );
		if( IsDefined( player ) && player != owner )
		{
			self disablePlayerUse( player );
		}
	}
}

/*
============= 
///ScriptDocBegin
"Name: isStrStart( <string>, <subStr> )"
"Summary:  Returns true or false if the strings starts with the sub string passed in."
"Module: Utility"
"CallOn: None"
"MandatoryArg: <string> The base string to check against."
"MandatoryArg: <subStr> The sub string to check for."
"Example: if( isStrStart( sWeapon, "gl_" ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isStrStart( string, subStr )
{
	return ( GetSubStr( string, 0, subStr.size ) == subStr );
}

validateUseStreak()
{
	if ( isDefined( self.lastStand ) && !self _hasPerk( "specialty_finalstand" ) )
	{
		self iPrintLnBold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return false;
	}
	else if ( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
		return false;
	}
	else if ( self isUsingRemote() )
	{
		return false;
	}
	else if ( self isEMPed() )
	{
		return false;
	}
	else 
		return true;
}

/*
============= 
///ScriptDocBegin
"Name: currentActiveVehicleCount( <extra> )"
"Summary:  Returns the count of active vehicles currently in the match."
"OptionalArg: <extra> The number of extra vehicles to add on to the count."
"Module: Utility"
"CallOn: None"
"Example: if( currentActiveVehicleCount( level.fauxVehicleCount ) > 8 )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
currentActiveVehicleCount( extra )
{
	if( !IsDefined( extra ) )
		extra = 0;

	count = extra;
	if( IsDefined( level.helis ) )
		count += level.helis.size;
	if( IsDefined( level.littleBirds ) )
		count += level.littleBirds.size;
	if( IsDefined( level.ugvs ) )
		count += level.ugvs.size;

	return count;
}

/*
============= 
///ScriptDocBegin
"Name: maxVehiclesAllowed()"
"Summary:  Returns the number of max vehicles allowed at once in a match."
"Module: Utility"
"CallOn: None"
"Example: if( currentActiveVehicleCount() > maxVehiclesAllowed() )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
maxVehiclesAllowed()
{
	return MAX_VEHICLES;
}

/*
============= 
///ScriptDocBegin
"Name: incrementFauxVehicleCount()"
"Summary:  Increments the level.fauxVehicleCount variable."
"Module: Utility"
"CallOn: None"
"Example: incrementFauxVehicleCount();
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
incrementFauxVehicleCount()
{
	level.fauxVehicleCount++;
}

/*
============= 
///ScriptDocBegin
"Name: decrementFauxVehicleCount()"
"Summary:  Decrements the level.fauxVehicleCount variable."
"Module: Utility"
"CallOn: None"
"Example: decrementFauxVehicleCount();
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
decrementFauxVehicleCount()
{
	level.fauxVehicleCount--;
	if( level.fauxVehicleCount < 0 )
		level.fauxVehicleCount = 0;
}

/*
============= 
///ScriptDocBegin
"Name: lightWeightScalar()"
"Summary:  Returns the movement speed scalar value for Lightweight."
"Module: Utility"
"CallOn: None"
"Example: self.moveSpeedScaler = lightWeightScalar();
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
lightWeightScalar()
{
	return LIGHTWEIGHT_SCALAR;
}

allowTeamChoice()
{
	allowed = int( tableLookup( "mp/gametypesTable.csv", 0, level.gameType, 4 ) );
	assert( isDefined( allowed ) );
	
	return allowed;
}

allowClassChoice()
{
	allowed = int( tableLookup( "mp/gametypesTable.csv", 0, level.gameType, 5 ) );
	assert( isDefined( allowed ) );
	
	return allowed;	
}

/*
============= 
///ScriptDocBegin
"Name: isBuffUnlockedForWeapon( <buffRef>, <weaponRef> )"
"Summary: Returns true if the weapon buff is unlocked for this weapon."
"Module: Utility"
"CallOn: player"
"MandatoryArg: <buffRef> The name of the weapon buff to check."
"MandatoryArg: <weaponRef> The name of the weapon to check."
"Example: if( isBuffUnlockedForWeapon( "specialty_bulletpenetration", sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isBuffUnlockedForWeapon( buffRef, weaponRef )
{
	WEAPON_RANK_TABLE_LEVEL_COL	=				4;
	WEAPON_RANK_TABLE_WEAPONCLASS_COL =			0;
	WEAPON_RANK_TABLE_WEAPONCLASS_BUFF_COL =	4;

	weaponRank = self GetPlayerData( "weaponRank", weaponRef );
	rankTableBuffCol = int( tableLookup( "mp/weaponRankTable.csv", WEAPON_RANK_TABLE_WEAPONCLASS_COL, getWeaponClass( weaponRef ), WEAPON_RANK_TABLE_WEAPONCLASS_BUFF_COL ) );
	rankTableBuffLevel = tableLookup( "mp/weaponRankTable.csv", rankTableBuffCol, buffRef, WEAPON_RANK_TABLE_LEVEL_COL );
	
	if( rankTableBuffLevel != "" )
	{
		if( weaponRank >= int( rankTableBuffLevel ) )
			return true;
	}

	return false;
}

/*
============= 
///ScriptDocBegin
"Name: isBuffEquippedOnWeapon( <buffRef>, <weaponRef> )"
"Summary: Returns true if the weapon buff is equipped on this weapon."
"Module: Utility"
"CallOn: player"
"MandatoryArg: <buffRef> The name of the weapon buff to check."
"MandatoryArg: <weaponRef> The name of the weapon to check."
"Example: if( isBuffEquippedOnWeapon( "specialty_bulletpenetration", sWeapon ) )
"SPMP: multiplayer"
///ScriptDocEnd
============= 
*/
isBuffEquippedOnWeapon( buffRef, weaponRef )
{
	if( IsDefined( self.loadoutPrimary ) && self.loadoutPrimary == weaponRef )
	{
		if( IsDefined( self.loadoutPrimaryBuff ) && self.loadoutPrimaryBuff == buffRef )
			return true;
	}
	else if( IsDefined( self.loadoutSecondary ) && self.loadoutSecondary == weaponRef )
	{
		if( IsDefined( self.loadoutSecondaryBuff ) && self.loadoutSecondaryBuff == buffRef )
			return true;
	}

	return false;
}


setCommonRulesFromMatchRulesData( skipFriendlyFire )
{
	//	game options
	timeLimit = GetMatchRulesData( "commonOption", "timeLimit" );
	SetDynamicDvar( "scr_" + level.gameType + "_timeLimit", timeLimit );
	registerTimeLimitDvar( level.gameType, timeLimit );
	
	scoreLimit = GetMatchRulesData( "commonOption", "scoreLimit" );
	SetDynamicDvar( "scr_" + level.gameType + "_scoreLimit", scoreLimit );
	registerScoreLimitDvar( level.gameType, scoreLimit );
	
	//	player options
	numLives = GetMatchRulesData( "commonOption", "numLives" );
	SetDynamicDvar( "scr_" + level.gameType + "_numLives", numLives );
	registerNumLivesDvar( level.gameType, numLives );
	
	SetDynamicDvar( "scr_player_maxhealth", GetMatchRulesData( "commonOption", "maxHealth" ) );
	SetDynamicDvar( "scr_player_healthregentime", GetMatchRulesData( "commonOption", "healthRegen" ) );
	
	//	cut for MW3
	//level.matchRules_damageMultiplier = GetMatchRulesData( "commonOption", "damageMultiplier" );
	//level.matchRules_vampirism = GetMatchRulesData( "commonOption", "vampirism" );
	level.matchRules_damageMultiplier = 0;
	level.matchRules_vampirism = 0;
	
	//	team options
	SetDynamicDvar( "scr_game_spectatetype", GetMatchRulesData( "commonOption", "spectateModeAllowed" ) );
	SetDynamicDvar( "scr_game_allowkillcam", GetMatchRulesData( "commonOption", "showKillcam" ) );
	SetDynamicDvar( "scr_game_forceuav", GetMatchRulesData( "commonOption", "radarAlwaysOn" ) );
	SetDynamicDvar( "scr_" + level.gameType + "_playerrespawndelay", GetMatchRulesData( "commonOption", "respawnDelay" ) );
	SetDynamicDvar( "scr_" + level.gameType + "_waverespawndelay", GetMatchRulesData( "commonOption", "waveRespawnDelay" ) );
	SetDynamicDvar( "scr_player_forcerespawn", GetMatchRulesData( "commonOption", "forceRespawn" ) );
	
	//	gameplay options
	level.matchRules_allowCustomClasses = GetMatchRulesData( "commonOption", "allowCustomClasses" );
	SetDynamicDvar( "scr_game_hardpoints", GetMatchRulesData( "commonOption", "allowKillstreaks" ) );
	SetDynamicDvar( "scr_game_perks", GetMatchRulesData( "commonOption", "allowPerks" ) );
	SetDynamicDvar( "g_hardcore", GetMatchRulesData( "commonOption", "hardcoreModeOn" ) );
	SetDynamicDvar( "scr_thirdPerson", GetMatchRulesData( "commonOption", "forceThirdPersonView" ) );
	SetDynamicDvar( "camera_thirdPerson", GetMatchRulesData( "commonOption", "forceThirdPersonView" ) );	// This is what the game uses, set both anyway so they're in sync.
	SetDynamicDvar( "scr_game_onlyheadshots", GetMatchRulesData( "commonOption", "headshotsOnly" ) );
	if ( !isDefined( skipFriendlyFire ) )
		SetDynamicDvar( "scr_team_fftype", GetMatchRulesData( "commonOption", "friendlyFire" ) );		
		
	//	hardcore overrides these options
	if ( GetMatchRulesData( "commonOption", "hardcoreModeOn" ) )
	{
		SetDynamicDvar( "scr_team_fftype", 1 );
		SetDynamicDvar( "scr_player_maxhealth", 30 );
		SetDynamicDvar( "scr_player_healthregentime", 0 );
		SetDynamicDvar( "scr_player_respawndelay", 10 ); // hardcore_settings.cfg only sets this
		//SetDynamicDvar( "scr_" + level.gameType + "_playerrespawndelay", 10 );
		SetDynamicDvar( "scr_game_allowkillcam", 0 );
		SetDynamicDvar( "scr_game_forceuav", 0 );
	}
}


reInitializeMatchRulesOnMigration()
{
	assert( isUsingMatchRulesData() );
	assert( isDefined( level.initializeMatchRules ) );
	
	while(1)
	{
		level waittill( "host_migration_begin" );
		[[level.initializeMatchRules]]();
	}
}


GetMatchRulesSpecialClass( team, index )
{
	class = [];
	class["loadoutPrimaryAttachment2"] = "none";
	class["loadoutSecondaryAttachment2"] = "none";		
	
	class["loadoutPrimary"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "weapon" );
	class["loadoutPrimaryAttachment"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "attachment", 0 );
	class["loadoutPrimaryAttachment2"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "attachment", 1 );
	class["loadoutPrimaryBuff"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "buff" );
	class["loadoutPrimaryCamo"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "camo" );
	class["loadoutPrimaryReticle"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 0, "reticle" );
	
	class["loadoutSecondary"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "weapon" );
	class["loadoutSecondaryAttachment"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "attachment", 0 );
	class["loadoutSecondaryAttachment2"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "attachment", 1 );
	class["loadoutSecondaryBuff"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "buff" );
	class["loadoutSecondaryCamo"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "camo" );
	class["loadoutSecondaryReticle"] = getMatchRulesData( "defaultClasses", team, index, "class", "weaponSetups", 1, "reticle" );
	
	class["loadoutEquipment"] = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 0 );
	class["loadoutOffhand"] = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 6 );
	//	hack, until game mode default class data can be reset
	if ( class["loadoutOffhand"] == "specialty_null" )
		class["loadoutOffhand"] = "none";
	
	class["loadoutPerk1"] = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 1 );
	class["loadoutPerk2"] = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 2 );
	class["loadoutPerk3"] = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 3 );
	
	loadoutStreakType = getMatchRulesData( "defaultClasses", team, index, "class", "perks", 5 );
	if ( loadoutStreakType != "specialty_null" )
	{
		class["loadoutStreakType"] = loadoutStreakType;
		class["loadoutKillstreak1"] = maps\mp\gametypes\_class::recipe_getKillstreak( team, index, loadoutStreakType, 0 );
		class["loadoutKillstreak2"] = maps\mp\gametypes\_class::recipe_getKillstreak( team, index, loadoutStreakType, 1 );
		class["loadoutKillstreak3"] = maps\mp\gametypes\_class::recipe_getKillstreak( team, index, loadoutStreakType, 2 );	
	}
	
	class["loadoutDeathstreak"] = getMatchRulesData( "defaultClasses", team, index, "class", "deathstreak" );	
	
	class["loadoutJuggernaut"] = getMatchRulesData( "defaultClasses", team, index, "juggernaut" );
	
	//	no killstreaks defined for special classes
	
	return class;
}


recipeClassApplyJuggernaut()
{
	level endon( "game_ended" );
	self endon( "disconnect" );
	
	if ( isDefined( self.jugg_chosenClass  ) )
	{
		//	we're spawning, wait for all of spawn to finish 
		self waittill( "spawned_player" );
		self.class = self.jugg_chosenClass;
		self.jugg_chosenClass = undefined;
		self maps\mp\gametypes\_class::setClass( self.class );			
	}
	else
	{
		//	we're just going through giveLoadout(), give it a frame
		wait( 0.5 );
	}			
	
	self.moveSpeedScaler = 0.7;
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
		self.juggernautOverlay SetShader( level.juggSettings[ "juggernaut" ].overlay, 640, 480 );
		self.juggernautOverlay.sort = -10;
		self.juggernautOverlay.archived = true;
		self.juggernautOverlay.hidein3rdperson = true;
	}

	self thread maps\mp\killstreaks\_juggernaut::juggernautSounds();

	level notify( "juggernaut_equipped", self );

	self thread maps\mp\killstreaks\_juggernaut::juggRemover();	
}