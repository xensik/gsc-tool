// Shared.gsc - Functions that are shared between animscripts and level scripts.
// Functions in this file can't rely on the animscripts\init function having run, and can't call any
// functions not allowed in level scripts.

#include maps\_utility;
#include animscripts\notetracks;
#include animscripts\utility;
#include animscripts\combat_utility;
#include common_scripts\utility;

#using_animtree( "generic_human" );

placeWeaponOn( weapon, position, activeWeapon )
{
	//prof_begin( "placeWeaponOn" );
	// make sure this it one of our weapons
	assert( AIHasWeapon( weapon ) );

	self notify( "weapon_position_change" );

	curPosition = self.weaponInfo[ weapon ].position;

	// make sure we're not out of sync
	assert( curPosition == "none" || self.a.weaponPos[ curPosition ] == weapon );

	// weapon already in place
	if ( position != "none" && self.a.weaponPos[ position ] == weapon )
	{
		//prof_end( "placeWeaponOn" );
		return;
	}

	self detachAllWeaponModels();

	// detach if we're already in a position
	if ( curPosition != "none" )
		self detachWeapon( weapon );

	// nothing more to do
	if ( position == "none" )
	{
		self updateAttachedWeaponModels();
		//prof_end( "placeWeaponOn" );
		return;
	}

	if ( self.a.weaponPos[ position ] != "none" )
		self detachWeapon( self.a.weaponPos[ position ] );

	// to ensure that the correct tags for the active weapon are used, we need to make sure it gets attached first
	if ( !isdefined( activeWeapon ) )
		activeWeapon = true;

	if ( activeWeapon && ( position == "left" || position == "right" ) )
	{
		self attachWeapon( weapon, position );
		self.weapon = weapon;
	}
	else
	{
		self attachWeapon( weapon, position );
	}

	self updateAttachedWeaponModels();

	// make sure we don't have a weapon in each hand
	//assert( self.a.weaponPos[ "left" ] == "none" || self.a.weaponPos[ "right" ] == "none" );
	//prof_end( "placeWeaponOn" );
}

detachWeapon( weapon )
{
	self.a.weaponPos[ self.weaponInfo[ weapon ].position ] = "none";
	self.weaponInfo[ weapon ].position = "none";
}


attachWeapon( weapon, position )
{
	self.weaponInfo[ weapon ].position = position;
	self.a.weaponPos[ position ] = weapon;

	if ( self.a.weaponPosDropping[ position ] != "none" )
	{
		// a new weapon has taken the place of the weapon we were dropping, so just stop showing the model for the dropping weapon.
		self notify( "end_weapon_drop_" + position );
		self.a.weaponPosDropping[ position ] = "none";
	}
}

getWeaponForPos( position ) // returns the weapon that should currently be visible in a given location.
{
	weapon = self.a.weaponPos[ position ];

	if ( weapon == "none" )
		return self.a.weaponPosDropping[ position ];

	assert( self.a.weaponPosDropping[ position ] == "none" );

	return weapon;
}

detachAllWeaponModels()
{
	positions = [];
	positions[ positions.size ] = "right";
	positions[ positions.size ] = "left";
	positions[ positions.size ] = "chest";
	positions[ positions.size ] = "back";

	self laserOff();

	foreach ( position in positions )
	{
		weapon = self getWeaponForPos( position );

		if ( weapon == "none" )
			continue;

		if ( weapontype( weapon ) == "riotshield" && isDefined( self.shieldModelVariant ) )
		{
			// broken glass fx when riotshield breaks
    		if ( isdefined( self.shieldBroken ) && self.shieldBroken )
    		{
    			playfxontag( getfx( "riot_shield_dmg" ), self, "TAG_BRASS" );
    			self.shieldBroken = undefined;
    		}
    		
    		self detach( getWeaponModel( weapon, self.shieldModelVariant ), getTagForPos( position ) );
    	}
		else
	    	self detach( getWeaponModel( weapon ), getTagForPos( position ) );
	}
}

NO_COLLISION = true;

