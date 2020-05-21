init()
{
	game["menu_quickcommands"] = "quickcommands";
	game["menu_quickstatements"] = "quickstatements";
	game["menu_quickresponses"] = "quickresponses";

	precacheMenu(game["menu_quickcommands"]);
	precacheMenu(game["menu_quickstatements"]);
	precacheMenu(game["menu_quickresponses"]);
	precacheHeadIcon("talkingicon");

	precacheString( &"QUICKMESSAGE_FOLLOW_ME" );
	precacheString( &"QUICKMESSAGE_MOVE_IN" );
	precacheString( &"QUICKMESSAGE_FALL_BACK" );
	precacheString( &"QUICKMESSAGE_SUPPRESSING_FIRE" );
	precacheString( &"QUICKMESSAGE_ATTACK_LEFT_FLANK" );
	precacheString( &"QUICKMESSAGE_ATTACK_RIGHT_FLANK" );
	precacheString( &"QUICKMESSAGE_HOLD_THIS_POSITION" );
	precacheString( &"QUICKMESSAGE_REGROUP" );
	precacheString( &"QUICKMESSAGE_ENEMY_SPOTTED" );
	precacheString( &"QUICKMESSAGE_ENEMIES_SPOTTED" );
	precacheString( &"QUICKMESSAGE_IM_IN_POSITION" );
	precacheString( &"QUICKMESSAGE_AREA_SECURE" );
	precacheString( &"QUICKMESSAGE_GRENADE" );
	precacheString( &"QUICKMESSAGE_SNIPER" );
	precacheString( &"QUICKMESSAGE_NEED_REINFORCEMENTS" );
	precacheString( &"QUICKMESSAGE_HOLD_YOUR_FIRE" );
	precacheString( &"QUICKMESSAGE_YES_SIR" );
	precacheString( &"QUICKMESSAGE_NO_SIR" );
	precacheString( &"QUICKMESSAGE_IM_ON_MY_WAY" );
	precacheString( &"QUICKMESSAGE_SORRY" );
	precacheString( &"QUICKMESSAGE_GREAT_SHOT" );
	precacheString( &"QUICKMESSAGE_TOOK_LONG_ENOUGH" );
	precacheString( &"QUICKMESSAGE_ARE_YOU_CRAZY" );	
	precacheString( &"QUICKMESSAGE_WATCH_SIX" );	
	precacheString( &"QUICKMESSAGE_COME_ON" );	
}

quickcommands(response)
{
	self endon ( "disconnect" );
	
	if(!isdefined(self.pers["team"]) || self.pers["team"] == "spectator" || isdefined(self.spamdelay))
		return;

	self.spamdelay = true;
	
	switch(response)		
	{
		case "1":
			soundalias = "mp_cmd_followme";
			saytext = &"QUICKMESSAGE_FOLLOW_ME";
			//saytext = "Follow Me!";
			break;

		case "2":
			soundalias = "mp_cmd_movein";
			saytext = &"QUICKMESSAGE_MOVE_IN";
			//saytext = "Move in!";
			break;

		case "3":
			soundalias = "mp_cmd_fallback";
			saytext = &"QUICKMESSAGE_FALL_BACK";
			//saytext = "Fall back!";
			break;

		case "4":
			soundalias = "mp_cmd_suppressfire";
			saytext = &"QUICKMESSAGE_SUPPRESSING_FIRE";
			//saytext = "Suppressing fire!";
			break;

		case "5":
			soundalias = "mp_cmd_attackleftflank";
			saytext = &"QUICKMESSAGE_ATTACK_LEFT_FLANK";
			//saytext = "Attack left flank!";
			break;

		case "6":
			soundalias = "mp_cmd_attackrightflank";
			saytext = &"QUICKMESSAGE_ATTACK_RIGHT_FLANK";
			//saytext = "Attack right flank!";
			break;

		case "7":
			soundalias = "mp_cmd_holdposition";
			saytext = &"QUICKMESSAGE_HOLD_THIS_POSITION";
			//saytext = "Hold this position!";
			break;

		default:
			assert(response == "8");
			soundalias = "mp_cmd_regroup";
			saytext = &"QUICKMESSAGE_REGROUP";
			//saytext = "Regroup!";
			break;
	}

	self saveHeadIcon();
	self doQuickMessage(soundalias, saytext);

	wait 2;
	self.spamdelay = undefined;
	self restoreHeadIcon();	
}

