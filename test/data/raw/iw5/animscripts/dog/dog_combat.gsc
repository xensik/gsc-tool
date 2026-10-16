#include common_scripts\utility;
#include animscripts\notetracks;
#include animscripts\utility;
#include maps\_utility;

#using_animtree( "dog" );

main()
{
	self endon( "killanimscript" );

	assert( isdefined( self.enemy ) );
	if ( !isalive( self.enemy ) )
	{
		combatIdle();
		return;
	}

	if ( isplayer( self.enemy ) )
		self meleeBiteAttackPlayer();
	else
		self meleeStruggleVsAI();
}

killplayer()
{
	self endon( "pvd_melee_interrupted" );
		
	if ( !isdefined( self.meleeingPlayer.player_view ) ) 
		return;
	
	player_view = self.meleeingPlayer.player_view;
	
	if ( isdefined( player_view.player_killed ) )
		return;

	player_view.player_killed = true;
	
	if ( killing_will_down( self.meleeingPlayer ) )
	{
		knock_down_player_coop( self.meleeingPlayer, self );
		return;
	}

	self.meleeingPlayer.specialDeath = true;
	self.meleeingPlayer setcandamage( true );

	PlayFXOnTag( level._effect[ "dog_bite_blood" ], player_view, "tag_torso" );

	wait 1;
	if( !isdefined(self) || !isdefined(self.meleeingPlayer) )
		return;
	
	// need to see if it's hyena before any waits that could kill self
	is_hyena = self is_hyena();
		
	self.meleeingPlayer enableHealthShield( false );

	if ( !isalive( self.meleeingPlayer ) )
		return;

	self.meleeingPlayer dog_player_kill( self );
	self.meleeingPlayer shellshock( "default", 5 );
	waittillframeend;// so quote gets set after _quotes sets it
	//setDvar( "ui_deadquote", level.dog_death_quote );
	setDvar( "ui_deadquote", "" );
	thread dog_death_hud( self.meleeingPlayer, is_hyena );
}

knock_down_player_coop( player, dog )
{
	player.dog_downed_player = true;
	
	rate = dog_vs_player_anim_rate();
	self setflaggedanimknobrestart( "meleeanim", %german_shepherd_player_getoff, 1, 0.1, rate );
	
	assert( isdefined( player.player_view ) );
	player.player_view notify( "pvd_melee_interrupted" );
	player.player_view notify( "pvd_melee_done" );
	player.player_view PlayerView_EndSequence( player );
	
	// Make sure that knocking the player down shouldn't 
	// kill the player at this point because of the wait
	// in PlayerView_EndSequence()
	if ( !killing_will_down( player ) )
	{
		player dog_player_kill( dog );
	}
}

dog_player_kill( killer )
{
	if ( laststand_enabled() )
		self enableDeathShield( false );

	self DisableInvulnerability();
	if ( isalive( killer ) )
		self kill( self.origin, killer );
	else
		self kill( self.origin );
}

dog_death_hud( player, is_hyena )
{
	// SO does death hints differently from SP.
	if ( is_specialop() )
		return;
		
	wait( 1.5 );

	thread dog_deathquote( player );
	overlay = newClientHudElem( player );
	overlay.x = 0;
	overlay.y = 50;
	if ( is_hyena )
	{
		overlay setshader( "hud_hyena_melee", 96, 96 );
	}
	else
	{
		overlay setshader( "hud_dog_melee", 96, 96 );
	}
	overlay.alignX = "center";
	overlay.alignY = "middle";
	overlay.horzAlign = "center";
	overlay.vertAlign = "middle";
	overlay.foreground = true;
	overlay.alpha = 0;
	overlay fadeOverTime( 1 );
	overlay.alpha = 1;
}

dog_deathquote( player )
{
	textOverlay = player maps\_hud_util::createClientFontString( "default", 1.75 );
	textOverlay.color = ( 1, 1, 1 );
	textOverlay setText( level.dog_death_quote );
	textOverlay.x = 0;
	textOverlay.y = -30;
	textOverlay.alignX = "center";
	textOverlay.alignY = "middle";
	textOverlay.horzAlign = "center";
	textOverlay.vertAlign = "middle";
	textOverlay.foreground = true;
	textOverlay.alpha = 0;
	textOverlay fadeOverTime( 1 );
	textOverlay.alpha = 1;
}

attackMiss()
{
	self clearanim( %root, 0.1 );
	missAnim = %german_shepherd_attack_player_miss_b;

	if ( isdefined( self.enemy ) )
	{
		forward	 = anglestoforward( ( 0, self.desiredAngle, 0 ) );
		dirToEnemy = vectorNormalize( self.enemy.origin - self.origin );
		landPosToEnemy = self.enemy.origin - ( self.origin + ( forward* 40 ) );
		
		if ( vectordot( dirToEnemy, forward ) > 0.707 || vectordot( landPosToEnemy, forward ) > 0 )
		{
			self thread animscripts\dog\dog_stop::lookAtTarget( "normal" );
		}
		else
		{
			self.skipStartMove = true;
			self thread attackMissTrackTargetThread();

			if ( ( dirToEnemy[ 0 ] * forward[ 1 ] - dirToEnemy[ 1 ] * forward[ 0 ] ) > 0 )
				missAnim = %german_shepherd_attack_player_miss_turnR;
			else
				missAnim = %german_shepherd_attack_player_miss_turnL;
		}
	}

	self setflaggedanimrestart( "miss_anim", missAnim, 1, 0, 1 );
	animLength = getAnimLength( missAnim );
	self DoNoteTracksForTime( animLength - 0.1, "miss_anim" );
	self notify( "stop tracking" );
}


attackMissTrackTargetThread()
{
	self endon( "killanimscript" );

	wait 0.6;
	self OrientMode( "face enemy" );
}


KnockOutOfADS( player )
{
	player endon( "death" );
	player AllowAds( false );
	wait 0.75;
	player AllowAds( true );
}

