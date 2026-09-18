//================================================================================
// SetPoseMovement - Sets the pose (stand, crouch, prone) and movement (run, walk, 
// crawl, stop) to the specified values.  Accounts for all possible starting poses 
// and movements.
//================================================================================

#include animscripts\notetracks;
#include animscripts\Utility;
#include maps\_Utility;
#include common_scripts\utility;
#using_animtree( "generic_human" );


SetPoseMovement( desiredPose, desiredMovement )
{
	// Scripts can pass empty strings, meaning they don't want to change that aspect of the state.
	if ( desiredPose == "" )
	{
		if ( ( self.a.pose == "prone" ) && ( ( desiredMovement == "walk" ) || ( desiredMovement == "run" ) ) )
			desiredPose = "crouch";
		else
			desiredPose = self.a.pose;
	}
	if ( !IsDefined( desiredMovement ) || desiredMovement == "" )
	{
		desiredMovement = self.a.movement;
	}

	// Now call the function.
	[[ anim.SetPoseMovementFnArray[ desiredPose ][ desiredMovement ] ]]();
}


// *****************************
//  All of the following "Begin" functions ensure that the actor is in the given pose and movement type.
//  They return false if nothing needs to be done, true otherwise.
// *****************************

InitPoseMovementFunctions()
{
	// Make an array of movement and pose changing functions.  
	// Indices are: "desired movement", "desired pose"
	anim.SetPoseMovementFnArray[ "stand" ][ "stop" ] = 	::BeginStandStop;
	anim.SetPoseMovementFnArray[ "stand" ][ "walk" ] = 	::BeginStandWalk;
	anim.SetPoseMovementFnArray[ "stand" ][ "run" ] = 	::BeginStandRun;

	anim.SetPoseMovementFnArray[ "crouch" ][ "stop" ] = 	::BeginCrouchStop;
	anim.SetPoseMovementFnArray[ "crouch" ][ "walk" ] = 	::BeginCrouchWalk;
	anim.SetPoseMovementFnArray[ "crouch" ][ "run" ] = 	::BeginCrouchRun;

	anim.SetPoseMovementFnArray[ "prone" ][ "stop" ] = 	::BeginProneStop;
	anim.SetPoseMovementFnArray[ "prone" ][ "walk" ] = 	::BeginProneWalk;
	anim.SetPoseMovementFnArray[ "prone" ][ "run" ] = 	::BeginProneRun;
}


//--------------------------------------------------------------------------------
// Standing poses
//--------------------------------------------------------------------------------

BeginStandStop()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			return false;

		case "walk":
			StandWalkToStand();
			break;

		default:
			assert( self.a.movement == "run" );
			StandRunToStand();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToStand();
			break;

		case "walk":
			CrouchWalkToStand();
			break;

		default:
			assert( self.a.movement == "run" );
			CrouchRunToStand();
			break;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		switch( self.a.movement )
		{
		case "stop":
			ProneToStand();
			break;

		default:
			assert( self.a.movement == "walk" || self.a.movement == "run" );
			ProneToStand();	// Do I need to stop crawling first?  Hope not.
			break;
		}
		break;
	}

	return true;
}

BeginStandWalk()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			BlendIntoStandWalk();
			break;

		case "walk":
			return false;

		default:
			assert( self.a.movement == "run" );
			BlendIntoStandWalk();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToStandWalk();
			break;

		case "walk":
			BlendIntoStandWalk();
			break;

		default:
			assert( self.a.movement == "run" );
			BlendIntoStandWalk();
			break;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		ProneToStandWalk();
		break;
	}

	return true;
}

BeginStandRun()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
		case "walk":
			return BlendIntoStandRun();

		default:
			assert( self.a.movement == "run" );
			return false;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			return CrouchToStandRun();

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			return BlendIntoStandRun();
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		ProneToStandRun();
		break;
	}

	return true;
}

