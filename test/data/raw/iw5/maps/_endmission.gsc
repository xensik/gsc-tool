#include maps\_utility;
#include common_scripts\utility;

emptyMissionDifficultyStr 	= "00000000000000000000000000000000000000000000000000";

SOTABLE_COL_INDEX			= 0;
SOTABLE_COL_REF				= 1;
SOTABLE_COL_NAME 			= 2;
SOTABLE_COL_GROUP			= 13;
SOTABLE_COL_UNLOCK			= 5;

main()
{
	missionSettings = [];

////	addLevel( levelName, keepWeapons, achievement, skipsSuccess, veteran_achievement, for_kleenex )
	missionSettings = createMission( "THE_BEST_OF_THE_BEST" );
	missionSettings addLevel( "sp_intro", 			false, 		"BACK_IN_THE_FIGHT",		true,	"THE_BIG_APPLE",			0.1 );
	missionSettings addLevel( "sp_ny_manhattan", 	false, 		"TOO_BIG_TO_FAIL", 			true,	"THE_BIG_APPLE",			undefined );
	missionSettings addLevel( "sp_ny_harbor", 		false, 		"WET_WORK", 				true,	"THE_BIG_APPLE",	 		undefined );
	missionSettings addLevel( "sp_intro",			false, 		"CARPE_DIEM",				true,	"OUT_OF_THE_FRYING_PAN",	undefined );
	missionSettings addLevel( "hijack", 			false, 		"FREQUENT_FLIER", 			true,	"OUT_OF_THE_FRYING_PAN",	undefined );
	missionSettings addLevel( "sp_warlord", 		false, 		"UP_TO_NO_GOOD", 			true,	"OUT_OF_THE_FRYING_PAN", 	undefined );
	missionSettings addLevel( "london", 			true, 		undefined,					true,	"EUROPEAN_VACATION",		1 );
	missionSettings addLevel( "innocent", 			false, 		"ONE_WAY_TICKET",			true,	"EUROPEAN_VACATION",		0.1 );
	missionSettings addLevel( "hamburg", 			false, 		"WELCOME_TO_WW3", 			true,	"EUROPEAN_VACATION",		undefined );
	missionSettings addLevel( "sp_payback", 		false, 		"SANDSTORM", 				true,	"EUROPEAN_VACATION",		undefined );
	missionSettings addLevel( "sp_paris_a", 		true, 		undefined, 					true,	"CITY_OF_LIGHTS",			undefined );
	missionSettings addLevel( "sp_paris_b", 		false, 		"BACK_SEAT_DRIVER",			true,	"CITY_OF_LIGHTS",			undefined );
	missionSettings addLevel( "paris_ac130", 		false, 		"WELL_ALWAYS_HAVE_PARIS",	true,	"CITY_OF_LIGHTS",			undefined );
	missionSettings addLevel( "sp_prague", 			false, 		"VIVE_LA_REVOLUTION", 		true,	"THE_DARKEST_HOUR",			undefined );
	missionSettings addLevel( "prague_escape", 		false, 		"REQUIEM",			 		true,	"THE_DARKEST_HOUR",			undefined );
	missionSettings addLevel( "castle", 			false, 		"STORM_THE_CASTLE", 		true,	"THE_DARKEST_HOUR",			undefined );
	missionSettings addLevel( "sp_berlin", 			false, 		"BAD_FIRST_DATE",	 		true,	"THIS_IS_THE_END",			undefined );
	missionSettings addLevel( "rescue_2", 			false, 		"DIAMOND_IN_THE_ROUGH",		true,	"THIS_IS_THE_END",			undefined );
	missionSettings addLevel( "sp_dubai", 			false, 		"WHO_DARES_WINS",			true,	"THIS_IS_THE_END",			undefined );

// need to add SO maps differently, need to save script vars
//--------
/*
TO DO:
*/
    if( is_specialop() )
    {
		level.specOpsGroups = [];
		
		// survival and mission group index 0-99
		for( i=0; i<100; i++ )
		{
			ref = tablelookup( "sp/specopstable.csv", SOTABLE_COL_INDEX, i, SOTABLE_COL_REF );
			if ( ref != "" )
				setupSoGroup( ref );
			else
				break;
		}
		
		specOpsSettings = createMission( "SPECIAL_OPS" );
		
		// number of survival maps on release of MW3
		release_survival_number = int( tablelookup( "sp/specopstable.csv", 0, "survival_count", 1 ) );
		
		//dlc_survival_number = 0;		// dlc maps do not track progress
		
		// survival levels index 100-199
		for( i=100; i<200; i++ )
		{
			internal_index = i - 100;
			ref = tablelookup( "sp/specopstable.csv", SOTABLE_COL_INDEX, i, SOTABLE_COL_REF );
			if ( ref != "" )
				specOpsSettings addSpecOpLevel( ref, internal_index );
			else
				break;
		}

		// mission levels index 200-299
		for( i=200; i<300; i++ )
		{
			internal_index = i - 200 + release_survival_number;
			ref = tablelookup( "sp/specopstable.csv", SOTABLE_COL_INDEX, i, SOTABLE_COL_REF );
			if ( ref != "" )
				specOpsSettings addSpecOpLevel( ref, internal_index );
			else
				break;
		}
		
		level.specOpsSettings = specOpsSettings;
	}

	level.missionSettings = missionSettings;
	
	/#
	thread ui_debug_clearall();
	thread debug_test_next_mission();
	#/
}

