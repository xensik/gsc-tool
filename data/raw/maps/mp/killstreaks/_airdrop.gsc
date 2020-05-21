#include maps\mp\_utility;
#include common_scripts\utility;
#include maps\mp\gametypes\_hud_util;

CRATE_KILLCAM_OFFSET = ( 0, 0, 300);
GRAVITY_UNITS_PER_SECOND = 800;

init()
{
	precacheVehicle( "littlebird_mp" );
	precacheModel( "com_plasticcase_friendly" );
	precacheModel( "com_plasticcase_enemy");
	precacheModel( "com_plasticcase_trap_friendly" );
	//*precacheModel( "com_plasticcase_trap_bombsquad" );
	precacheModel( "vehicle_little_bird_armed_mp" );
	precacheModel( "vehicle_ac130_low_mp" );
	precacheModel( "sentry_minigun_folded" );
	precacheString( &"PLATFORM_GET_RANDOM" );
	precacheString( &"PLATFORM_GET_KILLSTREAK" );
	precacheString( &"PLATFORM_CALL_NUKE" );
	precacheString( &"MP_CAPTURING_CRATE" );
	precacheShader( "compassping_friendly_mp" );
	precacheShader( "compassping_enemy" );
	precacheItem( "airdrop_trap_explosive_mp" );

	precacheModel( maps\mp\gametypes\_teams::getTeamCrateModel( "allies" ) );
	precacheModel( maps\mp\gametypes\_teams::getTeamCrateModel( "axis" ) );
	
	precacheModel( "prop_suitcase_bomb" );
	
	precacheShader( maps\mp\gametypes\_teams::getTeamHudIcon( "allies" ) );	
	precacheShader( maps\mp\gametypes\_teams::getTeamHudIcon( "axis" ) );
	precacheShader( "waypoint_ammo_friendly" );
	precacheShader( "compass_objpoint_ammo_friendly" );
	precacheShader( "compass_objpoint_trap_friendly" );
	precacheShader( "compass_objpoint_ammo_enemy" );
	precacheMiniMapIcon( "compass_objpoint_c130_friendly" );
	precacheMiniMapIcon( "compass_objpoint_c130_enemy" );
	
	game["strings"]["ammo_hint"] = &"MP_AMMO_PICKUP";
	game["strings"]["explosive_ammo_hint"] = &"MP_EXPLOSIVE_AMMO_PICKUP";
	game["strings"]["uav_hint"] = &"MP_UAV_PICKUP";
	game["strings"]["counter_uav_hint"] = &"MP_COUNTER_UAV_PICKUP";
	game["strings"]["sentry_hint"] = &"MP_SENTRY_PICKUP";
	game["strings"]["juggernaut_hint"] = &"MP_JUGGERNAUT_PICKUP";
	game["strings"]["airdrop_juggernaut_hint"] = &"MP_JUGGERNAUT_PICKUP";
	game["strings"]["airdrop_juggernaut_def_hint"] = &"MP_JUGGERNAUT_PICKUP";
	game["strings"]["airdrop_juggernaut_gl_hint"] = &"MP_JUGGERNAUT_PICKUP";
	game["strings"]["airdrop_juggernaut_recon_hint"] = &"MP_JUGGERNAUT_PICKUP";
	game["strings"]["trophy_hint"] = &"MP_PICKUP_TROPHY";
	//*game["strings"]["predator_missile_hint"] = &"MP_PREDATOR_MISSILE_PICKUP";
	game["strings"]["airstrike_hint"] = &"MP_AIRSTRIKE_PICKUP";
	game["strings"]["precision_airstrike_hint"] = &"MP_PRECISION_AIRSTRIKE_PICKUP";
	game["strings"]["harrier_airstrike_hint"] = &"MP_HARRIER_AIRSTRIKE_PICKUP";
	game["strings"]["helicopter_hint"] = &"MP_HELICOPTER_PICKUP";
	game["strings"]["helicopter_flares_hint"] = &"MP_HELICOPTER_FLARES_PICKUP";
	game["strings"]["stealth_airstrike_hint"] = &"MP_STEALTH_AIRSTRIKE_PICKUP";
	game["strings"]["helicopter_minigun_hint"] = &"MP_HELICOPTER_MINIGUN_PICKUP";
	//*game["strings"]["ac130_hint"] = &"MP_AC130_PICKUP";
	game["strings"]["emp_hint"] = &"MP_EMP_PICKUP";
	game["strings"]["littlebird_support_hint"] = &"MP_LITTLEBIRD_SUPPORT_PICKUP";
	game["strings"]["littlebird_flock_hint"] = &"MP_LITTLEBIRD_FLOCK_PICKUP";
	game["strings"]["uav_strike_hint"] = &"MP_UAV_STRIKE_PICKUP";
	game["strings"]["light_armor_hint"] = &"MP_LIGHT_ARMOR_PICKUP";
	game["strings"]["minigun_turret_hint"] = &"MP_MINIGUN_TURRET_PICKUP";
	game["strings"]["team_ammo_refill_hint"] = &"MP_TEAM_AMMO_REFILL_PICKUP";
	game["strings"]["deployable_vest_hint"] = &"MP_DEPLOYABLE_VEST_PICKUP";
	game["strings"]["deployable_exp_ammo_hint"] = &"MP_DEPLOYABLE_EXP_AMMO_PICKUP";
	game["strings"]["gl_turret_hint"] = &"MP_GL_TURRET_PICKUP";
	game["strings"]["directional_uav_hint"] = &"MP_DIRECTIONAL_UAV_PICKUP";
	game["strings"]["ims_hint"] = &"MP_IMS_PICKUP";
	game["strings"]["heli_sniper_hint"] = &"MP_HELI_SNIPER_PICKUP";
	game["strings"]["heli_minigunner_hint"] = &"MP_HELI_MINIGUNNER_PICKUP";
	//*game["strings"]["remote_mortar_hint"] = &"MP_REMOTE_MORTAR_PICKUP";
	//*game["strings"]["remote_uav_hint"] = &"MP_REMOTE_UAV_PICKUP";
	game["strings"]["littlebird_support_hint"] = &"MP_LITTLEBIRD_SUPPORT_PICKUP";
	//*game["strings"]["osprey_gunner_hint"] = &"MP_OSPREY_GUNNER_PICKUP";
	game["strings"]["remote_tank_hint"] = &"MP_REMOTE_TANK_PICKUP";
	game["strings"]["triple_uav_hint"] = &"MP_TRIPLE_UAV_PICKUP";
	game["strings"]["remote_mg_turret_hint"] = &"MP_REMOTE_MG_TURRET_PICKUP";
	game["strings"]["sam_turret_hint"] = &"MP_SAM_TURRET_PICKUP";
	game["strings"]["escort_airdrop_hint"] = &"MP_ESCORT_AIRDROP_PICKUP";

	level.airDropCrates = getEntArray( "care_package", "targetname" );
	level.oldAirDropCrates = getEntArray( "airdrop_crate", "targetname" );
	
	if ( !level.airDropCrates.size )
	{	
		level.airDropCrates = level.oldAirDropCrates;
		
		assert( level.airDropCrates.size );
		
		level.airDropCrateCollision = getEnt( level.airDropCrates[0].target, "targetname" );
	}
	else
	{
		foreach ( crate in level.oldAirDropCrates ) 
			crate deleteCrate();
		
		level.airDropCrateCollision = getEnt( level.airDropCrates[0].target, "targetname" );
		level.oldAirDropCrates = getEntArray( "airdrop_crate", "targetname" );
	}
	
	if ( level.airDropCrates.size )
	{
		foreach ( crate in level.airDropCrates ) 
			crate deleteCrate();
	}
	
	level.numDropCrates = 0;	
	
	level.killStreakFuncs["airdrop_assault"] = ::tryUseAssaultAirdrop;
	level.killStreakFuncs["airdrop_support"] = ::tryUseSupportAirdrop;
	level.killStreakFuncs["airdrop_mega"] = ::tryUseMegaAirdrop;

	level.killStreakFuncs["airdrop_predator_missile"] = ::tryUseAirdropPredatorMissile;
	level.killStreakFuncs["airdrop_sentry_minigun"] = ::tryUseAirdropSentryMinigun;
	level.killStreakFuncs["airdrop_juggernaut"] = ::tryUseJuggernautAirdrop;
	level.killStreakFuncs["airdrop_juggernaut_def"] = ::tryUseJuggernautDefAirdrop;	
	level.killStreakFuncs["airdrop_juggernaut_gl"] = ::tryUseJuggernautGLAirdrop;
	level.killStreakFuncs["airdrop_juggernaut_recon"] = ::tryUseJuggernautReconAirdrop;
	level.killStreakFuncs["airdrop_trophy"] = ::tryUseTrophyAirdrop;	
	level.killStreakFuncs["airdrop_trap"] = ::tryUseAirdropTrap;	
	level.killStreakFuncs["airdrop_remote_tank"] = ::tryUseAirdropRemoteTank;	
	
	//	JDS TODO: move these two to their own file if they don't become airdrops 
	//						(prototyping without airdrop first)
	level.killStreakFuncs["ammo"] = ::tryUseAmmo;
	level.killStreakFuncs["explosive_ammo"] = ::tryUseExplosiveAmmo;
	level.killStreakFuncs["explosive_ammo_2"] = ::tryUseExplosiveAmmo;
	level.killStreakFuncs["light_armor"] = ::tryUseLightArmor;
	
	level.littleBirds = [];		// this hold the entities

	level.crateTypes = [];

	// ASSAULT
	//				Drop Type			Type						Weight  Function				
	addCrateType(	"airdrop_assault",	"uav",						10,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"ims",						20,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_assault",	"predator_missile",			20,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"sentry",					20,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"precision_airstrike",		6,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"helicopter",				4,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"littlebird_support",		4,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"littlebird_flock",			4,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_assault",	"remote_mortar",			3,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"remote_tank",				3,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"helicopter_flares",		2,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_assault",	"ac130",					2,		::killstreakCrateThink );
	addCrateType(	"airdrop_assault",	"airdrop_juggernaut",		1,		::juggernautCrateThink );
	//*addCrateType(	"airdrop_assault",	"osprey_gunner",			1,		::killstreakCrateThink );

	// OSPREY GUNNER
	addCrateType(	"airdrop_osprey_gunner",	"uav",						10,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"ims",						20,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_osprey_gunner",	"predator_missile",			20,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"sentry",					20,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"precision_airstrike",		8,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"littlebird_flock",			8,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_osprey_gunner",	"remote_mortar",			5,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"remote_tank",				2,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"helicopter_flares",		2,		::killstreakCrateThink );
	addCrateType(	"airdrop_osprey_gunner",	"airdrop_juggernaut",		1,		::juggernautCrateThink );
	//*addCrateType(	"airdrop_osprey_gunner",	"ac130",					1,		::killstreakCrateThink );

	// SUPPORT
	addCrateType(	"airdrop_support",	"uav",						9,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"counter_uav",				9,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"deployable_vest",			8,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"sam_turret",				6,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_support",	"remote_uav",				5,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"remote_mg_turret",			5,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"stealth_airstrike",		4,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"triple_uav",				3,		::killstreakCrateThink );
	addCrateType(	"airdrop_support",	"airdrop_juggernaut_recon",	2,		::juggernautCrateThink );
	addCrateType(	"airdrop_support",	"escort_airdrop",			1,		::killstreakCrateThink );	
	addCrateType(	"airdrop_support",	"emp",						1,		::killstreakCrateThink );

	// ESCORT AIRDROP
	addCrateType(	"airdrop_escort",	"airdrop_trap",				10,		::trapCrateThink );
	addCrateType(	"airdrop_escort",	"uav",						8,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"counter_uav",				8,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"deployable_vest",			7,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"sentry",					7,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"ims",						7,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"sam_turret",				6,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"stealth_airstrike",		5,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"airdrop_juggernaut_recon",	5,		::juggernautCrateThink );
	//*addCrateType(	"airdrop_escort",	"remote_uav",				5,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"triple_uav",				3,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"remote_mg_turret",			3,		::killstreakCrateThink );
	addCrateType(	"airdrop_escort",	"emp",						1,		::killstreakCrateThink );
	
	//	TRAP CONTENTS
	addCrateType(	"airdrop_trapcontents",	"ims",					6,		::trapNullFunc );
	//*addCrateType(	"airdrop_trapcontents",	"predator_missile",		7,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"sentry",				7,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"precision_airstrike",	7,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"helicopter",			8,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"littlebird_support",	8,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"littlebird_flock",		8,		::trapNullFunc );	
	//*addCrateType(	"airdrop_trapcontents",	"remote_mortar",		9,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"remote_tank",			9,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"helicopter_flares",	10,		::trapNullFunc );
	//*addCrateType(	"airdrop_trapcontents",	"ac130",				10,		::trapNullFunc );
	addCrateType(	"airdrop_trapcontents",	"airdrop_juggernaut",	10,		::trapNullFunc );
	//*addCrateType(	"airdrop_trapcontents",	"osprey_gunner",		10,		::trapNullFunc );	

	// GRINDER DROP			
	addCrateType(	"airdrop_grnd",	"uav",						25,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"counter_uav",				25,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"deployable_vest",			21,		::killstreakCrateThink );	
	addCrateType(	"airdrop_grnd",	"sentry",					21,		::killstreakCrateThink );	
	addCrateType(	"airdrop_grnd",	"remote_mg_turret",			17,		::killstreakCrateThink );		
	addCrateType(	"airdrop_grnd",	"ims",						17,		::killstreakCrateThink );		
	addCrateType(	"airdrop_grnd",	"triple_uav",				13,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_grnd",	"predator_missile",			13,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"airdrop_trap",				11,		::trapCrateThink );	
	addCrateType(	"airdrop_grnd",	"precision_airstrike",		9,		::killstreakCrateThink );	
	addCrateType(	"airdrop_grnd",	"stealth_airstrike",		9,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"helicopter",				9,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"remote_tank",				7,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"sam_turret",				7,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_grnd",	"remote_uav",				7,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"littlebird_support",		4,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"airdrop_juggernaut_recon",	4,		::juggernautCrateThink );
	addCrateType(	"airdrop_grnd",	"littlebird_flock",			2,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"helicopter_flares",		2,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_grnd",	"remote_mortar",			2,		::killstreakCrateThink );
	//*addCrateType(	"airdrop_grnd",	"ac130",					2,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"airdrop_juggernaut",		1,		::juggernautCrateThink );		
	//*addCrateType(	"airdrop_grnd",	"osprey_gunner",			1,		::killstreakCrateThink );
	addCrateType(	"airdrop_grnd",	"emp",						1,		::killstreakCrateThink );

	//			  Drop Type						Type						Weight	Function					
	addCrateType( "airdrop_sentry_minigun",		"sentry",					100,	::killstreakCrateThink );
	addCrateType( "airdrop_juggernaut",			"airdrop_juggernaut",		100,	::juggernautCrateThink );
	addCrateType( "airdrop_juggernaut_recon",	"airdrop_juggernaut_recon",	100,	::juggernautCrateThink );
	addCrateType( "airdrop_trophy",				"airdrop_trophy",			100,	::trophyCrateThink );
	addCrateType( "airdrop_trap",				"airdrop_trap",				100,	::trapCrateThink );	
	addCrateType( "littlebird_support",			"littlebird_support",		100,	::killstreakCrateThink );
	addCrateType( "airdrop_remote_tank",		"remote_tank"		,		100,	::killstreakCrateThink );

	
	// generate the max weighted value
	foreach( dropType, crateTypes in level.crateTypes )
	{
		level.crateMaxVal[dropType] = 0;	
		foreach( crateType, crateWeight in level.crateTypes[dropType] )
		{
			if ( !crateWeight )
				continue;

			level.crateMaxVal[dropType] += crateWeight;
			level.crateTypes[dropType][crateType] = level.crateMaxVal[dropType];
		}
	}
	
	tdmSpawns = getEntArray( "mp_tdm_spawn" , "classname" );
	lowSpawn = undefined;
	
	foreach ( lspawn in tdmSpawns )
	{
		if ( !isDefined( lowSpawn ) || lspawn.origin[2] < lowSpawn.origin[2] )
		{
			lowSpawn = lspawn;
		}
	}
	level.lowSpawn = lowSpawn;

/#
	SetDevDvarIfUninitialized( "scr_crateOverride", "" );
	SetDevDvarIfUninitialized( "scr_crateTypeOverride", "" );
#/
}

addCrateType( dropType, crateType, crateWeight, crateFunc )
{
	level.crateTypes[dropType][crateType] = crateWeight;
	level.crateFuncs[dropType][crateType] = crateFunc;
}


getRandomCrateType( dropType )
{
	value = randomInt( level.crateMaxVal[dropType] );
	
	if ( isDefined( self.owner) && self.owner _hasPerk("specialty_luckycharm") )
		charmed = true;
	else
		charmed = false;

	selectedCrateType = undefined;
	foreach( crateType, crateWeight in level.crateTypes[dropType] )
	{
		if ( !crateWeight )
			continue;

		selectedCrateType = crateType;

		if ( crateWeight > value )
		{
			if ( charmed )
			{
				charmed = false;
				continue;
			}
			break;
		}
	}
	
	return( selectedCrateType );
}


getCrateTypeForDropType( dropType )
{
	switch	( dropType )
	{
		case "airdrop_sentry_minigun":
			return "sentry";
		case "airdrop_predator_missile":
			return "predator_missile";
		case "airdrop_juggernaut":
			return "airdrop_juggernaut";
		case "airdrop_juggernaut_def":
			return "airdrop_juggernaut_def";
		case "airdrop_juggernaut_gl":
			return "airdrop_juggernaut_gl";
		case "airdrop_juggernaut_recon":
			return "airdrop_juggernaut_recon";
		case "airdrop_trap":
			return "airdrop_trap";
		case "airdrop_trophy":
			return "airdrop_trophy";
		case "airdrop_remote_tank":
			return "remote_tank";
		case "airdrop_assault":
		case "airdrop_support":
		case "airdrop_escort":
		case "airdrop_mega":
		case "airdrop_grnd":
		case "airdrop_grnd_mega":
		default:
			return getRandomCrateType( dropType );
	}
}


/**********************************************************
*		 Helper/Debug functions
***********************************************************/

drawLine( start, end, timeSlice )
{
	drawTime = int(timeSlice * 15);
	for( time = 0; time < drawTime; time++ )
	{
		line( start, end, (1,0,0),false, 1 );
		wait ( 0.05 );
	}
}

/**********************************************************
*		 Usage functions
***********************************************************/

tryUseAssaultAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop(  lifeId, kID, "airdrop_assault" ) );
}

tryUseSupportAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop(  lifeId, kID, "airdrop_support" ) );
}

tryUseAirdropPredatorMissile( lifeId, kID )
{
	return ( self tryUseAirdrop(  lifeId, kID, "airdrop_predator_missile" ) );
}

tryUseAirdropSentryMinigun(  lifeId, kID )
{
	return ( self tryUseAirdrop(  lifeId, kID, "airdrop_sentry_minigun" ) );
}

tryUseJuggernautAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_juggernaut" ) );
}

tryUseJuggernautGLAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_juggernaut_gl" ) );
}

tryUseJuggernautReconAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_juggernaut_recon" ) );
}

tryUseJuggernautDefAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_juggernaut_def" ) );
}

tryUseTrophyAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_trophy" ) );
}

tryUseMegaAirdrop( lifeId, kID )
{
	return ( self tryUseAirdrop(  lifeId, kID, "airdrop_mega" ) );
}

tryUseAirdropTrap( lifeId, kID )
{
	if ( self tryUseAirdrop(  lifeId, kID, "airdrop_trap" ) )
	{
		if ( level.teamBased )
		{
			thread leaderDialog( level.otherTeam[ self.team ] + "_enemy_airdrop_assault_inbound", level.otherTeam[ self.team ] );
		}
		else
		{
			excludeList[0] = self;
			thread leaderDialog( level.otherTeam[ self.team ] + "_enemy_airdrop_assault_inbound", undefined, undefined, excludeList );
		}	
		return true;	
	}
	else
		return false;
}

tryUseAirdropRemoteTank( lifeId, kID )
{
	return ( self tryUseAirdrop( lifeId, kID, "airdrop_remote_tank" ) );
}

tryUseAmmo( lifeId )
{
	if ( self isJuggernaut() )
		return false;
	else
	{
		self refillAmmo( true );
		return true;
	}
}