//--------------------------------------------------------------------------------
// Crouching functions
//--------------------------------------------------------------------------------
BeginCrouchStop()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			StandToCrouch();
			break;
		case "walk":
			StandWalkToCrouch();
			break;
		case "run":
			StandRunToCrouch();
			break;
		default:
			assertEX( 0, "SetPoseMovement::BeginCrouchStop " + self.a.pose + " " + self.a.movement );
		}
		break;
	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			// Do nothing
			break;
		case "walk":
			CrouchWalkToCrouch();
			break;
		case "run":
			CrouchRunToCrouch();
			break;
		default:
			assertEX( 0, "SetPoseMovement::BeginCrouchStop " + self.a.pose + " " + self.a.movement );
		}
		break;
	case "prone":
		ProneToCrouch();
		break;
	default:
		assertEX( 0, "SetPoseMovement::BeginCrouchStop " + self.a.pose + " " + self.a.movement );
	}
}

BeginCrouchWalk()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			BlendIntoCrouchWalk();
			break;

		case "walk":
			BlendIntoCrouchWalk();
			break;

		default:
			assert( self.a.movement == "run" );
			BlendIntoCrouchWalk();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToCrouchWalk();
			break;

		case "walk":
			return false;

		default:
			assert( self.a.movement == "run" );
			BlendIntoCrouchWalk();
			break;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		// Let's try going straight to the run and then blending back to see what it looks like.
		ProneToCrouchWalk();
		break;
	}

	return true;
}

BeginCrouchRun()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			BlendIntoCrouchRun();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			BlendIntoCrouchRun();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToCrouchRun();
			break;

		case "walk":
			BlendIntoCrouchRun();
			break;

		default:
			assert( self.a.movement == "run" );
			return false;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		ProneToCrouchRun();
		break;
	}

	return true;
}


//--------------------------------------------------------------------------------
// Prone Functions
//--------------------------------------------------------------------------------

BeginProneStop()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			StandToProne();
			break;
		case "walk":
			StandToProne();
			break;
		case "run":
			CrouchRunToProne();
			break;
		default:
			assertEX( 0, "SetPoseMovement::BeginCrouchRun " + self.a.pose + " " + self.a.movement );
		}
		break;
	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToProne();
			break;
		case "walk":
			CrouchToProne();
			break;
		case "run":
			CrouchRunToProne();
			break;
		default:
			assertEX( 0, "SetPoseMovement::BeginCrouchRun " + self.a.pose + " " + self.a.movement );
		}
		break;
	case "prone":
		switch( self.a.movement )
		{
		case "stop":
			// Do nothing
			break;
		case "walk":
		case "run":
			ProneCrawlToProne();
			break;
		default:
			assertEX( 0, "SetPoseMovement::BeginCrouchRun " + self.a.pose + " " + self.a.movement );
		}
		break;
	default:
		assertEX( 0, "SetPoseMovement::BeginCrouchRun " + self.a.pose + " " + self.a.movement );
	}
}

BeginProneWalk()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			StandToProneWalk();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			CrouchRunToProneWalk();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToProneWalk();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			CrouchRunToProneWalk();
			break;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		switch( self.a.movement )
		{
		case "stop":
			ProneToProneRun();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			self.a.movement = "walk";
			return false;
		}
		break;
	}

	return true;
}

BeginProneRun()
{
	switch( self.a.pose )
	{
	case "stand":
		switch( self.a.movement )
		{
		case "stop":
			StandToProneRun();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			CrouchRunToProneRun();
			break;
		}
		break;

	case "crouch":
		switch( self.a.movement )
		{
		case "stop":
			CrouchToProneRun();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			CrouchRunToProneRun();
			break;
		}
		break;

	default:
		assert( self.a.pose == "prone" );
		switch( self.a.movement )
		{
		case "stop":
			assert( self.a.movement == "stop" );
			ProneToProneRun();
			break;

		default:
			assert( self.a.movement == "run" || self.a.movement == "walk" );
			self.a.movement = "run";
			return false;
		}
		break;
	}

	return true;
}


//--------------------------------------------------------------------------------
// Standing support functions
//--------------------------------------------------------------------------------

