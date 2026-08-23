#include common_scripts\utility;

#using_animtree( "dog" );

main()
{
	self endon( "killanimscript" );
	if ( isdefined( self.a.nodeath ) )
	{
		assertex( self.a.nodeath, "Nodeath needs to be set to true or undefined." );

 		wait 1.1;	// wait for point in animation where dog rolls off
 		// drop to floor, fixes bug where dog is floating when attacking on a slope
 		floorPos = self GetDropToFloorPosition();
 		if ( isdefined( floorPos ) )
 		{
			tag_origin = spawn_tag_origin();
			tag_origin.origin = self.origin;
			tag_origin.angles = self.angles;
			self LinkTo( tag_origin );

			tag_origin MoveTo( floorPos, 0.5 );
 			wait 0.5;
			
			self unlink();
			tag_origin Delete();
 		}
 		else
 		{
	 		wait 0.5;
 		}
		return;
	}

	self unlink();

	if ( isdefined( self.enemy ) && isdefined( self.enemy.syncedMeleeTarget ) && self.enemy.syncedMeleeTarget == self )
	{
		self.enemy.syncedMeleeTarget = undefined;
	}

	self clearanim( %root, 0.2 );
	self setflaggedanimrestart( "dog_anim", %german_shepherd_death_front, 1, 0.2, 1 );
	self animscripts\shared::DoNoteTracks( "dog_anim" );
}
