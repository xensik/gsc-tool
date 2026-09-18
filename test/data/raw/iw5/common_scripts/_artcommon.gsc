#include common_scripts\utility;

artStartVisionFileExport()
{
	fileprint_launcher_start_file();
}

artEndVisionFileExport()
{
	return fileprint_launcher_end_file( "\\share\\raw\\vision\\"+level.script+ ".vision", true );
}

artStartFogFileExport()
{
	fileprint_launcher_start_file();

}

artEndFogFileExport()
{
	return	fileprint_launcher_end_file( "\\share\\raw\\maps\\createart\\"+level.script+ "_art.gsc", true );
}

artCommonfxprintln( string )
{
	fileprint_launcher( string );
}


setfogsliders()
{
	/#
	fogcolor = getdvarvector( "g_fogColorReadOnly" );
	maxOpacity = GetDvar( "g_fogMaxOpacityReadOnly" );
	halfplane = GetDvar( "g_fogHalfDistReadOnly" );
	nearplane = GetDvar( "g_fogStartDistReadOnly" );

	sunFogEnabled = GetDvar( "g_sunFogEnabledReadOnly" );
	sunFogColor = getdvarvector( "g_sunFogColorReadOnly" );
	sunFogDir = getdvarvector( "g_sunFogDirReadOnly" );
	sunFogBeginFadeAngle = GetDvar( "g_sunFogBeginFadeAngleReadOnly" );
	sunFogEndFadeAngle = GetDvar( "g_sunFogEndFadeAngleReadOnly" );
	sunFogScale = GetDvar( "g_sunFogScaleReadOnly" );

	if ( !isdefined( fogcolor )
		 || !isdefined( maxOpacity )
		 || !isdefined( halfplane )
		 || !isdefined( nearplane )
		 || !isdefined( sunFogEnabled )
		 || !isdefined( sunFogColor )
		 || !isdefined( sunFogDir )
		 || !isdefined( sunFogBeginFadeAngle )
		 || !isdefined( sunFogEndFadeAngle )
		 || !isdefined( sunFogScale )
		 )
	{
		fogcolor = ( 1, 1, 1 );
		halfplane = 10000001;
		nearplane = 10000000;
		maxOpacity = 1;

		sunFogEnabled = false;
		sunFogColor = ( 1, 1, 1 );
		sunFogDir = ( 1.0, 0.0, 0.0 );
		sunFogBeginFadeAngle = GetDvar( "g_sunFogBeginFadeAngle" );
		sunFogEndFadeAngle = GetDvar( "g_sunFogEndFadeAngle" );
		sunFogScale = GetDvar( "g_sunFogScaleReadOnly" );

	}
	SetDevDvar( "scr_fog_exp_halfplane", halfplane );
	SetDevDvar( "scr_fog_nearplane", nearplane );
	SetDevDvar( "scr_fog_color", fogcolor );
	SetDevDvar( "scr_fog_max_opacity", maxOpacity );

	SetDevDvar( "scr_sunFogEnabled", sunFogEnabled );
	SetDevDvar( "scr_sunFogColor", sunFogColor );
	SetDevDvar( "scr_sunFogDir", sunFogDir );
	SetDevDvar( "scr_sunFogBeginFadeAngle", sunFogBeginFadeAngle );
	SetDevDvar( "scr_sunFogEndFadeAngle", sunFogEndFadeAngle );
	SetDevDvar( "scr_sunFogScale", sunFogScale );
	#/
}


