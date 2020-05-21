#include maps\mp\_utility;

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
	self.children[self.children.size] = element;
}

removeChild( element )
{
	element.parent = undefined;

	if ( self.children[self.children.size-1] != element )
	{
		self.children[element.index] = self.children[self.children.size-1];
		self.children[element.index].index = element.index;
	}
	self.children[self.children.size-1] = undefined;
	
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

	relativeX = "center_adjustable";
	relativeY = "middle";

	if ( isSubStr( relativePoint, "TOP" ) )
		relativeY = "top_adjustable";
	if ( isSubStr( relativePoint, "BOTTOM" ) )
		relativeY = "bottom_adjustable";
	if ( isSubStr( relativePoint, "LEFT" ) )
		relativeX = "left_adjustable";
	if ( isSubStr( relativePoint, "RIGHT" ) )
		relativeX = "right_adjustable";

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


	if ( strip_suffix( relativeX, "_adjustable" ) == element.alignX )
	{
		offsetX = 0;
		xFactor = 0;
	}
	else if ( relativeX == "center" || element.alignX == "center" )
	{
		offsetX = int(element.width / 2);
		if ( relativeX == "left_adjustable" || element.alignX == "right" )
			xFactor = -1;
		else
			xFactor = 1;	
	}
	else
	{
		offsetX = element.width;
		if ( relativeX == "left_adjustable" )
			xFactor = -1;
		else
			xFactor = 1;
	}
	self.x = element.x + (offsetX * xFactor);

	if ( strip_suffix( relativeY, "_adjustable" ) == element.alignY )
	{
		offsetY = 0;
		yFactor = 0;
	}
	else if ( relativeY == "middle" || element.alignY == "middle" )
	{
		offsetY = int(element.height / 2);
		if ( relativeY == "top_adjustable" || element.alignY == "bottom" )
			yFactor = -1;
		else
			yFactor = 1;	
	}
	else
	{
		offsetY = element.height;
		if ( relativeY == "top_adjustable" )
			yFactor = -1;
		else
			yFactor = 1;
	}
	self.y = element.y + (offsetY * yFactor);
	
	self.x += self.xOffset;
	self.y += self.yOffset;
	
	switch ( self.elemType )
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
		self.bar.x = self.x;
	else if ( self.alignX == "right" )
		self.bar.x = self.x - self.width;
	else
		self.bar.x = self.x - int(self.width / 2);
	
	if ( self.alignY == "top" )
		self.bar.y = self.y;
	else if ( self.alignY == "bottom" )
		self.bar.y = self.y;

	self updateBar( self.bar.frac );
}


updateBar( barFrac, rateOfChange )
{
	if ( self.elemType == "bar" )
		updateBarScale( barFrac, rateOfChange );
}


updateBarScale( barFrac, rateOfChange ) // rateOfChange is optional and is in "(entire bar lengths) per second"
{
	barWidth = int(self.width * barFrac + 0.5); // (+ 0.5 rounds)
	
	if ( !barWidth )
		barWidth = 1;
	
	self.bar.frac = barFrac;
	self.bar setShader( self.bar.shader, barWidth, self.height );
	
	assertEx( barWidth <= self.width, "barWidth <= self.width: " + barWidth + " <= " + self.width + " - barFrac was " + barFrac );
	
	//if barWidth is bigger than self.width then we are drawing more than 100%
	if ( isDefined( rateOfChange ) && barWidth < self.width ) 
	{
		if ( rateOfChange > 0 )
		{
			//printLn( "scaling from: " + barWidth + " to " + self.width + " at " + ((1 - barFrac) / rateOfChange) );
			assertex( ((1 - barFrac) / rateOfChange) > 0, "barFrac: " + barFrac + "rateOfChange: " + rateOfChange );
			self.bar scaleOverTime( (1 - barFrac) / rateOfChange, self.width, self.height );
		}
		else if ( rateOfChange < 0 )
		{
			//printLn( "scaling from: " + barWidth + " to " + 0 + " at " + (barFrac / (-1 * rateOfChange)) );
			assertex(  (barFrac / (-1 * rateOfChange)) > 0, "barFrac: " + barFrac + "rateOfChange: " + rateOfChange );
			self.bar scaleOverTime( barFrac / (-1 * rateOfChange), 1, self.height );
		}
	}
	self.bar.rateOfChange = rateOfChange;
	self.bar.lastUpdateTime = getTime();
}


