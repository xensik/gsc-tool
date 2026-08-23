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

	self.primaryTurretAnim = %standSAWgunner_aim;
	self.additiveTurretIdle = %saw_gunner_idle;
	self.additiveTurretFire = %saw_gunner_firing_add;

	thread animscripts\saw\common::main( turret );
}

//=====================================
#using_animtree( "mg42" );

turretInit( owner )
{
	self UseAnimTree( #animtree );

	self.additiveTurretIdle = %saw_gunner_idle_mg;
	self.additiveTurretFire = %saw_gunner_firing_mg_add;

	self endon( "death" );
	owner waittill( "killanimscript" );// code

	self stopUseAnimTree();
}