dogMelee()
{
	/#
	if ( isgodmode( self.meleeingPlayer ) )
	{
		println( "Player in god mode, aborting dog attack" );
		return;
	}
	#/

	if ( isdefined( self.meleeingPlayer ) )
	{
		// Julian: Knock player out of UAV/Predator view, else player is invincible to dog attacks
		if ( isdefined( self.meleeingPlayer.using_uav ) && self.meleeingPlayer.using_uav )
			self.meleeingPlayer notify( "force_out_of_uav" );
		
		if ( self.meleeingPlayer isLinked() )
			return undefined;

		if ( self.meleeingPlayer isMantling() )
			return undefined;
			
		if ( self.meleeingPlayer.lastStand && self.meleeingPlayer.ignoreMe )
			return undefined;
	}

	if ( isdefined( self.enemy ) )
	{
		if ( distance2D( self.origin, self.enemy.origin ) < 32 )
			return self melee();
	}
	
	return self melee( anglesToForward( self.angles ) );
}


handleMeleeBiteAttackNoteTracks( note )
{
	switch( note )
	{
		case "dog_melee":
		{
			hitEnt = self dogMelee();

			if ( isdefined( hitEnt ) )
			{
				if ( isplayer( hitEnt ) )
				{
					if ( GetDvarInt( "survival_chaos" ) != 1  )
					{
						hitEnt shellshock( "dog_bite", 1 );
						thread KnockOutOfADS( hitEnt );
					}
				}
			}
			else
			{
				attackMiss();
				return true;
			}
		}
		break;

		case "stop_tracking":
			self OrientMode( "face current" );
			break;
	}
}

// to prevent the player from dying from the intial dog jump bite attack
addSafetyHealth()
{
	healthFrac = self.meleeingPlayer getnormalhealth();
	if ( healthFrac == 0 )
		return false;

	if ( healthFrac < 0.25 )
	{
		self.meleeingPlayer setnormalhealth( healthFrac + 0.25 );
		return true;
	}
	return false;
}

removeSafetyHealth()
{
	healthFrac = self.meleeingPlayer getnormalhealth();
	if ( healthFrac > 0.25 )
		self.meleeingPlayer setnormalhealth( healthFrac - 0.25 );
	else
		self.meleeingPlayer setnormalhealth( 0.01 );
}

handleMeleeFinishAttackNoteTracks( note )
{
	switch( note )
	{
		case "dog_melee":

			healthAdded = addSafetyHealth();

			hitEnt = self dogMelee();
			if ( isdefined( hitEnt ) && isplayer( hitEnt ) && isalive( self.meleeingPlayer ) )
			{
				if ( healthAdded )
					removeSafetyHealth();

				self.skipStartMove = undefined;

				assert( !isdefined( self.meleeingPlayer.player_view ) );
				self.meleeingPlayer.player_view = PlayerView_Spawn( self );

				if ( self.meleeingPlayer.player_view PlayerView_StartSequence( self ) )
					self setcandamage( false );
			}
			else
			{
				if ( healthAdded )
					removeSafetyHealth();

				attackMiss();
				return true;
			}
			break;

		case "dog_early":
			self notify( "dog_early_notetrack" );

			rate = 0.45 + 0.8 * level.dog_melee_timing_array[ level.dog_melee_index ];
			rate = rate * dog_vs_player_anim_rate();

			//println( "rate " + rate );
			level.dog_melee_index++ ;
			if ( level.dog_melee_index >= level.dog_melee_timing_array.size )
			{
				level.dog_melee_index = 0;
				// randomize the array for variety in dog attack timing
				level.dog_melee_timing_array = maps\_utility::array_randomize( level.dog_melee_timing_array );
			}

			self setflaggedanimlimited( "meleeanim", %german_shepherd_attack_player, 1, 0.2, rate );
			self setflaggedanimlimited( "meleeanim", %german_shepherd_attack_player_late, 1, 0.2, rate );

			self.meleeingPlayer.player_view PlayerView_PlayKnockDownAnimLimited( rate );
			break;

		case "dog_lunge":
			thread set_melee_timer();
			rate = dog_vs_player_anim_rate();
			self setflaggedanim( "meleeanim", %german_shepherd_attack_player, 1, 0.2, rate );

			self.meleeingPlayer.player_view PlayerView_PlayKnockDownAnim( rate );
			break;

		case "dogbite_damage":
			 /#
			if ( isgodmode( self.meleeingPlayer ) )
				break;
			#/

			self thread killplayer();
			break;

		case "stop_tracking":
			self OrientMode( "face current" );
			break;
	}
}

handle_dogbite_notetrack( note )
{
	switch( note )
	{
		case "dogbite_damage":
			 /#
			if ( isgodmode( self.meleeingPlayer ) )
				break;
			#/

			self thread killplayer();
			break;
	}
}

set_melee_timer()
{
	wait( 0.1 ); // used to be 0.15

	// Have the dog_hint show up 50ms before the timer is set 
	// because it takes 50ms for the clienthudelem to start drawing
	self thread dog_hint();

	wait( 0.05 );
	self.melee_able_timer = gettime();

	 /#
	if ( getdebugdvar( "dog_hint" ) == "on" )
	{
		introblack = newHudElem();
		introblack.x = 50;
		introblack.y = 50;
		introblack.horzAlign = "fullscreen";
		introblack.vertAlign = "fullscreen";
		introblack.foreground = true;
		introblack setShader( "black", 100, 100 );
		wait( 0.25 );
		introblack destroy();
	}
	#/
}

playerDogInit()
{
	assert( isPlayer( self ) );
	self.lastDogMeleePlayerTime = 0;
	self.dogMeleePlayerCounter = 0;
}