createFontString( font, fontScale )
{
	fontElem = newClientHudElem( self );
	fontElem.elemType = "font";
	fontElem.font = font;
	fontElem.fontscale = fontScale;
	fontElem.baseFontScale = fontScale;
	fontElem.x = 0;
	fontElem.y = 0;
	fontElem.width = 0;
	fontElem.height = int(level.fontHeight * fontScale);
	fontElem.xOffset = 0;
	fontElem.yOffset = 0;
	fontElem.children = [];
	fontElem setParent( level.uiParent );
	fontElem.hidden = false;
	return fontElem;
}


createServerFontString( font, fontScale, team )
{
	if ( isDefined( team ) )
		fontElem = newTeamHudElem( team );
	else
		fontElem = newHudElem();
	
	fontElem.elemType = "font";
	fontElem.font = font;
	fontElem.fontscale = fontScale;
	fontElem.baseFontScale = fontScale;
	fontElem.x = 0;
	fontElem.y = 0;
	fontElem.width = 0;
	fontElem.height = int(level.fontHeight * fontScale);
	fontElem.xOffset = 0;
	fontElem.yOffset = 0;
	fontElem.children = [];
	fontElem setParent( level.uiParent );
	fontElem.hidden = false;
	
	return fontElem;
}

createServerTimer( font, fontScale, team )
{	
	if ( isDefined( team ) )
		timerElem = newTeamHudElem( team );
	else
		timerElem = newHudElem();
	timerElem.elemType = "timer";
	timerElem.font = font;
	timerElem.fontScale = fontScale;
	timerElem.baseFontScale = fontScale;
	timerElem.x = 0;
	timerElem.y = 0;
	timerElem.width = 0;
	timerElem.height = int(level.fontHeight * fontScale);
	timerElem.xOffset = 0;
	timerElem.yOffset = 0;
	timerElem.children = [];
	timerElem setParent( level.uiParent );
	timerElem.hidden = false;
	
	return timerElem;
}


createTimer( font, fontScale )
{	
	timerElem = newClientHudElem( self );
	timerElem.elemType = "timer";
	timerElem.font = font;
	timerElem.fontScale = fontScale;
	timerElem.baseFontScale = fontScale;
	timerElem.x = 0;
	timerElem.y = 0;
	timerElem.width = 0;
	timerElem.height = int(level.fontHeight * fontScale);
	timerElem.xOffset = 0;
	timerElem.yOffset = 0;
	timerElem.children = [];
	timerElem setParent( level.uiParent );
	timerElem.hidden = false;
	
	return timerElem;
}


createIcon( shader, width, height )
{
	iconElem = newClientHudElem( self );
	iconElem.elemType = "icon";
	iconElem.x = 0;
	iconElem.y = 0;
	iconElem.width = width;
	iconElem.height = height;
	iconElem.baseWidth = iconElem.width;
	iconElem.baseHeight = iconElem.height;
	iconElem.xOffset = 0;
	iconElem.yOffset = 0;
	iconElem.children = [];
	iconElem setParent( level.uiParent );
	iconElem.hidden = false;
	
	if ( isDefined( shader ) )
	{
		iconElem setShader( shader, width, height );
		iconElem.shader = shader;
	}
	
	return iconElem;
}


createServerIcon( shader, width, height, team )
{
	if ( isDefined( team ) )
		iconElem = newTeamHudElem( team );
	else
		iconElem = newHudElem();
	iconElem.elemType = "icon";
	iconElem.x = 0;
	iconElem.y = 0;
	iconElem.width = width;
	iconElem.height = height;
	iconElem.baseWidth = iconElem.width;
	iconElem.baseHeight = iconElem.height;
	iconElem.xOffset = 0;
	iconElem.yOffset = 0;
	iconElem.children = [];
	iconElem setParent( level.uiParent );
	iconElem.hidden = false;
	
	if ( isDefined( shader ) )
	{
		iconElem setShader( shader, width, height );
		iconElem.shader = shader;
	}
	
	return iconElem;
}