quickstatements(response)
{
	if(!isdefined(self.pers["team"]) || self.pers["team"] == "spectator" || isdefined(self.spamdelay))
		return;

	self.spamdelay = true;
	
	switch(response)		
	{
		case "1":
			soundalias = "mp_stm_enemyspotted";
			saytext = &"QUICKMESSAGE_ENEMY_SPOTTED";
			//saytext = "Enemy spotted!";
			break;

		case "2":
			soundalias = "mp_stm_enemiesspotted";
			saytext = &"QUICKMESSAGE_ENEMIES_SPOTTED";
			//saytext = "Enemy down!";
			break;

		case "3":
			soundalias = "mp_stm_iminposition";
			saytext = &"QUICKMESSAGE_IM_IN_POSITION";
			//saytext = "I'm in position.";
			break;

		case "4":
			soundalias = "mp_stm_areasecure";
			saytext = &"QUICKMESSAGE_AREA_SECURE";
			//saytext = "Area secure!";
			break;

		case "5":
			soundalias = "mp_stm_watchsix";
			saytext = &"QUICKMESSAGE_WATCH_SIX";
			//saytext = "Grenade!";
			break;

		case "6":
			soundalias = "mp_stm_sniper";
			saytext = &"QUICKMESSAGE_SNIPER";
			//saytext = "Sniper!";
			break;

		default:
			assert(response == "7");
			soundalias = "mp_stm_needreinforcements";
			saytext = &"QUICKMESSAGE_NEED_REINFORCEMENTS";
			//saytext = "Need reinforcements!";
			break;
	}

	self saveHeadIcon();
	self doQuickMessage(soundalias, saytext);

	wait 2;
	self.spamdelay = undefined;
	self restoreHeadIcon();
}

quickresponses(response)
{
	if(!isdefined(self.pers["team"]) || self.pers["team"] == "spectator" || isdefined(self.spamdelay))
		return;

	self.spamdelay = true;

	switch(response)		
	{
		case "1":
			soundalias = "mp_rsp_yessir";
			saytext = &"QUICKMESSAGE_YES_SIR";
			//saytext = "Yes Sir!";
			break;

		case "2":
			soundalias = "mp_rsp_nosir";
			saytext = &"QUICKMESSAGE_NO_SIR";
			//saytext = "No Sir!";
			break;

		case "3":
			soundalias = "mp_rsp_onmyway";
			saytext = &"QUICKMESSAGE_IM_ON_MY_WAY";
			//saytext = "On my way.";
			break;

		case "4":
			soundalias = "mp_rsp_sorry";
			saytext = &"QUICKMESSAGE_SORRY";
			//saytext = "Sorry.";
			break;

		case "5":
			soundalias = "mp_rsp_greatshot";
			saytext = &"QUICKMESSAGE_GREAT_SHOT";
			//saytext = "Great shot!";
			break;

		default:
			assert(response == "6");
			soundalias = "mp_rsp_comeon";
			saytext = &"QUICKMESSAGE_COME_ON";
			//saytext = "Took long enough!";
			break;
	}

	self saveHeadIcon();
	self doQuickMessage(soundalias, saytext);

	wait 2;
	self.spamdelay = undefined;
	self restoreHeadIcon();
}

doQuickMessage( soundalias, saytext )
{
	if(self.sessionstate != "playing")
		return;

	prefix = maps\mp\gametypes\_teams::getTeamVoicePrefix( self.team );

	if(isdefined(level.QuickMessageToAll) && level.QuickMessageToAll)
	{
		self.headiconteam = "none";
		self.headicon = "talkingicon";

		self playSound( prefix+soundalias );
		self sayAll(saytext);
	}
	else
	{
		if(self.sessionteam == "allies")
			self.headiconteam = "allies";
		else if(self.sessionteam == "axis")
			self.headiconteam = "axis";
		
		self.headicon = "talkingicon";

		self playSound( prefix+soundalias );
		self sayTeam( saytext );
		self pingPlayer();
	}
}

saveHeadIcon()
{
	if(isdefined(self.headicon))
		self.oldheadicon = self.headicon;

	if(isdefined(self.headiconteam))
		self.oldheadiconteam = self.headiconteam;
}

restoreHeadIcon()
{
	if(isdefined(self.oldheadicon))
		self.headicon = self.oldheadicon;

	if(isdefined(self.oldheadiconteam))
		self.headiconteam = self.oldheadiconteam;
}