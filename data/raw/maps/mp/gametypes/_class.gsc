#include common_scripts\utility;
// check if below includes are removable
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;

KILLSTREAK_GIMME_SLOT = 0;
KILLSTREAK_SLOT_1 = 1;
KILLSTREAK_SLOT_2 = 2;
KILLSTREAK_SLOT_3 = 3;
KILLSTREAK_ALL_PERKS_SLOT = 4;
KILLSTREAK_STACKING_START_SLOT = 5;

init()
{
	level.classMap["class0"] = 0;
	level.classMap["class1"] = 1;
	level.classMap["class2"] = 2;
	level.classMap["class3"] = 3;
	level.classMap["class4"] = 4;
	level.classMap["class5"] = 5;
	level.classMap["class6"] = 6;
	level.classMap["class7"] = 7;
	level.classMap["class8"] = 8;
	level.classMap["class9"] = 9;
	level.classMap["class10"] = 10;
	level.classMap["class11"] = 11;
	level.classMap["class12"] = 12;
	level.classMap["class13"] = 13;
	level.classMap["class14"] = 14;
	
	level.classMap["custom1"] = 0;
	level.classMap["custom2"] = 1;
	level.classMap["custom3"] = 2;
	level.classMap["custom4"] = 3;
	level.classMap["custom5"] = 4;
	level.classMap["custom6"] = 5;
	level.classMap["custom7"] = 6;
	level.classMap["custom8"] = 7;
	level.classMap["custom9"] = 8;
	level.classMap["custom10"] = 9;
	level.classMap["custom11"] = 10;
	level.classMap["custom12"] = 11;
	level.classMap["custom13"] = 12;
	level.classMap["custom14"] = 13;
	level.classMap["custom15"] = 14;
	
	level.classMap["axis_recipe1"] = 0;
	level.classMap["axis_recipe2"] = 1;
	level.classMap["axis_recipe3"] = 2;
	level.classMap["axis_recipe4"] = 3;
	level.classMap["axis_recipe5"] = 4;

	level.classMap["allies_recipe1"] = 0;
	level.classMap["allies_recipe2"] = 1;
	level.classMap["allies_recipe3"] = 2;
	level.classMap["allies_recipe4"] = 3;
	level.classMap["allies_recipe5"] = 4;

	level.classMap["copycat"] = -1;
	
	/#
	// classes testclients may choose from.
	level.botClasses = [];
	level.botClasses[0] = "class0";
	level.botClasses[1] = "class0";
	level.botClasses[2] = "class0";
	level.botClasses[3] = "class0";
	level.botClasses[4] = "class0";
	#/
	
	level.defaultClass = "CLASS_ASSAULT";
	
	level.classTableName = "mp/classTable.csv";
	
	level thread onPlayerConnecting();
}


getClassChoice( response )
{
	assert( isDefined( level.classMap[response] ) );
	
	return response;
}

getWeaponChoice( response )
{
	tokens = strtok( response, "," );
	if ( tokens.size > 1 )
		return int(tokens[1]);
	else
		return 0;
}


logClassChoice( class, primaryWeapon, specialType, perks )
{
	if ( class == self.lastClass )
		return;

	self logstring( "choseclass: " + class + " weapon: " + primaryWeapon + " special: " + specialType );		
	for( i=0; i<perks.size; i++ )
		self logstring( "perk" + i + ": " + perks[i] );
	
	self.lastClass = class;
}

cac_getCustomClassLoc()
{
	if( getDvarInt( "xblive_privatematch" ) )
	{
		return "privateMatchCustomClasses";
	}
	else
	{
		return "customClasses";
	}
}

cac_getWeapon( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "weapon" );
}

cac_getWeaponAttachment( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "attachment", 0 );
}

cac_getWeaponAttachmentTwo( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "attachment", 1 );
}

cac_getWeaponBuff( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "buff" );
}

cac_getWeaponCamo( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "camo" );
}

cac_getWeaponReticle( classIndex, weaponIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "weaponSetups", weaponIndex, "reticle" );
}

cac_getPerk( classIndex, perkIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "perks", perkIndex );
}

cac_getKillstreak( class_num, streakType, streakIndex )
{
	playerData = undefined;
	switch( streakType )
	{
	case "streaktype_support":
		playerData = "defenseStreaks";
		break;
	case "streaktype_specialist":
		playerData = "specialistStreaks";
		break;
	default: // assault
		playerData = "assaultStreaks";
		break;
	}
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, class_num, playerData, streakIndex );
}

cac_getDeathstreak( classIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "deathstreak" );
}

/*
cac_getAmmoType( classIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "perks", 6 );
}
*/

cac_getOffhand( classIndex )
{
	customClassLoc = cac_getCustomClassLoc();
	return self getPlayerData( customClassLoc, classIndex, "perks", 6 );
}

recipe_getKillstreak( teamName, classIndex, streakType, streakIndex )
{
	playerData = undefined;
	switch( streakType )
	{
	case "streaktype_support":
		playerData = "defenseStreaks";
		break;
	case "streaktype_specialist":
		playerData = "specialistStreaks";
		break;
	default: // assault
		playerData = "assaultStreaks";
		break;
	}
	return getMatchRulesData( "defaultClasses", teamName, classIndex, "class", playerData, streakIndex );
}

table_getWeapon( tableName, classIndex, weaponIndex )
{
	if ( weaponIndex == 0 )
		return tableLookup( tableName, 0, "loadoutPrimary", classIndex + 1 );
	else
		return tableLookup( tableName, 0, "loadoutSecondary", classIndex + 1 );
}

table_getWeaponAttachment( tableName, classIndex, weaponIndex, attachmentIndex )
{
	tempName = "none";
	
	if ( weaponIndex == 0 )
	{
		if ( !isDefined( attachmentIndex ) || attachmentIndex == 0 )
			tempName = tableLookup( tableName, 0, "loadoutPrimaryAttachment", classIndex + 1 );
		else
			tempName = tableLookup( tableName, 0, "loadoutPrimaryAttachment2", classIndex + 1 );
	}
	else
	{
		if ( !isDefined( attachmentIndex ) || attachmentIndex == 0 )
			tempName = tableLookup( tableName, 0, "loadoutSecondaryAttachment", classIndex + 1 );
		else
			tempName = tableLookup( tableName, 0, "loadoutSecondaryAttachment2", classIndex + 1 );
	}
	
	if ( tempName == "" || tempName == "none" )
		return "none";
	else
		return tempName;
	
	
}

table_getWeaponBuff( tableName, classIndex, weaponIndex )
{
	if ( weaponIndex == 0 )
		return tableLookup( tableName, 0, "loadoutPrimaryBuff", classIndex + 1 );
	else
		return tableLookup( tableName, 0, "loadoutSecondaryBuff", classIndex + 1 );
}

table_getWeaponCamo( tableName, classIndex, weaponIndex )
{
	if ( weaponIndex == 0 )
		return tableLookup( tableName, 0, "loadoutPrimaryCamo", classIndex + 1 );
	else
		return tableLookup( tableName, 0, "loadoutSecondaryCamo", classIndex + 1 );
}

table_getWeaponReticle( tableName, classIndex, weaponIndex )
{
	return "none";
}

table_getEquipment( tableName, classIndex, perkIndex )
{
	assert( perkIndex < 5 );
	return tableLookup( tableName, 0, "loadoutEquipment", classIndex + 1 );
}

table_getPerk( tableName, classIndex, perkIndex )
{
	assert( perkIndex <= 6 );
	return tableLookup( tableName, 0, "loadoutPerk" + perkIndex, classIndex + 1 );
}

table_getTeamPerk( tableName, classIndex )
{
	return tableLookup( tableName, 0, "loadoutTeamPerk", classIndex + 1 );
}

table_getOffhand( tableName, classIndex )
{
	return tableLookup( tableName, 0, "loadoutOffhand", classIndex + 1 );
}

table_getKillstreak( tableName, classIndex, streakIndex )
{
	return tableLookup( tableName, 0, "loadoutStreak" + streakIndex, classIndex + 1 );
}

table_getDeathstreak( tableName, classIndex )
{
	return tableLookup( tableName, 0, "loadoutDeathstreak", classIndex + 1 );
}

/*
table_getAmmoType( tableName, classIndex )
{
	return tableLookup( tableName, 0, "loadoutAmmoType", classIndex + 1 );
}
*/

getClassIndex( className )
{
	assert( isDefined( level.classMap[className] ) );
	
	return level.classMap[className];
}