PlayBlendTransition( transAnim, crossblendTime, endPose, endMovement )
{
	endTime = gettime() + crossblendTime * 1000;
	
	if( isarray( transAnim ) )
		transAnim = transAnim[ randomint( transAnim.size ) ];
	
	self setflaggedanimknoball( "blendTransition", transAnim, %body, 1, crossblendTime, 1 );

	self DoNoteTracksForTime( crossblendTime / 2, "blendTransition" );

	self.a.pose = endPose;
	self.a.movement = endMovement;

	waittime = ( endTime - gettime() ) / 1000;
	if ( waittime < 0.05 )
		waittime = 0.05;
	
	self DoNoteTracksForTime( waittime, "blendTransition" );
}

PlayTransitionStandWalk( transAnim, finalAnim )
{
	PlayTransitionAnimation( transAnim, "stand", "walk", finalAnim );
}

StandWalkToStand()
{
	assertEX( self.a.pose == "stand", "SetPoseMovement::StandWalkToStand " + self.a.pose );
	assertEX( self.a.movement == "walk", "SetPoseMovement::StandWalkToStand " + self.a.movement );

	// no transition animations.

	self.a.movement = "stop";
}


StandWalkToCrouch()
{
	StandWalkToStand();
	StandToCrouch();
}


StandRunToStand()
{
	assertEX( self.a.pose == "stand", "SetPoseMovement::StandRunToStand " + self.a.pose );
	assertEX( self.a.movement == "run", "SetPoseMovement::StandRunToStand " + self.a.movement );

	// Do nothing, just blend straight in
	self.a.movement = "stop";
}

StandRunToCrouch()
{
	self.a.movement = "stop";
	self.a.pose = "crouch";
}

PlayBlendTransitionStandRun( animname )
{
	// if we're blending into stand run from stop,
	// we probably just did utility::initialize's clearAnim(body, .3)
	// so we don't have to spend more than .3 seconds here.
	// (then we can do fun things like shooting or reloading.)
	transtime = 0.3;
	if ( self.a.movement != "stop" )
	{
		self endon( "movemode" );
		transtime = 1.0;
	}

	PlayBlendTransition( animname, transtime, "stand", "run" );
}

BlendIntoStandRun()
{
	if ( !self.faceMotion )
	{
		self.a.movement = "run";
		self.a.pose = "stand";
		return false;
	}
	
	if ( isDefined( self.run_overrideanim ) )
	{
		PlayBlendTransitionStandRun( self.run_overrideanim );
		return true;
	}

	// Set the specific forward animation we are using to weight 1 immediately
	// we will make sure it is blended smoothly by blending in its parent, combatrun_forward
	runAnimTransTime = 0.1;
	if ( self.a.movement != "stop" && self.stairsState == "none" )
		runAnimTransTime = 0.5;
		
	if ( isdefined( self.sprint ) )
		self setAnimKnobLimited( moveAnim( "sprint" ), 1, runAnimTransTime, 1 );
	else
		self setAnimKnobLimited( animscripts\run::GetRunAnim(), 1, runAnimTransTime, 1 );

	self animscripts\run::SetMoveNonForwardAnims( moveAnim( "move_b" ), moveAnim( "move_l" ), moveAnim( "move_r" ), self.sideStepRate );
	self thread animscripts\run::SetCombatStandMoveAnimWeights( "run" );

	wait 0.05;
	PlayBlendTransitionStandRun( %combatrun );
	return true;
}


BlendIntoStandWalk()
{
	if ( self.a.movement != "stop" )
		self endon( "movemode" );

	if ( !isdefined( self.alwaysRunForward ) && self.a.pose != "prone" )
		self animscripts\run::SetMoveNonForwardAnims( moveAnim( "move_b" ), moveAnim( "move_l" ), moveAnim( "move_r" ) );

	self.a.pose = "stand";
	self.a.movement = "walk";
}


CrouchToStand()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchToStand " + self.a.pose );
	assertEX( self.a.movement == "stop", "SetPoseMovement::CrouchToStand " + self.a.movement );

	standSpeed = 1;
	if ( isdefined( self.fastStand ) )
	{
		standSpeed = 1.8;
		self.fastStand = undefined;
	}

	if ( self usingSidearm() )
	{
		PlayTransitionAnimation( %pistol_crouchaimstraight2stand, "stand", "stop", undefined, standSpeed );
	}
	else
	{
		// Decide which idle animation to do
		self randomizeIdleSet();

		PlayTransitionAnimation( %crouch2stand, "stand", "stop", undefined, standSpeed );
	}

}


