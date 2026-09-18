/****************************************************************************
 
 battleChatter.gsc
 
 Basic concepts: Battle chatter events work on a queue system.  Events are 
   added the AI's queue, and script calls to playBattleChatter(), scattered
   throughout the animscripts, give the AI oppurtunities to play the events.
   Events have an expiration time; if there are no calls to playBattleChatter
   before an event expires, it will not play.
     Script calls, usually within animscripts or battleChatter_ai::*Waiter() 
   functions, call the add*Event(); functions to add a voice event to the 
   AI's queue.
     Since an AI can have multiple events in it's queue at a give time, there
   is a priority system in place to help the AI choose which events get added
   to the queue and which events it will play.  Events with a priority of 1
   will always be added to the queue (unless battlechatter is disabled on the
   AI)
		
*****************************************************************************/

#include common_scripts\utility;
#include maps\_utility;
#include animscripts\utility;
#include animscripts\battlechatter_ai;

/****************************************************************************
 initialization
*****************************************************************************/

// Initializes the battle chatter system
init_battleChatter()
{
	if ( IsDefined( anim.chatInitialized ) && anim.chatInitialized )
		return;

	SetDvarIfUninitialized( "bcs_enable", "on" );

	if ( GetDvar( "bcs_enable", "on" ) == "off" )
	{
		anim.chatInitialized = false;
		anim.player.chatInitialized = false;
		return;
	}

	anim.chatInitialized = true;
	anim.player.chatInitialized = false;

	SetDvarIfUninitialized( "bcs_filterThreat", "off" );
	SetDvarIfUninitialized( "bcs_filterInform", "off" );
	SetDvarIfUninitialized( "bcs_filterOrder", "off" );
	SetDvarIfUninitialized( "bcs_filterReaction", "off" );
	SetDvarIfUninitialized( "bcs_filterResponse", "off" );

	SetDvarIfUninitialized( "bcs_forceEnglish", "0" );
	// useful if you only have one voice actor's set of aliases and need to test responses
	SetDvarIfUninitialized( "bcs_allowsamevoiceresponse", "off" );

	SetDvarIfUninitialized( "debug_bcprint", "off" );
	SetDvarIfUninitialized( "debug_bcprintdump", "off" );
	SetDvarIfUninitialized( "debug_bcprintdumptype", "csv" );
	SetDvarIfUninitialized( "debug_bcshowqueue", "off" );

	/#
	SetDvarIfUninitialized( "debug_bcthreat", "off" );
	SetDvarIfUninitialized( "debug_bcresponse", "off" );
	SetDvarIfUninitialized( "debug_bcorder", "off" );
	SetDvarIfUninitialized( "debug_bcinform", "off" );
	SetDvarIfUninitialized( "debug_bcdrawobjects", "off" );
	SetDvarIfUninitialized( "debug_bcinteraction", "off" );
	#/

	anim.bcPrintFailPrefix = "^3***** BCS FAILURE: ";
	anim.bcPrintWarnPrefix = "^3***** BCS WARNING: ";

	bcs_setup_teams_array();
	bcs_setup_countryIDs();

	// Player Name IDs:
	// - these IDs map to whatever the sound dept. uses for the player name alias
	//   (ex. "US_name_player_1" would make our id = 1)
	anim.playerNameIDs[ "american" ]		 = "1";
	anim.playerNameIDs[ "seal" ]			 = "1";
	anim.playerNameIDs[ "taskforce" ]		 = "1";
	anim.playerNameIDs[ "secretservice" ]	 = "1";
	anim.playerNameIDs[ "delta" ]			 = "1";

	thread setPlayerBcNameID();

	// AI Name IDs
	// - update these when the number or ID(s) of voice actors for any nationality changes!
	anim.usedIDs = [];

	anim.usedIDs[ "russian" ] = [];
		anim.usedIDs[ "russian" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "russian" ][ 0 ].count = 0;
		anim.usedIDs[ "russian" ][ 0 ].npcID = "0";
		anim.usedIDs[ "russian" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "russian" ][ 1 ].count = 0;
		anim.usedIDs[ "russian" ][ 1 ].npcID = "1";
		anim.usedIDs[ "russian" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "russian" ][ 2 ].count = 0;
		anim.usedIDs[ "russian" ][ 2 ].npcID = "2";
		anim.usedIDs[ "russian" ][ 3 ] = SpawnStruct();
		anim.usedIDs[ "russian" ][ 3 ].count = 0;
		anim.usedIDs[ "russian" ][ 3 ].npcID = "3";
		anim.usedIDs[ "russian" ][ 4 ] = SpawnStruct();
		anim.usedIDs[ "russian" ][ 4 ].count = 0;
		anim.usedIDs[ "russian" ][ 4 ].npcID = "4";

	anim.usedIDs[ "portuguese" ] = [];
		anim.usedIDs[ "portuguese" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "portuguese" ][ 0 ].count = 0;
		anim.usedIDs[ "portuguese" ][ 0 ].npcID = "0";
		anim.usedIDs[ "portuguese" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "portuguese" ][ 1 ].count = 0;
		anim.usedIDs[ "portuguese" ][ 1 ].npcID = "1";
		anim.usedIDs[ "portuguese" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "portuguese" ][ 2 ].count = 0;
		anim.usedIDs[ "portuguese" ][ 2 ].npcID = "2";

	anim.usedIDs[ "shadowcompany" ] = [];
		anim.usedIDs[ "shadowcompany" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "shadowcompany" ][ 0 ].count = 0;
		anim.usedIDs[ "shadowcompany" ][ 0 ].npcID = "0";
		anim.usedIDs[ "shadowcompany" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "shadowcompany" ][ 1 ].count = 0;
		anim.usedIDs[ "shadowcompany" ][ 1 ].npcID = "1";
		anim.usedIDs[ "shadowcompany" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "shadowcompany" ][ 2 ].count = 0;
		anim.usedIDs[ "shadowcompany" ][ 2 ].npcID = "2";
		anim.usedIDs[ "shadowcompany" ][ 3 ] = SpawnStruct();
		anim.usedIDs[ "shadowcompany" ][ 3 ].count = 0;
		anim.usedIDs[ "shadowcompany" ][ 3 ].npcID = "3";

	anim.usedIDs[ "british" ] = [];
		anim.usedIDs[ "british" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "british" ][ 0 ].count = 0;
		anim.usedIDs[ "british" ][ 0 ].npcID = "0";
		anim.usedIDs[ "british" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "british" ][ 1 ].count = 0;
		anim.usedIDs[ "british" ][ 1 ].npcID = "1";

	anim.usedIDs[ "american" ] = [];
		anim.usedIDs[ "american" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "american" ][ 0 ].count = 0;
		anim.usedIDs[ "american" ][ 0 ].npcID = "0";
		anim.usedIDs[ "american" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "american" ][ 1 ].count = 0;
		anim.usedIDs[ "american" ][ 1 ].npcID = "1";
		anim.usedIDs[ "american" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "american" ][ 2 ].count = 0;
		anim.usedIDs[ "american" ][ 2 ].npcID = "2";

	anim.usedIDs[ "seal" ] = [];
		anim.usedIDs[ "seal" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "seal" ][ 0 ].count = 0;
		anim.usedIDs[ "seal" ][ 0 ].npcID = "0";
		anim.usedIDs[ "seal" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "seal" ][ 1 ].count = 0;
		anim.usedIDs[ "seal" ][ 1 ].npcID = "1";
		anim.usedIDs[ "seal" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "seal" ][ 2 ].count = 0;
		anim.usedIDs[ "seal" ][ 2 ].npcID = "2";
		anim.usedIDs[ "seal" ][ 3 ] = SpawnStruct();
		anim.usedIDs[ "seal" ][ 3 ].count = 0;
		anim.usedIDs[ "seal" ][ 3 ].npcID = "3";

	anim.usedIDs[ "taskforce" ] = [];
		anim.usedIDs[ "taskforce" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "taskforce" ][ 0 ].count = 0;
		anim.usedIDs[ "taskforce" ][ 0 ].npcID = "0";

	anim.usedIDs[ "secretservice" ] = [];
		anim.usedIDs[ "secretservice" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "secretservice" ][ 0 ].count = 0;
		anim.usedIDs[ "secretservice" ][ 0 ].npcID = "0";
		anim.usedIDs[ "secretservice" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "secretservice" ][ 1 ].count = 0;
		anim.usedIDs[ "secretservice" ][ 1 ].npcID = "1";
		anim.usedIDs[ "secretservice" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "secretservice" ][ 2 ].count = 0;
		anim.usedIDs[ "secretservice" ][ 2 ].npcID = "2";
		anim.usedIDs[ "secretservice" ][ 3 ] = SpawnStruct();
		anim.usedIDs[ "secretservice" ][ 3 ].count = 0;
		anim.usedIDs[ "secretservice" ][ 3 ].npcID = "3";

	anim.usedIDs[ "arab" ] = [];
		anim.usedIDs[ "arab" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "arab" ][ 0 ].count = 0;
		anim.usedIDs[ "arab" ][ 0 ].npcID = "0";
		anim.usedIDs[ "arab" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "arab" ][ 1 ].count = 0;
		anim.usedIDs[ "arab" ][ 1 ].npcID = "1";
		anim.usedIDs[ "arab" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "arab" ][ 2 ].count = 0;
		anim.usedIDs[ "arab" ][ 2 ].npcID = "2";

	anim.usedIDs[ "delta" ] = [];
		anim.usedIDs[ "delta" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "delta" ][ 0 ].count = 0;
		anim.usedIDs[ "delta" ][ 0 ].npcID = "0";
		anim.usedIDs[ "delta" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "delta" ][ 1 ].count = 0;
		anim.usedIDs[ "delta" ][ 1 ].npcID = "1";
		anim.usedIDs[ "delta" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "delta" ][ 2 ].count = 0;
		anim.usedIDs[ "delta" ][ 2 ].npcID = "2";

	anim.usedIDs[ "french" ] = [];
		anim.usedIDs[ "french" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "french" ][ 0 ].count = 0;
		anim.usedIDs[ "french" ][ 0 ].npcID = "0";

	anim.usedIDs[ "african" ] = [];
		anim.usedIDs[ "african" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "african" ][ 0 ].count = 0;
		anim.usedIDs[ "african" ][ 0 ].npcID = "0";
		anim.usedIDs[ "african" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "african" ][ 1 ].count = 0;
		anim.usedIDs[ "african" ][ 1 ].npcID = "1";
		anim.usedIDs[ "african" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "african" ][ 2 ].count = 0;
		anim.usedIDs[ "african" ][ 2 ].npcID = "2";

	anim.usedIDs[ "czech" ] = [];
		anim.usedIDs[ "czech" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "czech" ][ 0 ].count = 0;
		anim.usedIDs[ "czech" ][ 0 ].npcID = "0";
		anim.usedIDs[ "czech" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "czech" ][ 1 ].count = 0;
		anim.usedIDs[ "czech" ][ 1 ].npcID = "1";
		anim.usedIDs[ "czech" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "czech" ][ 2 ].count = 0;
		anim.usedIDs[ "czech" ][ 2 ].npcID = "2";

	anim.usedIDs[ "pmc" ] = [];
		anim.usedIDs[ "pmc" ][ 0 ] = SpawnStruct();
		anim.usedIDs[ "pmc" ][ 0 ].count = 0;
		anim.usedIDs[ "pmc" ][ 0 ].npcID = "0";
		anim.usedIDs[ "pmc" ][ 1 ] = SpawnStruct();
		anim.usedIDs[ "pmc" ][ 1 ].count = 0;
		anim.usedIDs[ "pmc" ][ 1 ].npcID = "1";
		anim.usedIDs[ "pmc" ][ 2 ] = SpawnStruct();
		anim.usedIDs[ "pmc" ][ 2 ].count = 0;
		anim.usedIDs[ "pmc" ][ 2 ].npcID = "2";
									
	init_flavorbursts();

	// doesn't impact friendlyfire warnings normally played when battlechatter is on,
	//  just whether it plays when battlechatter is otherwise turned off
	if ( !IsDefined( level.friendlyfire_warnings ) )
	{
		level.friendlyfire_warnings = false;
	}

	anim.eventTypeMinWait = [];
	anim.eventTypeMinWait[ "threat" ] = [];
	anim.eventTypeMinWait[ "response" ] = [];
	anim.eventTypeMinWait[ "reaction" ] = [];
	anim.eventTypeMinWait[ "order" ] = [];
	anim.eventTypeMinWait[ "inform" ] = [];
	anim.eventTypeMinWait[ "custom" ] = [];
	anim.eventTypeMinWait[ "direction" ] = [];

	// If you want to tweak how often battlechatter messages happen,
	// this is place to do it.
	// A priority of 1 will force an event to be added to the queue, and 
	// will make it override pre-existing events of the same type.

	// times are in milliseconds
	if ( IsDefined( level._stealth ) )
	{
		anim.eventActionMinWait[ "threat" ][ "self" ]	 = 20000;
		anim.eventActionMinWait[ "threat" ][ "squad" ]	 = 30000;
	}
	else
	{
		anim.eventActionMinWait[ "threat" ][ "self" ]	 = 12500;
		anim.eventActionMinWait[ "threat" ][ "squad" ]	 = 7500;
	}
	anim.eventActionMinWait[ "threat" ][ "location_repeat" ] = 5000;
	anim.eventActionMinWait[ "response" ][ "self" ]		 = 1000;
	anim.eventActionMinWait[ "response" ][ "squad" ]	 = 1000;
	anim.eventActionMinWait[ "reaction" ][ "self" ]		 = 1000;
	anim.eventActionMinWait[ "reaction" ][ "squad" ]	 = 1000;
	anim.eventActionMinWait[ "order" ][ "self" ]		 = 8000;
	anim.eventActionMinWait[ "order" ][ "squad" ]		 = 10000;
	anim.eventActionMinWait[ "inform" ][ "self" ]		 = 6000;
	anim.eventActionMinWait[ "inform" ][ "squad" ]		 = 8000;
	anim.eventActionMinWait[ "custom" ][ "self" ]		 = 0;
	anim.eventActionMinWait[ "custom" ][ "squad" ]		 = 0;

	anim.eventTypeMinWait[ "playername" ]					 = 50000;
	anim.eventTypeMinWait[ "reaction" ][ "casualty" ]		 = 14000;
	anim.eventTypeMinWait[ "reaction" ][ "friendlyfire" ]	 = 5000;
	anim.eventTypeMinWait[ "reaction" ][ "taunt" ]			 = 30000;
	anim.eventTypeMinWait[ "inform" ][ "reloading" ]		 = 20000;
	anim.eventTypeMinWait[ "inform" ][ "killfirm" ]			 = 15000;

	anim.eventPriority[ "threat" ][ "infantry" ]			 = 0.5;
	anim.eventPriority[ "threat" ][ "vehicle" ]				 = 0.7;
	anim.eventPriority[ "response" ][ "ack" ]				 = 0.9;
	anim.eventPriority[ "response" ][ "exposed" ]			 = 0.8;
	anim.eventPriority[ "response" ][ "callout" ]			 = 0.9;
	anim.eventPriority[ "response" ][ "echo" ]				 = 0.9;
	anim.eventPriority[ "reaction" ][ "casualty" ]			 = 0.5;
	anim.eventPriority[ "reaction" ][ "friendlyfire" ]		 = 1.0;
	anim.eventPriority[ "reaction" ][ "taunt" ]				 = 0.9;
	anim.eventPriority[ "order" ][ "action" ]				 = 0.3;
	anim.eventPriority[ "order" ][ "move" ]					 = 0.3;
	anim.eventPriority[ "order" ][ "displace" ]				 = 0.5;
	anim.eventPriority[ "inform" ][ "attack" ]				 = 0.9;
	anim.eventPriority[ "inform" ][ "incoming" ]			 = 0.9;
	anim.eventPriority[ "inform" ][ "reloading" ]			 = 0.2;
	anim.eventPriority[ "inform" ][ "suppressed" ]			 = 0.2;
	anim.eventPriority[ "inform" ][ "killfirm" ]			 = 0.7;
	anim.eventPriority[ "custom" ][ "generic" ]				 = 1.0;

	anim.eventDuration[ "threat" ][ "infantry" ]		 = 1000;
	anim.eventDuration[ "threat" ][ "vehicle" ]			 = 1000;
	anim.eventDuration[ "response" ][ "exposed" ]		 = 2000;
	anim.eventDuration[ "response" ][ "callout" ]		 = 2000;
	anim.eventDuration[ "response" ][ "echo" ]			 = 2000;
	anim.eventDuration[ "response" ][ "ack" ]			 = 1750;
	anim.eventDuration[ "reaction" ][ "casualty" ]		 = 2000;
	anim.eventDuration[ "reaction" ][ "friendlyfire" ]	 = 1000;
	anim.eventDuration[ "reaction" ][ "taunt" ]			 = 2000;
	anim.eventDuration[ "order" ][ "action" ]			 = 3000;
	anim.eventDuration[ "order" ][ "move" ]				 = 3000;
	anim.eventDuration[ "order" ][ "displace" ]			 = 3000;
	anim.eventDuration[ "inform" ][ "attack" ]			 = 1000;
	anim.eventDuration[ "inform" ][ "incoming" ]		 = 1500;
	anim.eventDuration[ "inform" ][ "reloading" ]		 = 1000;
	anim.eventDuration[ "inform" ][ "suppressed" ]		 = 2000;
	anim.eventDuration[ "inform" ][ "killfirm" ]		 = 2000;
	anim.eventDuration[ "custom" ][ "generic" ]			 = 1000;

	// event chances are in % out of 100
	anim.eventChance[ "response" ][ "exposed" ]				 = 75;
	anim.eventChance[ "response" ][ "reload" ]				 = 65;
	anim.eventChance[ "response" ][ "callout" ]				 = 75;
	anim.eventChance[ "response" ][ "callout_negative" ]	 = 20;
	anim.eventChance[ "response" ][ "order" ]				 = 40;
	anim.eventChance[ "moveEvent" ][ "coverme" ]			 = 70;
	anim.eventChance[ "moveEvent" ][ "ordertoplayer" ]		 = 10;

	// flavor burst transmission tweakables
	anim.fbt_desiredDistMax = 620;// try to keep fbts within this range from the player
	anim.fbt_waitMin = 12;// time to wait between transmissions
	anim.fbt_waitMax = 24;
	anim.fbt_lineBreakMin = 2;// time to wait between lines
	anim.fbt_lineBreakMax = 5;

	anim.moveOrigin = Spawn( "script_origin", ( 0, 0, 0 ) );

	// how many units from the player dudes can be and still chatter or be chattered about
	if ( !IsDefined( level.bcs_maxTalkingDistFromPlayer ) )
	{
		level.bcs_maxTalkingDistFromPlayer = 1500;
	}
	if ( !IsDefined( level.bcs_maxThreatDistFromPlayer ) )
	{
		level.bcs_maxThreatDistFromPlayer = 2500;
	}

	// difference in height for "high" callouts
	level.heightForHighCallout = 96.0;
	
	// min distance to use distance callouts (in yards)
	level.minDistanceCallout = 8.0;
	// max distance to use distance callouts (in yards)
	level.maxDistanceCallout = 45.0;

	// set up location triggers
	maps\_bcs_location_trigs::bcs_location_trigs_init();
	Assert( IsDefined( anim.bcs_locations ) );
	anim.locationLastCalloutTimes = [];

	// how long after starting some scripted dialogue will we wait before chattering? (milliseconds)
	anim.scriptedDialogueBufferTime = 4000;

	// how long before we can chatter about a threat again?
	anim.bcs_threatResetTime = 3000;

	/#
	if ( GetDvar( "debug_bcdrawobjects" ) == "on" )
		thread bcDrawObjects();
	#/

	anim.squadCreateFuncs[ anim.squadCreateFuncs.size ] = ::init_squadBattleChatter;
	anim.squadCreateStrings[ anim.squadCreateStrings.size ] = "::init_squadBattleChatter";

	foreach ( team in anim.teams )
	{
		anim.isTeamSpeaking[ team ] = false;
		anim.isTeamSaying[ team ][ "threat" ] = false;
		anim.isTeamSaying[ team ][ "order" ] = false;
		anim.isTeamSaying[ team ][ "reaction" ] = false;
		anim.isTeamSaying[ team ][ "response" ] = false;
		anim.isTeamSaying[ team ][ "inform" ] = false;
		anim.isTeamSaying[ team ][ "custom" ] = false;
	}

	bcs_setup_chatter_toggle_array();

	// which nationalities can do flavor burst transmissions?
	if ( !IsDefined( anim.flavorburstVoices ) )
	{
		anim.flavorburstVoices = [];
		anim.flavorburstVoices[ "american" ]		 = true;
		anim.flavorburstVoices[ "delta" ]			 = false;
		anim.flavorburstVoices[ "french" ]			 = false;
		anim.flavorburstVoices[ "czech" ]			 = false;
		anim.flavorburstVoices[ "pmc" ]				 = false;
		anim.flavorburstVoices[ "african" ]			 = false;
		anim.flavorburstVoices[ "shadowcompany" ]	 = true;
		anim.flavorburstVoices[ "seal" ]			 = false;
		anim.flavorburstVoices[ "taskforce" ]		 = false;
		anim.flavorburstVoices[ "secretservice" ]	 = false;
		anim.flavorburstVoices[ "british" ]			 = false;
	}

	bcs_setup_flavorburst_toggle_array();

	anim.lastTeamSpeakTime = [];
	anim.lastNameSaid = [];
	anim.lastNameSaidTime = [];
	foreach ( team in anim.teams )
	{
		anim.lastTeamSpeakTime[ team ] = -50000;// so it doesnt pause if nobody has ever spoken
		anim.lastNameSaid[ team ] = "none";
		anim.lastNameSaidTime[ team ] = -100000;
	}

	// how long we'll wait before allowing use of a certain AI name again
	anim.lastNameSaidTimeout = 120000;

	for ( index = 0; index < anim.squadIndex.size; index++ )
	{
		if ( IsDefined( anim.squadIndex[ index ].chatInitialized ) && anim.squadIndex[ index ].chatInitialized )
			continue;

		anim.squadIndex[ index ] init_squadBattleChatter();
	}

	/*----------- THREAT CALLOUT CHANCES -----------
	- anim.threatCallouts[] is indexed by the types of possible threat callouts for this AI,
	  and holds %chance weights that help determine if that the AI will
	  try to use that type of threat callout to alert players to a threat.
	  
	- These are matched against the values of self.allowedCallouts[] for each AI, to determine
	  whether the AI can use a particular kind of callout - not all nationalities get all callouts.
	  self.allowedCallouts gets set up for each AI in battlechatter_ai::init_aiBattleChatter.
	 
	 - higher numbers mean a higher chance!
	 - zero values do not get considered.
	 - 100+ values are prioritized above everything except other 100+ values.
	 - chances are dicerolled against one another to find a winner, like this:
	   if( RandomInt( threatCallouts[ "player_yourclock" ] ) > RandomInt( threatCallouts[ "ai_yourclock ] ) )
	
	rough priorities:
	1. RPG
	2. exposed
	3. player_obvious
	3. "catch-all":
		1. player_your_clock
		2. player_contact_clock
		3. player_target_clock
		4. ai_your_clock
		5. player_cardinal
	4. object (aka landmark):
		1. player_object_yourclock
		1. player_object_clock
		2. ai_object_yourclock
	5. location
		1. player_location
		2. ai_location
		3. generic_location
	-------------------------------------------------*/

	anim.threatCallouts = [];

	// RPG/exposed
	anim.threatCallouts[ "rpg" ] 						 = 100;// "RPG!"
	anim.threatCallouts[ "exposed" ] 					 = 25;// "Got a tango in the open!"

	// "obvious" callouts
	anim.threatCallouts[ "player_distance" ] 			 = 25;// "Player! Contact 10 yards!( for 12 o'clock threats )
	anim.threatCallouts[ "player_obvious" ] 			 = 25;// "Player! Light 'em up!"( for 12 o'clock threats )

	// player-relative callouts
	// anim.threatCallouts[ "player_yourclock" ] 			 = 30;// "Player! Contact at your 10 o'clock!"
	anim.threatCallouts[ "player_contact_clock" ] 		 = 25;// "Player! Contact at 10 o'clock!"
	anim.threatCallouts[ "player_target_clock" ] 		 = 25;// "Player! Target, 10 o'clock!"
	anim.threatCallouts[ "player_target_clock_high" ] 		 = 25;// "Player! Target, 10 o'clock high!"
	anim.threatCallouts[ "player_cardinal" ] 			 = 20;// "Player! Contact, northwest!"

	// "catch-all" callouts
	// anim.threatCallouts[ "ai_yourclock" ] 				 = 25;// "Peas! Contact at your 10 o'clock!"
	anim.threatCallouts[ "ai_distance" ] 			 = 25;// "Peas! Light 'em up!"( for 12 o'clock threats )
	anim.threatCallouts[ "ai_obvious" ] 			 = 25;// "Peas! Contact 10 yards!"( for 12 o'clock threats )
	anim.threatCallouts[ "ai_contact_clock" ]			 = 20;
	anim.threatCallouts[ "ai_target_clock" ]			 = 20;
	anim.threatCallouts[ "ai_target_clock_high" ]			 = 75;
	anim.threatCallouts[ "ai_cardinal" ]				 = 10;

	/* DEPRECATED
	// object (aka landmark) callouts
	anim.threatCallouts[ "player_object_yourclock" ]	= 100;// "Player! Movement by the dumpster at your 10 o'clock!"
	anim.threatCallouts[ "player_object_clock" ]		= 100;// "Player! Movement by the dumpster at 10 o'clock!"
	anim.threatCallouts[ "ai_object_yourclock" ]		= 95;// "Peas! Movement by the dumpster at your 10 o'clock!"
	*/

	// location callouts
	anim.threatCallouts[ "player_location" ]			 = 95;// ( Player - relative ) "Contact! 2nd floor window on the left!"
	anim.threatCallouts[ "ai_location" ]				 = 100;// ( AI - relative ) "Contact! 2nd floor window on the left!"
	anim.threatCallouts[ "generic_location" ]			 = 90;


	anim.lastTeamThreatCallout = [];
	anim.lastTeamThreatCalloutTime = [];
	foreach ( team in anim.teams )
	{
		anim.lastTeamThreatCallout[ team ]		 = undefined;
		anim.lastTeamThreatCalloutTime[ team ]	 = undefined;
	}
	anim.teamThreatCalloutLimitTimeout = 120000;


	level notify( "battlechatter initialized" );
	anim notify( "battlechatter initialized" );
}

