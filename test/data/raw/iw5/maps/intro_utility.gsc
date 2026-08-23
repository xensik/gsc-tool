#include common_scripts\utility;
#include maps\_hud_util;
#include maps\_utility;
#include maps\_anim;

/////////////////
// tutorial UI //
/////////////////

registerActions()
{
	level.actionBinds = [];
	
	registerActionBinding( "sprint",			"+breath_sprint",		&"INTRO_HINT_SPRINT_BREATH" );
	registerActionBinding( "sprint",			"+sprint",				&"INTRO_HINT_SPRINT" );
	
	registerActionBinding( "sprint_pc",			"+breath_sprint",		&"INTRO_HINT_SPRINT_BREATH_PC" );
	registerActionBinding( "sprint_pc",			"+sprint",				&"INTRO_HINT_SPRINT_PC" );

	registerActionBinding( "primary",			"weapnext",				&"INTRO_HINT_PRIMARY_SWAP" );
	registerActionBinding( "toggle_view",		"weapnext",				&"INTRO_HINT_TOGGLE_VIEW" );
	
	registerActionBinding( "ugv_grenade",		"+frag",				&"INTRO_HINT_UGV_GRENADE" );
	
	registerActionBinding( "ugv_zoom_360",		"+speed_throw",			&"INTRO_HINT_UGV_ZOOM_THROW_360" );
	registerActionBinding( "ugv_zoom_360",		"+speed",				&"INTRO_HINT_UGV_ZOOM_360" );
	
	registerActionBinding( "ugv_zoom",			"+speed_throw",			&"INTRO_HINT_UGV_ZOOM_THROW" );
	registerActionBinding( "ugv_zoom",			"+speed",				&"INTRO_HINT_UGV_ZOOM" );
	registerActionBinding( "ugv_zoom",			"+toggleads_throw",		&"INTRO_HINT_UGV_ZOOM_TOGGLE_THROW" );
	registerActionBinding( "ugv_zoom",			"toggleads",			&"INTRO_HINT_UGV_ZOOM_TOGGLE" );

	initKeys();
	updateKeysForBindings();
}

registerActionBinding( action, binding, hint )
{
	if ( !isDefined( level.actionBinds[action] ) )
		level.actionBinds[action] = [];

	actionBind = spawnStruct();
	actionBind.binding = binding;
	actionBind.hint = hint;

	actionBind.keyText = undefined;
	actionBind.hintText = undefined;

	precacheString( hint );

	level.actionBinds[action][level.actionBinds[action].size] = actionBind;
}

