#include animscripts\utility;
#include maps\_utility;
#using_animtree( "generic_human" );

// Deprecated. only used for old traverses that will be deleted.
advancedTraverse( traverseAnim, normalHeight )
{
	// do not do code prone in this script
	self.desired_anim_pose = "crouch";
	animscripts\utility::UpdateAnimPose();

	self endon( "killanimscript" );
	self traverseMode( "nogravity" );
	self traverseMode( "noclip" );// So he doesn't get stuck if the wall is a little too high

	// orient to the Negotiation start node
	startnode = self getnegotiationstartnode();
	assert( isdefined( startnode ) );
	self OrientMode( "face angle", startnode.angles[ 1 ] );
	realHeight = startnode.traverse_height - startnode.origin[ 2 ];

	self thread teleportThread( realHeight - normalHeight );

	blendTime = 0.15;

	self clearAnim( %body, blendTime );
	self setFlaggedAnimKnoballRestart( "traverse", traverseAnim, %root, 1, blendTime, 1 );

	gravityToBlendTime = 0.2;
	endBlendTime = 0.2;

	self thread animscripts\notetracks::DoNoteTracksForever( "traverse", "no clear" );
	if ( !animHasNotetrack( traverseAnim, "gravity on" ) )
	{
		magicWhateverTime_WhereTheHeckDidWeGetThisNumberAnyway = 1.23;
		wait( magicWhateverTime_WhereTheHeckDidWeGetThisNumberAnyway - gravityToBlendTime );
		self traverseMode( "gravity" );
		wait( gravityToBlendTime );
	}
	else
	{
		self waittillmatch( "traverse", "gravity on" );
		self traverseMode( "gravity" );
		if ( !animHasNotetrack( traverseAnim, "blend" ) )
			wait( gravityToBlendTime );
		else
			self waittillmatch( "traverse", "blend" );
	}
}

teleportThread( verticalOffset )
{
	self endon( "killanimscript" );
	self notify( "endTeleportThread" );
	self endon( "endTeleportThread" );

	reps = 5;
	offset = ( 0, 0, verticalOffset / reps );

	for ( i = 0; i < reps; i++ )
	{
		self forceTeleport( self.origin + offset );
		wait .05;
	}
}


teleportThreadEx( verticalOffset, delay, frames, animRate )
{
	self endon( "killanimscript" );
	self notify( "endTeleportThread" );
	self endon( "endTeleportThread" );

	if ( (verticalOffset == 0) || (frames <= 0) )
		return;

	if ( delay > 0 )
		wait delay;

	offset = ( 0, 0, verticalOffset / frames );
	
	if ( isDefined( animRate ) && (animRate < 1.0) )
		self setFlaggedAnimKnoball( "traverseAnim", self.traverseAnim, self.traverseAnimRoot, 1, .2, animRate );

	for ( i = 0; i < frames; i++ )
	{
		self forceTeleport( self.origin + offset );
		wait .05;
	}
	
	if ( isDefined( animRate ) && (animRate < 1.0) )
		self setFlaggedAnimKnoball( "traverseAnim", self.traverseAnim, self.traverseAnimRoot, 1, .2, 1.0 );
}