bcs_setup_teams_array()
{
	if ( !IsDefined( anim.teams ) )
	{
		anim.teams = [];
		anim.teams[ anim.teams.size ] = "axis";
		anim.teams[ anim.teams.size ] = "allies";
		anim.teams[ anim.teams.size ] = "team3";
		anim.teams[ anim.teams.size ] = "neutral";
	}
}

bcs_setup_countryIDs()
{
	if ( !IsDefined( anim.countryIDs ) )
	{
		anim.countryIDs[ "british" ]		 = "UK";
		anim.countryIDs[ "american" ]		 = "US";
		anim.countryIDs[ "seal" ]			 = "NS";
		anim.countryIDs[ "taskforce" ]		 = "TF";
		anim.countryIDs[ "secretservice" ]	 = "SS";
		anim.countryIDs[ "russian" ]		 = "RU";
		anim.countryIDs[ "arab" ]			 = "AB";
		anim.countryIDs[ "portuguese" ]		 = "PG";
		anim.countryIDs[ "shadowcompany" ]	 = "SC";
		anim.countryIDs[ "delta" ]	 		 = "DF";
		anim.countryIDs[ "french" ]			 = "FR";
		anim.countryIDs[ "african" ]		 = "AF";
		anim.countryIDs[ "czech" ]			 = "CZ";
		anim.countryIDs[ "pmc" ]			 = "PC";
	}
}

bcs_setup_chatter_toggle_array()
{
	bcs_setup_teams_array();

	if ( !IsDefined( level.battlechatter ) )
	{
		level.battlechatter = [];
		foreach ( team in anim.teams )
		{
			set_battlechatter_variable( team, true );
		}
	}
}

bcs_setup_flavorburst_toggle_array()
{
	bcs_setup_teams_array();

	if ( !IsDefined( level.flavorbursts ) )
	{
		level.flavorbursts = [];
		foreach ( team in anim.teams )
		{
			level.flavorbursts[ team ] = true;
		}
	}
}

init_flavorbursts()
{
	// flavor burst transmission aliases
	// update these as new transmissions are recorded
	// (format of the fbt aliases is "FB_US_7_11",
	//  where the first number is what you put below)
	anim.flavorbursts[ "american" ] = [];
	numBursts = 41;

	us = [];
	if ( level.script == "roadkill" || level.script == "trainer" )
	{
		// we don't want to hear chatter about US locales when we're operating in another country
		//  (these correspond to sequence numbers in the aliases)
		us[ us.size ] = 13;
		us[ us.size ] = 15;
		us[ us.size ] = 16;
		us[ us.size ] = 19;
		us[ us.size ] = 20;
		us[ us.size ] = 30;
		us[ us.size ] = 31;
		us[ us.size ] = 33;
		us[ us.size ] = 38;
	}

	for ( i = 0; i < numBursts; i++ )
	{
		// don't include US-specific aliases, if applicable
		if ( us.size )
		{
			foundOne = false;
			foreach ( sequenceNum in us )
			{
				if ( sequenceNum == i )
				{
					foundOne = true;
					break;
				}
			}

			if ( foundOne )
			{
				continue;
			}
		}

		anim.flavorbursts[ "american" ][ i ] = string( i + 1 );
	}

	anim.flavorbursts[ "shadowcompany" ] = [];
	numBursts = 9;

	for ( i = 1; i <= numBursts; i++ )
	{
		anim.flavorbursts[ "shadowcompany" ][ i ] = string( i + 1 );
	}

	anim.flavorburstsUsed = [];
}

shutdown_battleChatter()
{
	anim.countryIDs = undefined;
	anim.eventTypeMinWait = undefined;
	anim.eventActionMinWait = undefined;
	anim.eventTypeMinWait = undefined;
	anim.eventPriority = undefined;
	anim.eventDuration = undefined;

	anim.moveOrigin = undefined;

	anim.scriptedDialogueBufferTime = undefined;
	anim.bcs_threatResetTime = undefined;

	anim.locationLastCalloutTimes = undefined;

	anim.usedIDs = undefined;

	anim.flavorburstsUsed = undefined;

	anim.lastTeamThreatCallout = undefined;
	anim.lastTeamThreatCalloutTime = undefined;

	anim.lastNameSaidTimeout = undefined;
	anim.lastNameSaid = undefined;
	anim.lastNameSaidTime = undefined;

	anim.chatInitialized = false;
	anim.player.chatInitialized = false;

	level.battlechatter = undefined;

	for ( i = 0; i < anim.squadCreateFuncs.size; i++ )
	{
		if ( anim.squadCreateStrings[ i ] != "::init_squadBattleChatter" )
			continue;

		if ( i != ( anim.squadCreateFuncs.size - 1 ) )
		{
			anim.squadCreateFuncs[ i ] = anim.squadCreateFuncs[ anim.squadCreateFuncs.size - 1 ];
			anim.squadCreateStrings[ i ] = anim.squadCreateStrings[ anim.squadCreateStrings.size - 1 ];
		}

		anim.squadCreateFuncs[ anim.squadCreateFuncs.size - 1 ] = undefined;
		anim.squadCreateStrings[ anim.squadCreateStrings.size - 1 ] = undefined;
	}

	level notify( "battlechatter disabled" );
	anim notify( "battlechatter disabled" );
}

// initializes battlechatter data that resides in the squad manager
// this is done to keep the squad management system free from clutter
init_squadBattleChatter()
{
	squad = self;

	// tweakables
	squad.numSpeakers = 0;
	squad.maxSpeakers = 1;

	// non tweakables
	squad.nextSayTime = GetTime() + 50;
	squad.nextSayTimes[ "threat" ] = GetTime() + 50;
	squad.nextSayTimes[ "order" ] = GetTime() + 50;
	squad.nextSayTimes[ "reaction" ] = GetTime() + 50;
	squad.nextSayTimes[ "response" ] = GetTime() + 50;
	squad.nextSayTimes[ "inform" ] = GetTime() + 50;
	squad.nextSayTimes[ "custom" ] = GetTime() + 50;

	squad.nextTypeSayTimes[ "threat" ] = [];
	squad.nextTypeSayTimes[ "order" ] = [];
	squad.nextTypeSayTimes[ "reaction" ] = [];
	squad.nextTypeSayTimes[ "response" ] = [];
	squad.nextTypeSayTimes[ "inform" ] = [];
	squad.nextTypeSayTimes[ "custom" ] = [];

	squad.isMemberSaying[ "threat" ] = false;
	squad.isMemberSaying[ "order" ] = false;
	squad.isMemberSaying[ "reaction" ] = false;
	squad.isMemberSaying[ "response" ] = false;
	squad.isMemberSaying[ "inform" ] = false;
	squad.isMemberSaying[ "custom" ] = false;
	squad.lastDirection = "";

	squad.memberAddFuncs[ squad.memberAddFuncs.size ] = ::addToSystem;
	squad.memberAddStrings[ squad.memberAddStrings.size ] = "::addToSystem";
	squad.memberRemoveFuncs[ squad.memberRemoveFuncs.size ] = ::removeFromSystem;
	squad.memberRemoveStrings[ squad.memberRemoveStrings.size ] = "::removeFromSystem";
	squad.squadUpdateFuncs[ squad.squadUpdateFuncs.size ] = ::initContact;
	squad.squadUpdateStrings[ squad.squadUpdateStrings.size ] = "::initContact";

	squad.fbt_firstBurst = true;
	squad.fbt_lastBursterID = undefined;

	for ( i = 0; i < anim.squadIndex.size; i++ )
		squad thread initContact( anim.squadIndex[ i ].squadName );

	squad thread squadThreatWaiter();
	squad thread squadOfficerWaiter();

	squad thread squadFlavorBurstTransmissions();

	squad.chatInitialized = true;
	squad notify( "squad chat initialized" );
}

