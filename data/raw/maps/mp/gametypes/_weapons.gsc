#include common_scripts\utility;
#include maps\mp\_utility;
#include maps\mp\gametypes\_equipment;

attachmentGroup( attachmentName )
{
	return tableLookup( "mp/attachmentTable.csv", 4, attachmentName, 2 );
}

getAttachmentList()
{
	attachmentList = [];
	
	index = 0;
	attachmentName = tableLookup( "mp/attachmentTable.csv", 9, index, 4 );
	
	while ( attachmentName != "" )
	{
		attachmentList[attachmentList.size] = attachmentName;
		
		index++;
		attachmentName = tableLookup( "mp/attachmentTable.csv", 9, index, 4 );
	}
	
	return alphabetize( attachmentList );
}

init()
{
	level.scavenger_altmode = true;
	level.scavenger_secondary = true;
	
	// 0 is not valid
	level.maxPerPlayerExplosives = max( getIntProperty( "scr_maxPerPlayerExplosives", 2 ), 1 );
	level.riotShieldXPBullets = getIntProperty( "scr_riotShieldXPBullets", 15 );

	switch ( getIntProperty( "perk_scavengerMode", 0 ) )
	{
		case 1: // disable altmode
			level.scavenger_altmode = false;
			break;

		case 2: // disable secondary
			level.scavenger_secondary = false;
			break;
			
		case 3: // disable altmode and secondary
			level.scavenger_altmode = false;
			level.scavenger_secondary = false;
			break;		
	}
	
	attachmentList = getAttachmentList();	
	
	// assigns weapons with stat numbers from 0-149
	// attachments are now shown here, they are per weapon settings instead
	
	max_weapon_num = 149;

	level.weaponList = [];
	for( weaponId = 0; weaponId <= max_weapon_num; weaponId++ )
	{
		weapon_name = tablelookup( "mp/statstable.csv", 0, weaponId, 4 );
		
		if( weapon_name == "" )
			continue;
		
		if ( !isSubStr( tableLookup( "mp/statsTable.csv", 0, weaponId, 2 ), "weapon_" ) )
			continue;
		
		if ( IsSubStr( weapon_name, "iw5_" ) )
		{
			weaponTokens = StrTok( weapon_name, "_" );
			weapon_name = weaponTokens[0] + "_" + weaponTokens[1] + "_mp";
			
			level.weaponList[level.weaponList.size] = weapon_name ;
			continue;
		}
		else
			level.weaponList[level.weaponList.size] = weapon_name + "_mp";
		
		/#
		if ( getDvar( "scr_dump_weapon_assets" ) != "" )
		{
			printLn( "" );
			printLn( "// " + weapon_name + " real assets" );
			printLn( "weapon,mp/" + weapon_name + "_mp" );
		}
		#/

		// the alphabetize function is slow so we try not to do it for every weapon/attachment combo; a code solution would be better.
		attachmentNames = [];
		for ( innerLoopCount = 0; innerLoopCount < 10; innerLoopCount++ )
		{
			// generating attachment combinations
			attachmentName = tablelookup( "mp/statStable.csv", 0, weaponId, innerLoopCount + 11 );
			
			if( attachmentName == "" )
				break;
			
			attachmentNames[attachmentName] = true;
		}

		// generate an alphabetized attachment list
		attachments = [];
		foreach ( attachmentName in attachmentList )
		{
			if ( !isDefined( attachmentNames[attachmentName] ) )
				continue;
				
			level.weaponList[level.weaponList.size] = weapon_name + "_" + attachmentName + "_mp";
			attachments[attachments.size] = attachmentName;
			/#
			if ( getDvar( "scr_dump_weapon_assets" ) != "" )
				println( "weapon,mp/" + weapon_name + "_" + attachmentName + "_mp" );
			#/
		}

		attachmentCombos = [];
		for ( i = 0; i < (attachments.size - 1); i++ )
		{
			colIndex = tableLookupRowNum( "mp/attachmentCombos.csv", 0, attachments[i] );
			for ( j = i + 1; j < attachments.size; j++ )
			{
				if ( tableLookup( "mp/attachmentCombos.csv", 0, attachments[j], colIndex ) == "no" )
					continue;
					
				attachmentCombos[attachmentCombos.size] = attachments[i] + "_" + attachments[j];
			}
		}

		/#
		if ( getDvar( "scr_dump_weapon_assets" ) != "" && attachmentCombos.size )
			println( "// " + weapon_name + " virtual assets" );
		#/
		
		foreach ( combo in attachmentCombos )
		{
			/#
			if ( getDvar( "scr_dump_weapon_assets" ) != "" )
				println( "weapon,mp/" + weapon_name + "_" + combo + "_mp" );
			#/

			level.weaponList[level.weaponList.size] = weapon_name + "_" + combo + "_mp";
		}
		
	} 

	foreach ( weaponName in level.weaponList )
	{
		precacheItem( weaponName );
		
		/#
		if ( getDvar( "scr_dump_weapon_assets" ) != "" )
		{
			altWeapon = weaponAltWeaponName( weaponName );
			if ( altWeapon != "none" )
				println( "weapon,mp/" + altWeapon );				
		}
		#/
	}

	precacheItem( "flare_mp" );
	precacheItem( "scavenger_bag_mp" );
	precacheItem( "frag_grenade_short_mp" );	
	precacheItem( "c4death_mp" );	
	precacheItem( "destructible_car" );
	precacheItem( "destructible_toy" );
	precacheItem( "bouncingbetty_mp" );
	precacheItem( "scrambler_mp" );
	precacheItem( "portable_radar_mp" );
	
	precacheShellShock( "default" );
	precacheShellShock( "concussion_grenade_mp" );
	thread maps\mp\_flashgrenades::main();
	thread maps\mp\_entityheadicons::init();
	thread maps\mp\_empgrenade::init();

	claymoreDetectionConeAngle = 70;
	level.claymoreDetectionDot = cos( claymoreDetectionConeAngle );
	level.claymoreDetectionMinDist = 20;
	level.claymoreDetectionGracePeriod = .75;
	level.claymoreDetonateRadius = 192;

	level.mineDetectionGracePeriod = .3;
	level.mineDetectionRadius = 100;
	level.mineDetectionHeight = 20;
	level.mineDamageRadius = 256;
	level.mineDamageMin = 70;
	level.mineDamageMax = 210;
	level.mineDamageHalfHeight = 46;
	level.mineSelfDestructTime = 120;
	level.mine_launch = loadfx( "impacts/bouncing_betty_launch_dirt" );
	level.mine_spin = loadfx( "dust/bouncing_betty_swirl" );
	level.mine_explode = loadfx( "explosions/bouncing_betty_explosion" );
	level.mine_beacon["enemy"] = loadfx( "misc/light_c4_blink" );
	level.mine_beacon["friendly"] = loadfx( "misc/light_mine_blink_friendly" );
	level.empGrenadeExplode = loadfx("explosions/emp_grenade");
	
	level.delayMineTime = 3.0;

	level.sentry_fire = loadfx( "muzzleflashes/shotgunflash" );
	
	// this should move to _stinger.gsc
	level.stingerFXid = loadfx ("explosions/aerial_explosion_large");

	// generating weapon type arrays which classifies the weapon as primary (back stow), pistol, or inventory (side pack stow)
	// using mp/statstable.csv's weapon grouping data ( numbering 0 - 149 )
	level.primary_weapon_array = [];
	level.side_arm_array = [];
	level.grenade_array = [];
	level.missile_array = [];
	level.inventory_array = [];
	level.mines = [];
	
	//*precacheModel( "weapon_claymore_bombsquad" );
	//*precacheModel( "weapon_c4_bombsquad" );
	//*precacheModel( "projectile_m67fraggrenade_bombsquad" );
	//*precacheModel( "projectile_semtex_grenade_bombsquad" );
	//*precacheModel( "weapon_light_stick_tactical_bombsquad" );
	precacheModel( "projectile_bouncing_betty_grenade" );
	//*precacheModel( "projectile_bouncing_betty_grenade_bombsquad" );
	precacheModel( "projectile_bouncing_betty_trigger" );
	precacheModel( "weapon_jammer" );
	//*precacheModel( "weapon_jammer_bombsquad" );
	precacheModel( "weapon_radar" );
	//*precacheModel( "weapon_radar_bombsquad" );
	PreCacheModel( "mp_trophy_system" );
	//*PreCacheModel( "mp_trophy_system_bombsquad" );

	//PrecacheMpAnim( "bouncing_betty_detonate" );
	
	level._effect[ "equipment_explode" ] = LoadFX( "explosions/sparks_a" );

	level._effect[ "sniperDustLarge" ] = LoadFX( "dust/sniper_dust_kickup" );
	level._effect[ "sniperDustSmall" ] = LoadFX( "dust/sniper_dust_kickup_minimal" );
	level._effect[ "sniperDustLargeSuppress" ] = LoadFX( "dust/sniper_dust_kickup_accum_suppress" );
	level._effect[ "sniperDustSmallSuppress" ] = LoadFX( "dust/sniper_dust_kickup_accum_supress_minimal" );

	level thread onPlayerConnect();
	
	level.c4explodethisframe = false;

	array_thread( getEntArray( "misc_turret", "classname" ), ::turret_monitorUse );
	
//	thread dumpIt();
}


dumpIt()
{
	
	wait ( 5.0 );
	/#
	max_weapon_num = 149;

	for( weaponId = 0; weaponId <= max_weapon_num; weaponId++ )
	{
		weapon_name = tablelookup( "mp/statstable.csv", 0, weaponId, 4 );
		if( weapon_name == "" )
			continue;
	
		if ( !isSubStr( tableLookup( "mp/statsTable.csv", 0, weaponId, 2 ), "weapon_" ) )
			continue;
			
		if ( getDvar( "scr_dump_weapon_challenges" ) != "" )
		{
			/*
			sharpshooter
			marksman
			veteran
			expert
			master
			*/

			weaponLStringName = tableLookup( "mp/statsTable.csv", 0, weaponId, 3 );
			weaponRealName = tableLookupIString( "mp/statsTable.csv", 0, weaponId, 3 );

			prefix = "WEAPON_";
			weaponCapsName = getSubStr( weaponLStringName, prefix.size, weaponLStringName.size );

			weaponGroup = tableLookup( "mp/statsTable.csv", 0, weaponId, 2 );
			
			weaponGroupSuffix = getSubStr( weaponGroup, prefix.size, weaponGroup.size );

			/*
			iprintln( "REFERENCE           TITLE_" + weaponCapsName + "_SHARPSHOOTER" );
			iprintln( "LANG_ENGLISH        ", weaponRealName, ": Sharpshooter" );
			iprintln( "" );
			iprintln( "REFERENCE           TITLE_" + weaponCapsName + "_MARKSMAN" );
			iprintln( "LANG_ENGLISH        ", weaponRealName, ": Marksman" );
			iprintln( "" );
			iprintln( "REFERENCE           TITLE_" + weaponCapsName + "_VETERAN" );
			iprintln( "LANG_ENGLISH        ", weaponRealName, ": Veteran" );
			iprintln( "" );
			iprintln( "REFERENCE           TITLE_" + weaponCapsName + "_EXPERT" );
			iprintln( "LANG_ENGLISH        ", weaponRealName, ": Expert" );
			iprintln( "" );
			iprintln( "REFERENCE           TITLE_" + weaponCapsName + "_Master" );
			iprintln( "LANG_ENGLISH        ", weaponRealName, ": Master" );
			*/
			
			iprintln( "cardtitle_" + weapon_name + "_sharpshooter,PLAYERCARDS_TITLE_" + weaponCapsName + "_SHARPSHOOTER,cardtitle_" + weaponGroupSuffix + "_sharpshooter,1,1,1" );
			iprintln( "cardtitle_" + weapon_name + "_marksman,PLAYERCARDS_TITLE_" + weaponCapsName + "_MARKSMAN,cardtitle_" + weaponGroupSuffix + "_marksman,1,1,1" );
			iprintln( "cardtitle_" + weapon_name + "_veteran,PLAYERCARDS_TITLE_" + weaponCapsName + "_VETERAN,cardtitle_" + weaponGroupSuffix + "_veteran,1,1,1" );
			iprintln( "cardtitle_" + weapon_name + "_expert,PLAYERCARDS_TITLE_" + weaponCapsName + "_EXPERT,cardtitle_" + weaponGroupSuffix + "_expert,1,1,1" );
			iprintln( "cardtitle_" + weapon_name + "_master,PLAYERCARDS_TITLE_" + weaponCapsName + "_MASTER,cardtitle_" + weaponGroupSuffix + "_master,1,1,1" );
			
			wait ( 0.05 );
		}
	}
	#/
}