debug_test_next_mission()
{
	wait( 10 );
	while ( GetDvarInt( "test_next_mission" ) < 1 )
	{
		wait( 3 );
	}

	_nextmission();
}

setupSoGroup( so_ref )
{
	level.specOpsGroups[ so_ref ] 				= spawnStruct();
	level.specOpsGroups[ so_ref ].ref		 	= so_ref;
	level.specOpsGroups[ so_ref ].unlock		= int( tablelookup( "sp/specopstable.csv", SOTABLE_COL_REF, so_ref, SOTABLE_COL_UNLOCK ) );
}


_nextmission()
{
	
	/#
	if( getdvarint("nextmission_disable") )
	{
		iprintlnbold( "Nextmission Here, but disabled!" );
		return;
	}
	#/

	if ( is_demo() )
	{
		SetSavedDvar( "ui_nextMission", "0" );
		if ( IsDefined( level.nextmission_exit_time ) )
		{
			ChangeLevel( "", false, level.nextmission_exit_time );
		}
		else
		{
			ChangeLevel( "", false );
		}
		return;
	}
	
	level notify( "nextmission" );
	level.nextmission = true;
	level.player enableinvulnerability();

	levelIndex = undefined;
	
	setsaveddvar( "ui_nextMission", "1" );
	setdvar( "ui_showPopup", "0" );
	setdvar( "ui_popupString", "" );
	SetDvar( "ui_prev_map", level.script );

	// todo: seems to be related to the skip innocent if user doesn't want to be offended stuff, but has been gimped...
	if ( level.script == "london" )
	{
		game[ "previous_map" ] = "london";
	}
	else
	{
		game[ "previous_map" ] = undefined;
	}
	
	levelIndex = level.missionSettings getLevelIndex( level.script );
	
	if ( level.script == "sp_intro" && !getdvarint( "prologue_select" ) )	// special case for intro.map as it is used as the basis for two levels
	{
		assert(levelIndex >= 0 && levelIndex < level.missionSettings.levels.size );
		for ( i = levelIndex + 1; i < level.missionSettings.levels.size-1; i++ )
		{
			if ( level.missionSettings.levels[i].name == "sp_intro" )
			{
				levelIndex = i;
				break;
			}
		}
	}
	setdvar( "prologue_select", "0" );

	
	maps\_gameskill::auto_adust_zone_complete( "aa_main_" + level.script );
											
	if ( !isDefined( levelIndex ) )
	{
		// run the same mission again if the nextmission is not defiend.
		MissionSuccess( level.script );
		return;
	}

	if ( level.script != "sp_dubai" )
		maps\_utility::level_end_save();
	

	// update mission difficulty and highest completed profile values
	level.missionSettings setLevelCompleted( levelIndex );
	
	// a congradulations popup when you complete the last mission
	// todo: do we want this?
	if ( (level.player GetLocalPlayerProfileData( "highestMission" )) < levelindex + 1 && ( level.script == "sp_dubai" ) && getdvarint( "mis_cheat" ) == 0 )
	{
		// todo: suspect this doesn't do anything anymore
		setdvar( "ui_sp_unlock", "0" );// set reset value to 0
		setdvar( "ui_sp_unlock", "1" );
	}
	
	/#
	PrintLn( ">> SP PERCENT UPDATE - _nextmission()" );
	#/
	completion_percentage = updateSpPercent();
	
	/#	
	if( getdvarint( "ui_debug_setlevel" ) != 0 )	
	{
		_setHighestMissionIfNotCheating( getdvarint( "ui_debug_clearlevel" ) );
		level.missionSettings setLevelCompleted( max( 0, getdvarint( "ui_debug_clearlevel" ) - 1 ) );
		
		setdvar( "ui_debug_setlevel", "" );
	}
	
	// Debug prints
	if ( completion_percentage < level.player GetLocalPlayerProfileData( "percentCompleteSP" ) )
		PrintLn( ">> SP DEBUG: 					[ WARNING! NEW:" + completion_percentage + "% < OLD:" + level.player GetLocalPlayerProfileData( "percentCompleteSP" ) + "% ]\n" );
	
	PrintLn( ">> SP DEBUG: 				[ setlevel:" + getdvarint( "ui_debug_setlevel" ) + " clearall:" + getdvarint( "ui_debug_clearall" ) + " ]" );
	PrintLn( ">> SP PLAYER DIFFICULTY: 		[" + (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" )) + "]" );
	PrintLn( ">> SP PERCENTAGE COMPLETED:		[" + completion_percentage/100 + "%]" );
	PrintLn( ">> SP LEVEL INDEX: 			[" + levelIndex + "]" );
	PrintLn( ">> SP LEVEL NAME: 			[" + level.script + "]" );
	PrintLn( ">> SP LEVELS COMPLETED: 		[" + (level.player GetLocalPlayerProfileData( "highestMission" )) + "]" );
	PrintLn( ">> SP MAX LEVELS: 			[" + level.missionSettings.levels.size + "]" );
	#/
	
	UpdateGamerProfile();
	
	if ( level.missionSettings hasAchievement( levelIndex ) )
		maps\_utility::giveachievement_wrapper( level.missionSettings getAchievement( levelIndex ) );
	
	if ( level.missionSettings hasLevelVeteranAward( levelIndex ) && getLevelCompleted( levelIndex ) == 4
		&& level.missionSettings check_other_hasLevelVeteranAchievement( levelIndex ) )
		maps\_utility::giveachievement_wrapper( level.missionSettings getLevelVeteranAward( levelIndex ) );
	
	if ( level.missionSettings hasMissionHardenedAward() &&
		level.missionSettings getLowestSkill() > 2 )
		giveachievement_wrapper( level.missionSettings getHardenedAward() );
	
	// credits happen in the dubai level, so dubai will call this function before the credits are done
	// and we don't want to cut the credits short, so early out.
	if ( level.script == "sp_dubai" )
		return;
	
	// dubai is the last level, so if we're not dubai this should be valid
	nextLevelIndex = levelIndex + 1;
	
	Assert(nextLevelIndex < level.missionSettings.levels.size);
	
	// todo: do we support this still?		
	if ( arcadeMode() )
	{
		if ( !getdvarint( "arcademode_full" ) )
		{
			SetSavedDvar( "ui_nextMission", "0" );
			missionSuccess( level.script );
			return;
		}
	}

	if ( level.missionSettings skipssuccess( levelIndex ) )
	{
		if ( IsDefined( level.missionsettings getfadetime( levelIndex ) ) )
		{
			ChangeLevel( level.missionSettings getLevelName( nextLevelIndex ), level.missionSettings getKeepWeapons( levelIndex ), level.missionsettings getfadetime( levelIndex ) );
		}
		else
		{
			ChangeLevel( level.missionSettings getLevelName( nextLevelIndex ), level.missionSettings getKeepWeapons( levelIndex ) );
		}
	}
	else
	{
		MissionSuccess( level.missionSettings getLevelName( nextLevelIndex ), level.missionSettings getKeepWeapons( levelIndex ) );
	}
		
	// DEMO BUILD
	// */
}

updateSpPercent()
{
	completion_percentage = int( getTotalpercentCompleteSP()*100 );
	
	if( getdvarint( "mis_cheat" ) == 0 )
	{
		assertex( ( completion_percentage >= 0 && completion_percentage <= 10000 ), "SP's Completion percentage [ " + completion_percentage + "% ] is outside of 0 to 100 range!" );
		level.player SetLocalPlayerProfileData( "percentCompleteSP", completion_percentage );
	}
	
	return completion_percentage;
}
	
getTotalpercentCompleteSP()
{
	/*
	SP STATS:
	
	Game Progression  	60%    	-50
	Hardened Progress  	60%   	-25
	Veteran Progress  	60%    	-10
	Intel Items  		21/45   -15
	--------------------------------
	Total    			x%		-100
	Play Time			##:##:##
	*/
	
	stat_progression = max( getStat_easy(), getStat_regular() ); // easy is always higher than regular anyways...
	stat_progression_ratio = 0.5/1;
	/#
		PrintLn( ">> SP STAT REGULAR: " + stat_progression + "%" + "(" + stat_progression_ratio*100 + "%)" );
	#/
	
	stat_hardened = getStat_hardened();
	stat_hardened_ratio = 0.25/1;
	/#
		PrintLn( ">> SP STAT HARDENED: " + stat_hardened + "%" + "(" + stat_hardened_ratio*100 + "%)" );
	#/
	
	stat_veteran = getStat_veteran();
	stat_veteran_ratio = 0.1/1;
	/#
		PrintLn( ">> SP STAT VETERAN: " + stat_veteran + "%" + "(" + stat_veteran_ratio*100 + "%)" );
	#/
	
	stat_intel = getStat_intel();
	stat_intel_ratio = 0.15/1;
	/#
		PrintLn( ">> SP STAT INTEL: " + stat_intel + "%" + "(" + stat_intel_ratio*100 + "%)" );
	#/

	assertex( ( stat_progression_ratio + stat_hardened_ratio + stat_veteran_ratio + stat_intel_ratio ) <= 1.0, "Total sum of SP progress breakdown contributes to more than 100%!" );

	total_progress = 0.0;
	total_progress += stat_progression_ratio*stat_progression;
	total_progress += stat_hardened_ratio*stat_hardened;
	total_progress += stat_veteran_ratio*stat_veteran;
	total_progress += stat_intel_ratio*stat_intel;

	assertex( total_progress <= 100.0, "Total Percentage calculation is out of bound, larger then 100%" );
	/#
		PrintLn( ">> SP STAT TOTAL: " + total_progress + "%" );
	#/
	
	return total_progress;	
}

// recruit and regular difficulty
getStat_progression( difficulty )
{
	assert( isdefined( level.missionSettings ) );
	assert( isdefined( level.script ) );

	difficulty_string = (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ));
	
	levels = 0;
	notplayed = [];
	skipped = false;
	// level.missionSettings.levels.size - 1 : the minus one is to remove the credits level
	for ( i = 0; i < level.missionSettings.levels.size-1; i++ )
	{
		if ( int( difficulty_string[ i ] ) >= difficulty )
			levels++;
	}

	completion = ( levels/(level.missionsettings.levels.size-1) )*100;
	return completion; // 0->100
}