cloneLoadout()
{
	teamName = "none";
	
	clonedLoadout = [];
	
	class = self.curClass;
	
	if ( class == "copycat" )
		return ( undefined );

	if( isSubstr( class, "axis" ) )
	{
	    teamName = "axis";
	}
	else if( isSubstr( class, "allies" ) )
	{
	    teamName = "allies";
	}
	
 	if (teamName != "none")
	{
		classIndex = getClassIndex( class );

		loadoutPrimaryAttachment2 = "none";
		loadoutSecondaryAttachment2 = "none";

		loadoutPrimary = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "weapon" );
		loadoutPrimaryAttachment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "attachment", 0 );
		loadoutPrimaryAttachment2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "attachment", 1 );
		loadoutPrimaryBuff = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "buff" );
		loadoutPrimaryCamo = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "camo" );
		loadoutPrimaryReticle = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "reticle" );

		loadoutSecondary = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "weapon" );
		loadoutSecondaryAttachment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "attachment", 0 );
		loadoutSecondaryAttachment2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "attachment", 1 );
		loadoutSecondaryBuff = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "buff" );
		loadoutSecondaryCamo = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "camo" );
		loadoutSecondaryReticle = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "reticle" );

		loadoutEquipment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 0 );
		loadoutPerk1 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 1 );
		loadoutPerk2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 2 );
		loadoutPerk3 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 3 );
		loadoutStreakType = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 5 );
		loadoutKillstreak1 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 0 );
		loadoutKillstreak2 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 1 );
		loadoutKillstreak3 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 2 );
		loadoutOffhand = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 6 );
		loadoutDeathStreak = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "deathstreak" );
 	}
 	else if( isSubstr( class, "custom" ) )
	{
		class_num = getClassIndex( class );

		loadoutPrimaryAttachment2 = "none";
		loadoutSecondaryAttachment2 = "none";

		loadoutPrimary = cac_getWeapon( class_num, 0 );
		loadoutPrimaryAttachment = cac_getWeaponAttachment( class_num, 0 );
		loadoutPrimaryAttachment2 = cac_getWeaponAttachmentTwo( class_num, 0 );
		loadoutPrimaryBuff = cac_getWeaponBuff( class_num, 0 );
		loadoutPrimaryCamo = cac_getWeaponCamo( class_num, 0 );
		loadoutPrimaryReticle = cac_getWeaponReticle( class_num, 0 );
		loadoutSecondary = cac_getWeapon( class_num, 1 );
		loadoutSecondaryAttachment = cac_getWeaponAttachment( class_num, 1 );
		loadoutSecondaryAttachment2 = cac_getWeaponAttachmentTwo( class_num, 1 );
		loadoutSecondaryBuff = cac_getWeaponBuff( class_num, 1 );
		loadoutSecondaryCamo = cac_getWeaponCamo( class_num, 1 );
		loadoutSecondaryReticle = cac_getWeaponReticle( class_num, 1 );
		loadoutEquipment = cac_getPerk( class_num, 0 );
		loadoutPerk1 = cac_getPerk( class_num, 1 );
		loadoutPerk2 = cac_getPerk( class_num, 2 );
		loadoutPerk3 = cac_getPerk( class_num, 3 );
		loadoutStreakType = cac_getPerk( class_num, 5 );
		loadoutKillstreak1 = cac_getKillstreak( class_num, loadoutStreakType, 0 );
		loadoutKillstreak2 = cac_getKillstreak( class_num, loadoutStreakType, 1 );
		loadoutKillstreak3 = cac_getKillstreak( class_num, loadoutStreakType, 2 );
		loadoutOffhand = cac_getOffhand( class_num );
		loadoutDeathStreak = cac_getDeathstreak( class_num );
		//loadoutAmmoType = cac_getAmmoType( class_num );
	}
	else
	{
		class_num = getClassIndex( class );
		
		loadoutPrimary = table_getWeapon( level.classTableName, class_num, 0 );
		loadoutPrimaryAttachment = table_getWeaponAttachment( level.classTableName, class_num, 0 , 0);
		loadoutPrimaryAttachment2 = table_getWeaponAttachment( level.classTableName, class_num, 0, 1 );
		loadoutPrimaryBuff = table_getWeaponBuff( level.classTableName, class_num, 0 );
		loadoutPrimaryCamo = table_getWeaponCamo( level.classTableName, class_num, 0 );
		loadoutPrimaryReticle = table_getWeaponReticle( level.classTableName, class_num, 0 );
		loadoutSecondary = table_getWeapon( level.classTableName, class_num, 1 );
		loadoutSecondaryAttachment = table_getWeaponAttachment( level.classTableName, class_num, 1, 0);
		loadoutSecondaryAttachment2 = table_getWeaponAttachment( level.classTableName, class_num, 1, 1 );
		loadoutSecondaryBuff = table_getWeaponBuff( level.classTableName, class_num, 1 );
		loadoutSecondaryCamo = table_getWeaponCamo( level.classTableName, class_num, 1 );
		loadoutSecondaryReticle = table_getWeaponReticle( level.classTableName, class_num, 1 );
		loadoutEquipment = table_getEquipment( level.classTableName, class_num, 0 );
		loadoutPerk1 = table_getPerk( level.classTableName, class_num, 1 );
		loadoutPerk2 = table_getPerk( level.classTableName, class_num, 2 );
		loadoutPerk3 = table_getPerk( level.classTableName, class_num, 3 );
		loadoutStreakType = table_getPerk( level.classTableName, class_num, 5 );
		loadoutOffhand = table_getOffhand( level.classTableName, class_num );
		loadoutDeathStreak = table_getDeathstreak( level.classTableName, class_num );
		//loadoutAmmoType = table_getAmmoType( level.classTableName, class_num );
		
		switch( loadoutStreakType )
		{
		case "streaktype_support":
			defaultKillstreak1 = table_getKillstreak( level.classTableName, 3, 1 );
			defaultKillstreak2 = table_getKillstreak( level.classTableName, 3, 2 );
			defaultKillstreak3 = table_getKillstreak( level.classTableName, 3, 3 );
			break;
		case "streaktype_specialist":
			defaultKillstreak1 = table_getKillstreak( level.classTableName, 1, 1 );
			defaultKillstreak2 = table_getKillstreak( level.classTableName, 1, 2 );
			defaultKillstreak3 = table_getKillstreak( level.classTableName, 1, 3 );
			break;
		default: // assault
			defaultKillstreak1 = table_getKillstreak( level.classTableName, 0, 1 );
			defaultKillstreak2 = table_getKillstreak( level.classTableName, 0, 2 );
			defaultKillstreak3 = table_getKillstreak( level.classTableName, 0, 3 );
			break;
		}

		loadoutKillstreak1 = defaultKillstreak1;
		loadoutKillstreak2 = defaultKillstreak2;
		loadoutKillstreak3 = defaultKillstreak3;
	}
	
	clonedLoadout["inUse"] = false;
	clonedLoadout["loadoutPrimary"] = loadoutPrimary;
	clonedLoadout["loadoutPrimaryAttachment"] = loadoutPrimaryAttachment;
	clonedLoadout["loadoutPrimaryAttachment2"] = loadoutPrimaryAttachment2;
	clonedLoadout["loadoutPrimaryBuff"] = loadoutPrimaryBuff;
	clonedLoadout["loadoutPrimaryCamo"] = loadoutPrimaryCamo;
	clonedLoadout["loadoutPrimaryReticle"] = loadoutPrimaryReticle;
	clonedLoadout["loadoutSecondary"] = loadoutSecondary;
	clonedLoadout["loadoutSecondaryAttachment"] = loadoutSecondaryAttachment;
	clonedLoadout["loadoutSecondaryAttachment2"] = loadoutSecondaryAttachment2;
	clonedLoadout["loadoutSecondaryBuff"] = loadoutSecondaryBuff;
	clonedLoadout["loadoutSecondaryCamo"] = loadoutSecondaryCamo;
	clonedLoadout["loadoutSecondaryReticle"] = loadoutSecondaryReticle;
	clonedLoadout["loadoutEquipment"] = loadoutEquipment;
	clonedLoadout["loadoutPerk1"] = loadoutPerk1;
	clonedLoadout["loadoutPerk2"] = loadoutPerk2;
	clonedLoadout["loadoutPerk3"] = loadoutPerk3;
	clonedLoadout["loadoutStreakType"] = loadoutStreakType;
	clonedLoadout["loadoutKillstreak1"] = loadoutKillstreak1;
	clonedLoadout["loadoutKillstreak2"] = loadoutKillstreak2;
	clonedLoadout["loadoutKillstreak3"] = loadoutKillstreak3;
	clonedLoadout["loadoutDeathstreak"] = loadoutDeathstreak;
	//clonedLoadout["loadoutAmmoType"] = loadoutAmmoType;
	clonedLoadout["loadoutOffhand"] = loadoutOffhand;
	
	return ( clonedLoadout );
}

//avoiding going through code for extra perk types
loadoutFakePerks( loadoutStreakType, loadoutAmmoType )
{
	switch ( loadoutStreakType )
	{
		case "streaktype_support":
			self.streakType = "support";
			break;
		case "streaktype_specialist":
			self.streakType = "specialist";
			break;
		default: // assault/null:
			self.streakType = "assault";		 
	}
		
	//self.ammoType = loadoutAmmoType;
}

getLoadoutStreakTypeFromStreakType( streakType )
{
	if ( !isDefined( streakType ) )
	{
		assertEx( false, "getLoadoutStreakTypeFromStreakType() called with undefined streaktype" );
		return "streaktype_assault";
	}
	
	switch ( streakType )
	{
		case "support":
			return "streaktype_support";
		case "specialist":
			return "streaktype_specialist";
		case "assault":
			return "streaktype_assault";
		default: 
			assertEx( false, "getLoadoutStreakTypeFromStreakType() called with unknown streaktype" );		
			return "streaktype_assault"; 
	}	
}