bombSquadWaiter()
{
	self endon ( "disconnect" );
	
	for ( ;; )
	{
		self waittill ( "grenade_fire", weaponEnt, weaponName );
		
		team = level.otherTeam[self.team];
		
		if ( weaponName == "c4_mp" )
			weaponEnt thread createBombSquadModel( "weapon_c4", "tag_origin", team, self );
		else if ( weaponName == "claymore_mp" )
			weaponEnt thread createBombSquadModel( "weapon_claymore", "tag_origin", team, self );
		else if ( weaponName == "frag_grenade_mp" )
			weaponEnt thread createBombSquadModel( "projectile_m67fraggrenade", "tag_weapon", team, self );
		else if ( weaponName == "frag_grenade_short_mp" )
			weaponEnt thread createBombSquadModel( "projectile_m67fraggrenade", "tag_weapon", team, self );
		else if ( weaponName == "semtex_mp" )
			weaponEnt thread createBombSquadModel( "projectile_semtex_grenade", "tag_weapon", team, self );
	}
}


createBombSquadModel( modelName, tagName, teamName, owner )
{
	bombSquadModel = spawn( "script_model", (0,0,0) );
	bombSquadModel hide();
	wait ( 0.05 );
	
	if (!isDefined( self ) ) //grenade model may not be around if picked up
		return;
		
	bombSquadModel thread bombSquadVisibilityUpdater( teamName, owner );
	bombSquadModel setModel( modelName );
	bombSquadModel linkTo( self, tagName, (0,0,0), (0,0,0) );
	bombSquadModel SetContents( 0 );
	bombSquadModel SetSwitchToObjective( 1 );
	
	self waittill ( "death" );
	
	if ( isDefined(self.trigger) )
		self.trigger delete();
	
	bombSquadModel delete();
}


bombSquadVisibilityUpdater( teamName, owner )
{
	self endon ( "death" );

	foreach ( player in level.players )
	{
		if ( level.teamBased )
		{
			if ( player.team == teamName && player _hasPerk( "specialty_detectexplosive" ) )
				self showToPlayer( player );
		}
		else
		{
			if ( isDefined( owner ) && player == owner )
				continue;
			
			if ( !player _hasPerk( "specialty_detectexplosive" ) )
				continue;
				
			self showToPlayer( player );
		}		
	}
	
	for ( ;; )
	{
		level waittill_any( "joined_team", "player_spawned", "changed_kit" );
		
		self hide();

		foreach ( player in level.players )
		{
			if ( level.teamBased )
			{
				if ( player.team == teamName && player _hasPerk( "specialty_detectexplosive" ) )
					self showToPlayer( player );
			}
			else
			{
				if ( isDefined( owner ) && player == owner )
					continue;
				
				if ( !player _hasPerk( "specialty_detectexplosive" ) )
					continue;
					
				self showToPlayer( player );
			}		
		}
	}
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill("connected", player);

		player.hits = 0;
		player.hasDoneCombat = false;

		player KC_RegWeaponForFXRemoval( "remotemissile_projectile_mp" );

		player thread onPlayerSpawned();
		player thread bombSquadWaiter();
		player thread watchMissileUsage();
		player thread sniperDustWatcher();
	}
}

onPlayerSpawned()
{
	self endon("disconnect");

	for(;;)
	{
		self waittill("spawned_player");
		
		self.currentWeaponAtSpawn = self getCurrentWeapon(); // optimization so these threads we start don't have to call it.
		
		self.empEndTime = 0;
		self.concussionEndTime = 0;
		self.hits = 0;
		self.hasDoneCombat = false;
		if( !isdefined( self.trackingWeaponName ) )
		{
			self.trackingWeaponName = "";
			self.trackingWeaponName = "none";
			self.trackingWeaponShots = 0;
			self.trackingWeaponKills = 0;
			self.trackingWeaponHits = 0;
			self.trackingWeaponHeadShots = 0;
			self.trackingWeaponDeaths = 0;
		}
		self thread watchWeaponUsage();
		self thread watchGrenadeUsage();
		self thread watchWeaponChange();
		self thread watchStingerUsage();
		self thread watchJavelinUsage();
		self thread watchSentryUsage();
		self thread watchWeaponReload();
		self thread watchMineUsage();
		self thread maps\mp\gametypes\_class::trackRiotShield();
		self thread watchTrophyUsage();
		self thread stanceRecoilAdjuster();

		self.lastHitTime = [];
		
		self.droppedDeathWeapon = undefined;
		self.tookWeaponFrom = [];
		
		self thread updateSavedLastWeapon();
		
		self thread updateWeaponRank();

		if ( self hasWeapon( "semtex_mp" ) )
			self thread monitorSemtex();
		
		self.currentWeaponAtSpawn = undefined;
		self.trophyRemainingAmmo = undefined;
	}
}

sniperDustWatcher()
{
	self endon ( "death" );
	self endon ( "disconnect" );
	level endon ( "game_ended" );
	
	lastLargeShotFiredTime = undefined;
	
	for (;;)
	{
		self waittill( "weapon_fired" );
			
		if( getWeaponClass( self GetCurrentWeapon() ) != "weapon_sniper" )
			continue;
		
		if ( self GetStance() != "prone" )
			continue;
		
		playerForward = AnglesToForward( self.angles );
		//self thread drawLine( self.origin, ( self.origin + (0,0,10) ) + playerForward * 50, 10000, (1,0,0));
		
		if ( !isDefined(lastLargeShotFiredTime) || ( getTime() - lastLargeShotFiredTime ) > 2000 )
	 	{
	 		playFX( level._effect[ "sniperDustLarge" ], ( self.origin + (0,0,10) ) + playerForward * 50 , playerForward );
	 		lastLargeShotFiredTime = GetTime();
	 	}
	 	else
	 	{
	 		playFX( level._effect[ "sniperDustLargeSuppress" ], ( self.origin + (0,0,10) ) + playerForward * 50 , playerForward );
		}
	}
}


WatchStingerUsage()
{
	self maps\mp\_stinger::StingerUsageLoop();
}


WatchJavelinUsage()
{
	self maps\mp\_javelin::JavelinUsageLoop();
}

watchWeaponChange()
{
	self endon("death");
	self endon("disconnect");
	
	self thread watchStartWeaponChange();
	self.lastDroppableWeapon = self.currentWeaponAtSpawn;
	self.hitsThisMag = [];

	weapon = self getCurrentWeapon();
	
	if ( isCACPrimaryWeapon( weapon ) && !isDefined( self.hitsThisMag[ weapon ] ) )
		self.hitsThisMag[ weapon ] = weaponClipSize( weapon );

	self.bothBarrels = undefined;

	if ( isSubStr( weapon, "ranger" ) )
		self thread watchRangerUsage( weapon );

	while(1)
	{
		self waittill( "weapon_change", weaponName );
		
		if( weaponName == "none" )
			continue;
			
		if( weaponName == "briefcase_bomb_mp" || weaponName == "briefcase_bomb_defuse_mp" )
			continue;

		if( isKillstreakWeapon( weaponName ) )
			continue;

		weaponTokens = StrTok( weaponName, "_" );

		self.bothBarrels = undefined;

		if ( isSubStr( weaponName, "ranger" ) )
			self thread watchRangerUsage( weaponName );

		//if ( weaponTokens[0] == "iw5" )
		//weaponName = weaponTokens[0] + "_" + weaponTokens[1];
		if ( weaponTokens[0] == "alt" )
		{
			tmp = GetSubStr( weaponName, 4 );
			weaponName = tmp;
			weaponTokens = StrTok( weaponName, "_" );
		}
		else if ( weaponTokens[0] != "iw5" )
			weaponName = weaponTokens[0];

		if ( weaponName != "none" && weaponTokens[0] != "iw5" )
		{
			if ( isCACPrimaryWeapon( weaponName ) && !isDefined( self.hitsThisMag[ weaponName + "_mp" ] ) )
				self.hitsThisMag[ weaponName + "_mp" ] = weaponClipSize( weaponName + "_mp" );
		}
		else if( weaponName != "none" && weaponTokens[0] == "iw5")
		{
			if ( isCACPrimaryWeapon( weaponName ) && !isDefined( self.hitsThisMag[ weaponName ] ) )
				self.hitsThisMag[ weaponName ] = weaponClipSize( weaponName );	
		}
		
		self.changingWeapon = undefined;
		
		if ( weaponTokens[0] == "iw5" )
			self.lastDroppableWeapon = weaponName;
		else if ( weaponName != "none" && mayDropWeapon( weaponName + "_mp" ) )
			self.lastDroppableWeapon = weaponName + "_mp";

		// we need to manage the weapon buffs here, if the new weapon has a buff then give, if not, take
		if( IsDefined( self.class_num ) )
		{
			// since we stripped _mp off of the weapon name if it doesn't start with iw5, we need it back for this
			if( weaponTokens[0] != "iw5" )
				weaponName += "_mp";

			if( IsDefined( self.loadoutPrimaryBuff ) && self.loadoutPrimaryBuff != "specialty_null" )
			{
				if( weaponName == self.primaryWeapon && !( self _hasPerk( self.loadoutPrimaryBuff ) ) )
				{
					self givePerk( self.loadoutPrimaryBuff, true );
				}
				if( weaponName != self.primaryWeapon && self _hasPerk( self.loadoutPrimaryBuff ) )
				{
					self _unsetPerk( self.loadoutPrimaryBuff );
				}
			}

			if( IsDefined( self.loadoutSecondaryBuff ) && self.loadoutSecondaryBuff != "specialty_null" )
			{
				if( weaponName == self.secondaryWeapon && !( self _hasPerk( self.loadoutSecondaryBuff ) ) )
				{
					self givePerk( self.loadoutSecondaryBuff, true );
				}
				if( weaponName != self.secondaryWeapon && self _hasPerk( self.loadoutSecondaryBuff ) )
				{
					self _unsetPerk( self.loadoutSecondaryBuff );
				}
			}
		}
	}
}


watchStartWeaponChange()
{
	self endon("death");
	self endon("disconnect");
	self.changingWeapon = undefined;

	while(1)
	{
		self waittill( "weapon_switch_started", newWeapon );
		self.changingWeapon = newWeapon;

		// there's an issue where self.changingWeapon can get stuck on "none" if the owner captures but a full weapon_change doesn't happen
		if( newWeapon == "none" && IsDefined( self.isCapturingCrate ) && self.isCapturingCrate )
		{
			while( self.isCapturingCrate )
				wait( 0.05 );

			self.changingWeapon = undefined;
		}
	}
}

watchWeaponReload()
{
	self endon("death");
	self endon("disconnect");

	for ( ;; )
	{
		self waittill( "reload" );

		weaponName = self getCurrentWeapon();

		self.bothBarrels = undefined;
		
		if ( !isSubStr( weaponName, "ranger" ) )
			continue;

		self thread watchRangerUsage( weaponName );
	}
}


watchRangerUsage( rangerName )
{
	rightAmmo = self getWeaponAmmoClip( rangerName, "right" );
	leftAmmo = self getWeaponAmmoClip( rangerName, "left" );

	self endon ( "reload" );
	self endon ( "weapon_change" );

	for ( ;; )
	{
		self waittill ( "weapon_fired", weaponName );
		
		if ( weaponName != rangerName )
			continue;

		self.bothBarrels = undefined;

		if ( isSubStr( rangerName, "akimbo" ) )
		{
			newLeftAmmo = self getWeaponAmmoClip( rangerName, "left" );
			newRightAmmo = self getWeaponAmmoClip( rangerName, "right" );

			if ( leftAmmo != newLeftAmmo && rightAmmo != newRightAmmo )
				self.bothBarrels = true;
			
			if ( !newLeftAmmo || !newRightAmmo )
				return;
				
				
			leftAmmo = newLeftAmmo;
			rightAmmo = newRightAmmo;
		}
		else if ( rightAmmo == 2 && !self getWeaponAmmoClip( rangerName, "right" ) )
		{
			self.bothBarrels = true;
			return;
		}
	}
}


isHackWeapon( weapon )
{
	if ( weapon == "radar_mp" || weapon == "airstrike_mp" || weapon == "helicopter_mp" )
		return true;
	if ( weapon == "briefcase_bomb_mp" )
		return true;
	return false;
}


mayDropWeapon( weapon )
{
	if ( weapon == "none" )
		return false;
		
	if ( isSubStr( weapon, "ac130" ) )
		return false;
		
	if ( isSubStr( weapon, "uav" ) )
		return false;

	if ( isSubStr( weapon, "killstreak" ) )
		return false;

	invType = WeaponInventoryType( weapon );
	
	if ( invType != "primary" )
		return false;
	
	return true;
}

