#include maps\_utility;
#include animscripts\utility;
#include animscripts\Combat_utility;
#include animscripts\notetracks;
#include animscripts\melee;
#include common_scripts\utility;

RIOTSHIELD_FACE_ENEMY_DIST = 1500;
RIOTSHIELD_FORCE_WALK_DIST = 500;

#using_animtree( "generic_human" );

init_riotshield_AI_anims()
{
	anim.notetracks[ "detach shield" ] = ::noteTrackDetachShield;

	animscripts\init_move_transitions::init_move_transition_arrays();

	anim.coverTrans[ "riotshield" ] = [];
	anim.coverTrans[ "riotshield" ][ 1 ] = %riotshield_run_approach_1;
	anim.coverTrans[ "riotshield" ][ 2 ] = %riotshield_run_approach_2;
	anim.coverTrans[ "riotshield" ][ 3 ] = %riotshield_run_approach_3;
	anim.coverTrans[ "riotshield" ][ 4 ] = %riotshield_run_approach_4;
	anim.coverTrans[ "riotshield" ][ 6 ] = %riotshield_run_approach_6;
	anim.coverTrans[ "riotshield" ][ 7 ] = undefined;
	anim.coverTrans[ "riotshield" ][ 8 ] = %riotshield_walk2crouch_8;
	anim.coverTrans[ "riotshield" ][ 9 ] = undefined;

	anim.coverTrans[ "riotshield_crouch" ] = [];
	anim.coverTrans[ "riotshield_crouch" ][ 1 ] = %riotshield_walk_approach_1;
	anim.coverTrans[ "riotshield_crouch" ][ 2 ] = %riotshield_walk_approach_2;
	anim.coverTrans[ "riotshield_crouch" ][ 3 ] = %riotshield_walk_approach_3;
	anim.coverTrans[ "riotshield_crouch" ][ 4 ] = %riotshield_walk_approach_4;
	anim.coverTrans[ "riotshield_crouch" ][ 6 ] = %riotshield_walk_approach_6;
	anim.coverTrans[ "riotshield_crouch" ][ 7 ] = undefined;
	anim.coverTrans[ "riotshield_crouch" ][ 8 ] = %riotshield_walk2crouch_8;
	anim.coverTrans[ "riotshield_crouch" ][ 9 ] = undefined;

	riotshieldTransTypes = [];
	riotshieldTransTypes[0] = "riotshield";
	riotshieldTransTypes[1] = "riotshield_crouch";

	for ( j = 0; j < riotshieldTransTypes.size; j++ )
	{
		trans = riotshieldTransTypes[ j ];

		for ( i = 1; i <= 9; i++ )
		{
			if ( i == 5 )
				continue;

			if ( isdefined( anim.coverTrans[ trans ][ i ] ) )
			{
				anim.coverTransDist  [ trans ][ i ] = getMoveDelta( anim.coverTrans[ trans ][ i ], 0, 1 );
			}
		}
	}

	anim.coverTransAngles[ "riotshield_crouch" ][ 1 ] = 45;
	anim.coverTransAngles[ "riotshield_crouch" ][ 2 ] = 0;
	anim.coverTransAngles[ "riotshield_crouch" ][ 3 ] = -45;
	anim.coverTransAngles[ "riotshield_crouch" ][ 4 ] = 90;
	anim.coverTransAngles[ "riotshield_crouch" ][ 6 ] = -90;
	anim.coverTransAngles[ "riotshield_crouch" ][ 8 ] = 180;

	anim.coverTransAngles[ "riotshield" ][ 1 ] = 45;
	anim.coverTransAngles[ "riotshield" ][ 2 ] = 0;
	anim.coverTransAngles[ "riotshield" ][ 3 ] = -45;
	anim.coverTransAngles[ "riotshield" ][ 4 ] = 90;
	anim.coverTransAngles[ "riotshield" ][ 6 ] = -90;
	anim.coverTransAngles[ "riotshield" ][ 8 ] = 180;

	anim.arrivalEndStance[ "riotshield" ] = "crouch";
	anim.arrivalEndStance[ "riotshield_crouch" ] = "crouch";


	addGrenadeThrowAnimOffset( %riotshield_crouch_grenade_toss, (-3.20014, 1.7098, 55.6886) );
}