initKeys()
{
	level.kbKeys = "1234567890-=qwertyuiop[]asdfghjkl;'zxcvbnm,./";

	level.specialKeys = [];

	level.specialKeys[level.specialKeys.size] = "TAB";
	level.specialKeys[level.specialKeys.size] = "ENTER";
	level.specialKeys[level.specialKeys.size] = "ESCAPE";
	level.specialKeys[level.specialKeys.size] = "SPACE";
	level.specialKeys[level.specialKeys.size] = "BACKSPACE";
	level.specialKeys[level.specialKeys.size] = "UPARROW";
	level.specialKeys[level.specialKeys.size] = "DOWNARROW";
	level.specialKeys[level.specialKeys.size] = "LEFTARROW";
	level.specialKeys[level.specialKeys.size] = "RIGHTARROW";
	level.specialKeys[level.specialKeys.size] = "ALT";
	level.specialKeys[level.specialKeys.size] = "CTRL";
	level.specialKeys[level.specialKeys.size] = "SHIFT";
	level.specialKeys[level.specialKeys.size] = "CAPSLOCK";
	level.specialKeys[level.specialKeys.size] = "F1";
	level.specialKeys[level.specialKeys.size] = "F2";
	level.specialKeys[level.specialKeys.size] = "F3";
	level.specialKeys[level.specialKeys.size] = "F4";
	level.specialKeys[level.specialKeys.size] = "F5";
	level.specialKeys[level.specialKeys.size] = "F6";
	level.specialKeys[level.specialKeys.size] = "F7";
	level.specialKeys[level.specialKeys.size] = "F8";
	level.specialKeys[level.specialKeys.size] = "F9";
	level.specialKeys[level.specialKeys.size] = "F10";
	level.specialKeys[level.specialKeys.size] = "F11";
	level.specialKeys[level.specialKeys.size] = "F12";
	level.specialKeys[level.specialKeys.size] = "INS";
	level.specialKeys[level.specialKeys.size] = "DEL";
	level.specialKeys[level.specialKeys.size] = "PGDN";
	level.specialKeys[level.specialKeys.size] = "PGUP";
	level.specialKeys[level.specialKeys.size] = "HOME";
	level.specialKeys[level.specialKeys.size] = "END";
	level.specialKeys[level.specialKeys.size] = "MOUSE1";
	level.specialKeys[level.specialKeys.size] = "MOUSE2";
	level.specialKeys[level.specialKeys.size] = "MOUSE3";
	level.specialKeys[level.specialKeys.size] = "MOUSE4";
	level.specialKeys[level.specialKeys.size] = "MOUSE5";
	level.specialKeys[level.specialKeys.size] = "MWHEELUP";
	level.specialKeys[level.specialKeys.size] = "MWHEELDOWN";
	level.specialKeys[level.specialKeys.size] = "AUX1";
	level.specialKeys[level.specialKeys.size] = "AUX2";
	level.specialKeys[level.specialKeys.size] = "AUX3";
	level.specialKeys[level.specialKeys.size] = "AUX4";
	level.specialKeys[level.specialKeys.size] = "AUX5";
	level.specialKeys[level.specialKeys.size] = "AUX6";
	level.specialKeys[level.specialKeys.size] = "AUX7";
	level.specialKeys[level.specialKeys.size] = "AUX8";
	level.specialKeys[level.specialKeys.size] = "AUX9";
	level.specialKeys[level.specialKeys.size] = "AUX10";
	level.specialKeys[level.specialKeys.size] = "AUX11";
	level.specialKeys[level.specialKeys.size] = "AUX12";
	level.specialKeys[level.specialKeys.size] = "AUX13";
	level.specialKeys[level.specialKeys.size] = "AUX14";
	level.specialKeys[level.specialKeys.size] = "AUX15";
	level.specialKeys[level.specialKeys.size] = "AUX16";
	level.specialKeys[level.specialKeys.size] = "KP_HOME";
	level.specialKeys[level.specialKeys.size] = "KP_UPARROW";
	level.specialKeys[level.specialKeys.size] = "KP_PGUP";
	level.specialKeys[level.specialKeys.size] = "KP_LEFTARROW";
	level.specialKeys[level.specialKeys.size] = "KP_5";
	level.specialKeys[level.specialKeys.size] = "KP_RIGHTARROW";
	level.specialKeys[level.specialKeys.size] = "KP_END";
	level.specialKeys[level.specialKeys.size] = "KP_DOWNARROW";
	level.specialKeys[level.specialKeys.size] = "KP_PGDN";
	level.specialKeys[level.specialKeys.size] = "KP_ENTER";
	level.specialKeys[level.specialKeys.size] = "KP_INS";
	level.specialKeys[level.specialKeys.size] = "KP_DEL";
	level.specialKeys[level.specialKeys.size] = "KP_SLASH";
	level.specialKeys[level.specialKeys.size] = "KP_MINUS";
	level.specialKeys[level.specialKeys.size] = "KP_PLUS";
	level.specialKeys[level.specialKeys.size] = "KP_NUMLOCK";
	level.specialKeys[level.specialKeys.size] = "KP_STAR";
	level.specialKeys[level.specialKeys.size] = "KP_EQUALS";
	level.specialKeys[level.specialKeys.size] = "PAUSE";
	level.specialKeys[level.specialKeys.size] = "SEMICOLON";
	level.specialKeys[level.specialKeys.size] = "COMMAND";
	level.specialKeys[level.specialKeys.size] = "181";
	level.specialKeys[level.specialKeys.size] = "191";
	level.specialKeys[level.specialKeys.size] = "223";
	level.specialKeys[level.specialKeys.size] = "224";
	level.specialKeys[level.specialKeys.size] = "225";
	level.specialKeys[level.specialKeys.size] = "228";
	level.specialKeys[level.specialKeys.size] = "229";
	level.specialKeys[level.specialKeys.size] = "230";
	level.specialKeys[level.specialKeys.size] = "231";
	level.specialKeys[level.specialKeys.size] = "232";
	level.specialKeys[level.specialKeys.size] = "233";
	level.specialKeys[level.specialKeys.size] = "236";
	level.specialKeys[level.specialKeys.size] = "241";
	level.specialKeys[level.specialKeys.size] = "242";
	level.specialKeys[level.specialKeys.size] = "243";
	level.specialKeys[level.specialKeys.size] = "246";
	level.specialKeys[level.specialKeys.size] = "248";
	level.specialKeys[level.specialKeys.size] = "249";
	level.specialKeys[level.specialKeys.size] = "250";
	level.specialKeys[level.specialKeys.size] = "252";
}