dropWeaponForDeath( attacker )
{
	if ( isDefined( level.blockWeaponDrops ) )
		return;
	
	if ( isdefined( self.droppedDeathWeapon ) )
		return;

	if ( level.inGracePeriod )
		return;
	
	weapon = self.lastDroppableWeapon;
	if ( !isdefined( weapon ) )
	{
		/#
		if ( getdvar("scr_dropdebug") == "1" )
			println( "didn't drop weapon: not defined" );
		#/
		return;
	}
	
	if ( weapon == "none" )
	{
		/#
		if ( getdvar("scr_dropdebug") == "1" )
			println( "didn't drop weapon: weapon == none" );
		#/
		return;
	}
	
	if ( !( self hasWeapon( weapon ) ) )
	{
		/#
		if ( getdvar("scr_dropdebug") == "1" )
			println( "didn't drop weapon: don't have it anymore (" + weapon + ")" );
		#/
		return;
	}
	
	// don't drop juggernaut weapons
	if( self isJuggernaut() )
		return;

	tokens = strTok( weapon, "_" );
	
	//passing weapon if the weapon is in alt mode.
	if ( tokens[0] == "alt" )
	{
		for( i = 0; i < tokens.size; i++ )
		{
			if( i > 0 && i < 2 )
				weapon += ( tokens[i] );
			else if( i > 0 )
				weapon += ( "_" + tokens[i] );
			else
				weapon = "";
		}
	}
	
	if ( weapon != "riotshield_mp" )
	{
		if ( !(self AnyAmmoForWeaponModes( weapon )) )
		{
			/#
			if ( getdvar("scr_dropdebug") == "1" )
			  println( "didn't drop weapon: no ammo for weapon modes" );
			#/
			return;
		}

		clipAmmoR = self GetWeaponAmmoClip( weapon, "right" );
		clipAmmoL = self GetWeaponAmmoClip( weapon, "left" );
		if ( !clipAmmoR && !clipAmmoL )
		{
			/#
			if ( getdvar("scr_dropdebug") == "1" )
			  println( "didn't drop weapon: no ammo in clip" );
			#/
			return;
		}
  
		stockAmmo = self GetWeaponAmmoStock( weapon );
		stockMax = WeaponMaxAmmo( weapon );
		if ( stockAmmo > stockMax )
			stockAmmo = stockMax;

		item = self dropItem( weapon );
		if ( !isDefined( item ) )
			return;

		item ItemWeaponSetAmmo( clipAmmoR, stockAmmo, clipAmmoL );
	}
	else
	{
		item = self dropItem( weapon );	
		if ( !isDefined( item ) )
			return;
		item ItemWeaponSetAmmo( 1, 1, 0 );
	}

	/#
	if ( getdvar("scr_dropdebug") == "1" )
		println( "dropped weapon: " + weapon );
	#/

	self.droppedDeathWeapon = true;

	item.owner = self;
	item.ownersattacker = attacker;

	item thread watchPickup();

	item thread deletePickupAfterAWhile();
}


detachIfAttached( model, baseTag )
{
	attachSize = self getAttachSize();
	
	for ( i = 0; i < attachSize; i++ )
	{
		attach = self getAttachModelName( i );
		
		if ( attach != model )
			continue;
		
		tag = self getAttachTagName( i );			
		self detach( model, tag );
		
		if ( tag != baseTag )
		{
			attachSize = self getAttachSize();
			
			for ( i = 0; i < attachSize; i++ )
			{
				tag = self getAttachTagName( i );
				
				if ( tag != baseTag )
					continue;
					
				model = self getAttachModelName( i );
				self detach( model, tag );
				
				break;
			}
		}		
		return true;
	}
	return false;
}


deletePickupAfterAWhile()
{
	self endon("death");
	
	wait 60;

	if ( !isDefined( self ) )
		return;

	self delete();
}

getItemWeaponName()
{
	classname = self.classname;
	assert( getsubstr( classname, 0, 7 ) == "weapon_" );
	weapname = getsubstr( classname, 7 );
	return weapname;
}

watchPickup()
{
	self endon("death");
	
	weapname = self getItemWeaponName();
	
	while(1)
	{
		self waittill( "trigger", player, droppedItem );
		
		if ( isdefined( droppedItem ) )
			break;
		// otherwise, player merely acquired ammo and didn't pick this up
	}
	
	/#
	if ( getdvar("scr_dropdebug") == "1" )
		println( "picked up weapon: " + weapname + ", " + isdefined( self.ownersattacker ) );
	#/

	assert( isdefined( player.tookWeaponFrom ) );
	
	// make sure the owner information on the dropped item is preserved
	droppedWeaponName = droppedItem getItemWeaponName();
	if ( isdefined( player.tookWeaponFrom[ droppedWeaponName ] ) )
	{
		droppedItem.owner = player.tookWeaponFrom[ droppedWeaponName ];
		droppedItem.ownersattacker = player;
		player.tookWeaponFrom[ droppedWeaponName ] = undefined;
	}
	droppedItem thread watchPickup();
	
	// take owner information from self and put it onto player
	if ( isdefined( self.ownersattacker ) && self.ownersattacker == player )
	{
		player.tookWeaponFrom[ weapname ] = self.owner;
	}
	else
	{
		player.tookWeaponFrom[ weapname ] = undefined;
	}
}

itemRemoveAmmoFromAltModes()
{
	origweapname = self getItemWeaponName();
	
	curweapname = weaponAltWeaponName( origweapname );
	
	altindex = 1;
	while ( curweapname != "none" && curweapname != origweapname )
	{
		self itemWeaponSetAmmo( 0, 0, 0, altindex );
		curweapname = weaponAltWeaponName( curweapname );
		altindex++;
	}
}


handleScavengerBagPickup( scrPlayer )
{
	self endon( "death" );
	level endon ( "game_ended" );

	assert( isDefined( scrPlayer ) );

	// Wait for the pickup to happen
	self waittill( "scavenger", destPlayer );
	assert( isDefined ( destPlayer ) );

	destPlayer notify( "scavenger_pickup" );
	destPlayer playLocalSound( "scavenger_pack_pickup" );		
		
	offhandWeapons = destPlayer getWeaponsListOffhands();
	foreach ( offhand in offhandWeapons )
	{		
		if ( offhand != "throwingknife_mp" )
			continue;
		
		currentClipAmmo = destPlayer GetWeaponAmmoClip( offhand );
		destPlayer SetWeaponAmmoClip( offhand, currentClipAmmo + 1);
	}

	primaryWeapons = destPlayer getWeaponsListPrimaries();	
	foreach ( primary in primaryWeapons )
	{
		if ( !isCACPrimaryWeapon( primary ) && !level.scavenger_secondary )
			continue;
		
		if ( isSubStr( primary, "alt" ) && ( isSubStr( primary, "m320" ) || isSubStr( primary, "gl" ) || isSubStr( primary, "gp25" ) || isSubStr( primary, "hybrid" ) ) )
			continue;
		
		//MW3 Scavenger no longer refills explosives
		if ( getWeaponClass( primary )== "weapon_projectile" )
			continue;
		
		currentStockAmmo = destPlayer GetWeaponAmmoStock( primary );
		addStockAmmo = weaponClipSize( primary );
		
		destPlayer setWeaponAmmoStock( primary, currentStockAmmo + addStockAmmo );
	}

	destPlayer maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "scavenger" );
}


dropScavengerForDeath( attacker )
{
	if ( level.inGracePeriod )
		return;
	
 	if( !isDefined( attacker ) )
 		return;

 	if( attacker == self )
 		return;

	dropBag = self dropScavengerBag( "scavenger_bag_mp" );	
	dropBag thread handleScavengerBagPickup( self );

}

getWeaponBasedGrenadeCount(weapon)
{
	return 2;
}

getWeaponBasedSmokeGrenadeCount(weapon)
{
	return 1;
}

getFragGrenadeCount()
{
	grenadetype = "frag_grenade_mp";

	count = self getammocount(grenadetype);
	return count;
}

getSmokeGrenadeCount()
{
	grenadetype = "smoke_grenade_mp";

	count = self getammocount(grenadetype);
	return count;
}

setWeaponStat( name, incValue, statName )
{
	self maps\mp\gametypes\_gamelogic::setWeaponStat(  name, incValue, statName );
}

watchWeaponUsage( weaponHand )
{
	self endon( "death" );
	self endon( "disconnect" );
	level endon ( "game_ended" );
	
	for ( ;; )
	{	
		self waittill ( "weapon_fired", weaponName );

		self.hasDoneCombat = true;

		if ( !maps\mp\gametypes\_weapons::isPrimaryWeapon( weaponName ) && !maps\mp\gametypes\_weapons::isSideArm( weaponName ) )
			continue;
		
		if ( isDefined( self.hitsThisMag[ weaponName ] ) )
			self thread updateMagShots( weaponName );
			
		totalShots = self maps\mp\gametypes\_persistence::statGetBuffered( "totalShots" ) + 1;
		hits = self maps\mp\gametypes\_persistence::statGetBuffered( "hits" );
		
		assert( totalShots > 0 );
		accuracy = Clamp( float( hits ) / float( totalShots ), 0.0, 1.0 ) * 10000.0;
		
		self maps\mp\gametypes\_persistence::statSetBuffered( "totalShots", totalShots );
		self maps\mp\gametypes\_persistence::statSetBuffered( "accuracy", int( accuracy ) );		
		self maps\mp\gametypes\_persistence::statSetBuffered( "misses", int( totalShots - hits ) );
		
		if ( isDefined( self.lastStandParams ) && self.lastStandParams.lastStandStartTime == getTime() )
	 	{
	 		self.hits = 0;
	 		return;
	 	}
	 	
	 	shotsFired = 1;
	 	self setWeaponStat( weaponName , shotsFired, "shots" );
	 	self setWeaponStat( weaponName , self.hits, "hits");
	 	
	 	self.hits = 0;
	}
}


updateMagShots( weaponName )
{
	self endon ( "death" );
	self endon ( "disconnect" );
	self endon ( "updateMagShots_" + weaponName );
	
	self.hitsThisMag[ weaponName ]--;
	
	wait ( 0.05 );
	
	self.hitsThisMag[ weaponName ] = weaponClipSize( weaponName );
}


checkHitsThisMag( weaponName )
{
	self endon ( "death" );
	self endon ( "disconnect" );

	self notify ( "updateMagShots_" + weaponName );
	waittillframeend;
	
	if ( isDefined( self.hitsThisMag[ weaponName ] ) && self.hitsThisMag[ weaponName ] == 0 )
	{
		weaponClass = getWeaponClass( weaponName );
		
		maps\mp\gametypes\_missions::genericChallenge( weaponClass );

		self.hitsThisMag[ weaponName ] = weaponClipSize( weaponName );
	}	
}


checkHit( weaponName, victim )
{
	if( isStrStart( weaponName, "alt_" ) )
	{
		tokens = strTok( weaponName, "_" );
		foreach( token in tokens )
		{
			if ( token == "shotgun" )
			{
				tmpWeaponName = GetSubStr( weaponName, 0, 4 );
				if ( !maps\mp\gametypes\_weapons::isPrimaryWeapon( tmpWeaponName ) && !maps\mp\gametypes\_weapons::isSideArm( tmpWeaponName ) )
					self.hits = 1;					
			}
			else if ( token == "hybrid" )
			{
				tmp = GetSubStr( weaponName, 4 );
				weaponName = tmp;
			}
		}
	}

	if ( !maps\mp\gametypes\_weapons::isPrimaryWeapon( weaponName ) && !maps\mp\gametypes\_weapons::isSideArm( weaponName ) )
		return;

	switch ( weaponClass( weaponName ) )
	{
		case "rifle":
		case "pistol":
		case "mg":
		case "smg":
			self.hits++;
			break;
		case "spread":
			self.hits = 1;
			break;
		default:
			break;
	}
	
	// sometimes the "weapon_fired" notify happens after we hit the guy...
	waittillframeend;

	if ( isDefined( self.hitsThisMag[ weaponName ] ) )
		self thread checkHitsThisMag( weaponName );

	if ( !isDefined( self.lastHitTime[ weaponName ] ) )
		self.lastHitTime[ weaponName ] = 0;
		
	// already hit with this weapon on this frame
	if ( self.lastHitTime[ weaponName ] == getTime() )
		return;

	self.lastHitTime[ weaponName ] = getTime();

	totalShots = self maps\mp\gametypes\_persistence::statGetBuffered( "totalShots" );		
	hits = self maps\mp\gametypes\_persistence::statGetBuffered( "hits" ) + 1;

	if ( hits <= totalShots )
	{
		self maps\mp\gametypes\_persistence::statSetBuffered( "hits", hits );
		self maps\mp\gametypes\_persistence::statSetBuffered( "misses", int(totalShots - hits) );
		self maps\mp\gametypes\_persistence::statSetBuffered( "accuracy", int(hits * 10000 / totalShots) );
	}
}


