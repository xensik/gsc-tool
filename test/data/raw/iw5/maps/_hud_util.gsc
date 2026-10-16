#include maps\_utility;
#include animscripts\utility;
#include common_scripts\utility;

setParent( element )
{
	if ( isDefined( self.parent ) && self.parent == element )
		return;

	if ( isDefined( self.parent ) )
		self.parent removeChild( self );

	self.parent = element;
	self.parent addChild( self );

	if ( isDefined( self.point ) )
		self setPoint( self.point, self.relativePoint, self.xOffset, self.yOffset );
	else
		self setPoint( "TOPLEFT" );
}

getParent()
{
	return self.parent;
}

addChild( element )
{
	element.index = self.children.size;
	self.children[ self.children.size ] = element;
}

removeChild( element )
{
	element.parent = undefined;

	if ( self.children[ self.children.size - 1 ] != element )
	{
		self.children[ element.index ] = self.children[ self.children.size - 1 ];
		self.children[ element.index ].index = element.index;
	}
	self.children[ self.children.size - 1 ] = undefined;

	element.index = undefined;
}


setPoint( point, relativePoint, xOffset, yOffset, moveTime )
{
	if ( !isDefined( moveTime ) )
		moveTime = 0;

	element = self getParent();

	if ( moveTime )
		self moveOverTime( moveTime );

	if ( !isDefined( xOffset ) )
		xOffset = 0;
	self.xOffset = xOffset;

	if ( !isDefined( yOffset ) )
		yOffset = 0;
	self.yOffset = yOffset;

	self.point = point;

	self.alignX = "center";
	self.alignY = "middle";

	if ( isSubStr( point, "TOP" ) )
		self.alignY = "top";
	if ( isSubStr( point, "BOTTOM" ) )
		self.alignY = "bottom";
	if ( isSubStr( point, "LEFT" ) )
		self.alignX = "left";
	if ( isSubStr( point, "RIGHT" ) )
		self.alignX = "right";

	if ( !isDefined( relativePoint ) )
		relativePoint = point;

	self.relativePoint = relativePoint;

	relativeX = "center";
	relativeY = "middle";

	if ( isSubStr( relativePoint, "TOP" ) )
		relativeY = "top";
	if ( isSubStr( relativePoint, "BOTTOM" ) )
		relativeY = "bottom";
	if ( isSubStr( relativePoint, "LEFT" ) )
		relativeX = "left";
	if ( isSubStr( relativePoint, "RIGHT" ) )
		relativeX = "right";

	if ( element == level.uiParent )
	{
		self.horzAlign = relativeX;
		self.vertAlign = relativeY;
	}
	else
	{
		self.horzAlign = element.horzAlign;
		self.vertAlign = element.vertAlign;
	}


	if ( relativeX == element.alignX )
	{
		offsetX = 0;
		xFactor = 0;
	}
	else if ( relativeX == "center" || element.alignX == "center" )
	{
		offsetX = int( element.width / 2 );
		if ( relativeX == "left" || element.alignX == "right" )
			xFactor = -1;
		else
			xFactor = 1;
	}
	else
	{
		offsetX = element.width;
		if ( relativeX == "left" )
			xFactor = -1;
		else
			xFactor = 1;
	}
	self.x = element.x + ( offsetX * xFactor );

	if ( relativeY == element.alignY )
	{
		offsetY = 0;
		yFactor = 0;
	}
	else if ( relativeY == "middle" || element.alignY == "middle" )
	{
		offsetY = int( element.height / 2 );
		if ( relativeY == "top" || element.alignY == "bottom" )
			yFactor = -1;
		else
			yFactor = 1;
	}
	else
	{
		offsetY = element.height;
		if ( relativeY == "top" )
			yFactor = -1;
		else
			yFactor = 1;
	}
	self.y = element.y + ( offsetY * yFactor );

	self.x += self.xOffset;
	self.y += self.yOffset;

	switch( self.elemType )
	{
		case "bar":
			setPointBar( point, relativePoint, xOffset, yOffset );
			break;
	}

	self updateChildren();
}


setPointBar( point, relativePoint, xOffset, yOffset )
{
	self.bar.horzAlign = self.horzAlign;
	self.bar.vertAlign = self.vertAlign;

	self.bar.alignX = "left";
	self.bar.alignY = self.alignY;
	self.bar.y = self.y;

	if ( self.alignX == "left" )
		self.bar.x = self.x + self.padding;
	else if ( self.alignX == "right" )
		self.bar.x = self.x - ( self.width - self.padding );
	else
		self.bar.x = self.x - int( ( self.width - self.padding ) / 2 );

	self updateBar( self.bar.frac );
}


