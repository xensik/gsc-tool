main()
{
	self endon( "death" );
	self endon( "stop_animmode" );
	self notify( "killanimscript" );
	self._tag_entity endon( self._anime );

	if ( isdefined( self._custom_anim_thread ) )
	{
		self thread [[ self._custom_anim_thread ]]();
		self._custom_anim_thread = undefined;
	}
	
	loop = isdefined( self._custom_anim_loop ) && self._custom_anim_loop;
	if ( loop )
	{
		self endon( "stop_loop" );
		self._custom_anim_loop = undefined;
	}
	else
	{
		thread notify_on_end( self._anime );
	}
	
	anime = self._anime;
	self._anime = undefined;
	
	arraySize = 0;
	if ( loop )
	{
		arraySize = level.scr_anim[ self._animname ][ anime ].size;
		animationName = level.scr_anim[ self._animname ][ anime ][ randomint( arraySize ) ];
	}
	else
	{
		animationName = level.scr_anim[ self._animname ][ anime ];
	}

	origin = getstartOrigin( self._tag_entity.origin, self._tag_entity.angles, animationName );
	angles = getstartAngles( self._tag_entity.origin, self._tag_entity.angles, animationName );

	newOrigin = self getDropToFloorPosition( origin );
	if ( isdefined( newOrigin ) )
		origin = newOrigin;
	else
		println( "Custom animation may be playing in solid for entity '" + self getentnum() + "'\n" );

	if ( !isdefined( self.noTeleport ) )
		self teleport( origin, angles );

	self.pushable = 0;

	clear_time = 0.3;
	blend_time = 0.2;

	if ( isdefined( self.anim_blend_time_override ) )
	{
		clear_time = self.anim_blend_time_override;
		blend_time = self.anim_blend_time_override;
	}
		 
	self animMode( self._animmode );
    self clearAnim( self.root_anim, clear_time );
    
//	self setAnim( %body, 1, 0 );	// The %body node should always have weight 1.
	self OrientMode( "face angle", angles[ 1 ] );

	anim_string = "custom_animmode";
	self setflaggedanimrestart( anim_string, animationName, 1, blend_time, 1 );
	self._tag_entity thread maps\_anim::start_notetrack_wait( self, anim_string, anime, self._animname );
	self._tag_entity thread maps\_anim::animscriptDoNoteTracksThread( self, anim_string, anime );

	//thread maps\_debug::drawArrowForever( self._tag_entity.origin, self._tag_entity.angles );

	tag_entity = self._tag_entity;
	self._tag_entity = undefined;
	self._animmode = undefined;

	self endon( "killanimscript" );
	
	endMarker = "end";
	
	if ( !loop ) 
	{
		if ( animHasNoteTrack( animationName, "finish" ) )
			endMarker = "finish";
		else if ( animHasNoteTrack( animationName, "stop anim" ) )
			endMarker = "stop anim";
	}
	
	while ( 1 )
	{
		self waittillmatch( anim_string, endMarker );
		
		if ( loop )
		{
			animationName = level.scr_anim[ self._animname ][ anime ][ randomint( arraySize ) ];
			self SetFlaggedAnimKnobLimitedRestart( anim_string, animationName, 1, 0.2, 1 );
			
			if ( isdefined( tag_entity ) )
			{
				tag_entity thread maps\_anim::start_notetrack_wait( self, anim_string, anime, self._animname );
				tag_entity thread maps\_anim::animscriptDoNoteTracksThread( self, anim_string, anime );
			}
		}
		else
		{
			break;
		}
	}
	
	if ( endMarker != "end" )
		self OrientMode( "face motion" );
	
	self notify( "finished_custom_animmode" + anime );
}

notify_on_end( msg )
{
	self endon( "death" );
	self endon( "finished_custom_animmode" + msg );

	self waittill( "killanimscript" );

	self notify( "finished_custom_animmode" + msg );
}