// initializes battlechatter data that resides in the squad manager
// this is done to keep the squad management system free from clutter
shutdown_squadBattleChatter()
{
	squad = self;

	// tweakables
	squad.numSpeakers = undefined;
	squad.maxSpeakers = undefined;

	// non tweakables
	squad.nextSayTime = undefined;
	squad.nextSayTimes = undefined;

	squad.nextTypeSayTimes = undefined;

	squad.isMemberSaying = undefined;

	squad.fbt_firstBurst = undefined;
	squad.fbt_lastBursterID = undefined;

	for ( i = 0; i < squad.memberAddFuncs.size; i++ )
	{
		if ( squad.memberAddStrings[ i ] != "::addToSystem" )
			continue;

		if ( i != ( squad.memberAddFuncs.size - 1 ) )
		{
			squad.memberAddFuncs[ i ] = squad.memberAddFuncs[ squad.memberAddFuncs.size - 1 ];
			squad.memberAddStrings[ i ] = squad.memberAddStrings[ squad.memberAddStrings.size - 1 ];
		}

		squad.memberAddFuncs[ squad.memberAddFuncs.size - 1 ] = undefined;
		squad.memberAddStrings[ squad.memberAddStrings.size - 1 ] = undefined;
	}

	for ( i = 0; i < squad.memberRemoveFuncs.size; i++ )
	{
		if ( squad.memberRemoveStrings[ i ] != "::removeFromSystem" )
			continue;

		if ( i != ( squad.memberRemoveFuncs.size - 1 ) )
		{
			squad.memberRemoveFuncs[ i ] = squad.memberRemoveFuncs[ squad.memberRemoveFuncs.size - 1 ];
			squad.memberRemoveStrings[ i ] = squad.memberRemoveStrings[ squad.memberRemoveStrings.size - 1 ];
		}

		squad.memberRemoveFuncs[ squad.memberRemoveFuncs.size - 1 ] = undefined;
		squad.memberRemoveStrings[ squad.memberRemoveStrings.size - 1 ] = undefined;
	}

	for ( i = 0; i < squad.squadUpdateFuncs.size; i++ )
	{
		if ( squad.squadUpdateStrings[ i ] != "::initContact" )
			continue;

		if ( i != ( squad.squadUpdateFuncs.size - 1 ) )
		{
			squad.squadUpdateFuncs[ i ] = squad.squadUpdateFuncs[ squad.squadUpdateFuncs.size - 1 ];
			squad.squadUpdateStrings[ i ] = squad.squadUpdateStrings[ squad.squadUpdateStrings.size - 1 ];
		}

		squad.squadUpdateFuncs[ squad.squadUpdateFuncs.size - 1 ] = undefined;
		squad.squadUpdateStrings[ squad.squadUpdateStrings.size - 1 ] = undefined;
	}

	for ( i = 0; i < anim.squadIndex.size; i++ )
		squad shutdownContact( anim.squadIndex[ i ].squadName );

	squad.chatInitialized = false;
}

bcsEnabled()
{
	return anim.chatInitialized;
}

bcsDebugWaiter()
{
	lastState = GetDvar( "bcs_enable", "on" );

	while ( 1 )
	{
		state = GetDvar( "bcs_enable", "on" );

		if ( state != lastState )
		{
			switch( state )
			{
				case "on":
					if ( !anim.chatInitialized )
						enableBattleChatter();
					break;
				case "off":
					if ( anim.chatInitialized )
						disableBattleChatter();
					break;
			}
			lastState = state;
		}

		wait( 1.0 );
	}
}

enableBattleChatter()
{
	init_battleChatter();

	anim.player thread animscripts\battleChatter_ai::addToSystem();

	ai = GetAIArray();
	for ( i = 0; i < ai.size; i++ )
	{
		ai[ i ] addToSystem();
	}
}

disableBattleChatter()
{
	shutdown_battleChatter();

	ai = GetAIArray();
	for ( i = 0; i < ai.size; i++ )
	{
		if ( IsDefined( ai[ i ].squad ) && ai[ i ].squad.chatInitialized )
			ai[ i ].squad shutdown_squadBattleChatter();

		ai[ i ] removeFromSystem();
	}
}

// sets the player name to use when playing player-relative phrases
// these are used to make an alias that looks like: US_1_name_player_US_1
setPlayerBcNameID( overrideNameID, overrideCountryID )
{
	if ( IsDefined( overrideNameID ) && IsDefined( overrideCountryID ) )
	{
		level.player.bcNameID = overrideNameID;
		level.player.bcCountryID = overrideCountryID;
		return;
	}

	while ( !IsDefined( level.campaign ) )
	{
		wait( 0.1 );
	}

	nationality = level.campaign;

	nameID = anim.playerNameIDs[ nationality ];
	countryID = anim.countryIDs[ nationality ];

	if ( IsDefined( nameID ) )
	{
		level.player.bcNameID = nameID;
	}

	if ( IsDefined( countryID ) )
	{
		level.player.bcCountryID = countryID;
	}
}

/****************************************************************************
 processing
*****************************************************************************/

playBattleChatter()
{
	if ( !IsAlive( self ) )
	{
		return;
	}

	// battlechatter system is totally turned off (as opposed to dormant)
	if ( !bcsEnabled() )
	{
		return;
	}

	// he's doing a scripted animation
 	if ( self._animActive > 0 )
 	{
 		return;
 	}

	// he's already saying a battlechatter line
	if ( IsDefined( self.isSpeaking ) && self.isSpeaking )
	{
 		return;
 	}

 	// an ally is doing scripted dialogue
 	if ( self.team == "allies" && IsDefined( anim.scriptedDialogueStartTime ) )
	{
		if ( ( anim.scriptedDialogueStartTime + anim.scriptedDialogueBufferTime ) > GetTime() )
		{
			return;
		}
	}

	// hacky! friendlyfire warnings have greatly reduced requirements for whether they can play
	if ( self friendlyfire_warning() )
	{
		return;
	}

	if ( !IsDefined( self.battleChatter ) || !self.battleChatter )
	{
		return;
	}

	if ( self.team == "allies" && GetDvarInt( "bcs_forceEnglish", 0 ) )
	{
		return;
	}

	if ( anim.isTeamSpeaking[ self.team ] )
	{
		return;
	}

	self endon( "death" );

//	self thread debugQueueEvents();
//	self thread debugPrintEvents();

	event = self getHighestPriorityEvent();

	if ( !IsDefined( event ) )
	{
		return;
	}

	switch( event )
	{
		case "custom":
			self thread playCustomEvent();
			break;
		case "response":
			self thread playResponseEvent();
			break;
		case "order":
			self thread playOrderEvent();
			break;
		case "threat":
			self thread playThreatEvent();
			break;
		case "reaction":
			self thread playReactionEvent();
			break;
		case "inform":
			self thread playInformEvent();
			break;
	}
}

//// threat events functions
playThreatEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );
	self endon( "cancel speaking" );

	self.curEvent = self.chatQueue[ "threat" ];

	threat = self.chatQueue[ "threat" ].threat;

	if ( !IsAlive( threat ) )
	{
		return;
	}

	if ( threatWasAlreadyCalledOut( threat ) && !IsPlayer( threat ) )
	{
		return;
	}

	anim thread lockAction( self, "threat" );

	/#
	if ( GetDvar( "debug_bcinteraction" ) == "on" )
		animscripts\utility::showDebugLine( self.origin + ( 0, 0, 50 ), threat.origin + ( 0, 0, 50 ), ( 1, 0, 0 ), 1.5 );
	#/

	success = false;

	switch( self.chatQueue[ "threat" ].eventType )
	{
	case "infantry":
		if ( IsPlayer( threat ) || !IsDefined( threat GetTurret() ) )
		{
			success = self threatInfantry( threat );
		}
		else
		{
			// if we ever want emplacement callouts again, put one here
		}
		break;
	case "dog":
		success = self threatDog( threat );
		break;
	case "vehicle":
		break;
	}

	self notify( "done speaking" );

	if ( !success )
	{
		return;
	}

	if ( !IsAlive( threat ) )
	{
		return;
	}

	threat.calledOut[ self.squad.squadName ] = SpawnStruct();
	threat.calledOut[ self.squad.squadName ].spotter = self;
	threat.calledOut[ self.squad.squadName ].threatType = self.chatQueue[ "threat" ].eventType;
	threat.calledOut[ self.squad.squadName ].expireTime = GetTime() + anim.bcs_threatResetTime;

	if ( IsDefined( threat.squad ) )
	{
		self.squad.squadList[ threat.squad.squadName ].calledOut = true;
	}
}

threatWasAlreadyCalledOut( threat )
{
	if ( IsDefined( threat.calledOut ) && IsDefined( threat.calledOut[ self.squad.squadName ] ) )
	{
		// maybe we can talk about him again if he was previously called out
		if ( threat.calledOut[ self.squad.squadName ].expireTime < GetTime() )
		{
			return true;
		}
	}

	return false;
}

