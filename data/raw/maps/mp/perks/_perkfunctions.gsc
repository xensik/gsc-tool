/******************************************************************* 
//						_perkfunctions.gsc  
//	
//	Holds all the perk set/unset and listening functions 
//	
//	Jordan Hirsh	Sept. 11th 	2008
********************************************************************/

#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include maps\mp\perks\_perks;


setOverkillPro()
{
}

unsetOverkillPro()
{	
}

setEMPImmune()
{
}

unsetEMPImmune()
{	
}

// highlight enemies while sniping
setAutoSpot()
{
	self autoSpotAdsWatcher();
	self autoSpotDeathWatcher();
}

autoSpotDeathWatcher()
{
	self waittill( "death" );
	self endon ( "disconnect" );
	self endon ( "endAutoSpotAdsWatcher" );
	level endon ( "game_ended" );
	
	self AutoSpotOverlayOff();
}

unsetAutoSpot()
{	
	self notify( "endAutoSpotAdsWatcher" );
	self AutoSpotOverlayOff();
}

autoSpotAdsWatcher()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "endAutoSpotAdsWatcher" );
	level endon ( "game_ended" );
	
	spotter = false;
	
	for( ;; )
	{
		wait( 0.05 );
		
		if( self IsUsingTurret() )
		{
			self AutoSpotOverlayOff();
			continue;
		}
		
		adsLevel = self PlayerADS();
		
		if( adsLevel < 1 && spotter )
		{
			spotter = false;
			self AutoSpotOverlayOff();
		}	
			
		if( adsLevel < 1 && !spotter )
			continue;
		
		if( adsLevel == 1 && !spotter )
		{
			spotter = true;
			self AutoSpotOverlayOn();		
		}
	}
}

//faster health regen
setRegenSpeed()
{
}

unsetRegenSpeed()
{	
}

//shellshock Reduction
setHardShell()
{
	self.shellShockReduction = .25;
}

unsetHardShell()
{	
	self.shellShockReduction = 0;
}

//viewkick Reduction
setSharpFocus()
{
	self setViewKickScale( .50 );
}

unsetSharpFocus()
{	
	self setViewKickScale( 1 );
}

setDoubleLoad()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "endDoubleLoad" );
	level endon ( "game_ended" );
	
	for( ;; )
	{
		self waittill( "reload" );
		
		weapons = self GetWeaponsList( "primary" );
		
		foreach( weapon in weapons )
		{
			
			ammoInClip = self GetWeaponAmmoClip( weapon );
			clipSize = weaponClipSize( weapon );
			difference =  clipSize - ammoInClip;
			ammoReserves = self getWeaponAmmoStock( weapon );
			
			if ( ammoInClip != clipSize && ammoReserves > 0 )
			{
				
				if ( ammoInClip + ammoReserves >= clipSize )
				{
					self setWeaponAmmoClip( weapon, clipSize );
					self setWeaponAmmoStock( weapon, (ammoReserves - difference ) );
				}
				else
				{
					self setWeaponAmmoClip( weapon, ammoInClip + ammoReserves );
					
					if ( ammoReserves - difference > 0 )
						self setWeaponAmmoStock( weapon, ( ammoReserves - difference ) );	
					else
						self setWeaponAmmoStock( weapon, 0 );
				}
			}
		}
	}

}

unsetDoubleLoad()
{	
	self notify( "endDoubleLoad" );
}


setMarksman()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self setRecoilScale( 10 );
	self.recoilScale = 10;
}

unsetMarksman()
{	
	self setRecoilScale( 0 );
	self.recoilScale = 0;
}


setStunResistance()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self.stunScaler = .5;
}

unsetStunResistance()
{	
	self.stunScaler = 1;
}

setSteadyAimPro()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self setaimspreadmovementscale( 0.5 );
}

unsetSteadyAimPro()
{
	self notify( "end_SteadyAimPro" );
	self setaimspreadmovementscale( 1.0 ); 
}

blastshieldUseTracker( perkName, useFunc )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "end_perkUseTracker" );
	level endon ( "game_ended" );

	for ( ;; )
	{
		self waittill ( "empty_offhand" );

		if ( !isOffhandWeaponEnabled() )
			continue;
			
		self [[useFunc]]( self _hasPerk( "_specialty_blastshield" ) );
	}
}

perkUseDeathTracker()
{
	self endon ( "disconnect" );
	
	self waittill("death");
	self._usePerkEnabled = undefined;
}

setRearView()
{
	//self thread perkUseTracker( "specialty_rearview", ::toggleRearView );
}

unsetRearView()
{
	self notify ( "end_perkUseTracker" );
}

/* NO LONGER FUNCTIONS
toggleRearView( isEnabled )
{
	if ( isEnabled )
	{
		self givePerk( "_specialty_rearview" );
		self SetRearViewRenderEnabled(true);
	}
	else
	{
		self _unsetPerk( "_specialty_rearview" );
		self SetRearViewRenderEnabled(false);
	}
}
*/

setEndGame()
{
	if ( isdefined( self.endGame ) )
		return;
		
	self.maxhealth = ( maps\mp\gametypes\_tweakables::getTweakableValue( "player", "maxhealth" ) * 4 );
	self.health = self.maxhealth;
	self.endGame = true;
	self.attackerTable[0] = "";
	self visionSetNakedForPlayer("end_game", 5 );
	self thread endGameDeath( 7 );
	self.hasDoneCombat = true;
}