noteTrackDetachShield( note, flagName )
{
	self animscripts\shared::DropAIWeapon( self.secondaryWeapon );
	self.secondaryWeapon = "none";

	if ( isAlive( self ) )
		riotshield_turn_into_regular_ai();
}

riotshield_approach_type()
{
	if ( self.a.pose == "crouch" )
		return "riotshield_crouch";

	return "riotshield";
}

riotshield_approach_conditions( node )
{
	// to allow approach while facing enemy and crouch walking
	return true;
}


init_riotshield_AI()
{
	//shieldModel = getWeaponModel( self.secondaryWeapon );
	//self attach( shieldModel, "tag_weapon_left" );

	animscripts\shared::placeWeaponOn( self.secondaryWeapon, "left", false );

	self InitRiotshieldHealth( self.secondaryWeapon );
	self.shieldModelVariant = 0;
	self thread riotshield_damaged();

	self.subclass = "riotshield";	// incase guy didn't spawn as a "riotshield" ai

	self.approachTypeFunc = ::riotshield_approach_type;
	self.approachConditionCheckFunc = ::riotshield_approach_conditions;

	self.faceEnemyArrival = true;
	self.disableCoverArrivalsOnly = true;
	self.pathRandomPercent = 0;
	self.interval = 0;
	self.disableDoorBehavior = true;
	self.no_pistol_switch = true;
	self.dontShootWhileMoving = true;
	self.disableBulletWhizbyReaction = true;
	self.disableFriendlyFireReaction = true;
	self.neverSprintForVariation = true;
	self.combatMode = "no_cover";
	self.fixednode = false;
	self.maxFaceEnemyDist = RIOTSHIELD_FACE_ENEMY_DIST;
	self.noMeleeChargeDelay = true;
	self.meleeChargeDistSq = squared( 256 );
	self.meleePlayerWhileMoving = true;
	self.useMuzzleSideOffset = true;

	// fall over after getting hit this many times on the shield all within 0.3 seconds of each other
	if ( level.gameSkill < 1 )
		self.shieldBulletBlockLimit = randomintrange( 4, 8 );
	else
		self.shieldBulletBlockLimit = randomintrange( 8, 12 );

	self.shieldBulletBlockCount = 0;
	self.shieldBulletBlockTime = 0;

	self.walkDist = RIOTSHIELD_FORCE_WALK_DIST;
	self.walkDistFacingMotion = RIOTSHIELD_FORCE_WALK_DIST;

	self.grenadeAwareness = 1;
	self.frontShieldAngleCos = 0.5;
	self.noGrenadeReturnThrow = true;
	self.a.grenadeThrowPose = "crouch";
	self.minExposedGrenadeDist = 400;

	self.ignoresuppression = true;

	self.specialMelee_Standard = ::riotshield_melee_standard;
	self.specialMeleeChooseAction = ::riotshield_melee_AIvsAI;

	self disable_turnAnims();
	self disable_surprise();
	self disable_cqbwalk();

	init_riotshield_animsets();

	if ( level.gameSkill < 1 )
		self.bullet_resistance = 30;
	else
		self.bullet_resistance = 40;

	self add_damage_function( maps\_spawner::bullet_resistance );
	self add_damage_function( animscripts\pain::additive_pain );
}


riotshield_charge()
{
	if ( !Melee_Standard_UpdateAndValidateTarget() )
		return false;

	// get from animation
	delta = getMoveDelta( %riotshield_bashA_attack, 0, 1 );
	rangeSq = lengthSquared( delta );

	if ( distanceSquared( self.origin, self.melee.target.origin ) < rangeSq )
		return true;

	self animscripts\melee::Melee_PlayChargeSound();

	sampleTime = 0.1;
	firstTry = true;

	while ( 1 )
	{
		assert( isdefined( self.melee.target ) );

		// now that we moved a bit, see if our target moved before we check for valid melee
		// it's possible something happened in the meantime that makes meleeing impossible.
		if ( !Melee_Standard_UpdateAndValidateTarget() )
			return false;

		if ( firstTry )
		{
			self.a.pose = "stand";
			self SetFlaggedAnimKnobAll( "chargeanim", %riotshield_sprint, %body, 1, .2, 1 );
			firstTry = false;
		}

		self orientMode( "face point", self.melee.target.origin );
		self DoNoteTracksForTime( sampleTime, "chargeanim" );

		enemyDistanceSq = distanceSquared( self.origin, self.melee.target.origin );

		// if we're done raising our gun, and starting a melee now will hit the guy, our preparation is finished
		if ( enemyDistanceSq < rangeSq )
			break;

		// don't keep charging if we've been doing this for too long.
		if ( gettime() >= self.melee.giveUpTime )
			return false;
	}

	return true;
}