threatInfantry( threat, forceDetail )
{
	self endon( "cancel speaking" );

	chatPhrase = self createChatPhrase();
	chatPhrase.master = true;
	chatPhrase.threatEnt = threat;

	// figure out what kind of callout we want to do
	callout = self getThreatInfantryCalloutType( threat );

	if ( !IsDefined( callout ) || ( IsDefined( callout ) && !IsDefined( callout.type ) ) )
	{
		/*
		printStr = anim.bcPrintFailPrefix + "Couldn't find a threat callout type using getThreatInfantryCalloutType. ";
		
		if( IsDefined( threat ) && IsDefined( threat.classname ) )
		{
			printStr += "Threat classname was: " + threat.classname;
		}
		else if( IsDefined( threat ) && !IsDefined( threat.classname ) )
		{
			printStr += "Threat didn't have a classname!";
		}
		else if( !IsDefined( threat ) )
		{
			printStr += "Threat wasn't defined!";
		}
		
		PrintLn( printStr );
		*/
		return false;
	}

	switch( callout.type )
	{
	case "rpg":

		chatPhrase threatInfantryRPG( threat );
		break;

	case "exposed":

		// not getting enough variety when we count on AIs to see the targets themselves
		//  before responding, so do a simpler diceroll check that we can control better
		//
		// - check for callout.responder because it's not required
		//   for this callout, just nice to have
		doResponse = self doExposedCalloutResponse( callout.responder );

		// if we can say their name, do it
		if ( doResponse && self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		}

		// set up the exposed line to play
		chatPhrase threatInfantryExposed( threat );

		// add a response event, if we decided to do it
		if ( doResponse )
		{
			if ( RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout_negative" ] )
			{
				callout.responder addResponseEvent( "callout", "neg", self, 0.9 );
			}
			else
			{
				callout.responder addResponseEvent( "exposed", "acquired", self, 0.9 );
			}
		}
		break;

	case "player_obvious":
		chatPhrase addPlayerNameAlias();
		chatPhrase addThreatObviousAlias();
		break;

	case "player_distance":
		distance = getDistanceYardsNormalized( level.player.origin, threat.origin );
		chatPhrase addPlayerNameAlias();
		chatPhrase addThreatDistanceAlias( distance );
		break;

//	IW5 DEPRECATED
//	case "player_yourclock":
//
//		chatPhrase addPlayerNameAlias();
//
//		chatPhrase addThreatCalloutAlias( "yourclock", callout.playerClockDirection );
//		break;

	case "player_contact_clock":

		chatPhrase addPlayerNameAlias();

		chatPhrase addThreatCalloutAlias( "contactclock", callout.playerClockDirection );
		break;

	case "player_target_clock":

		chatPhrase addPlayerNameAlias();

		chatPhrase addThreatCalloutAlias( "targetclock", callout.playerClockDirection );
		break;

	case "player_target_clock_high":

		chatPhrase addPlayerNameAlias();

		degreesElevation = getDegreesElevation( level.player.origin, threat.origin );
		
		if ( degreesElevation >= 20 && degreesElevation <= 50 )
		{
			chatPhrase addThreatCalloutAlias( "targetclock", callout.playerClockDirection );
			chatPhrase addThreatElevationAlias( degreesElevation );
		}
		else
			chatPhrase addThreatCalloutAlias( "targetclock", callout.playerClockDirection + "_high" );

		break;

	case "player_cardinal":

		chatPhrase addPlayerNameAlias();

		cardinalDirection = getDirectionCompass( level.player.origin, threat.origin );
		normalizedDirection = normalizeCompassDirection( cardinalDirection );

		if ( normalizedDirection == "impossible" )
		{
			return false;
		}

		chatPhrase addThreatCalloutAlias( "cardinal", normalizedDirection );
		break;

	/* IW5 DEPRECATED
	case "ai_yourclock":

		AssertEx( IsDefined( callout.responder ), "we should have found a valid responder in order to do an ai_yourclock callout!" );

		angles = getRelativeAngles( callout.responder );

		if ( self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		}

		chatPhrase addThreatCalloutAlias( "yourclock", callout.responderClockDirection );

		chatPhrase addCalloutResponseEvent( self, callout, threat );

		break; */
	case "ai_obvious":
		if ( IsDefined( callout.responder ) && self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		}

		chatPhrase addThreatObviousAlias();

		chatPhrase addCalloutResponseEvent( self, callout, threat );

		break;


	case "ai_distance":
		relativeGuy = self;

		if ( self.team == "allies" )
		{
			// make it player relative for allied callouts
			relativeGuy = level.player;
		}
		// for axis, make it relative to a responder if we have one
		else if ( IsDefined( callout.responder )
		 && RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout" ] )
		{
			relativeGuy = callout.responder;
		}
		
		distance = getDistanceYardsNormalized( relativeGuy.origin, threat.origin );
		
		chatPhrase addThreatDistanceAlias( distance );
		
		chatPhrase addCalloutResponseEvent( self, callout, threat );
		
		break;
		
	case "ai_contact_clock":

		relativeGuy = self;

		if ( self.team == "allies" )
		{
			// make it player relative for allied callouts
			relativeGuy = level.player;
		}
		// for axis, make it relative to a responder if we have one
		else if ( IsDefined( callout.responder )
		 && RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout" ] )
		{
			relativeGuy = callout.responder;
		}

		angles = getRelativeAngles( relativeGuy );
		clockDirection = getDirectionFacingClock( angles, relativeGuy.origin, threat.origin );

		/* EDIT: No names for o'clock calls
		if ( IsDefined( callout.responder ) && self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		} */

		chatPhrase addThreatCalloutAlias( "contactclock", clockDirection );

		chatPhrase addCalloutResponseEvent( self, callout, threat );

		break;

	case "ai_target_clock":

		relativeGuy = self;

		if ( self.team == "allies" )
		{
			// make it player relative for allied callouts
			relativeGuy = level.player;
		}
		// for axis, make it relative to a responder if we have one
		else if ( IsDefined( callout.responder )
		 && RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout" ] )
		{
			relativeGuy = callout.responder;
		}

		angles = getRelativeAngles( relativeGuy );
		clockDirection = getDirectionFacingClock( angles, relativeGuy.origin, threat.origin );
		/* EDIT: No names for o'clock calls
		if ( IsDefined( callout.responder ) && self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		} */
		
		chatPhrase addThreatCalloutAlias( "targetclock", clockDirection );

		chatPhrase addCalloutResponseEvent( self, callout, threat );

		break;

	case "ai_target_clock_high":

		relativeGuy = self;

		if ( self.team == "allies" )
		{
			// make it player relative for allied callouts
			relativeGuy = level.player;
		}
		// for axis, make it relative to a responder if we have one
		else if ( IsDefined( callout.responder )
		 && RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout" ] )
		{
			relativeGuy = callout.responder;
		}

		angles = getRelativeAngles( relativeGuy );
		clockDirection = getDirectionFacingClock( angles, relativeGuy.origin, threat.origin );
		degreesElevation = getDegreesElevation( relativeGuy.origin, threat.origin );
		/* EDIT: No names for o'clock calls
		if ( IsDefined( callout.responder ) && self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		} */
		
		if ( degreesElevation >= 20 && degreesElevation <= 50 )
		{
			chatPhrase addThreatCalloutAlias( "targetclock", clockDirection );
			chatPhrase addThreatElevationAlias( degreesElevation );
		}
		else
			chatPhrase addThreatCalloutAlias( "targetclock", clockDirection + "_high" );

		chatPhrase addCalloutResponseEvent( self, callout, threat );

		break;

	case "ai_cardinal":

		relativeGuy = self;

		if ( self.team == "allies" )
		{
			relativeGuy = level.player;
		}

		cardinalDirection = getDirectionCompass( relativeGuy.origin, threat.origin );
		normalizedDirection = normalizeCompassDirection( cardinalDirection );

		if ( normalizedDirection == "impossible" )
		{
			return false;
		}

		chatPhrase addThreatCalloutAlias( "cardinal", normalizedDirection );

		break;

	/* DEPRECATED
	case "player_object_yourclock":

		chatPhrase addPlayerNameAlias();

		success = chatPhrase addThreatCalloutLandmarkAlias( callout.landmark, callout.playerClockDirection, true );
		if ( !success )
		{
			return false;
		}

		break;

	case "player_object_clock":

		chatPhrase addPlayerNameAlias();

		success = chatPhrase addThreatCalloutLandmarkAlias( callout.landmark, callout.playerClockDirection );
		if ( !success )
		{
			return false;
		}

		break;

	case "ai_object_yourclock":

		// SRS TODO add when we have obj_your_[clocknum] aliases
		break;
	*/

	case "generic_location":

		Assert( IsDefined( callout.location ) );

		success = chatPhrase threatInfantry_doCalloutLocation( callout );
		if ( !success )
		{
			return false;
		}

		break;

	case "player_location":

		Assert( IsDefined( callout.location ) );

		chatPhrase addPlayerNameAlias();

		success = chatPhrase threatInfantry_doCalloutLocation( callout );
		if ( !success )
		{
			return false;
		}

		break;

	case "ai_location":

		Assert( IsDefined( callout.location ) );
		AssertEx( IsDefined( callout.responder ), "we should have found a valid responder in order to do an ai_location callout!" );

		if ( self canSayName( callout.responder ) )
		{
			chatPhrase addNameAlias( callout.responder.bcName );
			chatPhrase.lookTarget = callout.responder;
		}

		success = chatPhrase threatInfantry_doCalloutLocation( callout );
		if ( !success )
		{
			return false;
		}

		// the last alias in the soundaliases array is always the one with the actual location info
		index = chatPhrase.soundaliases.size - 1;
		alias = chatPhrase.soundaliases[ index ];

		// if the location alias is a "report" we'll have an "echo" to go with it
		if ( IsCalloutTypeReport( alias ) )
		{
			callout.responder addResponseEvent( "callout", "echo", self, 0.9, alias );
		}
		else if ( IsCalloutTypeQA( alias, self ) )
		{
			callout.responder addResponseEvent( "callout", "QA", self, 0.9, alias, callout.location );
		}
		// otherwise do a generic response
		else
		{
			if ( RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout_negative" ] )
			{
				callout.responder addResponseEvent( "callout", "neg", self, 0.9 );
			}
			else
			{
				callout.responder addResponseEvent( "exposed", "acquired", self, 0.9 );
			}
		}

		break;
	}

	setLastCalloutType( callout.type );

	self playPhrase( chatPhrase );

	return true;
}

doExposedCalloutResponse( responder )
{
	if ( !IsDefined( responder ) )
	{
		return false;
	}

	if ( responder.countryID != "US" && responder.countryID != "NS" && responder.countryID != "TF" )
	{
		return false;
	}

	if ( RandomInt( 100 ) > anim.eventChance[ "response" ][ "exposed" ] )
	{
		return false;
	}

	return true;
}

// self = a chatPhrase
// refEnt = the player or an AI, they will determine where the threat is in worldspace relative to themselves
threatInfantry_doCalloutLocation( callout )
{
	success = self addThreatCalloutLocationAlias( callout.location );

	return success;
}

// self = a chatPhrase
addCalloutResponseEvent( respondTo, callout, threat )
{
	if ( !IsDefined( callout.responder ) )
	{
		return;
	}

	if ( RandomInt( 100 ) > anim.eventChance[ "response" ][ "callout" ] )
	{
		return;
	}

	modifier = "affirm";

	// make sure that the guy can't actually see the enemy while we do the diceroll
	if ( !callout.responder CanSee( threat ) && RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout_negative" ] )
	{
		modifier = "neg";
	}

	callout.responder addResponseEvent( "callout", modifier, respondTo, 0.9 );
}

// figures out what kind of callout to do for infantry threats
// - uses chances from anim.threatCallouts[], matched against callout types in self.allowedCallouts[]
getThreatInfantryCalloutType( threat )
{
	// get info about the AI
	location = threat GetLocation();
	selfClockDirection = getDirectionFacingClock( self.angles, self.origin, threat.origin );

	// try to find a responder
	responder = self getResponder( 64, 1024, "response" );

	responderClockDirection = undefined;
	if ( IsDefined( responder ) )
	{
		responderClockDirection = getDirectionFacingClock( responder.angles, responder.origin, threat.origin );
	}

	// get relative info
//	playerCanSeeThreat = false;
//	if ( self.team == level.player.team )
//	{
//		playerCanSeeThreat = player_can_see_ai( threat );
//	}
//	threatInPlayerFOV = level.player pointInFov( threat.origin );
//	threatInFrontArc = level.player entInFrontArc( threat );	

	playerClockDirection = getDirectionFacingClock( level.player.angles, level.player.origin, threat.origin );

	if ( self.team == "allies" )
	{
		clockDirectionToUse = playerClockDirection;
		relativeGuy = level.player;
	}
	else if ( IsDefined( responder ) )
	{
		clockDirectionToUse = responderClockDirection;
		relativeGuy = responder;
	}
	else
	{
		clockDirectionToUse = selfClockDirection;
		relativeGuy = self;
	}

	distanceYards = getDistanceYards( relativeGuy.origin, threat.origin );

	// now, figure out all possible kinds of callouts that this AI can say
	self.possibleThreatCallouts = [];

	// is it an RPG?
	if ( !IsPlayer( threat ) && threat usingRocketLauncher() )
	{
		self addPossibleThreatCallout( "rpg" );
	}

	// is the threat exposed?
	if ( threat IsExposed() )
	{
		self addPossibleThreatCallout( "exposed" );
	}

	// guys right in front of you either get "obvious" callouts or nothing
	if ( self.team == "allies" )
	{
		calloutHigh = false;
		if ( threat.origin[2] - relativeGuy.origin[2] >= level.heightForHighCallout )
		{
			if ( addPossibleThreatCallout( "player_target_clock_high" ) )
				calloutHigh = true;
		}
		
		if ( !calloutHigh )
		{
			if ( clockDirectionToUse == "12" )
			{
				self addPossibleThreatCallout( "player_obvious" );
				
				if ( distanceYards > level.minDistanceCallout && distanceYards < level.maxDistanceCallout )
					self addPossibleThreatCallout( "player_distance" );
			}
			
			if ( self canSayPlayerName() && clockDirectionToUse != "12" )
			{
				self addPossibleThreatCallout( "player_contact_clock" );
				self addPossibleThreatCallout( "player_target_clock" );
				self addPossibleThreatCallout( "player_cardinal" );
			}
		}
	}

	// can another AI whose name we can say see the threat?
	// EDIT: no mode "your" callouts
	/*
	if ( IsDefined( responder ) && self canSayName( responder ) && enemy_team_name() )
	{
		self addPossibleThreatCallout( "ai_yourclock" );
	}
	*/

	calloutHigh = false;
	if ( threat.origin[2] - relativeGuy.origin[2] >= level.heightForHighCallout )
	{
		if ( addPossibleThreatCallout( "ai_target_clock_high" ) )
			calloutHigh = true;
	}

	if ( !calloutHigh )
	{
		if ( clockDirectionToUse == "12" )
		{
			self addPossibleThreatCallout( "ai_distance" );
			
			if ( distanceYards > level.minDistanceCallout && distanceYards < level.maxDistanceCallout )
				self addPossibleThreatCallout( "ai_obvious" );
		}
		
		self addPossibleThreatCallout( "ai_contact_clock" );
		self addPossibleThreatCallout( "ai_target_clock" );
		self addPossibleThreatCallout( "ai_cardinal" );
	}
	
	/* DEPRECATED
	// is the threat in a landmark trigger?
	if ( IsDefined( landmark ) )
	{
		// only call out landmarks at 10 or 2
		if ( playerClockDirection == "10" || playerClockDirection == "2" )
		{
		
			if ( self canSayPlayerName() )
			{
				self addPossibleThreatCallout( "player_object_yourclock" );
			}

			self addPossibleThreatCallout( "player_object_clock" );
		}

		if ( IsDefined( responder ) && self canSayName( responder ) )
		{
			if ( responderClockDirection == "10" || responderClockDirection == "2" )
			{
				self addPossibleThreatCallout( "ai_object_yourclock" );
			}
		}
	}
	*/

	// is the threat in a location trigger?
	if ( IsDefined( location ) )
	{
		cannedResponse = location GetCannedResponse( self );

		// locations with responses are the best
		if ( IsDefined( cannedResponse ) )
		{
			// if we have an accompanying response line and a responder, don't tell the player because it's cool to have the AI respond
			if ( IsDefined( responder ) )
			{
				self addPossibleThreatCallout( "ai_location" );
			}
			else
			{
				/#
				debugstring = anim.bcPrintWarnPrefix + "Calling out a location at origin " + location.origin + " with a canned response, but there are no AIs able to respond.";
				#/

				if ( self canSayPlayerName() )
				{
					self addPossibleThreatCallout( "player_location" );
				}

				self addPossibleThreatCallout( "generic_location" );
			}
		}
		// otherwise do whichever
		else
		{
			if ( IsDefined( responder ) )
			{
				self addPossibleThreatCallout( "ai_location" );
			}

			if ( self canSayPlayerName() )
			{
				self addPossibleThreatCallout( "player_location" );
			}

			// last ditch effort!
			self addPossibleThreatCallout( "generic_location" );
		}
	}

	if ( !self.possibleThreatCallouts.size )
	{
		return undefined;
	}

	// now figure out which of the possible threat callouts we're actually going to use
	best = getWeightedChanceRoll( self.possibleThreatCallouts, anim.threatCallouts );

	callout = SpawnStruct();
	callout.type = best;
	callout.responder = responder;
	callout.responderClockDirection = responderClockDirection;
	//callout.landmark = landmark;  // DEPRECATED
	callout.playerClockDirection = playerClockDirection;

	if ( IsDefined( location ) )
	{
		callout.location = location;
	}

	//println( "CALLOUT: " + callout.type );

	return callout;
}

// determines whether this kind of location has an alias that could do a canned response
GetCannedResponse( speaker )
{
	cannedResponseAlias = undefined;

	aliases = self.locationAliases;
	foreach ( alias in aliases )
	{
		// always do a "QA" type callout if we can, since it's cooler
		if ( IsCalloutTypeQA( alias, speaker ) && !IsDefined( self.qaFinished ) )
		{
			cannedResponseAlias = alias;
			break;
		}

		// it's ok that we always choose the last one because we randomize them earlier
		if ( IsCalloutTypeReport( alias ) )
		{
			cannedResponseAlias = alias;
		}
	}

	return cannedResponseAlias;
}

IsCalloutTypeReport( alias )
{
	return IsSubStr( alias, "_report" );
}

// tells us whether a given alias can start a back-and-forth conversation about the location
IsCalloutTypeQA( alias, speaker )
{
	// first try to see if it's fully constructed
	if ( IsSubStr( alias, "_qa" ) && SoundExists( alias ) )
	{
		return true;
	}

	// otherwise, maybe we have to add prefix/suffix info
	tryQA = speaker GetQACalloutAlias( alias, 0 );

	if ( SoundExists( tryQA ) )
	{
		return true;
	}

	return false;
}

GetQACalloutAlias( basealias, lineIndex )
{
	alias = self.countryID + "_" + self.npcID + "_co_";
	alias += basealias;
	alias += "_qa" + lineIndex;

	return alias;
}

addAllowedThreatCallout( threatType )
{
	self.allowedCallouts[ self.allowedCallouts.size ] = threatType;
}

addPossibleThreatCallout( threatType )
{
	allowed = false;
	foreach ( calloutType in self.allowedCallouts )
	{
		if ( calloutType == threatType )
		{
			if ( !self calloutTypeWillRepeat( threatType ) )
			{
				allowed = true;
			}
			break;
		}
	}

	if ( !allowed )
	{
		return allowed;
	}

	self.possibleThreatCallouts[ self.possibleThreatCallouts.size ] = threatType;
	return allowed;
}

calloutTypeWillRepeat( threatType )
{
	if ( !IsDefined( anim.lastTeamThreatCallout[ self.team ] ) )
	{
		return false;
	}

	if ( !IsDefined( anim.lastTeamThreatCalloutTime[ self.team ] ) )
	{
		return false;
	}

	lastThreat = anim.lastTeamThreatCallout[ self.team ];
	lastCalloutTime = anim.lastTeamThreatCalloutTime[ self.team ];
	timeout = anim.teamThreatCalloutLimitTimeout;

	if ( ( threatType == lastThreat ) && ( GetTime() - lastCalloutTime < timeout ) )
	{
		return true;
	}

	return false;
}

setLastCalloutType( type )
{
	anim.lastTeamThreatCallout[ self.team ] = type;
	anim.lastTeamThreatCalloutTime[ self.team ] = GetTime();
}

// returns a member of possibleValues[], determined by dicerolling it against all the other
//  members of possibleValues[].
// - chances are provided for each possible value by the values
//   in chancesForValues[], which is indexed by possibleValues, so we can match them up
getWeightedChanceRoll( possibleValues, chancesForValues )
{
	best = undefined;
	bestRoll = -1;// only want to roll once per value so store this off
	foreach ( value in possibleValues )
	{
		// don't consider it if the chance is 0
		if ( chancesForValues[ value ] <= 0 )
		{
			continue;
		}

		thisRoll = RandomInt( chancesForValues[ value ] );

		// if the best is 100+...
		if ( IsDefined( best ) && ( chancesForValues[ best ] >= 100 ) )
		{
			// ...and the new challenger isn't at that level, keep going
			if ( chancesForValues[ value ] < 100 )
			{
				continue;
			}
		}
		// otherwise, if the new challenger is 100+...
		else if ( ( chancesForValues[ value ] >= 100 ) )
		{
			// he wins automatically
			best = value;
			bestRoll = thisRoll;
		}
		// otherwise, everyone else rolls against each other, or 100+'s roll against each other
		else if ( thisRoll > bestRoll )
		{
			best = value;
			bestRoll = thisRoll;
		}
	}

	return best;
}


threatDog( threat, forceDetail )
{
	self endon( "cancel speaking" );
	chatPhrase = self createChatPhrase();

	chatPhrase.master = true;
	chatPhrase.threatEnt = threat;

	// SRS 10/27/08: updated to be more generic until we have actual dog aliases
	chatPhrase addThreatAlias( "dog", "generic" );

	self playPhrase( chatPhrase );
	return true;
}

threatInfantryExposed( threat )
{
	exposedVariants = [];
	exposedVariants = array_add( exposedVariants, "open" );
	exposedVariants = array_add( exposedVariants, "breaking" );

	// only allies get these variants - except Russians, who are usually enemies so we didn't record extras for them
	if ( self.owner.team == "allies" && self.owner.countryID != "RU" )
	{
		// EDIT: Getting rid of oscar mike callouts
		// exposedVariants = array_add( exposedVariants, "oscarmike" );
		exposedVariants = array_add( exposedVariants, "movement" );
	}

	exposedVariant = exposedVariants[ RandomInt( exposedVariants.size ) ];

	self addThreatExposedAlias( exposedVariant );
}

threatInfantryRPG( threat )
{
	self addThreatAlias( "rpg" );
}

//// reaction events functions
playReactionEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	self.curEvent = self.chatQueue[ "reaction" ];

	reactTo = self.chatQueue[ "reaction" ].reactTo;
	modifier = self.chatQueue[ "reaction" ].modifier;

	anim thread lockAction( self, "reaction" );

	switch( self.chatQueue[ "reaction" ].eventType )
	{
		case "casualty":
			self reactionCasualty( reactTo, modifier );
			break;
		case "taunt":
			self reactionTaunt( reactTo, modifier );
			break;
		case "friendlyfire":
			self reactionFriendlyFire( reactTo, modifier );
			break;
	}

	self notify( "done speaking" );
}

reactionCasualty( reactTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addReactionAlias( "casualty", "generic" );

	self playPhrase( chatPhrase );
}

reactionTaunt( reactTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();

	if ( IsDefined( modifier ) && modifier == "hostileburst" )
	{
		chatPhrase addHostileBurstAlias();
	}
	else
	{
		chatPhrase addTauntAlias( "taunt", "generic" );
	}

	self playPhrase( chatPhrase );
}

reactionFriendlyFire( reactTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addCheckFireAlias();

	self playPhrase( chatPhrase );
}

playResponseEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	self.curEvent = self.chatQueue[ "response" ];

	modifier = self.chatQueue[ "response" ].modifier;
	respondTo = self.chatQueue[ "response" ].respondTo;

	if ( !IsAlive( respondTo ) )
	{
		return;
	}

	// if he's responding to a "follow" order, make sure that he's actually moving
	if ( self.chatQueue[ "response" ].modifier == "follow" && self.a.state != "move" )
	{
		return;
	}

	anim thread lockAction( self, "response" );

	/#
	if ( GetDvar( "debug_bcinteraction" ) == "on" )
		animscripts\utility::showDebugLine( self.origin + ( 0, 0, 50 ), respondTo.origin + ( 0, 0, 50 ), ( 1, 1, 0 ), 1.5 );
	#/

	switch( self.chatQueue[ "response" ].eventType )
	{
	case "exposed":
		self responseThreatExposed( respondTo, modifier );
		break;

	case "callout":
		self responseThreatCallout( respondTo, modifier );
		break;

	case "ack":
		self responseGeneric( respondTo, modifier );
		break;
	}

	self notify( "done speaking" );
}

responseThreatExposed( respondTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	if ( !IsAlive( respondTo ) )
	{
		return;
	}

	chatPhrase = self createChatPhrase();
	// these aliases look different from regular responses,
	//  so construct them using addThreatExposedAlias()
	chatPhrase addThreatExposedAlias( modifier );
	chatPhrase.lookTarget = respondTo;
	chatPhrase.master = true;

	self playPhrase( chatPhrase );
}

responseThreatCallout( respondTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	if ( !IsAlive( respondTo ) )
	{
		return;
	}

	chatPhrase = self createChatPhrase();

	success = false;
	if ( modifier == "echo" )
	{
		success = chatPhrase addThreatCalloutEcho( self.curEvent.reportAlias, respondTo );
	}
	else if ( modifier == "QA" )
	{
		success = chatPhrase addThreatCalloutQA_NextLine( respondTo, self.curEvent.reportAlias, self.curEvent.location );
	}
	else
	{
		success = chatPhrase addThreatCalloutResponseAlias( modifier );
	}

	if ( !success )
	{
		return;
	}

	chatPhrase.lookTarget = respondTo;
	chatPhrase.master = true;

	self playPhrase( chatPhrase );
}

responseGeneric( respondTo, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	if ( !IsAlive( respondTo ) )
	{
		return;
	}

	type = self.chatQueue[ "response" ].eventType;

	chatPhrase = self createChatPhrase();
	chatPhrase addResponseAlias( type, modifier );
	chatPhrase.lookTarget = respondTo;
	chatPhrase.master = true;

	self playPhrase( chatPhrase );
}

//// order events functions
playOrderEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	self.curEvent = self.chatQueue[ "order" ];

	modifier = self.chatQueue[ "order" ].modifier;
	orderTo = self.chatQueue[ "order" ].orderTo;

	anim thread lockAction( self, "order" );

	switch( self.chatQueue[ "order" ].eventType )
	{
	case "action":
		self orderAction( modifier, orderTo );
		break;
	case "move":
		self orderMove( modifier, orderTo );
		break;
	case "displace":
		self orderDisplace( modifier );
		break;
	}

	self notify( "done speaking" );
}

orderAction( modifier, orderTo )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();

	self tryOrderTo( chatPhrase, orderTo );

	chatPhrase addOrderAlias( "action", modifier );

	self playPhrase( chatPhrase );
}

orderMove( modifier, orderTo )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();

	/#
	if ( GetDvar( "debug_bcinteraction" ) == "on" && IsDefined( orderTo ) )
		animscripts\utility::showDebugLine( self.origin + ( 0, 0, 50 ), orderTo.origin + ( 0, 0, 50 ), ( 0, 1, 0 ), 1.5 );
	#/

	self tryOrderTo( chatPhrase, orderTo );

	chatPhrase addOrderAlias( "move", modifier );

	self playPhrase( chatPhrase );
}

orderDisplace( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addOrderAlias( "displace", modifier );

	self playPhrase( chatPhrase, true );
}

tryOrderTo( chatPhrase, orderTo )
{
	if ( RandomInt( 100 ) > anim.eventChance[ "response" ][ "order" ] )
	{
		// only return if the orderTo guy isn't the player
		if ( !IsDefined( orderTo ) || ( IsDefined( orderTo ) && !IsPlayer( orderTo ) ) )
		{
			return;
		}
	}

	if ( IsDefined( orderTo ) && IsPlayer( orderTo ) && IsDefined( level.player.bcNameID ) )
	{
		chatPhrase addPlayerNameAlias();
		chatPhrase.lookTarget = level.player;
	}
	else if ( IsDefined( orderTo ) && self canSayName( orderTo ) )
	{
		chatPhrase addNameAlias( orderTo.bcName );
		chatPhrase.lookTarget = orderTo;

		orderTo addResponseEvent( "ack", "yes", self, 0.9 );
	}
	else
	{
		// if we can't specifically respond to someone, throw a notify out there
		//  and hope that someone is around to catch it
		level notify( "follow order", self );
	}
}

//// inform events functions
playInformEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	self.curEvent = self.chatQueue[ "inform" ];

	modifier = self.chatQueue[ "inform" ].modifier;

	anim thread lockAction( self, "inform" );

	switch( self.chatQueue[ "inform" ].eventType )
	{
	case "incoming":
		self informIncoming( modifier );
		break;
	case "attack":
		self informAttacking( modifier );
		break;
	case "reloading":
		self informReloading( modifier );
		break;
	case "suppressed":
		self informSuppressed( modifier );
		break;
	case "killfirm":
		self informKillfirm( modifier );
		break;
	}

	self notify( "done speaking" );
}

informReloading( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addInformAlias( "reloading", modifier );

	self playPhrase( chatPhrase );
}

informSuppressed( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addInformAlias( "suppressed", modifier );

	self playPhrase( chatPhrase );
}

informIncoming( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	if ( modifier == "grenade" )
		chatPhrase.master = true;

	chatPhrase addInformAlias( "incoming", modifier );

	self playPhrase( chatPhrase );
}

informAttacking( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addInformAlias( "attack", modifier );

	self playPhrase( chatPhrase );
}

informKillfirm( modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	chatPhrase = self createChatPhrase();
	chatPhrase addInformAlias( "killfirm", modifier );

	self playPhrase( chatPhrase );
}

//// custom events functions
playCustomEvent()
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	self.curEvent = self.chatQueue[ "custom" ];

	anim thread lockAction( self, self.curEvent.type, true );

	self playPhrase( self.customChatPhrase );

	self notify( "done speaking" );
	self.customChatEvent = undefined;
	self.customChatPhrase = undefined;
}