unsetEndGame()
{
	self notify( "stopEndGame" );
	self.endGame = undefined;
	revertVisionSet();
	
	if (! isDefined( self.endGameTimer ) )
		return;
	
	self.endGameTimer destroyElem();
	self.endGameIcon destroyElem();		
}


revertVisionSet()
{
	if ( IsDefined( level.nukeDetonated ) )
		self VisionSetNakedForPlayer( level.nukeVisionSet, 1 );
	else
		self VisionSetNakedForPlayer( "", 1 ); // go to default visionset
}

endGameDeath( duration )
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "joined_team" );
	level endon( "game_ended" );
	self endon( "stopEndGame" );
		
	wait( duration + 1 );
	//self visionSetNakedForPlayer("end_game2", 1 );
	//wait(1);
	self _suicide();			
}

setSiege()
{
	self thread trackSiegeEnable();
	self thread trackSiegeDissable();
}

trackSiegeEnable()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "stop_trackSiege" );
	
	for ( ;; )
	{
		self waittill ( "gambit_on" );
		
		//self setStance( "crouch" );
		//self thread stanceStateListener();
		//self thread jumpStateListener();  
		self.moveSpeedScaler = 0;
		self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
		class = weaponClass( self getCurrentWeapon() );
		
		if ( class == "pistol" || class == "smg" ) 
			self setSpreadOverride( 1 );
		else
			self setSpreadOverride( 2 );
		
		self player_recoilScaleOn( 0 );
		self allowJump(false);	
	}	
}

trackSiegeDissable()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "stop_trackSiege" );
	
	for ( ;; )
	{
		self waittill ( "gambit_off" );
		
		unsetSiege();
	}	
}

stanceStateListener()
{
	self endon ( "death" );
	self endon ( "disconnect" );	
	
	self notifyOnPlayerCommand( "adjustedStance", "+stance" );

	for ( ;; )
	{
		self waittill( "adjustedStance" );
		if ( self.moveSPeedScaler != 0 )
			continue;
			
		unsetSiege();
	}
}

jumpStateListener()
{
	self endon ( "death" );
	self endon ( "disconnect" );	
	
	self notifyOnPlayerCommand( "jumped", "+goStand" );

	for ( ;; )
	{
		self waittill( "jumped" );
		if ( self.moveSPeedScaler != 0 )
			continue;
				
		unsetSiege();
	}
}

unsetSiege()
{
	self.moveSpeedScaler = 1;
	//if siege is not cut add check to see if
	//using lightweight and siege for movespeed scaler
	self resetSpreadOverride();
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
	self player_recoilScaleOff();
	self allowJump(true);
}

setChallenger()
{
	if ( !level.hardcoreMode )
	{
		self.maxhealth = maps\mp\gametypes\_tweakables::getTweakableValue( "player", "maxhealth" );
		
		if ( isDefined( self.xpScaler ) && self.xpScaler == 1 && self.maxhealth > 30 )
		{		
			self.xpScaler = 2;
		}	
	}
}

unsetChallenger()
{
	self.xpScaler = 1;
}


setSaboteur()
{
	self.objectiveScaler = 1.2;
}

unsetSaboteur()
{
	self.objectiveScaler = 1;
}


setLightWeight()
{
	self.moveSpeedScaler = lightWeightScalar();	
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
}

unsetLightWeight()
{
	self.moveSpeedScaler = 1;
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
}


setBlackBox()
{
	self.killStreakScaler = 1.5;
}

unsetBlackBox()
{
	self.killStreakScaler = 1;
}

setSteelNerves()
{
	self givePerk( "specialty_bulletaccuracy", true );
	self givePerk( "specialty_holdbreath", false );
}

unsetSteelNerves()
{
	self _unsetperk( "specialty_bulletaccuracy" );
	self _unsetperk( "specialty_holdbreath" );
}

setDelayMine()
{
}

unsetDelayMine()
{
}


setBackShield()
{
	self AttachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );	
}


unsetBackShield()
{
	self DetachShieldModel( "weapon_riot_shield_mp", "tag_shield_back" );
}


setLocalJammer()
{
	if ( !self isEMPed() )
		self RadarJamOn();
}


unsetLocalJammer()
{
	self RadarJamOff();
}


setAC130()
{
	self thread killstreakThink( "ac130", 7, "end_ac130Think" );
}

unsetAC130()
{
	self notify ( "end_ac130Think" );
}


setSentryMinigun()
{
	self thread killstreakThink( "airdrop_sentry_minigun", 2, "end_sentry_minigunThink" );
}

unsetSentryMinigun()
{
	self notify ( "end_sentry_minigunThink" );
}

setTank()
{
	self thread killstreakThink( "tank", 6, "end_tankThink" );
}

unsetTank()
{
	self notify ( "end_tankThink" );
}

setPrecision_airstrike()
{
	println( "!precision airstrike!" );
	self thread killstreakThink( "precision_airstrike", 6, "end_precision_airstrike" );
}

unsetPrecision_airstrike()
{
	self notify ( "end_precision_airstrike" );
}

setPredatorMissile()
{
	self thread killstreakThink( "predator_missile", 4, "end_predator_missileThink" );
}

unsetPredatorMissile()
{
	self notify ( "end_predator_missileThink" );
}


setHelicopterMinigun()
{
	self thread killstreakThink( "helicopter_minigun", 5, "end_helicopter_minigunThink" );
}

unsetHelicopterMinigun()
{
	self notify ( "end_helicopter_minigunThink" );
}



