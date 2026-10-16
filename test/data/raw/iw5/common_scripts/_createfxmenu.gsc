#include common_scripts\utility;
#include common_scripts\_createfx;

menu( name )
{
	return level.create_fx_menu == name;
}

setmenu( name )
{
	level.create_fx_menu = name;
}

create_fx_menu()
{
	if ( button_is_clicked( "escape", "x" ) )
	{
		_exit_menu();
		return;
	}

	if ( menu( "creation" ) )
	{
		if ( button_is_clicked( "1" ) )
		{
			setmenu( "create_oneshot" );
			draw_effects_list();
			return;
		}
		if ( button_is_clicked( "2" ) )
		{
			setmenu( "create_loopfx" );
			draw_effects_list();
			return;
		}
		if ( button_is_clicked( "3" ) )
		{
			setmenu( "create_loopsound" );
			ent = createLoopSound();
			finish_creating_entity( ent );
			return;
		}
		if ( button_is_clicked( "4" ) )
		{
			setmenu( "create_exploder" );
			ent = createNewExploder();
			finish_creating_entity( ent );
			return;
		}
		if ( button_is_clicked( "5" ) )
		{
			setmenu( "create_interval_sound" );
			ent = createIntervalSound();
			finish_creating_entity( ent );
			return;
		}
	}
	else
	if ( menu( "create_oneshot" ) || menu( "create_loopfx" ) || menu( "change_fxid" ) )
	{
		if ( button_is_clicked( "m" ) )
		{
			increment_list_offset();
			draw_effects_list();
		}

		menu_fx_creation();
	}
	else
	if ( menu( "none" ) )
	{
		if ( button_is_clicked( "m" ) )
			increment_list_offset();

		// change selected entities
		menu_change_selected_fx();

		// if there's a selected ent then display the info on the last one to be selected
		if ( entities_are_selected() )
		{
			last_selected_ent = get_last_selected_entity();
			
			// only update hudelems when we have new info
			if ( !IsDefined( level.last_displayed_ent ) || last_selected_ent != level.last_displayed_ent )
			{
				display_fx_info( last_selected_ent );
				level.last_displayed_ent = last_selected_ent;
			}

			if ( button_is_clicked( "a" ) )
			{
				clear_settable_fx();
				setMenu( "add_options" );
			}
		}
	}
	else
	if ( menu( "add_options" ) )
	{
		if ( !entities_are_selected() )
		{
			clear_fx_hudElements();
			setMenu( "none" );
			return;
		}

		display_fx_add_options( get_last_selected_entity() );
		if ( button_is_clicked( "m" ) )
		{
			increment_list_offset();
//			draw_effects_list();		
		}
	}
}

_exit_menu()
{
	clear_fx_hudElements();
	clear_entity_selection();
	update_selected_entities();
	setmenu( "none" );
}

get_last_selected_entity()
{
	return level.selected_fx_ents[ level.selected_fx_ents.size - 1 ];
}

menu_fx_creation()
{
	count = 0;
	picked_fx = undefined;
	keys = func_get_level_fx();

	for ( i = level.effect_list_offset; i < keys.size; i++ )
	{
		count = count + 1;
		button_to_check = count;
		if ( button_to_check == 10 )
			button_to_check	 = 0;
		if ( button_is_clicked( button_to_check + "" ) )
		{
			picked_fx = keys[ i ];
			break;
		}

		if ( count > level.effect_list_offset_max )
			break;
	}

	if ( !isdefined( picked_fx ) )
		return;

	if ( menu( "change_fxid" ) )
	{
		apply_option_to_selected_fx( get_option( "fxid" ), picked_fx );
		level.effect_list_offset = 0;
		clear_fx_hudElements();
		setMenu( "none" );
		return;
	}


	ent = undefined;
	if ( menu( "create_loopfx" ) )
		ent = createLoopEffect( picked_fx );
	if ( menu( "create_oneshot" ) )
		ent = createOneshotEffect( picked_fx );

	finish_creating_entity( ent );
}

