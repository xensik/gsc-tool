#include common_scripts\utility;

#using_animtree( "animated_props" );
main()
{
	//level.init_animatedmodels_dump = false;

	if ( !isdefined( level.anim_prop_models ) )
		level.anim_prop_models = []; // this is what the LD puts in their map

	// Do special MP anim precaching
	model_keys = GetArrayKeys( level.anim_prop_models );
	foreach ( model_key in model_keys )
	{
		anim_keys = GetArrayKeys( level.anim_prop_models[model_key] );
		foreach ( anim_key in anim_keys )
			PrecacheMpAnim( level.anim_prop_models[model_key][anim_key] );
			//PrecacheMpAnim( level.anim_prop_models[ "foliage_tree_palm_bushy_1" ][ "strong" ] );
	}

	// wait until the end of the frame so that maps can init their trees
	// in their _anim instead of only above _load
	waittillframeend;

	level.init_animatedmodels = [];

	animated_models = getentarray( "animated_model", "targetname" );
	//array_thread( animated_models, ::model_init );

	// one or more of the models initialized by model_init() was not setup by the map
	// so print this helpful note so the designer can see how to add it ot their level
	//if ( level.init_animatedmodels_dump )
		//assertmsg( "anims not cached for animated prop model, Repackage Zones and Rebuild Precache Script in Launcher:" );

	array_thread( animated_models, ::animateModel );

	level.init_animatedmodels = undefined;
}

// Disabled for now since we are precaching .animation prefabs in a non-standard way
/*model_init()
{
	if ( !isdefined( level.anim_prop_models[ self.model ] ) )
		level.init_animatedmodels_dump = true;
}*/

// TODO: When we have multiple animations, instead of choosing randomly, do round-robin to get an even spread
animateModel()
{
	if ( IsDefined( self.animation ) )
	{
		animation = self.animation;
	}
	else
	{
		keys = GetArrayKeys( level.anim_prop_models[ self.model ] );
		animkey = keys[ RandomInt( keys.size ) ];
		animation = level.anim_prop_models[ self.model ][ animkey ];
	}
	
	//wait( RandomFloatRange( 0, 5 ) ); // TODO: get a way to play animations at random starting points
	self ScriptModelPlayAnim( animation );
	self willNeverChange();
}