tryUseExplosiveAmmo( lifeId )
{
	if ( self isJuggernaut() )
		return false;
	else
	{
		self refillAmmo( false );
		self givePerk( "specialty_explosivebullets", false );
		return true;
	}
}

tryUseLightArmor( lifeId )
{
	if ( self isJuggernaut() )
		return false;
	else
	{
		self thread maps\mp\perks\_perkfunctions::giveLightArmor();
		return true;	
	}
}

tryUseAirdrop( lifeId, kID, dropType )
{
	result = undefined;
	
	if ( !isDefined( dropType ) )
		dropType = "airdrop_assault";

	//if ( !isDefined( self.pers["kIDs_valid"][kID] ) )
	//	return true;
		
	numIncomingVehicles = 1;
	if( ( level.littleBirds.size >= 4 || level.fauxVehicleCount >= 4 ) && dropType != "airdrop_mega" && !isSubStr( toLower( dropType ), "juggernaut" ) )
	{
		self iPrintLnBold( &"MP_AIR_SPACE_TOO_CROWDED" );
		return false;
	} 
	else if( currentActiveVehicleCount() >= maxVehiclesAllowed() || level.fauxVehicleCount + numIncomingVehicles >= maxVehiclesAllowed() )
	{
		self iPrintLnBold( &"MP_TOO_MANY_VEHICLES" );
		return false;
	}		
	else if( isDefined( level.civilianJetFlyBy ) )
	{
		self iPrintLnBold( &"MP_CIVILIAN_AIR_TRAFFIC" );
		return false;
	}
	else if( self isUsingRemote() )
	{
		return false;
	}
	else if( !self validateUseStreak() )
	{
		return false;
	}
	
	if ( dropType != "airdrop_mega" && !isSubStr( toLower( dropType ), "juggernaut" ) )
	{
		self thread watchDisconnect();
	}
	
	// increment the faux vehicle count before we spawn the vehicle so no other vehicles try to spawn
	incrementFauxVehicleCount();

/#
	// let bots use the full functionality of the killstreak usage	
	if( IsDefined( self.pers[ "isBot" ] ) && self.pers[ "isBot" ] )
		return true;
#/

	result = self beginAirdropViaMarker( lifeId, kID, dropType );
	
	if ( (!isDefined( result ) || !result) /*&& isDefined( self.pers["kIDs_valid"][kID] )*/ )
	{
		self notify( "markerDetermined" );

		// decrement the faux vehicle count since this failed to spawn
		decrementFauxVehicleCount();

		return false;
	}
	
	if ( dropType == "airdrop_mega" )
		thread teamPlayerCardSplash( "used_airdrop_mega", self );
	
	self notify( "markerDetermined" );
	
	self maps\mp\_matchdata::logKillstreakEvent( dropType, self.origin );	
	
	return true;
}

watchDisconnect()
{
	self endon( "markerDetermined" );
	
	self waittill( "disconnect" );
	return;
}


/**********************************************************
*		 Marker functions
***********************************************************/

beginAirdropViaMarker( lifeId, kID, dropType )
{	
	self notify( "beginAirdropViaMarker" );
	self endon( "beginAirdropViaMarker" );

	self endon( "disconnect" );
	level endon( "game_ended" );

	// reworked this to thread all of the functions at once and then watch for what returns
	// this fixes an infinite care package bug where you can kill the player as they throw it and they'll respawn with another one
	self.threwAirDropMarker = undefined;
	self thread watchAirDropWeaponChange( lifeId, kID, dropType );
	self thread watchAirDropMarkerUsage( lifeId, kID, dropType );
	self thread watchAirDropMarker( lifeId, kID, dropType );

	result = self waittill_any_return( "notAirDropWeapon", "markerDetermined" );
	if( IsDefined( result ) && result == "markerDetermined" )
		return true;
	// result comes back as undefined if the player is killed while throwing, so we need to check to see if they threw the marker before dying
	else if( !IsDefined( result ) && IsDefined( self.threwAirDropMarker ) )
		return true;

	return false;
}

watchAirDropWeaponChange( lifeId, kID, dropType )
{
	self notify( "watchAirDropWeaponChange" );
	self endon( "watchAirDropWeaponChange" );
	
	self endon( "disconnect" );
	self endon( "markerDetermined" );

	while( self isChangingWeapon() )
		wait ( 0.05 );	

	currentWeapon = self getCurrentWeapon();

	if ( isAirdropMarker( currentWeapon ) )
		airdropMarkerWeapon = currentWeapon;
	else
		airdropMarkerWeapon = undefined;

	while( isAirdropMarker( currentWeapon ) /*|| currentWeapon == "none"*/ )
	{
		self waittill( "weapon_change", currentWeapon );

		if ( isAirdropMarker( currentWeapon ) )
			airdropMarkerWeapon = currentWeapon;
	}

	if( IsDefined( self.threwAirDropMarker ) )
	{
		// need to take the killstreak weapon here because the weapon_change happens before it can be taken in _killstreaks::waitTakeKillstreakWeapon()
		killstreakWeapon = maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreaks"][self.killstreakIndexWeapon].streakName );
		self TakeWeapon( killstreakWeapon );

		self notify( "markerDetermined" );
	}
	else
		self notify( "notAirDropWeapon" );
}

watchAirDropMarkerUsage( lifeId, kID, dropType )
{
	self notify( "watchAirDropMarkerUsage" );
	self endon( "watchAirDropMarkerUsage" );

	self endon( "disconnect" );
	self endon( "markerDetermined" );
	
	while( true )
	{
		self waittill( "grenade_pullback", weaponName );

		// could've thrown a grenade while holding the airdrop weapon
		if( !isAirdropMarker( weaponName ) )
			continue;

		self _disableUsability();

		self beginAirDropMarkerTracking();
	}
}

watchAirDropMarker( lifeId, kID, dropType )
{
	self notify( "watchAirDropMarker" );
	self endon( "watchAirDropMarker" );

	self endon( "disconnect" );
	self endon( "markerDetermined" );

	while( true )
	{
		self waittill( "grenade_fire", airDropWeapon, weapname );
		
		if ( !isAirdropMarker( weapname ) )
			continue;
		
		//if( !IsAlive( self ) )
		//{
		//	airDropWeapon delete();
		//	return;
		//}
	
		//if ( !isDefined( self.pers["kIDs_valid"][kID] ) )
		//{
		//	airDropWeapon delete();
		//	continue;
		//}
			
		//self.pers["kIDs_valid"][kID] = undefined;

		self.threwAirDropMarker = true;
		airDropWeapon thread airdropDetonateOnStuck();
			
		airDropWeapon.owner = self;
		airDropWeapon.weaponName = weapname;
		
		airDropWeapon thread airDropMarkerActivate( dropType );		
	}
}

beginAirDropMarkerTracking()
{
	self notify( "beginAirDropMarkerTracking" );
	self endon( "beginAirDropMarkerTracking" );

	self endon( "death" );
	self endon( "disconnect" );

	self waittill_any( "grenade_fire", "weapon_change" );
	self _enableUsability();
}

airDropMarkerActivate( dropType, lifeId )
{	
	self notify( "airDropMarkerActivate" );
	self endon( "airDropMarkerActivate" );

	self waittill( "explode", position );

	owner = self.owner;

	if ( !isDefined( owner ) )
		return;
	
	if ( owner isEMPed() )
		return;
		
	if ( owner isAirDenied() )
		return;
	
	if( IsSubStr( toLower( dropType ), "escort_airdrop" ) && isDefined( level.chopper ) )
		return;

	// play an additional smoke fx that is longer than the normal for the escort airdrop
	if( IsSubStr( toLower( dropType ), "escort_airdrop" ) && IsDefined( level.chopper_fx["smoke"]["signal_smoke_30sec"] ) )
	{
		PlayFX( level.chopper_fx["smoke"]["signal_smoke_30sec"], position, ( 0, 0, -1 ) );
	}

	wait 0.05;
	
	if ( IsSubStr( toLower( dropType ), "juggernaut" ) )
		level doC130FlyBy( owner, position, randomFloat( 360 ), dropType );
	else if ( IsSubStr( toLower( dropType ), "escort_airdrop" ) )
		owner maps\mp\killstreaks\_escortairdrop::finishSupportEscortUsage( lifeId, position, randomFloat( 360 ), "escort_airdrop" );
	else
		level doFlyBy( owner, position, randomFloat( 360 ), dropType );
}

/**********************************************************
*		 crate functions
***********************************************************/
initAirDropCrate()
{
	self.inUse = false;
	self hide();

	if ( isDefined( self.target ) )
	{
		self.collision = getEnt( self.target, "targetname" );
		self.collision notSolid();
	}
	else
	{
		self.collision = undefined;
	}
}