meleeBiteAttackPlayer()
{
	assert( isPlayer( self.enemy ) );
	self.meleeingPlayer = self.enemy;

	if ( !isdefined( self.meleeingPlayer.dogInited ) )
		self.meleeingPlayer playerDogInit();

	attackRangeBuffer = 30;
	meleeRange = self.meleeAttackDist + attackRangeBuffer;

	for ( ;; )
	{
		if ( !isalive( self.enemy ) )
			break;
		
		// During the wait at the bottom of this loop 
		// the dog could have gotten a new target that
		// is not the player
		if ( !IsPlayer( self.enemy) )
			break;
		
		if ( is_player_down( self.enemy ) )
		{
			combatIdle();
			continue;
		}

		if ( ( isdefined( self.meleeingPlayer.syncedMeleeTarget ) && self.meleeingPlayer.syncedMeleeTarget != self ) ||
			( isdefined( self.meleeingPlayer.player_view ) && isdefined( self.meleeingPlayer.player_view.inSeq ) ) )
		{
			if ( checkEndCombat( meleeRange ) )
			{
				break;
			}
			else
			{
				combatIdle();
				continue;
			}
		}

		if ( self shouldWaitInCombatIdle() )
		{
			combatIdle();
			continue;
		}

		self OrientMode( "face enemy" );
		self animMode( "zonly_physics" );

		self.safeToChangeScript = false;

		prepareAttackPlayer();

		self clearanim( %root, 0.1 );
		self clearpitchorient();

 /#
		if ( getdebugdvar( "debug_dog_sound" ) != "" )
			iprintln( "dog " + ( self getentnum() ) + " attack player " + getTime() );

#/
		//self thread play_sound_on_tag( "anml_dog_growl", "tag_eye" );

		self.meleeingPlayer setNextDogAttackAllowTime( 500 );
		
		if ( dog_cant_kill_in_one_hit() )
		{
			self.meleeingPlayer.lastDogMeleePlayerTime = getTime();
			self.meleeingPlayer.dogMeleePlayerCounter++ ;

			self setflaggedanimrestart( "meleeanim", %german_shepherd_run_attack_b, 1, 0.2, 1 );
			self animscripts\shared::DoNoteTracks( "meleeanim", ::handleMeleeBiteAttackNoteTracks );
		}
		else
		{
			self thread dog_melee_death();
			self.meleeingPlayer.attacked_by_dog = true;
			self.meleeingPlayer.laststand = false;
			self.meleeingPlayer.achieve_downed_kills = undefined;
			self thread clear_player_attacked_by_dog_on_death();
			self setflaggedanimrestart( "meleeanim", %german_shepherd_attack_player, 1, 0.2, 1 );
			self setflaggedanimrestart( "meleeanim", %german_shepherd_attack_player_late, 1, 0, 1 );
			self setanimlimited( %attack_player, 1, 0, 1 );
			self setanimlimited( %attack_player_late, 0.01, 0, 1 );

			self animscripts\shared::DoNoteTracks( "meleeanim", ::handleMeleeFinishAttackNoteTracks );
			self notify( "dog_no_longer_melee_able" );
			self setcandamage( true );
			self unlink();
		}

		self.safeToChangeScript = true;
		wait 0.05;	// give code chance to react

		if ( checkEndCombat( meleeRange ) )
			break;
	}

	self.safeToChangeScript = true;
	self animMode( "none" );
}

clear_player_attacked_by_dog_on_death()
{
	self waittill( "death" );
	self.meleeingPlayer.attacked_by_dog = undefined;
}


dog_cant_kill_in_one_hit()
{
	if ( isdefined( self.meleeingPlayer.dogs_dont_instant_kill ) )
	{
		assertex( self.meleeingPlayer.dogs_dont_instant_kill, "Dont set self.meleeingPlayer.dogs_dont_instant_kill to false, set to undefined" );
		return true;
	}
	
	// In Chaos mode, stop dogs from being able to bring the player down
	if ( GetDvarInt( "survival_chaos" ) == 1 )
		return true;

	if ( is_player_down( self.meleeingPlayer ) )
		return true;

	if ( isdefined( self.meleeingPlayer.slideModel ) )
		return true;

	if ( getTime() - self.meleeingPlayer.lastDogMeleePlayerTime > 8000 )
		self.meleeingPlayer.dogMeleePlayerCounter = 0;

	return self.meleeingPlayer.dogMeleePlayerCounter < self.meleeingPlayer.gs.dog_hits_before_kill &&
		   self.meleeingPlayer.health > 25;	// little more than the damage one melee dog bite hit will do
}


// prevent multiple dogs attacking at the same time and overlapping
shouldWaitInCombatIdle()
{
	assert( isdefined( self.enemy ) && isalive( self.enemy ) );

	return isdefined( self.enemy.dogAttackAllowTime ) && ( gettime() < self.enemy.dogAttackAllowTime );
}

// call on target
setNextDogAttackAllowTime( time )
{
	self.dogAttackAllowTime = gettime() + time;
}