attackerCanDamageItem( attacker, itemOwner )
{
	return friendlyFireCheck( itemOwner, attacker );
}

// returns true if damage should be done to the item given its owner and the attacker
friendlyFireCheck( owner, attacker, forcedFriendlyFireRule )
{
	if ( !isdefined( owner ) )// owner has disconnected? allow it
		return true;

	if ( !level.teamBased )// not a team based mode? allow it
		return true;

	attackerTeam = attacker.team;

	friendlyFireRule = level.friendlyfire;
	if ( isdefined( forcedFriendlyFireRule ) )
		friendlyFireRule = forcedFriendlyFireRule;

	if ( friendlyFireRule != 0 )// friendly fire is on? allow it
		return true;

	if ( attacker == owner )// owner may attack his own items
		return true;

	if ( !isdefined( attackerTeam ) )// attacker not on a team? allow it
		return true;

	if ( attackerTeam != owner.team )// attacker not on the same team as the owner? allow it
		return true;

	return false;// disallow it
}

watchGrenadeUsage()
{
	self endon( "death" );
	self endon( "disconnect" );

	self.throwingGrenade = undefined;
	self.gotPullbackNotify = false;

	if ( getIntProperty( "scr_deleteexplosivesonspawn", 1 ) == 1 )
	{
		// delete c4 from previous spawn
		if ( isdefined( self.c4array ) )
		{
			for ( i = 0; i < self.c4array.size; i++ )
			{
				if ( isdefined( self.c4array[ i ] ) )
				{
					if ( isdefined( self.c4array[i].trigger ) )
						self.c4array[i].trigger delete();
						
					self.c4array[ i ] delete();
				}
			}
		}
		self.c4array = [];
		// delete claymores from previous spawn
		if ( isdefined( self.claymorearray ) )
		{
			for ( i = 0; i < self.claymorearray.size; i++ )
			{
				if ( isdefined( self.claymorearray[ i ] ) )
				{
					if ( isdefined( self.claymorearray[i].trigger ) )
						self.claymorearray[i].trigger delete();
					
					self.claymorearray[ i ] delete();
				}
			}
		}
		self.claymorearray = [];
		
		//delete bouncing bettys from previous spawn
		if ( isdefined( self.bouncingbettyArray ) )
		{
			for ( i = 0; i < self.bouncingbettyArray.size; i++ )
			{
				if ( isdefined( self.bouncingbettyArray[ i ] ) )
				{
					
					if ( isdefined( self.bouncingbettyArray[i].trigger ) )
						self.bouncingbettyArray[i].trigger delete();
					
					self.bouncingbettyArray[ i ] delete();
				}
			}
		}
		self.bouncingbettyArray = [];
	}
	else
	{
		if ( !isdefined( self.c4array ) )
			self.c4array = [];
		if ( !isdefined( self.claymorearray ) )
			self.claymorearray = [];
		if ( !isdefined( self.bouncingbettyArray ) )
			self.bouncingbettyArray = [];
	}

	thread watchC4();
	thread watchC4Detonation();
	thread watchC4AltDetonation();
	thread watchClaymores();
	thread deleteC4AndClaymoresOnDisconnect();

	self thread watchForThrowbacks();

	for ( ;; )
	{
		self waittill( "grenade_pullback", weaponName );
		
		self setWeaponStat( weaponName, 1, "shots" );

		self.hasDoneCombat = true;

		if ( weaponName == "claymore_mp" )
			continue;

		self.throwingGrenade = weaponName;
		self.gotPullbackNotify = true;
		
		if ( weaponName == "c4_mp" )
			self beginC4Tracking();
		else
			self beginGrenadeTracking();
			
		self.throwingGrenade = undefined;
	}
}

beginGrenadeTracking()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "offhand_end" );
	self endon( "weapon_change" );

	startTime = getTime();

	self waittill( "grenade_fire", grenade, weaponName );

	if ( ( getTime() - startTime > 1000 ) && weaponName == "frag_grenade_mp" )
		grenade.isCooked = true;

	self.changingWeapon = undefined;
	
	grenade.owner = self;

	switch( weaponName )
	{
	case "frag_grenade_mp":
	case "semtex_mp":
		grenade thread maps\mp\gametypes\_shellshock::grenade_earthQuake();
		grenade.originalOwner = self;
		break;
	case "flash_grenade_mp":
	case "concussion_grenade_mp":
		grenade thread empExplodeWaiter();
		break;
	case "smoke_grenade_mp":
		grenade thread watchSmokeExplode();
		break;
	}
}

watchSmokeExplode()	// self == smoke grenade
{
	level endon( "smokeTimesUp" );
	
	owner = self.owner;
	owner endon( "disconnect" );

	self waittill( "explode", position );

	smokeRadius = 128;
	smokeTime = 8;
	level thread waitSmokeTime( smokeTime, smokeRadius, position );

/#
	//maps\mp\killstreaks\_ac130::debug_circle( position, smokeRadius, smokeTime, ( 0, 0, 1 ) );
#/

	while( true )
	{
		if( !IsDefined( owner ) )
			break;

		foreach( player in level.players )
		{
			if( !IsDefined( player ) )
				continue;

			if( level.teamBased && player.team == owner.team )
				continue;

			if( DistanceSquared( player.origin, position ) < smokeRadius * smokeRadius )
				player.inPlayerSmokeScreen = owner;
			else
				player.inPlayerSmokeScreen = undefined;
		}

		wait( 0.05 );
	}
}

waitSmokeTime( smokeTime, smokeRadius, position )
{
	maps\mp\gametypes\_hostmigration::waitLongDurationWithHostMigrationPause( smokeTime );
	level notify( "smokeTimesUp" );
	waittillframeend;

	foreach( player in level.players )
	{
		if( IsDefined( player ) )
		{
			player.inPlayerSmokeScreen = undefined;
		}
	}

}

AddMissileToSightTraces( team )
{
	self.team = team;
	level.missilesForSightTraces[ level.missilesForSightTraces.size ] = self;
	
	self waittill( "death" );
	
	newArray = [];
	foreach( missile in level.missilesForSightTraces )
	{
		if ( missile != self )
			newArray[ newArray.size ] = missile;
	}
	level.missilesForSightTraces = newArray;
}

watchMissileUsage()
{
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "missile_fire", missile, weaponName );
		
		if ( isSubStr( weaponName, "gl_" ) )
		{
			missile.primaryWeapon = self getCurrentPrimaryWeapon();
			missile thread maps\mp\gametypes\_shellshock::grenade_earthQuake();
		}

		switch ( weaponName )
		{
			case "at4_mp":
			case "iw5_smaw_mp":
			case "stinger_mp":
				level notify ( "stinger_fired", self, missile, self.stingerTarget );
				self thread setAltSceneObj( missile, "tag_origin", 65 );
				break;
			case "uav_strike_projectile_mp":
			case "remote_mortar_missile_mp":
			case "javelin_mp":
				level notify ( "stinger_fired", self, missile, self.javelinTarget );
				self thread setAltSceneObj( missile, "tag_origin", 65 );
				break;			
			default:
				break;
		}

		switch ( weaponName )
		{
			case "at4_mp":
			case "iw5_smaw_mp":
			case "uav_strike_projectile_mp":
			case "remote_mortar_missile_mp":			
			case "javelin_mp":
			case "rpg_mp":
			case "ac130_105mm_mp":
			case "ac130_40mm_mp":
			case "remotemissile_projectile_mp":
				missile thread maps\mp\gametypes\_shellshock::grenade_earthQuake();
			default:
				break;
		}
	}
}


watchSentryUsage()
{
	self endon( "death" );
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "sentry_placement_finished", sentry );
		
		self thread setAltSceneObj( sentry, "tag_flash", 65 );
	}
}


empExplodeWaiter()
{
	self thread maps\mp\gametypes\_shellshock::endOnDeath();
	self endon( "end_explode" );

	self waittill( "explode", position );

	ents = getEMPDamageEnts( position, 512, false );

	foreach ( ent in ents )
	{
		if ( isDefined( ent.owner ) && !friendlyFireCheck( self.owner, ent.owner ) )
			continue;

		ent notify( "emp_damage", self.owner, 8.0 );
	}
}


beginC4Tracking()
{
	self endon( "death" );
	self endon( "disconnect" );

	self waittill_any( "grenade_fire", "weapon_change", "offhand_end" );
	
	// need to clear the changing weapon because it'll get stuck on c4_mp and player will stop spawning because we get locked in isChangingWeapon() loop when a killstreak is earned
	self.changingWeapon = undefined;
}


watchForThrowbacks()
{
	self endon( "death" );
	self endon( "disconnect" );

	for ( ;; )
	{
		self waittill( "grenade_fire", grenade, weapname );
		
		if ( self.gotPullbackNotify )
		{
			self.gotPullbackNotify = false;
			continue;
		}
		if ( !isSubStr( weapname, "frag_" ) && !isSubStr( weapname, "semtex_" ) )
			continue;

		// no grenade_pullback notify! we must have picked it up off the ground.
		grenade.threwBack = true;
		self thread incPlayerStat( "throwbacks", 1 );

		grenade thread maps\mp\gametypes\_shellshock::grenade_earthQuake();
		grenade.originalOwner = self;
	}
}


watchC4()
{
	self endon( "spawned_player" );
	self endon( "disconnect" );

	//maxc4 = 2;

	while ( 1 )
	{
		self waittill( "grenade_fire", c4, weapname );
		if ( weapname == "c4" || weapname == "c4_mp" )
		{
			if ( !self.c4array.size )
				self thread watchC4AltDetonate();

			if ( self.c4array.size )
			{
				self.c4array = array_removeUndefined( self.c4array );
				
				if( self.c4array.size >= level.maxPerPlayerExplosives )
				{
					self.c4array[0] detonate();
				}
			}

			self.c4array[ self.c4array.size ] = c4;
			c4.owner = self;
			c4.team = self.team;
			c4.activated = false;
			c4.weaponName = weapname;

			c4 thread maps\mp\gametypes\_shellshock::c4_earthQuake();
			c4 thread c4Activate();
			c4 thread c4Damage();
			c4 thread c4EMPDamage();
			c4 thread c4EMPKillstreakWait();
			
			c4 waittill ( "missile_stuck" ); //to spawn pickup trigger in the correct location
			c4.trigger = spawn( "script_origin", c4.origin );
			c4 thread equipmentWatchUse( self );
			
			//c4 thread c4DetectionTrigger( self.pers[ "team" ] );
		}
	}
}


c4EMPDamage()
{
	self endon( "death" );

	for ( ;; )
	{
		self waittill( "emp_damage", attacker, duration );

		playfxOnTag( getfx( "sentry_explode_mp" ), self, "tag_origin" );

		self.disabled = true;
		self notify( "disabled" );

		wait( duration );

		self.disabled = undefined;
		self notify( "enabled" );
	}
}


c4EMPKillstreakWait()
{
	self endon( "death" );

	for ( ;; )
	{
		level waittill( "emp_update" );

		if ( (level.teamBased && level.teamEMPed[self.team]) || (!level.teamBased && isDefined( level.empPlayer ) && level.empPlayer != self.owner ) )
		{
			self.disabled = true;
			self notify( "disabled" );
		}
		else
		{
			self.disabled = undefined;
			self notify( "enabled" );
		}
	}
}


setClaymoreTeamHeadIcon( team )
{
	self endon( "death" );
	wait .05;
	if ( level.teamBased )
		self maps\mp\_entityheadicons::setTeamHeadIcon( team, ( 0, 0, 20 ) );
	else if ( isDefined( self.owner ) )
		self maps\mp\_entityheadicons::setPlayerHeadIcon( self.owner, (0,0,20) );
}