giveLoadout( team, class, allowCopycat, setPrimarySpawnWeapon ) // setPrimarySpawnWeapon only when called during spawn
{
	self takeAllWeapons();
	
	self.changingWeapon = undefined;

	teamName = "none";
	if ( !isDefined( setPrimarySpawnWeapon ) )
		setPrimarySpawnWeapon = true;

	primaryIndex = 0;
	
	// initialize specialty array
	self.specialty = [];

	if ( !isDefined( allowCopycat ) )
		allowCopycat = true;

	primaryWeapon = undefined;
	
	//	set in game mode custom class
	loadoutKillstreak1 = undefined;
	loadoutKillstreak2 = undefined;
	loadoutKillstreak3 = undefined;	

	if( isSubstr( class, "axis" ) )
	{
	    teamName = "axis";
	}
	else if( isSubstr( class, "allies" ) )
	{
	    teamName = "allies";
	}

	clonedLoadout = [];
	if ( isDefined( self.pers["copyCatLoadout"] ) && self.pers["copyCatLoadout"]["inUse"] && allowCopycat )
	{
		self maps\mp\gametypes\_class::setClass( "copycat" );
		self.class_num = getClassIndex( "copycat" );

		clonedLoadout = self.pers["copyCatLoadout"];

		loadoutPrimary = clonedLoadout["loadoutPrimary"];
		loadoutPrimaryAttachment = clonedLoadout["loadoutPrimaryAttachment"];
		loadoutPrimaryAttachment2 = clonedLoadout["loadoutPrimaryAttachment2"] ;
		loadoutPrimaryBuff = clonedLoadout["loadoutPrimaryBuff"];
		loadoutPrimaryCamo = clonedLoadout["loadoutPrimaryCamo"];
		loadoutPrimaryReticle = clonedLoadout["loadoutPrimaryReticle"];
		loadoutSecondary = clonedLoadout["loadoutSecondary"];
		loadoutSecondaryAttachment = clonedLoadout["loadoutSecondaryAttachment"];
		loadoutSecondaryAttachment2 = clonedLoadout["loadoutSecondaryAttachment2"];
		loadoutSecondaryBuff = clonedLoadout["loadoutSecondaryBuff"];
		loadoutSecondaryCamo = clonedLoadout["loadoutSecondaryCamo"];
		loadoutSecondaryReticle = clonedLoadout["loadoutSecondaryReticle"];
		loadoutEquipment = clonedLoadout["loadoutEquipment"];
		loadoutPerk1 = clonedLoadout["loadoutPerk1"];
		loadoutPerk2 = clonedLoadout["loadoutPerk2"];
		loadoutPerk3 = clonedLoadout["loadoutPerk3"];
		loadoutStreakType = clonedLoadout["loadoutStreakType"];
		loadoutOffhand = clonedLoadout["loadoutOffhand"];
		loadoutDeathStreak = clonedLoadout["loadoutDeathstreak"];
		loadoutAmmoType	 = clonedLoadout["loadoutAmmoType"];
	}
	else if (teamName != "none")
	{
		classIndex = getClassIndex( class );

		loadoutPrimaryAttachment2 = "none";
		loadoutSecondaryAttachment2 = "none";

		loadoutPrimary = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "weapon" );
		loadoutPrimaryAttachment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "attachment", 0 );
		loadoutPrimaryAttachment2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "attachment", 1 );
		loadoutPrimaryBuff = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "buff" );
		loadoutPrimaryCamo = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "camo" );
		loadoutPrimaryReticle = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 0, "reticle" );

		loadoutSecondary = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "weapon" );
		loadoutSecondaryAttachment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "attachment", 0 );
		loadoutSecondaryAttachment2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "attachment", 1 );
		loadoutSecondaryBuff = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "buff" );
		loadoutSecondaryCamo = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "camo" );
		loadoutSecondaryReticle = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "weaponSetups", 1, "reticle" );
		
		//	replace the placeholder throwing knife with the valid secondary if there is one
		if ( loadoutPrimary == "throwingknife" && loadoutSecondary != "none" )
		{
			loadoutPrimary = loadoutSecondary;
			loadoutPrimaryAttachment = loadoutSecondaryAttachment;
			loadoutPrimaryAttachment2 = loadoutSecondaryAttachment2;
			loadoutPrimaryBuff = loadoutSecondaryBuff;
			loadoutPrimaryCamo = loadoutSecondaryCamo;
			loadoutPrimaryReticle = loadoutSecondaryReticle;	
			
			loadoutSecondary = "none";
			loadoutSecondaryAttachment = "none";
			loadoutSecondaryAttachment2 = "none";
			loadoutSecondaryBuff = "specialty_null";
			loadoutSecondaryCamo = "none";
			loadoutSecondaryReticle = "none";				
		}
		//	otherwise replace with normal default for invalid class
		else if ( loadoutPrimary == "throwingknife" && loadoutSecondary == "none" )
		{
			loadoutPrimary = table_getWeapon( level.classTableName, 10, 1 );
		}

		loadoutEquipment = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 0 );
		loadoutPerk1 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 1 );
		loadoutPerk2 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 2 );
		loadoutPerk3 = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 3 );
		
		//	replace secondary with default in case overkill perk was used to give 2 primaries and perks are disabled
		if ( loadoutSecondary != "none" && !isValidSecondary( loadoutSecondary, loadoutPerk2, loadoutPerk3, false ) )
			loadoutSecondary = table_getWeapon( level.classTableName, 10, 1 );		
		
		loadoutStreakType = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 5 );
		loadoutKillstreak1 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 0 );
		loadoutKillstreak2 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 1 );
		loadoutKillstreak3 = recipe_getKillstreak( teamName, classIndex, loadoutStreakType, 2 );
		loadoutOffhand = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "perks", 6 );	
		//	hack, until game mode default class data can be reset
		if ( loadoutOffhand == "specialty_null" )
			loadoutOffhand = "none";	
		loadoutDeathStreak = getMatchRulesData( "defaultClasses", teamName, classIndex, "class", "deathstreak" );
		if ( getMatchRulesData( "defaultClasses", teamName, classIndex, "juggernaut" ) )
		{
			self.isJuggernaut = true;
			self thread recipeClassApplyJuggernaut();
		}
	}
	else if ( isSubstr( class, "custom" ) )
	{
		class_num = getClassIndex( class );
		self.class_num = class_num;

		loadoutPrimary = cac_getWeapon( class_num, 0 );
		loadoutPrimaryAttachment = cac_getWeaponAttachment( class_num, 0 );
		loadoutPrimaryAttachment2 = cac_getWeaponAttachmentTwo( class_num, 0 );
		loadoutPrimaryBuff = cac_getWeaponBuff( class_num, 0 );
		loadoutPrimaryCamo = cac_getWeaponCamo( class_num, 0 );
		loadoutPrimaryReticle = cac_getWeaponReticle( class_num, 0 );
		loadoutSecondary = cac_getWeapon( class_num, 1 );
		loadoutSecondaryAttachment = cac_getWeaponAttachment( class_num, 1 );
		loadoutSecondaryAttachment2 = cac_getWeaponAttachmentTwo( class_num, 1 );
		loadoutSecondaryBuff = cac_getWeaponBuff( class_num, 1 );
		loadoutSecondaryCamo = cac_getWeaponCamo( class_num, 1 );
		loadoutSecondaryReticle = cac_getWeaponReticle( class_num, 1 );
		loadoutEquipment = cac_getPerk( class_num, 0 );
		loadoutPerk1 = cac_getPerk( class_num, 1 );
		loadoutPerk2 = cac_getPerk( class_num, 2 );
		loadoutPerk3 = cac_getPerk( class_num, 3 );
		loadoutStreakType = cac_getPerk( class_num, 5 );
		loadoutOffhand = cac_getOffhand( class_num );
		loadoutDeathStreak = cac_getDeathstreak( class_num );
	}
	else if ( class == "gamemode" )
	{
		gamemodeLoadout = self.pers["gamemodeLoadout"];

		loadoutPrimary = gamemodeLoadout["loadoutPrimary"];
		loadoutPrimaryAttachment = gamemodeLoadout["loadoutPrimaryAttachment"];
		loadoutPrimaryAttachment2 = gamemodeLoadout["loadoutPrimaryAttachment2"] ;
		loadoutPrimaryBuff = gamemodeLoadout["loadoutPrimaryBuff"];
		loadoutPrimaryCamo = gamemodeLoadout["loadoutPrimaryCamo"];
		loadoutPrimaryReticle = gamemodeLoadout["loadoutPrimaryReticle"];
		loadoutSecondary = gamemodeLoadout["loadoutSecondary"];		
		loadoutSecondaryAttachment = gamemodeLoadout["loadoutSecondaryAttachment"];
		loadoutSecondaryAttachment2 = gamemodeLoadout["loadoutSecondaryAttachment2"];
		loadoutSecondaryBuff = gamemodeLoadout["loadoutSecondaryBuff"];
		loadoutSecondaryCamo = gamemodeLoadout["loadoutSecondaryCamo"];
		loadoutSecondaryReticle = gamemodeLoadout["loadoutSecondaryReticle"];
		
		//	replace the placeholder throwing knife with the valid secondary if there is one
		if ( loadoutPrimary == "throwingknife" && loadoutSecondary != "none" )
		{
			loadoutPrimary = loadoutSecondary;
			loadoutPrimaryAttachment = loadoutSecondaryAttachment;
			loadoutPrimaryAttachment2 = loadoutSecondaryAttachment2;
			loadoutPrimaryBuff = loadoutSecondaryBuff;
			loadoutPrimaryCamo = loadoutSecondaryCamo;
			loadoutPrimaryReticle = loadoutSecondaryReticle;	
			
			loadoutSecondary = "none";
			loadoutSecondaryAttachment = "none";
			loadoutSecondaryAttachment2 = "none";
			loadoutSecondaryBuff = "specialty_null";
			loadoutSecondaryCamo = "none";
			loadoutSecondaryReticle = "none";				
		}	
		//	otherwise replace with normal default for invalid class
		else if ( loadoutPrimary == "throwingknife" && loadoutSecondary == "none" )
		{
			loadoutPrimary = table_getWeapon( level.classTableName, 10, 1 );
		}	
		
		loadoutEquipment = gamemodeLoadout["loadoutEquipment"];
		loadoutOffhand = gamemodeLoadout["loadoutOffhand"];
		//	hack, until game mode default class data can be reset
		if ( loadoutOffhand == "specialty_null" )
			loadoutOffhand = "none";	
		loadoutPerk1 = gamemodeLoadout["loadoutPerk1"];
		loadoutPerk2 = gamemodeLoadout["loadoutPerk2"];
		loadoutPerk3 = gamemodeLoadout["loadoutPerk3"];
		//	replace secondary with default in case overkill perk was used to give 2 primaries and perks are disabled
		if ( loadoutSecondary != "none" && !isValidSecondary( loadoutSecondary, loadoutPerk2, loadoutPerk3, false ) )
			loadoutSecondary = table_getWeapon( level.classTableName, 10, 1 );		
		if ( level.killstreakRewards && isDefined( gamemodeLoadout["loadoutStreakType"] ) && gamemodeLoadout["loadoutStreakType"] != "specialty_null" )
		{
			loadoutStreakType = gamemodeLoadout["loadoutStreakType"];
			loadoutKillstreak1 = gamemodeLoadout["loadoutKillstreak1"];
			loadoutKillstreak2 = gamemodeLoadout["loadoutKillstreak2"];
			loadoutKillstreak3 = gamemodeLoadout["loadoutKillstreak3"];			
		}
		else if ( level.killstreakRewards && isDefined( self.streakType ) )
			loadoutStreakType = getLoadoutStreakTypeFromStreakType( self.streakType );
		else 
		{
			loadoutStreakType = "streaktype_assault";
			loadoutKillstreak1 = "none";
			loadoutKillstreak2 = "none";
			loadoutKillstreak3 = "none";			
		}
		loadoutDeathStreak = gamemodeLoadout["loadoutDeathstreak"];		
		if ( !self isJuggernaut() && gamemodeLoadout["loadoutJuggernaut"] )
		{
			self.isJuggernaut = true;
			self thread recipeClassApplyJuggernaut();
		}
	}
	else if( class == "juggernaut" )
	{
		loadoutPrimary = "iw5_m60jugg";
		loadoutPrimaryAttachment = "none";
		loadoutPrimaryAttachment2 = "none";
		loadoutPrimaryBuff = "specialty_null";
		loadoutPrimaryCamo = "none";
		loadoutPrimaryReticle = "none";
		loadoutSecondary = "iw5_mp412jugg";
		loadoutSecondaryAttachment = "none";
		loadoutSecondaryAttachment2 = "none";
		loadoutSecondaryBuff = "specialty_null";
		loadoutSecondaryCamo = "none";
		loadoutSecondaryReticle = "none";
		loadoutEquipment = "frag_grenade_mp";
		loadoutPerk1 = "specialty_scavenger";
		loadoutPerk2 = "specialty_quickdraw";
		loadoutPerk3 = "specialty_detectexplosive";
		loadoutStreakType = getLoadoutStreakTypeFromStreakType( self.streakType );
		loadoutOffhand = "smoke_grenade_mp";
		loadoutDeathStreak = "specialty_null";
	}
	else if( class == "juggernaut_recon" )
	{
		loadoutPrimary = "iw5_riotshieldjugg";
		loadoutPrimaryAttachment = "none";
		loadoutPrimaryAttachment2 = "none";
		loadoutPrimaryBuff = "specialty_null";
		loadoutPrimaryCamo = "none";
		loadoutPrimaryReticle = "none";
		loadoutSecondary = "iw5_usp45jugg";
		loadoutSecondaryAttachment = "none";
		loadoutSecondaryAttachment2 = "none";
		loadoutSecondaryBuff = "specialty_null";
		loadoutSecondaryCamo = "none";
		loadoutSecondaryReticle = "none";
		loadoutEquipment = "specialty_portable_radar";
		loadoutPerk1 = "specialty_scavenger";
		loadoutPerk2 = "specialty_coldblooded";
		loadoutPerk3 = "specialty_detectexplosive";
		loadoutStreakType = getLoadoutStreakTypeFromStreakType( self.streakType );
		loadoutOffhand = "smoke_grenade_mp";
		loadoutDeathStreak = "specialty_null";
	}
	else
	{
		class_num = getClassIndex( class );
		self.class_num = class_num;
		
		loadoutPrimary = table_getWeapon( level.classTableName, class_num, 0 );
		loadoutPrimaryAttachment = table_getWeaponAttachment( level.classTableName, class_num, 0 , 0);
		loadoutPrimaryAttachment2 = table_getWeaponAttachment( level.classTableName, class_num, 0, 1 );
		loadoutPrimaryBuff = table_getWeaponBuff( level.classTableName, class_num, 0 );
		loadoutPrimaryCamo = table_getWeaponCamo( level.classTableName, class_num, 0 );
		loadoutPrimaryReticle = table_getWeaponReticle( level.classTableName, class_num, 0 );
		loadoutSecondary = table_getWeapon( level.classTableName, class_num, 1 );
		loadoutSecondaryAttachment = table_getWeaponAttachment( level.classTableName, class_num, 1 , 0);
		loadoutSecondaryAttachment2 = table_getWeaponAttachment( level.classTableName, class_num, 1, 1 );;
		loadoutSecondaryBuff = table_getWeaponBuff( level.classTableName, class_num, 1 );
		loadoutSecondaryCamo = table_getWeaponCamo( level.classTableName, class_num, 1 );
		loadoutSecondaryReticle = table_getWeaponReticle( level.classTableName, class_num, 1 );
		loadoutEquipment = table_getEquipment( level.classTableName, class_num, 0 );
		loadoutPerk1 = table_getPerk( level.classTableName, class_num, 1 );
		loadoutPerk2 = table_getPerk( level.classTableName, class_num, 2 );
		loadoutPerk3 = table_getPerk( level.classTableName, class_num, 3 );
		loadoutStreakType = table_getPerk( level.classTableName, class_num, 5 );
		loadoutOffhand = table_getOffhand( level.classTableName, class_num );
		loadoutDeathstreak = table_getDeathstreak( level.classTableName, class_num );
	}

	self loadoutFakePerks( loadoutStreakType );

	isCustomClass = isSubstr( class, "custom" );
	isRecipeClass = isSubstr( class, "recipe" );
	isGameModeClass = ( class == "gamemode" );
	
	if ( !isGameModeClass && !isRecipeClass && !(isDefined( self.pers["copyCatLoadout"] ) && self.pers["copyCatLoadout"]["inUse"] && allowCopycat) )
	{
		if ( !isValidPrimary( loadoutPrimary ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutPrimary )) )
			loadoutPrimary = table_getWeapon( level.classTableName, 10, 0 );
		
		if ( !isValidAttachment( loadoutPrimaryAttachment ) || (  level.rankedMatch && isCustomClass && !self isAttachmentUnlocked( loadoutPrimary, loadoutPrimaryAttachment ) ) )
			loadoutPrimaryAttachment = table_getWeaponAttachment( level.classTableName, 10, 0 , 0);
		
		if ( !isValidAttachment( loadoutPrimaryAttachment2 ) || (  level.rankedMatch && isCustomClass && !self isAttachmentUnlocked( loadoutPrimary, loadoutPrimaryAttachment2 ) ) )
			loadoutPrimaryAttachment2 = table_getWeaponAttachment( level.classTableName, 10, 0, 1 );
		
		if ( !isValidWeaponBuff( loadoutPrimaryBuff ) || ( level.rankedMatch && isCustomClass && !self isWeaponBuffUnlocked( loadoutPrimary, loadoutPrimaryBuff )) )
			loadoutPrimaryBuff = table_getWeaponBuff( level.classTableName, 10, 0 );

		if ( !isValidCamo( loadoutPrimaryCamo ) || (  level.rankedMatch && isCustomClass && !self isCamoUnlocked( loadoutPrimary, loadoutPrimaryCamo )) )
			loadoutPrimaryCamo = table_getWeaponCamo( level.classTableName, 10, 0 );

		if ( !isValidReticle( loadoutPrimaryReticle ) )
			loadoutPrimaryReticle = table_getWeaponReticle( level.classTableNum, 10, 0 );
		
		if ( !isValidSecondary( loadoutSecondary, loadoutPerk2, loadoutPerk3 ) || (  level.rankedMatch && level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutSecondary )) )
			loadoutSecondary = table_getWeapon( level.classTableName, 10, 1 );
		
		if ( !isValidAttachment( loadoutSecondaryAttachment ) || (  level.rankedMatch && isCustomClass && !self isAttachmentUnlocked( loadoutSecondary, loadoutSecondaryAttachment )) )
			loadoutSecondaryAttachment = table_getWeaponAttachment( level.classTableName, 10, 1 , 0);
		
		if ( !isValidAttachment( loadoutSecondaryAttachment2 ) || (  level.rankedMatch && isCustomClass && !self isAttachmentUnlocked( loadoutSecondary, loadoutSecondaryAttachment2 )) )
			loadoutSecondaryAttachment2 = table_getWeaponAttachment( level.classTableName, 10, 1, 1 );;
		
		if ( loadoutPerk2 == "specialty_twoprimaries" && !isValidWeaponBuff( loadoutSecondaryBuff ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutSecondary + " " + loadoutSecondaryBuff )) )
			loadoutSecondaryBuff = table_getWeaponBuff( level.classTableName, 10, 1 );

		if ( !isValidCamo( loadoutSecondaryCamo ) || ( level.rankedMatch && isCustomClass && !self isCamoUnlocked( loadoutSecondary, loadoutSecondaryCamo )) )
			loadoutSecondaryCamo = table_getWeaponCamo( level.classTableName, 10, 1 );

		if ( !isValidReticle( loadoutSecondaryReticle ) )
			loadoutSecondaryReticle = table_getWeaponReticle( level.classTableName, 10, 1 );
		
		if ( !isValidEquipment( loadoutEquipment ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutEquipment )) )
			loadoutEquipment = table_getEquipment( level.classTableName, 10, 0 );
		
		if ( !isValidPerk1( loadoutPerk1 ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutPerk1 )) )
			loadoutPerk1 = table_getPerk( level.classTableName, 10, 1 );
		
		if ( !isValidPerk2( loadoutPerk2, loadoutPerk1 ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutPerk2 )) )
			loadoutPerk2 = table_getPerk( level.classTableName, 10, 2 );
		
		if ( !isValidPerk3( loadoutPerk3, loadoutPerk1 ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutPerk3 )) )
			loadoutPerk3 = table_getPerk( level.classTableName, 10, 3 );
		
		if ( !isValidDeathStreak( loadoutDeathStreak ) || ( level.rankedMatch && isCustomClass && !self isItemUnlocked( loadoutDeathStreak ) ) )
			loadoutDeathStreak = table_getDeathstreak( level.classTableName, 10 );

		if ( !isValidOffhand( loadoutOffhand ) )
			loadoutOffhand = table_getOffhand( level.classTableName, 10 );
	}

	// TODO: give bling if the weapon is properly ranked up
	//if ( loadoutPerk1 != "specialty_bling" )
	//{
	//	loadoutPrimaryAttachment2 = "none";
	//	loadoutSecondaryAttachment2 = "none";
	//}
	
	/*
	if ( loadoutPerk1 != "specialty_onemanarmy" && loadoutSecondary == "onemanarmy" )
		loadoutSecondary = table_getWeapon( level.classTableName, 10, 1 );
	*/

	//loadoutSecondaryCamo = "none";

	self.loadoutPrimary = loadoutPrimary;
	self.loadoutPrimaryCamo = int(tableLookup( "mp/camoTable.csv", 1, loadoutPrimaryCamo, 0 ));
	self.loadoutSecondary = loadoutSecondary;
	self.loadoutSecondaryCamo = int(tableLookup( "mp/camoTable.csv", 1, loadoutSecondaryCamo, 0 ));
	
	// sorry, not supporting camo variants on old weapons.
	if ( !IsSubstr( loadoutPrimary, "iw5" ) )
		self.loadoutPrimaryCamo = 0;
	if ( !IsSubstr( loadoutSecondary, "iw5" ) )
		self.loadoutSecondaryCamo = 0;

	self.loadoutPrimaryReticle = int(tableLookup( "mp/reticleTable.csv", 1, loadoutPrimaryReticle, 0 ));
	self.loadoutSecondaryReticle = int(tableLookup( "mp/reticleTable.csv", 1, loadoutSecondaryReticle, 0));
	
	// sorry, not supporting reticle variants on old weapons.
	if ( !IsSubstr( loadoutPrimary, "iw5" ) )
		self.loadoutPrimaryReticle = 0;
	if ( !IsSubstr( loadoutSecondary, "iw5" ) )
		self.loadoutSecondaryReticle = 0;

	if ( loadoutSecondary == "none" )
		secondaryName = "none";
	else
	{
		secondaryName = buildWeaponName( loadoutSecondary, loadoutSecondaryAttachment, loadoutSecondaryAttachment2, self.loadoutSecondaryCamo, self.loadoutSecondaryReticle );
		self _giveWeapon( secondaryName );
		// do a quick check to make sure the weapon xp and rank jive with each other
		weaponTokens = StrTok( secondaryName, "_" );
		
		if ( weaponTokens[0] == "iw5" )
			weaponTokens[0] = weaponTokens[0] + "_" + weaponTokens[1];
		else if ( weaponTokens[0] == "alt" )
			weaponTokens[0] = weaponTokens[1] + "_" + weaponTokens[2];
		
		weaponName = weaponTokens[0];
		
		curWeaponRank = self maps\mp\gametypes\_rank::getWeaponRank( weaponName );
		curWeaponStatRank = self GetPlayerData( "weaponRank", weaponName );
		if( curWeaponRank != curWeaponStatRank )
			self SetPlayerData( "weaponRank", weaponName, curWeaponRank );
	}
		
	self SetOffhandPrimaryClass( "other" );

	// Action Slots
	self _SetActionSlot( 1, "" );
	//self _SetActionSlot( 1, "nightvision" );
	self _SetActionSlot( 3, "altMode" );
	self _SetActionSlot( 4, "" );

	// Perks
	self _clearPerks();
	self _detachAll();
	
	// these special case giving pistol death have to come before
	// perk loadout to ensure player perk icons arent overwritten
	if ( level.dieHardMode )
		self givePerk( "specialty_pistoldeath", false );
	
	self loadoutAllPerks( loadoutEquipment, loadoutPerk1, loadoutPerk2, loadoutPerk3, loadoutPrimaryBuff, loadoutSecondaryBuff );
		
	if ( self _hasPerk( "specialty_extraammo" ) && secondaryName != "none" && getWeaponClass( secondaryName ) != "weapon_projectile" )
		self giveMaxAmmo( secondaryName );

	// trying to stop killstreaks from targeting the newly spawned
	self.spawnPerk = false;
	if( !self _hasPerk( "specialty_blindeye" ) && self.avoidKillstreakOnSpawnTimer > 0 )
		self thread maps\mp\perks\_perks::giveBlindEyeAfterSpawn();

	// need to give deathstreaks after perks because some deathstreaks need to supercede perks, like juiced needs to happen after lightweight because of the speed change
	// only give the deathstreak for the initial spawn for this life.
	if( self.pers["cur_death_streak"] > 0 )
	{
		deathStreaks = [];
		if( loadoutDeathStreak != "specialty_null" )
			deathStreaks[ loadoutDeathStreak ] = int( tableLookup( "mp/perkTable.csv", 1, loadoutDeathStreak, 6 ) );

		if ( self getPerkUpgrade( loadoutPerk1 ) == "specialty_rollover" || self getPerkUpgrade( loadoutPerk2 ) == "specialty_rollover" || self getPerkUpgrade( loadoutPerk3 ) == "specialty_rollover" )
		{
			foreach( key, value in deathStreaks )
				deathStreaks[ key ] -= 1;
		}

		foreach( key, value in deathStreaks )
		{
			if ( self.pers["cur_death_streak"] >= value )
			{
				// the care package death streak should only be given once per death streak, not every time after the value is hit
				if( key == "specialty_carepackage" && self.pers[ "cur_death_streak" ] > value )
					continue;
				// the uav death streak should only be given once per death streak, not every time after the value is hit
				if( key == "specialty_uav" && self.pers[ "cur_death_streak" ] > value )
					continue;

				self thread givePerk( key, true );
				self thread maps\mp\gametypes\_hud_message::splashNotify( key );
			}
		}
	}

	// killstreaks need to be given after perks because of things like hardline
	if ( level.killstreakRewards && !isDefined( loadoutKillstreak1 ) && !isDefined( loadoutKillstreak2 ) && !isDefined( loadoutKillstreak3 ) )
	{
		if ( isDefined( self.pers["copyCatLoadout"] ) && self.pers["copyCatLoadout"]["inUse"] && allowCopycat )
		{
			loadoutKillstreak1 = clonedLoadout["loadoutKillstreak1"];
			loadoutKillstreak2 = clonedLoadout["loadoutKillstreak2"];
			loadoutKillstreak3 = clonedLoadout["loadoutKillstreak3"];
		}
		else
		{
			defaultKillstreak1 = undefined;
			defaultKillstreak2 = undefined;
			defaultKillstreak3 = undefined;
			playerData = undefined;

			// IW5 Defcon Killstreak loadout
			switch( self.streakType )
			{
			case "support":
				defaultKillstreak1 = table_getKillstreak( level.classTableName, 2, 1 );
				defaultKillstreak2 = table_getKillstreak( level.classTableName, 2, 2 );
				defaultKillstreak3 = table_getKillstreak( level.classTableName, 2, 3 );
				playerData = "defenseStreaks";
				break;
			case "specialist":
				defaultKillstreak1 = table_getKillstreak( level.classTableName, 1, 1 );
				defaultKillstreak2 = table_getKillstreak( level.classTableName, 1, 2 );
				defaultKillstreak3 = table_getKillstreak( level.classTableName, 1, 3 );
				playerData = "specialistStreaks";
				break;
			default: // assault
				defaultKillstreak1 = table_getKillstreak( level.classTableName, 0, 1 );
				defaultKillstreak2 = table_getKillstreak( level.classTableName, 0, 2 );
				defaultKillstreak3 = table_getKillstreak( level.classTableName, 0, 3 );
				playerData = "assaultStreaks";
				break;
			}

			loadoutKillstreak1 = undefined;
			loadoutKillstreak2 = undefined;
			loadoutKillstreak3 = undefined;

			// this is a custom class so pull from the player data
			if( IsSubStr( class, "custom" ) )
			{
				assert( IsDefined( self.class_num ) );
				customClassLoc = cac_getCustomClassLoc();
				loadoutKillstreak1 = self getPlayerData( customClassLoc, self.class_num, playerData, 0 );
				loadoutKillstreak2 = self getPlayerData( customClassLoc, self.class_num, playerData, 1 );
				loadoutKillstreak3 = self getPlayerData( customClassLoc, self.class_num, playerData, 2 );
			}

			// give juggernauts and special gamemode classes the current killstreaks the player has
			if( IsSubStr( class, "juggernaut" ) || isGameModeClass )
			{
				foreach( killstreak in self.killstreaks )
				{
					if( !IsDefined( loadoutKillstreak1 ) )
						loadoutKillstreak1 = killstreak;
					else if( !IsDefined( loadoutKillstreak2 ) )
						loadoutKillstreak2 = killstreak;
					else if( !IsDefined( loadoutKillstreak3 ) )
						loadoutKillstreak3 = killstreak;
				}
			}

			// give defaults if this isn't a custom class, or juggernauts, or special gamemode classes
			if( !isSubstr( class, "custom" ) && !isSubstr( class, "juggernaut" ) && !isGameModeClass )
			{
				loadoutKillstreak1 = defaultKillstreak1;
				loadoutKillstreak2 = defaultKillstreak2;
				loadoutKillstreak3 = defaultKillstreak3;
			}

			// if the killstreak variables are undefined by the time they get here then we should set them to "none" because they may not have selected a killstreak
			if( !IsDefined( loadoutKillstreak1 ) )
				loadoutKillstreak1 = "none";
			if( !IsDefined( loadoutKillstreak2 ) )
				loadoutKillstreak2 = "none";
			if( !IsDefined( loadoutKillstreak3 ) )
				loadoutKillstreak3 = "none";

			// validate to stop cheaters
			if( !isValidKillstreak( loadoutKillstreak1 ) || ( isCustomClass && !self isItemUnlocked( loadoutKillstreak1 ) ) )
				loadoutKillstreak1 = table_getKillstreak( level.classTableName, 0, 1 );
			if( !isValidKillstreak( loadoutKillstreak2 ) || ( isCustomClass && !self isItemUnlocked( loadoutKillstreak2 ) ) )
				loadoutKillstreak2 = table_getKillstreak( level.classTableName, 0, 2 );
			if( !isValidKillstreak( loadoutKillstreak3 ) || ( isCustomClass && !self isItemUnlocked( loadoutKillstreak3 ) ) )
				loadoutKillstreak3 = table_getKillstreak( level.classTableName, 0, 3 );
		}
	}
	else if ( !level.killstreakRewards )
	{
		loadoutKillstreak1 = "none";
		loadoutKillstreak2 = "none";
		loadoutKillstreak3 = "none";
	}

	self setKillstreaks( loadoutKillstreak1, loadoutKillstreak2, loadoutKillstreak3 );
	// reset the killstreaks when there is a new class chosen, unless it's juggernaut or special gamemode class, this fixes the bug where killstreaks don't reset if you change classes during pre-match timer
	if ( IsDefined( self.lastClass ) && self.lastClass != self.class && !IsSubStr( self.class, "juggernaut" ) && !IsSubStr( self.lastClass, "juggernaut" ) && !IsSubStr( class, "juggernaut" ) )
	{
		if( wasOnlyRound() || self.lastClass != "" )
		{
			// put all of their killstreaks into the gimme slot now that it stacks
			streakNames = [];
			inc = 0;
			// first go through the gimme slot killstreaks, this way they will be in the bottom of the pile
			if( self.pers["killstreaks"].size > KILLSTREAK_STACKING_START_SLOT )
			{
				for( i = KILLSTREAK_STACKING_START_SLOT; i < self.pers["killstreaks"].size; i++ )
				{
					streakNames[inc] = self.pers["killstreaks"][i].streakName;
					inc++;
				}
			}
			// now go through the earned killstreaks, so these will be on the top of the pile
			if( self.pers["killstreaks"].size )
			{
				for( i = KILLSTREAK_SLOT_1; i < KILLSTREAK_SLOT_3 + 1; i++ )
				{
					if( IsDefined( self.pers["killstreaks"][i] ) && 
						IsDefined( self.pers["killstreaks"][i].streakName ) &&
						self.pers["killstreaks"][i].available && 
						!self.pers["killstreaks"][i].isSpecialist )
					{
						streakNames[inc] = self.pers["killstreaks"][i].streakName;
						inc++;
					}
				}
			}

			maps\mp\killstreaks\_killstreaks::clearKillstreaks();

			for( i = 0; i < streakNames.size; i++ )
			{
				self maps\mp\killstreaks\_killstreaks::giveKillstreak( streakNames[i] );
			}
		}
	}
	
	// don't change these if we're becoming a juggernaut
	if( !IsSubStr( class, "juggernaut" ) )
	{
		if( isDefined( self.lastClass ) && self.lastClass != "" && self.lastClass != self.class )
		{
			self incPlayerStat( "mostclasseschanged", 1 );
		}

		self.pers["lastClass"] = self.class;
		self.lastClass = self.class;		
	}

	// Primary Weapon
	primaryName = buildWeaponName( loadoutPrimary, loadoutPrimaryAttachment, loadoutPrimaryAttachment2, self.loadoutPrimaryCamo, self.loadoutPrimaryReticle );
	self _giveWeapon( primaryName );


	self SwitchToWeapon( primaryName );
	// do a quick check to make sure the weapon xp and rank jive with each other
	weaponTokens = StrTok( primaryName, "_" );
	
	if ( weaponTokens[0] == "iw5" )
		weaponName = weaponTokens[0] + "_" + weaponTokens[1];
	else if ( weaponTokens[0] == "alt" )
		weaponName = weaponTokens[1] + "_" + weaponTokens[2];
	else
		weaponName = weaponTokens[0];
	
	curWeaponRank = self maps\mp\gametypes\_rank::getWeaponRank( weaponName );
	curWeaponStatRank = self GetPlayerData( "weaponRank", weaponName );
	if( curWeaponRank != curWeaponStatRank )
		self SetPlayerData( "weaponRank", weaponName, curWeaponRank );

	// fix changing from a riotshield class to a riotshield class during grace period not giving a shield
	if ( primaryName == "riotshield_mp" && level.inGracePeriod )
		self notify ( "weapon_change", "riotshield_mp" );

	if ( self _hasPerk( "specialty_extraammo" ) )
		self giveMaxAmmo( primaryName );

	//	only when called during spawn flow
	if ( setPrimarySpawnWeapon )
		self setSpawnWeapon( primaryName );
	
	self.pers["primaryWeapon"] = weaponName;
	
	primaryTokens = strtok( primaryName, "_" );
	
	// Primary Offhand was given by givePerk (it's your perk1)
	
	// Secondary Offhand
	offhandSecondaryWeapon = loadoutOffhand;
	
	if ( loadoutOffhand == "none" )
		self SetOffhandSecondaryClass( "none" );
	else if ( loadoutOffhand == "flash_grenade_mp" )
		self SetOffhandSecondaryClass( "flash" );
	else if ( loadoutOffhand == "smoke_grenade_mp" || loadoutOffhand == "concussion_grenade_mp" )
		self SetOffhandSecondaryClass( "smoke" );	
	else 
		self SetOffhandSecondaryClass( "flash" );
	
	switch( offhandSecondaryWeapon )
	{
		case "none":
			break;
		case "specialty_portable_radar":
		case "specialty_scrambler":
		case "specialty_tacticalinsertion":
		case "trophy_mp":
			self givePerk( offhandSecondaryWeapon, false );
			break;
	
		default:
			self giveWeapon( offhandSecondaryWeapon );
	
			if( loadOutOffhand == "flash_grenade_mp" )
				self setWeaponAmmoClip( offhandSecondaryWeapon, 2 );
			else if( loadOutOffhand == "concussion_grenade_mp" )
				self setWeaponAmmoClip( offhandSecondaryWeapon, 2 );
			else
				self setWeaponAmmoClip( offhandSecondaryWeapon, 1 );
			break;
	}

	primaryWeapon = primaryName;
	self.primaryWeapon = primaryWeapon;
	self.secondaryWeapon = secondaryName;

	self maps\mp\gametypes\_teams::playerModelForWeapon( self.pers["primaryWeapon"], getBaseWeaponName( secondaryName ) );
		
	self.isSniper = (weaponClass( self.primaryWeapon ) == "sniper");
	
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();

	// cac specialties that require loop threads
	self maps\mp\perks\_perks::cac_selector();
	
	self notify ( "changed_kit" );
	self notify ( "giveLoadout" );
}