meleeStruggleVsAI()
{
	if ( !isalive( self.enemy ) )
		return;
	
	self.enemy notify( "dog_attacks_ai" );
	
	if ( isdefined( self.enemy.syncedMeleeTarget ) || self shouldWaitInCombatIdle() || !isAI( self.enemy ) )
	{
		combatIdle();
		return;
	}

	self.enemy setNextDogAttackAllowTime( 500 );

	self.safeToChangeScript = false;
	self animMode( "zonly_physics" );
	self.pushable = false;

	self clearpitchorient();

	self.meleeKillTarget = !isdefined( self.enemy.magic_bullet_shield ) &&
						  ( isdefined( self.enemy.a.doingLongDeath ) || isdefined( self.meleeAlwaysWin ) || randomint( 100 ) > 50 );

	meleeSeqAnims = [];
	meleeSeqAnim[ 0 ] = %root;
	meleeSeqAnim[ 1 ] = %german_shepherd_attack_AI_01_start_a;
	meleeSeqAnim[ 2 ] = %german_shepherd_attack_AI_02_idle_a;
	if ( self.meleeKillTarget )
	{
		meleeSeqAnim[ 3 ] = %german_shepherd_attack_AI_03_pushed_a;
		meleeSeqAnim[ 4 ] = %german_shepherd_attack_AI_04_middle_a;
		meleeSeqAnim[ 5 ] = %german_shepherd_attack_AI_05_kill_a;
		numMeleeStage = 5;
	}
	else
	{
		meleeSeqAnim[ 3 ] = %german_shepherd_attack_AI_03_shot_a;
		numMeleeStage = 3;
	}

	angles = vectorToAngles( self.origin - self.enemy.origin );
	angles = (0, angles[1], 0);

	
	self.originalTarget = self.enemy;

	self setcandamage( false );
	self clearanim( meleeSeqAnim[ 0 ], 0.1 );
	self animrelative( "meleeanim", self.enemy.origin, angles, meleeSeqAnim[ 1 ] );
	self animscripts\shared::DoNoteTracks( "meleeanim", ::handleStartAIPart );

	self setcandamage( true );
	self animMode( "zonly_physics" );

	for ( meleeSeq = 1; meleeSeq < numMeleeStage; meleeSeq++ )
	{
		self clearanim( meleeSeqAnim[ meleeSeq ], 0 );

		if ( !inSyncMeleeWithTarget() )
			break;

		// get ready to die
		if ( !self.meleeKillTarget && meleeSeq + 1 == numMeleeStage )
			self.health = 1;

		self setflaggedanimrestart( "meleeanim", meleeSeqAnim[ meleeSeq + 1 ], 1, 0, 1 );
		self animscripts\shared::DoNoteTracks( "meleeanim" );
	}
	
	self unlink();

	if ( !self.meleeKillTarget )
	{
		self kill();
	}
	else
	{
		self.pushable = true;
		self.safeToChangeScript = true;
		self.flashBangImmunity = false;
	}
}

combatIdle()
{
	self OrientMode( "face enemy" );
	self clearanim( %root, 0.1 );
	self animMode( "zonly_physics" );

	idleAnims = [];
	idleAnims[ 0 ] = %german_shepherd_attackidle_b;
	idleAnims[ 1 ] = %german_shepherd_attackidle_bark;
	idleAnims[ 2 ] = %german_shepherd_attackidle_growl;

	idleAnim = random( idleAnims );

	self thread combatIdlePreventOverlappingPlayer();

	self setflaggedanimrestart( "combat_idle", idleAnim, 1, 0.2, 1 );
	self animscripts\shared::DoNoteTracks( "combat_idle" );

	self notify( "combatIdleEnd" );
}


// when player is in melee sequence, other dogs need to move away
combatIdlePreventOverlappingPlayer()
{
	self endon( "killanimscript" );
	self endon( "combatIdleEnd" );

	while ( 1 )
	{
		wait 0.1;

		players = getentarray( "player", "classname" );
		for ( i = 0; i < players.size; i++ )
		{
			player = players[ i ];
			if ( !isdefined( player.syncedMeleeTarget ) || player.syncedMeleeTarget == self )
				continue;

			offsetVec = player.origin - self.origin;

			if ( offsetVec[ 2 ] * offsetVec[ 2 ] > 6400 )
				continue;

			offsetVec = ( offsetVec[ 0 ], offsetVec[ 1 ], 0 );

			offset = length( offsetVec );

			if ( offset < 1 )
				offsetVec = anglestoforward( self.angles );

			if ( offset < 30 )
			{
				offsetVec *=( 3 / offset );
				self safeTeleport( self.origin - offsetVec, ( 0, 30, 0 ) );
			}
		}
	}
}


inSyncMeleeWithTarget()
{
	return( isdefined( self.enemy ) && isdefined( self.enemy.syncedMeleeTarget ) && self.enemy.syncedMeleeTarget == self );
}

handleStartAIPart( note )
{
	if ( note != "ai_attack_start" )
		return false;

	if ( !isdefined( self.enemy ) )
		return true;

	if ( self.enemy != self.originalTarget )
		return true;

	// enemy already has a synced melee target
	if ( isdefined( self.enemy.syncedMeleeTarget ) )
		return true;

	// self.enemy thread draw_tag( "tag_sync" );

	self.flashBangImmunity = true;
	self.enemy.syncedMeleeTarget = self;
	self.enemy animcustom( ::meleeStruggleVsDog );
}

checkEndCombat( meleeRange )
{
	if ( !isdefined( self.enemy ) )
		return false;

	distToTargetSq = distanceSquared( self.origin, self.enemy.origin );

	return( distToTargetSq > meleeRange * meleeRange );
}

prepareAttackPlayer()
{
	if ( self is_hyena() )
	{
		// Press ^3[{+melee}]^7 when the hint appears to grab a hyena.
		level.dog_death_quote 		= &"NEW_HYENA_DEATH_DO_NOTHING_ALT";
		level.so_dog_death_quote 	= "@NEW_HYENA_DEATH_DO_NOTHING_ALT";
	}
	else
	{
		// Press ^3[{+melee}]^7 when the hint appears to grab a dog.
		level.dog_death_quote 		= &"NEW_DOG_DEATH_DO_NOTHING_ALT";
		level.so_dog_death_quote 	= "@NEW_DOG_DEATH_DO_NOTHING_ALT";
	}
	
	level.dog_death_type = "nothing";
	distanceToTarget = distance( self.origin, self.enemy.origin );

	if ( distanceToTarget > self.meleeAttackDist )
	{
		offset = self.enemy.origin - self.origin;

		length = ( distanceToTarget - self.meleeAttackDist ) / distanceToTarget;
		offset = ( offset[ 0 ] * length, offset[ 1 ] * length, offset[ 2 ] * length );

		self thread attackTeleportThread( offset );
	}
}

// make up for error in intial attack jump position
attackTeleportThread( offset )
{
	self endon( "death" );
	self endon( "killanimscript" );
	reps = 5;
	increment = ( offset[ 0 ] / reps, offset[ 1 ] / reps, offset[ 2 ] / reps );
	for ( i = 0; i < reps; i++ )
	{
		self teleport( self.origin + increment );
		wait( 0.05 );
	}
}

