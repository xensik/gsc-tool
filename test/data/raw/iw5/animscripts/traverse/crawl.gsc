// crawl.gsc
// crawl under a low area

#using_animtree( "generic_human" );

main()
{
	
	animscripts\SetPoseMovement::BeginProneRun();
	animscripts\utility::UpdateAnimPose();

	self endon( "killanimscript" );
	self traverseMode( "noclip" );

    // orient to the Negotiation start node
    startnode = self getnegotiationstartnode();
    assert( isdefined( startnode ) );
    self OrientMode( "face angle", startnode.angles[ 1 ] );

	self setFlaggedAnimKnoballRestart( "crawlanim", %prone_crawl, %body, 1, .1, 1 );

	self animscripts\shared::DoNoteTracks( "crawlanim" );
	
	self.a.movement = "run";
	self.a.pose = "crouch";
}