getStat_easy()
{
	easy = 1;
	return getStat_progression( easy ); // 0->100	
}

getStat_regular()
{
	regular = 2;
	return getStat_progression( regular ); // 0->100	
}

getStat_hardened()
{
	hardened = 3;
	return getStat_progression( hardened ); // 0->100
}

getStat_veteran()
{
	veteran = 4;
	return getStat_progression( veteran ); // 0->100
}

getStat_intel()
{
	total_intel_items = 45;
	intel_percentage = ( (level.player GetLocalPlayerProfileData( "cheatPoints" ) )/total_intel_items )*100;
	return intel_percentage; // 0->100
}

//allMissionsCompleted( difficulty )
//{
//	difficulty += 10;
//	for ( index = 0; index < level.missionSettings.size; index++ )
//	{
//		missionDvar = getMissionDvarString( index );
//		if ( getdvarInt( missionDvar ) < difficulty )
//			return( false );
//	}
//	return( true );
//}

getLevelCompleted( levelIndex )
{
	return int( (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ))[ levelIndex ] );
}

getSoLevelCompleted( levelIndex )
{
	return int( (level.player GetLocalPlayerProfileData( "missionSOHighestDifficulty" ))[ levelIndex ] );
}

setSoLevelCompleted( levelIndex )
{
	foreach( player in level.players )
	{
		if ( isdefined( player.eog_noreward ) && player.eog_noreward )
			continue;
			
		specOpsString = player GetLocalPlayerProfileData( "missionSOHighestDifficulty" );
		
		if ( !isdefined( specOpsString ) )
			continue;
		
		if ( isdefined( player.award_no_stars ) )
			continue;
		
		pre_total_stars = 0;
		for ( i = 0; i < specOpsString.size; i++ )
			pre_total_stars += max( 0, int( specOpsString[ i ] ) - 1 );

		if ( specOpsString.size == 0 )
			specOpsString = emptyMissionDifficultyStr;

		// if profile has no zeros for unplayed levels, we need to populate it with zeros
		while( levelIndex >= specOpsString.size )
			specOpsString += "0";
		
		// survival stars are calculated by waves, not difficulty
		stars = 0;
		if ( is_survival() )
		{
			stars = 0;
		}
		else
		{
			assertex( isdefined( level.specops_reward_gameskill ), "Game skill not setup correctly for coop." );
			stars = level.specops_reward_gameskill;
			
			if ( isdefined( player.forcedGameSkill ) )
				stars = player.forcedGameSkill;	
		}
		
		// only set record if more stars earned
		// difficulty of "4" is 3 stars, thus if 4>3 means we are already at 3 stars, so we skip
		if ( int( specOpsString[ levelIndex ] ) > stars )
			continue;
		
		newString = "";
		for ( index = 0; index < specOpsString.size; index++ )
		{
			if ( index != levelIndex )
				newString += specOpsString[ index ];
			else
				newString += stars + 1;
		}
		
		post_total_stars = 0;
		for ( i = 0; i < newString.size; i++ )
			post_total_stars += max( 0, int( newString[ i ] ) - 1 );
			
		delta_total_stars = post_total_stars - pre_total_stars;
		if ( delta_total_stars > 0 )
		{
			player.eog_firststar = is_first_difficulty_star( newString );
			player.eog_newstar = true;
			player.eog_newstar_value = delta_total_stars;
			
			foreach ( group in level.specOpsGroups )
			{
				if ( group.unlock == 0 )
					continue;
					
				if ( level.ps3 && isSplitscreen() && isdefined( level.player2 ) && player == level.player2 )
					continue;
					
				if ( pre_total_stars < group.unlock && post_total_stars >= group.unlock )
				{
					player.eog_unlock = true;
					player.eog_unlock_value = group.ref;
					
					// BELOW: no more groups in main menu thus we dont need "ui_last_opened_group" dvar set.
					/* 
					if ( getdvarint( "solo_play" ) && ( player == level.player ) )
						setdvar( "ui_last_opened_group", 0 );
					*/
				}
			}
			
			if ( post_total_stars >= 48 )
			{
				player.eog_unlock = true;
				player.eog_unlock_value = "so_completed";
				music_stop( 1 );
			}
		}
		
		if ( player maps\_specialops_code::can_save_to_profile() || ( isSplitscreen() && level.ps3 && isdefined( level.player2 ) && player == level.player2 ) )
			player SetLocalPlayerProfileData( "missionSOHighestDifficulty", newString );
	}
}