updateKeysForBindings()
{
	if ( level.console )
	{
		setKeyForBinding( getCommandFromKey( "BUTTON_START" ), "BUTTON_START" );
		setKeyForBinding( getCommandFromKey( "BUTTON_A" ), "BUTTON_A" );
		setKeyForBinding( getCommandFromKey( "BUTTON_B" ), "BUTTON_B" );
		setKeyForBinding( getCommandFromKey( "BUTTON_X" ), "BUTTON_X" );
		setKeyForBinding( getCommandFromKey( "BUTTON_Y" ), "BUTTON_Y" );
		setKeyForBinding( getCommandFromKey( "BUTTON_LSTICK" ), "BUTTON_LSTICK" );
		setKeyForBinding( getCommandFromKey( "BUTTON_RSTICK" ), "BUTTON_RSTICK" );
		setKeyForBinding( getCommandFromKey( "BUTTON_LSHLDR" ), "BUTTON_LSHLDR" );
		setKeyForBinding( getCommandFromKey( "BUTTON_RSHLDR" ), "BUTTON_RSHLDR" );
		setKeyForBinding( getCommandFromKey( "BUTTON_LTRIG" ), "BUTTON_LTRIG" );
		setKeyForBinding( getCommandFromKey( "BUTTON_RTRIG" ), "BUTTON_RTRIG" );
	}
	else
	{
		//level.kbKeys = "1234567890-=QWERTYUIOP[]ASDFGHJKL;'ZXCVBNM,./";
		//level.specialKeys = [];

		for ( index = 0; index < level.kbKeys.size; index++ )
		{
			setKeyForBinding( getCommandFromKey( level.kbKeys[index] ), level.kbKeys[index] );
		}

		for ( index = 0; index < level.specialKeys.size; index++ )
		{
			setKeyForBinding( getCommandFromKey( level.specialKeys[index] ), level.specialKeys[index] );
		}

	}
}

setKeyForBinding( binding, key )
{
	if ( binding == "" )
		return;

	arrayKeys = getArrayKeys( level.actionBinds );
	for ( index = 0; index < arrayKeys.size; index++ )
	{
		bindArray = level.actionBinds[arrayKeys[index]];
		for ( bindIndex = 0; bindIndex < bindArray.size; bindIndex++ )
		{
			if ( bindArray[bindIndex].binding != binding )
				continue;

			bindArray[bindIndex].key = key;
		}
	}
}

notify_on_action( actionName )
{
	notifyName = "did_action_" + actionName;
	for ( index = 0; index < level.actionBinds[actionName].size; index++ )
	{
		actionBind = level.actionBinds[actionName][index];
		notifyOnCommand( notifyName, actionBind.binding );
	}
	
	return notifyName;
}

hint_for_action( actionName, timeOut, doubleline, notifyName )
{
	clear_hints();
	level endon ( "clearing_hints" );
/*
	if ( isdefined ( doubleline ) )
		add_hint_background( doubleline );
	else
		add_hint_background();
		*/
	
	actionBind = getActionBind( actionName );
	if ( !IsDefined( actionBind ) )
		return;
	
	level.hintElem = createFontString( "objective", level.hint_text_size );
	level.hintElem.hidewheninmenu = true;
	level.hintElem setPoint( "TOP", undefined, 0, 110 );
	level.hintElem.sort = 0.5;

	if ( ( actionName == "melee" ) && ( level.xenon ) && ( actionBind.key == "BUTTON_RSTICK" ) )
		level.hintElem setText( &"TRAINER_HINT_MELEE_CLICK" );
	else
		level.hintElem setText( actionBind.hint );

	wait_for_hint_notify_or_timeout( notifyName, timeOut );
	
	level.hintElem fadeOverTime( 0.5 );
	level.hintElem.alpha = 0;
	wait ( 0.5 );
	
	clear_hints();
}