/****************************************************************************
 utility
*****************************************************************************/

playPhrase( chatPhrase, noSound )
{
	anim endon( "battlechatter disabled" );
	self endon( "death" );

	if ( IsDefined( noSound ) )
	{
		return;
	}
/* Removed this since we have seperate BCS packages for stealth now  --Carlos
//	if ( GetDvar( "bcs_stealth" ) != "" && self.voice == "british" )
	if ( IsDefined( level._stealth ) && ( self voice_is_british_based() ) )
	{
		for ( i = 0; i < chatPhrase.soundAliases.size; i++ )
			chatPhrase.soundAliases[ i ] = chatPhrase.soundAliases[ i ] + "_s";
	}
*/
	if ( self battleChatter_canPrint() || self battleChatter_canPrintDump() )
	{
		bcAliases = [];
		foreach ( alias in chatPhrase.soundAliases )
		{
			bcAliases[ bcAliases.size ] = alias;
		}

		if ( self battleChatter_canPrint() )
		{
			self battleChatter_print( bcAliases );
		}

		if ( self battleChatter_canPrintDump() )
		{
			bcDescriptor = self.curEvent.eventAction + "_" + self.curEvent.eventType;

			if ( IsDefined( self.curEvent.modifier ) )
			{
				bcDescriptor += ( "_" + self.curEvent.modifier );
			}

			self thread battleChatter_printDump( bcAliases, bcDescriptor );
		}
	}

	for ( i = 0; i < chatPhrase.soundAliases.size; i++ )
	{
		// if battlechatter is turned off and this isn't a friendly fire event, don't keep talking
		if ( !self.battleChatter )
		{
			if ( !is_friendlyfire_event( self.curEvent ) )
			{
				continue;
			}
			// hacky! passing false here - don't check the typelimit since we set it early for friendlyfire
			else if ( !self can_say_friendlyfire( false ) )
			{
				continue;
			}
		}

		if ( self._animActive > 0 )
		{
			continue;
		}

		if ( isFiltered( self.curEvent.eventAction ) )
		{
			wait( 0.85 );
			continue;
		}

		if ( !SoundExists( chatPhrase.soundAliases[ i ] ) )
		{
			/#
			PrintLn( anim.bcPrintFailPrefix + "Tried to play an alias that doesn't exist: '" + chatPhrase.soundAliases[ i ] + "'." );
			#/

			continue;
		}

		startTime = GetTime();
		
		// need to spawn an origin to play the sound so sound doesn't occlude because it's
		
		soundOrg = Spawn( "script_origin", self GetTagOrigin( "j_head" ) );
		soundOrg LinkTo( self );

		if ( chatPhrase.master && self.team == "allies" )
		{
			self thread maps\_anim::anim_facialFiller( chatPhrase.soundAliases[ i ], chatPhrase.lookTarget );
			soundOrg PlaySoundAsMaster( chatPhrase.soundAliases[ i ], chatPhrase.soundAliases[ i ], true );
			soundOrg waittill( chatPhrase.soundAliases[ i ] );
			self notify( chatPhrase.soundAliases[ i ] );
		}
		else
		{
			self thread maps\_anim::anim_facialFiller( chatPhrase.soundAliases[ i ], chatPhrase.lookTarget );

			if ( GetDvarInt( "bcs_forceEnglish", 0 ) )
			{
				soundOrg PlaySoundAsMaster( chatPhrase.soundAliases[ i ], chatPhrase.soundAliases[ i ], true );
			}
			else
			{
				soundOrg PlaySound( chatPhrase.soundAliases[ i ], chatPhrase.soundAliases[ i ], true );
			}
			soundOrg waittill( chatPhrase.soundAliases[ i ] );
			
			self notify( chatPhrase.soundAliases[ i ] );
		}
		
		soundOrg Delete();
		
		if ( GetTime() < startTime + 250 )
		{
			// This could mean the alias points to a 'null.wav', or that PlaySound() failed for some other reason.
			//println( anim.bcPrintFailPrefix + "alias exists but sound didn't play: " + chatPhrase.soundAliases[i] );
		}
	}
//	animscripts\shared::LookAtStop();

	self notify( "playPhrase_done" );

	self doTypeLimit( self.curEvent.eventAction, self.curEvent.eventType );
}

is_friendlyfire_event( curEvent )
{
	if ( !IsDefined( curEvent.eventAction ) || !IsDefined( curEvent.eventType ) )
	{
		return false;
	}

	if ( curEvent.eventAction == "reaction" && curEvent.eventType == "friendlyfire" )
	{
		return true;
	}

	return false;
}

isSpeakingFailSafe( eventAction )
{
	self endon( "death" );
	wait( 25 );
	self clearIsSpeaking( eventAction );
}

clearIsSpeaking( eventAction )
{
	self.isSpeaking = false;
	self.chatQueue[ eventAction ].expireTime = 0;
	self.chatQueue[ eventAction ].priority = 0.0;
	self.nextSayTimes[ eventAction ] = GetTime() + anim.eventActionMinWait[ eventAction ][ "self" ];
}

lockAction( speaker, eventAction, customEvent )
{
	anim endon( "battlechatter disabled" );

	Assert( !speaker.isSpeaking );

	squad = speaker.squad;
	team = speaker.team;

	speaker.isSpeaking = true;
	speaker thread isSpeakingFailSafe( eventAction );

	squad.isMemberSaying[ eventAction ] = true;
	squad.numSpeakers++;
	anim.isTeamSpeaking[ team ] = true;
	anim.isTeamSaying[ team ][ eventAction ] = true;

	message = speaker waittill_any_return( "death", "done speaking", "cancel speaking" );

	squad.isMemberSaying[ eventAction ] = false;
	squad.numSpeakers--;
	anim.isTeamSpeaking[ team ] = false;
	anim.isTeamSaying[ team ][ eventAction ] = false;

	if ( message == "cancel speaking" )
	{
		return;
	}

	anim.lastTeamSpeakTime[ team ] = GetTime();

	if ( IsAlive( speaker ) )
	{
		speaker clearIsSpeaking( eventAction );
	}
	squad.nextSayTimes[ eventAction ] = GetTime() + anim.eventActionMinWait[ eventAction ][ "squad" ];
}

updateContact( squadName, member )
{
	if ( GetTime() - self.squadList[ squadName ].lastContact > 10000 )
	{
		isInContact = false;
		for ( i = 0; i < self.members.size; i++ )
		{
			if ( self.members[ i ] != member && IsAlive( self.members[ i ].enemy ) && IsDefined( self.members[ i ].enemy.squad ) && self.members[ i ].enemy.squad.squadName == squadName )
				isInContact = true;
		}

		if ( !isInContact )
		{
			self.squadList[ squadName ].firstContact = GetTime();
			self.squadList[ squadName ].calledOut = false;
		}
	}

	self.squadList[ squadName ].lastContact = GetTime();
}

canSay( eventAction, eventType, priority, modifier )
{
	self endon( "death" );
	self endon( "removed from battleChatter" );

	if ( IsPlayer( self ) )
	{
		return false;
	}

	if ( Distance( level.player.origin, self.origin ) > level.bcs_maxTalkingDistFromPlayer )
	{
		return false;
	}

	// our battlechatter is disabled
	if ( !IsDefined( self.battlechatter ) || !self.battlechatter )
		return( false );

	if ( IsDefined( priority ) && priority >= 1 )
		return( true );

	// we're not allowed to call out a threat now, and won't be able to before it expires
	if ( ( GetTime() + anim.eventActionMinWait[ eventAction ][ "self" ] ) < self.nextSayTimes[ eventAction ] )
		return( false );

	// the squad is not allowed to call out a threat yet and won't be able to before it expires
	if ( ( GetTime() + anim.eventActionMinWait[ eventAction ][ "squad" ] ) < self.squad.nextSayTimes[ eventAction ] )
		return( false );

	if ( IsDefined( eventType ) && typeLimited( eventAction, eventType ) )
		return( false );

	if ( IsDefined( eventType ) && anim.eventPriority[ eventAction ][ eventType ] < self.bcs_minPriority )
		return( false );

	return( true );
}



getHighestPriorityEvent()
{
	prof_begin("getHighestPriorityEvent");
	
	best = undefined;
	bestpriority = -999999999;

	foreach( type, chatQueueEntry in self.chatQueue )
	{
		if ( self isValidEvent( type ) )
		{
			if ( chatQueueEntry.priority > bestpriority )
			{
				best = type;
				bestpriority = chatQueueEntry.priority;
			}
		}
	}

	prof_end("getHighestPriorityEvent");
	return best;
}

getTargettingAI( threat )
{
	squad = self.squad;
	targettingAI = [];
	for ( index = 0; index < squad.members.size; index++ )
	{
		if ( IsDefined( squad.members[ index ].enemy ) && squad.members[ index ].enemy == threat )
			targettingAI[ targettingAI.size ] = squad.members[ index ];
	}

	if ( !IsDefined( targettingAI[ 0 ] ) )
		return( undefined );

	targettingSpeaker = undefined;
	for ( index = 0; index < targettingAI.size; index++ )
	{
		if ( targettingAI[ index ] canSay( "response" ) )
			return( targettingSpeaker );
	}
	return( getClosest( self.origin, targettingAI ) );
}