updateAttachedWeaponModels()
{
	positions = [];
	positions[ positions.size ] = "right";
	positions[ positions.size ] = "left";
	positions[ positions.size ] = "chest";
	positions[ positions.size ] = "back";

	foreach ( position in positions )
	{
		weapon = self getWeaponForPos( position );

		if ( weapon == "none" )
			continue;

        variant = 0;
		if ( weapontype( weapon ) == "riotshield" && isDefined( self.shieldModelVariant ) )
		    variant = self.shieldModelVariant;

		weapon_model = getWeaponModel( weapon, variant );
		assertEx( weapon_model != "", "No weapon model for '" + weapon + "', make sure it is precached" );

		if ( weapontype( weapon ) == "riotshield" )
			self attach( weapon_model, getTagForPos( position ) );
		else
			self attach( weapon_model, getTagForPos( position ), NO_COLLISION );

		hideTagList = GetWeaponHideTags( weapon );
		for ( i = 0; i < hideTagList.size; i++ )
		{
			self HidePart( hideTagList[ i ], weapon_model );
		}

		if ( self.weaponInfo[ weapon ].useClip && !self.weaponInfo[ weapon ].hasClip )
			self hidepart( "tag_clip" );
	}

	self updateLaserStatus();
}

updateLaserStatus()
{
	if ( isdefined( self.custom_laser_function ) )
	{
		[[ self.custom_laser_function ]]();
		return;
	}

	// we have no weapon so there's no laser to turn off or on
	if ( self.a.weaponPos[ "right" ] == "none" )
		return;

	if ( canUseLaser() )
		self laserOn();
	else
		self laserOff();
}

canUseLaser()
{
	if ( !self.a.laserOn )
		return false;

	// shotguns don't have lasers
	if ( isShotgun( self.weapon ) )
		return false;

	return isAlive( self );
}

getTagForPos( position )
{
	switch( position )
	{
		case "chest":
			return "tag_weapon_chest";
		case "back":
			return "tag_stowed_back";
		case "left":
			return "tag_weapon_left";
		case "right":
			return "tag_weapon_right";
		case "hand":
			return "tag_inhand";
		default:
			assertMsg( "unknown weapon placement position: " + position );
		break;
	}
}