wait_for_hint_notify_or_timeout( notifyName, timeOut )
{
	if ( isDefined( timeOut ) )
	{
		timeOutNotify = notifyName + "_timeout";
		level.player endon( timeOutNotify );
		level.player thread notifyOnTimeout( notifyName, timeOutNotify, timeOut );
	}
	level.player waittill( notifyName );
}

/*
keyHint( actionName, timeOut, doubleline, alwaysDisplay )
{
	clear_hints();
	level endon ( "clearing_hints" );

	if ( isdefined ( doubleline ) )
		add_hint_background( doubleline );
	else
		add_hint_background();
	level.hintElem = createFontString( "objective", level.hint_text_size );
	level.hintElem.hidewheninmenu = true;
	level.hintElem setPoint( "TOP", undefined, 0, 110 );
	level.hintElem.sort = 0.5;

	actionBind = getActionBind( actionName );
	if ( ( actionName == "melee" ) && ( level.xenon ) && ( actionBind.key == "BUTTON_RSTICK" ) )
		level.hintElem setText( &"TRAINER_HINT_MELEE_CLICK" );
	else
		level.hintElem setText( actionBind.hint );
	//level.hintElem endon ( "death" );
	
	if ( !isdefined( alwaysDisplay ) )
	{
		notifyName = "did_action_" + actionName;
		for ( index = 0; index < level.actionBinds[actionName].size; index++ )
		{
			actionBind = level.actionBinds[actionName][index];
			notifyOnCommand( notifyName, actionBind.binding );
		}
	
		if ( isDefined( timeOut ) )
			level.player thread notifyOnTimeout( notifyName, timeOut );
		level.player waittill( notifyName );
	
		level.hintElem fadeOverTime( 0.5 );
		level.hintElem.alpha = 0;
		wait ( 0.5 );
	
		clear_hints();
	}
}
*/

clear_hints()
{
	if ( isDefined( level.hintElem ) )
		level.hintElem destroyElem();
	if ( isDefined( level.iconElem ) )
		level.iconElem destroyElem();
	if ( isDefined( level.iconElem2 ) )
		level.iconElem2 destroyElem();
	if ( isDefined( level.iconElem3 ) )
		level.iconElem3 destroyElem();
	if ( isDefined( level.hintbackground ) )
		level.hintbackground destroyElem();
	level notify ( "clearing_hints" );
}

add_hint_background( double_line )
{
	if ( isdefined ( double_line ) )
		level.hintbackground = createIcon( "popmenu_bg", 650, 50 );
	else
		level.hintbackground = createIcon( "popmenu_bg", 650, 30 );
	level.hintbackground.hidewheninmenu = true;
	level.hintbackground setPoint( "TOP", undefined, 0, 105 );
	level.hintbackground.alpha = .5;
	level.hintbackground.sort = 0;
}

getActionBind( action )
{
    for ( index = 0; index < level.actionBinds[action].size; index++ )
    {
        actionBind = level.actionBinds[action][index];

        binding = getKeyBinding( actionBind.binding );
        if ( !binding["count"] )
            continue;

        return level.actionBinds[action][index];
    }

    return undefined;
}

notifyOnTimeout( finishedNotify, timeOutNotify, timeOut )
{
	self endon( finishedNotify );
	wait timeOut;
	self notify( timeOutNotify );
}

fade_to_black( fade_time )
{
	if ( !IsDefined( level.black_overlay ) )
	{
		level.black_overlay = create_client_overlay( "black", 0, level.player );
	}
	
	level.black_overlay fadeOverTime( fade_time );
	level.black_overlay.alpha = 1;
}

unfade_from_black( fade_time )
{
	if ( IsDefined( level.black_overlay ) )
	{
		level.black_overlay fadeOverTime( fade_time );
		level.black_overlay.alpha = 0;
	}
	
	wait fade_time;
	level.black_overlay Destroy();
}

check_anim_reached( guy, anime, tag, animname_override, within_distance )
{
	pos = get_anim_position( tag );
	org = pos[ "origin" ];
	angles = pos[ "angles" ];
	
	if ( IsDefined( animname_override ) )
		animname = animname_override;
	else
		animname = guy.animname;

	if ( IsDefined( level.scr_anim[ animname ][ anime ] ) )
	{
		if ( IsArray( level.scr_anim[ animname ][ anime ] ) )
			startorg = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ][ 0 ] );
		else
			startorg = GetStartOrigin( org, angles, level.scr_anim[ animname ][ anime ] );
	}
	else
	{
		startorg = org;
	}
	
	if( !isdefined( within_distance ) )
		within_distance = 4 * 12;
		
	distance_delta = DistanceSquared( guy.origin, startorg );
	if ( distance_delta > ( within_distance * within_distance ) )
	{
		return false;
	}
		
	return true;
}