DoTraverse( traverseData )
{
 	self endon( "killanimscript" );

	// do not do code prone in this script
	self.desired_anim_pose = "stand";
	animscripts\utility::UpdateAnimPose();

	// orient to the Negotiation start node
    startnode = self getNegotiationStartNode();
 	endNode = self getNegotiationEndNode();

    assert( isDefined( startnode ) );
    assert( isDefined( endNode ) );

    self OrientMode( "face angle", startnode.angles[ 1 ] );

	self.traverseHeight = traverseData[ "traverseHeight" ];
	self.traverseStartNode = startnode;

	traverseAnim = traverseData[ "traverseAnim" ];
	traverseToCoverAnim = traverseData[ "traverseToCoverAnim" ];  // traversals that end up with 180-degree spins into cover at the end

	self traverseMode( "nogravity" );
	self traverseMode( "noclip" );

	self.traverseStartZ = self.origin[ 2 ];
	if ( !animHasNotetrack( traverseAnim, "traverse_align" ) )
	{
		 /# println( "^1Warning: animation ", traverseAnim, " has no traverse_align notetrack" ); #/
		self handleTraverseAlignment();
	}

	toCover = false;
	if ( isDefined( traverseToCoverAnim ) && isDefined( self.node ) && self.node.type == traverseData[ "coverType" ] && distanceSquared( self.node.origin, endNode.origin ) < 25 * 25 )
	{
		if ( AbsAngleClamp180( self.node.angles[ 1 ] - endNode.angles[ 1 ] ) > 160 )
		{
			toCover = true;
			traverseAnim = traverseToCoverAnim;
		}
	}

	if ( toCover )
	{
		if ( isdefined( traverseData[ "traverseToCoverSound" ] ) )
		{
			self thread play_sound_on_entity( traverseData[ "traverseToCoverSound" ] );
		}
	}
	else
	{
		if ( isdefined( traverseData[ "traverseSound" ] ) )
		{
			self thread play_sound_on_entity( traverseData[ "traverseSound" ] );
		}
	}
	self.traverseAnim = traverseAnim;
	self.traverseAnimRoot = %body;
	self setFlaggedAnimKnoballRestart( "traverseAnim", traverseAnim, %body, 1, .2, 1 );

	self.traverseDeathIndex = 0;
	self.traverseDeathAnim = traverseData[ "interruptDeathAnim" ];
	self animscripts\shared::DoNoteTracks( "traverseAnim", ::handleTraverseNotetracks );
	self traverseMode( "gravity" );

	if ( self.delayedDeath )
		return;

	self.a.nodeath = false;
	if ( toCover && isDefined( self.node ) && distanceSquared( self.origin, self.node.origin ) < 16 * 16 )
	{
		self.a.movement = "stop";
		self teleport( self.node.origin );
	}
	else if( IsDefined( traverseData[ "traverseStopsAtEnd" ] ) )
	{
		self.a.movement = "stop";
	}
	else
	{
		self.a.movement = "run";
		//self setAnimKnobAllRestart( animscripts\run::GetRunAnim(), %body, 1, 0.0, 1 );
		self clearanim( traverseAnim, 0.2 );
	}
	
	self.traverseAnimRoot = undefined;
	self.traverseAnim = undefined;
	self.deathAnim = undefined;
}

handleTraverseNotetracks( note )
{
	if ( note == "traverse_death" )
		return handleTraverseDeathNotetrack();
	else if ( note == "traverse_align" )
		return handleTraverseAlignment();
	else if ( note == "traverse_drop" )
		return handleTraverseDrop();
}

handleTraverseDeathNotetrack()
{
	if ( isdefined( self.traverseDeathAnim ) )
	{
		deathAnimArray = self.traverseDeathAnim[ self.traverseDeathIndex ];
		self.deathAnim = deathAnimArray[ randomint( deathAnimArray.size ) ];
		self.traverseDeathIndex++;
	}
}

handleTraverseAlignment()
{
	self traverseMode( "nogravity" );
	self traverseMode( "noclip" );
	if ( isDefined( self.traverseHeight ) && isDefined( self.traverseStartNode.traverse_height ) )
	{
		currentHeight = self.traverseStartNode.traverse_height - self.traverseStartZ;
		self thread teleportThread( currentHeight - self.traverseHeight );
	}
}

handleTraverseDrop()
{
	startpos = self.origin + ( 0, 0, 32 );
	trace = bullettrace( startpos, self.origin + ( 0, 0, -512 ), false, undefined );
	endpos = trace[ "position" ];
	dist = distance( startpos, endpos );
	realDropHeight = dist - 32 - 0.5;// 0.5 makes sure we end up above the ground a bit

	traverseAnimPos = self getAnimTime( self.traverseAnim );
	traverseAnimDelta = getMoveDelta( self.traverseAnim, traverseAnimPos, 1.0 );
	traverseAnimLength = getAnimLength( self.traverseAnim );
	
	animDropHeight = 0 - traverseAnimDelta[ 2 ];
	assertEx( animDropHeight >= 0, animDropHeight );
	dropOffset = animDropHeight - realDropHeight;
	
	/#
	if ( getdvarint( "scr_traverse_debug" ) )
	{
		thread animscripts\utility::debugLine( startpos, endpos, ( 1, 1, 1 ), 2 * 20 );
		thread animscripts\utility::drawStringTime( "drop offset: " + dropOffset, endpos, ( 1, 1, 1 ), 2 );
	}
	#/
	
	if ( animDropHeight < realDropHeight )
		animRate = animDropHeight / realDropHeight;
	else
		animRate = 1;
		
	teleportLength = ( traverseAnimLength - traverseAnimPos ) / 3.0;	// let's make the teleport take 1/3 of the animation time roughly
	numFrames = ceil( teleportLength * 20 );	// 0.05 per frame. Maximum number of frames we can use

	self thread teleportThreadEx( dropOffset, 0, numFrames, animRate );
	self thread finishTraverseDrop( endpos[ 2 ] );
}