player_attacked()
{
	return isalive( self.meleeingPlayer ) && ( self.meleeingPlayer MeleeButtonPressed() );
}



dog_hint()
{
	press_time = self.meleeingPlayer.gs.dog_presstime / 1000 / dog_vs_player_anim_rate();
	level endon( "clearing_dog_hint" );
	if ( isDefined( self.meleeingPlayer.dogHintElem ) )
		self.meleeingPlayer.dogHintElem maps\_hud_util::destroyElem();

	self.meleeingPlayer.dogHintElem = self.meleeingPlayer maps\_hud_util::createClientFontString( "default", 3 );
	self.meleeingPlayer.dogHintElem.color = ( 1, 1, 1 );
	// [{+melee}]
	self.meleeingPlayer.dogHintElem setText( &"SCRIPT_PLATFORM_DOG_HINT" );
	self.meleeingPlayer.dogHintElem.x = 0;
	self.meleeingPlayer.dogHintElem.y = 20;
	self.meleeingPlayer.dogHintElem.alignX = "center";
	self.meleeingPlayer.dogHintElem.alignY = "middle";
	self.meleeingPlayer.dogHintElem.horzAlign = "center";
	self.meleeingPlayer.dogHintElem.vertAlign = "middle";
	self.meleeingPlayer.dogHintElem.foreground = true;
	self.meleeingPlayer.dogHintElem.alpha = 1;
	self.meleeingPlayer.dogHintElem.hidewhendead = true;
	self.meleeingPlayer.dogHintElem.sort = -1;
	self.meleeingPlayer.dogHintElem endon( "death" );

	wait( press_time );
	thread dog_hint_fade();
}

dog_hint_fade()
{
	level notify( "clearing_dog_hint" );
	if ( IsDefined( self ) && isDefined( self.meleeingPlayer.dogHintElem ) )
	{
		hud = self.meleeingPlayer.dogHintElem;
		if ( IsDefined( self.meleeingPlayer.player_view.neckSnapped ) && self.meleeingPlayer.player_view.neckSnapped )
		{
			time = 0.5;
			hud ChangeFontScaleOvertime( time );
			hud.fontScale = hud.fontScale * 1.5;
			hud.glowColor = ( 0.3, 0.6, 0.3 );
			hud.glowAlpha = 1;
			hud FadeOverTime( time );
			hud.color = ( 0, 0, 0 );
			hud.alpha = 0;
			wait( time );
			hud maps\_hud_util::destroyElem();
		}
		else
		{
			hud maps\_hud_util::destroyElem();
		}
	}
}

dog_delayed_unlink()
{
	wait 0.7;
	if ( isdefined( self ) )
		self unlink();
}

// for safety
dog_delayed_allow_damage()
{
	self endon( "death" );
	
	wait 1.5;
	if ( isdefined( self ) )
		self setCanDamage( true );
}

dog_melee_death()
{
	self endon( "killanimscript" );
	self endon( "dog_no_longer_melee_able" );
	pressed = false;

	// change this number for difficulty level:
	press_time = self.meleeingPlayer.gs.dog_presstime / dog_vs_player_anim_rate();

	self waittill( "dog_early_notetrack" );

	while ( player_attacked() )
	{
		// wait until the player lets go of the button, if he's holding it
		wait( 0.05 );
	}

	pressed_too_soon = false;
	for ( ;; )
	{
		if ( !pressed )
		{
			if ( self player_attacked() )
			{
				pressed = true;
				if ( isdefined( self.melee_able_timer ) && isalive( self.meleeingPlayer ) )
				{
					if ( gettime() - self.melee_able_timer <= press_time )
					{
						self.meleeingPlayer set_melee_early( pressed_too_soon );

						self.meleeingPlayer.player_view.neckSnapped = true;
						self notify( "melee_stop" );
						self setflaggedanimknobrestart( "dog_death_anim", %german_shepherd_player_neck_snap, 1, 0.2, 1 );
						self thread dog_delayed_allow_damage();
						self setcandamage( false );
						
						//maps\_utility::giveachievement_wrapper( "DOWN_BOY_DOWN" );
						self waittillmatch( "dog_death_anim", "dog_death" );
						self thread play_sound_in_space( "dog_neckbreak", self getEye() );
						self setcandamage( true );
						self.a.nodeath = true;
						self.dog_neck_snapped = true;
						dif = self.meleeingPlayer.origin - self.origin;
						dif = ( dif[ 0 ], dif [ 1 ], 0 );
						arcadeMode_kill( self.origin, "melee", 50 );
						self thread dog_delayed_unlink();
						self kill( self geteye() - dif, self.meleeingPlayer );
						self notify( "killanimscript" );
					}
					else
					{
						self.meleeingPlayer set_melee_early( pressed_too_soon );

						self.meleeingPlayer.player_view PlayerView_KnockDownLate();

						self setanimlimited( %attack_player, 0.01, 0.2, 1 );
						self setanimlimited( %attack_player_late, 1, 0.2, 1 );
						
						if ( self is_hyena() )
						{
							// Too late. Press ^3[{+melee}]^7 when the hint appears to grab a hyena.
							level.dog_death_quote		= &"NEW_HYENA_DEATH_TOO_LATE_ALT";
							level.so_dog_death_quote 	= "@NEW_HYENA_DEATH_TOO_LATE_ALT";
						}
						else
						{
							// Too late. Press ^3[{+melee}]^7 when the hint appears to grab a dog.
							level.dog_death_quote 		= &"NEW_DOG_DEATH_TOO_LATE_ALT";
							level.so_dog_death_quote 	= "@NEW_DOG_DEATH_TOO_LATE_ALT";
						}
						level.dog_death_type = "late";
					}

					return;
				}

				pressed_too_soon = true;
				if ( self.meleeingPlayer can_early_melee() )
				{
					if ( self is_hyena() )
					{
						// Too early. Press ^3[{+melee}]^7 when the hint appears to grab a hyena.
						level.dog_death_quote 		= &"NEW_HYENA_DEATH_TOO_SOON_ALT";
						level.so_dog_death_quote 	= "@NEW_HYENA_DEATH_TOO_SOON_ALT";
					}
					else
					{
						// Too early. Press ^3[{+melee}]^7 when the hint appears to grab a dog.
						level.dog_death_quote 		= &"NEW_DOG_DEATH_TOO_SOON_ALT";
						level.so_dog_death_quote 	= "@NEW_DOG_DEATH_TOO_SOON_ALT";
					}
					level.dog_death_type = "soon";
	
					rate = dog_vs_player_anim_rate();
					self setflaggedanimknobrestart( "meleeanim", %german_shepherd_player_neck_miss, 1, 0.2, rate );
					
					self.meleeingPlayer.player_view PlayerView_PlayMissAnim( rate );
	
					// once player clicks, if it is at the wrong time, he does not get another chance.
					return;
				}
			}
		}
		else
		{
			if ( !self player_attacked() )
			{
				pressed = false;
			}
		}

		wait( 0.05 );
	}
}

