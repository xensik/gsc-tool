#include maps\_utility;
#include common_scripts\utility;

#using_animtree( "generic_human" );

// self = the guy using the turret
main()
{
	turret = self getTurret();
	
	death_anim = get_death_anim();
	
	self.desired_anim_pose = "stand";
	animscripts\utility::UpdateAnimPose();

	// .primaryTurretAnim is used by code so don't change this variable name
	self.primaryTurretAnim			= %gazGunner_aim;  //%humveeGunner_aim;
	
	self.additiveTurretRotateLeft	= %gaz_turret_aim_6_add; //%humvee_turret_aim_6_add;
	self.additiveTurretRotateRight	= %gaz_turret_aim_4_add; //%humvee_turret_aim_4_add;
	self.additiveRotateRoot			= %additive_gazGunner_aim_leftright ; //%additive_humveeGunner_aim_leftright;

	self.additiveTurretIdle			= %gaz_turret_idle; //%humvee_turret_idle;
	self.additiveTurretDriveIdle	= %gaz_turret_idle; //%humvee_turret_driveidle;
	self.additiveTurretFire			= %gaz_turret_fire; //%humvee_turret_fire;
	self.additiveUsegunRoot			= %additive_gazGunner_usegun ; //%additive_humveeGunner_usegun;
	
	self.turretDeathAnimRoot		= %gazGunner_death; //%humveeGunner_death;
	self.turretDeathAnim			= death_anim; //%humvee_turret_death;
	
	self.turretPainAnims[ 0 ]		= %gaz_turret_paina; //%humvee_turret_painA;
	self.turretPainAnims[ 1 ]		= %gaz_turret_painb; //%humvee_turret_painB;
	
	self.turretFlashbangedAnim		= %gaz_turret_flincha; //%humvee_turret_flinchA;
	
	// stealing a hummer reload seems to screw it up, use pain instead
	self.turretReloadAnim			= %gaz_turret_paina; ////%humvee_turret_rechamber;
	
	self.turretSpecialAnimsRoot		= %gazGunner; //%humveeGunner;
	arr = [];
	//arr[ "humvee_turret_bounce" ]				= %humvee_turret_bounce;
	//arr[ "humvee_turret_idle_lookback" ]		= %humvee_turret_idle_lookback;
	//arr[ "humvee_turret_idle_lookbackB" ]		= %humvee_turret_idle_lookbackB;
	//arr[ "humvee_turret_idle_signal_forward" ]	= %humvee_turret_idle_signal_forward;
	//arr[ "humvee_turret_idle_signal_side" ]		= %humvee_turret_idle_signal_side;
	//arr[ "humvee_turret_radio" ]				= %humvee_turret_radio;
	arr[ "humvee_turret_flinchA" ]				= %gaz_turret_flincha; //%humvee_turret_flinchA;
	arr[ "humvee_turret_flinchB" ]				= %gaz_turret_flinchb; //%humvee_turret_flinchB;
	//arr[ "humvee_turret_rechamber" ]			= %humvee_turret_rechamber;
	self.turretSpecialAnims = arr;
	
	turret setup_turret_anims();

	self thread animscripts\hummer_turret\minigun_code::main( turret );
}

get_death_anim()
{
	death_anim = %gaz_turret_death;

	if ( IsDefined( self.ridingvehicle ) )
	{
		if ( IsDefined( level.dshk_death_anim ) )
		{
			death_anim = self [[ level.dshk_death_anim ]]();
		}
	}

	return death_anim;
}

#using_animtree( "vehicles" );
setup_turret_anims()
{
	self UseAnimTree( #animtree );
	self.passenger2turret_anime = %humvee_passenger_2_turret_minigun;
	self.turret2passenger_anime = %humvee_turret_2_passenger_minigun;
}