finish_creating_entity( ent )
{
	ent.v[ "angles" ] = vectortoangles( ( ent.v[ "origin" ] + ( 0, 0, 100 ) ) - ent.v[ "origin" ] );
	assert( isdefined( ent ) );
	ent post_entity_creation_function();// for createfx dev purposes
	clear_entity_selection();
	select_last_entity();
	move_selection_to_cursor();
	update_selected_entities();
	setMenu( "none" );
}

menu_init()
{
	level.createFX_options = [];
	// each option has a type, a name its stored under, a description, a default, and a mask it uses to determine
	// which types of fx can have this option
	addOption( "string", "fxid", "The FX", "nil", "fx" );
	addOption( "float", "delay", "Repeat rate/start delay", 0.5, "fx" );
	addOption( "float", "fire_range", "Fire damage range", 0, "fx" );
	addOption( "string", "flag", "Flag", "nil", "exploder" );

	addOption( "string", "firefx", "2nd FX id", "nil", "exploder" );
	addOption( "float", "firefxdelay", "2nd FX id repeat rate", 0.5, "exploder" );
	addOption( "float", "firefxtimeout", "2nd FX timeout", 5, "exploder" );
	addOption( "string", "firefxsound", "2nd FX soundalias", "nil", "exploder" );
	addOption( "float", "damage", "Radius damage", 150, "exploder" );
	addOption( "float", "damage_radius", "Radius of radius damage", 250, "exploder" );
	addOption( "float", "delay_min", "Minimimum time between repeats", 1, "soundfx_interval" );
	addOption( "float", "delay_max", "Maximum time between repeats", 2, "soundfx_interval" );
	addOption( "int", "repeat", "Number of times to repeat", 5, "exploder" );
	addOption( "string", "exploder", "Exploder", "1", "exploder" );
	addOption( "string", "earthquake", "Earthquake", "nil", "exploder" );
	
	if( !level.mp_createfx )
		addOption( "string", "rumble", "Rumble", "nil", "exploder" );
	addOption( "string", "ender", "Level notify for ending 2nd FX", "nil", "exploder" );

	addOption( "string", "soundalias", "Soundalias", "nil", "all" );
	addOption( "string", "loopsound", "Loopsound", "nil", "exploder" );

	if( !level.mp_createfx )
		addOption( "int", "stoppable", "Can be stopped from script", "1", "all" );

	level.effect_list_offset = 0;
	level.effect_list_offset_max = 10;


	// creates mask groups. For example if the above says its mask is "fx", then all the types under "fx" can use the option
	level.createfxMasks = [];
	level.createfxMasks[ "all" ] = [];
	level.createfxMasks[ "all" ][ "exploder" ] = true;
	level.createfxMasks[ "all" ][ "oneshotfx" ] = true;
	level.createfxMasks[ "all" ][ "loopfx" ] = true;
	level.createfxMasks[ "all" ][ "soundfx" ] = true;
	level.createfxMasks[ "all" ][ "soundfx_interval" ] = true;
	

	level.createfxMasks[ "fx" ] = [];
	level.createfxMasks[ "fx" ][ "exploder" ] = true;
	level.createfxMasks[ "fx" ][ "oneshotfx" ] = true;
	level.createfxMasks[ "fx" ][ "loopfx" ] = true;

	level.createfxMasks[ "exploder" ] = [];
	level.createfxMasks[ "exploder" ][ "exploder" ] = true;

	level.createfxMasks[ "loopfx" ] = [];
	level.createfxMasks[ "loopfx" ][ "loopfx" ] = true;

	level.createfxMasks[ "oneshotfx" ] = [];
	level.createfxMasks[ "oneshotfx" ][ "oneshotfx" ] = true;

	level.createfxMasks[ "soundfx" ] = [];
	level.createfxMasks[ "soundfx" ][ "soundalias" ] = true;
	
	level.createfxMasks[ "soundfx_interval" ] = [];
	level.createfxMasks[ "soundfx_interval" ][ "soundfx_interval" ] = true;

}

get_last_selected_ent()
{
	return level.selected_fx_ents[ level.selected_fx_ents.size - 1 ];
}

entities_are_selected()
{
	return level.selected_fx_ents.size > 0;
}