/*
	just like anim_loop_solo with the addition that 
	  you can notify the entity the loop is playing on to stop the loop
	  (instead of notifying the root node (you can still notify the root node also))
*/
play_loop_solo_stoppable( ent, scene, ender )
{
	self thread anim_loop_solo( ent, scene, ender );
	self thread also_stop_loop_on( ent, ender );
}

also_stop_loop_on( ent, ender )
{
	self endon( ender );
	ent waittill( ender );
	self notify( ender );
}

play_loop_stoppable( ents, scene, ender )
{
	self thread anim_loop( ents, scene, ender );
	
	foreach( ent in ents )
	{
		self thread also_stop_loop_on( ent, ender );
	}
}


kill_no_react()
{
	if ( !isalive( self ) )
		return;
	self.allowDeath = true;
	self.a.nodeath = true;
	self set_battlechatter( false );

	self kill();
}

create_exploder_id( group_id, index_id )
{
	return group_id + " - " + index_id;
}

adjust_exploders()
{
	new_exploder_list = [];
	
	foreach ( key,exploder_group in level.createFXexploders )
	{
		// check special warlord exploders set up properly
		exploder_is_grouped = undefined;
		
		foreach ( exploder_ent in exploder_group )
		{
			assert_message = "script group not on all parts of exploder: " + key + ", at: " + exploder_ent.v[ "origin" ];
			
			if ( !IsDefined( exploder_ent.model ) || !IsDefined( exploder_ent.model.script_group ) )
			{
				AssertEx( !IsDefined( exploder_is_grouped ) || !exploder_is_grouped, assert_message );
				exploder_is_grouped = false;
				
				if ( !IsDefined( new_exploder_list[ key ] ) )
					new_exploder_list[ key ] = [];
			
				new_exploder_list[ key ][ new_exploder_list[ key ].size ] = exploder_ent;
				continue;
			}

			AssertEx( !IsDefined( exploder_is_grouped ) || exploder_is_grouped, assert_message );
			exploder_is_grouped = true;
			
			new_exploder_id = create_exploder_id( exploder_ent.model.script_group, exploder_ent.model.script_exploder );
			exploder_ent.v[ "exploder" ] = new_exploder_id;
			
			if ( !IsDefined( new_exploder_list[ new_exploder_id ] ) )
				new_exploder_list[ new_exploder_id ] = [];
			
			new_exploder_list[ new_exploder_id ][ new_exploder_list[ new_exploder_id ].size ] = exploder_ent;
		}
	}
	
	level.createFXexploders = new_exploder_list;
	
	// adjust any triggers
	for ( p = 0;p < 6;p ++ )
	{
		switch( p )
		{
			case 0:
				triggertype = "trigger_multiple";
				break;

			case 1:
				triggertype = "trigger_once";
				break;

			case 2:
				triggertype = "trigger_use";
				break;
				
			case 3:	
				triggertype = "trigger_radius";
				break;
			
			case 4:	
				triggertype = "trigger_lookat";
				break;

			default:
				assert( p == 5 );
				triggertype = "trigger_damage";
				break;
		}

		triggers = getentarray( triggertype, "classname" );
		
		for ( i = 0;i < triggers.size;i ++ )
		{
			if( isdefined( triggers[ i ].script_prefab_exploder) )
				triggers[i].script_exploder = triggers[ i ].script_prefab_exploder;

			if( isdefined( triggers[ i ].script_exploder) )
			{
				if ( IsDefined( triggers[ i ].script_group ) )
				{
					level notify( "killexplodertridgers" + triggers[ i ].script_exploder );
					triggers[ i ].script_exploder = create_exploder_id( triggers[ i ].script_group, triggers[ i ].script_exploder );
					level thread intro_exploder_load( triggers[ i ] );
				}
				
				// link trigger to every exploder with the same id
				exploder_group = level.createFXexploders[ triggers[ i ].script_exploder ];
				foreach ( exploder_ent in exploder_group )
				{
					if ( !IsDefined( exploder_ent.v[ "trigger" ] ) )
					{
						exploder_ent.v[ "trigger" ] = [];
					}
					exploder_ent.v[ "trigger" ][ exploder_ent.v[ "trigger" ].size ] = triggers[ i ];
				}
			}
		}
	}
}