_detachAll()
{
	if ( isDefined( self.hasRiotShield ) && self.hasRiotShield )
	{
		if ( self.hasRiotShieldEquipped )
		{
			self DetachShieldModel( "weapon_riot_shield_mp", "tag_weapon_left" );
			self.hasRiotShieldEquipped = false;
		}
		else
		{
			self DetachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );
		}
		
		self.hasRiotShield = false;
	}
	
	self detachAll();
}

isPerkUpgraded( perkName )
{
	perkUpgrade = tablelookup( "mp/perktable.csv", 1, perkName, 8 );
	
	if ( perkUpgrade == "" || perkUpgrade == "specialty_null" )
		return false;
		
	if ( !self isItemUnlocked( perkUpgrade ) )
		return false;
		
	return true;
}

getPerkUpgrade( perkName )
{
	perkUpgrade = tablelookup( "mp/perktable.csv", 1, perkName, 8 );
	
	if ( perkUpgrade == "" || perkUpgrade == "specialty_null" )
		return "specialty_null";
		
	if ( !self isItemUnlocked( perkUpgrade ) )
		return "specialty_null";
		
	return ( perkUpgrade );
}

loadoutAllPerks( loadoutEquipment, loadoutPerk1, loadoutPerk2, loadoutPerk3, loadoutPrimaryBuff, loadoutSecondaryBuff )
{
	loadoutEquipment = maps\mp\perks\_perks::validatePerk( 1, loadoutEquipment );
	loadoutPerk1 = maps\mp\perks\_perks::validatePerk( 1, loadoutPerk1 );
	loadoutPerk2 = maps\mp\perks\_perks::validatePerk( 2, loadoutPerk2 );
	loadoutPerk3 = maps\mp\perks\_perks::validatePerk( 3, loadoutPerk3 );

	loadoutPrimaryBuff = maps\mp\perks\_perks::validatePerk( undefined, loadoutPrimaryBuff );
	if( loadoutPerk2 == "specialty_twoprimaries" )
		loadoutSecondaryBuff = maps\mp\perks\_perks::validatePerk( undefined, loadoutSecondaryBuff );

	self.loadoutPerk1 = loadoutPerk1;
	self.loadoutPerk2 = loadoutPerk2;
	self.loadoutPerk3 = loadoutPerk3;
	self.loadoutPerkEquipment = loadoutEquipment;
	self.loadoutPrimaryBuff = loadoutPrimaryBuff;
	if( loadoutPerk2 == "specialty_twoprimaries" )
		self.loadoutSecondaryBuff = loadoutSecondaryBuff;

	if( loadoutEquipment != "specialty_null" )
		self givePerk( loadoutEquipment, true );
	if( loadoutPerk1 != "specialty_null" )
		self givePerk( loadoutPerk1, true );
	if( loadoutPerk2 != "specialty_null" )
		self givePerk( loadoutPerk2, true );
	if( loadoutPerk3 != "specialty_null" )
		self givePerk( loadoutPerk3, true );

	//self givePerk( loadoutTeamPerk ); //not currently validated
		
	//self givePerk( loadoutAmmoType );
	
	if( loadoutPrimaryBuff != "specialty_null" )
		self givePerk( loadoutPrimaryBuff, true );
	// NOTE: don't give the secondary buff here because it should be weapon specific and only if you're currently holding the weapon, see watchWeaponChange()

	perkUpgrd[0] = tablelookup( "mp/perktable.csv", 1, loadoutPerk1, 8 );
	perkUpgrd[1] = tablelookup( "mp/perktable.csv", 1, loadoutPerk2, 8 );
	perkUpgrd[2] = tablelookup( "mp/perktable.csv", 1, loadoutPerk3, 8 );
	
	foreach( upgrade in perkUpgrd )
	{
		if ( upgrade == "" || upgrade == "specialty_null" )
			continue;
			
		if ( self isItemUnlocked( upgrade ) || !self rankingEnabled() )
		{
			// we want to put the upgrade perk in the slot in code
			self givePerk( upgrade, true );
		}
	}

	// now if we don't have specialty_assists then reset the persistent data
	if( !self _hasPerk( "specialty_assists" ) )
		self.pers["assistsToKill"] = 0;
}