menu_change_selected_fx()
{
	if ( !level.selected_fx_ents.size )
		return;

	count = 0;
	drawnCount = 0;
	ent = get_last_selected_ent();

	for ( i = 0; i < level.createFX_options.size; i++ )
	{
		option = level.createFX_options[ i ];
		if ( !isdefined( ent.v[ option[ "name" ] ] ) )
			continue;
		count++ ;
		if ( count < level.effect_list_offset )
			continue;

		drawnCount++ ;
		button_to_check = drawnCount;
		if ( button_to_check == 10 )
			button_to_check = 0;

		if ( button_is_clicked( button_to_check + "" ) )
		{
			prepare_option_for_change( option, drawnCount );
			break;
		}

		if ( drawnCount > level.effect_list_offset_max )
		{
			more = true;
			break;
		}
	}
}

prepare_option_for_change( option, drawnCount )
{
	if ( option[ "name" ] == "fxid" )
	{
		setMenu( "change_fxid" );
		draw_effects_list();
		return;
	}

	createfx_centerprint( "To change " + option[ "description" ] + " on selected entities, type /fx newvalue" );
	level.createfx_inputlocked = true;
	set_option_index( option[ "name" ] );
	setdvar( "fx", "nil" );
	// change color of text to look selected
	level.createFxHudElements[ drawnCount + 3 ][ 0 ].color = ( 1, 1, 0 );
}

menu_fx_option_set()
{
	if ( getdvar( "fx" ) == "nil" )
		return;

	option = get_selected_option();
	setting = undefined;
	if ( option[ "type" ] == "string" )
		setting = getdvar( "fx" );
	if ( option[ "type" ] == "int" )
		setting = getdvarint( "fx" );
	if ( option[ "type" ] == "float" )
		setting = getdvarfloat( "fx" );

	apply_option_to_selected_fx( option, setting );
}

apply_option_to_selected_fx( option, setting )
{
	for ( i = 0; i < level.selected_fx_ents.size; i++ )
	{
		ent = level.selected_fx_ents[ i ];

		if ( mask( option[ "mask" ], ent.v[ "type" ] ) )
			ent.v[ option[ "name" ] ] = setting;
	}

	level.last_displayed_ent = undefined; // needed to force a redraw of the last display ent
	update_selected_entities();
	clear_settable_fx();
}

set_option_index( name )
{
	for ( i = 0; i < level.createFX_options.size; i++ )
	{
		if ( level.createFX_options[ i ][ "name" ] != name )
			continue;

		level.selected_fx_option_index = i;
		return;
	}
}

get_selected_option()
{
	return level.createFX_options[ level.selected_fx_option_index ];
}

mask( type, name )
{
	return isdefined( level.createfxMasks[ type ][ name ] );
}

addOption( type, name, description, defaultSetting, mask )
{
	option = [];
	option[ "type" ] = type;
	option[ "name" ] = name;
	option[ "description" ] = description;
	option[ "default" ] = defaultSetting;
	option[ "mask" ] = mask;
	level.createFX_options[ level.createFX_options.size ] = option;
}

get_option( name )
{
	for ( i = 0; i < level.createFX_options.size; i++ )
	{
		if ( level.createFX_options[ i ][ "name" ] == name )
			return level.createFX_options[ i ];
	}
}