riotshield_melee_standard()
{
	self animMode( "zonly_physics" );

	animscripts\melee::Melee_Standard_ResetGiveUpTime();

    while ( true )
    {
		if ( !riotshield_charge() )
		{
			// if we couldn't get in place to melee, don't try to charge for a little while and abort
			self.nextMeleeChargeTime = getTime() + 1500;
			self.nextMeleeChargeTarget = self.melee.target;
			break;
		}

		assert( (self.a.pose == "stand") || (self.a.pose == "crouch") );

		self animscripts\battleChatter_ai::evaluateMeleeEvent();

		self orientMode( "face point", self.melee.target.origin );
		self setflaggedanimknoballrestart( "meleeanim", %riotshield_bash_vs_player, %body, 1, .2, 1 );

		self.melee.inProgress = true;

		// If the attack loop returns false, we need to stop this melee
		if( !animscripts\melee::Melee_Standard_PlayAttackLoop() )
		{
			// Since getting here means that we've done a melee but our attack is no longer valid, delay before we can do a standard attack again.
			animscripts\melee::Melee_Standard_DelayStandardCharge( self.melee.target );
			break;
		}

		self animMode( "none" );
    }

	self animMode( "none" );
}

riotshield_melee_AIvsAI()
{
	assert( isDefined( self ) );
	assert( isDefined( self.melee.target ) );

	target = self.melee.target;
	
	// Don't let two riotshield guys script melee eachother because the
	// weapons clip with the shields badly.
	if	( self.subclass == "riotshield" && target.subclass == "riotshield" )
	{
		return false;
	}
	
	animscripts\melee::Melee_Decide_Winner();

	// Choose which sequence to play based on angles
	angleToEnemy = vectortoangles( target.origin - self.origin );
	angleDiff = AngleClamp180( target.angles[ 1 ] - angleToEnemy[ 1 ] );

	if ( abs( angleDiff ) > 100 )		// facing each other
	{
		if ( self.melee.winner )
		{
			if ( self.subclass == "riotshield" )
			{
				self.melee.animName = %riotshield_bashA_attack;
				target.melee.animName = %riotshield_bashA_defend;
				target.melee.surviveAnimName = %riotshield_bashA_defend_survive;
			}
			else
			{
				assert( target.subclass == "riotshield" );
				self.melee.animName = %riotshield_bashB_defend;
				target.melee.animName = %riotshield_bashB_attack;
			}
		}
		else
		{
			if ( self.subclass == "riotshield" )
			{
				self.melee.animName = %riotshield_bashB_attack;
				target.melee.animName = %riotshield_bashB_defend;
			}
			else
			{
				assert( target.subclass == "riotshield" );
				self.melee.animName = %riotshield_bashA_defend;
				target.melee.animName = %riotshield_bashA_attack;
			}
		}
	}
	else
	{
		return false;
	}

	self.melee.startPos = getStartOrigin( target.origin, target.angles, self.melee.animName );
	self.melee.startAngles = ( target.angles[0], AngleClamp180( target.angles[1] + 180 ), target.angles[2] );

	self.lockOrientation = false;
	target.lockOrientation = false;

	// Make sure we can move to the selected point ( no re-try for now )
	return Melee_UpdateAndValidateStartPos();
}

riotshield_startMoveTransition()
{
	if ( isdefined( self.disableExits ) )
		return;

	self orientmode( "face angle", self.angles[1] );
	self animmode( "zonly_physics", false );

	if ( self.a.pose == "crouch" )
	{
		if ( isdefined( self.sprint ) || isdefined( self.fastwalk ) )
			transAnim = %riotshield_crouch2stand;
		else
			transAnim = %riotshield_crouch2walk;

		rate = randomfloatrange( 0.9, 1.1 );
		self setFlaggedAnimKnobAllRestart( "startmove", transAnim, %body, 1, .1, rate );
		self animscripts\shared::DoNoteTracks( "startmove" );
		self clearanim( %riotshield_crouch2walk, 0.5 );
	}

	if ( isdefined( self.sprint ) || isdefined( self.fastwalk ) )
	{
		self allowedStances( "stand", "crouch" );
		self.a.pose = "stand";
	}

	self orientmode( "face default" );
	self animMode( "normal", false );

	self thread riotshield_bullet_hit_shield();
}