can_early_melee()
{
	if ( self.gameskill == 3 )
	{
		return true;
	}

	if ( IsDefined( self.dogMeleeEarly ) && self.dogMeleeEarly )
	{
		return true;
	}

	return false;
}

set_melee_early( pressed_too_soon )
{
	if ( !pressed_too_soon )
	{
		return;
	}

	// Hardened will return false the first time, but after that
	// the player can melee too early and be penalized
	if ( level.gameskill > 1 && !IsDefined( self.dogMeleeEarly ) )
	{
		self.dogMeleeEarly = true;
	}
}

// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
// 
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
#using_animtree( "generic_human" );

meleeStruggleVsDog()
{
	self endon( "killanimscript" );
	self endon( "death" );
	self endon( "end_melee_struggle" );
	self endon( "end_melee_all" );

	if ( !isdefined( self.syncedMeleeTarget ) )
		return;

	// self.syncedMeleeTarget = self;

	self OrientMode( "face point", self.syncedMeleeTarget.origin, 1 );
	self animMode( "gravity" );

	self.a.pose = "stand";
	self.a.special = "none";

	if ( usingSidearm() )
		self animscripts\shared::placeWeaponOn( self.primaryweapon, "right" );

	meleeSeqAnim = [];
	meleeSeqAnim[ 0 ] = %root;
	meleeSeqAnim[ 1 ] = %AI_attacked_german_shepherd_01_start_a;
	meleeSeqAnim[ 2 ] = %AI_attacked_german_shepherd_02_idle_a;
	if ( self.syncedMeleeTarget.meleeKillTarget )
	{
		meleeSeqAnim[ 3 ] = %AI_attacked_german_shepherd_03_push_a;
		meleeSeqAnim[ 4 ] = %AI_attacked_german_shepherd_04_middle_a;
		meleeSeqAnim[ 5 ] = %AI_attacked_german_shepherd_05_death_a;
		numMeleeStage = 5;
	}
	else
	{
		meleeSeqAnim[ 3 ] = %AI_attacked_german_shepherd_03_shoot_a;
		numMeleeStage = 3;
	}

	self.meleeSeq = 0;

	self thread meleeStruggleVsDog_interruptedCheck();

	self clearanim( meleeSeqAnim[ 0 ], 0.1 );

	self setflaggedanimrestart( "aianim", meleeSeqAnim[ 1 ], 1, 0.1, 1 );

	// this needs to happen here and not when the dog starts, because "tag_sync" won't be correct at that point
	wait 0.15;// also wait a bit before tag_sync in AI animation to settle to right spot
	self.syncedMeleeTarget linkto( self, "tag_sync", ( 0, 0, 0 ), ( 0, 0, 0 ) );

	self waittillmatch( "aianim", "end" );

	for ( self.meleeSeq = 1; self.meleeSeq < numMeleeStage; )
	{
		self clearanim( meleeSeqAnim[ self.meleeSeq ], 0 );

		self.meleeSeq++ ;

		// if starting the pistol pull out to shoot, don't let any other dog attack me for a bit
		if ( numMeleeStage == 3 && self.meleeSeq == 3 )
			self setNextDogAttackAllowTime( getAnimLength( meleeSeqAnim[ self.meleeSeq ] ) * 1000 - 1000 );

		self setflaggedanimrestart( "aianim", meleeSeqAnim[ self.meleeSeq ], 1, 0, 1 );
		self animscripts\shared::DoNoteTracks( "aianim" );

		// hack to let %AI_attacked_german_shepherd_03_push_a play to end when interrupted
		if ( !isdefined( self.syncedMeleeTarget ) || !isAlive( self.syncedMeleeTarget ) )
		{
			if ( self.meleeSeq == 3 && numMeleeStage == 5 )
			{
				meleeSeqAnim[ 4 ] = %AI_attacked_german_shepherd_04_getup_a;
				numMeleeStage = 4;
			}
		}

		if ( self.meleeSeq == 5 )
		{
			if ( !isdefined( self.magic_bullet_shield ) )
			{
				self.a.nodeath = true;
				self animscripts\shared::DropAllAIWeapons();
				self kill();
			}
		}
	}

	meleeStruggleVsDog_End();
}


// check for premature termination from dog being shot by another AI or player
meleeStruggleVsDog_interruptedCheck()
{
	self endon( "killanimscript" );
	self endon( "death" );
	self endon( "end_melee_all" );

	meleeSeqAnim = [];
	meleeSeqAnim[ 1 ] = %AI_attacked_german_shepherd_02_getup_a;
	meleeSeqAnim[ 2 ] = %AI_attacked_german_shepherd_02_getup_a;

	if ( self.syncedMeleeTarget.meleeKillTarget )
	{
		// meleeSeqAnim[ 3 ] = %AI_attacked_german_shepherd_04_getup_a;	// handle this in meleeStruggleVsDog()
		meleeSeqAnim[ 4 ] = %AI_attacked_german_shepherd_04_getup_a;
	}

	while ( 1 )
	{
		if ( !isdefined( self.syncedMeleeTarget ) || !isAlive( self.syncedMeleeTarget ) )
			break;

		wait 0.1;
	}

	if ( self.meleeSeq > 0 )
	{
		if ( !isdefined( meleeSeqAnim[ self.meleeSeq ] ) )
			return;	// don't call meleeStruggleVsDog_End()

		self clearanim( %melee_dog, 0.1 );
		self setflaggedanimrestart( "getupanim", meleeSeqAnim[ self.meleeSeq ], 1, 0.1, 1 );
		self animscripts\shared::DoNoteTracks( "getupanim" );
	}

	meleeStruggleVsDog_End();
}


