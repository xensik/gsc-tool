#include maps\mp\_utility;
#include maps\mp\gametypes\_hud_util;
#include common_scripts\utility;

init()
{
	level.killStreakFuncs["auto_shotgun"] = ::tryUseAutoShotgun;	
	level.killstreakSetupFuncs["auto_shotgun"] = ::shotgunSetup;

	level.killStreakFuncs["thumper"] = ::tryUseThumper;	
	level.killstreakSetupFuncs["thumper"] = ::thumperSetup;
	
	thread onPlayerConnect();
}


shotgunSetup()
{
	self giveMaxAmmo( "aa12_mp" );
	
	self thread saveWeaponAmmoOnDeath( "aa12_mp" );
}


tryUseAutoShotgun( lifeId )
{
	self thread removeWeaponOnOutOfAmmo( "aa12_mp" );
	return true;
}


thumperSetup()
{
	self giveMaxAmmo( "m79_mp" );
	
	self thread saveWeaponAmmoOnDeath( "m79_mp" );
}


tryUseThumper()
{
	self thread removeWeaponOnOutOfAmmo( "m79_mp" );
	return true;
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );
		
		player thread onPlayerSpawned();
	}
}


onPlayerSpawned()
{
	self endon( "disconnect" );

	for(;;)
	{
		self waittill( "spawned_player" );
		
		if ( !isDefined( self.pers["ksWeapon_clip_ammo"] ) || !isDefined( self.pers["ksWeapon_name"] ) )
			continue;

		weaponName = self.pers["ksWeapon_name"];

		if ( isDefined( self.pers["killstreak"] ) && maps\mp\killstreaks\_killstreaks::getKillstreakWeapon( self.pers["killstreak"] ) != weaponName )
		{
			self.pers["ksWeapon_name"] = undefined;
			self.pers["ksWeapon_clip_ammo"] = undefined;
			self.pers["ksWeapon_stock_ammo"] = undefined;
			continue; 
		}
		
		self maps\mp\killstreaks\_killstreaks::giveKillstreakWeapon( weaponName );

		self setWeaponAmmoStock( weaponName, self.pers["ksWeapon_stock_ammo"] );
		self setWeaponAmmoClip( weaponName, self.pers["ksWeapon_clip_ammo"] );

		self thread removeWeaponOnOutOfAmmo( weaponName );
		self thread saveWeaponAmmoOnDeath( weaponName );
	}
}

saveWeaponAmmoOnDeath( weaponName )
{
	self endon ( "disconnect" );
	self endon ( "got_killstreak" );

	self notify( "saveWeaponAmmoOnDeath" );
	self endon( "saveWeaponAmmoOnDeath" );

	self.pers["ksWeapon_name"] = undefined;
	self.pers["ksWeapon_clip_ammo"] = undefined;
	self.pers["ksWeapon_stock_ammo"] = undefined;
	
	self waittill ( "death" );
	
	if ( !self hasWeapon( weaponName ) )
		return;
		
	self.pers["ksWeapon_name"] = weaponName;
	self.pers["ksWeapon_clip_ammo"] = self getWeaponAmmoClip( weaponName );
	self.pers["ksWeapon_stock_ammo"] = self getWeaponAmmoStock( weaponName );
}


removeWeaponOnOutOfAmmo( weaponName )
{
	self endon ( "disconnect" );
	self endon ( "death" );	
	
	self notify( weaponName + "_ammo_monitor" );
	self endon( weaponName + "_ammo_monitor" );
	
	while( 1 )
	{
		self waittill ( "end_firing" );
		
		if ( self getCurrentWeapon() != weaponName )
			continue;

		total_ammo = self getWeaponAmmoClip( weaponName ) + self getWeaponAmmoStock( weaponName );
		if ( total_ammo )
			continue;
		
		self takeWeapon( weaponName );		
		return;
	}
}