deleteOnOwnerDeath( owner )
{
	wait ( 0.25 );
	self linkTo( owner, "tag_origin", (0,0,0), (0,0,0) );

	owner waittill ( "death" );
	
	self delete();
}


crateTeamModelUpdater() // self == crate team model (the logo)
{
	self endon ( "death" );

	for ( ;; )
	{
		level waittill ( "joined_team" );
		
		self hide();
		foreach ( player in level.players )
		{
			if ( player.team != "spectator" )
				self ShowToPlayer( player );
		}
	}	
}


crateModelTeamUpdater( showForTeam ) // self == crate model (friendly or enemy)
{
	self endon ( "death" );

	self hide();

	foreach ( player in level.players )
	{
		if( player.team == showForTeam )
			self ShowToPlayer( player );
	}

	for ( ;; )
	{
		level waittill ( "joined_team" );
		
		self hide();
		foreach ( player in level.players )
		{
			if ( player.team == showForTeam )
				self ShowToPlayer( player );
		}
	}	
}

// for FFA
crateModelPlayerUpdater( owner, friendly ) // self == crate model (friendly or enemy)
{
	self endon ( "death" );

	self hide();

	foreach ( player in level.players )
	{
		if( friendly && IsDefined( owner ) && player != owner )
			continue;
		if( !friendly && IsDefined( owner ) && player == owner )
			continue;

		self ShowToPlayer( player );
	}

	for ( ;; )
	{
		level waittill ( "joined_team" );

		self hide();
		foreach ( player in level.players )
		{
			if( friendly && IsDefined( owner ) && player != owner )
				continue;
			if( !friendly && IsDefined( owner ) && player == owner )
				continue;

			self ShowToPlayer( player );
		}
	}	
}

crateUseTeamUpdater( team )
{
	self endon ( "death" );

	for ( ;; )
	{
		setUsableByTeam( team );

		level waittill ( "joined_team" );
		
	}	
}

crateUseJuggernautUpdater()
{
	if ( !isSubStr( self.crateType, "juggernaut" ) )
		return;
	
	self endon( "death" );
	level endon( "game_ended" );
	
	for ( ;; )
	{
		level waittill ( "juggernaut_equipped", player );
		
		self disablePlayerUse( player );
		self thread crateUsePostJuggernautUpdater( player );
	}	
}

crateUsePostJuggernautUpdater( player )
{
	self endon( "death" );
	level endon( "game_ended" );
	player endon( "disconnect" );
	
	player waittill( "death" );
	self enablePlayerUse( player );	
}

createAirDropCrate( owner, dropType, crateType, startPos )
{
	dropCrate = spawn( "script_model", startPos );
	
	dropCrate.curProgress = 0;
	dropCrate.useTime = 0;
	dropCrate.useRate = 0;
	dropCrate.team = self.team;
	
	if ( isDefined( owner ) )
		dropCrate.owner = owner;
	else
		dropCrate.owner = undefined;
	
	dropCrate.crateType = crateType;
	dropCrate.dropType = dropType;
	dropCrate.targetname = "care_package";
	
	dropCrate setModel( maps\mp\gametypes\_teams::getTeamCrateModel( dropCrate.team ) );	
	dropCrate thread crateTeamModelUpdater();	

	modelName = "com_plasticcase_friendly";
	if( crateType == "airdrop_trap" )
	{
		modelName = "com_plasticcase_trap_friendly";
		dropCrate thread trap_createBombSquadModel();
	}
	dropCrate.friendlyModel = spawn( "script_model", startPos );
	dropCrate.friendlyModel setModel( modelName );
	dropCrate.enemyModel = spawn( "script_model", startPos );
	dropCrate.enemyModel setModel( "com_plasticcase_enemy" );

	dropCrate.friendlyModel thread deleteOnOwnerDeath( dropCrate );
	if( level.teambased )
		dropCrate.friendlyModel thread crateModelTeamUpdater( dropCrate.team );
	else
		dropCrate.friendlyModel thread crateModelPlayerUpdater( owner, true );

	dropCrate.enemyModel thread deleteOnOwnerDeath( dropCrate );
	if( level.teambased )
		dropCrate.enemyModel thread crateModelTeamUpdater( level.otherTeam[dropCrate.team] );
	else
		dropCrate.enemyModel thread crateModelPlayerUpdater( owner, false );

	dropCrate.inUse = false;
	
	dropCrate CloneBrushmodelToScriptmodel( level.airDropCrateCollision );
	
	dropCrate.killCamEnt = Spawn( "script_model", dropCrate.origin + CRATE_KILLCAM_OFFSET );
	dropCrate.killCamEnt LinkTo( dropCrate );

	level.numDropCrates++;
	dropCrate thread dropCrateExistence();

	return dropCrate;
}

dropCrateExistence()
{
	level endon( "game_ended" );
	
	self waittill( "death" );
	
	level.numDropCrates--;
}

trap_createBombSquadModel() // self == crate
{
	bombSquadModel = spawn( "script_model", self.origin );
	bombSquadModel.angles = self.angles;
	bombSquadModel hide();

	team = level.otherTeam[ self.team ];
	bombSquadModel thread maps\mp\gametypes\_weapons::bombSquadVisibilityUpdater( team, self.owner );
	bombSquadModel setModel( "com_plasticcase_trap_friendly" );
	bombSquadModel setSwitchToObjective( 1 );
	bombSquadModel linkTo( self );
	bombSquadModel SetContents( 0 );

	self waittill ( "death" );

	bombSquadModel delete();
}

crateSetupForUse( hintString, mode, icon )
{	
	self setCursorHint( "HINT_NOICON" );
	self setHintString( hintString );
	self makeUsable();
	self.mode = mode;

	if ( level.teamBased || IsDefined( self.owner ) )
	{
		curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
		objective_add( curObjID, "invisible", (0,0,0) );
		objective_position( curObjID, self.origin );
		objective_state( curObjID, "active" );
		
		shaderName = "compass_objpoint_ammo_friendly";
		if( mode == "trap" )
			shaderName = "compass_objpoint_trap_friendly";
		objective_icon( curObjID, shaderName );
		
		if ( !level.teamBased && IsDefined( self.owner ) )
			Objective_PlayerTeam( curObjId, self.owner GetEntityNumber() );
		else
			Objective_Team( curObjID, self.team );
		
		self.objIdFriendly = curObjID;
	}

	curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
	objective_add( curObjID, "invisible", (0,0,0) );
	objective_position( curObjID, self.origin );
	objective_state( curObjID, "active" );
	objective_icon( curObjID, "compass_objpoint_ammo_enemy" );

	if ( !level.teamBased && IsDefined( self.owner ) )
		Objective_PlayerEnemyTeam( curObjId, self.owner GetEntityNumber() );
	else
		Objective_Team( curObjID, level.otherTeam[self.team] );

	self.objIdEnemy = curObjID;

	if ( mode == "trap" )
	{	
		self thread crateUseTeamUpdater( getOtherTeam( self.team ) );
	}
	else
	{
		self thread crateUseTeamUpdater();	
		
		if ( isSubStr( self.crateType, "juggernaut" ) )
		{
			foreach ( player in level.players )
				if ( player isJuggernaut() )
					self thread crateUsePostJuggernautUpdater( player );
		}		

		if ( level.teamBased )
			self maps\mp\_entityheadIcons::setHeadIcon( self.team, icon, (0,0,24), 14, 14, undefined, undefined, undefined, undefined, undefined, false );
		else if ( IsDefined( self.owner ) )
			self maps\mp\_entityheadIcons::setHeadIcon( self.owner, icon, (0,0,24), 14, 14, undefined, undefined, undefined, undefined, undefined, false );
	}
	
	self thread crateUseJuggernautUpdater();
}

setUsableByTeam( team )
{
	foreach ( player in level.players )
	{
		if ( isSubStr( self.crateType, "juggernaut" ) && player isJuggernaut() )
		{
			self DisablePlayerUse( player );
		}
		else if ( !level.teamBased && self.mode == "trap" )
		{
			if ( IsDefined( self.owner ) && player == self.owner )
				self DisablePlayerUse( player );
			else
				self EnablePlayerUse( player );
		}
		else if ( !IsDefined( team ) || team == player.team )
			self EnablePlayerUse( player );
		else
			self DisablePlayerUse( player );
	}	
}


dropTheCrate( dropPoint, dropType, lbHeight, dropImmediately, crateOverride, startPos, dropImpulse, previousCrateTypes, tagName )
{
	dropCrate = [];
	self.owner endon ( "disconnect" );
	
	if ( !isDefined( crateOverride ) )
	{
		//	verify emergency airdrops don't drop dupes
		if ( isDefined( previousCrateTypes ) )
		{
			foundDupe = undefined;
			crateType = undefined;
			for ( i=0; i<100; i++ )
			{
				crateType = getCrateTypeForDropType( dropType );
				foundDupe = false;
				for ( j=0; j<previousCrateTypes.size; j++ )
				{
					if ( crateType == previousCrateTypes[j] )
					{
						foundDupe = true;
						break;
					}
				}
				if ( foundDupe == false )
					break;
			}
			//	if 100 attempts fail, just get whatever, we tried		
			if ( foundDupe == true )
			{
				crateType = getCrateTypeForDropType( dropType );
			}
		}
		else
			crateType = getCrateTypeForDropType( dropType );	
	}	
	else
		crateType = crateOverride;
		
	if ( !isDefined( dropImpulse ) )
		dropImpulse = (randomInt(5),randomInt(5),randomInt(5));
		
	dropCrate = createAirDropCrate( self.owner, dropType, crateType, startPos );
	
	switch( dropType )
	{
	case "airdrop_mega":
	case "nuke_drop":
	case "airdrop_juggernaut":
	case "airdrop_juggernaut_recon":
		dropCrate LinkTo( self, "tag_ground" , (64,32,-128) , (0,0,0) );
		break;
	case "airdrop_escort":
	case "airdrop_osprey_gunner":
		dropCrate LinkTo( self, tagName, (0,0,0), (0,0,0) );
		break;
	default:
		dropCrate LinkTo( self, "tag_ground" , (32,0,5) , (0,0,0) );
		break;
	}

	dropCrate.angles = (0,0,0);
	dropCrate show();
	dropSpeed = self.veh_speed;
	
	self thread waitForDropCrateMsg( dropCrate, dropImpulse, dropType, crateType );
	
	return crateType;
}