createServerBar( color, width, height, flashFrac, team, selected )
{
	if ( isDefined( team ) )
		barElem = newTeamHudElem( team );
	else
		barElem = newHudElem();
	barElem.x = 0;
	barElem.y = 0;
	barElem.frac = 0;
	barElem.color = color;
	barElem.sort = -2;
	barElem.shader = "progress_bar_fill";
	barElem setShader( "progress_bar_fill", width, height );
	barElem.hidden = false;
	if ( isDefined( flashFrac ) )
	{
		barElem.flashFrac = flashFrac;
//		barElem thread flashThread();
	}

	if ( isDefined( team ) )
		barElemBG = newTeamHudElem( team );
	else
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
	barElemBG.sort = -3;
	barElemBG.color = (0,0,0);
	barElemBG.alpha = 0.5;
	barElemBG setParent( level.uiParent );
	barElemBG setShader( "progress_bar_bg", width, height );
	barElemBG.hidden = false;
	
	return barElemBG;
}

createBar( color, width, height, flashFrac )
{
	barElem = newClientHudElem(	self );
	barElem.x = 0 ;
	barElem.y = 0;
	barElem.frac = 0;
	barElem.color = color;
	barElem.sort = -2;
	barElem.shader = "progress_bar_fill";
	barElem setShader( "progress_bar_fill", width, height );
	barElem.hidden = false;
	if ( isDefined( flashFrac ) )
	{
		barElem.flashFrac = flashFrac;
//		barElem thread flashThread();
	}
	
	barElemBG = newClientHudElem( self );
	barElemBG.elemType = "bar";
	barElemBG.width = width;
	barElemBG.height = height;
	barElemBG.xOffset = 0;
	barElemBG.yOffset = 0;
	barElemBG.bar = barElem;
	barElemBG.children = [];
	barElemBG.sort = -3;
	barElemBG.color = (0,0,0);
	barElemBG.alpha = 0.5;
	barElemBG setParent( level.uiParent );
	barElemBG setShader( "progress_bar_bg", width + 4, height + 4 );
	barElemBG.hidden = false;
	
	return barElemBG;
}

getCurrentFraction()
{
	frac = self.bar.frac;
	if (isdefined(self.bar.rateOfChange))
	{
		frac += (getTime() - self.bar.lastUpdateTime) * self.bar.rateOfChange;
		if (frac > 1) frac = 1;
		if (frac < 0) frac = 0;
	}
	return frac;
}

createPrimaryProgressBar( xOffset, yOffset )
{
	if ( !isDefined( xOffset ) )
		xOffset = 0;
	if ( !isDefined( yOffset ) )
		yOffset = 0;
		
	bar = createBar( (1, 1, 1), level.primaryProgressBarWidth, level.primaryProgressBarHeight );
	bar setPoint("CENTER", undefined, level.primaryProgressBarX + xOffset, level.primaryProgressBarY + yOffset );

	return bar;
}
createPrimaryProgressBarText( xOffset, yOffset )
{
	if ( !isDefined( xOffset ) )
		xOffset = 0;
	if ( !isDefined( yOffset ) )
		yOffset = 0;
		
	text = createFontString( "hudbig", level.primaryProgressBarFontSize );
	text setPoint("CENTER", undefined, level.primaryProgressBarTextX + xOffset, level.primaryProgressBarTextY + yOffset );
	text.sort = -1;
	return text;
}


createTeamProgressBar( team )
{
	bar = createServerBar( (1,0,0), level.teamProgressBarWidth, level.teamProgressBarHeight, undefined, team );
	bar setPoint("TOP", undefined, 0, level.teamProgressBarY);
	return bar;
}
createTeamProgressBarText( team )
{
	text = createServerFontString( "default", level.teamProgressBarFontSize, team );
	text setPoint("TOP", undefined, 0, level.teamProgressBarTextY);
	return text;
}


setFlashFrac( flashFrac )
{
	self.bar.flashFrac = flashFrac;
}