updateBar( barFrac )
{
	barWidth = int( ( self.width - ( self.padding * 2 ) ) * barFrac );

	if ( !barWidth )
		barWidth = 1;

	self.bar.frac = barFrac;
	self.bar setShader( self.bar.shader, barWidth, self.height - ( self.padding * 2 ) );
}

hideBar( bool )
{
	// Default to hiding
	bool = ter_op( isdefined( bool ), bool, true );
	
	// If hiding or if showing when already visible
	// set the original values
	if ( bool || !isdefined( self.orig_alpha ) || !isdefined( self.bar.orig_alpha ) )
	{
		// Store the original alpha values
		self.orig_alpha		= self.alpha;
		self.bar.orig_alpha	= self.bar.alpha;
	}
	
	// Hide or Show
	self.alpha			= ter_op( bool, 0, self.orig_alpha );
	self.bar.alpha		= ter_op( bool, 0, self.bar.orig_alpha );
}


/*
=============
///ScriptDocBegin
"Name: createFontString( <font>, <fontScale> )"
"Summary: Creates a hud element for font purposes"
"Module: Hud"
"MandatoryArg: <font>: Apparently this is always set to default."
"MandatoryArg: <fontScale>: The scale you want."
"Example: level.hintElem = createFontString( "default", 2.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

createFontString( font, fontScale )
{
	fontElem = newHudElem();
	fontElem.elemType = "font";
	fontElem.font = font;
	fontElem.fontscale = fontScale;
	fontElem.x = 0;
	fontElem.y = 0;
	fontElem.width = 0;
	fontElem.height = int( level.fontHeight * fontScale );
	fontElem.xOffset = 0;
	fontElem.yOffset = 0;
	fontElem.children = [];
	fontElem setParent( level.uiParent );

	return fontElem;
}


/*
=============
///ScriptDocBegin
"Name: createClientFontString( <font>, <fontScale> )"
"Summary: Creates a client hud element for font purposes"
"Module: Hud"
"MandatoryArg: <font>: Apparently this is always set to default."
"MandatoryArg: <fontScale>: The scale you want."
"Example: level.hintElem = level.player createClientFontString( "default", 2.0 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/

createClientFontString( font, fontScale )
{
	assert( isplayer( self ) );

	fontElem = newClientHudElem( self );
	fontElem.elemType = "font";
	fontElem.font = font;
	fontElem.fontscale = fontScale;
	fontElem.x = 0;
	fontElem.y = 0;
	fontElem.width = 0;
	fontElem.height = int( level.fontHeight * fontScale );
	fontElem.xOffset = 0;
	fontElem.yOffset = 0;
	fontElem.children = [];
	fontElem setParent( level.uiParent );

	return fontElem;
}

createClientTimer( font, fontScale )
{
	assert( isplayer( self ) );

	timerElem = newClientHudElem( self );
	timerElem.elemType = "timer";
	timerElem.font = font;
	timerElem.fontscale = fontScale;
	timerElem.x = 0;
	timerElem.y = 0;
	timerElem.width = 0;
	timerElem.height = int( level.fontHeight * fontScale );
	timerElem.xOffset = 0;
	timerElem.yOffset = 0;
	timerElem.children = [];
	timerElem setParent( level.uiParent );

	return timerElem;
}


createServerFontString( font, fontScale )
{
	fontElem = newHudElem();
	fontElem.elemType = "font";
	fontElem.font = font;
	fontElem.fontscale = fontScale;
	fontElem.x = 0;
	fontElem.y = 0;
	fontElem.width = 0;
	fontElem.height = int( level.fontHeight * fontScale );
	fontElem.xOffset = 0;
	fontElem.yOffset = 0;
	fontElem.children = [];
	fontElem setParent( level.uiParent );

	return fontElem;
}

createServerTimer( font, fontScale )
{
	timerElem = newHudElem();
	timerElem.elemType = "timer";
	timerElem.font = font;
	timerElem.fontscale = fontScale;
	timerElem.x = 0;
	timerElem.y = 0;
	timerElem.width = 0;
	timerElem.height = int( level.fontHeight * fontScale );
	timerElem.xOffset = 0;
	timerElem.yOffset = 0;
	timerElem.children = [];
	timerElem setParent( level.uiParent );

	return timerElem;
}

createIcon( shader, width, height )
{
	iconElem = newHudElem();
	return createIcon_Hudelem( iconElem, shader, width, height );
}

createClientIcon( shader, width, height )
{
	iconElem = newClientHudElem( self );
	return createIcon_Hudelem( iconElem, shader, width, height );
}

createIcon_Hudelem( iconElem, shader, width, height )
{
	iconElem.elemType = "icon";
	iconElem.x = 0;
	iconElem.y = 0;
	iconElem.width = width;
	iconElem.height = height;
	iconElem.xOffset = 0;
	iconElem.yOffset = 0;
	iconElem.children = [];
	iconElem setParent( level.uiParent );

	if ( isDefined( shader ) )
		iconElem setShader( shader, width, height );

	return iconElem;
}


createBar( shader, bgshader, width, height, flashFrac )
{
	if ( !isdefined( shader ) )
		shader = "white";

	if ( !isdefined( bgshader ) )
		bgshader = "black";

	if ( !isdefined( width ) )
		width = 100;

	if ( !isdefined( height ) )
		height = 9;

	barElem = newHudElem();
	barElem.x = 0 + 2;
	barElem.y = 0 + 2;
	barElem.frac = 0.25;
	barElem.shader = shader;
	barElem.sort = -1;
	barElem setShader( shader, width - 2, height - 2 );
	if ( isDefined( flashFrac ) )
	{
		barElem.flashFrac = flashFrac;
		barElem thread flashThread();
	}

	barElemBG = newHudElem();
	barElemBG.elemType = "bar";
	barElemBG.x = 0;
	barElemBG.y = 0;
	barElemBG.width = width;
	barElemBG.height = height;
	barElemBG.xOffset = 0;
	barElemBG.yOffset = 0;
	barElemBG.bar = barElem;
	barElemBG.children = [];
	barElemBG.padding = 2;
	barElemBG.sort = -2;
	barElemBG.alpha = 0.5;
	barElemBG setParent( level.uiParent );
	barElemBG setShader( bgshader, width, height );

	return barElemBG;
}

createClientProgressBar( player, y_offset, shader, bgshader, width, height )
{
	player		= ter_op( isdefined( player ), player, level.player );
	y_offset	= ter_op( isdefined( y_offset ), y_offset, 90 );
	shader		= ter_op( isdefined( shader ), shader, "white" );
	bgshader	= ter_op( isdefined( bgshader ), bgshader, "black" );
	width		= ter_op( isdefined( width ), width, 100 );
	height		= ter_op( isdefined( height ), height, 9 );
		
    bar = player createClientBar( shader, bgshader, width, height );
	bar setPoint( "CENTER", undefined, 0, y_offset );

    return bar;
}

createClientBar( shader, bgshader, width, height, flashFrac )
{
	barElem = newClientHudElem( self );
	barElem.x = 0 + 2;
	barElem.y = 0 + 2;
	barElem.frac = 0.25;
	barElem.shader = shader;
	barElem.sort = -1;
	barElem setShader( shader, width - 2, height - 2 );
	if ( isDefined( flashFrac ) )
	{
		barElem.flashFrac = flashFrac;
		barElem thread flashThread();
	}

	barElemBG = newClientHudElem( self );
	barElemBG.elemType = "bar";
	barElemBG.x = 0;
	barElemBG.y = 0;
	barElemBG.width = width;
	barElemBG.height = height;
	barElemBG.xOffset = 0;
	barElemBG.yOffset = 0;
	barElemBG.bar = barElem;
	barElemBG.children = [];
	barElemBG.padding = 2;
	barElemBG.sort = -2;
	barElemBG.alpha = 0.5;
	barElemBG setParent( level.uiParent );
	barElemBG setShader( bgshader, width, height );

	return barElemBG;
}


setFlashFrac( flashFrac )
{
	self.bar.flashFrac = flashFrac;
}

/*
=============
///ScriptDocBegin
"Name: fade_over_time( <target_alpha> , <fade_time> )"
"Summary: Fade the hud_elem to the target_alpha over fade_time."
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <target_alpha>: Desired alpha to transition to"
"OptionalArg: <fade_time>: Time for the fade to take place"
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
fade_over_time( target_alpha, fade_time )
{
	assertex( isdefined( target_alpha ), "fade_over_time must be passed a target_alpha." );
	
	if ( isdefined( fade_time ) && fade_time > 0 )
	{
	self fadeOverTime( fade_time );
	}
	
	self.alpha = target_alpha;
	
	if ( isdefined( fade_time ) && fade_time > 0 )
	{
	wait fade_time;
}
}

flashThread()
{
	self endon( "death" );

	self.alpha = 1;
	while ( 1 )
	{
		if ( self.frac >= self.flashFrac )
		{
			self fadeOverTime( 0.3 );
			self.alpha = .2;
			wait( 0.35 );
			self fadeOverTime( 0.3 );
			self.alpha = 1;
			wait( 0.7 );
		}
		else
		{
			self.alpha = 1;
			wait( 0.05 );
		}
	}
}


destroyElem()
{
	tempChildren = [];

	for ( index = 0; index < self.children.size; index++ )
		tempChildren[ index ] = self.children[ index ];

	for ( index = 0; index < tempChildren.size; index++ )
		tempChildren[ index ] setParent( self getParent() );

	if ( self.elemType == "bar" )
		self.bar destroy();

	self destroy();
}

setIconShader( shader )
{
	self setShader( shader, self.width, self.height );
}

setWidth( width )
{
	self.width = width;
}


setHeight( height )
{
	self.height = height;
}

setSize( width, height )
{
	self.width = width;
	self.height = height;
}

updateChildren()
{
	for ( index = 0; index < self.children.size; index++ )
	{
		child = self.children[ index ];
		child setPoint( child.point, child.relativePoint, child.xOffset, child.yOffset );
	}
}

/*
	thread stance_carry_icon_enable( bool );
	Diasables all stance icons and replaces with an icon of 
	a person carrying another person on his back. True/false
*/
stance_carry_icon_enable( bool )
{
	if ( isdefined( bool ) && bool == false )
	{
		stance_carry_icon_disable();
		return;
	}

	if ( isDefined( level.stance_carry ) )
		level.stance_carry destroy();

	SetSavedDvar( "hud_showStance", "0" );

	level.stance_carry = newHudElem();
	level.stance_carry.x = -75;
	if ( level.console )
		level.stance_carry.y = -20;
	else
		level.stance_carry.y = -10;
	level.stance_carry setshader( "stance_carry", 64, 64 );
	level.stance_carry.alignX = "right";
	level.stance_carry.alignY = "bottom";
	level.stance_carry.horzAlign = "right";
	level.stance_carry.vertAlign = "bottom";
	level.stance_carry.foreground = true;
	level.stance_carry.alpha = 0;
	level.stance_carry fadeOverTime( 0.5 );
	level.stance_carry.alpha = 1;
}

