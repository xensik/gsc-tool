#include maps\_utility;
#include common_scripts\utility;

#using_animtree( "generic_human" );

// self = the guy using the turret
main()
{
	turret = self getTurret();
	
	self.desired_anim_pose = "stand";
	animscripts\utility::UpdateAnimPose();

	// .primaryTurretAnim is used by code so don't change this variable name
	self.primaryTurretAnim			= %humveeGunner_aim;
	
	self.additiveTurretRotateLeft	= %humvee_turret_aim_6_add;
	self.additiveTurretRotateRight	= %humvee_turret_aim_4_add;
	self.additiveRotateRoot			= %additive_humveeGunner_aim_leftright;

	self.additiveTurretIdle			= %humvee_turret_idle;
	self.additiveTurretDriveIdle	= %humvee_turret_driveidle;
	self.additiveTurretFire			= %humvee_turret_fire;
	self.additiveUsegunRoot			= %additive_humveeGunner_usegun;
	
	self.turretDeathAnimRoot		= %humveeGunner_death;
	self.turretDeathAnim			= %humvee_turret_death;
	
	self.turretPainAnims[ 0 ]		= %humvee_turret_painA;
	self.turretPainAnims[ 1 ]		= %humvee_turret_painB;
	
	self.turretFlashbangedAnim		= %humvee_turret_flinchA;
	
	self.turretReloadAnim			= %humvee_turret_rechamber;
	
	self.turretSpecialAnimsRoot		= %humveeGunner;
	arr = [];
	arr[ "humvee_turret_bounce" ]				= %humvee_turret_bounce;
	arr[ "humvee_turret_idle_lookback" ]		= %humvee_turret_idle_lookback;
	arr[ "humvee_turret_idle_lookbackB" ]		= %humvee_turret_idle_lookbackB;
	arr[ "humvee_turret_idle_signal_forward" ]	= %humvee_turret_idle_signal_forward;
	arr[ "humvee_turret_idle_signal_side" ]		= %humvee_turret_idle_signal_side;
	arr[ "humvee_turret_radio" ]				= %humvee_turret_radio;
	arr[ "humvee_turret_flinchA" ]				= %humvee_turret_flinchA;
	arr[ "humvee_turret_flinchB" ]				= %humvee_turret_flinchB;
	arr[ "humvee_turret_rechamber" ]			= %humvee_turret_rechamber;
	self.turretSpecialAnims = arr;
	
	turret setup_turret_anims();

	self thread animscripts\hummer_turret\minigun_code::main( turret );
}

#using_animtree( "vehicles" );
setup_turret_anims()
{
	self UseAnimTree( #animtree );
	self.passenger2turret_anime = %humvee_passenger_2_turret_minigun;
	self.turret2passenger_anime = %humvee_turret_2_passenger_minigun;
}