is_first_difficulty_star( specOpsString )
{
	// returns false if the current level does not require difficulty selection
	if ( !is_survival() )
	{
		if( int( tablelookup( "sp/specOpsTable.csv", 1, level.script, 14 ) ) == 0 )
			return false;
	}
	
	// number of survival maps on release of MW3
	release_survival_number = int( tablelookup( "sp/specopstable.csv", 0, "survival_count", 1 ) );
	release_mission_number 	= int( tablelookup( "sp/specopstable.csv", 0, "mission_count", 1 ) );
	release_total			= release_survival_number + release_mission_number;
	
	specOpsSum = 0;
	if ( is_survival() )
	{
		for( i=0; i<release_survival_number; i++ )
			specOpsSum += int( max ( 0, int( specOpsString[i] ) - 1 ) );
	}
	else
	{
		for( i=release_survival_number; i<release_total; i++ )
			specOpsSum += int( max ( 0, int( specOpsString[i] ) - 1 ) );
	}
	return ( specOpsSum == 1 );
}

setLevelCompleted( levelIndex )
{
	missionString = ( level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ) );
	
	newString = "";
	for ( index = 0; index < missionString.size; index++ )
	{
		if ( index != levelIndex )
		{
			newString += missionString[ index ];
		}
		else
		{
			if ( level.gameskill + 1 > int( missionString[ levelIndex ] ) )
				newString += level.gameskill + 1;
			else
				newString += missionString[ index ];
		}
	}
	
	// levels completed after skipping levels in order will not get its progress recorded, becuase player was hacking or doing devmap
	finalString = "";
	skip = false;
	highest = 0;
	for ( i = 0; i < newString.size; i++ )
	{
		if ( int( newString[ i ] ) == 0 || skip )
		{
			finalString += "0";
			skip = true;
		}
		else
		{
			finalString += newString[ i ];
			highest++;
		}
	}

	_setHighestMissionIfNotCheating( highest );
	_setMissionDiffStringIfNotCheating( finalString );
}