riotshield_endMoveTransition()
{
	if ( self.prevScript == "move" && self.a.pose == "crouch" )
	{
		self clearAnim( %root, .2 );

		rate = randomfloatrange( 0.9, 1.1 );
		self animmode( "zonly_physics" );
		self setFlaggedAnimKnobAllRestart( "endmove", %riotshield_walk2crouch_8, %body, 1, .2, rate );
		self animscripts\shared::DoNoteTracks( "endmove" );
		self animMode( "normal" );
	}

	self allowedStances( "crouch" );
}

riotshield_startCombat()
{
	//assertex( self.combatmode == "no_cover", "riotshield AI combat mode should be 'no_cover'" );
	riotshield_endMoveTransition();
	self.pushable = false;
	self thread riotshield_bullet_hit_shield();
}

riotshield_bullet_hit_shield()
{
	self endon( "killanimscript" );

	while (1)
	{
		self waittill( "bullet_hitshield" );

		time = gettime();
		if ( time - self.shieldBulletBlockTime > 500 )
			self.shieldBulletBlockCount = 0;
		else
			self.shieldBulletBlockCount++;

		self.shieldBulletBlockTime = time;
		if ( self.shieldBulletBlockCount > self.shieldBulletBlockLimit )
			self doDamage( 1, ( 0, 0, 0 ) );	// do minimal damage to fall down

		if ( cointoss() )
			reactAnim = %riotshield_reactA;
		else
			reactAnim = %riotshield_reactB;

		self notify( "new_hit_react" );
		self setFlaggedAnimRestart( "hitreact", reactAnim, 1, 0.1, 1 );
		self thread riotshield_bullet_hit_shield_clear();
	}
}


riotshield_bullet_hit_shield_clear()
{
	self endon( "killanimscript" );
	self endon( "new_hit_react" );

	self waittillmatch( "hitreact", "end" );
	self clearanim( %riotshield_react, 0.1 );
}


riotshield_grenadeCower()
{
	if ( self.a.pose == "stand" )
	{
		self clearanim( %root, .2 );
		self setFlaggedAnimKnobAllRestart( "trans", %riotshield_walk2crouch_8, %body, 1, .2, 1.2 );
		self animscripts\shared::DoNoteTracks( "trans" );
	}

	if ( isdefined( self.grenade ) )
	{
		faceGrenade = true;
		dirToGrenade = self.grenade.origin - self.origin;

		if ( isdefined( self.enemy ) )
		{
			dirToEnemy = self.enemy.origin - self.origin;
			if ( vectorDot( dirToGrenade, dirToEnemy ) < 0 )
				faceGrenade = false;
		}

		if ( faceGrenade )
		{
			relYaw = AngleClamp180( self.angles[ 1 ] - vectorToYaw( dirToGrenade ) );

			if ( !isdefined( self.turnThreshold ) )
				self.turnThreshold = 55;

			while ( abs( relYaw ) > self.turnThreshold )
			{
				if ( !isdefined( self.a.array ) )
					animscripts\combat::setup_anim_array();

				if ( !self animscripts\combat::TurnToFaceRelativeYaw( relYaw ) )
					break;

				relYaw = AngleClamp180( self.angles[ 1 ] - vectorToYaw( dirToGrenade ) );
			}
		}
	}

	self setAnimKnobAll( %riotshield_crouch_aim_5, %body, 1, 0.2, 1 );
	self setFlaggedAnimKnobAllRestart( "grenadecower", %riotshield_crouch_idle_add, %add_idle, 1, 0.2, self.animplaybackrate );
	self animscripts\shared::DoNoteTracks( "grenadecower" );
}

// TO DO: Julian
// IW5 BUG 167874: When an AI is on his back, the AI will get stuck in DoNoteTracks() forever if AI wasn't playing an animation
// Only checking for self.a.onback to assuming something was playing is not safe.