trackRiotShield()
{
	self endon ( "death" );
	self endon ( "disconnect" );

	self.hasRiotShield = self hasWeapon( "riotshield_mp" );
	self.hasRiotShieldEquipped = (self.currentWeaponAtSpawn == "riotshield_mp");
	
	// note this function must play nice with _detachAll().
	
	if ( self.hasRiotShield )
	{
		if ( self.primaryWeapon == "riotshield_mp" && self.secondaryWeapon == "riotshield_mp" )
		{
			self AttachShieldModel( "weapon_riot_shield_mp", "tag_weapon_left" );
			self AttachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );
		}
		else if ( self.hasRiotShieldEquipped )
		{
			self AttachShieldModel( "weapon_riot_shield_mp", "tag_weapon_left" );
		}
		else
		{
			self AttachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );
		}
	}
	
	for ( ;; )
	{
		self waittill ( "weapon_change", newWeapon );
		
		//	need to check both, player can be 'juggernaut' by game setup default class specification now, not only killstreak
		if ( newWeapon == "riotshield_mp" || newWeapon == "iw5_riotshieldjugg_mp" )
		{
			// defensive check in case we somehow get an extra "weapon_change"
			if ( self.hasRiotShieldEquipped )
				continue;
			
			if ( self.primaryWeapon == newWeapon && self.secondaryWeapon == newWeapon )
				continue;
			else if ( self.hasRiotShield )
				self MoveShieldModel( "weapon_riot_shield_mp", "tag_shield_back", "tag_weapon_left" );
			else
				self AttachShieldModel( "weapon_riot_shield_mp", "tag_weapon_left" );
			
			self.hasRiotShield = true;
			self.hasRiotShieldEquipped = true;
		}
		else if ( (self IsMantling()) && (newWeapon == "none") )
		{
			// Do nothing, we want to keep that weapon on their arm.
		}
		else if ( self.hasRiotShieldEquipped )
		{
			assert( self.hasRiotShield );
			self.hasRiotShield = ( self hasWeapon( "riotshield_mp" ) || self hasWeapon( "iw5_riotshieldjugg_mp" ) );
			
			if ( self.hasRiotShield )
				self MoveShieldModel( "weapon_riot_shield_mp", "tag_weapon_left", "tag_shield_back" );
			else
				self DetachShieldModel( "weapon_riot_shield_mp", "tag_weapon_left" );
			
			self.hasRiotShieldEquipped = false;
		}
		else if ( self.hasRiotShield )
		{
			if ( !self hasWeapon( "riotshield_mp" ) && !self hasWeapon( "iw5_riotshieldjugg_mp" ) )
			{
				// we probably just lost all of our weapons (maybe switched classes)
				self DetachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );
				self.hasRiotShield = false;
			}
		}
	}
}