killstreakThink( streakName, streakVal, endonString )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( endonString );
	
	for ( ;; )
	{
		self waittill ( "killed_enemy" );
		
		if ( self.pers["cur_kill_streak"] != streakVal )
			continue;

		self thread maps\mp\killstreaks\_killstreaks::giveKillstreak( streakName );
		self thread maps\mp\gametypes\_hud_message::killstreakSplashNotify( streakName, streakVal );
		return;
	}
}


setThermal()
{
	self ThermalVisionOn();
}


unsetThermal()
{
	self ThermalVisionOff();
}


setOneManArmy()
{
	self thread oneManArmyWeaponChangeTracker();
}


unsetOneManArmy()
{
	self notify ( "stop_oneManArmyTracker" );
}


oneManArmyWeaponChangeTracker()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	self endon ( "stop_oneManArmyTracker" );
	
	for ( ;; )
	{
		self waittill( "weapon_change", newWeapon );

		if ( newWeapon != "onemanarmy_mp" )	
			continue;
	
		//if ( self isUsingRemote() )
		//	continue;
		
		self thread selectOneManArmyClass();	
	}
}


isOneManArmyMenu( menu )
{
	if ( menu == game["menu_onemanarmy"] )
		return true;

	if ( isDefined( game["menu_onemanarmy_defaults_splitscreen"] ) && menu == game["menu_onemanarmy_defaults_splitscreen"] )
		return true;

	if ( isDefined( game["menu_onemanarmy_custom_splitscreen"] ) && menu == game["menu_onemanarmy_custom_splitscreen"] )
		return true;

	return false;
}


selectOneManArmyClass()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self _disableWeaponSwitch();
	self _disableOffhandWeapons();
	self _disableUsability();
	
	self openPopupMenu( game["menu_onemanarmy"] );
	
	self thread closeOMAMenuOnDeath();
	
	self waittill ( "menuresponse", menu, className );

	self _enableWeaponSwitch();
	self _enableOffhandWeapons();
	self _enableUsability();
	
	if ( className == "back" || !isOneManArmyMenu( menu ) || self isUsingRemote() )
	{
		if ( self getCurrentWeapon() == "onemanarmy_mp" )
		{
			self _disableWeaponSwitch();
			self _disableOffhandWeapons();
			self _disableUsability();
			self switchToWeapon( self getLastWeapon() );
			self waittill ( "weapon_change" );
			self _enableWeaponSwitch();
			self _enableOffhandWeapons();
			self _enableUsability();
		}
		return;
	}	
	
	self thread giveOneManArmyClass( className );	
}

closeOMAMenuOnDeath()
{
	self endon ( "menuresponse" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	self waittill ( "death" );

	self _enableWeaponSwitch();
	self _enableOffhandWeapons();
	self _enableUsability();

	self closePopupMenu();
}

giveOneManArmyClass( className )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );

	if ( self _hasPerk( "specialty_omaquickchange" ) )
	{
		changeDuration = 3.0;
		self playLocalSound( "foly_onemanarmy_bag3_plr" );
		self playSoundToTeam( "foly_onemanarmy_bag3_npc", "allies", self );
		self playSoundToTeam( "foly_onemanarmy_bag3_npc", "axis", self );
	}
	else
	{
		changeDuration = 6.0;
		self playLocalSound( "foly_onemanarmy_bag6_plr" );
		self playSoundToTeam( "foly_onemanarmy_bag6_npc", "allies", self );
		self playSoundToTeam( "foly_onemanarmy_bag6_npc", "axis", self );
	}
		
	self thread omaUseBar( changeDuration );
		
	self _disableWeapon();
	self _disableOffhandWeapons();
	self _disableUsability();
	
	wait ( changeDuration );

	self _enableWeapon();
	self _enableOffhandWeapons();
	self _enableUsability();
	
	self.OMAClassChanged = true;

	self maps\mp\gametypes\_class::giveLoadout( self.pers["team"], className, false );
	
	// handle the fact that detachAll in giveLoadout removed the CTF flag from our back
	// it would probably be better to handle this in _detachAll itself, but this is a safety fix
	if ( isDefined( self.carryFlag ) )
		self attach( self.carryFlag, "J_spine4", true );
	
	self notify ( "changed_kit" );
	level notify ( "changed_kit" );
}


omaUseBar( duration )
{
	self endon( "disconnect" );
	
	useBar = createPrimaryProgressBar( 0, -25 );
	useBarText = createPrimaryProgressBarText( 0, -25 );
	useBarText setText( &"MPUI_CHANGING_KIT" );

	useBar updateBar( 0, 1 / duration );
	for ( waitedTime = 0; waitedTime < duration && isAlive( self ) && !level.gameEnded; waitedTime += 0.066 )
		wait ( 0.05 );
	
	useBar destroyElem();
	useBarText destroyElem();
}


setBlastShield()
{
	//self thread blastshieldUseTracker( "specialty_blastshield", ::toggleBlastShield );
	//self givePerk( "_specialty_blastshield" );
	self SetWeaponHudIconOverride( "primaryoffhand", "specialty_blastshield" );
}


unsetBlastShield()
{
	//self notify ( "end_perkUseTracker" );
	//self _unsetPerk( "_specialty_blastshield" );
	self SetWeaponHudIconOverride( "primaryoffhand", "none" );
}

//toggleBlastShield( isEnabled )
//{
//	if ( !isEnabled )
//	{
//		self VisionSetNakedForPlayer( "black_bw", 0.15 );
//		wait ( 0.15 );
//		self givePerk( "_specialty_blastshield" );
//		self VisionSetNakedForPlayer( "", 0 ); // go to default visionset
//		self playSoundToPlayer( "item_blast_shield_on", self );
//	}
//	else
//	{
//		self VisionSetNakedForPlayer( "black_bw", 0.15 );
//		wait ( 0.15 );	
//		self _unsetPerk( "_specialty_blastshield" );
//		self VisionSetNakedForPlayer( "", 0 ); // go to default visionset
//		self playSoundToPlayer( "item_blast_shield_off", self );
//	}
//}