hideElem()
{
	if ( self.hidden )
		return;
		
	self.hidden = true;

	if ( self.alpha != 0 )
		self.alpha = 0;
	
	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		self.bar.hidden = true;
		if ( self.bar.alpha != 0 )
			self.bar.alpha = 0;
	}
}

showElem()
{
	if ( !self.hidden )
		return;
		
	self.hidden = false;

	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		if ( self.alpha != .5 )
			self.alpha = .5;
		
		self.bar.hidden = false;
		if ( self.bar.alpha != 1 )
			self.bar.alpha = 1;

	}
	else
	{
		if ( self.alpha != 1 )
			self.alpha = 1;
	}
}


flashThread()
{
	self endon ( "death" );

	if ( !self.hidden )
		self.alpha = 1;
		
	while(1)
	{
		if ( self.frac >= self.flashFrac )
		{
			if ( !self.hidden )
			{
				self fadeOverTime(0.3);
				self.alpha = .2;
				wait(0.35);
				self fadeOverTime(0.3);
				self.alpha = 1;
			}
			wait(0.7);
		}
		else
		{
			if ( !self.hidden && self.alpha != 1 )
				self.alpha = 1;

			wait ( 0.05 );
		}
	}
}


destroyElem()
{
	tempChildren = [];

	for ( index = 0; index < self.children.size; index++ )
	{
		if ( isDefined( self.children[index] ) )
			tempChildren[tempChildren.size] = self.children[index];
	}

	for ( index = 0; index < tempChildren.size; index++ )
		tempChildren[index] setParent( self getParent() );
		
	if ( self.elemType == "bar" || self.elemType == "bar_shader" )
	{
		self.bar destroy();
	}
		
	self destroy();
}

setIconShader( shader )
{
	self setShader( shader, self.width, self.height );
	self.shader = shader;
}


getIconShader( shader )
{
	return self.shader;
}


setIconSize( width, height )
{
	assert( isDefined( self.shader ) );
	
	self setShader( self.shader, width, height );
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
		child = self.children[index];
		child setPoint( child.point, child.relativePoint, child.xOffset, child.yOffset );
	}
}



transitionReset()
{
	self.x = self.xOffset;
	self.y = self.yOffset;
	if ( self.elemType == "font" )
	{
		self.fontScale = self.baseFontScale;
		self.label = &"";
	}
	else if ( self.elemType == "icon" )
	{
		//self scaleOverTime( 0.001, self.width, self.height );
		self setShader( self.shader, self.width, self.height );
	}	
	self.alpha = 0;
}


transitionZoomIn( duration )
{
	switch ( self.elemType )
	{
		case "font":
		case "timer":
			self.fontScale = 6.3;
			self changeFontScaleOverTime( duration );
			self.fontScale = self.baseFontScale;
			break;
		case "icon":
			self setShader( self.shader, self.width * 6, self.height * 6 );
			self scaleOverTime( duration, self.width, self.height );
			break;
	}
}


transitionPulseFXIn( inTime, duration )
{
	transTime = int(inTime)*1000;
	showTime = int(duration)*1000;
	
	switch ( self.elemType )
	{
		case "font":
		case "timer":
			self setPulseFX( transTime+250, showTime+transTime, transTime+250 );
			break;
		default:
			break;
	}
}


transitionSlideIn( duration, direction )
{
	if ( !isDefined( direction ) )
		direction = "left";

	switch ( direction )
	{
		case "left":
			self.x += 1000;
			break;
		case "right":
			self.x -= 1000;
			break;
		case "up":
			self.y -= 1000;
			break;
		case "down":
			self.y += 1000;
			break;		
	}
	self moveOverTime( duration );
	self.x = self.xOffset;
	self.y = self.yOffset;
}


transitionSlideOut( duration, direction )
{
	if ( !isDefined( direction ) )
		direction = "left";

	gotoX = self.xOffset;
	gotoY = self.yOffset;

	switch ( direction )
	{
		case "left":
			gotoX += 1000;
			break;
		case "right":
			gotoX -= 1000;
			break;
		case "up":
			gotoY -= 1000;
			break;
		case "down":
			gotoY += 1000;
			break;		
	}

	self.alpha = 1;
	
	self moveOverTime( duration );
	self.x = gotoX;
	self.y = gotoY;
}


