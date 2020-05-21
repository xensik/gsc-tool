init()
{
	// level.destructableFX = loadfx("breakables/exp_wall_cinderblock_96");

	ents = getentarray("destructable", "targetname");
	
	if (getdvar("scr_destructables") == "0")
	{
		for (i = 0; i < ents.size; i++)
			ents[i] delete();
	}
	else
	{
		for (i = 0; i < ents.size; i++)
		{
			ents[i] thread destructable_think();
		}
	}
	
	glassarray = getentarray( "glass", "targetname" );
	if ( glassarray.size )
	{
		level._glass_info = [];

		level._glass_info[ "glass_large" ][ "breakfx" ] = loadfx( "props/car_glass_large" );
		level._glass_info[ "glass_large" ][ "breaksnd" ] = "veh_glass_break_large";

		level._glass_info[ "glass_med" ][ "breakfx" ] = loadfx( "props/car_glass_med" );
		level._glass_info[ "glass_med" ][ "breaksnd" ] = "veh_glass_break_small";

		level._glass_info[ "glass_small" ][ "breakfx" ] = loadfx( "props/car_glass_headlight" );
		level._glass_info[ "glass_small" ][ "breaksnd" ] = "veh_glass_break_small";
	}	
	for( x = 0; x < glassarray.size; x++ )
	{
		glassarray[x] thread glass_logic();
	}
}

destructable_think()
{
	accumulate = 40;
	threshold = 0;

	if (isdefined(self.script_accumulate))
		accumulate = self.script_accumulate;
	if (isdefined(self.script_threshold))
		threshold = self.script_threshold;
	
	if (isdefined(self.script_destructable_area)) {
		areas = strtok(self.script_destructable_area, " ");
		for (i = 0; i < areas.size; i++)
			self blockArea(areas[i]);
	}
	
	if ( isdefined( self.script_fxid ) )
		self.fx = loadfx( self.script_fxid );
	
	dmg = 0;

	self setcandamage(true);
	while(1)
	{
		self waittill("damage", amount, other);
		if (amount >= threshold)
		{
			dmg += amount;
			if (dmg >= accumulate)
			{
				self thread destructable_destruct();
				return;
			}
		}
	}
}

destructable_destruct()
{
	ent = self;
	if (isdefined(self.script_destructable_area)) {
		areas = strtok(self.script_destructable_area, " ");
		for (i = 0; i < areas.size; i++)
			self unblockArea(areas[i]);
	}
	if ( isdefined( ent.fx ) )
		playfx( ent.fx, ent.origin + (0,0,6) );
	ent delete();
}

blockArea(area)
{
	spawns = getentarray("mp_tdm_spawn", "classname");
	blockEntsInArea(spawns, area);
	spawns = getentarray("mp_dm_spawn", "classname");
	blockEntsInArea(spawns, area);
}
blockEntsInArea(ents, area)
{
	for (i = 0; i < ents.size; i++) {
		if (!isdefined(ents[i].script_destructable_area) || ents[i].script_destructable_area != area)
			continue;
		ents[i].blockedoff = true;
	}
}
unblockArea(area)
{
	spawns = getentarray("mp_tdm_spawn", "classname");
	unblockEntsInArea(spawns, area);
	spawns = getentarray("mp_dm_spawn", "classname");
	unblockEntsInArea(spawns, area);
}
unblockEntsInArea(ents, area)
{
	for (i = 0; i < ents.size; i++) {
		if (!isdefined(ents[i].script_destructable_area) || ents[i].script_destructable_area != area)
			continue;
		ents[i].blockedoff = false;
	}
}

glass_logic()
{	
	direction_vec 	 = undefined;
	glasshealth		 = 0;

// setup		
	assertex( isdefined( self.destructible_type ), "Destructible glass at origin( " + self.origin + " ) doesnt have a destructible_type" );
	switch( self.destructible_type )
	{
		case "glass_large":
			
			break;
		case "glass_med":
			
			break;
		case "glass_small":
			
			break;
		default:
			assertMsg( "Destructible glass 'destructible_type' key / value of '" + self.destructible_type + "' is not valid" );
			break;
	}
	
	if ( isdefined( self.script_health ) )
		glasshealth = self.script_health;
	else
		glasshealth = 100;
	
// break	
	self setcandamage( true );
	while ( glasshealth > 0 )
	{
		self waittill( "damage", damage, attacker, direction_vec, point, damageType );
		
		if ( !isdefined( direction_vec ) )
				direction_vec = ( 0, 0, 1 );		
		if ( !isdefined( damageType ) )
			damage = 100000;// scripted calls to break the glass
		else if ( damageType == "MOD_GRENADE_SPLASH" )
			damage = damage * 1.75;
		else if ( damageType == "MOD_IMPACT" )
			damage = 100000;
		
		glasshealth -= damage;		
	}
	
	prevdamage = glasshealth * - 1;
		
	self hide();
	self notsolid();
	
	glass_play_break_fx( self getorigin(), self.destructible_type, direction_vec );
	
	self delete();
}

glass_play_break_fx( origin, info, direction_vec )
{

	thread play_break_sound( level._glass_info[ info ][ "breaksnd" ] );
	playfx( level._glass_info[ info ][ "breakfx" ], origin, direction_vec );
}

play_break_sound( alias )
{

	org = Spawn( "script_origin", ( 0, 0, 1 ) );
	org Hide();
	org.origin = self.origin;
	org.angles = self.angles;
	org LinkTo( self );

	org PlaySound( alias );
	if( IsAudioDisabled() )
	{
		org waittill_notify_or_timeout_hack( "sounddone", 2.0 );
	}
	else
	{
		org waittill( "sounddone" );
	}
	org Delete();
}

//Just in case sounds are disabled
waittill_notify_or_timeout_hack( msg, timer )
{
	self endon( msg );
	wait( timer );
}