_setHighestMissionIfNotCheating( mission )
{
	//if ( maps\_cheat::is_cheating() || flag( "has_cheated" ) )
	//	return;
	if ( getdvar( "mis_cheat" ) == "1" )
		return;
	
	level.player SetLocalPlayerProfileData( "highestMission", mission );
}


_setMissionDiffStringIfNotCheating( missionsDifficultyString )
{
	if ( getdvar( "mis_cheat" ) == "1" )
		return;
	
	level.player SetLocalPlayerProfileData( "missionHighestDifficulty", missionsDifficultyString );
}


getLevelSkill( levelIndex )
{
	missionString = (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ));
	return( int( missionString[ levelIndex ] ) );
}


getMissionDvarString( missionIndex )
{
	if ( missionIndex < 9 )
		return( "mis_0" + ( missionIndex + 1 ) );
	else
		return( "mis_" + ( missionIndex + 1 ) );
}


getLowestSkill()
{
	missionString = (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ));
	lowestSkill = 4;

	for ( index = 0; index < self.levels.size; index++ )
	{
		if ( int( missionString[ index ] ) < lowestSkill )
			lowestSkill = int( missionString[ index ] );
	}
	return( lowestSkill );
}


createMission( HardenedAward )
{
	mission = spawnStruct();
	mission.levels = [];
	mission.prereqs = [];
// 	mission.slideShow = slideShow;
	mission.HardenedAward = HardenedAward;
	return( mission );
}

addLevel( levelName, keepWeapons, achievement, skipsSuccess, veteran_achievement, fade_time, for_kleenex )
{
//	if ( GetDvarInt( "iw_kleenex" ) )
//	{
//		if ( !IsDefined( for_kleenex ) )
//		{
//			for_kleenex = false;
//		}
//
//		if ( !for_kleenex )
//		{
//			return;
//		}
//	}

	assert( isdefined( keepweapons ) );
	levelIndex = self.levels.size;
	self.levels[ levelIndex ] = spawnStruct();
	self.levels[ levelIndex ].name = levelName;
	self.levels[ levelIndex ].keepWeapons = keepWeapons;
	self.levels[ levelIndex ].achievement = achievement;
	self.levels[ levelIndex ].skipsSuccess = skipsSuccess;
	self.levels[ levelIndex ].veteran_achievement = veteran_achievement;

	if ( IsDefined( fade_time ) )
	{
		self.levels[ levelIndex ].fade_time = fade_time;
	}
}

addSpecOpLevel( levelName, internal_index )
{
	if ( isdefined( internal_index ) )
		levelIndex = internal_index;
	else
		levelIndex = self.levels.size;
	
	self.levels[ levelIndex ] = spawnStruct();
	self.levels[ levelIndex ].name = levelName;

	level_group = tablelookup( "sp/specopstable.csv", SOTABLE_COL_REF, levelName, SOTABLE_COL_GROUP );
	if ( level_group == "" )
		return;
	
	if( !isdefined( level.specOpsGroups[ level_group ].group_members ) )
		level.specOpsGroups[ level_group ].group_members = [];
	
	member_size = level.specOpsGroups[ level_group ].group_members.size;
	level.specOpsGroups[ level_group ].group_members[ member_size ] = levelName;
}

addPreReq( missionIndex )
{
	preReqIndex = self.prereqs.size;
	self.prereqs[ preReqIndex ] = missionIndex;
}

getLevelIndex( levelName )
{
	foreach ( levelIndex, so_level in self.levels )
	{
		if ( so_level.name == levelName )
			return levelIndex;
	}
	
	return ( undefined );
}