tryAttach( placement ) // deprecated; hopefully we won't need to bring this defensive function back
{
	if ( !isDefined( placement ) || placement != "back" )
		tag = "tag_weapon_left";
	else
		tag = "tag_shield_back";
	
	attachSize = self getAttachSize();
	
	for ( i = 0; i < attachSize; i++ )
	{
		attachedTag = self getAttachTagName( i );
		if ( attachedTag == tag &&  self getAttachModelName( i ) == "weapon_riot_shield_mp" )
		{
			return;
		}
	}
	
	self AttachShieldModel( "weapon_riot_shield_mp", tag );
}

tryDetach( placement ) // deprecated; hopefully we won't need to bring this defensive function back
{
	if ( !isDefined( placement ) || placement != "back" )
		tag = "tag_weapon_left";
	else
		tag = "tag_shield_back";
	
	
	attachSize = self getAttachSize();
	
	for ( i = 0; i < attachSize; i++ )
	{
		attachedModel = self getAttachModelName( i );
		if ( attachedModel == "weapon_riot_shield_mp" )
		{
			self DetachShieldModel( attachedModel, tag);
			return;
		}
	}
	return;
}


buildWeaponName( baseName, attachment1, attachment2, camo, reticle )
{
	if ( !isDefined( level.letterToNumber ) )
		level.letterToNumber = makeLettersToNumbers();
	
	// disable bling when perks are disabled
	if ( getDvarInt ( "scr_game_perks" ) == 0 )
	{
		attachment2 = "none";
	}
	
	//hack for current menu bug - remove before ship
	if ( isDefined( reticle ) && reticle != 0 && getAttachmentType( attachment1 ) != "rail" && getAttachmentType( attachment2 ) != "rail" )
	{
		reticle = undefined;
	}
		
	if( getAttachmentType( attachment1 ) == "rail" )
	{
		attachment1 = attachmentMap( attachment1, baseName );
	}
	else if ( getAttachmentType( attachment2 ) == "rail" )
	{
		attachment2 = attachmentMap( attachment2, baseName );
	}
	
	bareWeaponName = "";
	
	if ( isSubstr(baseName, "iw5_") )
	{
		weaponName = baseName + "_mp";
		endIndex = baseName.size;
		bareWeaponName = GetSubStr( baseName, 4, endIndex );
	}
	else
	{
		weaponName = baseName;
	}
	
	attachments = [];

	if ( attachment1 != "none" && attachment2 != "none" )
	{
		if ( level.letterToNumber[attachment1[0]] < level.letterToNumber[attachment2[0]] )
		{
			
			attachments[0] = attachment1;
			attachments[1] = attachment2;
			
		}
		else if ( level.letterToNumber[attachment1[0]] == level.letterToNumber[attachment2[0]] )
		{
			if ( level.letterToNumber[attachment1[1]] < level.letterToNumber[attachment2[1]] )
			{
				attachments[0] = attachment1;
				attachments[1] = attachment2;
			}
			else
			{
				attachments[0] = attachment2;
				attachments[1] = attachment1;
			}	
		}
		else
		{
			attachments[0] = attachment2;
			attachments[1] = attachment1;
		}
		
		if ( getWeaponClass( baseName ) == "weapon_sniper" && getAttachmentType( attachment1 ) != "rail" && getAttachmentType( attachment2 ) != "rail" ) 	
		{
			if ( attachment1 != "zoomscope" && attachment2 != "zoomscope" )
				attachments[2] = bareWeaponName + "scope";
		}
	}
	else if ( attachment1 != "none" )
	{
		attachments[0] = attachment1;
		
		if ( getWeaponClass( baseName ) == "weapon_sniper" && getAttachmentType( attachment1 ) != "rail" && attachment1 != "zoomscope" )
			attachments[1] = bareWeaponName + "scope";
		
	}
	else if ( attachment2 != "none" )
	{
		attachments[0] = attachment2;	
		
		if ( getWeaponClass( baseName ) == "weapon_sniper" && getAttachmentType( attachment2 ) != "rail" && attachment2 != "zoomscope" )
			attachments[1] = bareWeaponName + "scope";
	}
	else if ( getWeaponClass( baseName ) == "weapon_sniper" )
	{
		attachments[0] = bareWeaponName + "scope";
	}
	
	
	//Handle VZ Scopes
	if( isDefined( attachments[0] ) && attachments[0] == "vzscope" )
		attachments[0] = bareWeaponName + "scopevz";
	else if( isDefined( attachments[1] ) && attachments[1] == "vzscope" )
		attachments[1] = bareWeaponName + "scopevz";
	else if( isDefined( attachments[2] ) && attachments[2] == "vzscope" )
		attachments[2] = bareWeaponName + "scopevz";
	
	//orders attachments alphabetically.
	if ( isDefined( attachments.size ) && attachments.size )
	{
		i = 0;
		while( i < attachments.size )
		{
			if ( isDefined( attachments[i+1] ) && is_later_in_alphabet( attachments[i], attachments[i+1] ) )
			{
				tmpAtch = attachments[i];
				attachments[i] = attachments[i+1];
				attachments[i+1] = tmpAtch;
				i = 0;
				continue;
			}
			i++;
		}
	}
	
	foreach ( attachment in attachments )
	{
		weaponName += "_" + attachment;
	}

	if ( isSubstr(weaponName, "iw5_") )
	{
		weaponName = buildWeaponNameCamo( weaponName, camo );
		weaponName = buildWeaponNameReticle( weaponName, reticle );
		return ( weaponName );
	}
	else if ( !isValidWeapon( weaponName + "_mp" ) )
	{
		return ( baseName + "_mp" );
	}
	else
	{
		weaponName = buildWeaponNameCamo( weaponName, camo );
		weaponName = buildWeaponNameReticle( weaponName, reticle );
		return ( weaponName + "_mp" );
	}
}