riotshield_flashbang()
{
	self notify( "flashed" );

	if ( !isdefined( self.a.onback ) )
	{
		rate = randomfloatrange( 0.9, 1.1 );
		self.frontShieldAngleCos = 1;

		flashArray = [];
		flashArray[0] = %riotshield_crouch_grenade_flash1;
		flashArray[1] = %riotshield_crouch_grenade_flash2;
		flashArray[2] = %riotshield_crouch_grenade_flash3;
		flashArray[3] = %riotshield_crouch_grenade_flash4;
		flashAnim = flashArray[ randomint( flashArray.size ) ];

		self setFlaggedAnimKnobAllRestart( "flashanim", flashAnim, %body, 1, .1, rate );
		self.minPainDamage = 1000;
		
		self animscripts\shared::DoNoteTracks( "flashanim" );		
	}
	else
	{
		wait 0.1; // introducing delay as DoNoteTracks() would always have some delay. TO DO [rescript later]
	}
	
	self.minPainDamage = 0;
	if ( IsDefined( self.subclass ) && self.subclass == "riotshield" )
	{
		self.frontShieldAngleCos = 0.5;
	}
}


riotshield_pain()
{
	// all the pain animations are in crouch
	self.a.pose = "crouch";

	if ( usingSideArm() )
		forceUseWeapon( self.primaryweapon, "primary" );

	if ( !isdefined( self.a.onback ) )
	{
		rate = randomfloatrange( 0.8, 1.15 );
		self.frontShieldAngleCos = 1;
		if ( ( self.damageYaw < -120 || self.damageYaw > 120 ) && isExplosiveDamageMOD( self.damageMOD ) )
		{
			painArray = [];
			painArray[0] = %riotshield_crouch_grenade_blowback;
			painArray[1] = %riotshield_crouch_grenade_blowbackL;
			painArray[2] = %riotshield_crouch_grenade_blowbackR;
			painAnim = painArray[ randomint( painArray.size ) ];

			self setFlaggedAnimKnobAllRestart( "painanim", painAnim, %body, 1, .2, rate );
			self.minPainDamage = 1000;
		}
		else
		{
			self setFlaggedAnimKnobAllRestart( "painanim", %riotshield_crouch_pain, %body, 1, .2, rate );
		}
		
		self animscripts\shared::DoNoteTracks( "painanim" );
	}
	else
	{
		wait 0.1; // introducing delay as DoNoteTracks() would always have some delay. TO DO [rescript later]
	}

	self.minPainDamage = 0;
	if ( IsDefined( self.subclass ) && self.subclass == "riotshield" )
	{
		self.frontShieldAngleCos = 0.5;
	}
}

riotshield_death()
{
	if ( isdefined( self.a.onback ) && self.a.pose == "crouch" )
	{
		deathArray = [];
		deathArray[0] = %dying_back_death_v2;
		deathArray[1] = %dying_back_death_v3;
		deathArray[2] = %dying_back_death_v4;
		deathAnim = deathArray[ randomint( deathArray.size ) ];

		self animscripts\death::playDeathAnim( deathAnim );
		return true;
	}

	if ( self.prevScript == "pain" || self.prevScript == "flashed" )
		doShieldDeath = randomInt( 2 ) == 0;
	else
		doShieldDeath = true;

	if ( doShieldDeath )
	{
		if ( cointoss() )
			deathAnim = %riotshield_crouch_death;
		else
			deathAnim = %riotshield_crouch_death_fallback;

		self animscripts\death::playDeathAnim( deathAnim );
		return true;
	}

	self.a.pose = "crouch";
	return false;
}

