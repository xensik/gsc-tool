#include maps\_utility;
#include common_scripts\utility;
#include maps\_sp_airdrop;
#include maps\_remotemissile_utility;

//
// --- HOW TO ADD KILLSTREAKS TO YOUR SP LEVEL AND GIVE THEM TO THE PLAYER ---
// (for level examples, check out the test_sp_killstreaks testmap.)
//
// -- FIRST... --
// - add these lines to your level CSV for base functionality:
//   - include,common_sp_killstreaks
//   - sound,sp_killstreaks,[levelname],all_sp
// - add extra CSVs for the killstreaks that you want to enable in your level:
//   - SENTRY: include,sp_killstreak_sentry
//
// -- FOR AIRDROPS... (care packages, airdropped sentries, etc) --
// - add these lines to your level CSV for base functionality:
//   - include,common_sp_airdrop
//   - sound,sp_airdrop,[levelname],all_sp
// - add a script_vehicle_littlebird_armed spawner to your level with targetname "airdrop_littlebird". make sure you check SPAWNER in its entity window!
// - also add an instance of prefabs/sp_airdrop_crate_collision_multi.map somewhere in your nonplayable space (this supplies the collision needed by the airdrop crate scripts).
// - add a script_origin with a targetname of "airstrikeheight" up in the sky of your map, this is used as reference for the chopper's Z position
// - make sure you recompile the map!
//
// ** NOTE: you don't need to include airdrops if you're just going to manually give killstreaks to the player, as long as those killstreaks don't themselves activate an airdrop (like a sentry drop)!
//
// -- FINALLY... --
// - before load\_main, run maps\_sp_airdrop::sp_airdrop_preload() and maps\_sp_killstreaks::sp_killstreaks_global_preload()
// - after load\_main, run maps\_sp_killstreaks::sp_killstreaks_init()
// - after sp_killstreaks_init() returns, run _sp_killstreaks::add_sp_killstreak() for each killstreak type you want to use in the map, for example add_sp_killstreak( "carepackage" )
//
// - finally, when you want to award a killstreak to the player, run _sp_killstreaks::give_sp_killstreak() on the player, for example level.player give_sp_killstreak( "carepackage" )
//


// -- SP KILLSTREAKS TODO --
// - script documentation
// - rework precaching system so that killstreaks that don't exist in the level don't need to be loaded
// - nationality-specific VO for killstreak events
// - care packages should randomly pick from among only the killstreaks loaded in a given level
//