getLevelName( levelIndex )
{
	return( self.levels[ levelIndex ].name );
}

getKeepWeapons( levelIndex )
{
	return( self.levels[ levelIndex ].keepWeapons );
}

getAchievement( levelIndex )
{
	return( self.levels[ levelIndex ].achievement );
}

getLevelVeteranAward( levelIndex )
{
	return( self.levels[ levelIndex ].veteran_achievement );
}

getfadetime( index )
{
	if ( !IsDefined( self.levels[ index ].fade_time ) )
	{
		return undefined;
	}

	return self.levels[ index ].fade_time;
}

hasLevelVeteranAward( levelIndex )
{
	if ( isDefined( self.levels[ levelIndex ].veteran_achievement ) )
		return( true );
	else
		return( false );
}

hasAchievement( levelIndex )
{
	if ( isDefined( self.levels[ levelIndex ].achievement ) )
		return( true );
	else
		return( false );
}

check_other_hasLevelVeteranAchievement( levelIndex )
{
	//check for other levels that have the same Hardened achievement.  
	//If they have it and other level has been completed at a hardened level check passes.

	for ( i = 0; i < self.levels.size; i++ )
	{
		if ( i == levelIndex )
			continue;
		if ( ! hasLevelVeteranAward( i ) )
			continue;
		if ( self.levels[ i ].veteran_achievement == self.levels[ levelIndex ].veteran_achievement )
			if ( getLevelCompleted( i ) < 4 )
				return false;
	}
	return true;
}

skipsSuccess( levelIndex )
{
	if ( !isDefined( self.levels[ levelIndex ].skipsSuccess ) )
		return false;
	return true;
}


getHardenedAward()
{
	return( self.HardenedAward );
}


hasMissionHardenedAward()
{
	if ( isDefined( self.HardenedAward ) )
		return( true );
	else
		return( false );
}

getNextLevelIndex()
{
	for ( index = 0; index < self.levels.size; index++ )
	{
		if ( !self getLevelSkill( index ) )
			return( index );
	}
	return( 0 );
}

force_all_complete()
{
	println( "tada!" );
	missionString = (level.player GetLocalPlayerProfileData( "missionHighestDifficulty" ));
	newString = "";
	for ( index = 0; index < missionString.size; index++ )
	{
		if ( index < 20 )
			newString += 2;
		else
			newstring += 0;
	}
	level.player SetLocalPlayerProfileData( "missionHighestDifficulty", newString );
	level.player SetLocalPlayerProfileData( "highestMission", 20 );
}
/#
ui_debug_clearall()
{
	for(;;)
	{
		if( getdvarint( "ui_debug_clearall" ) )
		{
			clearall();
			level.player SetLocalPlayerProfileData( "percentCompleteSP", 0 );	
			
			foreach( player in level.players )
			{
				player SetLocalPlayerProfileData( "missionspecops", 0 );
				player SetLocalPlayerProfileData( "missionsohighestdifficulty", "00000000000000000000000000000000000000000000000000" );
				player SetLocalPlayerProfileData( "percentCompleteSO", 0 );
				
				best_time_name = tablelookup( "sp/specOpsTable.csv", 1, level.script, 9 );
				if ( isdefined( best_time_name ) && best_time_name != "" )
					player SetLocalPlayerProfileData( best_time_name, 0 );
			}
			
			setdvar( "ui_debug_clearall", "" );
		}
		
		wait 0.05;
	}
}
#/
clearall()
{
	level.player SetLocalPlayerProfileData( "missionHighestDifficulty", emptyMissionDifficultyStr );
	level.player SetLocalPlayerProfileData( "highestMission", 1 );
}

credits_end()
{
	ChangeLevel( "airplane", false );
}