waitForDropCrateMsg( dropCrate, dropImpulse, dropType, crateType )
{
	self waittill ( "drop_crate" );
	
	dropCrate Unlink();
	dropCrate PhysicsLaunchServer( (0,0,0), dropImpulse );		
	dropCrate thread physicsWaiter( dropType, crateType );

	if( IsDefined( dropCrate.killCamEnt ) )
	{
		// calculate the time it takes to get from here to the ground
		dropCrate.killCamEnt Unlink();
		groundTrace = BulletTrace( dropCrate.origin, dropCrate.origin + ( 0, 0, -10000 ), false, dropCrate );
		travelDistance = Distance( dropCrate.origin, groundTrace[ "position" ] );
		//travelDistance *= 2;
		travelTime = travelDistance / GRAVITY_UNITS_PER_SECOND;
		//travleTime = sqrt( travelTime );
		dropCrate.killCamEnt MoveTo( groundTrace[ "position" ] + CRATE_KILLCAM_OFFSET, travelTime );
		//dropCrate.killCamEnt MoveGravity( ( 0, 0, -1 ), travelTime );
	}
}	

physicsWaiter( dropType, crateType )
{
	self waittill( "physics_finished" );

	self thread [[ level.crateFuncs[ dropType ][ crateType ] ]]( dropType );
	level thread dropTimeOut( self, self.owner, crateType );
		
	if ( abs(self.origin[2] - level.lowSpawn.origin[2]) > 3000 )
	{
		self deleteCrate();	
	}	
}


//deletes if crate wasnt used after 90 seconds
dropTimeOut( dropCrate, owner, crateType )
{
	level endon ( "game_ended" );
	dropCrate endon( "death" );
	
	if ( dropCrate.dropType == "nuke_drop" )
		return;	
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 90.0 );
	
	while ( dropCrate.curProgress != 0 )
		wait 1;
	
	dropCrate deleteCrate();
}


getPathStart( coord, yaw )
{
	pathRandomness = 100;
	lbHalfDistance = 15000;

	direction = (0,yaw,0);

	startPoint = coord + ( AnglesToForward( direction ) * ( -1 * lbHalfDistance ) );
	startPoint += ( (randomfloat(2) - 1)*pathRandomness, (randomfloat(2) - 1)*pathRandomness, 0 );
	
	return startPoint;
}


getPathEnd( coord, yaw )
{
	pathRandomness = 150;
	lbHalfDistance = 15000;

	direction = (0,yaw,0);

	endPoint = coord + ( AnglesToForward( direction + ( 0, 90, 0 ) ) * lbHalfDistance );
	endPoint += ( (randomfloat(2) - 1)*pathRandomness  , (randomfloat(2) - 1)*pathRandomness  , 0 );
	
	return endPoint;
}


getFlyHeightOffset( dropSite )
{
	lbFlyHeight = 850;
	
	heightEnt = GetEnt( "airstrikeheight", "targetname" );
	
	if ( !isDefined( heightEnt ) )//old system 
	{
		/#
		println( "NO DEFINED AIRSTRIKE HEIGHT SCRIPT_ORIGIN IN LEVEL" );
		#/
		if ( isDefined( level.airstrikeHeightScale ) )
		{	
			if ( level.airstrikeHeightScale > 2 )
			{
				lbFlyHeight = 1500;
				return( lbFlyHeight * (level.airStrikeHeightScale ) );
			}
			
			return( lbFlyHeight * level.airStrikeHeightScale + 256 + dropSite[2] );
		}
		else
			return ( lbFlyHeight + dropsite[2] );	
	}
	else
	{
		return heightEnt.origin[2];
	}
	
}


/**********************************************************
*		 Helicopter Functions
***********************************************************/

doFlyBy( owner, dropSite, dropYaw, dropType, heightAdjustment, crateOverride )
{	
	if ( !isDefined( owner ) ) 
		return;
		
	flyHeight = self getFlyHeightOffset( dropSite );
	if ( isDefined( heightAdjustment ) )
		flyHeight += heightAdjustment;	
	foreach( littlebird in level.littlebirds )
	{
		if ( isDefined( littlebird.dropType ) )
			flyHeight += 128;
	}

	pathGoal = dropSite * (1,1,0) +  (0,0,flyHeight);	
	pathStart = getPathStart( pathGoal, dropYaw );
	pathEnd = getPathEnd( pathGoal, dropYaw );		
	
	pathGoal = pathGoal + ( AnglesToForward( ( 0, dropYaw, 0 ) ) * -50 );

	chopper = heliSetup( owner, pathStart, pathGoal );
	assert ( isDefined( chopper ) );
	
	chopper endon( "death" );
	
	if ( !isDefined( crateOverride ) )
		crateOverride = undefined;		

/#
	if( GetDvar( "scr_crateOverride" ) != "" )
	{
		crateOverride = GetDvar( "scr_crateOverride" );
		dropType = GetDvar( "scr_crateTypeOverride" );
	}
#/

	chopper.dropType = dropType;
	
	chopper setVehGoalPos( pathGoal, 1 );
		
	chopper thread dropTheCrate( dropSite, dropType, flyHeight, false, crateOverride, pathStart );
	
	wait ( 2 );
	
	chopper Vehicle_SetSpeed( 75, 40 );
	chopper SetYawSpeed( 180, 180, 180, .3 );
	
	chopper waittill ( "goal" );
	wait( .10 );
	chopper notify( "drop_crate" );
	chopper setvehgoalpos( pathEnd, 1 );
	chopper Vehicle_SetSpeed( 300, 75 );
	chopper.leaving = true;
	chopper waittill ( "goal" );
	chopper notify( "leaving" );
	chopper notify( "delete" );
	chopper delete();
}

doMegaFlyBy( owner, dropSite, dropYaw, dropType )
{
	level thread doFlyBy( owner, dropSite, dropYaw, dropType, 0 );
	wait( RandomIntRange( 1,2 ) );
	level thread doFlyBy( owner, dropSite + (128,128,0), dropYaw, dropType, 128 );
	wait( RandomIntRange( 1,2 ) );
	level thread doFlyBy( owner, dropSite + (172,256,0), dropYaw, dropType, 256 );
	wait( RandomIntRange( 1,2 ) );
	level thread doFlyBy( owner, dropSite + (64,0,0), dropYaw, dropType, 0 );
}

doC130FlyBy( owner, dropSite, dropYaw, dropType )
{	
	planeHalfDistance = 18000;
	planeFlySpeed = 3000;
	yaw = vectorToYaw( dropsite - owner.origin );
	
	direction = ( 0, yaw, 0 );
	
	flyHeight = self getFlyHeightOffset( dropSite );
	
	pathStart = dropSite + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	pathStart = pathStart * ( 1, 1, 0 ) + ( 0, 0, flyHeight );

	pathEnd = dropSite + ( AnglesToForward( direction ) * planeHalfDistance );
	pathEnd = pathEnd * ( 1, 1, 0 ) + ( 0, 0, flyHeight );
	
	d = length( pathStart - pathEnd );
	flyTime = ( d / planeFlySpeed );
	
	c130 = c130Setup( owner, pathStart, pathEnd );
	c130.veh_speed = planeFlySpeed;
	c130.dropType = dropType;
 	c130 playloopsound( "veh_ac130_dist_loop" );

	c130.angles = direction;
	forward = anglesToForward( direction );
	c130 moveTo( pathEnd, flyTime, 0, 0 ); 
	
	minDist = distance2D( c130.origin, dropSite );
	boomPlayed = false;
	
	for(;;)
	{
		dist = distance2D( c130.origin, dropSite );
		
		// handle missing our target
		if ( dist < minDist )
			minDist = dist;
		else if ( dist > minDist )
			break;
		
		if ( dist < 420 )
		{
			break;
		}
		else if ( dist < 768 )
		{
			earthquake( 0.15, 1.5, dropSite, 1500 );
			if ( !boomPlayed )
			{
				c130 playSound( "veh_ac130_sonic_boom" );
				//c130 thread stopLoopAfter( 0.5 );
				boomPlayed = true;
			}
		}	
		
		wait ( .05 );	
	}	
	wait( 0.05 );
	
	dropImpulse = (0.25,0,0);
	crateType[0] = c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, undefined, pathStart, dropImpulse );	
	wait ( 0.05 );
	c130 notify ( "drop_crate" );

	newPathEnd = dropSite + ( AnglesToForward( direction ) * (planeHalfDistance*1.5) );
	c130 moveTo( newPathEnd, flyTime/2, 0, 0 ); 

	wait ( 6 );
	c130 delete();
}