// this should kill both meleeStruggleVsDog() and meleeStruggleVsDog_endCheck() threads
meleeStruggleVsDog_End()
{
	self orientmode( "face default" );
	self.syncedMeleeTarget = undefined;
	self.meleeSeq = undefined;
	self.allowPain = true;
	self setNextDogAttackAllowTime( 1000 );

	self notify( "end_melee_all" );
}


//////////////////////////////////////////////////////////
#using_animtree( "player_3rd_person" );

playerDrone_create( player )
{
	playerDrone = spawn( "script_model", player.origin );
	
	assert( isdefined( player.last_modelfunc ) );
	playerDrone [[ player.last_modelfunc ]]();
	playerDrone useAnimTree( #animtree );
	return playerDrone;
}

playerDrone_anim_knockdown( rate )
{
	self endon( "death" );
	
	time = getAnimLength( %player_3rd_dog_knockdown );
	
	self setanim( %player_3rd_dog_knockdown, 1, 0, rate );
}

playerDone_anim_neck_snap()
{
	self setanimknobrestart( %player_3rd_dog_knockdown_neck_snap, 1, 0, 1 );
}


playerDone_anim_saved()
{
	self setanimknobrestart( %player_3rd_dog_knockdown_saved, 1, 0, 1 );
}

playerDone_anim_laststand()
{
	self setanimknobrestart( %player_3rd_dog_knockdown_laststand, 1, 0, 1 );
}


// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
// 
// -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
#using_animtree( "player" );

PlayerView_Spawn( dog )
{
	playerView = spawn( "script_model", dog.meleeingPlayer.origin );
	playerView.angles = dog.meleeingPlayer.angles;
	playerView setModel( level.player_viewhand_model );	// Add to level initialization maps\_load::set_player_viewhand_model;
	playerView useAnimTree( #animtree );
	playerView hide();

	return playerView;
}


handlePlayerKnockDownNotetracks( note )
{
	switch( note )
	{
		case "allow_player_save":
		{
			if ( isdefined( self.dog ) )
			{
				wait 1;
				self.dog setcandamage( true );
			}
		}
		break;

		case "blood_pool":
		{
			if ( !isdefined( self.dog.meleeingPlayer ) )
				break;
			
			if ( killing_will_down( self.dog.meleeingPlayer ) )
				break;
				
			tagPos = self gettagorigin( "tag_torso" );	// rough tag to play fx on
			tagAngles = self gettagangles( "tag_torso" );
			forward = anglestoforward( tagAngles );
			up = anglestoup( tagAngles );
			right = anglestoright( tagAngles );

			tagPos = tagPos + ( forward * -8.5 ) + ( up * 5 ) + ( right * 0 );
			playfx( level._effect[ "deathfx_bloodpool" ], tagPos, forward, up );	// Add to level initialization animscripts\dog\dog_init::initDogAnimations();
		}
		break;
	}
}


PlayerView_KnockDownAnim( dog )
{
	self endon( "pvd_melee_interrupted" );

	player = dog.meleeingPlayer;
	self.dog = dog;
	self thread PlayerView_CheckInterrupted( player );

	self setflaggedanimrestart( "viewanim", %player_view_dog_knockdown );
	self setflaggedanimrestart( "viewanim", %player_view_dog_knockdown_late );

	self setanimlimited( %knockdown, 1, 0, 1 );
	self setanimlimited( %knockdown_late, 0.01, 0, 1 );

	self animscripts\shared::DoNoteTracks( "viewanim", ::handlePlayerKnockDownNotetracks );

	self dontInterpolate();

	self.dog = undefined;
	PlayerView_EndSequence( player );
	self notify( "pvd_melee_done" );
}


PlayerView_CheckInterrupted( player )
{
	self endon( "pvd_melee_done" );

	self.dog waittill_any( "death", "pain", "melee_stop" );

	if ( !isdefined( player.specialDeath ) && isAlive( player ) )
	{
		self notify( "pvd_melee_interrupted" );
		self.dog notify( "pvd_melee_interrupted" );
		PlayerView_EndSequence( player );
	}
}


PlayerView_StartSequence( dog )
{
	if ( isdefined( self.inSeq ) )
		return false;

	player = dog.meleeingPlayer;
	
	if ( isdefined( player ) && isdefined( player.placingSentry ) )
		player notify( "sentry_placement_canceled" );
		
	player notify( "dog_attacks_player" );
	self.inSeq = true;

	if ( isalive( player ) )
		player hideHud();

	player setstance( "stand" );
	player.syncedMeleeTarget = dog;
	player.player_view PlayerView_Show( player );
	
	assert( !isdefined( player.dog_downed_player ), "The dog_downed_player flag should never be defined in the start sequence of the attack." );

	direction = dog.origin - player.origin;
	self.angles = vectortoangles( direction );
	self.angles = ( 0, self.angles[ 1 ], 0 );
	self.startAngles = self.angles;

	playerpos = player.origin;

	newOrigin = player getDropToFloorPosition( player.origin );
	if ( isdefined( newOrigin ) )
		self.origin = newOrigin;
	else
		self.origin = player.origin;

	self thread PlayerView_KnockDownAnim( dog );
	self dontInterpolate();

	player playerLinkToAbsolute( self, "tag_player" );
	dog linkto( self, "tag_sync", ( 0, 0, 0 ), ( 0, 0, 0 ) );

	syncTagAngles = self gettagangles( "tag_sync" );
	dog orientmode( "face angle", syncTagAngles[ 1 ] );
	dog orientmode( "face default" );

	//self thread draw_tag( "tag_player" );
	//self thread draw_tag( "tag_camera" );
	//self thread draw_tag( "tag_origin" );

	player allowstand ( true );
	player allowLean( false );
	player allowCrouch( false );
	player allowProne( false );
	player freezeControls( true );

	player setcandamage( false );

	return true;
}

SavedNotify( player )
{
	wait 0.5;
	player playsound( "saved_from_dog" );
}

player_gets_weapons_back()
{
	self endon( "death" );
	self showViewModel();
	self enableweapons();
}

PlayerView_EndSequence( player )
{
	player showHud();

	if ( isalive( player ) )
	{
		self clearanim( %player_view_dog_knockdown, 0.1 );
		if ( isdefined( self.neckSnapped ) )
		{
			self setflaggedanimrestart( "viewanim", %player_view_dog_knockdown_neck_snap, 1, 0.2, 1 );
			
			if ( isdefined( self.playerDrone ) )
				self.playerDrone playerDone_anim_neck_snap();
		}
		else if ( isdefined( player.dog_downed_player ) )
		{
			self setflaggedanimknobrestart( "viewanim", %player_view_dog_knockdown_laststand, 1, 0.1, 1 );
	
			if ( isdefined( self.playerDrone ) )
				self.playerDrone playerDone_anim_laststand();
		}
		else
		{
			thread SavedNotify( player );
			self setflaggedanimrestart( "viewanim", %player_view_dog_knockdown_saved );
			
			if ( isdefined( self.playerDrone ) )
				self.playerDrone playerDone_anim_saved();
		}

		if ( !isdefined( player.dog_downed_player ) )
		{
			player delaythread( 2.5, ::player_gets_weapons_back );
			self animscripts\shared::DoNoteTracks( "viewanim" );
			player notify( "player_saved_from_dog" );
		}
		else
		{
			self animscripts\shared::DoNoteTracks( "viewanim" );
			player notify( "deathshield", 1000000, self.dog );
			player showViewModel();
		}

		PlayerView_UnlinkPlayerAndDelete( player );
	}
	else
	{
		setsaveddvar( "compass", 0 );
	}

	player.syncedMeleeTarget = undefined;
	player.dog_downed_player = undefined;

	RestorePlayerControls( player );
}


PlayerView_UnlinkPlayerAndDelete( player )
{
	player show();
	player unlink();
	player setOrigin( self.origin );
	player setplayerangles( self.startAngles );
	player setcandamage( true );

	player_view = player.player_view;
	if ( isdefined( player_view ) )
	{
		if ( isdefined( player_view.playerDrone ) )
			player_view.playerDrone delete();
	
		player_view delete();
		player.player_view = undefined;
	}
}

RestorePlayerControls( player )
{
	player allowLean( true );
	player allowCrouch( true );
	player allowProne( true );
	player freezeControls( false );
	player.attacked_by_dog = undefined;
}


PlayerView_Show( player )
{
	self showOnClient( player );
	
	if ( is_coop() )
	{
		playerDrone = playerDrone_create( player );
		playerDrone linkto( self, "tag_origin", ( 0, 0, 0 ), ( 0, 0, 0 ) );
		playerDrone thread playerDrone_anim_knockdown( 1 );

		self.playerDrone = playerDrone;

		if ( level.player == player && isdefined( level.player2 )  )
		{
			player hideOnClient( level.player2 );
			playerDrone hideOnClient( level.player );
		}
		else
		{
			player hideOnClient( level.player );
			playerDrone hideOnClient( level.player2 );
		}
	}
		
	player hideViewModel();
	player disableweapons();
}


PlayerView_PlayKnockDownAnimLimited( rate )
{
	self setflaggedanimlimited( "viewanim", %player_view_dog_knockdown, 1, 0.2, rate );
	self setflaggedanimlimited( "viewanim", %player_view_dog_knockdown_late, 1, 0.2, rate );
	
	if ( isdefined( self.playerDrone ) )
		self.playerDrone playerDrone_anim_knockdown( rate );
}


PlayerView_PlayKnockDownAnim( rate )
{
	self setflaggedanimlimited( "viewanim", %player_view_dog_knockdown, 1, 0.2, rate );
	self setflaggedanimlimited( "viewanim", %player_view_dog_knockdown_late, 1, 0.2, rate );

	if ( isdefined( self.playerDrone ) )
		self.playerDrone playerDrone_anim_knockdown( rate );
}


PlayerView_PlayMissAnim( rate )
{
	self setflaggedanimknobrestart( "viewanim", %player_view_dog_knockdown_neck_miss, 1, 0.2, rate );
}


PlayerView_KnockDownLate()
{
	self setanimlimited( %knockdown, 0.01, 0.2, 1 );
	self setanimlimited( %knockdown_late, 1, 0.2, 1 );
}

/*draw_tag( tagname )
{
	self endon( "death" );
	
	range = 25;
	
	while ( 1 )
	{
		angles = self gettagangles( tagname );	
		origin = self gettagorigin( tagname );
		
		forward = anglestoforward( angles );
		forward = vector_multiply( forward, range );
		right = anglestoright( angles );
		right = vector_multiply( right, range );
		up = anglestoup( angles );
		up = vector_multiply( up, range );
		line( origin, origin + forward, ( 1, 0, 0 ), 1 );
		line( origin, origin + up, ( 0, 1, 0 ), 1 );
		line( origin, origin + right, ( 0, 0, 1 ), 1 );
		wait 0.05;
	}
}*/


dog_vs_player_anim_rate()
{
	//if ( is_coop() )
	//	return 0.25;
	return 1;
}

is_hyena()
{
	if ( IsSubStr( self.classname, "hyena" ) )
	{
		return true;
	}
	
	return false;
}