init_riotshield_animsets()
{
	// move animations
	animset = [];
	animset[ "sprint" ] = %riotshield_sprint;
	animset[ "prone" ] = %prone_crawl;

	animset[ "straight" ] = %riotshield_run_F;

	animset[ "move_f" ] = %riotshield_run_F;
	animset[ "move_l" ] = %riotshield_run_L;
	animset[ "move_r" ] = %riotshield_run_R;
	animset[ "move_b" ] = %riotshield_run_B;

	animset[ "crouch" ] = %riotshield_crouchwalk_F;
	animset[ "crouch_l" ] = %riotshield_crouchwalk_L;
	animset[ "crouch_r" ] = %riotshield_crouchwalk_R;
	animset[ "crouch_b" ] = %riotshield_crouchwalk_B;

	animset[ "stairs_up" ] = %traverse_stair_run_01;
	animset[ "stairs_down" ] = %traverse_stair_run_down;

	self.customMoveAnimSet[ "run" ] = animset;
	self.customMoveAnimSet[ "walk" ] = animset;
	self.customMoveAnimSet[ "cqb" ] = animset;

	self.customIdleAnimSet = [];
	self.customIdleAnimSet[ "crouch" ] = %riotshield_crouch_aim_5;
	self.customIdleAnimSet[ "crouch_add" ] = %riotshield_crouch_idle_add;
	self.customIdleAnimSet[ "stand" ] = %riotshield_crouch_aim_5;
	self.customIdleAnimSet[ "stand_add" ] = %riotshield_crouch_idle_add;

	self.a.pose = "crouch";
	self allowedStances( "crouch" );

	// combat animations
	animset = anim.animsets.defaultStand;

	animset[ "add_aim_up" ] = %riotshield_crouch_aim_8;
	animset[ "add_aim_down" ] = %riotshield_crouch_aim_2;
	animset[ "add_aim_left" ] = %riotshield_crouch_aim_4;
	animset[ "add_aim_right" ] = %riotshield_crouch_aim_6;

	animset[ "straight_level" ] = %riotshield_crouch_aim_5;

	animset[ "fire" ] = %riotshield_crouch_fire_auto;
	animset[ "single" ] = array( %riotshield_crouch_fire_single );

	// remove this burst, semi nonsense soon
	animset[ "burst2" ] = %riotshield_crouch_fire_burst;
	animset[ "burst3" ] = %riotshield_crouch_fire_burst;
	animset[ "burst4" ] = %riotshield_crouch_fire_burst;
	animset[ "burst5" ] = %riotshield_crouch_fire_burst;
	animset[ "burst6" ] = %riotshield_crouch_fire_burst;
	animset[ "semi2" ] = %riotshield_crouch_fire_burst;
	animset[ "semi3" ] = %riotshield_crouch_fire_burst;
	animset[ "semi4" ] = %riotshield_crouch_fire_burst;
	animset[ "semi5" ] = %riotshield_crouch_fire_burst;

	animset[ "exposed_idle" ] = array( %riotshield_crouch_idle_add, %riotshield_crouch_twitch );
	animset[ "exposed_grenade" ] = array( %riotshield_crouch_grenade_toss );

	animset[ "reload" ] = array( %riotshield_crouch_reload );
	animset[ "reload_crouchhide" ] = array( %riotshield_crouch_reload );

	animset[ "turn_left_45" ] = %riotshield_crouch_Lturn;
	animset[ "turn_left_90" ] = %riotshield_crouch_Lturn;
	animset[ "turn_left_135" ] = %riotshield_crouch_Lturn;
	animset[ "turn_left_180" ] = %riotshield_crouch_Lturn;
	animset[ "turn_right_45" ] = %riotshield_crouch_Rturn;
	animset[ "turn_right_90" ] = %riotshield_crouch_Rturn;
	animset[ "turn_right_135" ] = %riotshield_crouch_Rturn;
	animset[ "turn_right_180" ] = %riotshield_crouch_Rturn;

	animset[ "stand_2_crouch" ] = %riotshield_walk2crouch_8;

	self animscripts\animset::init_animset_complete_custom_stand( animset );
	self animscripts\animset::init_animset_complete_custom_crouch( animset );

	self.choosePoseFunc = ::riotshield_choose_pose;
	self.painFunction = ::riotshield_pain;
	self.specialDeathFunc = ::riotshield_death;
	self.specialFlashedFunc = ::riotshield_flashbang;
	self.grenadeCowerFunction = ::riotshield_grenadeCower;
	self.customMoveTransition = ::riotshield_startMoveTransition;
	self.permanentCustomMoveTransition = true;

	set_exception( "exposed", ::riotshield_startCombat );
	//set_exception( "stop_immediate", ::riotshield_endMoveTransition );
}

riotshield_choose_pose( preferredPose )
{
	if ( isdefined( self.grenade ) )
		return "stand";

	return self animscripts\utility::choosePose( preferredPose );
}


riotshield_sprint_on()
{
	self.maxFaceEnemyDist = 128;
	self.sprint = true;
	self orientmode( "face default" );
	self.lockorientation = false;

	self.walkDist = 32;
	self.walkDistFacingMotion = 32;
}

riotshield_fastwalk_on()
{
	self.maxFaceEnemyDist = 128;
	self.fastwalk = true;

	self.walkDist = 32;
	self.walkDistFacingMotion = 32;
}