intro_exploder_load( trigger )
{
	level endon( "killexplodertridgers" + trigger.script_exploder );
	trigger waittill( "trigger", triggered_entity );
	
	if ( IsDefined( triggered_entity ) )
	{
		if ( ( IsAI( triggered_entity ) && triggered_entity IsBadGuy() ) || 
		     ( IsDefined( triggered_entity.script_team ) && triggered_entity.script_team == "axis" ) )
		{
			level thread intro_exploder_load( trigger );
			return;
		}
	}
	
	if ( IsDefined( trigger.script_chance ) && RandomFloat( 1 ) > trigger.script_chance )
	{
		if ( !trigger script_delay() )
			wait 4;

		level thread intro_exploder_load( trigger );
		return;
	}

	if ( !trigger script_delay() && IsDefined( trigger.script_exploder_delay ) )
	{
		wait( trigger.script_exploder_delay );
	}

	exploder( trigger.script_exploder );
	level notify( "killexplodertridgers" + trigger.script_exploder );
}

setup_ent_for_damage()
{
	self.maxhealth = 20000;
	self SetNormalHealth( self.maxhealth );
	self SetCanDamage( true );
}

setup_custom_glass_destruction()
{
	setup_ent_for_damage();
	
	self.glass_parts = [ "tag_glass_front", "tag_glass_back", "tag_glass_left_front", "tag_glass_right_front",
						 "tag_glass_left_back", "tag_glass_right_back", "tag_light_left_front", "tag_light_right_front", 
						 "tag_light_left_back", "tag_light_right_back" ];
	
	self.glass_damage_state = [];
	for ( i = 0; i < self.glass_parts.size; i++ )
	{
		self.glass_damage_state[i] = SpawnStruct();
		self.glass_damage_state[i].v[ "currentState" ] = 0;
		self.glass_damage_state[i].v[ "health" ] = 40;
		self.glass_damage_state[i].v[ "invul" ] = false;
		update_glass( self, i );
	}
	
	self.glass_damage_state[0].v[ "destruct_fx" ] = "car_glass_large";
	self.glass_damage_state[0].v[ "tag_fx" ] = "tag_glass_front_fx";
	self.glass_damage_state[0].v[ "maxState" ] = 2;
	self.glass_damage_state[1].v[ "destruct_fx" ] = "car_glass_large";
	self.glass_damage_state[1].v[ "tag_fx" ] = "tag_glass_back_fx";
	self.glass_damage_state[1].v[ "maxState" ] = 2;
	self.glass_damage_state[2].v[ "destruct_fx" ] = "car_glass_med";
	self.glass_damage_state[2].v[ "tag_fx" ] = "tag_glass_left_front_fx";
	self.glass_damage_state[2].v[ "maxState" ] = 2;
	self.glass_damage_state[3].v[ "destruct_fx" ] = "car_glass_med";
	self.glass_damage_state[3].v[ "tag_fx" ] = "tag_glass_right_front_fx";
	self.glass_damage_state[3].v[ "maxState" ] = 1;
	self.glass_damage_state[4].v[ "destruct_fx" ] = "car_glass_med";
	self.glass_damage_state[4].v[ "tag_fx" ] = "tag_glass_left_back_fx";
	self.glass_damage_state[4].v[ "maxState" ] = 2;
	self.glass_damage_state[5].v[ "destruct_fx" ] = "car_glass_med";
	self.glass_damage_state[5].v[ "tag_fx" ] = "tag_glass_right_back_fx";
	self.glass_damage_state[5].v[ "maxState" ] = 2;
	self.glass_damage_state[6].v[ "destruct_fx" ] = "car_glass_headlight";
	self.glass_damage_state[6].v[ "tag_fx" ] = "tag_light_left_front";
	self.glass_damage_state[6].v[ "maxState" ] = 1;
	self.glass_damage_state[7].v[ "destruct_fx" ] = "car_glass_headlight";
	self.glass_damage_state[7].v[ "tag_fx" ] = "tag_light_right_front";
	self.glass_damage_state[7].v[ "maxState" ] = 1;
	self.glass_damage_state[8].v[ "destruct_fx" ] = "car_glass_brakelight";
	self.glass_damage_state[8].v[ "tag_fx" ] = "tag_light_left_back";
	self.glass_damage_state[8].v[ "maxState" ] = 1;
	self.glass_damage_state[9].v[ "destruct_fx" ] = "car_glass_brakelight";
	self.glass_damage_state[9].v[ "tag_fx" ] = "tag_light_right_back";
	self.glass_damage_state[9].v[ "maxState" ] = 1;
	
	thread custom_glass_think();
}