buildWeaponNameCamo( weaponName, camo )
{
	if ( !isdefined( camo ) )
		return weaponName;
	if ( camo <= 0 )
		return weaponName;

	if ( camo < 10 )
		weaponName += "_camo0";
	else
		weaponName += "_camo";
	weaponName += camo;

	return weaponName;
}

buildWeaponNameReticle( weaponName, reticle )
{
	if ( !isdefined( reticle ) )
		return weaponName;
	if ( reticle <= 0 )
		return weaponName;

	weaponName += "_scope";
	weaponName += reticle;

	return weaponName;
}

makeLettersToNumbers()
{
	array = [];
	
	array["a"] = 0;
	array["b"] = 1;
	array["c"] = 2;
	array["d"] = 3;
	array["e"] = 4;
	array["f"] = 5;
	array["g"] = 6;
	array["h"] = 7;
	array["i"] = 8;
	array["j"] = 9;
	array["k"] = 10;
	array["l"] = 11;
	array["m"] = 12;
	array["n"] = 13;
	array["o"] = 14;
	array["p"] = 15;
	array["q"] = 16;
	array["r"] = 17;
	array["s"] = 18;
	array["t"] = 19;
	array["u"] = 20;
	array["v"] = 21;
	array["w"] = 22;
	array["x"] = 23;
	array["y"] = 24;
	array["z"] = 25;
	
	return array;
}

setKillstreaks( streak1, streak2, streak3 )
{
	self.killStreaks = [];

	killStreaks = [];

	if ( IsDefined( streak1 ) && streak1 != "none" )
	{
		streakVal = self maps\mp\killstreaks\_killstreaks::getStreakCost( streak1 );
		killStreaks[streakVal] = streak1;
	}
	if ( IsDefined( streak2 ) && streak2 != "none" )
	{
		streakVal = self maps\mp\killstreaks\_killstreaks::getStreakCost( streak2 );
		killStreaks[streakVal] = streak2;
	}
	if ( IsDefined( streak3 ) && streak3 != "none" )
	{
		streakVal = self maps\mp\killstreaks\_killstreaks::getStreakCost( streak3 );
		killStreaks[streakVal] = streak3;
	}

	// foreach doesn't loop through numbers arrays in number order; it loops through the elements in the order
	// they were added.  We'll use this to fix it for now.
	maxVal = 0;
	foreach ( streakVal, streakName in killStreaks )
	{
		if ( streakVal > maxVal )
			maxVal = streakVal;
	}

	for ( streakIndex = 0; streakIndex <= maxVal; streakIndex++ )
	{
		if ( !isDefined( killStreaks[streakIndex] ) )
			continue;
			
		streakName = killStreaks[streakIndex];
			
		self.killStreaks[ streakIndex ] = killStreaks[ streakIndex ];
	}
	// end lameness
}


replenishLoadout() // used by ammo hardpoint.
{
	team = self.pers["team"];
	class = self.pers["class"];

    weaponsList = self GetWeaponsListAll();
    for( idx = 0; idx < weaponsList.size; idx++ )
    {
		weapon = weaponsList[idx];

		self giveMaxAmmo( weapon );
		self SetWeaponAmmoClip( weapon, 9999 );

		if ( weapon == "claymore_mp" || weapon == "claymore_detonator_mp" )
			self setWeaponAmmoStock( weapon, 2 );
    }
	
	if ( self getAmmoCount( level.classGrenades[class]["primary"]["type"] ) < level.classGrenades[class]["primary"]["count"] )
 		self SetWeaponAmmoClip( level.classGrenades[class]["primary"]["type"], level.classGrenades[class]["primary"]["count"] );

	if ( self getAmmoCount( level.classGrenades[class]["secondary"]["type"] ) < level.classGrenades[class]["secondary"]["count"] )
 		self SetWeaponAmmoClip( level.classGrenades[class]["secondary"]["type"], level.classGrenades[class]["secondary"]["count"] );	
}


onPlayerConnecting()
{
	for(;;)
	{
		level waittill( "connected", player );

		if ( !isDefined( player.pers["class"] ) )
		{
			player.pers["class"] = "";
		}
		if ( !isDefined( player.pers["lastClass"] ) )
		{
			player.pers["lastClass"] = "";
		}
		player.class = player.pers["class"];
		player.lastClass = player.pers["lastClass"];
		player.detectExplosives = false;
		player.bombSquadIcons = [];
		player.bombSquadIds = [];
	}
}


fadeAway( waitDelay, fadeDelay )
{
	wait waitDelay;
	
	self fadeOverTime( fadeDelay );
	self.alpha = 0;
}


setClass( newClass )
{
	self.curClass = newClass;
}

getPerkForClass( perkSlot, className )
{
    class_num = getClassIndex( className );

    if( isSubstr( className, "custom" ) )
        return cac_getPerk( class_num, perkSlot );
    else
        return table_getPerk( level.classTableName, class_num, perkSlot );
}


classHasPerk( className, perkName )
{
	return( getPerkForClass( 0, className ) == perkName || getPerkForClass( 1, className ) == perkName || getPerkForClass( 2, className ) == perkName );
}

isValidPrimary( refString, showAssert )
{
	if( !IsDefined( showAssert ) )
		showAssert = true;

	switch ( refString )
	{
		case "iw5_m4":
		case "riotshield":
		case "iw5_ak47":
		case "iw5_m16":
		case "iw5_fad":
		case "iw5_acr":
		case "iw5_type95":
		case "iw5_mk14":
		case "iw5_scar":
		case "iw5_g36c":
		case "iw5_cm901":
		case "iw5_mp5":
		case "iw5_mp7":
		case "iw5_m9":
		case "iw5_p90":
		case "iw5_pp90m1":
		case "iw5_ump45":
		case "iw5_barrett":
		case "iw5_rsass":
		case "iw5_dragunov":
		case "iw5_msr":
		case "iw5_as50":
		case "iw5_ksg":
		case "iw5_1887":
		case "iw5_striker":
		case "iw5_aa12":
		case "iw5_usas12":
		case "iw5_spas12":
		case "xm25":
		case "iw5_m60":
		case "iw5_mk46":
		case "iw5_pecheneg":
		case "iw5_sa80":
		case "iw5_mg36":
		case "iw5_l96a1":
		case "iw5_m60jugg":
		case "iw5_riotshieldjugg":
			return true;
		default:
			if( showAssert )
				assertMsg( "Replacing invalid primary weapon: " + refString );
			return false;
	}
}