riotshield_sprint_off()
{
	self.maxFaceEnemyDist = RIOTSHIELD_FACE_ENEMY_DIST;

	self.walkDist = RIOTSHIELD_FORCE_WALK_DIST;
	self.walkDistFacingMotion = RIOTSHIELD_FORCE_WALK_DIST;
	self.sprint = undefined;
	self allowedStances( "crouch" );
}

riotshield_fastwalk_off()
{
	self.maxFaceEnemyDist = RIOTSHIELD_FACE_ENEMY_DIST;

	self.walkDist = RIOTSHIELD_FORCE_WALK_DIST;
	self.walkDistFacingMotion = RIOTSHIELD_FORCE_WALK_DIST;
	self.fastwalk = undefined;
	self allowedStances( "crouch" );
}

null_func()
{
}

riotshield_init_flee()
{
	// hack to restart move script
	if ( self.script == "move" )
		self animcustom( ::null_func );

	self.customMoveTransition = ::riotshield_flee_and_drop_shield;
}

riotshield_flee_and_drop_shield()
{
	// restore this incase flee gets interrupted
	self.customMoveTransition = ::riotshield_startMoveTransition;

	self animmode( "zonly_physics", false );
	self orientmode( "face current" );

	if ( !isdefined( self.dropShieldInPlace ) && isdefined( self.enemy ) && vectordot( self.lookaheadDir, anglesToForward( self.angles ) ) < 0 )
		fleeAnim = %riotshield_crouch2walk_2flee;
	else
		fleeAnim = %riotshield_crouch2stand_shield_drop;

	rate = randomFloatRange( 0.85, 1.1 );
	self SetFlaggedAnimKnobAll( "fleeanim", fleeAnim, %root, 1, .1, rate );
	self animscripts\shared::DoNoteTracks( "fleeanim" );	// return on code_move

	self.maxFaceEnemyDist = 32;
	self.lockOrientation = false;
	self orientmode( "face default" );
	self animmode( "normal", false );
	self animscripts\shared::DoNoteTracks( "fleeanim" );
	self clearanim( fleeAnim, 0.2 );
	self.maxFaceEnemyDist = 128;
}

riotshield_turn_into_regular_ai()
{
	self.subclass = "regular";

	self.combatMode = "cover";

	self.approachTypeFunc = undefined;
	self.approachConditionCheckFunc = undefined;
	self.faceEnemyArrival = undefined;
	self.disableCoverArrivalsOnly = undefined;
	self.pathRandomPercent = 0;
	self.interval = 80;
	self.disableDoorBehavior = undefined;
	self.no_pistol_switch = undefined;
	self.dontShootWhileMoving = undefined;
	self.disableBulletWhizbyReaction = undefined;
	self.disableFriendlyFireReaction = undefined;
	self.neverSprintForVariation = undefined;
	self.maxFaceEnemyDist = 128;
	self.noMeleeChargeDelay = undefined;
	self.meleeChargeDistSq = undefined;
	self.meleePlayerWhileMoving = undefined;
	self.useMuzzleSideOffset = undefined;

	self.pathEnemyFightDist = 128;
	self.pathenemylookahead = 128;

	self.walkDist = 256;
	self.walkDistFacingMotion = 64;
	self.lockorientation = false;

	self.frontShieldAngleCos = 1;
	self.noGrenadeReturnThrow = false;

	self.ignoresuppression = false;
	self.sprint = undefined;

	self allowedStances( "stand", "crouch", "prone" );

	self.specialMelee_Standard = undefined;
	self.specialMeleeChooseAction = undefined;

	self enable_turnAnims();

	self.bullet_resistance = undefined;
	self remove_damage_function( maps\_spawner::bullet_resistance );
	self remove_damage_function( animscripts\pain::additive_pain );

	self animscripts\animset::clear_custom_animset();

	self.choosePoseFunc = animscripts\utility::choosePose;
	self.painFunction = undefined;
	self.specialDeathFunc = undefined;
	self.specialFlashedFunc = undefined;
	self.grenadeCowerFunction = undefined;
	self.customMoveTransition = undefined;
	self.permanentCustomMoveTransition = undefined;

	clear_exception( "exposed" );
	clear_exception( "stop_immediate" );
}

riotshield_damaged()
{
	self endon( "death" );
	self waittill( "riotshield_damaged" );
	self.shieldBroken = 1;

    self animscripts\shared::detachAllWeaponModels();
    self.shieldModelVariant = 1;
    self animscripts\shared::updateAttachedWeaponModels();
}