setFreefall()
{
	//eventually set a listener to do a roll when falling damage is taken
}

unsetFreefall()
{
}


setTacticalInsertion()
{
	self SetOffhandSecondaryClass( "flash" );
	self _giveWeapon( "flare_mp", 0 );
	self giveStartAmmo( "flare_mp" );
	
	self thread monitorTIUse();
}

unsetTacticalInsertion()
{
	self notify( "end_monitorTIUse" );
}

clearPreviousTISpawnpoint()
{
	self waittill_any ( "disconnect", "joined_team", "joined_spectators" );
	
	if ( isDefined ( self.setSpawnpoint ) )
		self deleteTI( self.setSpawnpoint );
}

updateTISpawnPosition()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	self endon ( "end_monitorTIUse" );
	
	while ( isReallyAlive( self ) )
	{
		if ( self isValidTISpawnPosition() )
			self.TISpawnPosition = self.origin;

		wait ( 0.05 );
	}
}

isValidTISpawnPosition()
{
	if ( CanSpawn( self.origin ) && self IsOnGround() )
		return true;
	else
		return false;
}

monitorTIUse()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	self endon ( "end_monitorTIUse" );

	self thread updateTISpawnPosition();
	self thread clearPreviousTISpawnpoint();
	
	for ( ;; )
	{
		self waittill( "grenade_fire", lightstick, weapName );
				
		if ( weapName != "flare_mp" )
			continue;
		
		//lightstick delete();
		
		if ( isDefined( self.setSpawnPoint ) )
			self deleteTI( self.setSpawnPoint );

		if ( !isDefined( self.TISpawnPosition ) )
			continue;

		if ( self touchingBadTrigger() )
			continue;

		TIGroundPosition = playerPhysicsTrace( self.TISpawnPosition + (0,0,16), self.TISpawnPosition - (0,0,2048) ) + (0,0,1);
		
		glowStick = spawn( "script_model", TIGroundPosition );
		glowStick.angles = self.angles;
		glowStick.team = self.team;
		glowStick.owner = self;
		glowStick.enemyTrigger =  spawn( "script_origin", TIGroundPosition );
		glowStick thread GlowStickSetupAndWaitForDeath( self );
		glowStick.playerSpawnPos = self.TISpawnPosition;
		
		glowStick thread maps\mp\gametypes\_weapons::createBombSquadModel( level.spawnGlowModel["friendly"], "tag_fire_fx", level.otherTeam[self.team], self );
		
		self.setSpawnPoint = glowStick;		
		return;
	}
}


GlowStickSetupAndWaitForDeath( owner )
{
	self setModel( level.spawnGlowModel["enemy"] );
	if ( level.teamBased )
		self maps\mp\_entityheadIcons::setTeamHeadIcon( self.team , (0,0,20) );
	else
		self maps\mp\_entityheadicons::setPlayerHeadIcon( owner, (0,0,20) );

	self thread GlowStickDamageListener( owner );
	self thread GlowStickEnemyUseListener( owner );
	self thread GlowStickUseListener( owner );
	self thread GlowStickTeamUpdater( level.otherTeam[self.team], level.spawnGlow["enemy"], owner );	

	dummyGlowStick = spawn( "script_model", self.origin+ (0,0,0) );
	dummyGlowStick.angles = self.angles;
	dummyGlowStick setModel( level.spawnGlowModel["friendly"] );
	dummyGlowStick setContents( 0 );
	dummyGlowStick thread GlowStickTeamUpdater( self.team, level.spawnGlow["friendly"], owner );
	
	dummyGlowStick playLoopSound( "emt_road_flare_burn" );

	self waittill ( "death" );
	
	dummyGlowStick stopLoopSound();
	dummyGlowStick delete();
}


GlowStickTeamUpdater( showForTeam, showEffect, owner )
{
	self endon ( "death" );
	
	// PlayFXOnTag fails if run on the same frame the parent entity was created
	wait ( 0.05 );
	
	//PlayFXOnTag( showEffect, self, "TAG_FX" );
	angles = self getTagAngles( "tag_fire_fx" );
	fxEnt = SpawnFx( showEffect, self getTagOrigin( "tag_fire_fx" ), anglesToForward( angles ), anglesToUp( angles ) );
	TriggerFx( fxEnt );
	
	self thread deleteOnDeath( fxEnt );
	
	for ( ;; )
	{
		self hide();
		fxEnt hide();
		foreach ( player in level.players )
		{
			if ( player.team == showForTeam && level.teamBased )
			{
				self showToPlayer( player );
				fxEnt showToPlayer( player );
			}
			else if ( !level.teamBased && player == owner && showEffect == level.spawnGlow["friendly"] )
			{
				self showToPlayer( player );
				fxEnt showToPlayer( player );
			}
			else if ( !level.teamBased && player != owner && showEffect == level.spawnGlow["enemy"] )
			{
				self showToPlayer( player );
				fxEnt showToPlayer( player );
			}
		}
		
		level waittill_either ( "joined_team", "player_spawned" );
	}
}

deleteOnDeath( ent )
{
	self waittill( "death" );
	if ( isdefined( ent ) )
		ent delete();
}

