init()
{
	level.hostname = getdvar("sv_hostname");
	if(level.hostname == "")
		level.hostname = "CoDHost";
	setdvar("sv_hostname", level.hostname);

	level.allowvote = getdvarint("g_allowvote", 1);
	SetDvar("g_allowvote", level.allowvote);
	makedvarserverinfo("ui_allowvote", level.allowvote);

	level.friendlyfire = maps\mp\gametypes\_tweakables::getTweakableValue( "team", "fftype" );
	makedvarserverinfo("ui_friendlyfire", level.friendlyfire);

	constrainGameType(getdvar("g_gametype"));

	for(;;)
	{
		updateServerSettings();
		wait 5;
	}
}

updateServerSettings()
{
	sv_hostname = getdvar("sv_hostname");
	if(level.hostname != sv_hostname)
	{
		level.hostname = sv_hostname;
	}

	g_allowvote = getdvarint("g_allowvote", 1);
	if(level.allowvote != g_allowvote)
	{
		level.allowvote = g_allowvote;
		setdvar("ui_allowvote", level.allowvote);
	}
	
	scr_friendlyfire = maps\mp\gametypes\_tweakables::getTweakableValue( "team", "fftype" );
	if(level.friendlyfire != scr_friendlyfire)
	{
		level.friendlyfire = scr_friendlyfire;
		setdvar("ui_friendlyfire", level.friendlyfire);
	}
}

constrainGameType(gametype)
{
	entities = getentarray();
	for(i = 0; i < entities.size; i++)
	{
		entity = entities[i];
		
		if(gametype == "dm")
		{
			if(isdefined(entity.script_gametype_dm) && entity.script_gametype_dm != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
		else if(gametype == "tdm")
		{
			if(isdefined(entity.script_gametype_tdm) && entity.script_gametype_tdm != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
		else if(gametype == "ctf")
		{
			if(isdefined(entity.script_gametype_ctf) && entity.script_gametype_ctf != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
		else if(gametype == "hq")
		{
			if(isdefined(entity.script_gametype_hq) && entity.script_gametype_hq != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
		else if(gametype == "sd")
		{
			if(isdefined(entity.script_gametype_sd) && entity.script_gametype_sd != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
		else if(gametype == "koth")
		{
			if(isdefined(entity.script_gametype_koth) && entity.script_gametype_koth != "1")
			{
				//iprintln("DELETED(GameType): ", entity.classname);
				entity delete();
			}
		}
	}
}