finishTraverseDrop( finalz )
{
	self endon( "killanimscript" );

	finalz += 4.0;
	while ( 1 )
	{
		if ( self.origin[ 2 ] < finalz )
		{
			self traverseMode( "gravity" );
			break;
		}
		wait .05;
	}
}

doNothingFunc()
{
	self animMode( "zonly_physics" );
	self waittill( "killanimscript" );
}

#using_animtree( "dog" );

dog_wall_and_window_hop( traverseName, height )
{
	self endon( "killanimscript" );
	self traverseMode( "nogravity" );
	self traverseMode( "noclip" );

	// orient to the Negotiation start node
	startnode = self getnegotiationstartnode();
	assert( isdefined( startnode ) );
	self OrientMode( "face angle", startnode.angles[ 1 ] );

	realHeight = startnode.traverse_height - startnode.origin[ 2 ];
	self thread teleportThread( realHeight - height );

	self clearanim( %root, 0.2 );
	self setflaggedanimrestart( "dog_traverse", anim.dogTraverseAnims[ traverseName ], 1, 0.2, 1 );

	self animscripts\shared::DoNoteTracks( "dog_traverse" );

	self.traverseComplete = true;
}


dog_jump_down( frames, rate )
{
	self endon( "killanimscript" );
	self traverseMode( "noclip" );

	// orient to the Negotiation start node
	startnode = self getnegotiationstartnode();
	assert( isdefined( startnode ) );
	self OrientMode( "face angle", startnode.angles[ 1 ] );

	height = self getNegotiationStartNode().origin[2] - self getNegotiationEndNode().origin[2];
	self.traverseAnim = anim.dogTraverseAnims[ "jump_down_40" ];
	self.traverseAnimRoot = %root;
	self thread teleportThreadEx( 40.0 - height, 0.1, frames, rate );

	self clearanim( %root, 0.2 );
	self setflaggedanimrestart( "traverseAnim", self.traverseAnim, 1, 0.2, 1 );
	self animscripts\shared::DoNoteTracks( "traverseAnim" );

	self clearanim( self.traverseAnim, 0 );	// start run immediately
	self traverseMode( "gravity" );
	self.traverseComplete = true;
	self.traverseAnimRoot = undefined;
	self.traverseAnim = undefined;
}

dog_jump_up( height, frames )
{
	self endon( "killanimscript" );
	self traverseMode( "noclip" );

	// orient to the Negotiation start node
	startnode = self getnegotiationstartnode();
	assert( isdefined( startnode ) );
	self OrientMode( "face angle", startnode.angles[ 1 ] );

	self thread teleportThreadEx( height - 40.0, 0.2, frames );

	self clearanim( %root, 0.25 );
	self setflaggedanimrestart( "traverseAnim", anim.dogTraverseAnims[ "jump_up_40" ], 1, 0.2, 1 );
	self animscripts\shared::DoNoteTracks( "traverseAnim" );

	self clearanim( anim.dogTraverseAnims[ "jump_up_40" ], 0 );	// start run immediately
	self traverseMode( "gravity" );
	self.traverseComplete = true;
}

// Duped above dog_wall_and_window_hop() function to allow dogs to
// use traversals that do not have a script_origin ent targetted
// from their first node. This ent is used to set the anim offset height
// for the traversal in _load::traverseThink(). In this function assume the
// z value of the first node if the traverse_height field does not exist.
dog_long_jump( traverseName, height )
{
	self endon( "killanimscript" );
	self traverseMode( "nogravity" );
	self traverseMode( "noclip" );

	// orient to the Negotiation start node
	startnode = self getnegotiationstartnode();
	assert( isdefined( startnode ) );
	self OrientMode( "face angle", startnode.angles[ 1 ] );

	// If this traverse node doesn't have a traverse_height
	// use the z height of the node, not perfect but works -JC
	if ( !IsDefined( startnode.traverse_height ) )
		startnode.traverse_height = startnode.origin[ 2 ];
	
	realHeight = startnode.traverse_height - startnode.origin[ 2 ];
	self thread teleportThread( realHeight - height );

	self clearanim( %root, 0.2 );
	self setflaggedanimrestart( "dog_traverse", anim.dogTraverseAnims[ traverseName ], 1, 0.2, 1 );

	self animscripts\shared::DoNoteTracks( "dog_traverse" );

	self.traverseComplete = true;
}