//--------------------------------------------------------------------------------
// Crouched Support Functions
//--------------------------------------------------------------------------------


CrouchToCrouchWalk()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchToCrouchWalk " + self.a.pose );
	assertEX( self.a.movement == "stop", "SetPoseMovement::CrouchToCrouchWalk " + self.a.movement );

	BlendIntoCrouchWalk();
}

CrouchToStandWalk()
{
	CrouchToCrouchWalk();
	BlendIntoStandWalk();
}

CrouchWalkToCrouch()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchWalkToCrouch " + self.a.pose );
	assertEX( self.a.movement == "walk", "SetPoseMovement::CrouchWalkToCrouch " + self.a.movement );

	// Do nothing, just blend straight in
	self.a.movement = "stop";
}

CrouchWalkToStand()
{
	CrouchWalkToCrouch();
	CrouchToStand();
}

CrouchRunToCrouch()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchRunToCrouch " + self.a.pose );
	assertEX( self.a.movement == "run", "SetPoseMovement::CrouchRunToCrouch " + self.a.movement );

	// Do nothing, just blend straight in
	self.a.movement = "stop";
}

CrouchRunToStand()
{
	CrouchRunToCrouch();
	CrouchToStand();
}

CrouchToCrouchRun()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchToCrouchRun " + self.a.pose );
	assertEX( self.a.movement == "stop", "SetPoseMovement::CrouchToCrouchRun " + self.a.movement );

	BlendIntoCrouchRun();
}

CrouchToStandRun()
{
	return BlendIntoStandRun();
}

BlendIntoCrouchRun()
{
	if ( isDefined( self.crouchrun_combatanim ) )
	{
		PlayBlendTransition( self.crouchrun_combatanim, 0.6, "crouch", "run" );
	}
	else
	{
		self setanimknob( %crouchrun, 1, 0.4, self.moveplaybackrate );
		
		self thread animscripts\run::UpdateMoveAnimWeights( "crouchrun", moveAnim( "crouch" ), moveAnim( "crouch_b" ), moveAnim( "crouch_l" ), moveAnim( "crouch_r" ) );

		wait 0.05;
		PlayBlendTransition( %crouchrun, 0.4, "crouch", "run" );
	}
}