transitionZoomOut( duration )
{
	switch ( self.elemType )
	{
		case "font":
		case "timer":
			self changeFontScaleOverTime( duration );
			self.fontScale = 6.3;
		case "icon":
			self scaleOverTime( duration, self.width * 6, self.height * 6 );
			break;
	}
}


transitionFadeIn( duration )
{
	self fadeOverTime( duration );
	if ( isDefined( self.maxAlpha ) )
		self.alpha = self.maxAlpha;
	else
		self.alpha = 1;
}


transitionFadeOut( duration )
{
	self fadeOverTime( 0.15 );
	self.alpha = 0;
}

getWeeklyRef( chRef )
{
	for ( chIndex = 0; chIndex < 3; chIndex++ )
	{
		weeklyId = self getPlayerData( "weeklyChallengeId", chIndex );
		weeklyRef = tableLookupByRow( "mp/weeklyChallengesTable.csv", weeklyId, 0 );
		
		if ( weeklyRef == chRef )
			return "ch_weekly_" + chIndex;
	}
	
	return "";
}

getDailyRef( chRef )
{
	for ( chIndex = 0; chIndex < 3; chIndex++ )
	{
		dailyId = self getPlayerData( "dailyChallengeId", chIndex );
		dailyRef = tableLookupByRow( "mp/dailyChallengesTable.csv", dailyId, 0 );
		
		if ( dailyRef == chRef )
			return "ch_daily_" + chIndex;
	}
	
	return "";
}

ch_getProgress( refString )
{
	if ( level.challengeInfo[refString]["type"] == 0 )
		return self getPlayerData( "challengeProgress", refString );
	//*else if ( level.challengeInfo[refString]["type"] == 1 )
	//*	return self getPlayerData( "challengeProgress", getDailyRef( refString ) );
	//*else if ( level.challengeInfo[refString]["type"] == 2 )
	//*	return self getPlayerData( "challengeProgress", getWeeklyRef( refString ) );
}


ch_getState( refString )
{
	if ( level.challengeInfo[refString]["type"] == 0 )
		return self getPlayerData( "challengeState", refString );
	//*else if ( level.challengeInfo[refString]["type"] == 1 )
	//*	return self getPlayerData( "challengeState", getDailyRef( refString ) );
	//*else if ( level.challengeInfo[refString]["type"] == 2 )
	//*	return self getPlayerData( "challengeState", getWeeklyRef( refString ) );
}


ch_setProgress( refString, value )
{
	if ( level.challengeInfo[refString]["type"] == 0 )
		return self setPlayerData( "challengeProgress", refString, value );
	//*else if ( level.challengeInfo[refString]["type"] == 1 )
	//*	return self setPlayerData( "challengeProgress", getDailyRef( refString ), value );
	//*else if ( level.challengeInfo[refString]["type"] == 2 )
	//*	return self setPlayerData( "challengeProgress", getWeeklyRef( refString ), value );
}


ch_setState( refString, value )
{
	if ( level.challengeInfo[refString]["type"] == 0 )
		return self setPlayerData( "challengeState", refString, value );
	//*else if ( level.challengeInfo[refString]["type"] == 1 )
	//*	return self setPlayerData( "challengeState", getDailyRef( refString ), value );
	//*else if ( level.challengeInfo[refString]["type"] == 2 )
	//*	return self setPlayerData( "challengeState", getWeeklyRef( refString ), value );
}

ch_getTarget( refString, state )
{
	if ( level.challengeInfo[refString]["type"] == 0 )
		return int( tableLookup( "mp/allChallengesTable.csv", 0, refString, 6 + ((state-1)*2) ) );
	//*else if ( level.challengeInfo[refString]["type"] == 1 )
	//*	return int( tableLookup( "mp/dailyChallengesTable.csv", 0, refString, 6 + ((state-1)*2) ) );
	//*else if ( level.challengeInfo[refString]["type"] == 2 )
	//*	return int( tableLookup( "mp/weeklyChallengesTable.csv", 0, refString, 6 + ((state-1)*2) ) );
}