display_fx_info( ent )
{
	// are we doing the create fx menu right now?
	if ( !menu( "none" ) )
		return;

	clear_fx_hudElements();
	set_fx_hudElement( "Name: " + ent.v[ "fxid" ] );
	set_fx_hudElement( "Type: " + ent.v[ "type" ] );
	set_fx_hudElement( "Origin: " + ent.v[ "origin" ] );
	set_fx_hudElement( "Angles: " + ent.v[ "angles" ] );

	if ( entities_are_selected() )
	{
		// if entities are selected then we make the entity stats modifiable
		count = 0;
		drawnCount = 0;
		more = false;
		for ( i = 0; i < level.createFX_options.size; i++ )
		{
			option = level.createFX_options[ i ];
			if ( !isdefined( ent.v[ option[ "name" ] ] ) )
				continue;
			count++ ;
			if ( count < level.effect_list_offset )
				continue;

			drawnCount++ ;
			set_fx_hudElement( drawnCount + ". " + option[ "description" ] + ": " + ent.v[ option[ "name" ] ] );
			if ( drawnCount > level.effect_list_offset_max )
			{
				more = true;
				break;
			}
		}
		if ( count > level.effect_list_offset_max )
			set_fx_hudElement( "(m) More >" );
		set_fx_hudElement( "(a) Add >" );
		set_fx_hudElement( "(x) Exit >" );
	}
	else
	{
		count = 0;
		more = false;
		for ( i = 0; i < level.createFX_options.size; i++ )
		{
			option = level.createFX_options[ i ];
			if ( !isdefined( ent.v[ option[ "name" ] ] ) )
				continue;
			count++ ;
			set_fx_hudElement( option[ "description" ] + ": " + ent.v[ option[ "name" ] ] );
			if ( count > level.createFx_hudElements )
				break;
		}
	}
}

display_fx_add_options( ent )
{
	// are we doing the create fx menu right now?
	assert( menu( "add_options" ) );
	assert( entities_are_selected() );

	clear_fx_hudElements();
	set_fx_hudElement( "Name: " + ent.v[ "fxid" ] );
	set_fx_hudElement( "Type: " + ent.v[ "type" ] );
	set_fx_hudElement( "Origin: " + ent.v[ "origin" ] );
	set_fx_hudElement( "Angles: " + ent.v[ "angles" ] );

	// if entities are selected then we make the entity stats modifiable
	count = 0;
	drawnCount = 0;
	more = false;

	if ( level.effect_list_offset >= level.createFX_options.size )
		level.effect_list_offset = 0;

	for ( i = 0; i < level.createFX_options.size; i++ )
	{
		option = level.createFX_options[ i ];
		if ( isdefined( ent.v[ option[ "name" ] ] ) )
			continue;

		// does this type of effect get this kind of option?
		if ( !mask( option[ "mask" ], ent.v[ "type" ] ) )
			continue;

		count++ ;
		if ( count < level.effect_list_offset )
			continue;
		if ( drawnCount >= level.effect_list_offset_max )
			continue;

		drawnCount++ ;
		button_to_check = drawnCount;
		if ( button_to_check == 10 )
			button_to_check = 0;
		if ( button_is_clicked( button_to_check + "" ) )
		{
			add_option_to_selected_entities( option );
//			prepare_option_for_change( option, drawnCount );
			menuNone();
			level.last_displayed_ent = undefined; // needed to force a redraw of the last display ent
			return;
		}

		set_fx_hudElement( button_to_check + ". " + option[ "description" ] );
	}

	if ( count > level.effect_list_offset_max )
		set_fx_hudElement( "(m) More >" );

	set_fx_hudElement( "(x) Exit >" );
}

add_option_to_selected_entities( option )
{
	setting = undefined;
	for ( i = 0; i < level.selected_fx_ents.size; i++ )
	{
		ent = level.selected_fx_ents[ i ];

		if ( mask( option[ "mask" ], ent.v[ "type" ] ) )
			ent.v[ option[ "name" ] ] = option[ "default" ];
	}
}

menuNone()
{
	level.effect_list_offset = 0;
	clear_fx_hudElements();
	setMenu( "none" );
}


draw_effects_list()
{

	clear_fx_hudElements();

	set_fx_hudElement( "Pick an effect:" );
	count = 0;
	more = false;

	keys = func_get_level_fx();

	if ( level.effect_list_offset >= keys.size )
		level.effect_list_offset = 0;

	for ( i = level.effect_list_offset; i < keys.size; i++ )
	{
		count = count + 1;
		set_fx_hudElement( count + ". " + keys[ i ] );
		if ( count >= level.effect_list_offset_max )
		{
			more = true;
			break;
		}
	}

	if ( keys.size > level.effect_list_offset_max )
		set_fx_hudElement( "(m) More >" );
}

increment_list_offset()
{
	level.effect_list_offset += level.effect_list_offset_max;
//	keys = getarraykeys(level._effect);
//	if (level.effect_list_offset >= keys.size)
//		level.effect_list_offset = 0;
}