getQueueEvents()
{
	prof_begin("getQueueEvents");
	queueEvents = [];
	queueEventStates = [];

	queueEvents[ 0 ] = "custom";
	queueEvents[ 1 ] = "response";
	queueEvents[ 2 ] = "order";
	queueEvents[ 3 ] = "threat";
	queueEvents[ 4 ] = "inform";

	for ( i = queueEvents.size - 1; i >= 0; i-- )
	{
		for ( j = 1; j <= i; j++ )
		{
			if ( self.chatQueue[ queueEvents[ j - 1 ] ].priority < self.chatQueue[ queueEvents[ j ] ].priority )
			{
				strTemp = queueEvents[ j - 1 ];
				queueEvents[ j - 1 ] = queueEvents[ j ];
				queueEvents[ j ] = strTemp;
			}
		}
	}

	validEventFound = false;
	for ( i = 0; i < queueEvents.size; i++ )
	{
		eventState = self getEventState( queueEvents[ i ] );

		if ( eventState == " valid" && !validEventFound )
		{
			validEventFound = true;
			queueEventStates[ i ] = "g " + queueEvents[ i ] + eventState + " " + self.chatQueue[ queueEvents[ i ] ].priority;
		}
		else if ( eventState == " valid" )
		{
			queueEventStates[ i ] = "y " + queueEvents[ i ] + eventState + " " + self.chatQueue[ queueEvents[ i ] ].priority;
		}
		else
		{
			if ( self.chatQueue[ queueEvents[ i ] ].expireTime == 0 )
				queueEventStates[ i ] = "b " + queueEvents[ i ] + eventState + " " + self.chatQueue[ queueEvents[ i ] ].priority;
			else
				queueEventStates[ i ] = "r " + queueEvents[ i ] + eventState + " " + self.chatQueue[ queueEvents[ i ] ].priority;
		}
	}

	prof_end("getQueueEvents");
	return queueEventStates;
}

getEventState( strAction )
{
	strState = "";
	if ( self.squad.isMemberSaying[ strAction ] )
		strState += " playing";
	if ( GetTime() > self.chatQueue[ strAction ].expireTime )
		strState += " expired";
	if ( GetTime() < self.squad.nextSayTimes[ strAction ] )
		strState += " cantspeak";

	if ( strState == "" )
		strState = " valid";

	return( strState );
}

isFiltered( strAction )
{
	if ( GetDvar( "bcs_filter" + strAction, "off" ) == "on" || GetDvar( "bcs_filter" + strAction, "off" ) == "1" )
		return( true );

	return( false );
}

isValidEvent( strAction )
{
	if ( !self.squad.isMemberSaying[ strAction ] &&
		!anim.isTeamSaying[ self.team ][ strAction ] &&
		GetTime() < self.chatQueue[ strAction ].expireTime &&
		GetTime() > self.squad.nextSayTimes[ strAction ] )
	{
		// redundant?
		if ( !typeLimited( strAction, self.chatQueue[ strAction ].eventType ) )
			return( true );
	}

	return( false );
}

typeLimited( strAction, strType )
{
	if ( !IsDefined( anim.eventTypeMinWait[ strAction ][ strType ] ) )
		return( false );

	if ( !IsDefined( self.squad.nextTypeSayTimes[ strAction ][ strType ] ) )
		return( false );

	if ( GetTime() > self.squad.nextTypeSayTimes[ strAction ][ strType ] )
		return( false );

	return( true );
}

doTypeLimit( strAction, strType )
{
	if ( !IsDefined( anim.eventTypeMinWait[ strAction ][ strType ] ) )
		return;

	self.squad.nextTypeSayTimes[ strAction ][ strType ] = GetTime() + anim.eventTypeMinWait[ strAction ][ strType ];
}

bcIsSniper()
{
	if ( IsPlayer( self ) )
		return false;

	if ( self isExposed() )
		return false;

	return IsSniperRifle( self.weapon );
}

isExposed()
{
	// if he's too far away, the disadvantage of his exposed state
	//  is negated by contact distance
	if ( Distance( self.origin, level.player.origin ) > 1500 )
	{
		return false;
	}

	// if he's in a "location" that'll be a better way to find him
	if ( IsDefined( self GetLocation() ) )
	{
		return false;
	}

	node = self bcGetClaimedNode();

	// if he doesn't have a claimed node, he's not in cover
	if ( !IsDefined( node ) )
	{
		return true;
	}

	// if the node is cover or conceal, he's not exposed
	if ( !self isNodeCoverOrConceal() )
	{
		return false;
	}

	return true;
}

isNodeCoverOrConceal()
{
	node = self.node;

	if ( !IsDefined( node ) )
	{
		return false;
	}

	if ( IsSubStr( node.type, "Cover" ) || IsSubStr( node.type, "Conceal" ) )
	{
		return true;
	}

	return false;
}

squadHasOfficer( squad )
{
	if ( squad.officerCount > 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

isOfficer()
{
	fullRank = self getRank();

	if ( !IsDefined( fullRank ) )
		return false;

	if ( fullRank == "sergeant"
	 || fullRank == "lieutenant"
	 || fullRank == "captain"
	 || fullRank == "sergeant" )
	{
		return true;
	}

	return false;
}

bcGetClaimedNode()
{
	if ( IsPlayer( self ) )
		return self.node;
	else
		return self GetClaimedNode();
}

enemy_team_name()
{
	if ( self IsBadGuy() )
		return true;
	else
		return false;
}

getName()
{
	if ( enemy_team_name() )
	{
		name = self.ainame;
	}
	else if ( self.team == "allies" )
	{
		name = self.name;
	}
	else
	{
		name = undefined;
	}

	if ( !IsDefined( name ) )
	{
		return( undefined );
	}

	// check to see if this is a name with two parts, like "Sgt. Peas" or "Agent Smith"
	tokens = StrTok( name, " " );
	if ( tokens.size < 2 )
	{
		return( name );
	}

	Assert( tokens.size > 1 );
	return( tokens[ 1 ] );
}

getRank()
{
	return self.airank;
}

getClosestFriendlySpeaker( strAction )
{
	speakers = self getSpeakers( strAction, self.team );

	speaker = getClosest( self.origin, speakers );
	return( speaker );
}

getSpeakers( strAction, team )
{
	speakers = [];

	soldiers = GetAIArray( team );

	for ( i = 0; i < soldiers.size; i++ )
	{
		if ( soldiers[ i ] == self )
		{
			continue;
		}

		if ( !soldiers[ i ] canSay( strAction ) )
		{
			continue;
		}

		speakers[ speakers.size ] = soldiers[ i ];
	}

	return( speakers );
}

// see if self can find someone to respond to him
getResponder( distMin, distMax, eventType )
{
	responder = undefined;

	if ( !IsDefined( eventType ) )
	{
		eventType = "response";
	}

	soldiers = array_randomize( self.squad.members );

	distMin *= distMin;
	distMax *= distMax;

	for ( i = 0; i < soldiers.size; i++ )
	{
		if ( soldiers[ i ] == self )
		{
			continue;
		}

		if ( !IsAlive( soldiers[ i ] ) )
		{
			continue;
		}

		dist_sqrd = DistanceSquared( self.origin, soldiers[ i ].origin );

		if ( dist_sqrd < distMin )
		{
			continue;
		}

		if ( dist_sqrd > distMax )
		{
			continue;
		}

		if ( self isUsingSameVoice( soldiers[ i ] ) )
		{
			continue;
		}

		if ( !soldiers[ i ] canSay( eventType ) )
		{
			continue;
		}

		responder = soldiers[ i ];

		//  prioritize for guys whose names we know how to say
		if ( self canSayName( responder ) )
		{
			break;
		}
	}

	return responder;
}

getLocation()
{
	myLocations = self get_all_my_locations();
	myLocations = array_randomize( myLocations );

	if ( myLocations.size )
	{
		// give us new ones first
		foreach ( location in myLocations )
		{
			if ( !location_called_out_ever( location ) )
			{
				return location;
			}
		}

		// otherwise just get a valid one
		foreach ( location in myLocations )
		{
			if ( !location_called_out_recently( location ) )
			{
				return location;
			}
		}
	}

	return undefined;
}

get_all_my_locations()
{
	allLocations = anim.bcs_locations;
	myLocations = [];

	foreach ( location in allLocations )
	{
		if ( self IsTouching( location ) && IsDefined( location.locationAliases ) )
		{
			myLocations[ myLocations.size ] = location;
		}
	}

	return myLocations;
}

update_bcs_locations()
{
	if ( IsDefined( anim.bcs_locations ) )
	{
		anim.bcs_locations = array_removeUndefined( anim.bcs_locations );
	}
}

is_in_callable_location()
{
	myLocations = self get_all_my_locations();

	foreach ( location in myLocations )
	{
		if ( !location_called_out_recently( location ) )
		{
			return true;
		}
	}

	return false;
}

location_called_out_ever( location )
{
	lastCalloutTime = location_get_last_callout_time( location );
	if ( !IsDefined( lastCalloutTime ) )
	{
		return false;
	}

	return true;
}

location_called_out_recently( location )
{
	lastCalloutTime = location_get_last_callout_time( location );
	if ( !IsDefined( lastCalloutTime ) )
	{
		return false;
	}

	nextCalloutTime = lastCalloutTime + anim.eventActionMinWait[ "threat" ][ "location_repeat" ];
	if ( GetTime() < nextCalloutTime )
	{
		return true;
	}

	return false;
}

location_add_last_callout_time( location )
{
	anim.locationLastCalloutTimes[ location.classname ] = GetTime();
}

location_get_last_callout_time( location )
{
	if ( IsDefined( anim.locationLastCalloutTimes[ location.classname ] ) )
	{
		return anim.locationLastCalloutTimes[ location.classname ];
	}

	return undefined;
}

// if AI is on a cover node, we want to use the node angles to determine threats relative
// to him; this eliminates false callouts in case the AI's cover animation turns him
//  away from the threats
getRelativeAngles( ent )
{
	Assert( IsDefined( ent ) );

	angles = ent.angles;

	if ( !IsPlayer( ent ) )
	{
		node = ent bcGetClaimedNode();
		if ( IsDefined( node ) )
		{
			angles = node.angles;
		}
	}

	return angles;
}

sideIsLeftRight( side )
{
	if ( side == "left" || side == "right" )
	{
		return true;
	}

	return false;
}

/* DEPRECATED but this is a cool function, we should keep it around somewhere
getDirectionReferenceSide( vOrigin, vPoint, vReference )
{
	anglesToReference = VectorToAngles( vReference - vOrigin );
	anglesToPoint = VectorToAngles( vPoint - vOrigin );

	angle = anglesToReference[ 1 ] - anglesToPoint[ 1 ];
	angle += 360;
	angle = Int( angle ) % 360;
	if ( angle > 180 )
		angle -= 360;

	if ( angle > 2 && angle < 45 )
		 side = "right";
	else if ( angle < - 2 && angle > - 45 )
		 side = "left";
	else
	{
		if ( Distance( vOrigin, vPoint ) < Distance( vOrigin, vReference ) )
			side = "front";
		else
			side = "rear";
	}

	return( side );
}
*/

getDirectionFacingFlank( vOrigin, vPoint, vFacing )
{
	anglesToFacing = VectorToAngles( vFacing );
	anglesToPoint = VectorToAngles( vPoint - vOrigin );

	angle = anglesToFacing[ 1 ] - anglesToPoint[ 1 ];
	angle += 360;
	angle = Int( angle ) % 360;

	if ( angle > 315 || angle < 45 )
		direction = "front";
	else if ( angle < 135 )
		direction = "right";
	else if ( angle < 225 )
		direction = "rear";
	else
		direction = "left";

	return( direction );
}

// takes output from getDirectionCompass and normalizes it to the convention
//  used by the soundaliases
normalizeCompassDirection( direction )
{
	Assert( IsDefined( direction ) );

	new = undefined;

	switch( direction )
	{
		case "north":
			new = "n";
			break;
		case "northwest":
			new = "nw";
			break;
		case "west":
			new = "w";
			break;
		case "southwest":
			new = "sw";
			break;
		case "south":
			new = "s";
			break;
		case "southeast":
			new = "se";
			break;
		case "east":
			new = "e";
			break;
		case "northeast":
			new = "ne";
			break;
		case "impossible":
			new = "impossible";
			break;
		default:
			AssertMsg( "Can't normalize compass direction " + direction );
			return;
	}

	Assert( IsDefined( new ) );

	return new;
}

getDirectionCompass( vOrigin, vPoint )
{
	angles = VectorToAngles( vPoint - vOrigin );
	angle = angles[ 1 ];

	northYaw = GetNorthYaw();
	angle -= northYaw;

	if ( angle < 0 )
		angle += 360;
	else if ( angle > 360 )
		angle -= 360;

	if ( angle < 22.5 || angle > 337.5 )
		direction = "north";
	else if ( angle < 67.5 )
		direction = "northwest";
	else if ( angle < 112.5 )
		direction = "west";
	else if ( angle < 157.5 )
		direction = "southwest";
	else if ( angle < 202.5 )
		direction = "south";
	else if ( angle < 247.5 )
		direction = "southeast";
	else if ( angle < 292.5 )
		direction = "east";
	else if ( angle < 337.5 )
		direction = "northeast";
	else
		direction = "impossible";

	return( direction );
}

getDistanceYards( source, target )
{
	distanceInches = Distance2D( source, target );
	distanceYards = 0.0254 * distanceInches; // METERS now, not yards
	return distanceYards;
}

getDistanceYardsNormalized( source, target )
{
	distanceYards = getDistanceYards( source, target );
	if ( distanceYards < 15.0 )
		return "10";
	else if ( distanceYards < 25.0 )
		return "20";
	else if ( distanceYards < 35.0 )
		return "30";	
	else
		return "40";
}
// takes a getDirectionFacingClock value and, if it's in the "front arc" (10-2 on the clock face),
//  will return it normalized to 10, 12, or 2.  Otherwise, returns undefined.
getFrontArcClockDirection( direction )
{
	AssertEx( IsDefined( direction ) );

	faDirection = "undefined";

	if ( direction == "10" || direction == "11" )
	{
		faDirection = "10";
	}
	else if ( direction == "12" )
	{
		faDirection = direction;
	}
	else if ( direction == "1" || direction == "2" )
	{
		faDirection = "2";
	}

	return faDirection;
}

// gets a clock direction from a "viewer" to a "target"
getDirectionFacingClock( viewerAngles, viewerOrigin, targetOrigin )
{
	forward = AnglesToForward( viewerAngles );
	vFacing = VectorNormalize( forward );
	anglesToFacing = VectorToAngles( vFacing );
	anglesToPoint = VectorToAngles( targetOrigin - viewerOrigin );

	angle = anglesToFacing[ 1 ] - anglesToPoint[ 1 ];
	angle += 360;
	angle = Int( angle ) % 360;

	if ( angle > 345 || angle < 15 )
	{
		direction = "12";
	}
	else if ( angle < 45 )
	{
		direction = "1";
	}
	else if ( angle < 75 )
	{
		direction = "2";
	}
	else if ( angle < 105 )
	{
		direction = "3";
	}
	else if ( angle < 135 )
	{
		direction = "4";
	}
	else if ( angle < 165 )
	{
		direction = "5";
	}
	else if ( angle < 195 )
	{
		direction = "6";
	}
	else if ( angle < 225 )
	{
		direction = "7";
	}
	else if ( angle < 255 )
	{
		direction = "8";
	}
	else if ( angle < 285 )
	{
		direction = "9";
	}
	else if ( angle < 315 )
	{
		direction = "10";
	}
	else
	{
		direction = "11";
	}

	return( direction );
}

getDegreesElevation( viewerOrigin, targetOrigin )
{
	ht = targetOrigin[2] - viewerOrigin[2];
	dist = Distance2D( viewerOrigin, targetOrigin );
	
	angle = ATan( ht/dist );
	
	if ( angle < 15 || angle > 55 )
		return angle;
	else if ( angle < 25 )
		return 20;
	else if ( angle < 35 )
		return 30;
	else if ( angle < 45 )
		return 40;
	else if ( angle < 55 )
		return 50;
}

getVectorRightAngle( vDir )
{
	return( vDir[ 1 ], 0 - vDir[ 0 ], vDir[ 2 ] );
}

getVectorArrayAverage( avAngles )
{
	vDominantDir = ( 0, 0, 0 );

	for ( i = 0; i < avAngles.size; i++ )
		vDominantDir += avAngles[ i ];

	return( vDominantDir[ 0 ] / avAngles.size, vDominantDir[ 1 ] / avAngles.size, vDominantDir[ 2 ] / avAngles.size );
}

addNameAlias( name )
{
	self.soundAliases[ self.soundAliases.size ] =
	self.owner.countryID + "_" + self.owner.npcID + "_name_" + name;

	anim.lastNameSaid[ self.owner.team ] = name;
	anim.lastNameSaidTime[ self.owner.team ] = GetTime();
}

addPlayerNameAlias()
{
	if ( !self.owner canSayPlayerName() )
	{
		return;
	}

	anim.lastPlayerNameCallTime = GetTime();

	nameAlias = self.owner.countryID + "_" + self.owner.npcID + "_name_player_" + level.player.bcCountryID + "_" + level.player.bcNameID;

	self.soundAliases[ self.soundAliases.size ] = nameAlias;

	self.lookTarget = level.player;
}

addRankAlias( name )
{
	self.soundAliases[ self.soundAliases.size ] = self.owner.countryID + "_" + self.owner.npcID + "_rank_" + name;
}

canSayName( ai )
{
	// axis don't use names
	if ( enemy_team_name() )
	{
		return false;
	}

	if ( !IsDefined( ai.bcName ) )
	{
		return false;
	}

	// don't say my name if i'm not using battlechatter
	if ( ai.battlechatter == false )
	{
		return false;
	}

	// SRE'd so added this defensive mechanism
	if ( !IsDefined( ai.countryID ) )
	{
		return false;
	}

	// don't want to cross the streams for AI names in mixed-nationality squads
	if ( self.countryID != ai.countryID )
	{
		return false;
	}

	// make sure we don't say this names too frequently
	if ( self nameSaidRecently( ai ) )
	{
		return false;
	}

	nameAlias = self.countryID + "_" + self.npcID + "_name_" + ai.bcName;

	if ( SoundExists( nameAlias ) )
	{
		return true;
	}

	return false;
}

nameSaidRecently( ai )
{
	if ( ( anim.lastNameSaid[ self.team ] == ai.bcName ) || ( ( GetTime() - anim.lastNameSaidTime[ self.team ] ) < anim.lastNameSaidTimeout ) )
	{
		return true;
	}

	return false;
}

canSayPlayerName()
{
	if ( enemy_team_name() )
	{
		return false;
	}

	if ( !IsDefined( level.player.bcNameID ) || !IsDefined( level.player.bcCountryID ) )
	{
		return false;
	}

	if ( player_name_called_recently() )
	{
		return false;
	}

	nameAlias = self.countryID + "_" + self.npcID + "_name_player_" + level.player.bcCountryID + "_" + level.player.bcNameID;

	if ( SoundExists( nameAlias ) )
	{
		return true;
	}

	return false;
}

player_name_called_recently()
{
	if ( !IsDefined( anim.lastPlayerNameCallTime ) )
	{
		return false;
	}

	if ( GetTime() - anim.lastPlayerNameCallTime >= anim.eventTypeMinWait[ "playername" ] )
	{
		return false;
	}

	return true;
}

isUsingSameVoice( otherguy )
{
	/#
	if ( GetDvar( "bcs_allowsamevoiceresponse" ) == "on" )
	{
		return false;
	}
	#/

	if ( ( IsString( self.npcID ) && IsString( otherguy.npcID ) ) && ( self.npcID == otherguy.npcID ) )
	{
		return true;
	}
	else if ( ( !isString( self.npcID ) && !isString( otherguy.npcID ) ) && ( self.npcID == otherguy.npcID ) )
	{
		return true;
	}
	else
	{
		return false;
	}
}

// format: US_1_threat_[type], with optional _[modifier]
addThreatAlias( type, modifier )
{
	Assert( IsDefined( type ) );

	threat = self.owner.countryID + "_" + self.owner.npcID + "_threat_" + type;

	// not all threat aliases use modifiers anymore
	if ( IsDefined( modifier ) )
	{
		threat += ( "_" + modifier );
	}

	self.soundAliases = array_add( self.soundAliases, threat );
	return true;
}

// format: US_1_exposed_[type]
addThreatExposedAlias( type )
{
	Assert( IsDefined( type ) );

	alias = self.owner.countryID + "_" + self.owner.npcID + "_exposed_" + type;

	self.soundAliases[ self.soundAliases.size ] = alias;
	return true;
}

// format: US_1_order_action_suppress
addThreatObviousAlias()
{
	// just using the order_action_suppress aliases
	alias = self.owner.countryID + "_" + self.owner.npcID + "_order_action_suppress";

	self.soundAliases[ self.soundAliases.size ] = alias;

	return true;
}

addThreatDistanceAlias( distance )
{
	// just using the order_action_suppress aliases
	alias = self.owner.countryID + "_" + self.owner.npcID + "_co_dist_" + distance;

	self.soundAliases[ self.soundAliases.size ] = alias;

	return true;
}

addThreatElevationAlias( angle )
{
	// just using the order_action_suppress aliases
	alias = self.owner.countryID + "_" + self.owner.npcID + "_co_elev_" + angle;

	self.soundAliases[ self.soundAliases.size ] = alias;

	return true;
}

// format: [reportAlias]_echo ("_echo" replaces "_report" in the reportAlias)
addThreatCalloutEcho( reportAlias, respondTo )
{
	Assert( IsDefined( reportAlias ) );

	alias = self createEchoAlias( reportAlias, respondTo );

	if ( !SoundExists( alias ) )
	{
		/#
		PrintLn( anim.bcPrintFailPrefix + "Can't find echo alias '" + alias + "'." );
		#/
		// TODO maybe output to data csv/txt file later
		return false;
	}

	self.soundAliases[ self.soundAliases.size ] = alias;
	return true;
}

// format: US_1_resp_ack_co_gnrc_[affirm/neg]
addThreatCalloutResponseAlias( modifier )
{
	Assert( IsDefined( modifier ) );

	alias = self.owner.countryID + "_" + self.owner.npcID + "_resp_ack_co_gnrc_" + modifier;

	if ( !SoundExists( alias ) )
	{
		/#
		PrintLn( anim.bcPrintFailPrefix + "Can't find callout response alias '" + alias + "'." );
		#/
		// TODO maybe output to data csv/txt file later
		return false;
	}

	self.soundAliases[ self.soundAliases.size ] = alias;
	return true;
}

addThreatCalloutQA_NextLine( respondTo, prevLine, location )
{
	Assert( IsDefined( respondTo ) && IsDefined( prevLine ) );

	// figure out the partial alias so we can reconstruct it later
	// this is easier than parsing out the prevLine to just get the meat
	partialAlias = undefined;
	foreach ( str in location.locationAliases )
	{
		if ( IsSubStr( prevLine, str ) )
		{
			partialAlias = str;
			break;
		}
	}
	Assert( IsDefined( partialAlias ) );

	// now try to construct the new string
	prefix = self.owner.countryID + "_" + self.owner.npcID + "_co_";
	lastChar = GetSubStr( prevLine, prevLine.size - 1, prevLine.size );
	Assert( string_is_single_digit_integer( lastChar ) );
	nextIndex = Int( lastChar ) + 1;

	qaAlias = prefix + partialAlias + "_qa" + nextIndex;

	if ( !SoundExists( qaAlias ) )
	{
		// finish up the conversation with a yes/no response
		if ( RandomInt( 100 ) < anim.eventChance[ "response" ][ "callout_negative" ] )
		{
			respondTo addResponseEvent( "callout", "neg", self.owner, 0.9 );
		}
		else
		{
			respondTo addResponseEvent( "exposed", "acquired", self.owner, 0.9 );
		}

		// from now on we'll use the base alias to refer to it since we talked about it already
		location.qaFinished = true;

		return false;
	}

	// keep the QA conversation going, potentially
	respondTo addResponseEvent( "callout", "QA", self.owner, 0.9, qaAlias, location );

	self.soundAliases[ self.soundAliases.size ] = qaAlias;
	return true;
}


// takes a soundalias that ends with "_report" and returns a variant of it that ends with "_echo"
createEchoAlias( reportAlias, respondTo )
{
	reportSuffix = "_report";
	echoSuffix = "_echo";

	// make sure that we're responding in the responder's countryID and voice
	echoPrefix = self.owner.countryID + "_" + self.owner.npcID + "_";

	AssertEx( IsSubStr( reportAlias, reportSuffix ), "reportAlias doesn't have substring '" + reportSuffix + "', so it doesn't look like an eligible report alias." );

	reportSuffixStartIndex = reportAlias.size - reportSuffix.size;// figure out where the end of this baseAlias is
	
	// some guys have longer npcIDs than others, so we have to allow the base prefix to be variable length
	oldPrefix = self.owner.countryID + "_" + respondTo.npcID + "_";
	oldPrefixLength = oldPrefix.size;
	
	baseAlias = GetSubStr( reportAlias, oldPrefixLength, reportSuffixStartIndex );// start 5 spots in to eliminate the original countryID and npcID info

	// construct the final alias
	echoAlias = echoPrefix + baseAlias + echoSuffix;

	return echoAlias;
}

// format: US_1_callout_[contactclock/targetclock/yourclock/cardinal]_[modifier]
addThreatCalloutAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );

	alias = self.owner.countryID + "_" + self.owner.npcID + "_callout_" + type + "_" + modifier;

	self.soundAliases[ self.soundAliases.size ] = alias;
	return true;
}