// SpecOps end of game summary calculations
so_eog_summary_calculate( was_success )
{	
	assertex( isdefined( was_success ), "so_eog_summary_calculate() requires a true or false value for the was_success parameter." );

	if ( !isdefined( self.so_eog_summary_data ) )
		self.so_eog_summary_data = [];	

	// time is capped to 24 hours
	if ( !isdefined( level.challenge_start_time ) )
	{
		// If the mission never started, force it to a time of 0.
		level.challenge_start_time = 0;
		level.challenge_end_time = 0;
	}
	
	assertex( isdefined( level.challenge_end_time ), "level.challenge_end_time is not defined" );
	
	session_time = min( level.challenge_end_time - level.challenge_start_time, 86400000 );
	session_time = round_millisec_on_sec( session_time, 1, false );
	
	foreach ( player in level.players )
	{
		player.so_eog_summary_data[ "time" ] 			= session_time;
		player.so_eog_summary_data[ "name" ] 			= player.playername;
		player.so_eog_summary_data[ "difficulty" ] 		= player get_player_gameskill(); //level.specops_reward_gameskill;
		
		if ( isdefined( player.forcedGameSkill ) )
			player.so_eog_summary_data[ "difficulty" ] 	= player.forcedGameSkill;	
	}
	
	level.session_score = 0;
	if ( is_survival() )
	{
		// SURVIVAL MODE
		assert( isdefined( level.so_survival_score_func ) );
		assert( isdefined( level.so_survival_wave_func ) );

		foreach ( player in level.players )
		{
			player.so_eog_summary_data[ "score" ] 	= [[ level.so_survival_score_func ]]();
			player.so_eog_summary_data[ "wave" ] 	= [[ level.so_survival_wave_func ]]();
			
			assert( isdefined( player.game_performance ) && isdefined( player.game_performance[ "kill" ] ) );
			player.so_eog_summary_data[ "kills" ]	= player.game_performance[ "kill" ];
		}
		
		level.session_score	= [[ level.so_survival_score_func ]]();
	}
	else
	{
		// MISSION MODE
		worst_time = 300000; //5 mins
		if ( isdefined( level.so_mission_worst_time ) )
			worst_time = level.so_mission_worst_time;
		
		session_time_score = 0;
		if ( session_time < worst_time )
			session_time_score = int ( ( ( worst_time - session_time ) / worst_time ) * 10000 );
		
		assertex( isdefined( level.specops_reward_gameskill ), "SpecOps difficult is not setup correctly. 'level.specops_reward_gameskill'" );
		level.session_score = int( level.specops_reward_gameskill * 10000 ) + session_time_score;
		
		foreach ( player in level.players )
		{
			assert( isdefined( player.stats ) && isdefined( player.stats[ "kills" ] ) );
			
			player.so_eog_summary_data[ "kills" ]	= player.stats[ "kills" ];
			player.so_eog_summary_data[ "score" ] 	= level.session_score;
		}
	}

	//setdvar( "ui_eog_success_heading_player1", "" );	// clear summary title
	//setdvar( "ui_eog_success_heading_player2", "" );
	
	// if scripter does not specify no-defaults, then we save space for them
	if ( !isdefined( level.custom_eog_no_defaults ) || !level.custom_eog_no_defaults )
	{	
		foreach ( player in level.players )
		{
			if ( is_coop() )
				player.eog_line = 4;
			else
				player.eog_line = 3;
		}
	}
		
	//----------------------------------------------
	// Callback
	//----------------------------------------------
	
	// callback that sets custom data and/or overrides for eog summary
	if( isdefined( level.eog_summary_callback ) )
		[[level.eog_summary_callback]]();
	
	// give XP based on final score
	if ( was_success )
	{
		flag_set( "special_op_final_xp_given" );
		
		assert( isdefined( level.maxrank ) );
		foreach ( player in level.players )
		{		
			xp_earned = calculate_xp( player.so_eog_summary_data[ "score" ] );
			first_time_completion_xp = 0;
			
			if ( isdefined( level.never_played ) && level.never_played )
			{
				player thread givexp( "completion_xp" );
				first_time_completion_xp = maps\_rank::getScoreInfoValue( "completion_xp" );
			}
			else
			{
				best_score = undefined;
				best_score_var = tablelookup( "sp/specOpsTable.csv", 1, level.script, 9 );
				if ( IsDefined( best_score_var ) && best_score_var != "" )
					best_score = player GetLocalPlayerProfileData( best_score_var );
				
				// if never played and was sucessful then give completion XP
				if ( isdefined( best_score ) && best_score == 0 && !is_survival() )
				{
					player thread givexp( "completion_xp" );
					first_time_completion_xp = maps\_rank::getScoreInfoValue( "completion_xp" );
				}
			}
			
			if ( !is_survival() )
			{
				total_xp = first_time_completion_xp + xp_earned;
				
				// append a line to the end for XP!!
				assert( isdefined( player.summary ) && isdefined( player.summary[ "rankxp" ] ) );
				assert( isdefined( level.maxXP ) );
				
				// if no XP was given, do not display this message
				if ( player.summary[ "rankxp" ] < level.maxXP ) 
				{
					if ( first_time_completion_xp != 0 )
						player thread add_custom_eog_summary_line( "@SPECIAL_OPS_UI_XP_COMPLETION_FRIST_TIME", "^8+" + first_time_completion_xp, "@SPECIAL_OPS_UI_XP_COMPLETION", "^8+" + total_xp );	
					else
						player thread add_custom_eog_summary_line( "@SPECIAL_OPS_UI_XP_COMPLETION", "", "^8+" + total_xp );	
				}
				
				player thread giveXP( "final_score_xp", xp_earned );
			}
		}
	}
	
	// Don't use any defaults if specified.
	if ( !isdefined( level.custom_eog_no_defaults ) || !level.custom_eog_no_defaults )
		add_eog_default_stats();
}

calculate_xp( score )
{
	// self is player
	return int( score / 10 );	
}