doMegaC130FlyBy( owner, dropSite, dropYaw, dropType, forwardOffset )
{	
	planeHalfDistance = 24000;
	planeFlySpeed = 2000;
	yaw = vectorToYaw( dropsite - owner.origin );
	direction = ( 0, yaw, 0 );
	forward = anglesToForward( direction );
	
	if ( isDefined( forwardOffset ) )
		dropSite = dropSite + forward * forwardOffset;	
	
	flyHeight = self getFlyHeightOffset( dropSite );
	
	pathStart = dropSite + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	pathStart = pathStart * ( 1, 1, 0 ) + ( 0, 0, flyHeight );

	pathEnd = dropSite + ( AnglesToForward( direction ) * planeHalfDistance );
	pathEnd = pathEnd * ( 1, 1, 0 ) + ( 0, 0, flyHeight );
	
	d = length( pathStart - pathEnd );
	flyTime = ( d / planeFlySpeed );
	
	c130 = c130Setup( owner, pathStart, pathEnd );
	c130.veh_speed = planeFlySpeed;
	c130.dropType = dropType;
 	c130 playloopsound( "veh_ac130_dist_loop" );

	c130.angles = direction;
	forward = anglesToForward( direction );
	c130 moveTo( pathEnd, flyTime, 0, 0 ); 
	
	minDist = distance2D( c130.origin, dropSite );
	boomPlayed = false;
	
	for(;;)
	{
		dist = distance2D( c130.origin, dropSite );
		
		// handle missing our target
		if ( dist < minDist )
			minDist = dist;
		else if ( dist > minDist )
			break;
		
		if ( dist < 256 )
		{
			break;
		}
		else if ( dist < 768 )
		{
			earthquake( 0.15, 1.5, dropSite, 1500 );
			if ( !boomPlayed )
			{
				c130 playSound( "veh_ac130_sonic_boom" );
				//c130 thread stopLoopAfter( 0.5 );
				boomPlayed = true;
			}
		}	
		
		wait ( .05 );	
	}	
	wait( 0.05 );
	
	crateType[0] = c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, undefined, pathStart );	
	wait ( 0.05 );
	c130 notify ( "drop_crate" );
	wait ( 0.05 );

	crateType[1] = c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, undefined, pathStart, undefined, crateType );
	wait ( 0.05 );
	c130 notify ( "drop_crate" );
	wait ( 0.05 );

	crateType[2] = c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, undefined, pathStart, undefined, crateType );
	wait ( 0.05 );
	c130 notify ( "drop_crate" );
	wait ( 0.05 );

	crateType[3] = c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, undefined, pathStart, undefined, crateType );	
	wait ( 0.05 );
	c130 notify ( "drop_crate" );

	wait ( 4 );
	c130 delete();
}


dropNuke( dropSite, owner, dropType )
{
	planeHalfDistance = 24000;
	planeFlySpeed = 2000;
	yaw = RandomInt( 360 );
	
	direction = ( 0, yaw, 0 );
	
	flyHeight = self getFlyHeightOffset( dropSite );
	
	pathStart = dropSite + ( AnglesToForward( direction ) * ( -1 * planeHalfDistance ) );
	pathStart = pathStart * ( 1, 1, 0 ) + ( 0, 0, flyHeight );

	pathEnd = dropSite + ( AnglesToForward( direction ) * planeHalfDistance );
	pathEnd = pathEnd * ( 1, 1, 0 ) + ( 0, 0, flyHeight );
	
	d = length( pathStart - pathEnd );
	flyTime = ( d / planeFlySpeed );
	
	c130 = c130Setup( owner, pathStart, pathEnd );
	c130.veh_speed = planeFlySpeed;
	c130.dropType = dropType;
 	c130 playloopsound( "veh_ac130_dist_loop" );

	c130.angles = direction;
	forward = anglesToForward( direction );
	c130 moveTo( pathEnd, flyTime, 0, 0 ); 
	
	// TODO: fix this... it's bad.  if we miss our distance (which could happen if plane speed is changed in the future) we stick in this thread forever
	boomPlayed = false;
	minDist = distance2D( c130.origin, dropSite );
	for(;;)
	{
		dist = distance2D( c130.origin, dropSite );

		// handle missing our target
		if ( dist < minDist )
			minDist = dist;
		else if ( dist > minDist )
			break;
		
		if ( dist < 256 )
		{
			break;
		}
		else if ( dist < 768 )
		{
			earthquake( 0.15, 1.5, dropSite, 1500 );
			if ( !boomPlayed )
			{
				c130 playSound( "veh_ac130_sonic_boom" );
				//c130 thread stopLoopAfter( 0.5 );
				boomPlayed = true;
			}
		}	
		
		wait ( .05 );	
	}	
	
	c130 thread dropTheCrate( dropSite, dropType, flyHeight, false, "nuke", pathStart );
	wait ( 0.05 );
	c130 notify ( "drop_crate" );

	wait ( 4 );
	c130 delete();
}

stopLoopAfter( delay )
{
	self endon ( "death" );
	
	wait ( delay );
	self stoploopsound();
}


playloopOnEnt( alias )
{
	soundOrg = spawn( "script_origin", ( 0, 0, 0 ) );
	soundOrg hide();
	soundOrg endon( "death" );
	thread delete_on_death( soundOrg );
	
	soundOrg.origin = self.origin;
	soundOrg.angles = self.angles;
	soundOrg linkto( self );
	
	soundOrg playloopsound( alias );
	
	self waittill( "stop sound" + alias );
	soundOrg stoploopsound( alias );
	soundOrg delete();
}


// spawn C130 at a start node and monitors it
c130Setup( owner, pathStart, pathGoal )
{
	forward = vectorToAngles( pathGoal - pathStart );
	c130 = spawnplane( owner, "script_model", pathStart, "compass_objpoint_c130_friendly", "compass_objpoint_c130_enemy" );
	c130 setModel( "vehicle_ac130_low_mp" );
	
	if ( !isDefined( c130 ) )
		return;

	//chopper playLoopSound( "littlebird_move" );
	c130.owner = owner;
	c130.team = owner.team;
	level.c130 = c130;
	
	return c130;
}

// spawn helicopter at a start node and monitors it
heliSetup( owner, pathStart, pathGoal )
{
	
	forward = vectorToAngles( pathGoal - pathStart );
	lb = SpawnHelicopter( owner, pathStart, forward, "littlebird_mp" , "vehicle_little_bird_armed_mp" );

	if ( !isDefined( lb ) )
		return;

	lb maps\mp\killstreaks\_helicopter::addToLittleBirdList();
	lb thread maps\mp\killstreaks\_helicopter::removeFromLittleBirdListOnDeath();

	//lb playLoopSound( "littlebird_move" );

	lb.health = 999999; // keep it from dying anywhere in code 
	lb.maxhealth = 500; // this is the health we'll check
	lb.damageTaken = 0; // how much damage has it taken
	lb setCanDamage( true );
	lb.owner = owner;
	lb.team = owner.team;
	lb.isAirdrop = true;
	lb thread watchTimeOut();
	lb thread heli_existence();
	lb thread heliDestroyed();
	lb thread heli_handleDamage();
	lb SetMaxPitchRoll( 45, 85 );	
	lb Vehicle_SetSpeed( 250, 175 );
	lb.heliType = "airdrop";

	lb.specialDamageCallback = ::Callback_VehicleDamage;
	
	return lb;
}

watchTimeOut()
{
	level endon( "game_ended" );
	self endon( "leaving" );	
	self endon( "helicopter_gone" );
	self endon( "death" );
	
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( 25.0 );
	
	self notify( "death" );
}

heli_existence()
{
	self waittill_any( "crashing", "leaving" );
	
	self notify( "helicopter_gone" );
}

heli_handleDamage() // self == heli
{
	self endon( "death" );
	level endon( "game_ended" );

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, meansOfDeath, modelName, tagName, partName, iDFlags, weapon );

		if( IsDefined( self.specialDamageCallback ) )
			self [[self.specialDamageCallback]]( undefined, attacker, damage, iDFlags, meansOfDeath, weapon, point, direction_vec, undefined, undefined, modelName, partName );
	}
}

Callback_VehicleDamage( inflictor, attacker, damage, iDFlags, meansOfDeath, weapon, point, dir, hitLoc, timeOffset, modelIndex, partName )
{
	if( isDefined( self.alreadyDead ) && self.alreadyDead )
		return;

	if( !isDefined( attacker ) || attacker == self )
		return;
		
	// don't allow people to destroy things on their team if FF is off
	if( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
		return;			
		
	if( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		self.wasDamagedFromBulletPenetration = true;
	
	self.wasDamaged = true;

	modifiedDamage = damage;

	if ( isPlayer( attacker ) )
	{					
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "helicopter" );

		if( meansOfDeath == "MOD_RIFLE_BULLET" || meansOfDeath == "MOD_PISTOL_BULLET" )
		{
			if ( attacker _hasPerk( "specialty_armorpiercing" ) )
				modifiedDamage += damage * level.armorPiercingMod;
		}
	}

	// in case we are shooting from a remote position, like being in the osprey gunner shooting this
	if( IsDefined( attacker.owner ) && IsPlayer( attacker.owner ) )
	{
		attacker.owner maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "helicopter" );
	}

	if( IsDefined( weapon ) )
	{
		switch( weapon )
		{
		case "ac130_105mm_mp":
		case "ac130_40mm_mp":
		case "stinger_mp":
		case "javelin_mp":
		case "remote_mortar_missile_mp":		
		case "remotemissile_projectile_mp":
			self.largeProjectileDamage = true;
			modifiedDamage = self.maxhealth + 1;
			break;

		case "sam_projectile_mp":
			self.largeProjectileDamage = true;		
			modifiedDamage = self.maxHealth * 0.5; // takes about 1 burst of sam rockets
			break;

		case "emp_grenade_mp":
			self.largeProjectileDamage = false;
			modifiedDamage = self.maxhealth + 1;
			break;
		}
	}

	self.damageTaken += modifiedDamage;		

	if( self.damageTaken >= self.maxhealth )
	{
		if ( isPlayer( attacker ) && ( !isDefined( self.owner ) || attacker != self.owner ) )
		{
			self.alreadyDead = true;
			attacker notify( "destroyed_helicopter" );
			attacker notify( "destroyed_killstreak", weapon );
			thread teamPlayerCardSplash( "callout_destroyed_helicopter", attacker );			
			attacker thread maps\mp\gametypes\_rank::giveRankXP( "kill", 300, weapon, meansOfDeath );			
			attacker thread maps\mp\gametypes\_rank::xpEventPopup( &"SPLASHES_DESTROYED_HELICOPTER" );
			thread maps\mp\gametypes\_missions::vehicleKilled( self.owner, self, undefined, attacker, damage, meansOfDeath, weapon );		
		}

		self notify ( "death" );
	}			
}