// "landmarks" are aka "objects" in the soundaliases
// format: US_1_callout_obj_[landmark]_your(optional)_[frontArcDirection]
//  - isRelative dictates if we will add the "your" to the string
addThreatCalloutLandmarkAlias( landmark, frontArcDirection, isRelative )
{
	Assert( IsDefined( landmark ) && IsDefined( frontArcDirection ) );

	landmarkStr = landmark.script_landmark;

	if ( !IsDefined( isRelative ) )
	{
		isRelative = false;
	}

	alias = self.owner.countryID + "_" + self.owner.npcID + "_callout_obj_" + landmarkStr;
	if ( isRelative )
	{
		alias += "_y";
	}
	alias += "_" + frontArcDirection;

	if ( !SoundExists( alias ) )
	{
		/#
		PrintLn( anim.bcPrintFailPrefix + "Can't find sound alias '" + alias + "'. Does landmark '" + landmarkStr + "' have callout references in the battlechatter csv for nationality '" + self.owner.countryID + "'?" );
		#/
		// TODO maybe output to data csv/txt file later
		return false;
	}

	self.soundAliases[ self.soundAliases.size ] = alias;
	return true;
}

// format: US_1_co_[location.locationAliases[idx]]
// -- oldstyle format: US_1_callout_loc_[location](optional if floor exists)_[floor](optional if location exists)_[left/right](optional)_report(optional)
addThreatCalloutLocationAlias( location )
{
	Assert( IsDefined( location ) && IsDefined( location.locationAliases ) );

	finalAlias = undefined;

	// some triggers have more than one alias set up
	locationAliases = location.locationAliases;
	Assert( locationAliases.size );

	locAlias = locationAliases[ 0 ];

	if ( locationAliases.size > 1 )
	{
		// prefer aliases that make the AIs talk more
		responseAlias = undefined;
		responseAlias = location GetCannedResponse( self.owner );
		if ( IsDefined( responseAlias ) )
		{
			locAlias = responseAlias;
		}
		else
		{
			// otherwise just randomize it
			locAlias = random( locationAliases );
		}
	}

	alias = undefined;

	// see if this is a QA conversation that hasn't been finished
	if ( !IsDefined( location.qaFinished ) && IsCalloutTypeQA( locAlias, self.owner ) )
	{
		alias = self.owner GetQACalloutAlias( locAlias, 0 );
	}
	else
	{
		// standard prefix
		prefix = self.owner.countryID + "_" + self.owner.npcID + "_";

		// this separates oldstyle location callouts so we can use some older assets
		//  - in the future we'll just add the rest of the prefix string above
		if ( !IsSubStr( locAlias, "callout" ) )
		{
			prefix += "co_";// the newstyle standard
		}

		alias = prefix + locAlias;
	}

	if ( SoundExists( alias ) )
	{
		finalAlias = alias;
	}

	if ( !IsDefined( finalAlias ) )
	{
		/#
		printStr = anim.bcPrintFailPrefix + "Couldn't find a location callout alias for data:";
		if ( IsDefined( location ) )
		{
			printStr += " location=" + locAlias;
		}
		if ( IsDefined( alias ) )
		{
			printStr += " finalAlias=" + alias;
		}
		printStr += ". Are you sure that there is an alias to support it?";

		PrintLn( printStr );
		// TODO maybe output to data csv/txt file later
		#/

		return false;
	}

	location_add_last_callout_time( location );
	self.soundAliases[ self.soundAliases.size ] = finalAlias;
	return true;
}

addInformAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );

	alias = self.owner.countryID + "_" + self.owner.npcID + "_inform_" + type + "_" + modifier;

	self.soundAliases[ self.soundAliases.size ] = alias;
}

addResponseAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );

	alias = self.owner.countryID + "_" + self.owner.npcID + "_response_" + type + "_" + modifier;
	self.soundAliases[ self.soundAliases.size ] = alias;

	return( true );
}

addReactionAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );
	reaction = self.owner.countryID + "_" + self.owner.npcID + "_reaction_" + type + "_" + modifier;
	self.soundAliases[ self.soundAliases.size ] = reaction;

	return( true );
}

addCheckFireAlias()
{
	reaction = self.owner.countryID + "_" + self.owner.npcID + "_check_fire";
	self.soundAliases[ self.soundAliases.size ] = reaction;

	return true;
}

addTauntAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );
	reaction = self.owner.countryID + "_" + self.owner.npcID + "_taunt";
	self.soundAliases[ self.soundAliases.size ] = reaction;

	return( true );
}

// format: GE_1_hostile_burst
addHostileBurstAlias()
{
	burst = self.owner.countryID + "_" + self.owner.npcID + "_hostile_burst";
	self.soundAliases[ self.soundAliases.size ] = burst;

	return true;
}

// format: US_1_order_move_follow (etc.)
addOrderAlias( type, modifier )
{
	Assert( IsDefined( type ) && IsDefined( modifier ) );

	order = self.owner.countryID + "_" + self.owner.npcID + "_order_" + type + "_" + modifier;
	self.soundAliases[ self.soundAliases.size ] = order;

	return true;
}

initContact( squadName )
{
	if ( !IsDefined( self.squadList[ squadName ].calledOut ) )
		self.squadList[ squadName ].calledOut = false;

	if ( !IsDefined( self.squadList[ squadName ].firstContact ) )
		self.squadList[ squadName ].firstContact = 2000000000;

	if ( !IsDefined( self.squadList[ squadName ].lastContact ) )
		self.squadList[ squadName ].lastContact = 0;
}

shutdownContact( squadName )
{
	self.squadList[ squadName ].calledOut = undefined;
	self.squadList[ squadName ].firstContact = undefined;
	self.squadList[ squadName ].lastContact = undefined;
}

createChatEvent( eventAction, eventType, priority )
{
	chatEvent = SpawnStruct();
	chatEvent.owner = self;
	chatEvent.eventType = eventType;
	chatEvent.eventAction = eventAction;

	if ( IsDefined( priority ) )
		chatEvent.priority = priority;
	else
		chatEvent.priority = anim.eventPriority[ eventAction ][ eventType ];

	chatEvent.expireTime = GetTime() + anim.eventDuration[ eventAction ][ eventType ];

	return chatEvent;
}

createChatPhrase()
{
	chatPhrase = SpawnStruct();
	chatPhrase.owner = self;
	chatPhrase.soundAliases = [];
	chatPhrase.master = false;

	return chatPhrase;
}

pointInFov( origin )
{
	return within_fov( self.origin, self.angles, origin, 0.766 );	// fov = 80
}

// the "front arc" goes from 9 to 3 on a clock face - the front 180 degrees
entInFrontArc( ent )
{
	return within_fov( self.origin, self.angles, ent.origin, 0 );
}

/****************************************************************************
 flavor burst transmissions
*****************************************************************************/