watchClaymores()
{
	self endon( "spawned_player" );
	self endon( "disconnect" );

	self.claymorearray = [];
	while ( 1 )
	{
		self waittill( "grenade_fire", claymore, weapname );
		if ( weapname == "claymore" || weapname == "claymore_mp" )
		{
			if( !IsAlive( self ) )
			{
				claymore delete();
				return;
			}

			// need to see if this is being placed far away from the player and not let it do that
			// this will fix a legacy bug where you can stand on a ledge and plant a claymore down on the ground far below you
			claymore Hide();
			claymore waittill( "missile_stuck" );
			distanceZ = 40;
			
			if( distanceZ * distanceZ < DistanceSquared( claymore.origin, self.origin ) )
			{
				secTrace = bulletTrace( self.origin, self.origin - (0, 0, distanceZ), false, self );
			
				if( secTrace["fraction"] == 1 )
				{
					// there's nothing under us so don't place the claymore up in the air
					claymore delete();
					self SetWeaponAmmoStock( "claymore_mp", self GetWeaponAmmoStock( "claymore_mp" ) + 1 );
					continue;
				}
				claymore.origin = secTrace["position"];
			}
			claymore Show();

			self.claymorearray = array_removeUndefined( self.claymorearray );
			
			if( self.claymoreArray.size >= level.maxPerPlayerExplosives )
				self.claymoreArray[0] detonate();
			
			self.claymorearray[ self.claymorearray.size ] = claymore;
			claymore.owner = self;
			claymore.team = self.team;
			claymore.weaponName = weapname;
			claymore.trigger = spawn( "script_origin", claymore.origin );

			level.mines[level.mines.size] = claymore;
			claymore thread c4Damage();
			claymore thread c4EMPDamage();
			claymore thread c4EMPKillstreakWait();
			claymore thread claymoreDetonation();
			claymore thread equipmentWatchUse( self );
			//claymore thread claymoreDetectionTrigger_wait( self.pers[ "team" ] );
			claymore thread setClaymoreTeamHeadIcon( self.pers[ "team" ] );
			
			// need to clear the changing weapon because it'll get stuck on claymore_mp and player will stop spawning because we get locked in isChangingWeapon() loop when a killstreak is earned
			self.changingWeapon = undefined;

			 /#
			if ( getdvarint( "scr_claymoredebug" ) )
			{
				claymore thread claymoreDebug();
			}
			#/
		}
	}
}

equipmentWatchUse( owner )
{
	self endon( "spawned_player" );
	self endon( "disconnect" );
	
	self.trigger setCursorHint( "HINT_NOICON" );
	
	if ( self.weaponname == "c4_mp" )
		self.trigger setHintString( &"MP_PICKUP_C4" );
	else if (self.weaponname == "claymore_mp" )
		self.trigger setHintString( &"MP_PICKUP_CLAYMORE" );
	else if ( self.weaponname == "bouncingbetty_mp" )
		self.trigger setHintString( &"MP_PICKUP_BOUNCING_BETTY" );
	
	self.trigger setSelfUsable( owner );
	self.trigger thread notUsableForJoiningPlayers( self );

	for ( ;; )
	{
		self.trigger waittill ( "trigger", owner );
		
		owner playLocalSound( "scavenger_pack_pickup" );
		
		owner SetWeaponAmmoStock( self.weaponname, owner GetWeaponAmmoStock( self.weaponname ) + 1 );

		self.trigger delete();
		self delete();
		self notify( "death" );
	}
}

 /#
claymoreDebug()
{
	self waittill( "missile_stuck" );
	self thread showCone( acos( level.claymoreDetectionDot ), level.claymoreDetonateRadius, ( 1, .85, 0 ) );
	self thread showCone( 60, 256, ( 1, 0, 0 ) );
}

vectorcross( v1, v2 )
{
	return( v1[ 1 ] * v2[ 2 ] - v1[ 2 ] * v2[ 1 ], v1[ 2 ] * v2[ 0 ] - v1[ 0 ] * v2[ 2 ], v1[ 0 ] * v2[ 1 ] - v1[ 1 ] * v2[ 0 ] );
}

showCone( angle, range, color )
{
	self endon( "death" );

	start = self.origin;
	forward = anglestoforward( self.angles );
	right = vectorcross( forward, ( 0, 0, 1 ) );
	up = vectorcross( forward, right );

	fullforward = forward * range * cos( angle );
	sideamnt = range * sin( angle );

	while ( 1 )
	{
		prevpoint = ( 0, 0, 0 );
		for ( i = 0; i <= 20; i++ )
		{
			coneangle = i / 20.0 * 360;
			point = start + fullforward + sideamnt * ( right * cos( coneangle ) + up * sin( coneangle ) );
			if ( i > 0 )
			{
				line( start, point, color );
				line( prevpoint, point, color );
			}
			prevpoint = point;
		}
		wait .05;
	}
}
#/

claymoreDetonation()
{
	self endon( "death" );

	//self waittill( "missile_stuck" );

	damagearea = spawn( "trigger_radius", self.origin + ( 0, 0, 0 - level.claymoreDetonateRadius ), 0, level.claymoreDetonateRadius, level.claymoreDetonateRadius * 2 );
	self thread deleteOnDeath( damagearea );

	while ( 1 )
	{
		damagearea waittill( "trigger", player );

		if ( getdvarint( "scr_claymoredebug" ) != 1 )
		{
			if ( isdefined( self.owner ) && player == self.owner )
				continue;
			if ( !friendlyFireCheck( self.owner, player, 0 ) )
				continue;
		}
		if ( lengthsquared( player getEntityVelocity() ) < 10 )
			continue;
		
		zDistance = abs( player.origin[2] - self.origin[2] );
		
		if ( zDistance > 128)
			continue;

		if ( !player shouldAffectClaymore( self ) )
			continue;

		if ( player damageConeTrace( self.origin, self ) > 0 )
			break;
	}
	
	self playsound ("claymore_activated");
	
	if ( IsPlayer( player ) && player _hasPerk( "specialty_delaymine" ) )
	{
		player notify( "triggered_claymore" );
		wait level.delayMineTime;
	}
	else 
		wait level.claymoreDetectionGracePeriod;
	
	if ( isDefined( self.trigger ) )
		self.trigger delete();
	
	self detonate();
}

shouldAffectClaymore( claymore )
{
	if ( isDefined( claymore.disabled ) )
		return false;

	pos = self.origin + ( 0, 0, 32 );

	dirToPos = pos - claymore.origin;
	claymoreForward = anglesToForward( claymore.angles );

	dist = vectorDot( dirToPos, claymoreForward );
	if ( dist < level.claymoreDetectionMinDist )
		return false;

	dirToPos = vectornormalize( dirToPos );

	dot = vectorDot( dirToPos, claymoreForward );
	return( dot > level.claymoreDetectionDot );
}

deleteOnDeath( ent )
{
	self waittill( "death" );
	wait .05;
	
	if ( isdefined( ent ) )
	{
		if ( isDefined( ent.trigger ) )
			ent.trigger delete();
		
		ent delete();
	}
}

c4Activate()
{
	self endon( "death" );

	self waittill( "missile_stuck" );

	wait 0.05;

	self notify( "activated" );
	self.activated = true;
}

watchC4AltDetonate()
{
	self endon( "death" );
	self endon( "disconnect" );
	self endon( "detonated" );
	level endon( "game_ended" );

	buttonTime = 0;
	for ( ;; )
	{
		if ( self UseButtonPressed() )
		{
			buttonTime = 0;
			while ( self UseButtonPressed() )
			{
				buttonTime += 0.066;
				wait( 0.066 );
			}

			println( "pressTime1: " + buttonTime );
			if ( buttonTime >= 0.5 )
				continue;

			buttonTime = 0;
			while ( !self UseButtonPressed() && buttonTime < 0.5 )
			{
				buttonTime += 0.066;
				wait( 0.066 );
			}

			println( "delayTime: " + buttonTime );
			if ( buttonTime >= 0.5 )
				continue;

			if ( !self.c4Array.size )
				return;

			self notify( "alt_detonate" );
		}
		wait( 0.066 );
	}
}

watchC4Detonation()
{
	self endon( "death" );
	self endon( "disconnect" );

	while ( 1 )
	{
		self waittillmatch( "detonate", "c4_mp" );
		newarray = [];
		for ( i = 0; i < self.c4array.size; i++ )
		{
			c4 = self.c4array[ i ];
			if ( isdefined( self.c4array[ i ] ) )
				c4 thread waitAndDetonate( 0.1 );
		}
		self.c4array = newarray;
		self notify( "detonated" );
	}
}


watchC4AltDetonation()
{
	self endon( "death" );
	self endon( "disconnect" );

	while ( 1 )
	{
		self waittill( "alt_detonate" );
		weap = self getCurrentWeapon();
		if ( weap != "c4_mp" )
		{
			newarray = [];
			for ( i = 0; i < self.c4array.size; i++ )
			{
				c4 = self.c4array[ i ];
				if ( isdefined( self.c4array[ i ] ) )
					c4 thread waitAndDetonate( 0.1 );
			}
			self.c4array = newarray;
			self notify( "detonated" );
		}
	}
}


waitAndDetonate( delay )
{
	self endon( "death" );
	wait delay;

	self waitTillEnabled();

	self detonate();
}

deleteC4AndClaymoresOnDisconnect()
{
	self endon( "death" );
	self waittill( "disconnect" );

	c4array = self.c4array;
	claymorearray = self.claymorearray;

	wait .05;

	for ( i = 0; i < c4array.size; i++ )
	{
		if ( isdefined( c4array[ i ] ) )
			c4array[ i ] delete();
	}
	for ( i = 0; i < claymorearray.size; i++ )
	{
		if ( isdefined( claymorearray[ i ] ) )
			claymorearray[ i ] delete();
	}
}

c4Damage()
{
	self endon( "death" );

	self setcandamage( true );
	self.maxhealth = 100000;
	self.health = self.maxhealth;

	attacker = undefined;

	while ( 1 )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, iDFlags, weapon );
		if ( !isPlayer( attacker ) )
			continue;

		// don't allow people to destroy C4 on their team if FF is off
		if ( !friendlyFireCheck( self.owner, attacker ) )
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

		break;
	}

	if ( level.c4explodethisframe )
		wait .1 + randomfloat( .4 );
	else
		wait .05;

	if ( !isdefined( self ) )
		return;

	level.c4explodethisframe = true;

	thread resetC4ExplodeThisFrame();

	if ( isDefined( type ) && ( isSubStr( type, "MOD_GRENADE" ) || isSubStr( type, "MOD_EXPLOSIVE" ) ) )
		self.wasChained = true;

	if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		self.wasDamagedFromBulletPenetration = true;

	self.wasDamaged = true;

	if( isPlayer( attacker ) )
	{
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "c4" );
	}

	if ( level.teamBased )
	{
		// "destroyed_explosive" notify, for challenges
		if ( isdefined( attacker ) && isdefined( attacker.pers[ "team" ] ) && isdefined( self.owner ) && isdefined( self.owner.pers[ "team" ] ) )
		{
			if ( attacker.pers[ "team" ] != self.owner.pers[ "team" ] )
				attacker notify( "destroyed_explosive" );
		}
	}
	else
	{
		// checking isDefined attacker is defensive but it's too late in the project to risk issues by not having it
		if ( isDefined( self.owner ) && isDefined( attacker ) && attacker != self.owner )
			attacker notify( "destroyed_explosive" );		
	}
	
	if ( isDefined( self.trigger ) )
		self.trigger delete();
	
	self detonate( attacker );
	// won't get here; got death notify.
}

resetC4ExplodeThisFrame()
{
	wait .05;
	level.c4explodethisframe = false;
}

saydamaged( orig, amount )
{
	for ( i = 0; i < 60; i++ )
	{
		print3d( orig, "damaged! " + amount );
		wait .05;
	}
}

waitTillEnabled()
{
	if ( !isDefined( self.disabled ) )
		return;

	self waittill( "enabled" );
	assert( !isDefined( self.disabled ) );
}


c4DetectionTrigger( ownerTeam )
{
	self waittill( "activated" );

	trigger = spawn( "trigger_radius", self.origin - ( 0, 0, 128 ), 0, 512, 256 );
	trigger.detectId = "trigger" + getTime() + randomInt( 1000000 );

	trigger.owner = self;
	trigger thread detectIconWaiter( level.otherTeam[ ownerTeam ] );

	self waittill( "death" );
	trigger notify( "end_detection" );

	if ( isDefined( trigger.bombSquadIcon ) )
		trigger.bombSquadIcon destroy();

	trigger delete();
}


//claymoreDetectionTrigger_wait( ownerTeam )
//{
//	self endon( "death" );
//	self waittill( "missile_stuck" );
//
//	self thread claymoreDetectionTrigger( ownerTeam );
//}

claymoreDetectionTrigger( ownerTeam )
{
	trigger = spawn( "trigger_radius", self.origin - ( 0, 0, 128 ), 0, 512, 256 );
	trigger.detectId = "trigger" + getTime() + randomInt( 1000000 );

	trigger.owner = self;
	trigger thread detectIconWaiter( level.otherTeam[ ownerTeam ] );

	self waittill( "death" );
	trigger notify( "end_detection" );

	if ( isDefined( trigger.bombSquadIcon ) )
		trigger.bombSquadIcon destroy();

	trigger delete();
}


detectIconWaiter( detectTeam )
{
	self endon( "end_detection" );
	level endon( "game_ended" );

	while ( !level.gameEnded )
	{
		self waittill( "trigger", player );

		if ( !player.detectExplosives )
			continue;

		if ( level.teamBased && player.team != detectTeam )
			continue;
		else if ( !level.teamBased && player == self.owner.owner )
			continue;

		if ( isDefined( player.bombSquadIds[ self.detectId ] ) )
			continue;

		player thread showHeadIcon( self );
	}
}