update_glass( damage_state_ent, glass_index, show_fx )
{
	if ( !IsDefined( damage_state_ent ) )
		damage_state_ent = self;
	
	glass_tag = self.glass_parts[glass_index];
	if ( damage_state_ent.glass_damage_state[glass_index].v[ "currentState" ] == 0 )
	{
		// unbroken
		self ShowPart( glass_tag );
		self HidePart( glass_tag + "_d" );
	}
	else if ( damage_state_ent.glass_damage_state[glass_index].v[ "currentState" ] == 1 )
	{
		// damaged
		self HidePart( glass_tag );
		self ShowPart( glass_tag + "_d" );
	}
	else
	{
		// broken
		self HidePart( glass_tag );
		self HidePart( glass_tag + "_d" );
		
		if ( IsDefined( show_fx ) && show_fx )
		{
			fx = damage_state_ent.glass_damage_state[glass_index].v["destruct_fx"];
			fx_tag = damage_state_ent.glass_damage_state[glass_index].v["tag_fx"];
			PlayFXOnTag( getfx( fx ), self, fx_tag );
		}
	}
}

custom_glass_think( damage_ent )
{
	if ( !IsDefined( damage_ent ) )
		damage_ent = self;
		
	damage_ent endon( "death" );
	
	while ( true )
	{
		damage_ent SetNormalHealth( damage_ent.maxhealth );
		
		damage_ent waittill( "damage", amount, attacker, direction_vec, point, type, modelName, tagName, partName );
		
		if ( IsDefined( tagName ) && tagName == "" )
		{
			if ( IsDefined( partName ) && partName != "" && partName != "tag_body" && partName != "body_animate_jnt" )
				tagName = partName;
			else
				tagName = undefined;
		}
		
		if ( !IsDefined( tagName ) )
			continue;
		
		tagNameLower = ToLower( tagName );
		foreach ( i,tag_part in self.glass_parts )
		{
			if ( tagNameLower == tag_part || tagNameLower == tag_part + "_d" )
			{
				do_glass_damage( damage_ent, i, amount );
			}
		}
	}
}

do_glass_damage( display_model, tag_index, amount )
{
	if ( self.glass_damage_state[ tag_index ].v[ "currentState" ] < 2 )
	{
		if ( self.glass_damage_state[ tag_index ].v[ "invul" ] )
		{
			return;
		}
		
		// if not in broken state, damage window
		self.glass_damage_state[ tag_index ].v[ "health" ] -= amount;
		if ( self.glass_damage_state[ tag_index ].v[ "health" ] < 0 )
		{
			if ( self.glass_damage_state[ tag_index ].v[ "currentState" ] < self.glass_damage_state[ tag_index ].v[ "maxState" ] )
			{
				// change glass damage state
				self.glass_damage_state[ tag_index ].v[ "health" ] = 40;
				self.glass_damage_state[ tag_index ].v[ "currentState" ]++;
				display_model update_glass( self, tag_index, true );
			}
		}
	}
}

lerp_player_view_to_position_and_wait( origin, angles, lerptime, total_time, fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo, player )
{
	player = get_player_from_self();

	linker = Spawn( "script_origin", ( 0, 0, 0 ) );
	linker.origin = player.origin;
	linker.angles = player GetPlayerAngles();

	if ( IsDefined( hit_geo ) && hit_geo )
	{
		player PlayerLinkTo( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc, hit_geo );
	}
	else
	if ( IsDefined( right_arc ) )
	{
		player PlayerLinkTo( linker, "", fraction, right_arc, left_arc, top_arc, bottom_arc );
	}
	else
	if ( IsDefined( fraction ) )
	{
		player PlayerLinkTo( linker, "", fraction );
	}
	else
	{
		player PlayerLinkTo( linker );
	}

	linker MoveTo( origin, lerptime, lerptime * 0.25 );
	linker RotateTo( angles, lerptime, lerptime * 0.25 );
	wait( total_time );
	linker Delete();
}