// self = the squad
squadFlavorBurstTransmissions()
{
	anim endon( "battlechatter disabled" );
	self endon( "squad_deleting" );

	if ( self.team != "allies" )
	{
		// hackish, don't need it to be more complicated for now though
		if ( level.script != "af_caves" )
		{
			return;
		}
	}

	// wait until an AI gets put in the squad
	while ( self.memberCount <= 0 )
	{
		wait( 0.5 );
	}

	// don't do regular waits if we're coming back from flavorbursts being disabled
	burstingWasPaused = false;

	while ( IsDefined( self ) )
	{
		// make sure at least one of the guys in the squad can burst
		if ( !squadCanBurst( self ) )
		{
			burstingWasPaused = true;

			wait( 1 );
			continue;
		}
		else if ( self.fbt_firstBurst )
		{
			if ( !burstingWasPaused )
			{
				wait( RandomFloat( anim.fbt_waitMin ) );
			}

			if ( burstingWasPaused )
			{
				burstingWasPaused = false;
			}

			self.fbt_firstBurst = false;
		}
		else
		{
			if ( !burstingWasPaused )
			{
				wait( RandomFloatRange( anim.fbt_waitMin, anim.fbt_waitMax ) );
			}

			if ( burstingWasPaused )
			{
				burstingWasPaused = false;
			}
		}

		burster = getBurster( self );

		if ( !IsDefined( burster ) )
		{
			continue;
		}

		nationality = burster.voice;
		burstID = getFlavorBurstID( self, nationality );
		aliases = getFlavorBurstAliases( nationality, burstID );

		foreach ( i, alias in aliases )
		{
			// see if we need to migrate our burster
			if ( !burster canDoFlavorBurst() || Distance( level.player.origin, burster.origin ) > anim.fbt_desiredDistMax )
			{
				for ( j = 0; j < self.members.size; j++ )
				{
					burster = getBurster( self );

					if ( !IsDefined( burster ) )
					{
						continue;
					}

					// to continue the burst transmission, we want to stick with the same
					//  nationality - this is in case we have a squad of mixed nationalities
					if ( burster.voice == nationality )
					{
						break;
					}
				}

				// if we can't find a new burster of the same nationality,
				//  quit this transmission
				if ( !IsDefined( burster ) || burster.voice != nationality )
				{
					break;
				}
			}

			// play the burst
			self thread playFlavorBurstLine( burster, alias );
			self waittill( "burst_line_done" );

			if ( i != ( aliases.size - 1 ) )
			{
				wait( RandomFloatRange( anim.fbt_lineBreakMin, anim.fbt_lineBreakMax ) );
			}
		}
	}
}

squadCanBurst( squad )
{
	foundOne = false;
	foreach ( member in squad.members )
	{
		if ( member canDoFlavorBurst() )
		{
			foundOne = true;
			break;
		}
	}

	return foundOne;
}

canDoFlavorBurst()
{
	canDo = false;

	if ( !IsPlayer( self )
	 && IsAlive( self )
	 && self.classname != "actor_enemy_dog"
	 && level.flavorbursts[ self.team ]
	 && self voiceCanBurst()
	 && self.flavorbursts )
	{
		canDo = true;
	}

	return canDo;
}

voiceCanBurst()
{
	if ( IsDefined( anim.flavorburstVoices[ self.voice ] ) && anim.flavorburstVoices[ self.voice ] )
	{
		return true;
	}

	return false;
}

getBurster( squad )
{
	burster = undefined;
	// prioritize by player proximity
	//  for some reason, get_array_of_farthest returns the closest at index 0
	squadMembers = get_array_of_farthest( level.player.origin, squad.members );

	foreach ( guy in squadMembers )
	{
		if ( guy canDoFlavorBurst() )
		{
			burster = guy;

			if ( !IsDefined( squad.fbt_lastBursterID ) )
			{
				break;
			}

			// try not to play it off the last guy we played it off of
			if ( IsDefined( squad.fbt_lastBursterID ) && squad.fbt_lastBursterID == burster.unique_id )
			{
				continue;
			}
		}
	}

	if ( IsDefined( burster ) )
	{
		// store the ent's unique ID because the ent could be gone by the time we check again
		squad.fbt_lastBursterID = burster.unique_id;
	}

	return burster;
}

getFlavorBurstID( squad, nationality )
{
	bursts = array_randomize( anim.flavorbursts[ nationality ] );

	// if we used all of the flavor bursts already, reset
	if ( anim.flavorburstsUsed.size >= bursts.size )
	{
		anim.flavorburstsUsed = [];
	}

	burstID = undefined;
	foreach ( burst in bursts )
	{
		burstID = burst;

		if ( !flavorBurstWouldRepeat( burstID ) )
		{
			break;
		}
	}

	anim.flavorburstsUsed[ anim.flavorburstsUsed.size ] = burstID;
	return burstID;
}

flavorBurstWouldRepeat( burstID )
{
	if ( !anim.flavorburstsUsed.size )
	{
		return false;
	}

	foundIt = false;
	foreach ( usedBurst in anim.flavorburstsUsed )
	{
		if ( usedBurst == burstID )
		{
			foundIt = true;
			break;
		}
	}

	return foundIt;
}

getFlavorBurstAliases( nationality, burstID, startingLine )
{
	if ( !IsDefined( startingLine ) )
	{
		startingLine = 1;
	}

	burstLine = startingLine;
	aliases = [];

	while ( 1 )
	{
		alias = "FB_" + anim.countryIDs[ nationality ] + "_" + burstID + "_" + burstLine;

		burstLine++;

		if ( SoundExists( alias ) )
		{
			aliases[ aliases.size ] = alias;
		}
		else
		{
			break;
		}
	}

	return aliases;
}

playFlavorBurstLine( burster, alias )
{
	anim endon( "battlechatter disabled" );

	/#
	if ( GetDvar( "bcs_fbt_debug" ) == "on" )
	{
		self thread flavorBurstLineDebug( burster, alias );
	}
	#/

	// make a separate origin to play the sound off of so that mission dialogue doesn't get cut off when played on this guy at the same time
	soundOrg = Spawn( "script_origin", burster GetTagOrigin( "j_head" ) );
	soundOrg LinkTo( burster );

	soundOrg PlaySound( alias, alias, true );
	soundOrg waittill( alias );

	soundOrg Delete();

	if ( IsDefined( self ) )
		self notify( "burst_line_done" );
}

flavorBurstLineDebug( burster, alias )
{
	self endon( "burst_line_done" );

	while ( 1 )
	{
		Print3d( burster GetTagOrigin( "j_spinelower" ), alias, ( 1, 1, 1 ), 1, 0.5 );
		wait( 0.05 );
	}
}

/****************************************************************************
 debugging functions
*****************************************************************************/

 /*
debugPrintEvents()
{
	if ( !isalive( self ) )
		return;

	if ( GetDvar( "debug_bcshowqueue" ) != self.team && GetDvar( "debug_bcshowqueue" ) != "all" )
		return;

	self endon( "death" );
	self notify( "debugPrintEvents" );
	self endon( "debugPrintEvents" );

	queueEvents = self getQueueEvents();
	colors[ "g" ] = ( 0, 1, 0 );
	colors[ "y" ] = ( 1, 1, 0 );
	colors[ "r" ] = ( 1, 0, 0 );
	colors[ "b" ] = ( 0, 0, 0 );

	while ( 1 )
	{
		aboveHead = self GetShootAtPos() + ( 0, 0, 10 );
		for ( i = 0; i < queueEvents.size; i++ )
		{
			Print3d( aboveHead, queueEvents[ i ], colors[ queueEvents[ i ][ 0 ] ], 1, 0.5 );	// origin, text, RGB, alpha, scale
			aboveHead += ( 0, 0, 5 );
		}
		wait 0.05;
	}
}

debugQueueEvents()
{
	if ( GetDvar( "debug_bcresponse" ) == "on" )
		self thread printQueueEvent( "response" );
	if ( GetDvar( "debug_bcthreat" ) == "on" )
		self thread printQueueEvent( "threat" );
	if ( GetDvar( "debug_bcinform" ) == "on" )
		self thread printQueueEvent( "inform" );
	if ( GetDvar( "debug_bcorder" ) == "on" )
		self thread printQueueEvent( "order" );
}

printAboveHead( string, duration, offset )
{
	self endon( "death" );

	if ( !IsDefined( offset ) )
		offset = ( 0, 0, 0 );

	for ( i = 0; i < ( duration * 2 ); i++ )
	{
		if ( !isalive( self ) )
			return;

		aboveHead = self GetShootAtPos() + ( 0, 0, 10 ) + offset;
		Print3d( aboveHead, string, ( 1, 0, 0 ), 1, 0.5 );	// origin, text, RGB, alpha, scale
		wait 0.05;
	}
}

printQueueEvent( eventAction )
{
	time = GetTime();

	if ( self.chatQueue[ eventAction ].expireTime > 0 && !IsDefined( self.chatQueue[ eventAction ].printed ) )
	{
		Print( "QUEUE EVENT " + eventAction + "_" + self.chatQueue[ eventAction ].eventType + ": " );
		if ( time > self.chatQueue[ eventAction ].expireTime )
			PrintLn( "^2 missed by " + ( time - self.chatQueue[ eventAction ].expireTime ) + "ms" );
		else
			PrintLn( "slack of " + ( self.chatQueue[ eventAction ].expireTime - time ) + "ms" );

		self.chatQueue[ eventAction ].printed = true;
	}
}
*/

battleChatter_canPrint()
{
/#
	if ( GetDebugDvar( "debug_bcprint" ) == self.team || GetDebugDvar( "debug_bcprint" ) == "all" )
		return( true );
#/
	return( false );
}

battleChatter_canPrintDump()
{
/#
	if ( GetDebugDvar( "debug_bcprintdump" ) == self.team || GetDebugDvar( "debug_bcprintdump" ) == "all" )
	{
		return true;
	}
#/
	return false;
}

// SRS 10/16/08: this used to be unnecessarily covered with two functions
battleChatter_print( aliases )
{
	if ( aliases.size <= 0 )
	{
		AssertMsg( "battleChatter_print(): the aliases array is empty." );
		return;
	}

	if ( !self battleChatter_canPrint() )
	{
		return;
	}

	colorPrefix = "^5 ";// allies
	if ( enemy_team_name() )
	{
		colorPrefix = "^6 ";
	}

	// print to the console
	Print( colorPrefix );

	foreach ( alias in aliases )
	{
		Print( alias );
	}

	PrintLn( "" );
}

// optionally dumps info out to files for examination later
battleChatter_printDump( aliases, descriptor )
{
/#
	if ( !self battleChatter_canPrintDump() )
	{
		return;
	}

	if ( aliases.size <= 0 )
	{
		AssertMsg( "battleChatter_printDump(): the aliases array is empty." );
		return;
	}

	dumpType = GetDvar( "debug_bcprintdumptype" );
	if ( dumpType != "csv" && dumpType != "txt" )
	{
		return;
	}

	// do this early, in case the file writing hangs for a bit of time
	secsSinceLastDump = -1;
	if ( IsDefined( level.lastDumpTime ) )
	{
		secsSinceLastDump = ( GetTime() - level.lastDumpTime ) / 1000;
	}

	level.lastDumpTime = GetTime();// reset

	// -- CSV dumps help the audio dept optimize where they spend their time --
	if ( dumpType == "csv" )
	{
		// only 1 write at a time
		if ( !flag_exist( "bcs_csv_dumpFileWriting" ) )
		{
			flag_init( "bcs_csv_dumpFileWriting" );
		}

		// open the file, if it's not already open
		if ( !IsDefined( level.bcs_csv_dumpFile ) )
		{
			filePath = "scriptgen/battlechatter/bcsDump_" + level.script + ".csv";
			level.bcs_csv_dumpFile = OpenFile( filePath, "write" );
		}

		// dump a new line for each sound
		// format: levelname,countryID,npcID,aliasType
		foreach ( alias in aliases )
		{
			aliasType = getAliasTypeFromSoundalias( alias );

			dumpString = level.script + ","
			 + self.countryID + ","
			 + self.npcID + ","
			 + aliasType;

			battleChatter_printDumpLine( level.bcs_csv_dumpFile, dumpString, "bcs_csv_dumpFileWriting" );
		}
	}

	// -- TXT dumps help the design dept tweak distributions and timing --
	else if ( dumpType == "txt" )
	{
		AssertEx( IsDefined( descriptor ), "battlechatter print dumps of type 'txt' require a descriptor!" );

		if ( !flag_exist( "bcs_txt_dumpFileWriting" ) )
		{
			flag_init( "bcs_txt_dumpFileWriting" );
		}

		if ( !IsDefined( level.bcs_txt_dumpFile ) )
		{
			filePath = "scriptgen/battlechatter/bcsDump_" + level.script + ".txt";
			level.bcs_txt_dumpFile = OpenFile( filePath, "write" );
		}

		name = self.name;
		if ( enemy_team_name() )
		{
			name = self.ainame;
		}

		// format: (2.3 secs) US_1 order_move_follow: US_1_threat_rpg_generic, US_1_landmark_near_cargocontainer, US_1_direction_relative_north
		dumpString = "(" + secsSinceLastDump + " secs) ";
		dumpString += name + " " + descriptor + ": ";
		foreach ( i, alias in aliases )
		{
			dumpString += alias;
			if ( i != ( aliases.size - 1 ) )
			{
				dumpString += ", ";
			}
		}

		battleChatter_printDumpLine( level.bcs_txt_dumpFile, dumpString, "bcs_txt_dumpFileWriting" );
	}
#/
}

getAliasTypeFromSoundalias( alias )
{
	// get the prefix and make sure it matches as we'd expect
	prefix = self.countryID + "_" + self.npcID + "_";
	AssertEx( IsSubStr( alias, prefix ), "didn't find expected prefix info in alias '" + alias + "' with substr test of '" + prefix + "'." );

	// figure out the alias type by removing the prefix
	aliasType = GetSubStr( alias, prefix.size, alias.size );

	return aliasType;
}

battleChatter_printDumpLine( file, str, controlFlag )
{
	if ( flag( controlFlag ) )
	{
		flag_wait( controlFlag );
	}
	flag_set( controlFlag );

	FPrintLn( file, str );

	flag_clear( controlFlag );
}

bcDrawObjects()
{
	for ( i = 0; i < anim.bcs_locations.size; i++ )
	{
		locationAliases = anim.bcs_locations[ i ].locationAliases;

		if ( !IsDefined( locationAliases ) )
		{
			continue;
		}

		locationStr = "";
		foreach ( alias in locationAliases )
		{
			locationStr += alias;
		}
		thread drawBCObject( "Location: " + locationStr, anim.bcs_locations[ i ] GetOrigin(), ( 0, 0, 8 ), ( 1, 1, 1 ) );
	}
}

drawBCObject( string, origin, offset, color )
{
	while ( true )
	{
		if ( Distance( level.player.origin, origin ) > 2048 )
		{
			wait( 0.1 );
			continue;
		}

		Print3d( origin + offset, string, color, 1, 0.75 );	// origin, text, RGB, alpha, scale
		wait 0.05;
	}
}

drawBCDirections( landmark, offset, color )
{
	landmarkOrigin = landmark GetOrigin();

	while ( true )
	{
		if ( Distance( level.player.origin, landmarkOrigin ) > 2048 )
		{
			wait( 0.1 );
			continue;
		}

		compass = getDirectionCompass( level.player.origin, landmarkOrigin );
		compass = normalizeCompassDirection( compass );

		clock = getDirectionFacingClock( level.player.angles, level.player.origin, landmarkOrigin );

		string = compass + ", " + clock + ":00";

		Print3d( landmarkOrigin + offset, string, color, 1, 0.75 );	// origin, text, RGB, alpha, scale
		wait 0.05;
	}
}


resetNextSayTimes( team, action )
{
	soldiers = GetAIArray( team );

	for ( index = 0; index < soldiers.size; index++ )
	{
		soldier = soldiers[ index ];

		if ( !isAlive( soldier ) )
			continue;

		if ( !IsDefined( soldier.battlechatter ) )
			continue;

		soldier.nextSayTimes[ action ] = GetTime() + 350;
		soldier.squad.nextSayTimes[ action ] = GetTime() + 350;
	}
}

voice_is_british_based()
{
	self endon( "death" );
	if ( self.voice == "british" )
		return true;
	else
		return false;
}

friendlyfire_warning()
{
	if ( !self can_say_friendlyfire() )
	{
		return false;
	}

	// since we're skipping a lot of the normal bcs checks, multiple guys can potentially say this at the same time, so do the typelimit earlier than usual
	self doTypeLimit( "reaction", "friendlyfire" );

	self thread playReactionEvent();
	return true;
}

can_say_friendlyfire( checkTypeLimit )
{
	if ( IsDefined( self.friendlyfire_warnings_disable ) )
	{
		return false;
	}

	if ( !IsDefined( self.chatQueue ) )
	{
		return false;
	}

	// do we have a reaction event in our queue?
	if ( !IsDefined( self.chatQueue[ "reaction" ] ) || !IsDefined( self.chatQueue[ "reaction" ].eventType ) )
	{
		return false;
	}

	// is it a friendlyfire reaction?
	if ( self.chatQueue[ "reaction" ].eventType != "friendlyfire" )
	{
		return false;
	}

	// has it expired?
	if ( GetTime() > self.chatQueue[ "reaction" ].expireTime )
	{
		return false;
	}

	if ( !IsDefined( checkTypeLimit ) )
	{
		checkTypeLimit = true;
	}

	if ( checkTypeLimit )
	{
		// is it too early to do another one yet?
		if ( IsDefined( self.squad.nextTypeSayTimes[ "reaction" ][ "friendlyfire" ] ) )
		{
			if ( GetTime() < self.squad.nextTypeSayTimes[ "reaction" ][ "friendlyfire" ] )
			{
				return false;
			}
		}
	}

	return true;
}