setupBombSquad()
{
	self.bombSquadIds = [];

	if ( self.detectExplosives && !self.bombSquadIcons.size )
	{
		for ( index = 0; index < 4; index++ )
		{
			self.bombSquadIcons[ index ] = newClientHudElem( self );
			self.bombSquadIcons[ index ].x = 0;
			self.bombSquadIcons[ index ].y = 0;
			self.bombSquadIcons[ index ].z = 0;
			self.bombSquadIcons[ index ].alpha = 0;
			self.bombSquadIcons[ index ].archived = true;
			self.bombSquadIcons[ index ] setShader( "waypoint_bombsquad", 14, 14 );
			self.bombSquadIcons[ index ] setWaypoint( false, false );
			self.bombSquadIcons[ index ].detectId = "";
		}
	}
	else if ( !self.detectExplosives )
	{
		for ( index = 0; index < self.bombSquadIcons.size; index++ )
			self.bombSquadIcons[ index ] destroy();

		self.bombSquadIcons = [];
	}
}


showHeadIcon( trigger )
{
	triggerDetectId = trigger.detectId;
	useId = -1;
	for ( index = 0; index < 4; index++ )
	{
		detectId = self.bombSquadIcons[ index ].detectId;

		if ( detectId == triggerDetectId )
			return;

		if ( detectId == "" )
			useId = index;
	}

	if ( useId < 0 )
		return;

	self.bombSquadIds[ triggerDetectId ] = true;

	self.bombSquadIcons[ useId ].x = trigger.origin[ 0 ];
	self.bombSquadIcons[ useId ].y = trigger.origin[ 1 ];
	self.bombSquadIcons[ useId ].z = trigger.origin[ 2 ] + 24 + 128;

	self.bombSquadIcons[ useId ] fadeOverTime( 0.25 );
	self.bombSquadIcons[ useId ].alpha = 1;
	self.bombSquadIcons[ useId ].detectId = trigger.detectId;

	while ( isAlive( self ) && isDefined( trigger ) && self isTouching( trigger ) )
		wait( 0.05 );

	if ( !isDefined( self ) )
		return;

	self.bombSquadIcons[ useId ].detectId = "";
	self.bombSquadIcons[ useId ] fadeOverTime( 0.25 );
	self.bombSquadIcons[ useId ].alpha = 0;
	self.bombSquadIds[ triggerDetectId ] = undefined;
}


// these functions are used with scripted weapons (like c4, claymores, artillery)
// returns an array of objects representing damageable entities (including players) within a given sphere.
// each object has the property damageCenter, which represents its center (the location from which it can be damaged).
// each object also has the property entity, which contains the entity that it represents.
// to damage it, call damageEnt() on it.
getDamageableEnts( pos, radius, doLOS, startRadius )
{
	ents = [];

	if ( !isdefined( doLOS ) )
		doLOS = false;

	if ( !isdefined( startRadius ) )
		startRadius = 0;
	
	radiusSq = radius * radius;

	// players
	players = level.players;
	for ( i = 0; i < players.size; i++ )
	{
		if ( !isalive( players[ i ] ) || players[ i ].sessionstate != "playing" )
			continue;

		playerpos = get_damageable_player_pos( players[ i ] );
		distSq = distanceSquared( pos, playerpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, playerpos, startRadius, players[ i ] ) ) )
		{
			ents[ ents.size ] = get_damageable_player( players[ i ], playerpos );
		}
	}

	// grenades
	grenades = getentarray( "grenade", "classname" );
	for ( i = 0; i < grenades.size; i++ )
	{
		entpos = get_damageable_grenade_pos( grenades[ i ] );
		distSq = distanceSquared( pos, entpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, grenades[ i ] ) ) )
		{
			ents[ ents.size ] = get_damageable_grenade( grenades[ i ], entpos );
		}
	}

	destructibles = getentarray( "destructible", "targetname" );
	for ( i = 0; i < destructibles.size; i++ )
	{
		entpos = destructibles[ i ].origin;
		distSq = distanceSquared( pos, entpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, destructibles[ i ] ) ) )
		{
			newent = spawnstruct();
			newent.isPlayer = false;
			newent.isADestructable = false;
			newent.entity = destructibles[ i ];
			newent.damageCenter = entpos;
			ents[ ents.size ] = newent;
		}
	}

	destructables = getentarray( "destructable", "targetname" );
	for ( i = 0; i < destructables.size; i++ )
	{
		entpos = destructables[ i ].origin;
		distSq = distanceSquared( pos, entpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, destructables[ i ] ) ) )
		{
			newent = spawnstruct();
			newent.isPlayer = false;
			newent.isADestructable = true;
			newent.entity = destructables[ i ];
			newent.damageCenter = entpos;
			ents[ ents.size ] = newent;
		}
	}
	
	//sentries
	sentries = getentarray( "misc_turret", "classname" );
	foreach ( sentry in sentries )
	{
		entpos = sentry.origin + (0,0,32);
		distSq = distanceSquared( pos, entpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, sentry ) ) )
		{
			switch( sentry.model )
			{
			case "sentry_minigun_weak":
			case "mp_sam_turret":
			case "mp_remote_turret":
			case "vehicle_ugv_talon_gun_mp":
				ents[ ents.size ] = get_damageable_sentry(sentry, entpos);
				break;
			}
		}
	}

	// mines ( the problem here seems to be the traceline from 1 ground position to another is easily blocked, the origin offset helps but may have it's own issues )
	mines = getentarray( "script_model", "classname" );
	foreach ( mine in mines )
	{
		if ( mine.model != "projectile_bouncing_betty_grenade" && mine.model != "ims_scorpion_body" )
			continue;

		entpos = mine.origin + (0,0,32);
		distSq = distanceSquared( pos, entpos );
		if ( distSq < radiusSq && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, mine ) ) )
			ents[ ents.size ] = get_damageable_mine( mine, entpos );
	}

	return ents;
}


getEMPDamageEnts( pos, radius, doLOS, startRadius )
{
	ents = [];

	if ( !isDefined( doLOS ) )
		doLOS = false;

	if ( !isDefined( startRadius ) )
		startRadius = 0;

	grenades = getEntArray( "grenade", "classname" );
	foreach ( grenade in grenades )
	{
		//if ( !isDefined( grenade.weaponName ) )
		//	continue;

		entpos = grenade.origin;
		dist = distance( pos, entpos );
		if ( dist < radius && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, grenade ) ) )
			ents[ ents.size ] = grenade;
	}

	turrets = getEntArray( "misc_turret", "classname" );
	foreach ( turret in turrets )
	{
		//if ( !isDefined( turret.weaponName ) )
		//	continue;

		entpos = turret.origin;
		dist = distance( pos, entpos );
		if ( dist < radius && ( !doLOS || weaponDamageTracePassed( pos, entpos, startRadius, turret ) ) )
			ents[ ents.size ] = turret;
	}

	return ents;
}


weaponDamageTracePassed( from, to, startRadius, ent )
{
	midpos = undefined;

	diff = to - from;
	if ( lengthsquared( diff ) < startRadius * startRadius )
		return true;
	
	dir = vectornormalize( diff );
	midpos = from + ( dir[ 0 ] * startRadius, dir[ 1 ] * startRadius, dir[ 2 ] * startRadius );

	trace = bullettrace( midpos, to, false, ent );

	if ( getdvarint( "scr_damage_debug" ) != 0 || getdvarint( "scr_debugMines" ) != 0 )
	{
		thread debugprint( from, ".dmg" );
		if ( isdefined( ent ) )
			thread debugprint( to, "." + ent.classname );
		else
			thread debugprint( to, ".undefined" );
		if ( trace[ "fraction" ] == 1 )
		{
			thread debugline( midpos, to, ( 1, 1, 1 ) );
		}
		else
		{
			thread debugline( midpos, trace[ "position" ], ( 1, .9, .8 ) );
			thread debugline( trace[ "position" ], to, ( 1, .4, .3 ) );
		}
	}

	return( trace[ "fraction" ] == 1 );
}

// eInflictor = the entity that causes the damage (e.g. a claymore)
// eAttacker = the player that is attacking
// iDamage = the amount of damage to do
// sMeansOfDeath = string specifying the method of death (e.g. "MOD_PROJECTILE_SPLASH")
// sWeapon = string specifying the weapon used (e.g. "claymore_mp")
// damagepos = the position damage is coming from
// damagedir = the direction damage is moving in
damageEnt( eInflictor, eAttacker, iDamage, sMeansOfDeath, sWeapon, damagepos, damagedir )
{
	if ( self.isPlayer )
	{
		self.damageOrigin = damagepos;
		self.entity thread [[ level.callbackPlayerDamage ]](
			eInflictor,// eInflictor The entity that causes the damage.( e.g. a turret )
			eAttacker,// eAttacker The entity that is attacking.
			iDamage,// iDamage Integer specifying the amount of damage done
			0,// iDFlags Integer specifying flags that are to be applied to the damage
			sMeansOfDeath,// sMeansOfDeath Integer specifying the method of death
			sWeapon,// sWeapon The weapon number of the weapon used to inflict the damage
			damagepos,// vPoint The point the damage is from?
			damagedir,// vDir The direction of the damage
			"none",// sHitLoc The location of the hit
			0// psOffsetTime The time offset for the damage
		 );
	}
	else
	{
		// destructable walls and such can only be damaged in certain ways.
		if ( self.isADestructable && ( sWeapon == "artillery_mp" || sWeapon == "claymore_mp" || sWeapon == "stealth_bomb_mp" ) )
			return;

		self.entity notify( "damage", iDamage, eAttacker, ( 0, 0, 0 ), ( 0, 0, 0 ), "MOD_EXPLOSIVE", "", "", "", undefined, sWeapon );
	}
}


debugline( a, b, color )
{
	for ( i = 0; i < 30 * 20; i++ )
	{
		line( a, b, color );
		wait .05;
	}
}

debugcircle( center, radius, color, segments )
{
	if ( !isDefined( segments ) )
		segments = 16;
		
	angleFrac = 360/segments;
	circlepoints = [];
	
	for( i = 0; i < segments; i++ )
	{
		angle = (angleFrac * i);
		xAdd = cos(angle) * radius;
		yAdd = sin(angle) * radius;
		x = center[0] + xAdd;
		y = center[1] + yAdd;
		z = center[2];
		circlepoints[circlepoints.size] = ( x, y, z );
	}
	
	for( i = 0; i < circlepoints.size; i++ )
	{
		start = circlepoints[i];
		if (i + 1 >= circlepoints.size)
			end = circlepoints[0];
		else
			end = circlepoints[i + 1];
		
		thread debugline( start, end, color );
	}
}

debugprint( pt, txt )
{
	for ( i = 0; i < 30 * 20; i++ )
	{
		print3d( pt, txt );
		wait .05;
	}
}


onWeaponDamage( eInflictor, sWeapon, meansOfDeath, damage, eAttacker )
{
	self endon( "death" );
	self endon( "disconnect" );

	switch( sWeapon )
	{
		case "concussion_grenade_mp":
			// should match weapon settings in gdt
			
			if ( !isDefined( eInflictor ) )//check to ensure inflictor wasnt destroyed.
				return;
			else if( meansOfDeath == "MOD_IMPACT" )
				return;
			
			giveFeedback = true;
			if( IsDefined( eInflictor.owner ) && eInflictor.owner == eAttacker )
				giveFeedback = false;

			radius = 512;
			scale = 1 - ( distance( self.origin, eInflictor.origin ) / radius );

			if ( scale < 0 )
				scale = 0;

			time = 2 + ( 4 * scale );
			
			if ( isDefined( self.stunScaler ) )
				time = time * self.stunScaler;
			
			wait( 0.05 );
			eAttacker notify( "stun_hit" );
			self notify( "concussed", eAttacker );
			if( eAttacker != self )
				eAttacker maps\mp\gametypes\_missions::processChallenge( "ch_alittleconcussed" );
			self shellShock( "concussion_grenade_mp", time );
			self.concussionEndTime = getTime() + ( time * 1000 );
			if( giveFeedback )
				eAttacker thread maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "stun" );
		break;

		case "weapon_cobra_mk19_mp":
			// mk19 is too powerful with shellshock slowdown
		break;

		default:
			// shellshock will only be done if meansofdeath is an appropriate type and if there is enough damage.
			maps\mp\gametypes\_shellshock::shellshockOnDamage( meansOfDeath, damage );
		break;
	}

}