isValidSecondary( refString, perk2, perk3, showAssert )
{
	if( !IsDefined( showAssert ) )
		showAssert = true;

	switch ( refString )
	{
		case "iw5_44magnum":
		case "iw5_usp45":
		case "iw5_deserteagle":
		case "iw5_mp412":
		case "iw5_g18":
		case "iw5_fmg9":
		case "iw5_mp9":
		case "iw5_skorpion":
		case "iw5_p99":
		case "iw5_fnfiveseven":
		case "m320":
		case "rpg":
		case "iw5_smaw":
		case "stinger":
		case "javelin":
		case "xm25":

		case "iw5_usp45jugg":
		case "iw5_mp412jugg":
			return true;

		case "iw5_m4":
		case "riotshield":
		case "iw5_ak47":
		case "iw5_m16":
		case "iw5_fad":
		case "iw5_acr":
		case "iw5_type95":
		case "iw5_mk14":
		case "iw5_scar":
		case "iw5_g36c":
		case "iw5_cm901":
		case "iw5_mp5":
		case "iw5_mp7":
		case "iw5_m9":
		case "iw5_p90":
		case "iw5_pp90m1":
		case "iw5_ump45":
		case "iw5_barrett":
		case "iw5_rsass":
		case "iw5_dragunov":
		case "iw5_msr":
		case "iw5_as50":
		case "iw5_ksg":
		case "iw5_1887":
		case "iw5_striker":
		case "iw5_aa12":
		case "iw5_usas12":
		case "iw5_spas12":
		case "iw5_m60":
		case "iw5_mk46":
		case "iw5_pecheneg":
		case "iw5_sa80":
		case "iw5_mg36":
		case "iw5_l96a1":
			if ( getDvarInt ( "scr_game_perks" ) == 1 && ( perk2 == "specialty_twoprimaries" || perk3 == "specialty_twoprimaries" ) )
			{
				return true;
			}
			else
			{
				return false;
			}	
		default:
			if( showAssert )
				assertMsg( "Replacing invalid secondary weapon: " + refString );
			return false;
	}
}

isValidAttachment( refString, shouldAssert )
{
	if( !IsDefined( shouldAssert ) )
		shouldAssert = true;

	switch ( refString )
	{
		case "none":
		case "acog":
		case "acogsmg":
		case "reflex":
		case "reflexsmg":
		case "reflexlmg":
		case "silencer":
		case "silencer02":
		case "silencer03":
		case "grip":
		case "gl":
		case "gp25":
		case "m320":
		case "akimbo":
		case "thermal":
		case "thermalsmg":
		case "shotgun":
		case "heartbeat":
		case "fmj":
		case "rof":
		case "xmags":
		case "eotech":  
		case "eotechsmg":
		case "eotechlmg":
		case "tactical":
		case "vzscope":
		case "hamrhybrid":
		case "hybrid":
		case "zoomscope":
			return true;
		default:
			if( shouldAssert )
				assertMsg( "Replacing invalid equipment weapon: " + refString );
			return false;
	}
}

isAttachmentUnlocked( weaponRef, attachmentRef )
{
/#
	if( GetDvarInt( "unlockAllItems" ) )
		return true;
#/
	tableWeaponClassCol = 0;
	tableWeaponClassAttachmentCol = 2;
	tableWeaponRankCol = 4;
	weaponRank = self GetPlayerData( "weaponRank", weaponRef );
	colNum = int( tableLookup( "mp/weaponRankTable.csv", tableWeaponClassCol, getWeaponClass( weaponRef ), tableWeaponClassAttachmentCol ) );
	attachmentRank = int( tableLookup( "mp/weaponRankTable.csv", colNum, attachmentRef, tableWeaponRankCol ) );
	if( weaponRank >= attachmentRank )
		return true;

	return false;
}

isValidWeaponBuff( refString )
{
	switch ( refString )
	{
	case "specialty_bulletpenetration":
	case "specialty_marksman":
	case "specialty_bling":
	case "specialty_sharp_focus":
	case "specialty_armorpiercing":
	case "specialty_holdbreathwhileads":
	case "specialty_longerrange":
	case "specialty_fastermelee":
	case "specialty_reducedsway":
	case "specialty_lightweight":
	case "specialty_moredamage":
		return true;
	default:
		//assertMsg( "Replacing invalid weapon buff: " + refString );
		return false;
	}
}

isWeaponBuffUnlocked( weaponRef, buffRef )
{
/#
	if( GetDvarInt( "unlockAllItems" ) )
		return true;
#/
	tableWeaponClassCol = 0;
	tableWeaponClassBuffCol = 4;
	tableWeaponRankCol = 4;
	weaponRank = self GetPlayerData( "weaponRank", weaponRef );
	colNum = int( tableLookup( "mp/weaponRankTable.csv", tableWeaponClassCol, getWeaponClass( weaponRef ), tableWeaponClassBuffCol ) );
	buffRank = int( tableLookup( "mp/weaponRankTable.csv", colNum, buffRef, tableWeaponRankCol ) );
	if( weaponRank >= buffRank )
		return true;

	return false;
}

isValidCamo( refString )
{
	switch ( refString )
	{
		case "none":
		case "classic":
		case "snow":
		case "multi":
		case "d_urban":
		case "hex":
		case "choco":
		case "marine":
		case "snake":
		case "winter":
		case "blue":
		case "red":
		case "autumn":
		case "gold":
			return true;
		default:
			assertMsg( "Replacing invalid camo: " + refString );
			return false;
	}
}

isValidReticle( refString )
{
	switch ( refString )
	{
	case "none":
	case "ret1":
	case "ret2":
	case "ret3":
	case "ret4":
	case "ret5":
	case "ret6":
		return true;
	default:
		assertMsg( "Replacing invalid reticle " + refString );
		return false;
	}
}

isCamoUnlocked( weaponRef, camoRef )
{
/#
	if( GetDvarInt( "unlockAllItems" ) )
		return true;
#/
	tableWeaponClassCol = 0;
	tableWeaponClassCamoCol = 3;
	tableWeaponRankCol = 4;
	weaponRank = self GetPlayerData( "weaponRank", weaponRef );
	colNum = int( tableLookup( "mp/weaponRankTable.csv", tableWeaponClassCol, getWeaponClass( weaponRef ), tableWeaponClassCamoCol ) );
	camoRank = int( tableLookup( "mp/weaponRankTable.csv", colNum, camoRef, tableWeaponRankCol ) );
	if( weaponRank >= camoRank )
		return true;

	return false;
}

isValidEquipment( refString )
{
	switch ( refString )
	{
		case "frag_grenade_mp":
		case "semtex_mp":
		case "throwingknife_mp":
		case "claymore_mp":
		case "c4_mp":
		case "bouncingbetty_mp":
		case "specialty_portable_radar":
			return true;
		default:
			assertMsg( "Replacing invalid equipment: " + refString );
			return false;
	}
}


isValidOffhand( refString )
{
	switch ( refString )
	{
		case "flash_grenade_mp":
		case "concussion_grenade_mp":
		case "smoke_grenade_mp":
		case "emp_grenade_mp":
		case "trophy_mp":
		case "specialty_tacticalinsertion":
		case "specialty_scrambler":
		case "specialty_portable_radar":
			return true;
		default:
			assertMsg( "Replacing invalid offhand: " + refString );
			return false;
	}
}

isValidPerk1( refString )
{
	switch ( refString )
	{
	case "specialty_longersprint":
	case "specialty_fastreload":
	case "specialty_scavenger":	
	case "specialty_blindeye":
	case "specialty_paint":
		return true;
	default:
		assertMsg( "Replacing invalid perk1: " + refString );
		return false;
	}
}

isValidPerk2( refString, perk1 )
{
	if( !IsDefined( perk1 ) || perk1 != "specialty_anytwo" )
	{
		switch ( refString )
		{
		case "specialty_hardline":
		case "specialty_coldblooded":
		case "specialty_quickdraw":
		case "specialty_twoprimaries":
		case "specialty_assists":
		case "_specialty_blastshield":
			return true;
		default:
			assertMsg( "Replacing invalid perk2: " + refString );
			return false;
		}
	}
	return true;
}

isValidPerk3( refString, perk1 )
{
	if( !IsDefined( perk1 ) || perk1 != "specialty_anytwo" )
	{
		switch ( refString )
		{
		case "specialty_detectexplosive":
		case "specialty_autospot":
		case "specialty_bulletaccuracy":
		case "specialty_quieter":
		case "specialty_stalker":
			return true;
		default:
			assertMsg( "Replacing invalid perk3: " + refString );
			return false;
		}
	}
	return true;
}

isValidDeathStreak( refString )
{
	switch ( refString )
	{
	//case "specialty_copycat":
	//case "specialty_light_armor":
	//case "specialty_carepackage":
	case "specialty_juiced":
	case "specialty_grenadepulldeath":
	case "specialty_finalstand":
	case "specialty_revenge":
	case "specialty_stopping_power":
	case "specialty_c4death":
	case "specialty_uav":
	case "specialty_null":
		return true;
	default:
		assertMsg( "Replacing invalid death streak: " + refString );
		return false;
	}
}

isValidWeapon( refString )
{
	if ( !isDefined( level.weaponRefs ) )
	{
		level.weaponRefs = [];

		foreach ( weaponRef in level.weaponList )
			level.weaponRefs[ weaponRef ] = true;
	}

	if ( isDefined( level.weaponRefs[ refString ] ) )
		return true;

	assertMsg( "Replacing invalid weapon/attachment combo: " + refString );
	
	return false;
}

isValidKillstreak( refString )
{
	switch ( refString )
	{
	case "uav":
	case "double_uav":
	case "triple_uav":
	case "ac130":
	case "precision_airstrike":
	case "predator_missile":
	case "counter_uav":
	case "sentry":
	case "airdrop_assault":
	case "airdrop_sentry_minigun":
	case "airdrop_juggernaut":
	case "helicopter_flares":
	case "emp":
	case "littlebird_flock":
	case "stealth_airstrike":
	case "airdrop_trap":
	case "minigun_turret":
	case "escort_airdrop":
	case "osprey_gunner":
	case "deployable_vest":
	case "directional_uav":
	case "heli_sniper":
	case "ims":
	case "aastrike":
	case "remote_mortar":
	case "remote_mg_turret":
	case "airdrop_juggernaut_recon":
	case "uav_support":
	case "remote_uav":
	case "remote_tank":
	case "airdrop_remote_tank":
	case "sam_turret":
	case "helicopter":
	case "littlebird_support":

	case "specialty_longersprint_ks":
	case "specialty_fastreload_ks":
	case "specialty_scavenger_ks":
	case "specialty_blindeye_ks":
	case "specialty_paint_ks":
	case "specialty_hardline_ks":
	case "specialty_coldblooded_ks":
	case "specialty_quickdraw_ks":
	case "specialty_assists_ks":
	case "_specialty_blastshield_ks":
	case "specialty_detectexplosive_ks":
	case "specialty_autospot_ks":
	case "specialty_bulletaccuracy_ks":
	case "specialty_quieter_ks":
	case "specialty_stalker_ks":

	case "none":
		return true;
	default:
		assertMsg( "Replacing invalid killstreak: " + refString );
		return false;
	}
}