GlowStickDamageListener( owner )
{
	self endon ( "death" );

	self setCanDamage( true );
	// use a health buffer to prevent dying to friendly fire
	self.health = 999999; // keep it from dying anywhere in code
	self.maxHealth = 100; // this is the health we'll check
	self.damageTaken = 0; // how much damage has it taken

	while( true )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, iDFlags, weapon );

		// don't allow people to destroy equipment on their team if FF is off
		if ( !maps\mp\gametypes\_weapons::friendlyFireCheck( self.owner, attacker ) )
			continue;

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			case "concussion_grenade_mp":
			case "flash_grenade_mp":
			case "smoke_grenade_mp":
				continue;
			}
		}

		if ( !isdefined( self ) )
			return;

		if ( type == "MOD_MELEE" )
			self.damageTaken += self.maxHealth;

		if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
			self.wasDamagedFromBulletPenetration = true;

		self.wasDamaged = true;

		self.damageTaken += damage;

		if( isPlayer( attacker ) )
		{
			attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "tactical_insertion" );
		}

		if ( self.damageTaken >= self.maxHealth )
		{
			if ( isDefined( owner ) && attacker != owner )
			{
				attacker notify ( "destroyed_insertion", owner );
				attacker notify( "destroyed_explosive" ); // count towards SitRep Pro challenge
				owner thread leaderDialogOnPlayer( "ti_destroyed" );
			}
			
			attacker thread deleteTI( self );
		}
	}
}

GlowStickUseListener( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	
	self setCursorHint( "HINT_NOICON" );
	self setHintString( &"MP_PICKUP_TI" );
	
	self thread updateEnemyUse( owner );

	for ( ;; )
	{
		self waittill ( "trigger", player );
		
		player playSound( "chemlight_pu" );
		player thread setTacticalInsertion();
		player thread deleteTI( self );
	}
}

updateEnemyUse( owner )
{
	self endon ( "death" );
	
	for ( ;; )
	{
		self setSelfUsable( owner );
		level waittill_either ( "joined_team", "player_spawned" );
	}
}

deleteTI( TI )
{
	if (isDefined( TI.enemyTrigger ) )
		TI.enemyTrigger Delete();
	
	spot = TI.origin;
	spotAngles = TI.angles;
	
	TI Delete();
	
	dummyGlowStick = spawn( "script_model", spot );
	dummyGlowStick.angles = spotAngles;
	dummyGlowStick setModel( level.spawnGlowModel["friendly"] );
	
	dummyGlowStick setContents( 0 );
	thread dummyGlowStickDelete( dummyGlowStick );
}

dummyGlowStickDelete( stick )
{
	wait(2.5);
	stick Delete();
}

GlowStickEnemyUseListener( owner )
{
	self endon ( "death" );
	level endon ( "game_ended" );
	owner endon ( "disconnect" );
	
	self.enemyTrigger setCursorHint( "HINT_NOICON" );
	self.enemyTrigger setHintString( &"MP_DESTROY_TI" );
	self.enemyTrigger makeEnemyUsable( owner );
	
	for ( ;; )
	{
		self.enemyTrigger waittill ( "trigger", player );
		
		player notify ( "destroyed_insertion", owner );
		player notify( "destroyed_explosive" ); // count towards SitRep Pro challenge

		//playFX( level.spawnGlowSplat, self.origin);		
		
		if ( isDefined( owner ) && player != owner )
			owner thread leaderDialogOnPlayer( "ti_destroyed" );

		player thread deleteTI( self );
	}	
}

setLittlebirdSupport()
{
	self thread killstreakThink( "littlebird_support", 2, "end_littlebird_support_think" );
}

unsetLittlebirdSupport()
{
	self notify ( "end_littlebird_support_think" );
}

setPainted() // self == victim
{
	// this is called from cac_modified_damage, not the perk functions
	if( IsPlayer( self ) )
	{
		paintedTime = 10.0;
		// half the time if they have the anti-perk (whatever it may be)
		if( self _hasPerk( "specialty_quieter" ) )
			paintedTime *= 0.5;

		self.painted = true;
		self setPerk( "specialty_radararrow", true, false );

		self thread unsetPainted( paintedTime );
		self thread watchPaintedDeath();
	}
}

watchPaintedDeath()
{
	self endon( "disconnect" );
	level endon( "game_ended" );

	self waittill( "death" );

	self.painted = false;
}

unsetPainted( time )
{
	self notify( "painted_again" );
	self endon( "painted_again" );

	self endon( "disconnect" );
	self endon( "death" );
	level endon( "game_ended" );

	wait( time );

	self.painted = false;
	self unsetPerk( "specialty_radararrow", true );
}

isPainted()
{
	return ( IsDefined( self.painted ) && self.painted );
}

/***************************************************************************************************************
*	DEATH STREAKS
***************************************************************************************************************/


/////////////////////////////////////////////////////////////////
// FINAL STAND: the player falls into last stand but can get back up if they survive long enough
setFinalStand()
{
	self givePerk( "specialty_pistoldeath", false );
}

unsetFinalStand()
{
	self _unsetperk( "specialty_pistoldeath" );
}
// END FINAL STAND
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// CARE PACKAGE: give the player a care package on spawn
setCarePackage()
{
	self thread maps\mp\killstreaks\_killstreaks::giveKillstreak( "airdrop_assault", false, false, self, true );
}

unsetCarePackage()
{

}
// END CARE PACKAGE
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// UAV: give the player a uav on spawn
setUAV()
{
	self thread maps\mp\killstreaks\_killstreaks::giveKillstreak( "uav", false, false, self, true );
}