DropAIWeapon( weapon )
{
	if ( !isDefined( weapon ) )
		weapon = self.weapon;

	if ( weapon == "none" )
		return;

/*
=============
///ScriptFieldDocBegin
"Name: .noDrop"
"Summary: Makes an AI not drop grenades or their weapon"
"Module: ai"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

	if ( isdefined( self.noDrop ) )
		return;

	self detachAllWeaponModels();

	position = self.weaponInfo[ weapon ].position;

	if ( self.dropWeapon && position != "none" )
		self thread DropWeaponWrapper( weapon, position );

	self detachWeapon( weapon );
	if ( weapon == self.weapon )
		self.weapon = "none";

	self updateAttachedWeaponModels();
}

DropAllAIWeapons()
{
	if ( isdefined( self.noDrop ) )
		return "none";

	positions = [];
	positions[ positions.size ] = "left";
	positions[ positions.size ] = "right";
	positions[ positions.size ] = "chest";
	positions[ positions.size ] = "back";

	self detachAllWeaponModels();

	foreach ( position in positions )
	{
		weapon = self.a.weaponPos[ position ];

		if ( weapon == "none" )
			continue;

		self.weaponInfo[ weapon ].position = "none";
		self.a.weaponPos[ position ] = "none";

		if ( self.dropWeapon )
			self thread DropWeaponWrapper( weapon, position );
	}

	self.weapon = "none";

	self updateAttachedWeaponModels();
}


DropWeaponWrapper( weapon, position )
{
	// this must be between calls to detachAllWeaponModels and updateAttachedWeaponModels!

	if ( self IsRagdoll() )
		return "none"; // too late. our weapon is no longer where it looks like it is.

	assert( self.a.weaponPosDropping[ position ] == "none" );
	self.a.weaponPosDropping[ position ] = weapon;

	actualDroppedWeapon = weapon;
	if ( issubstr( tolower( actualDroppedWeapon ), "rpg" ) )
		actualDroppedWeapon = "rpg_player";

	// unless we're already in the process of dropping more than one weapon,
	// this will not actually create the weapon until the next frame, so it can get the tag's velocity.
	self DropWeapon( actualDroppedWeapon, position, 0 );

	// So we want to wait a bit before detaching the model.

	// No waiting before this point!
	self endon( "end_weapon_drop_" + position );
	wait .1;

	if ( !isDefined( self ) )
		return;

	self detachAllWeaponModels();
	self.a.weaponPosDropping[ position ] = "none";
	self updateAttachedWeaponModels();
}


// DoNoteTracks waits for and responds to standard noteTracks on the animation, returning when it gets an "end" or a "finish"
// For level scripts, a pointer to a custom function should be passed as the second argument, which handles notetracks not
// already handled by the generic function. This call should take the form DoNoteTracks(flagName, ::customFunction);
// The custom function will be called for each notetrack not recognized, and will pass the notetrack name. Note that this
// function could be called multiple times for a single animation.
DoNoteTracks( flagName, customFunction, debugIdentifier )// debugIdentifier isn't even used. we should get rid of it.
{
	for ( ;; )
	{
		self waittill( flagName, note );

		if ( !isDefined( note ) )
			note = "undefined";

		//prof_begin("HandleNoteTrack");
		val = self HandleNoteTrack( note, flagName, customFunction );
		//prof_end("HandleNoteTrack");

		if ( isDefined( val ) )
			return val;
	}
}


getPredictedAimYawToShootEntOrPos( time )
{
	if ( !isdefined( self.shootEnt ) )
	{
		if ( !isdefined( self.shootPos ) )
			return 0;

		return getAimYawToPoint( self.shootPos );
	}

	predictedPos = self.shootEnt.origin + ( self.shootEntVelocity * time );
	return getAimYawToPoint( predictedPos );
}

getAimYawToShootEntOrPos()
{
	// make use of the fact that shootPos = shootEnt getShootAtPos() if shootEnt is defined
	if ( !isdefined( self.shootEnt ) )
	{
		if ( !isdefined( self.shootPos ) )
			return 0;

		return getAimYawToPoint( self.shootPos );
	}

	return getAimYawToPoint( self.shootEnt getShootAtPos() );
}

getAimPitchToShootEntOrPos()
{
	pitch = getPitchToShootEntOrPos();
	if ( self.script == "cover_crouch" && isdefined( self.a.coverMode ) && self.a.coverMode == "lean" )
		pitch -= anim.coverCrouchLeanPitch;
	return pitch;
}

getPitchToShootEntOrPos()
{
	if ( !isdefined( self.shootEnt ) )
	{
		// make use of the fact that shootPos = shootEnt getShootAtPos() if shootEnt is defined
		if ( !isdefined( self.shootPos ) )
			return 0;

		return animscripts\combat_utility::getPitchToSpot( self.shootPos );
	}

	return animscripts\combat_utility::getPitchToSpot( self.shootEnt getShootAtPos() );
}

getShootFromPos()
{
	if ( isdefined( self.useMuzzleSideOffset ) )
	{
		muzzlePos = self getMuzzleSideOffsetPos();
		return ( muzzlePos[ 0 ], muzzlePos[ 1 ], self getEye()[ 2 ] );
	}

	return ( self.origin[ 0 ], self.origin[ 1 ], self getEye()[ 2 ] );
}

getAimYawToPoint( point )
{
	yaw = GetYawToSpot( point );

	// need to have fudge factor because the gun's origin is different than our origin,
	// the closer our distance, the more we need to fudge.
	dist = distance( self.origin, point );
	if ( dist > 3 )
	{
		angleFudge = asin( -3 / dist );
		yaw += angleFudge;
	}
	yaw = AngleClamp180( yaw );
	return yaw;
}


ramboAim( baseYaw )
{
	self endon( "killanimscript" );

	ramboAimInternal( baseYaw );

	self clearAnim( %generic_aim_left, 0.5 );
	self clearAnim( %generic_aim_right, 0.5 );
}

ramboAimInternal( baseYaw )
{
	self endon( "rambo_aim_end" );

	waittillframeend; // in case a previous ramboAim call is still doing its clearanims

	self clearAnim( %generic_aim_left, 0.2 );
	self clearAnim( %generic_aim_right, 0.2 );

	self setAnimLimited( %generic_aim_45l, 1, 0.2 );
	self setAnimLimited( %generic_aim_45r, 1, 0.2 );

	interval = 0.2;

	yaw = 0;
	for ( ;; )
	{
		if ( isDefined( self.shootPos ) )
		{
			newyaw = GetYaw( self.shootPos ) - self.coverNode.angles[1];
			newyaw = AngleClamp180( newyaw - baseYaw );

			if ( abs( newyaw - yaw ) > 10 )
			{
				if ( newyaw > yaw )
					newyaw = yaw + 10;
				else
					newyaw = yaw - 10;
			}
			yaw = newyaw;
		}
		// otherwise reuse old yaw

		if ( yaw < 0 )
		{
			weight = yaw / -45;
			if ( weight > 1 )
				weight = 1;

			self setAnimLimited( %generic_aim_right, weight, interval );
			self setAnimLimited( %generic_aim_left, 0, interval );
		}
		else
		{
			weight = yaw / 45;
			if ( weight > 1 )
				weight = 1;

			self setAnimLimited( %generic_aim_left, weight, interval );
			self setAnimLimited( %generic_aim_right, 0, interval );
		}

		wait interval;
	}
}


// decides on the number of shots to do in a burst.
decideNumShotsForBurst()
{
	numShots = 0;
	fixedBurstCount = weaponBurstCount( self.weapon );

	if ( fixedBurstCount )
		numShots = fixedBurstCount;
	else if ( animscripts\weaponList::usingSemiAutoWeapon() )
		numShots = anim.semiFireNumShots[ randomint( anim.semiFireNumShots.size ) ];
	else if ( self.fastBurst )
		numShots = anim.fastBurstFireNumShots[ randomint( anim.fastBurstFireNumShots.size ) ];
	else
		numShots = anim.burstFireNumShots[ randomint( anim.burstFireNumShots.size ) ];

	if ( numShots <= self.bulletsInClip )
		return numShots;

	assertex( self.bulletsInClip >= 0, self.bulletsInClip );

	if ( self.bulletsInClip <= 0 )
		return 1;

	return self.bulletsInClip;
}

decideNumShotsForFull()
{
	numShots = self.bulletsInClip;
	if ( weaponClass( self.weapon ) == "mg" )
	{
		choice = randomfloat( 10 );
		if ( choice < 3 )
			numShots = randomIntRange( 2, 6 );
		else if ( choice < 8 )
			numShots = randomIntRange( 6, 12 );
		else
			numShots = randomIntRange( 12, 20 );
	}

	return numShots;
}

insure_dropping_clip( note, flagName )
{
	/#
	// will turn this assert on after the current anims get fixed
	//assertex( isdefined( self.last_drop_clip_time ) && self.last_drop_clip_time > gettime() - 5000, "Tried to do attach clip notetrack without doing drop clip notetrack first, do /g_dumpanims " + self getentnum() + " and report erroneous anim." );
	#/
}

handleDropClip( flagName )
{
	self endon( "killanimscript" );
	self endon( "abort_reload" );

	/#
	// make sure that we don't do clip anims without drop clip first
	self.last_drop_clip_time = gettime();
	#/
	//prof_begin( "handleDropClip" );

	clipModel = undefined;
	if ( self.weaponInfo[ self.weapon ].useClip )
		clipModel = getWeaponClipModel( self.weapon );

	/#
	if ( isdefined( clipModel ) )
		self thread assertDropClipCleanedUp( 4, clipModel );
	#/

	if ( self.weaponInfo[ self.weapon ].hasClip )
	{
		if ( usingSidearm() )
			self playsound( "weap_reload_pistol_clipout_npc" );
		else
			self playsound( "weap_reload_smg_clipout_npc" );

		if ( isDefined( clipModel ) )
		{
			self hidepart( "tag_clip" );
			self thread dropClipModel( clipModel, "tag_clip" );
			self.weaponInfo[ self.weapon ].hasClip = false;

			self thread resetClipOnAbort( clipModel );
		}
	}

	//prof_end( "handleDropClip" );

	for ( ;; )
	{
		self waittill( flagName, noteTrack );

		switch( noteTrack )
		{
 		case "attach clip left":
 		case "attach clip right":
 			if ( isdefined( clipModel ) )
 			{
				self attach( clipModel, "tag_inhand" );
				self thread resetClipOnAbort( clipModel, "tag_inhand" );
			}

			// if we abort the reload after this point, we don't want to have to do it again
			self animscripts\weaponList::RefillClip();

 			break;

		case "detach clip nohand":
  			if ( isdefined( clipModel ) )
				self detach( clipModel, "tag_inhand" );
			break;

 		case "detach clip right":
 		case "detach clip left":
  			if ( isdefined( clipModel ) )
 			{
				self detach( clipModel, "tag_inhand" );
				self showpart( "tag_clip" );
 				self notify( "clip_detached" );
				self.weaponInfo[ self.weapon ].hasClip = true;
			}

			if ( usingSidearm() )
				self playsound( "weap_reload_pistol_clipin_npc" );
			else
				self playsound( "weap_reload_smg_clipin_npc" );

			self.a.needsToRechamber = 0;

 			return;
		}
	}
}


resetClipOnAbort( clipModel, currentTag )
{
	self notify( "clip_detached" );
	self endon( "clip_detached" );
	//self endon ( "death" ); // don't end on death or we won't delete the clip when we die!

	self waittill_any( "killanimscript", "abort_reload" );

	// we can be dead but still defined. if we're undefined we got deleted.
	if ( !isDefined( self ) )
		return;

	if ( isDefined( currentTag ) )
		self detach( clipModel, currentTag );

	if ( isAlive( self ) )
	{
		if ( self.weapon != "none" && self.weaponinfo[ self.weapon ].position != "none" )
		{
			self showpart( "tag_clip" );
		}
		self.weaponInfo[ self.weapon ].hasClip = true;
	}
	else
	{
		if ( isDefined( currentTag ) )
			self dropClipModel( clipModel, currentTag );
	}
}


dropClipModel( clipModel, tagName )
{
	clip = spawn( "script_model", self getTagOrigin( tagName ) );
	clip setModel( clipModel );
	clip.angles = self getTagAngles( tagName );
	clip PhysicsLaunchClient( clip.origin, (0,0,0) );

	wait 10;

	if ( isDefined( clip ) )
		clip delete();
}


/#
assertDropClipCleanedUp( waitTime, clipModel )
{
	self endon( "death" );
	self endon( "abort_reload" );
	self endon( "clip_detached" );

	wait waitTime;

	// this assert can be fixed by adding an "abort_reload" notify from whatever interrupted the reload.
	assertmsg( "AI " + self getEntityNumber() + " started a reload and didn't reset clip models after " + waitTime + " seconds" );
}
#/

moveToOriginOverTime( origin, time )
{
	self endon( "killanimscript" );

	distSq = distanceSquared( self.origin, origin );

	if ( distSq < 1 )
	{
		self safeTeleport( origin );
		return;
	}


	if ( distSq > 16 * 16 && !self mayMoveToPoint( origin ) )
	{
		 /# println( "^1Warning: AI starting behavior for node at " + origin + " but could not move to that point." ); #/
		return;
	}

	self.keepClaimedNodeIfValid = true;

	offset = self.origin - origin;

	frames = int( time * 20 );
	offsetreduction = ( offset * 1.0 / frames );

	for ( i = 0; i < frames; i++ )
	{
		offset -= offsetreduction;
		self safeTeleport( origin + offset );
		wait .05;
	}

	self.keepClaimedNodeIfValid = false;
}

returnTrue() { return true; }

playLookAnimation( lookAnim, lookTime, canStopCallback )
{
	if ( !isdefined( canStopCallback ) )
		canStopCallback = ::returnTrue;

	for ( i = 0; i < lookTime * 10; i++ )
	{
		// Break out if you saw somebody lately
		if ( isalive( self.enemy ) )
		{
			if ( self canSeeEnemy() && [[ canStopCallback ]]() )
				return;
		}
		if ( self isSuppressedWrapper() && [[ canStopCallback ]]() )
			return;

		self setAnimKnobAll( lookAnim, %body, 1, .1 );
		wait( 0.1 );
	}
}


throwDownWeapon( swapAnim )
{
	self endon( "killanimscript" );

	// Too many issues right now
//	self animMode( "angle deltas" );
//	self setFlaggedAnimKnobAllRestart( "weapon swap", swapAnim, %body, 1, .1, 1 );
//	self DoNoteTracks( "weapon swap" );

	self animscripts\shared::placeWeaponOn( self.secondaryweapon, "right" );

	self maps\_gameskill::didSomethingOtherThanShooting();
}

rpgPlayerRepulsor()
{
	// Creates a repulsor on the player when shooting at the player
	// After a couple freebe misses the repulsor is removed

	MISSES_REMAINING = rpgPlayerRepulsor_getNumMisses();
	if ( MISSES_REMAINING == 0 )
		return;

	self endon( "death" );
	for(;;)
	{
		level waittill( "an_enemy_shot", guy );

		if ( guy != self )
			continue;

		if ( !isdefined( guy.enemy ) )
			continue;

		if ( guy.enemy != level.player )
			continue;

		if ( ( isdefined( level.createRpgRepulsors ) ) && ( level.createRpgRepulsors == false ) )
			continue;

		thread rpgPlayerRepulsor_create();

		MISSES_REMAINING--;
		if ( MISSES_REMAINING <= 0 )
			return;
	}
}

rpgPlayerRepulsor_getNumMisses()
{
	skill = getdifficulty();
	switch( skill )
	{
		case "gimp":
		case "easy":
			return 2;
		case "medium":
		case "hard":
		case "difficult":
			return 1;
		case "fu":
			return 0;
	}
	return 2;
}

rpgPlayerRepulsor_create()
{
	repulsor = Missile_CreateRepulsorEnt( level.player, 5000, 800 );
	wait 4.0;
	Missile_DeleteAttractor( repulsor );
}