// weapon class boolean helpers
isPrimaryWeapon( weapName )
{
	if ( weapName == "none" )
		return false;
		
	if ( weaponInventoryType( weapName ) != "primary" )
		return false;

	switch ( weaponClass( weapName ) )
	{
		case "rifle":
		case "smg":
		case "mg":
		case "spread":
		case "pistol":
		case "rocketlauncher":
		case "sniper":
			return true;

		default:
			return false;
	}	
}


isAltModeWeapon( weapName )
{
	if ( weapName == "none" )
		return false;
		
	return ( weaponInventoryType( weapName ) == "altmode" );
}

isInventoryWeapon( weapName )
{
	if ( weapName == "none" )
		return false;
		
	return ( weaponInventoryType( weapName ) == "item" );
}

isRiotShield( weapName )
{
	if ( weapName == "none" )
		return false;
		
	return ( WeaponType( weapName ) == "riotshield" );
}

isOffhandWeapon( weapName )
{
	if ( weapName == "none" )
		return false;
		
	return ( weaponInventoryType( weapName ) == "offhand" );
}

isSideArm( weapName )
{
	if ( weapName == "none" )
		return false;

	if ( weaponInventoryType( weapName ) != "primary" )
		return false;

	return ( weaponClass( weapName ) == "pistol" );
}


// This needs for than this.. this would qualify c4 as a grenade
isGrenade( weapName )
{
	weapClass = weaponClass( weapName );
	weapType = weaponInventoryType( weapName );

	if ( weapClass != "grenade" )
		return false;
		
	if ( weapType != "offhand" )
		return false;
}


updateSavedLastWeapon()
{
	self endon( "death" );
	self endon( "disconnect" );

	currentWeapon = self.currentWeaponAtSpawn;
	self.saved_lastWeapon = currentWeapon;

	for ( ;; )
	{
		self waittill( "weapon_change", newWeapon );
	
		if ( newWeapon == "none" )
		{
			self.saved_lastWeapon = currentWeapon;
			continue;
		}

		weaponInvType = weaponInventoryType( newWeapon );

		if ( weaponInvType != "primary" && weaponInvType != "altmode" )
		{
			self.saved_lastWeapon = currentWeapon;
			continue;
		}
		
		/*
		if ( newWeapon == "onemanarmy_mp" )
		{
			self.saved_lastWeapon = currentWeapon;
			continue;
		}
		*/

		self updateMoveSpeedScale();

		self.saved_lastWeapon = currentWeapon;
		currentWeapon = newWeapon;
	}
}

updateWeaponRank()
{
	self endon( "death" );
	self endon( "disconnect" );

	currentWeapon = self.currentWeaponAtSpawn;

	// we just want the weapon name up to the first underscore
	weaponTokens = StrTok( currentWeapon, "_" );
	
	if ( weaponTokens[0] == "iw5" )
		weaponTokens[0] = weaponTokens[0] + "_" + weaponTokens[1];
	else if ( weaponTokens[0] == "alt" )
		weaponTokens[0] = weaponTokens[1] + "_" + weaponTokens[2];
	
	self.pers[ "weaponRank" ] = self maps\mp\gametypes\_rank::getWeaponRank( weaponTokens[0] ); 

	for ( ;; )
	{
		self waittill( "weapon_change", newWeapon );

		if( newWeapon == "none" || self isJuggernaut() || isDeathStreakWeapon( newWeapon ) )
		{
			continue;
		}

		weaponInvType = weaponInventoryType( newWeapon );

		if ( weaponInvType == "primary" )
		{
			// we just want the weapon name up to the first underscore unless its an IW5 weapon...
			weaponTokens = StrTok( newWeapon, "_" );
			if ( weaponTokens[0] == "iw5" )
				self.pers[ "weaponRank" ] = self maps\mp\gametypes\_rank::getWeaponRank( weaponTokens[0] + "_" + weaponTokens[1] ); 
			else if( weaponTokens[0] == "alt" )
				self.pers[ "weaponRank" ] = self maps\mp\gametypes\_rank::getWeaponRank( weaponTokens[1] + "_" + weaponTokens[2] ); 
			else
				self.pers[ "weaponRank" ] = self maps\mp\gametypes\_rank::getWeaponRank( weaponTokens[0] ); 
		}
	}
}

EMPPlayer( numSeconds )
{
	self endon( "disconnect" );
	self endon( "death" );

	self thread clearEMPOnDeath();

}


clearEMPOnDeath()
{
	self endon( "disconnect" );

	self waittill( "death" );
}


updateMoveSpeedScale()
{		
	self.weaponList = self GetWeaponsListPrimaries();	
	if ( self.weaponList.size )
	{
		heaviestWeaponValue = 1000;
		foreach ( weapon in self.weaponList )
		{
			baseWeapon = getBaseWeaponName( weapon );
			weaponSpeed = int( tableLookup( "mp/statstable.csv", 4, baseWeapon, 8 ) );
			
			if ( weaponSpeed == 0 )
				continue;
			
			if ( weaponSpeed < heaviestWeaponValue )
			{	
				heaviestWeaponValue = weaponSpeed;
			}	
		}
		assert ( heaviestWeaponValue != 1000 );
		if ( heaviestWeaponValue > 10 )
			heaviestWeaponValue = 10;
	}
	else
	{
		//	This should only ever happen half way through giveLoadout(), after weapons were
		//	cleared, when clearing perks (if player had juiced), and no secondary (in some new game modes).
		//	In that case, this would be called again at the end of giveLoadout(), after the primary had been 
		//	set and overwrite this correctly anyway.
		//	Setting a heavy default value to catch ending up here in any other circumstance (cheating).
		heaviestWeaponValue = 8;
	}
	
	normalizedWeaponSpeed = heaviestWeaponValue / 10;
	
	self.weaponSpeed = normalizedWeaponSpeed;
	self setMoveSpeedScale( normalizedWeaponSpeed * self.moveSpeedScaler );
}

stanceRecoilAdjuster()
{
	self endon ( "death" );
	self endon ( "disconnect" );	
	
	self notifyOnPlayerCommand( "adjustedStance", "+stance" );
	self notifyOnPlayerCommand( "adjustedStance", "+goStand" );
	
	for ( ;; )
	{
		self waittill_any( "adjustedStance", "sprint_begin" );
		
		weapClass = getWeaponClass( self GetCurrentPrimaryWeapon() );
		
		if ( weapClass != "weapon_lmg" && weapClass != "weapon_sniper" )
			continue;
		
		wait (.5 ); //necessary to ensure proper stance is given and to balance to ensure duck diving isnt a valid tactic
		
		self.stance = self GetStance();
		
		if ( self.stance == "prone" )
		{	
			if ( weapClass == "weapon_lmg" )
				self setRecoilScale( 0,40 );	
			else if ( weapClass == "weapon_sniper" )
				self setRecoilScale( 0,60 );
			else
				self setRecoilScale();		
		}
		else if ( self.stance == "crouch" )
		{
			if ( weapClass == "weapon_lmg" )
				self setRecoilScale( 0,10 );
			else if ( weapClass == "weapon_sniper" )
				self setRecoilScale( 0,30 );
			else
				self setRecoilScale();
		}
		else
		{
			self setRecoilScale();
		}
	}
}

buildWeaponData( filterPerks )
{
	attachmentList = getAttachmentList();		
	max_weapon_num = 149;

	baseWeaponData = [];
	
	for( weaponId = 0; weaponId <= max_weapon_num; weaponId++ )
	{
		baseName = tablelookup( "mp/statstable.csv", 0, weaponId, 4 );
		if( baseName == "" )
			continue;

		assetName = baseName + "_mp";

		if ( !isSubStr( tableLookup( "mp/statsTable.csv", 0, weaponId, 2 ), "weapon_" ) )
			continue;
		
		if ( weaponInventoryType( assetName ) != "primary" )
			continue;

		weaponInfo = spawnStruct();
		weaponInfo.baseName = baseName;
		weaponInfo.assetName = assetName;
		weaponInfo.variants = [];

		weaponInfo.variants[0] = assetName;
		// the alphabetize function is slow so we try not to do it for every weapon/attachment combo; a code solution would be better.
		attachmentNames = [];
		for ( innerLoopCount = 0; innerLoopCount < 6; innerLoopCount++ )
		{
			// generating attachment combinations
			attachmentName = tablelookup( "mp/statStable.csv", 0, weaponId, innerLoopCount + 11 );
			
			if ( filterPerks )
			{
				switch ( attachmentName )
				{
					case "fmj":
					case "xmags":
					case "rof":
						continue;
				}
			}
			
			if( attachmentName == "" )
				break;
			
			attachmentNames[attachmentName] = true;
		}

		// generate an alphabetized attachment list
		attachments = [];
		foreach ( attachmentName in attachmentList )
		{
			if ( !isDefined( attachmentNames[attachmentName] ) )
				continue;
			
			weaponInfo.variants[weaponInfo.variants.size] = baseName + "_" + attachmentName + "_mp";
			attachments[attachments.size] = attachmentName;
		}

		for ( i = 0; i < (attachments.size - 1); i++ )
		{
			colIndex = tableLookupRowNum( "mp/attachmentCombos.csv", 0, attachments[i] );
			for ( j = i + 1; j < attachments.size; j++ )
			{
				if ( tableLookup( "mp/attachmentCombos.csv", 0, attachments[j], colIndex ) == "no" )
					continue;
					
				weaponInfo.variants[weaponInfo.variants.size] = baseName + "_" + attachments[i] + "_" + attachments[j] + "_mp";
			}
		}
		
		baseWeaponData[baseName] = weaponInfo;
	}
	
	return ( baseWeaponData );
}

monitorSemtex()
{
	self endon( "disconnect" );
	self endon( "death" );
	
	for( ;; )
	{
		self waittill( "grenade_fire", weapon );

		if ( !isSubStr(weapon.model, "semtex" ) )
			continue;
			
		weapon waittill( "missile_stuck", stuckTo );
			
		if ( !isPlayer( stuckTo ) )
			continue;
			
		if ( level.teamBased && isDefined( stuckTo.team ) && stuckTo.team == self.team )
		{
			weapon.isStuck = "friendly";
			continue;
		}
	
		weapon.isStuck = "enemy";
		weapon.stuckEnemyEntity = stuckTo;
		
		stuckTo maps\mp\gametypes\_hud_message::playerCardSplashNotify( "semtex_stuck", self );
		
		self thread maps\mp\gametypes\_hud_message::SplashNotify( "stuck_semtex", 100 );
		self notify( "process", "ch_bullseye" );
	}	
}


turret_monitorUse()
{
	for( ;; )
	{
		self waittill ( "trigger", player );
		
		self thread turret_playerThread( player );
	}
}

turret_playerThread( player )
{
	player endon ( "death" );
	player endon ( "disconnect" );

	player notify ( "weapon_change", "none" );
	
	self waittill ( "turret_deactivate" );
	
	player notify ( "weapon_change", player getCurrentWeapon() );
}

spawnMine( origin, owner, type, angles )
{
	Assert( isDefined( owner ) );

	if ( !isDefined( angles ) )
		angles = (0, RandomFloat(360), 0);

	model = "projectile_bouncing_betty_grenade";
	mine = Spawn( "script_model", origin );
	mine.angles = angles;
	mine SetModel( model );
	mine.owner = owner;
	mine.weaponName = "bouncingbetty_mp";
	level.mines[level.mines.size] = mine;

	mine.killCamOffset = ( 0, 0, 4 );
	mine.killCamEnt = Spawn( "script_model", mine.origin + mine.killCamOffset );
	
	if ( !isDefined( type ) || type == "equipment" )
	{
		owner.equipmentMines = array_removeUndefined( owner.equipmentMines );
		if( owner.equipmentMines.size >= level.maxPerPlayerExplosives )
			owner.equipmentMines[0] delete();
	
		owner.equipmentMines[ owner.equipmentMines.size ] = mine;
	}
	else
	{
		owner.killstreakMines[ owner.killstreakMines.size ] = mine;
	}

	mine thread createBombSquadModel( "projectile_bouncing_betty_grenade", "tag_origin", level.otherTeam[owner.team], owner ); // may have issues with team and owner here
	mine thread mineBeacon();
	mine thread setClaymoreTeamHeadIcon( owner.pers[ "team" ] );
	mine thread mineDamageMonitor();
	mine thread mineProximityTrigger();	
	//mine thread mineSelfDestruct();
	
	return mine;
}