unsetUAV()
{

}
// END CARE PACKAGE
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// STOPPING POWER: give the player more bullet damage
setStoppingPower()
{
	self givePerk( "specialty_bulletdamage", false );
	self thread watchStoppingPowerKill();
}

watchStoppingPowerKill()
{
	self notify( "watchStoppingPowerKill" );
	self endon( "watchStoppingPowerKill" );
	self endon( "disconnect" );
	level endon( "game_ended" );

	self waittill( "killed_enemy" );

	self unsetStoppingPower();
}

unsetStoppingPower()
{
	self _unsetperk( "specialty_bulletdamage" );
	self notify( "watchStoppingPowerKill" );
}
// END STOPPING POWER
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// C4 DEATH: player falls into last stand with a c4 clacker for an explosive ending
setC4Death()
{
	if( !self _hasperk( "specialty_pistoldeath" ) )
		self givePerk( "specialty_pistoldeath", false );
}

unsetC4Death()
{
	if( self _hasperk( "specialty_pistoldeath" ) )
		self _unsetperk( "specialty_pistoldeath" );
}
// END C4 DEATH
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// JUICED: give a speed boost for a set amount of time
setJuiced()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "unset_juiced" );
	level endon( "end_game" );
	
	timeout = 0;
	//wait until the player is streamed in or until 10 seconds have passed
	while( self IsPlayerStreaming() && timeout < 10 )
	{
		timeout = timeout + 0.066;
		wait 0.066;
	}
		
	self.moveSpeedScaler = 1.25;
	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();
	
	if ( level.splitscreen )
	{
		yOffset = 56;
		iconSize = 21; // 32/1.5
	}
	else
	{
		yOffset = 80;
		iconSize = 32;
	}
	
	//self.juicedOverlay = newClientHudElem( self );
	//self.juicedOverlay.x = 0;
	//self.juicedOverlay.y = 0;
	//self.juicedOverlay.alignX = "left";
	//self.juicedOverlay.alignY = "top";
	//self.juicedOverlay.horzAlign = "fullscreen";
	//self.juicedOverlay.vertAlign = "fullscreen";
	//self.juicedOverlay setshader ( "combathigh_overlay", 640, 480 );
	//self.juicedOverlay.sort = -10;
	//self.juicedOverlay.archived = true;
	//self.juicedOverlay.alpha = 0.0;	
	//self.juicedOverlay fadeOverTime( 1.0 );
	//self.juicedOverlay.alpha = 1.0;

	self.juicedTimer = createTimer( "hudsmall", 1.0 );
	self.juicedTimer setPoint( "CENTER", "CENTER", 0, yOffset );
	self.juicedTimer setTimer( 7.0 );
	self.juicedTimer.color = (.8,.8,0);
	self.juicedTimer.archived = false;
	self.juicedTimer.foreground = true;

	self.juicedIcon = self createIcon( "specialty_juiced", iconSize, iconSize );
	self.juicedIcon.alpha = 0;
	self.juicedIcon setParent( self.juicedTimer );
	self.juicedIcon setPoint( "BOTTOM", "TOP" );
	self.juicedIcon.archived = true;
	self.juicedIcon.sort = 1;
	self.juicedIcon.foreground = true;
	self.juicedIcon fadeOverTime( 1.0 );
	self.juicedIcon.alpha = 0.85;
	
	self thread unsetJuicedOnDeath();
	self thread unsetJuicedOnRide();
	
	wait 5;

	if( IsDefined( self.juicedIcon ) )
	{
		self.juicedIcon	fadeOverTime( 2.0 );
		self.juicedIcon.alpha = 0.0;
	}	
	//if( IsDefined( self.juicedOverlay ) )
	//{
	//	self.juicedOverlay fadeOverTime( 2.0 );
	//	self.juicedOverlay.alpha = 0.0;
	//}
	if( IsDefined( self.juicedTimer ) )
	{
		self.juicedTimer fadeOverTime( 2.0 );
		self.juicedTimer.alpha = 0.0;
	}

	wait 2;

	self unsetJuiced();
}

unsetJuiced()
{	
	self.moveSpeedScaler = 1;
	if ( self _hasPerk( "specialty_lightweight" ) )
		self.moveSpeedScaler = lightWeightScalar();

	self maps\mp\gametypes\_weapons::updateMoveSpeedScale();

	if( IsDefined( self.juicedIcon ) )
	{
		self.juicedIcon	Destroy();
	}	
	//if( IsDefined( self.juicedOverlay ) )
	//{
	//	self.juicedOverlay Destroy();
	//}
	if( IsDefined( self.juicedTimer ) )
	{
		self.juicedTimer Destroy();
	}
	
	self notify("unset_juiced");
}

unsetJuicedOnRide()
{
	self endon ( "disconnect" );
	self endon ( "unset_juiced" );
	
	for ( ;; )
	{
		wait( 0.05 );
		
		if ( self isUsingRemote() )
		{
			self thread unsetJuiced();
			break;
		}
	}
	
}