// TODO DOCUMENT
// killstreak global preloads
sp_killstreaks_global_preload()
{
	PrecacheString( &"SP_KILLSTREAKS_CAPTURING_CRATE" );
	PrecacheShader( "progress_bar_fill" );
	PrecacheShader( "progress_bar_bg" );
	PrecacheShader( "dpad_killstreak_carepackage" );
	PrecacheShader( "specialty_carepackage" );
	PrecacheString( &"SP_KILLSTREAKS_SHAREPACKAGE_TITLE" );
	PrecacheString( &"SP_KILLSTREAKS_SHAREPACKAGE_DESC" );
	PrecacheString( &"SP_KILLSTREAKS_CRATE_HIJACK_TITLE" );
	PrecacheString( &"SP_KILLSTREAKS_CRATE_HIJACK_DESC" );
	
	// TODO - move individual killstreak precaches to another place
	// CAREPACKAGE PRECACHE
	PrecacheString( &"SP_KILLSTREAKS_EARNED_AIRDROP" );
	PrecacheString( &"SP_KILLSTREAKS_NAME_AIRDROP" );
	
	// SENTRY PRECACHE
	PrecacheItem( "killstreak_sentry_sp" );
	PrecacheShader( "specialty_sentry_gun_crate" );
	PrecacheShader( "specialty_airdrop_sentry_minigun" );
	PrecacheString( &"SP_KILLSTREAKS_EARNED_AIRDROP_SENTRY" );
	PrecacheString( &"SP_KILLSTREAKS_SENTRY_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_AIRDROP_SENTRY" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_SENTRY" );
	
	// PERK PRECACHE
	PrecacheShader( "specialty_stalker" );
	PrecacheShader( "specialty_longersprint" );
	PrecacheShader( "specialty_fastreload" );
	PrecacheShader( "specialty_quickdraw" );
	PrecacheShader( "specialty_steadyaim" );
	PrecacheString( &"SP_KILLSTREAKS_SPECIALTY_LONGERSPRINT_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_SPECIALTY_FASTRELOAD_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_SPECIALTY_QUICKDRAW_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_SPECIALTY_BULLETACCURACY_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_SPECIALTY_STALKER_PICKUP" );
	
	// C4 PRECACHE
	PrecacheItem( "c4" );
	PrecacheShader( "hud_icon_c4" );
	PrecacheString( &"SP_KILLSTREAKS_EARNED_AIRDROP_C4" );
	PrecacheString( &"SP_KILLSTREAKS_C4_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_AIRDROP_C4" );
	
	// AMMO PRECACHE
	PrecacheShader( "waypoint_ammo_friendly" );
	PrecacheString( &"PLATFORM_RESUPPLY" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_AIRDROP_AMMO" );

	// REMOTEMISSILE PRECACHE
	PrecacheItem( "remote_missile_detonator" );
	PrecacheItem( "remote_missile" );
	PrecacheShader( "dpad_killstreak_hellfire_missile" );
	PrecacheShader( "specialty_predator_missile" );
	PrecacheString( &"SP_KILLSTREAKS_EARNED_PREDATOR_MISSILE" );
	PrecacheString( &"SP_KILLSTREAKS_REMOTEMISSILE_PICKUP" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_AIRDROP_REMOTEMISSILE" );
	PrecacheString( &"SP_KILLSTREAKS_REWARDNAME_REMOTEMISSILE" );
	
	// NUKE PRECACHE
	PrecacheShader( "specialty_nuke" );
}

// TODO DOCUMENT
// killstreak initialization
sp_killstreaks_init()
{
	ASSERT( !sp_killstreaks_init_done() );
	ASSERT( !IsDefined( level.ks ) );
	level.ks = SpawnStruct();
	level.ks.killstreakTypes = [];
	
	mapCenterStruct = GetStruct( "map_center", "targetname" );
	ASSERT( IsDefined( mapCenterStruct ), "Couldn't find struct with targetname map_center." );
	level.mapCenter = mapCenterStruct.origin;
	
	array_thread( level.players, ::sp_killstreaks_player_init );
	
	// init airdrops if they haven't been already
	if( !sp_airdrop_init_done() )
	{
		sp_airdrop_init();
	}
	
	sp_killstreaks_hud_init();
	
	// flag that we're done with initialization
	level.ks.globalInitDone = true;
}

// sets up info needed in copied MP scripts that handle hudelems
sp_killstreaks_hud_init()
{
	level.uiParent = spawnstruct();
	level.uiParent.horzAlign = "left";
	level.uiParent.vertAlign = "top";
	level.uiParent.alignX = "left";
	level.uiParent.alignY = "top";
	level.uiParent.x = 0;
	level.uiParent.y = 0;
	level.uiParent.width = 0;
	level.uiParent.height = 0;
	level.uiParent.children = [];
	
	level.fontHeight = 12;
	
	level.hud["allies"] = spawnstruct();
	level.hud["axis"] = spawnstruct();
	
	// we can, of course, separate out the following constants for splitscreen.	
	// primary progress bars are for things like capturing flags or planting bombs - big, important things that happen as you play a gametype
	level.primaryProgressBarY = -61; // from center
	level.primaryProgressBarX = 0;
	level.primaryProgressBarHeight = 9; //28; // this is the height and width of the whole progress bar, including the outline. the part that actually moves is 2 pixels smaller.
	level.primaryProgressBarWidth = 120;
	level.primaryProgressBarTextY = -75;
	level.primaryProgressBarTextX = 0;
	level.primaryProgressBarFontSize = .6; // 1.4 before font change from "objective"
	
	level.teamProgressBarY = 32; // 205;
	level.teamProgressBarHeight = 14;
	level.teamProgressBarWidth = 192;
	level.teamProgressBarTextY = 8; // 155;
	level.teamProgressBarFontSize = 1.65;

	if ( IsSplitscreen() )
	{
		level.lowerTextYAlign = "BOTTOM";
		level.lowerTextY = -76;
		level.lowerTextFontSize = 1.14;
	}
	else
	{
		level.lowerTextYAlign = "CENTER";
		level.lowerTextY = 70;
		level.lowerTextFontSize = 1.6;
	}
}

// checks to see if initialization is done for the sp killstreaks system
sp_killstreaks_init_done()
{
	return( IsDefined( level.ks ) && IsDefined( level.ks.globalInitDone ) );
}

// sets each player up to use sp killstreaks
sp_killstreaks_player_init()
{
	self.ks = SpawnStruct();
	self.ks.killstreaks = [];  // killstreak types that have been earned by the player
	
	// waits for killstreak use
	self thread sp_killstreak_use_waiter();
	
	// REMOTEMISSILE player-specific init - TODO make this not happen if remotemissile isn't an available killstreak in the level
	if( !IsDefined( self.remotemissile_actionslot ) )
	{
		self.remotemissile_actionslot = 4;
	}
	
	self thread remotemissile_no_autoreload();
}

// TODO DOCUMENT
// sets up a killstreak for use in SP
add_sp_killstreak( streakType )
{
	ASSERT( sp_killstreaks_init_done() );
	
	// make sure this type isn't in the array already
	ASSERTEX( !sp_killstreak_exists( streakType ), "Couldn't add killstreak info for type '" + streakType + "' because info with that type name has already been added." );
	
	weaponName	= undefined;
	streakFunc	= undefined;
	achieveVO	= undefined;
	useVO		= undefined;
	splashIcon	= undefined;
	splashHint	= undefined;
	crateIcon	= undefined;
	crateHint	= undefined;
	crateOpenFunc = undefined;
	
	// perks
	if ( issubstr( streakType, "specialty_" ) )
	{
		weaponName	= "airdrop_marker_mp";
		streakFunc	= ::sp_killstreak_carepackage_main;
		menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP";
		achieveVO	= "UK_1mc_achieve_carepackage";
		useVO		= "UK_1mc_use_carepackage";
		splashIcon	= "specialty_carepackage";
		splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP";
		crateOpenFunc = ::sp_killstreak_perk_crateopen;
		
		switch( streakType )
		{
			case "specialty_longersprint":
				crateIcon	= "specialty_longersprint";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_LONGERSPRINT_PICKUP";
				break;
				
			case "specialty_fastreload":
				crateIcon	= "specialty_fastreload";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_FASTRELOAD_PICKUP";
				break;
				
			case "specialty_quickdraw":
				crateIcon	= "specialty_quickdraw";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_QUICKDRAW_PICKUP";
				break;
				
			case "specialty_detectexplosive":
				crateIcon	= "specialty_bombsquad";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_DETECTEXPLOSIVE_PICKUP";	
				break;	
				
			case "specialty_bulletaccuracy":
				crateIcon	= "specialty_steadyaim";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_BULLETACCURACY_PICKUP";
				break;
				
			case "specialty_stalker":
				crateIcon	= "specialty_stalker";
				crateHint	= &"SP_KILLSTREAKS_SPECIALTY_STALKER_PICKUP";
				break;
			
			default:
				ASSERTMSG( "Couldn't identify sp killstreak to add, of type '" + streakType + "'." );
				return;
		}
	}
	else
	{
		switch( streakType )
		{
			case "carepackage":
				weaponName	= "airdrop_marker_mp";
			streakFunc	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "specialty_carepackage";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP";
				crateIcon	= "dpad_killstreak_carepackage";
				crateHint	= &"SP_KILLSTREAKS_NAME_AIRDROP";
				crateOpenFunc = undefined;
				break;
			
			case "carepackage_sentry":
				weaponName	= "airdrop_marker_mp";
				streakFunc 	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP_SENTRY";
				achieveVO	= "UK_1mc_deploy_sentry";
				useVO		= undefined;
				splashIcon	= "specialty_airdrop_sentry_minigun";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP_SENTRY";
				crateIcon	= "specialty_sentry_gun_crate";
				crateHint	= &"SP_KILLSTREAKS_SENTRY_PICKUP";
				crateOpenFunc = undefined;
				break;
				
			case "sentry":
				weaponName	= "killstreak_sentry_sp";
				streakFunc 	= ::sp_killstreak_autosentry_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_SENTRY";
				if ( GetDvarInt( "survival_chaos" ) == 1 )
				{
					achieveVO	= "cm_bp_cp_sentrygun";
				}
				else
				{
					achieveVO	= "UK_1mc_deploy_sentry";
				}
				useVO		= undefined;
				splashIcon	= "specialty_airdrop_sentry_minigun";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP_SENTRY";
				crateIcon	= "specialty_sentry_gun_crate";
				crateHint	= &"SP_KILLSTREAKS_SENTRY_PICKUP";
				crateOpenFunc = undefined;
				break;
				
			case "sentry_gl":
				weaponName	= "killstreak_sentry_sp";
				streakFunc 	= ::sp_killstreak_autosentry_gl_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_SENTRY";
				achieveVO	= "UK_1mc_deploy_sentry";
				useVO		= undefined;
				splashIcon	= "specialty_airdrop_sentry_minigun";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP_SENTRY";
				crateIcon	= "specialty_sentry_gun_crate";
				crateHint	= &"SP_KILLSTREAKS_SENTRY_PICKUP";
				crateOpenFunc = undefined;
				break;	
						
			case "carepackage_remote_missile":
				weaponName	= "airdrop_marker_mp";
				streakFunc	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP_REMOTEMISSILE";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "specialty_predator_missile";
				splashHint	= &"SP_KILLSTREAKS_";
				crateIcon	= "dpad_killstreak_carepackage";
				crateHint	= &"SP_KILLSTREAKS_NAME_AIRDROP";
				crateOpenFunc = undefined;
				break;
			
			case "remote_missile":
				weaponName	= "remote_missile_detonator";
				streakFunc 	= ::sp_killstreak_remotemissile_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_REMOTEMISSILE";
				achieveVO	= "UK_1mc_achieve_hellfire";
				useVO		= "UK_1mc_use_hellfire";
				splashIcon	= "specialty_predator_missile";
				splashHint	= &"SP_KILLSTREAKS_EARNED_PREDATOR_MISSILE";
				crateIcon	= "dpad_killstreak_hellfire_missile";
				crateHint	= &"SP_KILLSTREAKS_REMOTEMISSILE_PICKUP";
				crateOpenFunc = undefined;
				break;
				
			case "carepackage_c4":
				weaponName	= "airdrop_marker_mp";
				streakFunc	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP_C4";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "hud_icon_c4";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP_C4";
				crateIcon	= "hud_icon_c4";
				crateHint	= &"SP_KILLSTREAKS_C4_PICKUP";
				crateOpenFunc = ::sp_killstreak_c4_crateopen;
				break;
	
			case "carepackage_ammo":
				weaponName	= "airdrop_marker_mp";
				streakFunc	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_AIRDROP_AMMO";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "specialty_carepackage";
				splashHint	= &"SP_KILLSTREAKS_EARNED_AIRDROP";
				crateIcon	= "waypoint_ammo_friendly";
				crateHint	= &"PLATFORM_RESUPPLY";
				crateOpenFunc = ::sp_killstreak_ammo_crateopen;
				break;
	
			case "carepackage_precision_airstrike":
				weaponName	= "airdrop_marker_mp";
				streakFunc 	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_PRECISION_AIRSTRIKE";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "specialty_precision_airstrike";
				splashHint	= &"SP_KILLSTREAKS_EARNED_PRECISION_AIRSTRIKE";
				crateIcon	= "dpad_killstreak_carepackage";
				crateHint	= &"SP_KILLSTREAKS_PRECISION_AIRSTRIKE_PICKUP";
				crateOpenFunc = undefined;
				break;
						
			case "precision_airstrike":
				weaponName	= "killstreak_precision_airstrike_sp";
				streakFunc 	= ::sp_killstreak_airstrike_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_PRECISION_AIRSTRIKE";
				achieveVO	= "UK_1mc_achieve_airstrike";
				useVO		= "UK_1mc_use_airstrike";
				splashIcon	= "specialty_precision_airstrike";
				splashHint	= &"SP_KILLSTREAKS_EARNED_PRECISION_AIRSTRIKE";
				crateIcon	= "dpad_killstreak_precision_airstrike";
				crateHint	= &"SP_KILLSTREAKS_PRECISION_AIRSTRIKE_PICKUP";
				crateOpenFunc = undefined;
				break;
	
			case "carepackage_stealth_airstrike":
				weaponName	= "airdrop_marker_mp";
				streakFunc 	= ::sp_killstreak_carepackage_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_STEALTH_AIRSTRIKE";
				achieveVO	= "UK_1mc_achieve_carepackage";
				useVO		= "UK_1mc_use_carepackage";
				splashIcon	= "specialty_stealth_bomber";
				splashHint	= &"SP_KILLSTREAKS_EARNED_STEALTH_AIRSTRIKE";
				crateIcon	= "dpad_killstreak_carepackage";
				crateHint	= &"SP_KILLSTREAKS_STEALTH_AIRSTRIKE_PICKUP";
				crateOpenFunc = undefined;
				break;
							
			case "stealth_airstrike":
				weaponName	= "killstreak_stealth_airstrike_sp";
				streakFunc 	= ::sp_killstreak_airstrike_main;
				menuRewardDesc	= "SP_KILLSTREAKS_REWARDNAME_STEALTH_AIRSTRIKE";
				achieveVO	= "UK_1mc_achieve_airstrike";
				useVO		= "UK_1mc_use_airstrike";
				splashIcon	= "specialty_stealth_bomber";
				splashHint	= &"SP_KILLSTREAKS_EARNED_STEALTH_AIRSTRIKE";
				crateIcon	= "dpad_killstreak_stealth_bomber";
				crateHint	= &"SP_KILLSTREAKS_STEALTH_AIRSTRIKE_PICKUP";
				crateOpenFunc = undefined;
				break;
				
			default:
				ASSERTMSG( "Couldn't identify sp killstreak to add, of type '" + streakType + "'." );
				return;
		}
	}
	
	// actually add the killstreak to the array
	info = SpawnStruct();
	info.streakType = streakType;
	info.weaponName = weaponName;
	info.streakFunc = streakFunc;
	info.menuRewardDesc = menuRewardDesc;
	info.achieveVO = achieveVO;
	info.useVO = useVO;
	info.splashIcon	= splashIcon;
	info.splashHint	= splashHint;
	info.crateIcon = crateIcon;
	info.crateHint = crateHint;
	info.crateOpenFunc = crateOpenFunc;
	level.ks.killstreakTypes[ streakType ] = info;
	
	add_killstreak_radio_dialogue( achieveVO, useVO );
}

add_killstreak_radio_dialogue( sound1, sound2 )
{
	if( !IsDefined( level.scr_radio ) )
	{
		level.scr_radio = [];
	}
	
	sounds[ 0 ] = sound1;
	sounds[ 1 ] = sound2;
	
	foreach( sound in sounds )
	{
		if( !array_contains( level.scr_radio, sound ) && IsDefined( sound ) )
		{
			level.scr_radio[ sound ] = sound;
		}
	}
}

sp_killstreak_exists( streakType )
{
	foreach( index, info in level.ks.killstreakTypes )
	{
		if( index == streakType )
		{
			return true;
		}
	}
	
	return false;
}

// gets an entity that holds info about this killstreak, previously set up in add_sp_killstreak()
get_sp_killstreak_info( streakType )
{
	ASSERT( sp_killstreaks_init_done() );
	
	info = level.ks.killstreakTypes[ streakType ];
	ASSERTEX( IsDefined( info ), "Couldn't find sp killstreak info for type '" + streakType + "'." );
	
	return info;
}

// TODO DOCUMENT
// actually give a killstreak to a player for use
give_sp_killstreak( streakType, regive )
{
	ASSERT( IsDefined( streakType ) );
	
	/* make sure player doesn't have this killstreak already
	foreach( existingType in self.ks.killstreaks )
	{
		if( existingType == streakType )
		{
			println( "Warning: tried to give sp killstreak of type '" + streakType + "', but the player already had one of those killstreaks." );
			return;
		}
	}
	*/
	
	if( !IsDefined( self.ks.killstreaks[ 0 ] ) )
	{
		// just add this one
		self.ks.killstreaks[ 0 ] = streakType;
	}
	else
	{
		// otherwise, add FILO style
		newarr = [];
		newarr[ 0 ]  = streakType;
		
		foreach( existingType in self.ks.killstreaks )
		{
			newarr[ newarr.size ] = existingType;
		}
		
		self.ks.killstreaks = newarr;
	}
	
	self activate_current_sp_killstreak( regive );
}

activate_current_sp_killstreak( regive )
{
	streakType = self.ks.killstreaks[ 0 ];
	ASSERT( IsDefined( streakType ) );
	
	// ENHANCEMENT SP splash notify for player getting the killstreak?
	println( "KILLSTREAK GET" );
	
	killstreakInfo = get_sp_killstreak_info( streakType );
	
	self GiveWeapon( killstreakInfo.weaponName );
	self SetActionSlot( 4, "weapon", killstreakInfo.weaponName );
	
	// remote missile needs to be activated when it's ready to go
	if( streakType == "remote_missile" )
	{
		maps\_remotemissile::enable_uav( true, killstreakInfo.weaponName );
	}
	
	// TODO needs to be set up to work for multiple nationalities and with SO battlechatter
	
	// skip dialogue if user cancenlled sentry placement and was regiven the same sentry
	if ( !isdefined( regive ) || !regive )
		self thread radio_dialogue( killstreakInfo.achieveVO );
}

// removes a killstreak from a player's queue
take_sp_killstreak( streakType )
{
	ASSERT( IsDefined( self.ks ) && IsDefined( self.ks.killstreaks ) );
	ASSERT( self.ks.killstreaks.size );
	
	taken = false;
	foreach( index, existingType in self.ks.killstreaks )
	{
		if( existingType == streakType )
		{
			self.ks.killstreaks = array_remove( self.ks.killstreaks, streakType );
			
			// if this is the active killstreak in the queue, take the weapon from the player
			if( index == 0 )
			{
				killstreakInfo = get_sp_killstreak_info( streakType );
				self TakeWeapon( killstreakInfo.weaponName );
			}
			taken = true;
			break;
		}
	}
	
	ASSERT( taken, "Couldn't take sp killstreak of type '" + streakType + "' because the player didn't actually have it in his queue." );
	
	if( self has_any_killstreak() )
	{
		self activate_current_sp_killstreak();
	}
}

has_any_killstreak()
{
	return( self.ks.killstreaks.size );
}

has_killstreak( type )
{
	if( self has_any_killstreak() )
	{
		foreach( streakType in self.ks.killstreaks )
		{
			if( type == streakType )
			{
				return true;
			}
		}
	}
	
	return false;
}

// waits for a player to use his given killstreak
sp_killstreak_use_waiter()
{
	self endon( "death" );
	
	for ( ;; )
	{
		self.ks.lastWeaponUsed = self GetCurrentWeapon();
		
		self waittill ( "weapon_change", newWeapon );
		
		if ( !IsAlive( self ) )
		{
			continue;
		}
		
		killstreakType = self.ks.killstreaks[ 0 ];
		
		// make sure we have a killstreak to wait for
		if ( !IsDefined( killstreakType ) )
		{
			continue;
		}
		
		killstreakInfo = get_sp_killstreak_info( killstreakType );
		
		if( IsDefined( killstreakInfo.weaponName ) )
		{
			// is this the weapon corresponding to the one used to call the killstreak?
			if ( newWeapon != killstreakInfo.weaponName )
			{
				continue;
			}
		}

		waittillframeend;

		success = self sp_killstreak_use_pressed( killstreakInfo );
		
		if( success )
		{
			self used_sp_killstreak( killstreakInfo );
			self take_sp_killstreak( killstreakType );
		}
		else
		{
			if ( !isdefined( self.carrying_pickedup_sentry ) || !self.carrying_pickedup_sentry )
				self post_killstreak_weapon_switchback();
		}
		
		if( is_survival() )
		{
			wait 0.05; // wait for self.sentry_placement_failed is updated
			
			if ( isdefined( self.sentry_placement_failed ) && self.sentry_placement_failed )
			{
				// sentry placement failed, regive sentry
				self give_sp_killstreak( killstreakType, true );
			}
		}
		
		// give time to switch to the near weapon; when the weapon is none (such as during a "disableWeapon()" period
		// re-enabling the weapon immediately does a "weapon_change" to the killstreak weapon we just used.  In the case that 
		// we have two of that killstreak, it immediately uses the second one
		if ( self GetCurrentWeapon() == "none" )
		{
			while ( self GetCurrentWeapon() == "none" )
			{
				wait ( 0.05 );
			}

			waittillframeend;
		}
	}
}

// figures out whether a killstreak can be used when the button is pressed, and tries to run that killstreak's activation function
sp_killstreak_use_pressed( killstreakInfo )
{
	streakType = killstreakInfo.streakType;

	ASSERT( IsDefined( streakType ) );
	ASSERT( IsDefined( killstreakInfo.streakFunc ) );

	if ( !self isOnGround() && isCarryKillstreak( streakType ) )
	{
		return ( false );
	}

	if ( self isUsingRemote() )
	{
		return ( false );
	}

	if ( isDefined( self.selectingLocation ) )
	{
		return ( false );
	}

	if ( self IsUsingTurret() && ( isRideKillstreak( streakType ) || isCarryKillstreak( streakType ) ) )
	{
		// TODO coop-ify, we don't have per-player printlnbolds in SP
		iprintlnbold( &"MP_UNAVAILABLE_USING_TURRET" );
		return ( false );
	}
	
	if ( ( self ent_flag_exist( "laststand_downed" ) && self ent_flag( "laststand_downed" ) ) && isRideKillstreak( streakType ) )
	{
		// TODO coop-ify, we don't have per-player printlnbolds in SP
		iprintlnbold( &"MP_UNAVILABLE_IN_LASTSTAND" );
		return ( false );
	}
	
	if ( !self isWeaponEnabled() )
	{
		return ( false );
	}
	
	// run the function for this killstreak
	if ( !self [[ killstreakInfo.streakFunc ]]( killstreakInfo ) )
	{
		return ( false );
	}

	return ( true );
}

// TODO needs to be set up to work for multiple nationalities and with SO battlechatter
used_sp_killstreak( info )
{
	self PlayLocalSound( "weap_c4detpack_trigger_plr" );
	
	// remotemissile needs to call its use VO during the killstreak, not after it's done
	if( IsDefined( info.useVO ) && info.streakType != "remote_missile" )
	{
		thread radio_dialogue( info.useVO );
	}
}

post_killstreak_weapon_switchback()
{
	if ( is_player_down( self ) )
	{
		return;
	}
	
	if( IsDefined( self.ks.lastWeaponUsed ) )
	{
		if ( self.ks.lastWeaponUsed == "none" )
		{
			primary_weapons = self GetWeaponsListPrimaries();
			assert( primary_weapons.size > 0 );
			self SwitchToWeapon( primary_weapons[0] );
		}
		else
		{
			self SwitchToWeapon( self.ks.lastWeaponUsed );
		}
	}
}


// -------------------------------------
// --- SP KILLSTREAK: REMOTE MISSILE ---
// -------------------------------------
sp_killstreak_remotemissile_main( killstreakInfo )
{
	weaponName = killstreakInfo.weaponName;
	
	self.remotemissileFired = false;
	self thread sp_killstreak_remotemissile_waitForFire( killstreakInfo.useVO );
	
	while( self.using_uav )
	{
		wait( 0.05 );
	}
	
	self notify( "stopped_using_uav" );
	
	// don't need to switch back to previous weapon here because the remotemissile script handles
	
	// only return true if the missile was fired; otherwise we don't want to take the killstreak away
	return self.remoteMissileFired;
}

sp_killstreak_remotemissile_waitForFire( useVO )
{
	self endon( "stopped_using_uav" );
	self waittill( "player_fired_remote_missile" );
	self.remoteMissileFired = true;
	self thread radio_dialogue( useVO );
}


// -----------------------------------
// --- SP KILLSTREAK: CARE PACKAGE ---
// -----------------------------------
sp_killstreak_carepackage_main( killstreakInfo )
{
	// figure out the care package type
	crateType = sp_carepackage_select_reward( killstreakInfo );
	
	// call in an airdrop for it
	airdropSuccess = sp_try_use_airdrop( crateType );
	
	if( !airdropSuccess )
	{
		return false;
	}
	
	return true;
}


sp_carepackage_select_reward( killstreakInfo )
{
	// perks pass its reference
	if( issubstr( killstreakInfo.streakType, "specialty_" ) )
	{
		return killstreakInfo.streakType;
	}
	
	if( killstreakInfo.streakType == "carepackage_c4" )
	{
		return "carepackage_c4";
	}
	else if( killstreakInfo.streakType == "carepackage_remote_missile" )
	{
		return "remote_missile";
	}
	else if( killstreakInfo.streakType == "carepackage_sentry" )
	{
		return "sentry";
	}
	else if( killstreakInfo.streakType == "carepackage_ammo" )
	{
		return "carepackage_ammo";
	}
	else if( killstreakInfo.streakType == "carepackage_precision_airstrike" )
	{
		return "precision_airstrike";
	}
	else if( killstreakInfo.streakType == "carepackage_stealth_airstrike" )
	{
		return "stealth_airstrike";
	}
		
	// TODO select from all currently-loaded killstreak types using level.ks.killstreakTypes
	types = [];
	weights = [];
	
	types[ types.size ] = "sentry";
	weights[ "sentry" ] = 5;
	
	types[ types.size ] = "remote_missile";
	weights[ "remote_missile" ] = 15;
	
	types[ types.size ] = "precision_airstrike";
	weights[ "precision_airstrike" ] = 10;
	
	types[ types.size ] = "stealth_airstrike";
	weights[ "stealth_airstrike" ] = 10;
	
	types[ types.size ] = "carepackage_c4";
	weights[ "carepackage_c4" ] = 5;
	
	types[ types.size ] = "carepackage_ammo";
	weights[ "carepackage_ammo" ] = 5;
	
	return getWeightedChanceRoll( types, weights );
}

// -----------------------------------
// --- SP KILLSTREAK: AMMO -----------
// -----------------------------------
sp_killstreak_ammo_crateopen()
{
	self PlayLocalSound( "ammo_crate_use" );
	self refillAmmo();
}

refillAmmo()
{
	weaponList = self GetWeaponsListAll();
	
	foreach ( weaponName in weaponList )
	{
		if ( isSubStr( weaponName, "grenade" ) )
		{
			if ( self getAmmoCount( weaponName ) >= 1 )
			{
				continue;
			}
		} 
		
		self GiveMaxAmmo( weaponName );
	}
}

// -----------------------------------
// --- SP KILLSTREAK: PERK -------------
// -----------------------------------
sp_killstreak_perk_crateopen( ref )
{
	self thread maps\_so_survival_perks::give_perk( ref );
}

// -----------------------------------
// --- SP KILLSTREAK: C4 -------------
// -----------------------------------
sp_killstreak_c4_crateopen()
{
	if( !self HasWeapon( "c4" ) )
	{
		self GiveWeapon( "c4" );
		self SetActionSlot( 2, "weapon", "c4" );
	}
	else
	{
		if( self GetFractionMaxAmmo( "c4" ) == 1 )
		{
			// player already has max c4
			return;
		}
		
		curr = self GetWeaponAmmoStock( "c4" );
		self SetWeaponAmmoStock( "c4", curr + 4 );
	}
		
}


// ---------------------------------
// --- SP KILLSTREAK: SENTRY GUN ---
// ---------------------------------
sp_killstreak_autosentry_main( killstreakInfo )
{
	self common_scripts\_sentry::giveSentry( "sentry_minigun" );
	self thread sentry_cancel_notify();
	
	self NotifyOnPlayerCommand( "controller_sentry_cancel", "+actionslot 4" ); // DPad Right
	self NotifyOnPlayerCommand( "controller_sentry_cancel", "weapnext" );		// BUTTON_Y
	
	self waittill_any( "sentry_placement_finished", "sentry_placement_canceled" );

	self post_killstreak_weapon_switchback();
		
	return true;
}

sp_killstreak_autosentry_gl_main( killstreakInfo )
{
	self common_scripts\_sentry::giveSentry( "sentry_gun" );
	self thread sentry_cancel_notify();
	
	self NotifyOnPlayerCommand( "controller_sentry_cancel", "+actionslot 4" ); // DPad Right
	self NotifyOnPlayerCommand( "controller_sentry_cancel", "weapnext" );		// BUTTON_Y
	
	self waittill_any( "sentry_placement_finished", "sentry_placement_canceled" );

	self post_killstreak_weapon_switchback();
	
	return true;
}

sentry_cancel_notify()
{
	// ends on cancel or finished from someone else
	self endon( "sentry_placement_canceled" );
	self endon( "sentry_placement_finished" );
	
	self waittill( "controller_sentry_cancel" );
	
	if ( !isdefined( self.carrying_pickedup_sentry ) || !self.carrying_pickedup_sentry )
		self notify( "sentry_placement_canceled" );
}

// --------------------------------
// --- SP KILLSTREAK: AIRSTRIKE ---
// --------------------------------
sp_killstreak_airstrike_main( killstreakInfo )
{
	streakType = killstreakInfo.streakType;
	airstrikeType = "default";
	
	if( streakType == "precision_airstrike" )
	{
		airstrikeType = "precision";
	}
	else if( streakType == "stealth_airstrike" )
	{
		airstrikeType = "stealth";
	}
	
	result = maps\_sp_airstrike::try_use_airstrike( airstrikeType );
	
	self post_killstreak_weapon_switchback();
	
	return result;
}


// --------------------
// --- DUPE SCRIPTS ---
// --------------------
isUsingRemote()
{
	return( isDefined( self.usingRemote ) );
}

isRideKillstreak( streakType )
{
	switch( streakType )
	{
		case "helicopter_minigun":
		case "helicopter_mk19":
		case "ac130":
		case "predator_missile":
			return true;

		default:
			return false;
	}
}

isCarryKillstreak( streakType )
{
	switch( streakType )
	{
		case "sentry":
		case "sentry_gl":
			return true;

		default:
			return false;
	}
}

deadlyKillstreak( streakType )
{
	switch ( streakType )
	{
		case "predator_missile":
		case "precision_airstrike":
		case "harrier_airstrike":
		//case "helicopter":
		//case "helicopter_flares":
		case "stealth_airstrike":
		//case "helicopter_minigun":
		case "ac130":
			return true;
	}
	
	return false;
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