mineDamageMonitor()
{
	self endon( "mine_triggered" );
	self endon( "mine_selfdestruct" );
	self endon( "death" );

	self setcandamage( true );
	self.maxhealth = 100000;
	self.health = self.maxhealth;

	attacker = undefined;

	while ( 1 )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, type, modelName, tagName, partName, iDFlags, weapon );
		
		if ( !isPlayer( attacker ) || isDefined( weapon ) && weapon == "bouncingbetty_mp" )
			continue;

		// don't allow people to destroy mines on their team if FF is off
		if ( !friendlyFireCheck( self.owner, attacker ) )
			continue;

		if( IsDefined( weapon ) )
		{
			switch( weapon )
			{
			//case "concussion_grenade_mp":
			//case "flash_grenade_mp":
			case "smoke_grenade_mp":
				continue;
			}
		}

		break;
	}

	self notify( "mine_destroyed" );

	if ( isDefined( type ) && ( isSubStr( type, "MOD_GRENADE" ) || isSubStr( type, "MOD_EXPLOSIVE" ) ) )
		self.wasChained = true;

	if ( isDefined( iDFlags ) && ( iDFlags & level.iDFLAGS_PENETRATION ) )
		self.wasDamagedFromBulletPenetration = true;

	self.wasDamaged = true;
	
	if( isPlayer( attacker ) )
	{
		attacker maps\mp\gametypes\_damagefeedback::updateDamageFeedback( "bouncing_betty" );
	}

	if ( level.teamBased )
	{
		// "destroyed_explosive" notify, for challenges
		if ( isdefined( attacker ) && isdefined( attacker.pers[ "team" ] ) && isdefined( self.owner ) && isdefined( self.owner.pers[ "team" ] ) )
		{
			if ( attacker.pers[ "team" ] != self.owner.pers[ "team" ] )
				attacker notify( "destroyed_explosive" );
		}
	}
	else
	{
		// checking isDefined attacker is defensive but it's too late in the project to risk issues by not having it
		if ( isDefined( self.owner ) && isDefined( attacker ) && attacker != self.owner )
			attacker notify( "destroyed_explosive" );		
	}

	self thread mineExplode( attacker );
}

mineProximityTrigger()
{
	self endon( "mine_destroyed" );
	self endon( "mine_selfdestruct" );
	self endon( "death" );
	
	//	arming time
	wait( 2 );

	trigger = Spawn( "trigger_radius", self.origin, 0, level.mineDetectionRadius, level.mineDetectionHeight );
	self thread mineDeleteTrigger( trigger );
	
	player = undefined;
	while ( 1 )
	{
		trigger waittill( "trigger", player );

		if ( getdvarint( "scr_minesKillOwner" ) != 1 )
		{
			if ( isDefined( self.owner ) && player == self.owner )
				continue;
				
			if ( !friendlyFireCheck( self.owner, player, 0 ) )
				continue;
		}
		
		if ( lengthsquared( player getEntityVelocity() ) < 10 )
			continue;

		if ( player damageConeTrace( self.origin, self ) > 0 )
			break;
	}

	self notify( "mine_triggered" );
	
	self playsound( "mine_betty_click" );
	
	if ( IsPlayer( player ) && player _hasPerk( "specialty_delaymine" ) )
	{
		player notify( "triggered_mine" );
		wait level.delayMineTime;
	}
	else 
		wait level.mineDetectionGracePeriod;

	self thread mineBounce();
}

mineDeleteTrigger( trigger )
{
	self waittill_any( "mine_triggered", "mine_destroyed", "mine_selfdestruct", "death" );

	trigger delete();
}

mineSelfDestruct()
{
	self endon( "mine_triggered" );
	self endon( "mine_destroyed" );
	self endon( "death" );
	
	wait( level.mineSelfDestructTime );
	wait RandomFloat( 0.4 );

	self notify( "mine_selfdestruct" );
	self thread mineExplode();
}

// TODO: 
//		 Handle a drop outside of a level, like highrise.
//		 Spawn protection against these. "protect players from spawnkill grenades"
//		 Killcam doesn't fly up. Probably needs code.
mineBounce()
{
	self playsound( "mine_betty_spin" );
	playFX( level.mine_launch, self.origin );
	
	explodePos = self.origin + (0, 0, 64);
	self MoveTo( explodePos, 0.7, 0, .65 );
	self.killCamEnt MoveTo( explodePos + self.killCamOffset, 0.7, 0, .65 );

	self RotateVelocity( (0, 750, 32), 0.7, 0, .65 );
	self thread playSpinnerFX();

	wait( 0.65 );

	self thread mineExplode();
}

mineExplode( attacker )
{
	if ( !IsDefined( self ) || !IsDefined(self.owner) )
		return;
	
	// using a passed in attacker means that the owner wasn't the one who detonated this, this way the correct credit will go to the correct player
	if( !IsDefined( attacker ) )
		attacker = self.owner;

	self PlaySound( "grenade_explode_metal" );
	PlayFXOnTag( level.mine_explode, self, "tag_fx" );
	
	wait( 0.05 ); // needed or the effect doesn't play
	if ( !IsDefined( self ) || !IsDefined(self.owner) )
		return;
	
	self Hide();
	self RadiusDamage( self.origin, level.mineDamageRadius, level.mineDamageMax, level.mineDamageMin, attacker, "MOD_EXPLOSIVE", "bouncingbetty_mp" );
	
	wait( 0.2 ); 
	if ( !IsDefined( self ) || !IsDefined(self.owner) )
		return;
	
	if ( IsDefined( self.trigger ) )
		self.trigger delete();
	
	self.killCamEnt delete();
	self delete();
}

playSpinnerFX()
{
	self endon( "death");
	
	timer = gettime() + 1000;
	
	while ( gettime() < timer )
	{
		wait .05;
		playFXontag( level.mine_spin, self, "tag_fx_spin1" );
		playFXontag( level.mine_spin, self, "tag_fx_spin3" );
		wait .05;
		playFXontag( level.mine_spin, self, "tag_fx_spin2" );
		playFXontag( level.mine_spin, self, "tag_fx_spin4" );
	}
}

/*mineDamagePassed( damageCenter, recieverCenter, radiusSq, ignoreEnt )
{
	damageTop = damageCenter[2] + level.mineDamageHalfHeight;
	damageBottom = damageCenter[2] - level.mineDamageHalfHeight;

	/#
	if ( getdvarint( "scr_debugMines" ) != 0 )
		thread mineDamageDebug( damageCenter, recieverCenter, radiusSq, ignoreEnt, damageTop, damageBottom );
	#/

	if ( recieverCenter[2] > damageTop || recieverCenter[2] < damageBottom )
		return false;

	distSq = distanceSquared( damageCenter, recieverCenter );
	if ( distSq > radiusSq )
		return false;

	if ( !weaponDamageTracePassed( damageCenter, recieverCenter, 0, ignoreEnt ) )
		return false;

	return true;
}*/

mineDamageDebug( damageCenter, recieverCenter, radiusSq, ignoreEnt, damageTop, damageBottom )
{
	color[0] = ( 1, 0, 0 );
	color[1] = ( 0, 1, 0 );

	/*if ( recieverCenter[2] > damageTop )
		pass = false;
	else
		pass = true;

	damageTopOrigin = ( damageCenter[0], damageCenter[1], damageTop );
	recieverTopOrigin = ( recieverCenter[0], recieverCenter[1], damageTop );
	thread debugcircle( damageTopOrigin, level.mineDamageRadius, color[pass], 32 );*/
	
	if ( recieverCenter[2] < damageBottom  )
		pass = false;
	else
		pass = true;

	damageBottomOrigin = ( damageCenter[0], damageCenter[1], damageBottom );
	recieverBottomOrigin = ( recieverCenter[0], recieverCenter[1], damageBottom );
	thread debugcircle( damageBottomOrigin, level.mineDamageRadius, color[pass], 32 );

	distSq = distanceSquared( damageCenter, recieverCenter );
	if ( distSq > radiusSq )
		pass = false;
	else
		pass = true;

	thread debugline( damageBottomOrigin, recieverBottomOrigin, color[pass] );
}

mineDamageHeightPassed( mine, victim )
{
	if ( isPlayer( victim ) && isAlive( victim ) && victim.sessionstate == "playing" )
		victimPos = victim getStanceCenter();
	else if ( victim.classname == "misc_turret" )
		victimPos = victim.origin + ( 0, 0, 32 );
	else
		victimPos = victim.origin;
	
	tempZOffset = 0; //66
	damageTop = mine.origin[2] + tempZOffset + level.mineDamageHalfHeight;  //46
	damageBottom = mine.origin[2] + tempZOffset - level.mineDamageHalfHeight;

	/#
	//if ( getdvarint( "scr_debugMines" ) != 0 )
		//thread mineDamageDebug( damageCenter, recieverCenter, radiusSq, victim, damageTop, damageBottom );
	#/

	if ( victimPos[2] > damageTop || victimPos[2] < damageBottom )
		return false;

	return true;
}

watchMineUsage()
{
	self endon( "disconnect" );
	self endon( "spawned_player" );
	
	if ( isDefined( self.equipmentMines ) )
	{
		if ( getIntProperty( "scr_deleteexplosivesonspawn", 1 ) == 1 )
		{
			self.equipmentMines = array_removeUndefined( self.equipmentMines );
			foreach ( equipmentMine in self.equipmentMines )
			{
				if ( isDefined( equipmentMine.trigger ) )
					equipmentMine.trigger delete();
			
				equipmentMine delete();
			}
		}
	}
	else
	{
		self.equipmentMines = [];
	}

	if ( !isDefined( self.killstreakMines ) )
		self.killstreakMines = [];
	
	thread mineDeleteOnDisconnect();

	for ( ;; )
	{
		self waittill( "grenade_fire", projectile, weaponName );
		if ( weaponName == "bouncingbetty" || weaponName == "bouncingbetty_mp" )		
		{
			if( !IsAlive( self ) )
			{
				projectile delete();
				return;
			}

			self.hasDoneCombat = true;

			projectile thread mineThrown( self );
		}
	}
}

mineDeleteOnDisconnect()
{
	self endon( "death" );
	self waittill( "disconnect" );

	equipmentMines = self.equipmentMines;
	killstreakMines = self.killstreakMines;

	wait .05;

	equipmentMines = array_removeUndefined( equipmentMines );
	foreach ( equipmentMine in equipmentMines )
	{
		if ( isDefined( equipmentMine.trigger ) )
			equipmentMine.trigger delete();
			
		equipmentMine delete();
	}

	killstreakMines = array_removeUndefined( killstreakMines );
	foreach ( killstreakMine in killstreakMines )
		killstreakMine delete();
}

// TODO: need self endon( "death" ); but also need an explosion to still happen
// TODO: fix beacon effect lasting through launch
// What if we never get "missile_stuck"? Endon death happen automatically after a set lifetime has passed?
// Owner may not exist by the time it is used. (maybe make this run on owner instead)
// Hitting trigger after respawn on these causes a script error.
mineThrown( owner )
{
	self.owner = owner;
	
	self waittill( "missile_stuck" );

	if( !isDefined( owner ) )
		return;
	
	trace = bulletTrace( self.origin + (0, 0, 4), self.origin - (0, 0, 4), false, self );
	
	pos = trace["position"];
	if ( trace["fraction"] == 1 ) //wtf, stuck to somthing that trace didnt hit
	{	
		pos = GetGroundPosition( self.origin, 12, 0, 32);
		trace["normal"] *= -1;
	}
	
	normal = vectornormalize( trace["normal"] );
	plantAngles = vectortoangles( normal );
	plantAngles += ( 90, 0, 0 );
	
	mine = spawnMine( pos, owner, "equipment", plantAngles );
	mine.trigger = spawn( "script_origin", mine.origin + (0,0,25) );
	mine thread equipmentWatchUse( owner );

	self delete();
}

mineBeacon()
{
	effect["friendly"] = SpawnFx( level.mine_beacon["friendly"], self getTagOrigin( "tag_fx" ) );
	effect["enemy"] = SpawnFx( level.mine_beacon["enemy"], self getTagOrigin( "tag_fx" ) );

	self thread mineBeaconTeamUpdater( effect );
	self waittill( "death" );
	
	effect["friendly"] delete();
	effect["enemy"] delete();
}

mineBeaconTeamUpdater( effect )
{
	self endon ( "death" );
	
	ownerTeam = self.owner.team;
	
	// PlayFXOnTag fails if run on the same frame the parent entity was created
	wait ( 0.05 );
	
	TriggerFx( effect["friendly"] ); //?
	TriggerFx( effect["enemy"] ); //?
	
	for ( ;; )
	{
		effect["friendly"] Hide();
		effect["enemy"] Hide();

		foreach ( player in level.players )
		{
			if ( level.teamBased )
			{
				if ( player.team == ownerTeam )
					effect["friendly"] showToPlayer( player );
				else
					effect["enemy"] showToPlayer( player );
			}
			else
			{
				if ( player == self.owner )
					effect["friendly"] showToPlayer( player );
				else
					effect["enemy"] showToPlayer( player );
			}
		}
		
		level waittill_either ( "joined_team", "player_spawned" );
	}
}