heliDestroyed()
{
	self endon( "leaving" );
	self endon( "helicopter_gone" );
	
	self waittill( "death" );
	
	if (! isDefined(self) )
		return;
		
	self Vehicle_SetSpeed( 25, 5 );
	self thread lbSpin( RandomIntRange(180, 220) );
	
	wait( RandomFloatRange( .5, 1.5 ) );
	
	self notify( "drop_crate" );
	
	lbExplode();
}

// crash explosion
lbExplode()
{
	forward = ( self.origin + ( 0, 0, 1 ) ) - self.origin;
	playfx ( level.chopper_fx["explode"]["death"]["cobra"], self.origin, forward );
	
	// play heli explosion sound
	self playSound( "cobra_helicopter_crash" );
	self notify ( "explode" );

	self delete();
}


lbSpin( speed )
{
	self endon( "explode" );
	
	// tail explosion that caused the spinning
	playfxontag( level.chopper_fx["explode"]["medium"], self, "tail_rotor_jnt" );
	playfxontag( level.chopper_fx["fire"]["trail"]["medium"], self, "tail_rotor_jnt" );
	
	self setyawspeed( speed, speed, speed );
	while ( isdefined( self ) )
	{
		self settargetyaw( self.angles[1]+(speed*0.9) );
		wait ( 1 );
	}
}

/**********************************************************
*		 crate trigger functions
***********************************************************/

nukeCaptureThink()
{
	while ( isDefined( self ) )
	{
		self waittill ( "trigger", player );

		if ( !player isOnGround() )
			continue;
			
		if ( !useHoldThink( player ) )
			continue;
			
		self notify ( "captured", player );
	}
}


crateOtherCaptureThink( useText )
{
	while ( isDefined( self ) )
	{
		self waittill ( "trigger", player );

		if ( isDefined( self.owner ) && player == self.owner )
			continue;
			
		if ( !self validateOpenConditions( player ) )
			continue;			

		player.isCapturingCrate = true;
		useEnt = self createUseEnt();
		result = useEnt useHoldThink( player, undefined, useText );
		
		if ( isDefined( useEnt ) )
			useEnt delete();
		
		if ( !result )
		{
			player.isCapturingCrate = false;
			continue;
		}
			
		player.isCapturingCrate = false;
		self notify ( "captured", player );
	}
}

crateOwnerCaptureThink( useText )
{
	while ( isDefined( self ) )
	{
		self waittill ( "trigger", player );

		if ( isDefined( self.owner ) && player != self.owner )
			continue;
				
		if ( !self validateOpenConditions( player ) )
			continue;

		player.isCapturingCrate = true;
		if ( !useHoldThink( player, 500, useText ) )
		{
			player.isCapturingCrate = false;
			continue;
		}
		
		player.isCapturingCrate = false;
		self notify ( "captured", player );
	}
}


validateOpenConditions( opener )
{
	//if ( !opener isOnGround() )
		//return false;	
	
	// don't let a juggernaut pick up a juggernaut crate
	if ( ( self.crateType == "airdrop_juggernaut_def" || self.crateType == "airdrop_juggernaut" ) && 
	   ( opener isJuggernaut() ) )
		return false;
	
	// don't let them open crates while using killstreaks, except being juggernaut
	currWeapon = opener GetCurrentWeapon();
	if( isKillstreakWeapon( currWeapon ) && !IsSubStr( currWeapon, "jugg_mp" ) )
		return false;
	if( IsDefined( opener.changingWeapon ) && isKillstreakWeapon( opener.changingWeapon ) && !IsSubStr( opener.changingWeapon, "jugg_mp" ) )
		return false;

	return true;
}


killstreakCrateThink( dropType )
{
	self endon ( "death" );
	
	if ( isDefined( game["strings"][self.crateType + "_hint"] ) )
		crateHint = game["strings"][self.crateType + "_hint"];
	else 
		crateHint = &"PLATFORM_GET_KILLSTREAK";
	
	crateSetupForUse( crateHint, "all", maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( self.crateType ) );

	self thread crateOtherCaptureThink();
	self thread crateOwnerCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		if ( isDefined( self.owner ) && player != self.owner )
		{
			if ( !level.teamBased || player.team != self.team )
			{
				switch( dropType )
				{
				case "airdrop_assault":
				case "airdrop_support":
				case "airdrop_escort":
				case "airdrop_osprey_gunner":
					player thread maps\mp\gametypes\_missions::genericChallenge( "hijacker_airdrop" );
					player thread hijackNotify( self, "airdrop" );
					break;
				case "airdrop_sentry_minigun":
					player thread maps\mp\gametypes\_missions::genericChallenge( "hijacker_airdrop" );
					player thread hijackNotify( self, "sentry" );
					break;
				case "airdrop_remote_tank":
					player thread maps\mp\gametypes\_missions::genericChallenge( "hijacker_airdrop" );
					player thread hijackNotify( self, "remote_tank" );
					break;
				case "airdrop_mega":
					player thread maps\mp\gametypes\_missions::genericChallenge( "hijacker_airdrop_mega" );
					player thread hijackNotify( self, "emergency_airdrop" );
					break;
				}
			}
			else
			{
				self.owner thread maps\mp\gametypes\_rank::giveRankXP( "killstreak_giveaway", Int(( maps\mp\killstreaks\_killstreaks::getStreakCost( self.crateType ) / 10 ) * 50) );
				//self.owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( "giveaway_airdrop", player );
				self.owner thread maps\mp\gametypes\_hud_message::SplashNotifyDelayed( "sharepackage", Int(( maps\mp\killstreaks\_killstreaks::getStreakCost( self.crateType ) / 10 ) * 50) );
			}
		}		
	
		player playLocalSound( "ammo_crate_use" );
		player thread maps\mp\killstreaks\_killstreaks::giveKillstreak( self.crateType, false, false, self.owner );

		// commented out because we handle this in _killstreaks::giveKillstreak as a mini-splash
		//player maps\mp\gametypes\_hud_message::killstreakSplashNotify( self.crateType, undefined );
		
		self deleteCrate();
	}
}


nukeCrateThink( dropType )
{
	self endon ( "death" );
	
	crateSetupForUse( &"PLATFORM_CALL_NUKE", "nukeDrop", maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( self.crateType ) );

	self thread nukeCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		player thread [[ level.killstreakFuncs[ self.crateType ] ]]( level.gtnw );
		level notify( "nukeCaptured", player );
		
		if ( isDefined( level.gtnw ) && level.gtnw )
			player.capturedNuke = 1;
		
		player playLocalSound( "ammo_crate_use" );
		self deleteCrate();
	}
}


trophyCrateThink( dropType )
{
	self endon ( "death" );

	crateSetupForUse( game["strings"]["trophy_hint"], "all", maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( self.crateType ) );

	self thread crateOtherCaptureThink();
	self thread crateOwnerCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		if ( isDefined( self.owner ) && player != self.owner )
		{
			if ( !level.teamBased || player.team != self.team )
			{
				player thread hijackNotify( self, "trophy" );
			}
			else
			{
				self.owner thread maps\mp\gametypes\_rank::giveRankXP( "killstreak_giveaway", Int( maps\mp\killstreaks\_killstreaks::getStreakCost( "airdrop_trophy" ) / 10 ) * 50 );
				self.owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( "giveaway_trophy", player );
			}
		}		
	
		player playLocalSound( "ammo_crate_use" );
		player thread giveLocalTrophy( dropType );
		
		self deleteCrate();
	}
}

juggernautCrateThink( dropType )
{
	self endon ( "death" );

	crateSetupForUse( game["strings"]["juggernaut_hint"], "all", maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( self.crateType ) );

	self thread crateOtherCaptureThink();
	self thread crateOwnerCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		if ( isDefined( self.owner ) && player != self.owner )
		{
			if ( !level.teamBased || player.team != self.team )
			{
				player thread hijackNotify( self, "juggernaut" );
			}
			else
			{
				self.owner thread maps\mp\gametypes\_rank::giveRankXP( "killstreak_giveaway", Int( maps\mp\killstreaks\_killstreaks::getStreakCost( self.crateType ) / 10 ) * 50 );
				self.owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( "giveaway_juggernaut", player );
			}
		}		
	
		player playLocalSound( "ammo_crate_use" );
		
		juggType = "juggernaut";
		switch( self.crateType )
		{
		case "airdrop_juggernaut":
			juggType = "juggernaut";
			break;
		case "airdrop_juggernaut_recon":
			juggType = "juggernaut_recon";
			break;
		}
		player thread maps\mp\killstreaks\_juggernaut::giveJuggernaut( juggType );
		
		self deleteCrate();
	}
}


