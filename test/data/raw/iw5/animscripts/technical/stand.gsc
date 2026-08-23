#using_animtree( "generic_human" );

main()
{
	// do not do code prone in this script
	self.desired_anim_pose = "stand";
	animscripts\utility::UpdateAnimPose();

	// It'd be nice if I had an animation to get to stand without moving...
	self.a.movement = "stop";

	turret = self getTurret();
	turret thread turretInit( self );

	self.primaryTurretAnim = %technicalGunner_aim;
	self.additiveTurretIdle = %technical_turret_driveidle;
	self.additiveTurretFire = %technical_turret_firing;

	self.painFunction = ::technical_pain;
	self.deathAnim = %technical_turret_death;
	
	thread animscripts\saw\common::main( turret );
}

technical_pain()
{
	self setFlaggedAnimKnobAllRestart( "painanim", %technical_turret_pain, %body, 1, .1, 1 );
	self animscripts\shared::DoNoteTracks( "painanim" );
}

//=====================================
#using_animtree( "mg42" );

turretInit( owner )
{
	self.leftArc = 180;
	self.rightArc = 180;
	
	self UseAnimTree( #animtree );

	self.additiveTurretIdle = %saw_gunner_idle_mg;
	self.additiveTurretFire = %saw_gunner_firing_mg_add;

	self endon( "death" );
	owner waittill( "killanimscript" );// code

	self stopUseAnimTree();
}