unsetJuicedOnDeath()
{
	self endon ( "disconnect" );
	self endon ( "unset_juiced" );
	
	self waittill ( "death" );
	
	self thread unsetJuiced();
}
// END JUICED
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// COMBAT HIGH: painkiller, give a health boost for a set time
setCombatHigh()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "unset_combathigh" );
	level endon( "end_game" );

	self.damageBlockedTotal = 0;
	//self visionSetNakedForPlayer( "end_game", 1 );

	if ( level.splitscreen )
	{
		yOffset = 56;
		iconSize = 21; // 32/1.5
	}
	else
	{
		yOffset = 112;
		iconSize = 32;
	}

	// since we can have more than one deathstreak, juiced might have an overlay and timer up, so delete them
	//if( IsDefined( self.juicedOverlay ) )
	//	self.juicedOverlay Destroy();
	if( IsDefined( self.juicedTimer ) )
		self.juicedTimer Destroy();
	if( IsDefined( self.juicedIcon ) )
		self.juicedIcon Destroy();

	self.combatHighOverlay = newClientHudElem( self );
	self.combatHighOverlay.x = 0;
	self.combatHighOverlay.y = 0;
	self.combatHighOverlay.alignX = "left";
	self.combatHighOverlay.alignY = "top";
	self.combatHighOverlay.horzAlign = "fullscreen";
	self.combatHighOverlay.vertAlign = "fullscreen";
	self.combatHighOverlay setshader ( "combathigh_overlay", 640, 480 );
	self.combatHighOverlay.sort = -10;
	self.combatHighOverlay.archived = true;

	self.combatHighTimer = createTimer( "hudsmall", 1.0 );
	self.combatHighTimer setPoint( "CENTER", "CENTER", 0, yOffset );
	self.combatHighTimer setTimer( 10.0 );
	self.combatHighTimer.color = (.8,.8,0);
	self.combatHighTimer.archived = false;
	self.combatHighTimer.foreground = true;

	self.combatHighIcon = self createIcon( "specialty_painkiller", iconSize, iconSize );
	self.combatHighIcon.alpha = 0;
	self.combatHighIcon setParent( self.combatHighTimer );
	self.combatHighIcon setPoint( "BOTTOM", "TOP" );
	self.combatHighIcon.archived = true;
	self.combatHighIcon.sort = 1;
	self.combatHighIcon.foreground = true;

	self.combatHighOverlay.alpha = 0.0;	
	self.combatHighOverlay fadeOverTime( 1.0 );
	self.combatHighIcon fadeOverTime( 1.0 );
	self.combatHighOverlay.alpha = 1.0;
	self.combatHighIcon.alpha = 0.85;

	self thread unsetCombatHighOnDeath();
	self thread unsetCombatHighOnRide();

	wait( 8 );

	self.combatHighIcon	fadeOverTime( 2.0 );
	self.combatHighIcon.alpha = 0.0;

	self.combatHighOverlay fadeOverTime( 2.0 );
	self.combatHighOverlay.alpha = 0.0;

	self.combatHighTimer fadeOverTime( 2.0 );
	self.combatHighTimer.alpha = 0.0;

	wait( 2 );
	self.damageBlockedTotal = undefined;

	self _unsetPerk( "specialty_combathigh" );
}

unsetCombatHighOnDeath()
{
	self endon ( "disconnect" );
	self endon ( "unset_combathigh" );

	self waittill ( "death" );

	self thread _unsetPerk( "specialty_combathigh" );
}

unsetCombatHighOnRide()
{
	self endon ( "disconnect" );
	self endon ( "unset_combathigh" );

	for ( ;; )
	{
		wait( 0.05 );

		if ( self isUsingRemote() )
		{
			self thread _unsetPerk( "specialty_combathigh" );
			break;
		}
	}
}

unsetCombatHigh()
{
	self notify ( "unset_combathigh" );
	self.combatHighOverlay destroy();
	self.combatHighIcon destroy();
	self.combatHighTimer destroy();
}
// END COMBAT HIGH
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// LIGHT ARMOR: give a health boost
setLightArmor()
{
	self thread giveLightArmor();
}

giveLightArmor()
{
	self notify( "give_light_armor" );
	self endon( "give_light_armor" );
	self endon ( "death" );
	self endon( "disconnect" );
	level endon( "end_game" );

	if ( isDefined( self.hasLightArmor ) && self.hasLightArmor == true )
		removeLightArmor( self.previousMaxHealth );

	lightArmorHP = 200;

	self thread removeLightArmorOnDeath();	
	self.hasLightArmor = true;

	self.combatHighOverlay = newClientHudElem( self );
	self.combatHighOverlay.x = 0;
	self.combatHighOverlay.y = 0;
	self.combatHighOverlay.alignX = "left";
	self.combatHighOverlay.alignY = "top";
	self.combatHighOverlay.horzAlign = "fullscreen";
	self.combatHighOverlay.vertAlign = "fullscreen";
	self.combatHighOverlay setshader ( "combathigh_overlay", 640, 480 );
	self.combatHighOverlay.sort = -10;
	self.combatHighOverlay.archived = true;	

	self.previousMaxHealth = self.maxhealth;
	self.maxhealth = lightArmorHP;
	self.health = self.maxhealth;

	sheildHealth = 50;
	previousHealth = self.health;

	for (;;)
	{
		if ( self.maxhealth != lightArmorHP )
		{
			removeLightArmor();
			break;
		}

		if ( self.health < 100 )
		{
			removeLightArmor( self.previousMaxHealth );
			break;
		}

		if ( self.health < previousHealth )
		{
			sheildHealth -= ( previousHealth - self.health );
			previousHealth = self.health;
			if ( sheildHealth <= 0 )
			{
				removeLightArmor( self.previousMaxHealth );
				break;
			}
		}

		wait( 0.5 );
	}
}

removeLightArmorOnDeath()
{
	self endon ( "disconnect" );
	self endon( "give_light_armor" );
	self endon( "remove_light_armor" );

	self waittill ( "death" );
	removeLightArmor();		
}