// displays end of game summary menus and popups
so_eog_summary_display()
{
	if ( isdefined( level.eog_summary_delay ) && level.eog_summary_delay > 0 )
		wait level.eog_summary_delay;
		
	thread maps\_ambient::use_eq_settings( "specialop_fadeout", level.eq_mix_track );
	thread maps\_ambient::blend_to_eq_track( level.eq_mix_track, 10 );	
	
	// reset popup dvars
	reset_eog_popup_dvars();
	
	// player 1
	// setup eog popups that shows stars earned, unlocks, and new best score
	if( isdefined( level.player.eog_firststar ) && level.player.eog_firststar )
		setdvar( "ui_first_star_player1", level.player.eog_firststar );		
	
	if( isdefined( level.player.eog_newstar ) && level.player.eog_newstar )
		setdvar( "ui_eog_player1_stars", level.player.eog_newstar_value );
		
	if( isdefined( level.player.eog_unlock ) && level.player.eog_unlock )
		setdvar( "ui_eog_player1_unlock", level.player.eog_unlock_value );		

	if( isdefined( level.player.eog_bestscore ) && level.player.eog_bestscore )
		setdvar( "ui_eog_player1_bestscore", level.player.eog_bestscore_value );	
	
	if ( is_coop() )
	{
		// player 1
		if( isdefined( level.player.eog_noreward ) && level.player.eog_noreward )
			setdvar( "ui_eog_player1_noreward", level.player.eog_noreward );	

		// player 2
		if( isdefined( level.player2.eog_firststar ) && level.player2.eog_firststar )
			setdvar( "ui_first_star_player2", level.player2.eog_firststar );

		if( isdefined( level.player2.eog_newstar ) && level.player2.eog_newstar )
			setdvar( "ui_eog_player2_stars", level.player2.eog_newstar_value );
			
		if( isdefined( level.player2.eog_unlock ) && level.player2.eog_unlock )
			setdvar( "ui_eog_player2_unlock", level.player2.eog_unlock_value );		

		if( isdefined( level.player2.eog_noreward ) && level.player2.eog_noreward )
			setdvar( "ui_eog_player2_noreward", level.player2.eog_noreward );	

		if( isdefined( level.player2.eog_bestscore ) && level.player2.eog_bestscore )
			setdvar( "ui_eog_player2_bestscore", level.player2.eog_bestscore_value );	

		wait 0.05;
		level.player openpopupmenu( "coop_eog_summary" );
		level.player2 openpopupmenu( "coop_eog_summary2" );
	}
	else
	{
		wait 0.05;
		level.player openpopupmenu( "sp_eog_summary" );
	}
}

reset_eog_popup_dvars()
{
	setdvar( "ui_eog_player1_stars", "" );
	setdvar( "ui_eog_player1_unlock", "" );		
	setdvar( "ui_eog_player1_besttime", "" );	
	setdvar( "ui_eog_player1_bestscore", "" );
	setdvar( "ui_eog_player1_noreward", "" );	
	
	setdvar( "ui_eog_player2_stars", "" );
	setdvar( "ui_eog_player2_unlock", "" );		
	setdvar( "ui_eog_player2_besttime", "" );		
	setdvar( "ui_eog_player2_bestscore", "" );	
	setdvar( "ui_eog_player2_noreward", "" );			
}

// ========================= Setup default stats in end-of-game summary ===========================
add_eog_default_stats()
{
	foreach ( player in level.players )
	{
		// Coop heading "You" "Teammate"
		player so_eog_default_playerlabel();	
		
		// Kills
		player so_eog_default_kills();
		
		// Time
		player so_eog_default_time();

		// Difficulty
		player so_eog_default_difficulty();
		
		// Score
		if ( !level.missionfailed )
			player so_eog_default_score();
	}
}

so_eog_default_playerlabel()
{
	if ( is_coop() )
		self add_custom_eog_summary_line( "", "@SPECIAL_OPS_PERFORMANCE_YOU", "@SPECIAL_OPS_PERFORMANCE_PARTNER", undefined, 1 );
}

so_eog_default_kills()
{
	kills = self.so_eog_summary_data[ "kills" ];
	
	if ( is_coop() )
	{
		p2_kills = get_other_player( self ).so_eog_summary_data[ "kills" ];
		self add_custom_eog_summary_line( "@SPECIAL_OPS_UI_KILLS", kills, p2_kills, undefined, 2 );
	}
	else
	{
		self add_custom_eog_summary_line( "@SPECIAL_OPS_UI_KILLS", kills, undefined, undefined, 1 );
	}
}

so_eog_default_difficulty()
{
	diffString[ 0 ] = "@MENU_RECRUIT";
	diffString[ 1 ] = "@MENU_REGULAR";
	diffString[ 2 ] = "@MENU_HARDENED";
	diffString[ 3 ] = "@MENU_VETERAN";
	
	diff = self get_player_gameskill();
	//diff = diffString[ self.so_eog_summary_data[ "difficulty" ] ];
	self add_custom_eog_summary_line( "@SPECIAL_OPS_UI_DIFFICULTY", diff, undefined, undefined, 2 + int( is_coop() ) );
}

so_eog_default_time()
{
	seconds 		= self.so_eog_summary_data[ "time" ] * 0.001;
	time_string 	= convert_to_time_string( seconds, true );

	self add_custom_eog_summary_line( "@SPECIAL_OPS_UI_TIME", time_string, undefined, undefined, 3 + int( is_coop() ) );
}


so_eog_default_score()
{
	if ( is_coop() )
		score_label = "@SPECIAL_OPS_UI_TEAM_SCORE";
	else
		score_label = "@SPECIAL_OPS_UI_SCORE";
	
	final_score = self.so_eog_summary_data[ "score" ];
	self add_custom_eog_summary_line( score_label, final_score );
}