translateFogSlidersToScript()
{
	level.fogexphalfplane = GetDvarFloat( "scr_fog_exp_halfplane" );
	level.fognearplane = GetDvarFloat( "scr_fog_nearplane" );
	level.fogcolor = getdvarvector( "scr_fog_color" );
	level.fogmaxopacity = GetDvarFloat( "scr_fog_max_opacity" );

	level.sunFogEnabled = GetDvarInt( "scr_sunFogEnabled" );
	level.sunFogColor = getdvarvector( "scr_sunFogColor" );
	level.sunFogDir = getdvarvector( "scr_sunFogDir" );
	level.sunFogBeginFadeAngle = GetDvarFloat( "scr_sunFogBeginFadeAngle" );
	level.sunFogEndFadeAngle = GetDvarFloat( "scr_sunFogEndFadeAngle" );
	level.sunFogScale = GetDvarFloat( "scr_sunFogScale" );
	
	
	// don't let the number get too small 1.10272e-005
	level.fogexphalfplane = limit( level.fogexphalfplane );
	level.fognearplane = limit( level.fognearplane );
	
	r = limit( level.fogcolor[0]);
	g = limit( level.fogcolor[1]);
	b = limit( level.fogcolor[2]);
	
	level.fogcolor = ( r, g , b );
	level.fogmaxopacity = limit( level.fogmaxopacity );

	level.sunFogEnabled = limit( level.sunFogEnabled );

	r = limit( level.sunFogColor[0]);
	g = limit( level.sunFogColor[1]);
	b = limit( level.sunFogColor[2]);

	level.sunFogColor =( r, g , b );
	
	x = limit( level.sunFogDir[0]);
	y = limit( level.sunFogDir[1]);
	z = limit( level.sunFogDir[2]);

	level.sunFogDir = (x,y,z);
	level.sunFogBeginFadeAngle = limit( level.sunFogBeginFadeAngle );
	level.sunFogEndFadeAngle= limit( level.sunFogEndFadeAngle );
	level.sunFogScale= limit( level.sunFogScale );
}

limit( i)
{
	limit = 0.001;
	if (i  < limit &&  i  > limit * - 1 )
		 i  = 0;
	return i;
}


updateFogFromScript()
{
	/#
	if ( GetDvarInt( "scr_cmd_plr_sun" ) )
	{
		SetDevDvar( "scr_sunFogDir", AnglesToForward( level.player GetPlayerAngles() ) );
		SetDevDvar( "scr_cmd_plr_sun", 0 );
	}

	#/

	if ( ! GetDvarInt( "scr_fog_disable" ) )
	{
		if ( level.sunFogEnabled )
			SetExpFog( level.fognearplane, level.fogexphalfplane, level.fogcolor[ 0 ], level.fogcolor[ 1 ], level.fogcolor[ 2 ], level.fogmaxopacity, 0, level.sunFogColor[ 0 ], level.sunFogColor[ 1 ], level.sunFogColor[ 2 ], level.sunFogDir, level.sunFogBeginFadeAngle, level.sunFogEndFadeAngle, level.sunFogScale );
		else
			SetExpFog( level.fognearplane, level.fogexphalfplane, level.fogcolor[ 0 ], level.fogcolor[ 1 ], level.fogcolor[ 2 ], level.fogmaxopacity, 0 );
	}
	else
	{
		SetExpFog( 100000000000, 100000000001, 0, 0, 0, 0, 0 );// couldn't find discreet fog disabling other than to never set it in the first place
	}
}


artfxprintlnFog()
{
	fileprint_launcher( "" );
	fileprint_launcher( "\t//* Fog section * " );
	fileprint_launcher( "" );

	fileprint_launcher( "\tsetDevDvar( \"scr_fog_disable\"" + ", " + "\"" + GetDvarInt( "scr_fog_disable" ) + "\"" + " );" );

	fileprint_launcher( "" );
	if ( ! GetDvarInt( "scr_fog_disable" ) )
	{
		if ( level.sunFogEnabled )
			fileprint_launcher( "\tsetExpFog( " + level.fognearplane + ", " + level.fogexphalfplane + ", " + level.fogcolor[0] + ", " + level.fogcolor[1] + ", " + level.fogcolor[2] + ", " + level.fogmaxopacity + ", 0, " + level.sunFogColor[0] + ", " + level.sunFogColor[1] + ", " + level.sunFogColor[2] + ", (" + level.sunFogDir[0] + ", " + level.sunFogDir[1] + ", " + level.sunFogDir[2] + "), " + level.sunFogBeginFadeAngle + ", " + level.sunFogEndFadeAngle + ", " + level.sunFogScale + " );" );
		else
			fileprint_launcher( "\tsetExpFog( " + level.fognearplane + ", " + level.fogexphalfplane + ", " + level.fogcolor[0] + ", " + level.fogcolor[1] + ", " + level.fogcolor[2] + ", " + level.fogmaxopacity + ", 0 );" );
	}
}