removeLightArmor( maxHealth )
{
	if ( isDefined( maxHealth ) )
		self.maxhealth = maxHealth;

	if ( isDefined( self.combatHighOverlay ) )
		self.combatHighOverlay destroy();

	self.hasLightArmor = undefined;

	self notify( "remove_light_armor" );
}

unsetLightArmor()
{
	self thread removeLightArmor( self.previousMaxHealth );
}
// END LIGHT ARMOR
/////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////
// REVENGE: show the last player who killed you, on your mini-map or in the world with a head icon
setRevenge() // this version does the head icon
{
	self notify( "stopRevenge" );
	wait( 0.05 ); // let all of the already running threads stop and clean up

	if( !IsDefined( self.lastKilledBy ) )
		return;

	if( self.team == self.lastKilledBy.team )
		return;

	revengeParams = SpawnStruct();
	revengeParams.showTo = self;
	revengeParams.icon = "compassping_revenge";
	revengeParams.offset = ( 0, 0, 64 );
	revengeParams.width = 10;
	revengeParams.height = 10;
	revengeParams.archived = false;
	revengeParams.delay = 1.5;
	revengeParams.constantSize = false;
	revengeParams.pinToScreenEdge = true;
	revengeParams.fadeOutPinnedIcon = false;
	revengeParams.is3D = false;
	self.revengeParams = revengeParams;

	self.lastKilledBy maps\mp\_entityheadIcons::setHeadIcon( 
		revengeParams.showTo, 
		revengeParams.icon, 
		revengeParams.offset, 
		revengeParams.width, 
		revengeParams.height, 
		revengeParams.archived, 
		revengeParams.delay, 
		revengeParams.constantSize, 
		revengeParams.pinToScreenEdge, 
		revengeParams.fadeOutPinnedIcon,
		revengeParams.is3D );
	
	self thread watchRevengeDeath();
	self thread watchRevengeKill();
	self thread watchRevengeDisconnected();
	self thread watchRevengeVictimDisconnected();
	self thread watchStopRevenge();
}

//setRevenge() // this version does the mini-map objective
//{
//	self notify( "stopRevenge" );
//	wait( 0.05 ); // let all of the already running threads stop and clean up
//
//	if( !IsDefined( self.lastKilledBy ) )
//		return;
//
//	// show objective only to a single player, not the whole team
//	curObjID = maps\mp\gametypes\_gameobjects::getNextObjID();	
//	Objective_Add( curObjID, "invisible", (0,0,0) );
//	Objective_OnEntity( curObjID, self.lastKilledBy );
//	Objective_State( curObjID, "active" );
//	Objective_Icon( curObjID, "compassping_revenge" );
//	Objective_Player( curObjID, self GetEntityNumber() );
//	self.objIdFriendly = curObjID;
//
//	self thread watchRevengeKill();
//	self thread watchRevengeDisconnected();
//	self thread watchRevengeVictimDisconnected();
//	self thread watchStopRevenge();
//}

watchRevengeDeath() // self == player with the deathstreak
{
	self endon( "stopRevenge" );
	self endon( "disconnect" );

	lastKilledBy = self.lastKilledBy;
	// since head icons get deleted on death, we need to keep giving this player a head icon until stop revenge
	while( true )
	{
		lastKilledBy waittill( "spawned_player" );
		lastKilledBy maps\mp\_entityheadIcons::setHeadIcon( 
			self.revengeParams.showTo, 
			self.revengeParams.icon, 
			self.revengeParams.offset, 
			self.revengeParams.width, 
			self.revengeParams.height, 
			self.revengeParams.archived, 
			self.revengeParams.delay, 
			self.revengeParams.constantSize, 
			self.revengeParams.pinToScreenEdge, 
			self.revengeParams.fadeOutPinnedIcon,
			self.revengeParams.is3D );
	}
}

watchRevengeKill()
{
	self endon( "stopRevenge" );

	self waittill( "killed_enemy" );

	self notify( "stopRevenge" );
}

watchRevengeDisconnected()
{
	self endon( "stopRevenge" );

	self.lastKilledBy waittill( "disconnect" );

	self notify( "stopRevenge" );
}

watchStopRevenge() // self == player with the deathstreak
{
	lastKilledBy = self.lastKilledBy;	
	
	// if the player gets any kill, then stop the revenge on the last killed by player
	// if the player dies again without getting any kills, have the new killer show and the old not	
	self waittill( "stopRevenge" );

	if( !IsDefined( lastKilledBy ) )
		return;

	foreach( key, headIcon in lastKilledBy.entityHeadIcons )
	{	
		if( !isDefined( headIcon ) )
			continue;

		headIcon destroy();
	}

	//if( isDefined( self.objIdFriendly ) )
	//	_objective_delete( self.objIdFriendly );
}

watchRevengeVictimDisconnected()
{
	// if the player with revenge gets disconnected then clean up
	objID = self.objIdFriendly;
	lastKilledBy = self.lastKilledBy;
	lastKilledBy endon( "disconnect" );
	level endon( "game_ended" );
	self endon( "stopRevenge" );

	self waittill( "disconnect" );

	if( !IsDefined( lastKilledBy ) )
		return;

	foreach( key, headIcon in lastKilledBy.entityHeadIcons )
	{	
		if( !isDefined( headIcon ) )
			continue;

		headIcon destroy();
	}

	//if( isDefined( objID ) )
	//	_objective_delete( objID );
}

unsetRevenge()
{	
	self notify( "stopRevenge" );
}
// END REVENGE
/////////////////////////////////////////////////////////////////


/***************************************************************************************************************
*	END DEATH STREAKS
***************************************************************************************************************/
