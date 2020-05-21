#include maps\mp\_utility;
#include common_scripts\utility;

/*
	Team Ammo Refill Killstreak: when the player uses this, everyone on their team gets an ammo refill
*/

init()
{
	level.killStreakFuncs[ "team_ammo_refill" ] 	= ::tryUseTeamAmmoRefill;
}

tryUseTeamAmmoRefill( lifeId )
{
	result = self giveTeamAmmoRefill();
	if ( result )
		self maps\mp\_matchdata::logKillstreakEvent( "team_ammo_refill", self.origin );

	return ( result );
}

giveTeamAmmoRefill()
{
	if( level.teambased )
	{
		foreach( teammate in level.players )
		{
			if( teammate.team == self.team )
			{
				teammate refillAmmo( true );
			}
		}
	}	
	else
	{
		self refillAmmo( true );
	}

	level thread teamPlayerCardSplash( "used_team_ammo_refill", self );

	return true;
}

refillAmmo( refillEquipment )
{
	weaponList = self GetWeaponsListAll();

	if ( refillEquipment )
	{
		if ( self _hasPerk( "specialty_tacticalinsertion" ) && self getAmmoCount( "flare_mp" ) < 1 )
			self givePerk( "specialty_tacticalinsertion", false );	

		if ( self _hasPerk( "specialty_scrambler" ) && self getAmmoCount( "scrambler_mp" ) < 1 )
			self givePerk( "specialty_scrambler", false );	

		if ( self _hasPerk( "specialty_portable_radar" ) && self getAmmoCount( "portable_radar_mp" ) < 1 )
			self givePerk( "specialty_portable_radar", false );	
	}

	foreach ( weaponName in weaponList )
	{
		if ( isSubStr( weaponName, "grenade" ) || ( GetSubStr( weaponName, 0, 2 ) == "gl" ) )
		{
			if ( !refillEquipment || self getAmmoCount( weaponName ) >= 1 )
				continue;
		} 

		self giveMaxAmmo( weaponName );
	}

	self playLocalSound( "ammo_crate_use" );

}