ProneToCrouchRun()
{
	assertEX( self.a.pose == "prone", "SetPoseMovement::ProneToCrouchRun " + self.a.pose );

	self OrientMode( "face current" );	// We don't want to rotate arbitrarily until we've actually stood up.
	self ExitProneWrapper( 1.0 );// make code stop lerping in the prone orientation to ground
	ProneLegsStraightTree( 0.2 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	PlayTransitionAnimation( %prone_2_crouch, "crouch", "run", animscripts\run::GetCrouchRunAnim() );
}

ProneToStandRun()
{
	ProneToCrouchRun();
	BlendIntoStandRun();
}

ProneToCrouchWalk()
{
	ProneToCrouchRun();
	BlendIntoCrouchWalk();
}

BlendIntoCrouchWalk()
{
	if ( isDefined( self.crouchrun_combatanim ) )
	{
		self setanimknoball( self.crouchrun_combatanim, %body, 1, 0.4 );
		PlayBlendTransition( self.crouchrun_combatanim, 0.6, "crouch", "walk" );
		self notify( "BlendIntoCrouchWalk" );
	}
	else
	{
		self setanimknob( %crouchrun, 1, 0.4, self.moveplaybackrate );
		
		self thread animscripts\run::UpdateMoveAnimWeights( "crouchrun", moveAnim( "crouch" ), moveAnim( "crouch_b" ), moveAnim( "crouch_l" ), moveAnim( "crouch_r" ) );

		wait 0.05;
		PlayBlendTransition( %crouchrun, 0.4, "crouch", "run" );
	}
}

StandToCrouch()
{
	assertEX( self.a.pose == "stand", "SetPoseMovement::StandToCrouch " + self.a.pose );
	assertEX( self.a.movement == "stop", "SetPoseMovement::StandToCrouch " + self.a.movement );

	// Decide which idle animation to do
	self randomizeIdleSet();

	crouchSpeed = 1;
	if ( isdefined( self.fastCrouch ) )
	{
		crouchSpeed = 1.8;
		self.fastCrouch = undefined;
	}

	PlayTransitionAnimation( %exposed_stand_2_crouch, "crouch", "stop", undefined, crouchspeed );
}

ProneToCrouch()
{
	assertEX( self.a.pose == "prone", "SetPoseMovement::StandToCrouch " + self.a.pose );

	// Decide which idle animation to do
	self randomizeIdleSet();

	self OrientMode( "face current" );	// We don't want to rotate arbitrarily until we've actually stood up.
	self ExitProneWrapper( 1.0 );// make code stop lerping in the prone orientation to ground
	ProneLegsStraightTree( 0.1 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	PlayTransitionAnimation( %prone_2_crouch, "crouch", "stop" );

// TODO: Find out if the above lines give the same functionality as below (notably the UpdateProne bit)
//	self exitprone(1.0); // make code stop lerping in the prone orientation to ground
//
//	ProneLegsStraightTree(0.1);
//	self setflaggedanimknob("animdone", %prone2crouch_straight, 1, .1, 1);
//	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
//	self waittill ("animdone");
//	self.a.pose = "crouch";
}

ProneToStand()
{
	assertEx( self.a.pose == "prone", self.a.pose );

	self OrientMode( "face current" );	// We don't want to rotate arbitrarily until we've actually stood up.
	self ExitProneWrapper( 1.0 );// make code stop lerping in the prone orientation to ground
	ProneLegsStraightTree( 0.1 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	PlayTransitionAnimation( %prone_2_stand, "stand", "stop" );
}

ProneToStandWalk()
{
	ProneToCrouch();
	CrouchToCrouchWalk();
	BlendIntoStandWalk();
}

//--------------------------------------------------------------------------------
// Prone Support Functions
//--------------------------------------------------------------------------------

ProneToProneMove( movement )
{
	// (The parameter "movement" is just used for setting the state variable, since prone guys move the same whether
	// "walking" or "running".
	assertEX( self.a.pose == "prone", "SetPoseMovement::ProneToProneMove " + self.a.pose );
	assertEX( self.a.movement == "stop", "SetPoseMovement::ProneToProneMove " + self.a.movement );
	assertEX( ( movement == "walk" || movement == "run" ), "SetPoseMovement::ProneToProneMove got bad parameter " + movement );

	ProneLegsStraightTree( 0.1 );
	PlayTransitionAnimation( %prone_2_prone_crawl, "prone", movement, %prone_crawl );

	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
}


ProneToProneRun()
{
	ProneToProneMove( "run" );
}

ProneCrawlToProne()
{
	assertEX( self.a.pose == "prone", "SetPoseMovement::ProneCrawlToProne " + self.a.pose );
	assertEX( ( self.a.movement == "walk" || self.a.movement == "run" ), "SetPoseMovement::ProneCrawlToProne " + self.a.movement );

	ProneLegsStraightTree( 0.1 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	PlayTransitionAnimation( %prone_crawl_2_prone, "prone", "stop" );

// TODO: Find out if the above lines give the same functionality as below (notably the UpdateProne bit)
//	ProneLegsStraightTree(0.1);
//	self setflaggedanimknob("animdone", %prone_crawl2aim, 1, 0.1, 1);
//	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
//	self waittill("animdone");
//	self.a.movement = "stop";
}

CrouchToProne()
{
	assertEX( self.a.pose == "crouch", "SetPoseMovement::CrouchToProne " + self.a.pose );
	// I'd like to be able to assert that I'm stopped at this point, but until I get a better solution for 
	// guys who are walking and running, this is used for them too.
//	assertEX(self.a.movement == "stop", "SetPoseMovement::CrouchToProne "+self.a.movement);

	self setProneAnimNodes( -45, 45, %prone_legs_down, %exposed_aiming, %prone_legs_up );
	self EnterProneWrapper( 1.0 );// make code start lerping in the prone orientation to ground

	ProneLegsStraightTree( 0.3 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	PlayTransitionAnimation( %crouch_2_prone, "prone", "stop" );

// TODO: Find out if the above lines give the same functionality as below (notably the UpdateProne bit)
//	self SetProneAnimNodes(-45, 45, %prone_legsdown, %prone_legsstraight, %prone_legsup);
//	self EnterProne(1.0); // make code start lerping in the prone orientation to ground
//
//	ProneLegsStraightTree(0.3);
//	self setflaggedanimknob("animdone", %crouch_2_prone, 1, .3, 1);
//	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
//	self waittill ("animdone");
//	self.a.pose = "prone";
}

CrouchToProneWalk()
{
	CrouchToProne();
	ProneToProneRun();
}

CrouchToProneRun()
{
	CrouchToProne();
	ProneToProneRun();
}

StandToProne()
{
	assertEX( self.a.pose == "stand", "SetPoseMovement::StandToProne " + self.a.pose );
	// I'd like to be able to assert that I'm stopped at this point, but until I get a better solution for 
	// guys who are walking and running, this is used for them too.
//	assertEX(self.a.movement == "stop", "SetPoseMovement::StandToProne "+self.a.movement);
	self endon( "entered_pose" + "prone" );

	proneTime = 0.5;// was 1
	thread PlayTransitionAnimationThread_WithoutWaitSetStates( %stand_2_prone, "prone", "stop", undefined, proneTime );

	self waittillmatch( "transAnimDone2", "anim_pose = \"crouch\"" );
	waittillframeend;// so that the one in donotetracks gets hit first
	// cause the next pose is prone
	self setProneAnimNodes( -45, 45, %prone_legs_down, %exposed_aiming, %prone_legs_up );
	self EnterProneWrapper( proneTime );// make code start lerping in the prone orientation to ground
	self.a.movement = "stop";

	ProneLegsStraightTree( 0.2 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
	self waittillmatch( "transAnimDone2", "end" );

// TODO: Find out if the above lines give the same functionality as below (notably the UpdateProne bit)
//	self SetProneAnimNodes(-45, 45, %prone_legsdown, %prone_legsstraight, %prone_legsup);
//	self EnterProne(1.0); // make code start lerping in the prone orientation to ground
//
//	ProneLegsStraightTree(0.2);
//	self setflaggedanimknob("animdone", %stand2prone_onehand, 1, .2, 1);
//	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
//	self waittill ("animdone");
//	self.a.pose = "prone";
}

StandToProneWalk()
{
	StandToProne();
	ProneToProneRun();
}

StandToProneRun()
{
	StandToProne();
	ProneToProneRun();
}

CrouchRunToProne()
{
	assertEX( ( self.a.pose == "crouch" ) || ( self.a.pose == "stand" ), "SetPoseMovement::CrouchRunToProne " + self.a.pose );
	assertEX( ( self.a.movement == "run" || self.a.movement == "walk" ), "SetPoseMovement::CrouchRunToProne " + self.a.movement );

	pronetime = 0.5;// was 1
	self setProneAnimNodes( -45, 45, %prone_legs_down, %exposed_aiming, %prone_legs_up );
	self EnterProneWrapper( proneTime );// make code start lerping in the prone orientation to ground

	ProneLegsStraightTree( 0.2 );
	self animscripts\cover_prone::UpdateProneWrapper( 0.1 );

	runDirection = animscripts\utility::getQuadrant( self getMotionAngle() );

	diveanim = %crouch_2_prone;

	localDeltaVector = GetMoveDelta( diveanim, 0, 1 );
	endPoint = self LocalToWorldCoords( localDeltaVector );
	if ( self maymovetopoint( endPoint ) )
	{
		PlayTransitionAnimation( diveanim, "prone", "stop", undefined, pronetime );
	}
	else
	{
		//thread [[anim.println]]("Can't dive to prone.");#/
		PlayTransitionAnimation( %crouch_2_prone_firing, "prone", "stop", undefined, pronetime );
	}
}

CrouchRunToProneWalk()
{
	CrouchRunToProne();
	ProneToProneRun();
}

CrouchRunToProneRun()
{
	CrouchRunToProne();
	ProneToProneRun();
}

//--------------------------------------------------------------------------------
// General support functions
//--------------------------------------------------------------------------------


PlayTransitionAnimationThread_WithoutWaitSetStates( transAnim, endPose, endMovement, finalAnim, rate )
{
	self endon( "killanimscript" );// the threaded one needs this or it wont die
	self endon( "entered_pose" + endPose );
	PlayTransitionAnimationFunc( transAnim, endPose, endMovement, finalAnim, rate, false );
}

PlayTransitionAnimation( transAnim, endPose, endMovement, finalAnim, rate )
{
	PlayTransitionAnimationFunc( transAnim, endPose, endMovement, finalAnim, rate, true );
}


PlayTransitionAnimationFunc( transAnim, endPose, endMovement, finalAnim, rate, waitSetStatesEnabled )
{
	if ( !isdefined( rate ) )
		rate = 1;

	 /#
	if ( getdebugdvar( "debug_grenadehand" ) == "on" )
	{
		if ( endPose != self.a.pose )
		{
			if ( !animhasnotetrack( transAnim, "anim_pose = \"" + endPose + "\"" ) )
			{
				println( "Animation ", transAnim, " lacks an endpose notetrack of ", endPose );
				assertEx( 0, "A transition animation is missing a pose notetrack (see the line above)" );
			}
		}
		if ( endMovement != self.a.movement )
		{
			if ( !animhasnotetrack( transAnim, "anim_movement = \"" + endMovement + "\"" ) )
			{
				println( "Animation ", transAnim, " lacks an endmovement notetrack of ", endMovement );
				assertEx( 0, "A transition animation is missing a movement notetrack (see the line above)" );
			}
		}
	}
	#/

	// Use a second thread to set the anim state halfway through the animation
	if ( waitSetStatesEnabled )
		self thread waitSetStates( getanimlength( transAnim ) / 2.0, "killtimerscript", endPose );

	// Play the anim
	// setflaggedanimknoball(notifyName, anim, rootAnim, goalWeight, goalTime, rate) 
	self setflaggedanimknoballrestart( "transAnimDone2", transAnim, %body, 1, .2, rate );
	if ( !isDefined( self.a.pose ) )
		self.pose = "undefined";
	if ( !isDefined( self.a.movement ) )
		self.movement = "undefined";
	debugIdentifier = "";
	 /#debugIdentifier = self.script + ", " + self.a.pose + " to " + endPose + ", " + self.a.movement + " to " + endMovement;#/
	self animscripts\shared::DoNoteTracks( "transAnimDone2", undefined, debugIdentifier );

	// In case we finished earlier than we expected (eg the animation was already playing before we started), 
	// set the variables and kill the other thread.
	self notify( "killtimerscript" );
	self.a.pose = endPose;
	self notify( "entered_pose" + endPose );

	self.a.movement = endMovement;

	if ( isDefined( finalAnim ) )
	{
		// setflaggedanimknoball(notifyName, anim, rootAnim, goalWeight, goalTime, rate) 
		self setanimknoball( finalAnim, %body, 1, 0.3, rate );	// Set the animation instantly
	}
}


waitSetStates( timetowait, killmestring, endPose )
{
	self endon( "killanimscript" );
	self endon( "death" );
	self endon( killmestring );
	oldpose = self.a.pose;
	wait timetowait;

	// We called Enter/ExitProne before this function was called.  These lines should not be necessary, but 
	// for some reason the code is picking up that I'm setting pose from prone to crouch without calling 
	// exitprone().  I just hope it's not a thread leak I've missed.
	if ( oldpose!= "prone" && endPose == "prone" )
	{
		self animscripts\cover_prone::UpdateProneWrapper( 0.1 );
		self EnterProneWrapper( 1.0 );// make code start lerping in the prone orientation to ground
	}
	else
	if ( oldpose == "prone" && endPose != "prone" )
	{
		self ExitProneWrapper( 1.0 );// make code stop lerping in the prone orientation to ground
		self OrientMode( "face default" );	// We were most likely in "face current" while we were prone.
	}
}


ProneLegsStraightTree( blendtime )
{
	self setanimknoball( %prone_legsstraight, %body, 1, blendtime, 1 );
}