stance_carry_icon_disable()
{
	if ( isDefined( level.stance_carry ) )
	{
		level.stance_carry fadeOverTime( 0.5 );
		level.stance_carry.alpha = 0;
		level.stance_carry destroy();
	}
	SetSavedDvar( "hud_showStance", "1" );
}


/*
=============
///ScriptDocBegin
"Name: create_mantle( <create_mantle> )"
"Summary: "
"Module: Entity"
"CallOn: An entity"
"MandatoryArg: <param1>: "
"OptionalArg: <param2>: "
"Example: "
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_mantle()
{
	if ( level.console )
	{
		text = createFontString( "default", 1.8 );
		text setPoint( "CENTER", undefined, -23, 115 );
		text settext( level.strings[ "mantle" ] );

		icon = createIcon( "hint_mantle", 40, 40 );
		icon setPoint( "CENTER", undefined, 73, 0 );
		icon setparent( text );
	}
	else
	{
		text = createFontString( "default", 1.6 );
		text setPoint( "CENTER", undefined, 0, 115 );
		text settext( level.strings[ "mantle" ] );

		icon = createIcon( "hint_mantle", 40, 40 );
		icon setPoint( "CENTER", undefined, 0, 30 );
		icon setparent( text );
	}

	icon.alpha = 0;
	text.alpha = 0;

	level.hud_mantle = [];
	level.hud_mantle[ "text" ] = text;
	level.hud_mantle[ "icon" ] = icon;
}

get_countdown_hud( x, y, player, forceXPos )
{
	if ( !isdefined( forceXPos ) )
		forceXPos = false;
	xPos = undefined;
	if ( !level.Console )
		xPos = -250; //override x-position if this is PC or the timer will get cut off
	else if ( !isdefined( x ) )
		xPos = -225;
	else
		xPos = x;
	
	if ( forceXPos )
		xPos = x;
	
	if ( !isdefined( y ) )
		yPos = 100;
	else
		yPos = y;

	if ( isdefined( player ) )
		hudelem = newClientHudElem( player );
	else
		hudelem = newHudElem();
	
	hudelem.alignX = "left";
	hudelem.alignY = "middle";
	hudelem.horzAlign = "right";
	hudelem.vertAlign = "top";
	hudelem.x = xPos;
	hudelem.y = yPos;
	hudelem.fontScale = 1.6;
	hudelem.color = ( 0.8, 1.0, 0.8 );
	hudelem.font = "objective";
	hudelem.glowColor = ( 0.3, 0.6, 0.3 );
	hudelem.glowAlpha = 1;
	hudelem.foreground = 1;
	hudelem.hidewheninmenu = true;
	hudelem.hidewhendead = true;
	return hudelem;
}

get_download_state_hud( x, y, player, forceXPos )
{
	if ( !isdefined( forceXPos ) )
		forceXPos = false;
	
	xPos = undefined;
	if ( !level.Console )
		xPos = -250; //override x-position if this is PC or the timer will get cut off
	else if ( !isdefined( x ) )
		xPos = -170;
	else
		xPos = x;
	
	if ( forceXPos )
		xPos = x;
	
	if ( !isdefined( y ) )
		yPos = 100;
	else
		yPos = y;

	if ( isdefined( player ) )
		hudelem = newClientHudElem( player );
	else
		hudelem = newHudElem();
	
	hudelem.alignX = "right";
	hudelem.alignY = "middle";
	hudelem.horzAlign = "right";
	hudelem.vertAlign = "top";
	hudelem.x = xPos;
	hudelem.y = yPos;
	hudelem.fontScale = 1.6;
	hudelem.color = ( 0.8, 1.0, 0.8 );
	hudelem.font = "objective";
	hudelem.glowColor = ( 0.3, 0.6, 0.3 );
	hudelem.glowAlpha = 1;
	hudelem.foreground = 1;
	hudelem.hidewheninmenu = true;
	hudelem.hidewhendead = true;
	return hudelem;
}

/*
=============
///ScriptDocBegin
"Name: create_client_overlay( <shader_name>, <start_alpha>, <player> )"
"Summary: Creates a full screen client hud overlay. Must also use code command precacheShader( <shader_name> ) to precache the element used (black, white, etc)."
"Module: Hud"
"MandatoryArg: <shader_name>: Name of the shader precached that you want to have displayed."
"MandatoryArg: <start_alpha>: Beginning alpha value for the element."
"OptionalArg: <player>: Pointer to the player for which the overlay will be displayed. If left blank, overlay will be displayed for all players."
"Example: black_overlay = create_client_overlay( "black", 0, level.player );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_client_overlay( shader_name, start_alpha, player )
{
	if ( isdefined( player ) )
		overlay = newClientHudElem( player );
	else
		overlay = newHudElem();
	overlay.x = 0;
	overlay.y = 0;
	overlay setshader( shader_name, 640, 480 );
	overlay.alignX = "left";
	overlay.alignY = "top";
	overlay.sort = 1;
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = start_alpha;
	overlay.foreground = true;
	return overlay;
}

/*
=============
///ScriptDocBegin
"Name: create_client_overlay_custom_size( <shader_name>, <start_alpha>, <x>, <y> )"
"Summary: Creates a full screen client hud overlay. Must also use code command precacheShader( <shader_name> ) to precache the element used (black, white, etc)."
"Module: Hud"
"MandatoryArg: <shader_name>: Name of the shader precached that you want to have displayed."
"MandatoryArg: <start_alpha>: Beginning alpha value for the element."
"MandatoryArg: <x>: Width."
"MandatoryArg: <y>: Height."
"CallOn: A player"
"Example: black_overlay = create_client_overlay_custom_size( "black", 0, 100, 50 );"
"SPMP: singleplayer"
///ScriptDocEnd
=============
*/
create_client_overlay_custom_size( shader_name, start_alpha, x, y, scale )
{
	player = get_player_from_self();
	overlay = newClientHudElem( player );

	if ( !IsDefined( scale ) )
	{
		scale = 1;
	}

	if ( !IsDefined( x ) )
	{
		x = 0;
	}

	if ( !IsDefined( y ) )
	{
		y = 0;
	}

	overlay.x = x;
	overlay.y = y;
	overlay Setshader( shader_name, int( 640 * scale ), int( 480 * scale ) );
	overlay.alignX = "center";
	overlay.alignY = "middle";
	overlay.sort = 1;
	overlay.horzAlign = "center";
	overlay.vertAlign = "middle";
	overlay.alpha = start_alpha;
	overlay.foreground = true;
	return overlay;
}

create_client_overlay_fullscreen( shader, start_alpha, x, y, scale )
{
	player 	= get_player_from_self();
	overlay = NewClientHudElem( player );

	if ( !IsDefined( scale ) )
	{
		scale = 1;
	}

	overlay.x = x;
	overlay.y = y;
	overlay Setshader( shader, int( 640 * scale ), int( 480 * scale ) );
	overlay.alignX = "center";
	overlay.alignY = "middle";
	overlay.sort = 1;
	overlay.horzAlign = "fullscreen";
	overlay.vertAlign = "fullscreen";
	overlay.alpha = start_alpha;
	overlay.foreground = true;
	return overlay;
}