sentryCrateThink( dropType )
{
	self endon ( "death" );

	crateSetupForUse( game["strings"]["sentry_hint"], "all", maps\mp\killstreaks\_killstreaks::getKillstreakCrateIcon( self.crateType ) );

	self thread crateOtherCaptureThink();
	self thread crateOwnerCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		if ( isDefined( self.owner ) && player != self.owner )
		{
			if ( !level.teamBased || player.team != self.team )
			{
				if ( isSubStr(dropType, "airdrop_sentry" ) )
					player thread hijackNotify( self, "sentry" );
				else
					player thread hijackNotify( self, "emergency_airdrop" );
			}
			else
			{
				self.owner thread maps\mp\gametypes\_rank::giveRankXP( "killstreak_giveaway", Int( maps\mp\killstreaks\_killstreaks::getStreakCost( "sentry" ) / 10 ) * 50 );
				self.owner maps\mp\gametypes\_hud_message::playerCardSplashNotify( "giveaway_sentry", player );
			}
		}		
	
		player playLocalSound( "ammo_crate_use" );
		player thread sentryUseTracker();
		
		self deleteCrate();
	}
}

trapNullFunc()
{
	
}

trapCrateThink( dropType )
{
	self endon ( "death" );

	randomType = getRandomCrateType( "airdrop_trapcontents" );	
	crateSetupForUse( game["strings"][randomType+"_hint"], "trap", "none" );
	
	self.bomb = spawn( "script_model", self.origin );

	result = BulletTrace( self.bomb.origin, self.bomb.origin + ( 100, 100, 128 ), false, self.bomb );
	self.bomb.killCamEnt = Spawn( "script_model", result[ "position" ] );
	
	self thread crateOtherCaptureThink();

	for ( ;; )
	{
		self waittill ( "captured", player );
		
		player thread detonateTrap( self.bomb, self, self.owner );		
	}	
}

detonateTrap( bomb, crate, owner )
{
	crate endon ( "death" );
	
	bomb rotatevelocity( ( 0, 300, 0 ), 3 );
	bomb setModel( "prop_suitcase_bomb" );
	
	location = crate.origin;
	
	thread play_sound_in_space( "javelin_clu_lock", location );
	wait (1.0);
	
	forward = ( location + ( 0, 0, 1 ) ) - location;
	playfx ( level.chopper_fx["explode"]["death"]["cobra"], location, forward );
	thread play_sound_in_space( "cobra_helicopter_crash", location );
	
	if ( isDefined( owner ) )
		bomb RadiusDamage( location, 400, 200, 50, owner, "MOD_EXPLOSIVE", "airdrop_trap_explosive_mp" ); 
	else
		bomb RadiusDamage( location, 400, 200, 50, undefined, "MOD_EXPLOSIVE", "airdrop_trap_explosive_mp" );
	
	crate deleteCrate();		
}

deleteCrate()
{
	if ( isDefined( self.objIdFriendly ) )
		_objective_delete( self.objIdFriendly );

	if ( isDefined( self.objIdEnemy ) )
		_objective_delete( self.objIdEnemy );

	if ( isDefined( self.bomb ) && isDefined( self.bomb.killcamEnt ) )
		self.bomb.killcamEnt delete();

	if ( isDefined( self.bomb ) )
		self.bomb delete();

	if( IsDefined( self.killCamEnt ) )
		self.killCamEnt delete();

	self delete();
}

sentryUseTracker()
{
	if ( !self maps\mp\killstreaks\_autosentry::giveSentry( "sentry_minigun" ) )
		self maps\mp\killstreaks\_killstreaks::giveKillstreak( "sentry" );
}


giveLocalTrophy( dropType )
{
	self.activeTrophy = true;
	self.trophyAmmo = 6;
	
	self thread personalTrophyActive();
}

hijackNotify( crate, crateType )
{
	self notify( "hijacker", crateType, crate.owner );
}


refillAmmo( refillEquipment )
{
	weaponList = self GetWeaponsListAll();
	
	if ( refillEquipment )
	{
		if ( self _hasPerk( "specialty_tacticalinsertion" ) && self getAmmoCount( "flare_mp" ) < 1 )
			self givePerk( "specialty_tacticalinsertion", false );	
		
		if ( self _hasPerk( "specialty_scrambler" ) && self getAmmoCount( "scrambler_mp" ) < 1 )
			self givePerk( "specialty_scrambler", false );	
		
		if ( self _hasPerk( "specialty_portable_radar" ) && self getAmmoCount( "portable_radar_mp" ) < 1 )
			self givePerk( "specialty_portable_radar", false );	
	}
		
	foreach ( weaponName in weaponList )
	{
		if ( isSubStr( weaponName, "grenade" ) || ( GetSubStr( weaponName, 0, 2 ) == "gl" ) )
		{
			if ( !refillEquipment || self getAmmoCount( weaponName ) >= 1 )
				continue;
		} 
		
		self giveMaxAmmo( weaponName );
	}
}


/**********************************************************
*		 Capture crate functions
***********************************************************/
useHoldThink( player, useTime, useText ) 
{
    player playerLinkTo( self );
    player playerLinkedOffsetEnable();
    
    player _disableWeapon();
    
    self.curProgress = 0;
    self.inUse = true;
    self.useRate = 0;
    
	if ( isDefined( useTime ) )
		self.useTime = useTime;
	else
		self.useTime = 3000;
    
    player thread personalUseBar( self, useText );
   
    result = useHoldThinkLoop( player );
	assert ( isDefined( result ) );
    
    if ( isAlive( player ) )
    {
        player _enableWeapon();
        player unlink();
    }
    
    if ( !isDefined( self ) )
    	return false;

    self.inUse = false;
	self.curProgress = 0;

	return ( result );
}


personalUseBar( object, useText )
{
    self endon( "disconnect" );
    
    useBar = createPrimaryProgressBar( 0, 25 );
    useBarText = createPrimaryProgressBarText( 0, 25 );
    if ( !isDefined( useText ) )
    	useText = &"MP_CAPTURING_CRATE";
    useBarText setText( useText );

    lastRate = -1;
    while ( isReallyAlive( self ) && isDefined( object ) && object.inUse && !level.gameEnded )
    {
        if ( lastRate != object.useRate )
        {
            if( object.curProgress > object.useTime)
                object.curProgress = object.useTime;
               
            useBar updateBar( object.curProgress / object.useTime, (1000 / object.useTime) * object.useRate );

            if ( !object.useRate )
            {
                useBar hideElem();
                useBarText hideElem();
            }
            else
            {
                useBar showElem();
                useBarText showElem();
            }
        }    
        lastRate = object.useRate;
        wait ( 0.05 );
    }
    
    useBar destroyElem();
    useBarText destroyElem();
}

useHoldThinkLoop( player )
{
    while( !level.gameEnded && isDefined( self ) && isReallyAlive( player ) && player useButtonPressed() && self.curProgress < self.useTime )
    {
        self.curProgress += (66 * self.useRate);
       
       	if ( isDefined(self.objectiveScaler) )
        	self.useRate = 1 * self.objectiveScaler;
		else
			self.useRate = 1;

        if ( self.curProgress >= self.useTime )
            return ( isReallyAlive( player ) );
       
        wait 0.05;
    } 
    
    return false;
}

isAirdropMarker( weaponName )
{
	switch ( weaponName )
	{
		case "airdrop_marker_mp":
		case "airdrop_mega_marker_mp":
		case "airdrop_sentry_marker_mp":
		case "airdrop_juggernaut_mp":
		case "airdrop_juggernaut_def_mp":
			return true;
		default:
			return false;
	}
}


createUseEnt()
{
	useEnt = spawn( "script_origin", self.origin );
	useEnt.curProgress = 0;
	useEnt.useTime = 0;
	useEnt.useRate = 3000;
	useEnt.inUse = false;

	useEnt thread deleteUseEnt( self );

	return ( useEnt );
}


deleteUseEnt( owner )
{
	self endon ( "death" );
	
	owner waittill ( "death" );
	
	self delete();
}


airdropDetonateOnStuck()
{
	self endon ( "death" );
	
	self waittill( "missile_stuck" );
	
	self detonate();
}

projectileExplode( projectile )
{
	self endon( "death" );
	
	projPosition = projectile.origin;
	projType = projectile.model;
	projAngles = projectile.angles;
	
	projectile delete();
	
	playFX( level.mine_explode, projPosition, AnglesToForward( projAngles ), AnglesToUp( projAngles ) );
	RadiusDamage( projPosition, 65, 75, 10, self );
}


personalTrophyActive()
{
	self endon( "disconnect" );
	self endon ( "death" );
	
	position = self.origin;
	
	for( ;; )
	{
		if ( !isDefined( level.grenades ) || level.grenades.size < 1 )
		{
			wait( .05 );
			continue;
		}
		
		sentryTargets = combineArrays ( level.grenades, level.missiles );
		
		foreach ( grenade in sentryTargets )
		{
			wait( .05 );
			
			if ( !isDefined(grenade) )
				continue;
			
			if ( grenade == self )
				continue;
			
			if ( isDefined( grenade.weaponName) && grenade.weaponName == "trophy_mp" )
				continue;
				
			if ( grenade.model == "weapon_parabolic_knife" )
				continue;
	
			if ( !isDefined( grenade.owner ) )
				grenade.owner = GetMissileOwner( grenade );
			
			assertEx( isDefined( grenade.owner ), "grenade has no owner"  );
			
			if ( isDefined( grenade.owner ) && level.teamBased && grenade.owner.team == self.team )
				continue;
			
			grenadeDistanceSquared = DistanceSquared( grenade.origin, self.origin );
			
			if ( grenadeDistanceSquared < 147456 )
			{
				if ( BulletTracePassed( grenade.origin, self.origin, false, self ) )
				{
					playFX( level.sentry_fire, self.origin + (0,0,32) , ( grenade.origin - self.origin ), AnglesToUp( self.angles ) );
					self thread projectileExplode( grenade );
					
					self.trophyAmmo--;
					
					if ( self.trophyAmmo <= 0 )
						return;
				}
			}
		}	
	}
	
}        
