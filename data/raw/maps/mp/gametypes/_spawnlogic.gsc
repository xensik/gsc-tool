#include common_scripts\utility;
#include maps\mp\_utility;

findBoxCenter( mins, maxs )
{
	center = ( 0, 0, 0 );
	center = maxs - mins;
	center = ( center[0]/2, center[1]/2, center[2]/2 ) + mins;
	return center;
}

expandMins( mins, point )
{
	if ( mins[0] > point[0] )
		mins = ( point[0], mins[1], mins[2] );
	if ( mins[1] > point[1] )
		mins = ( mins[0], point[1], mins[2] );
	if ( mins[2] > point[2] )
		mins = ( mins[0], mins[1], point[2] );
	return mins;
}

expandMaxs( maxs, point )
{
	if ( maxs[0] < point[0] )
		maxs = ( point[0], maxs[1], maxs[2] );
	if ( maxs[1] < point[1] )
		maxs = ( maxs[0], point[1], maxs[2] );
	if ( maxs[2] < point[2] )
		maxs = ( maxs[0], maxs[1], point[2] );
	return maxs;
}


addSpawnPoints( team, spawnPointName, isSetOptional )
{
	if ( !isDefined( isSetOptional ) )
		isSetOptional = false;
	
	oldSpawnPoints = [];
	if ( level.teamSpawnPoints[team].size )
		oldSpawnPoints = level.teamSpawnPoints[team];
	
	level.teamSpawnPoints[team] = getSpawnpointArray( spawnPointName );
	
	if ( !level.teamSpawnPoints[team].size && !isSetOptional )
	{
		println( "^1Error: No " + spawnPointName + " spawnpoints found in level!" );
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		wait 1; // so we don't try to abort more than once before the frame ends
		return;
	}
	
	if ( !isDefined( level.spawnpoints ) )
		level.spawnpoints = [];
	
	for ( index = 0; index < level.teamSpawnPoints[team].size; index++ )
	{
		spawnpoint = level.teamSpawnPoints[team][index];
		
		if ( !isdefined( spawnpoint.inited ) )
		{
			spawnpoint spawnPointInit();
			level.spawnpoints[ level.spawnpoints.size ] = spawnpoint;
		}
	}
	
	for ( index = 0; index < oldSpawnPoints.size; index++ )
	{
		origin = oldSpawnPoints[index].origin;
		
		// are these 2 lines necessary? we already did it in spawnPointInit
		level.spawnMins = expandMins( level.spawnMins, origin );
		level.spawnMaxs = expandMaxs( level.spawnMaxs, origin );
		
		level.teamSpawnPoints[team][ level.teamSpawnPoints[team].size ] = oldSpawnPoints[index];
	}
}

placeSpawnPoints( spawnPointName )
{
	spawnPoints = getSpawnpointArray( spawnPointName );
	
	/#
	if ( !isDefined( level.extraspawnpointsused ) )
		level.extraspawnpointsused = [];
	#/
	
	if ( !spawnPoints.size )
	{
		println( "^1Error: No " + spawnPointName + " spawnpoints found in level!" );
		maps\mp\gametypes\_callbacksetup::AbortLevel();
		wait 1; // so we don't try to abort more than once before the frame ends
		return;
	}
	
	if ( !isDefined( level.startSpawnPoints ) )
		level.startSpawnPoints = [];

	for( index = 0; index < spawnPoints.size; index++ )
	{
		spawnPoints[index] spawnPointInit();
		// don't add this spawnpoint to level.spawnpoints,
		// because it's an unimportant one that we don't want to do sight traces to
		
		// but we do want another array of spawnpoints for the uav in S&D
		level.startSpawnPoints[ level.startSpawnPoints.size ] = spawnPoints[index];

		/#
		spawnPoints[index].fakeclassname = spawnPointName;
		level.extraspawnpointsused[ level.extraspawnpointsused.size ] = spawnPoints[index];
		#/
	}
}

getSpawnpointArray( classname )
{
	spawnPoints = getEntArray( classname, "classname" );
	
	if ( !isdefined( level.extraspawnpoints ) || !isdefined( level.extraspawnpoints[classname] ) )
		return spawnPoints;
	
	for ( i = 0; i < level.extraspawnpoints[classname].size; i++ )
	{
		spawnPoints[ spawnPoints.size ] = level.extraspawnpoints[classname][i];
	}
	
	return spawnPoints;
}

expandSpawnpointBounds( classname )
{
	spawnPoints = getSpawnpointArray( classname );
	for( index = 0; index < spawnPoints.size; index++ )
	{
		level.spawnMins = expandMins( level.spawnMins, spawnPoints[index].origin );
		level.spawnMaxs = expandMaxs( level.spawnMaxs, spawnPoints[index].origin );
	}
}

setMapCenterForReflections()
{
	level.spawnMins = (0,0,0);
	level.spawnMaxs = (0,0,0);
	
	maps\mp\gametypes\_spawnlogic::expandSpawnpointBounds( "mp_tdm_spawn_allies_start" );
	maps\mp\gametypes\_spawnlogic::expandSpawnpointBounds( "mp_tdm_spawn_axis_start" );
	level.mapCenter = maps\mp\gametypes\_spawnlogic::findBoxCenter( level.spawnMins, level.spawnMaxs );
	setMapCenter( level.mapCenter );
}

// initspawnpoint()
spawnPointInit()
{
	spawnpoint = self;
	origin = spawnpoint.origin;
	
	level.spawnMins = expandMins( level.spawnMins, origin );
	level.spawnMaxs = expandMaxs( level.spawnMaxs, origin );
	
	spawnpoint placeSpawnpoint();
	spawnpoint.forward = anglesToForward( spawnpoint.angles );
	spawnpoint.sightTracePoint = spawnpoint.origin + (0,0,50);
	
	spawnpoint.lastspawnedplayer = spawnpoint; // just want this to be any entity for which isalive() returns false
	spawnpoint.lastspawntime = gettime();
	
	skyHeight = 1024;
	spawnpoint.outside = true;
	if ( !bullettracepassed( spawnpoint.sightTracePoint, spawnpoint.sightTracePoint + (0,0,skyHeight), false, undefined) )
	{
		startpoint = spawnpoint.sightTracePoint + spawnpoint.forward * 100;
		if ( !bullettracepassed( startpoint, startpoint + (0,0,skyHeight), false, undefined) )
			spawnpoint.outside = false;
	}
	
	right = anglesToRight( spawnpoint.angles );
	spawnpoint.alternates = [];
	AddAlternateSpawnpoint( spawnpoint, spawnpoint.origin + right * 45 );
	AddAlternateSpawnpoint( spawnpoint, spawnpoint.origin - right * 45 );
	//AddAlternateSpawnpoint( spawnpoint, spawnpoint.origin + spawnpoint.forward * 45 );
	
	/*
	spawnpoint.secondFloor = false;
	if ( isDefined( level.spawnSecondFloorTrig ) )
	{
		spawnpoint.secondFloor = (spawnpoint isTouching( level.spawnSecondFloorTrig ));
		
		spawnpoint.floorTransitionDistances = [];
		
		for ( pointIndex = 0; pointIndex < level.spawnFloorTransitions.size; pointIndex++ )
		{
			spawnpoint.floorTransitionDistances[ pointIndex ] = distance( level.spawnFloorTransitions[ pointIndex ], spawnpoint.origin );
		}
	}
	*/
	
	spawnPointUpdate( spawnpoint );
	
	spawnpoint.inited = true;
}

AddAlternateSpawnpoint( spawnpoint, alternatepos )
{
	spawnpointposRaised = playerPhysicsTrace( spawnpoint.origin, spawnpoint.origin + (0,0,18), false, undefined );
	zdiff = spawnpointposRaised[2] - spawnpoint.origin[2];
	
	alternateposRaised = (alternatepos[0], alternatepos[1], alternatepos[2] + zdiff );
	
	traceResult = playerPhysicsTrace( spawnpointposRaised, alternateposRaised, false, undefined );
	if ( traceResult != alternateposRaised )
		return;
	
	finalAlternatePos = playerPhysicsTrace( alternateposRaised, alternatepos );
	
	spawnpoint.alternates[ spawnpoint.alternates.size ] = finalAlternatePos;
}


getTeamSpawnPoints( team )
{
	return level.teamSpawnPoints[team];
}

// selects a spawnpoint, preferring ones with heigher weights (or toward the beginning of the array if no weights).
// also does final things like setting self.lastspawnpoint to the one chosen.
// this takes care of avoiding telefragging, so it doesn't have to be considered by any other function.
getSpawnpoint_Final( spawnpoints, useweights )
{
	prof_begin( "spawn_final" );
	
	bestspawnpoint = undefined;
	
	if ( !isdefined( spawnpoints ) || spawnpoints.size == 0 )
		return undefined;
	
	if ( !isdefined( useweights ) )
		useweights = true;
	
	if ( useweights )
	{
		// choose spawnpoint with best weight
		// (if a tie, choose randomly from the best)
		bestspawnpoint = getBestWeightedSpawnpoint( spawnpoints );
		/#
		thread spawnWeightDebug( spawnpoints, bestspawnpoint );
		#/
	}
	else
	{
		carePackages = getEntArray( "care_package", "targetname" );
		// (only place we actually get here from is getSpawnpoint_Random() )
		// no weights. prefer spawnpoints toward beginning of array
		for ( i = 0; i < spawnpoints.size; i++ )
		{
			if( isdefined( self.lastspawnpoint ) && self.lastspawnpoint == spawnpoints[i] )
				continue;
			
			if ( positionWouldTelefrag( spawnpoints[i].origin ) )
				continue;
			
			if ( carePackages.size && !canSpawn( spawnpoints[i].origin ) )
				continue;
			
			bestspawnpoint = spawnpoints[i];
			break;
		}
		if ( !isdefined( bestspawnpoint ) )
		{
			// Couldn't find a useable spawnpoint. All spawnpoints either telefragged or were our last spawnpoint
			// Our only hope is our last spawnpoint - unless it too will telefrag...
			if ( isdefined( self.lastspawnpoint ) && !positionWouldTelefrag( self.lastspawnpoint.origin ) )
			{
				// (make sure our last spawnpoint is in the valid array of spawnpoints to use)
				for ( i = 0; i < spawnpoints.size; i++ )
				{
					if ( spawnpoints[i] == self.lastspawnpoint )
					{
						bestspawnpoint = spawnpoints[i];
						break;
					}
				}
			}
		}
	}
	
	if ( !isdefined( bestspawnpoint ) )
	{
		// couldn't find a useable spawnpoint! all will telefrag.
		if ( useweights )
		{
			// at this point, forget about weights. just take a random one.
			bestspawnpoint = spawnpoints[randomint(spawnpoints.size)];
			
			/#
			
			#/
		}
		else
		{
			bestspawnpoint = spawnpoints[0];
		}
	}
	
	prof_end( "spawn_final" );

	return bestspawnpoint;
}

finalizeSpawnpointChoice( spawnpoint )
{
	time = getTime();
	
	self.lastspawnpoint = spawnpoint;
	self.lastspawntime = time;
	spawnpoint.lastspawnedplayer = self;
	spawnpoint.lastspawntime = time;
}

maxSightTracedSpawnpoints = 3;

getBestWeightedSpawnpoint( spawnpoints )
{
	otherteam = getOtherTeam( self.team );
	
	assert( spawnpoints.size > 0 );

	for ( try = 0; ; try++ )
	{
		bestspawnpoints = [];
		bestspawnpoints[0] = spawnpoints[0];
		bestweight = spawnpoints[0].weight;
		for ( i = 1; i < spawnpoints.size; i++ )
		{
			spawnpoint = spawnpoints[i];
			if ( spawnpoint.weight > bestweight ) 
			{
				bestspawnpoints = [];
				bestspawnpoints[0] = spawnpoint;
				bestweight = spawnpoint.weight;
			}
			else if ( spawnpoint.weight == bestweight ) 
			{
				bestspawnpoints[bestspawnpoints.size] = spawnpoint;
			}
		}
		
		// pick randomly from the available spawnpoints with the best weight
		assert( bestspawnpoints.size > 0 );
		bestspawnpoint = bestspawnpoints[randomint( bestspawnpoints.size )];
		
		if ( try >= maxSightTracedSpawnpoints )
		{
			println( "Spawning " + self.name + " at spawnpoint " + bestspawnpoint.origin + " because the " + maxSightTracedSpawnpoints + " best spawnpoints failed last minute sight trace tests." );
			/# DumpSpawnData( spawnpoints, bestspawnpoint ); #/
			return bestspawnpoint;
		}
		
		// if we already know that this spawnpoint has sight lines to the enemy team, and it's still the best we've got, there's no point doing more traces.
		sights = 0;
		if ( level.teambased )
			sights = bestspawnpoint.sights[otherteam];
		else
			sights = bestspawnpoint.sights;
		
		if ( sights > 0 )
		{
			println( "Spawning " + self.name + " at spawnpoint " + bestspawnpoint.origin + " even though " + sights + " lines of sight to the enemy exist." );
			/# DumpSpawnData( spawnpoints, bestspawnpoint ); #/
			return bestspawnpoint;
		}
		
		if ( isdefined( bestspawnpoint.lastSightTraceTime ) && bestspawnpoint.lastSightTraceTime == gettime() )
			return bestspawnpoint;
		
		sightValue = lastMinuteSightTraces( bestspawnpoint );
		if ( sightValue == 0 )
			return bestspawnpoint;
		
		sightValue = adjustSightValue( sightvalue );
		if ( level.teambased )
			bestspawnpoint.sights[otherteam] += sightValue;
		else
			bestspawnpoint.sights += sightValue;
		
		penalty = getLosPenalty() * sightValue;
		/#
		bestspawnpoint.spawnData[bestspawnpoint.spawnData.size] = "Last minute sight trace: -" + penalty;
		#/
		bestspawnpoint.weight -= penalty;
		
		bestspawnpoint.lastSightTraceTime = gettime();
	}
	assertmsg( "can't get here" );
}

/#

DumpSpawnData( spawnpoints, winnerspawnpoint )
{
	if ( getSubStr( self.name, 0, 3 ) == "bot" )
	{
		if ( getdvarint("scr_spawnpointdebug") == 0 )
			return;
	}
	
	println( "=================================" );
	println( "spawndata = spawnstruct();" );
	println( "spawndata.playername = \"" + self.name + "\";" );
	println( "spawndata.friends = [];" );
	println( "spawndata.enemies = [];" );
	foreach ( player in level.players )
	{
		if ( player.team == self.team )
			println( "spawndata.friends[ spawndata.friends.size ] = " + player.origin + ";" );
		else
			println( "spawndata.enemies[ spawndata.enemies.size ] = " + player.origin + ";" );
	}
	println( "spawndata.otherdata = [];" );
	
	println( "spawndata.spawnpoints = [];" );
	index = 0;
	foreach ( spawnpoint in spawnpoints )
	{
		if ( spawnpoint == winnerspawnpoint )
			println( "spawndata.spawnpointwinner = " + index + ";" );
		
		println( "spawnpoint = spawnstruct();" );
		println( "spawnpoint.weight = " + spawnpoint.weight + ";" );
		println( "spawnpoint.origin = " + spawnpoint.origin + ";" );
		println( "spawnpoint.spawndata = [];" );
		for ( i = 0; i < spawnpoint.spawndata.size; i++ )
		{
			println( "spawnpoint.spawndata[" + i + "] = \"" + spawnpoint.spawndata[i] + "\";" );
		}
		
		println( "spawndata.spawnpoints[spawndata.spawnpoints.size] = spawnpoint;" );
		index++;
	}
	println( "=================================" );
}

DrawRecordedSpawnData()
{
	spawndata = undefined;
	
	// to remove line beginnings from console log, use regexp: ^\[.*\]
	// ====================================
	// paste console log output in here
	// ====================================
	
	if ( isDefined( spawndata ) )
		thread drawSpawnData( spawndata );
}

checkBad( spawnpoint )
{
	for ( i = 0; i < level.players.size; i++ )
	{
		player = level.players[i];
		
		if ( !isAlive( player ) || player.sessionstate != "playing" )
			continue;
		if ( level.teambased && player.team == self.team )
			continue;
		
		losExists = bullettracepassed(player.origin + (0,0,50), spawnpoint.sightTracePoint, false, undefined);
		if ( losExists )
			thread badSpawnLine( spawnpoint.sightTracePoint, player.origin + (0,0,50), self.name, player.name );
	}
}

badSpawnLine( start, end, name1, name2 )
{
	dist = distance(start,end);
	for ( i = 0; i < 20 * 10; i++ )
	{
		line( start, end, (1,0,0) );
		print3d( start, "Bad spawn! " + name1 + ", dist = " + dist );
		print3d( end, name2 );
		
		wait .05;
	}
}

drawSpawnData( spawndata )
{
	level notify("drawing_spawn_data");
	level endon("drawing_spawn_data");
	
	textoffset = (0,0,-12);
	
	fakeplayer = spawnstruct();
	fakeplayer.name = spawndata.playername;
	
	fakeplayer thread spawnWeightDebug( spawndata.spawnpoints, spawndata.spawnpoints[spawndata.spawnpointwinner] );
	
	while(1)
	{
		for (i = 0; i < spawndata.friends.size; i++)
		{
			print3d(spawndata.friends[i], "=)", (.5,1,.5), 1, 5);
		}
		for (i = 0; i < spawndata.enemies.size; i++)
		{
			print3d(spawndata.enemies[i], "=(", (1,.5,.5), 1, 5);
		}
		
		for (i = 0; i < spawndata.otherdata.size; i++)
		{
			print3d(spawndata.otherdata[i].origin, spawndata.otherdata[i].text, (.5,.75,1), 1, 2);
		}
		
		wait .05;
	}
}

#/

getSpawnpoint_Random(spawnpoints)
{
//	level endon("game_ended");
	
	// There are no valid spawnpoints in the map
	if(!isdefined(spawnpoints))
		return undefined;

	// randomize order
	for ( i = 0; i < spawnpoints.size; i++ )
	{
		j = randomInt(spawnpoints.size);
		spawnpoint = spawnpoints[i];
		spawnpoints[i] = spawnpoints[j];
		spawnpoints[j] = spawnpoint;
	}
	
	if ( isDefined( self.predictedSpawnPoint ) )
	{
		// if we predicted spawning at one of these spawnpoints already, favor that one.
		for ( i = 1; i < spawnpoints.size; i++ )
		{
			if ( spawnpoints[i] == self.predictedSpawnPoint )
			{
				temp = spawnpoints[0];
				spawnpoints[0] = spawnpoints[i];
				spawnpoints[i] = temp;
				break;
			}
		}
	}
	
	return getSpawnpoint_Final(spawnpoints, false);
}

getAllOtherPlayers()
{
	aliveplayers = [];

	// Make a list of fully connected, non-spectating, alive players
	for(i = 0; i < level.players.size; i++)
	{
		if ( !isdefined( level.players[i] ) )
			continue;
		player = level.players[i];
		
		if ( player.sessionstate != "playing" || player == self )
			continue;

		aliveplayers[aliveplayers.size] = player;
	}
	return aliveplayers;
}


// weight array manipulation code
initWeights(spawnpoints)
{
	for (i = 0; i < spawnpoints.size; i++)
		spawnpoints[i].weight = 0;
	
	/#
	for (i = 0; i < spawnpoints.size; i++) {
		spawnpoints[i].spawnData = [];
	}
	#/
}

// ================================================


getSpawnpoint_NearTeam( spawnpoints, favoredspawnpoints )
{
//	level endon("game_ended");
	
	/*if ( self.wantSafeSpawn )
	{
		return getSpawnpoint_SafeSpawn( spawnpoints );
	}*/
	
	// There are no valid spawnpoints in the map
	if(!isdefined(spawnpoints))
		return undefined;
	
	/#
	setDevDvarIfUninitialized("scr_spawn_randomly", "0");
	if ( getdvarint("scr_spawn_randomly") == 1 )
		return getSpawnpoint_Random( spawnpoints );
	#/
		
	prof_begin("spawn_basiclogic");
	
	/#
	if ( getdvarint("scr_spawnsimple") > 0 )
		return getSpawnpoint_Random( spawnpoints );
	#/
	
	Spawnlogic_Begin();
	
	initWeights(spawnpoints);
	
	alliedDistanceWeight = 2;
	
	//prof_begin(" spawn_basicsumdists");
	myTeam = self.team;
	enemyTeam = getOtherTeam( myTeam );

	carePackages = getEntArray( "care_package", "targetname" );
	foreach ( spawnpoint in spawnpoints )
	{
		if ( spawnpoint.numPlayersAtLastUpdate > 0 )
		{
			allyDistSum = spawnpoint.weightedDistSum[ myTeam ]; // we weight the allied distSum to account for things like snipers and tactical insertion
			enemyDistSum = spawnpoint.distSum[ enemyTeam ];
			
			// high enemy distance is good, high ally distance is bad
			spawnpoint.weight = (enemyDistSum - alliedDistanceWeight*allyDistSum) / spawnpoint.numPlayersAtLastUpdate;

			//IW5 Modification for unusual game modes
			if( isDefined( level.favorCloseSpawnEnt ) )
			{
				if ( !isdefined( level.favorCloseSpawnScalar ) )
					level.favorCloseSpawnScalar = 1;
				
				distanceFromEnt = Distance( spawnpoint.origin, level.favorCloseSpawnEnt.origin );
				
				spawnpoint.weight -= distanceFromEnt * level.favorCloseSpawnScalar;  	
			}

			/#
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Base weight: " + int(spawnpoint.weight) + " = (" + int(enemyDistSum) + " - " + alliedDistanceWeight + "*" + int(allyDistSum) + ") / " + spawnpoint.numPlayersAtLastUpdate;
			#/
		}
		else
		{
			spawnpoint.weight = 0;

			/#
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Base weight: 0";
			#/
		}

		if ( carePackages.size && !canSpawn( spawnpoint.origin ) )
			spawnpoint.weight -= 500000;
	}
	//prof_end(" spawn_basicsumdists");
	
	if ( isdefined( favoredspawnpoints ) )
	{
		for (i = 0; i < favoredspawnpoints.size; i++)
		{
			favoredspawnpoints[i].weight += 50000;
			/#
			favoredspawnpoints[i].spawnData[favoredspawnpoints[i].spawnData.size] = "Favored: 50000";
			#/
		}
	}
	
	if ( isDefined( self.predictedSpawnPoint ) && isDefined( self.predictedSpawnPoint.weight ) )
	{
		// add a tiebreaker in case we end up choosing between spawnpoints of similar weight
		self.predictedSpawnPoint.weight += 100;
		/#
		self.predictedSpawnPoint.spawnData[self.predictedSpawnPoint.spawnData.size] = "Predicted: 100";
		#/
	}
	
	prof_end("spawn_basiclogic");

	prof_begin("spawn_complexlogic");

	avoidSameSpawn();
	// not avoiding spawn reuse because it doesn't do anything nearbyPenalty doesn't do
	//avoidSpawnReuse(spawnpoints, true);
	// not avoiding spawning near recent deaths for team-based modes. kills the fast pace.
	//avoidDangerousSpawns(spawnpoints, true);
	avoidWeaponDamage(spawnpoints);
	avoidVisibleEnemies(spawnpoints, true);
	
	//added to MW3
	if ( isDefined( self.lastDeathPos ) && level.gameType != "dom" )
		avoidRevengeSpawn( spawnpoints, self.lastDeathPos );
	
	prof_end("spawn_complexlogic");

	result = getSpawnpoint_Final(spawnpoints);
	
	/#
	setdevdvarIfUninitialized("scr_spawn_showbad", "0");
	if ( getdvarint("scr_spawn_showbad") == 1 )
		checkBad( result );
	#/
	
	/#
	foundIt = 0;
	foreach ( spawn in level.spawnLogData )
	{
		if ( spawn == result )
		{
			foundIt = 1;
		}
	}
	
	if ( foundIt == 0 )
		level.spawnLogData[level.spawnLogData.size] = result;
		
	if ( !isDefined( result.spawnCount ) )
	{
		result.spawnCount = 1;
	}
	
	#/
	
	
	return result;
}


//Not In Use --- IW5 ---
getSpawnpoint_SafeSpawn( spawnpoints )
{
	// There are no valid spawnpoints in the map
	if ( !isdefined( spawnpoints ) )
		return undefined;
	assert( spawnpoints.size > 0 );
	
	Spawnlogic_Begin();
	
	safestSpawnpoint = undefined;
	safestDangerDist = undefined;
	
	enemyTeam = getOtherTeam( self.team );
	if ( !level.teambased )
		enemyTeam = "all";
	
	mingrenadedistsquared = 500 * 500;
	
	foreach ( spawnpoint in spawnpoints )
	{
		dangerDist = spawnpoint.minDist[ enemyTeam ];
		
		foreach ( grenade in level.grenades )
		{
			if ( !isdefined( grenade ) )
				continue;
			
			if ( distancesquared( spawnpoint.origin, grenade.origin ) < mingrenadedistsquared )
			{
				grenadeDist = distance( spawnpoint.origin, grenade.origin ) - 220;
				if ( grenadeDist < dangerDist )
				{
					if ( grenadeDist < 0 )
						grenadeDist = 0;
					dangerDist = grenadeDist;
				}
			}
		}
		
		if ( positionWouldTelefrag( spawnpoint.origin ) )
			dangerDist -= 200; // discourage telefragging but don't worry too much
		
		if ( isDefined( level.artilleryDangerCenters ) )
		{
			airstrikeDanger = maps\mp\killstreaks\_airstrike::getAirstrikeDanger( spawnpoint.origin );
			if ( airstrikeDanger > 0 )
				dangerDist = 0;
		}
		
		if ( level.teambased )
		{
			if ( spawnpoint.sights[enemyTeam] > 0 )
				dangerDist = 0;
		}
		else
		{
			if ( spawnpoint.sights > 0 )
				dangerDist = 0;
		}
		
		if ( !isdefined( safestSpawnpoint ) || dangerDist > safestDangerDist )
		{
			safestSpawnpoint = spawnpoint;
			safestDangerDist = dangerDist;
		}
	}
	
	assert( isdefined( safestSpawnpoint ) );
	if ( !isdefined( safestSpawnpoint ) )
	{
		safestSpawnpoint = spawnpoints[ randomint( spawnpoints.size ) ];
		safestSpawnpoint.safeSpawnDangerDist = 500;
	}
	else
	{
		safestSpawnpoint.safeSpawnDangerDist = safestDangerDist;
	}
	
	return safestSpawnpoint;
}

/////////////////////////////////////////////////////////////////////////

getSpawnpoint_DM(spawnpoints)
{
//	level endon("game_ended");
	
	/*if ( self.wantSafeSpawn )
	{
		return getSpawnpoint_SafeSpawn( spawnpoints );
	}*/
	
	// There are no valid spawnpoints in the map
	if(!isdefined(spawnpoints))
		return undefined;
	
	Spawnlogic_Begin();

	initWeights(spawnpoints);
	
	aliveplayers = getAllOtherPlayers();
	
	// new logic: we want most players near idealDist units away.
	// players closer than badDist units will be considered negatively
	idealDist = 1600;
	badDist = 1200;
	
	if (aliveplayers.size > 0 )
	{
		for (i = 0; i < spawnpoints.size; i++)
		{
			totalDistFromIdeal = 0;
			nearbyBadAmount = 0;
			for (j = 0; j < aliveplayers.size; j++)
			{
				dist = distance(spawnpoints[i].origin, aliveplayers[j].origin);
				
				if (dist < badDist)
					nearbyBadAmount += (badDist - dist) / badDist;
				
				distfromideal = abs(dist - idealDist);
				totalDistFromIdeal += distfromideal;
			}
			avgDistFromIdeal = totalDistFromIdeal / aliveplayers.size;
			
			wellDistancedAmount = (idealDist - avgDistFromIdeal) / idealDist;
			// if (wellDistancedAmount < 0) wellDistancedAmount = 0;
			
			// wellDistancedAmount is between -inf and 1, 1 being best (likely around 0 to 1)
			// nearbyBadAmount is between 0 and inf,
			// and it is very important that we get a bad weight if we have a high nearbyBadAmount.
			
			spawnpoints[i].weight = wellDistancedAmount - nearbyBadAmount * 2 + randomfloat(.2);
		}
	}
	
	carePackages = getEntArray( "care_package", "targetname" );

	for (i = 0; i < spawnpoints.size; i++)
	{
		if ( carePackages.size && !canSpawn( spawnpoints[i].origin ) )
			spawnpoints[i].weight -= 500000;
	}
			
	if ( isDefined( self.predictedSpawnPoint ) && isDefined( self.predictedSpawnPoint.weight ) )
	{
		// add a tiebreaker in case we end up choosing between spawnpoints of similar weight
		self.predictedSpawnPoint.weight += 100;
		/#
		self.predictedSpawnPoint.spawnData[self.predictedSpawnPoint.spawnData.size] = "Predicted: 100";
		#/
	}
	
	avoidSameSpawn();
	//avoidSpawnReuse(spawnpoints, false);
	//avoidDangerousSpawns(spawnpoints, false);
	avoidWeaponDamage(spawnpoints);
	avoidVisibleEnemies(spawnpoints, false);
	
	return getSpawnpoint_Final(spawnpoints);
}

// =============================================

// called at the start of every spawn
Spawnlogic_Begin()
{
	//updateDeathInfo();

	/#
	level.debugSpawning = (getdvarint("scr_spawnpointdebug") > 0);
	#/
}

// called once at start of game
init()
{
	/#
	setDevDvarIfUninitialized("scr_spawnpointdebug", "0");
	setDevDvarIfUninitialized("scr_killbots", 0);
	setDevDvarIfUninitialized("scr_killbottimer", 0);

	thread loopbotspawns();
	#/

	SetupKillstreakSpawnShield();

	// start keeping track of deaths
	level.spawnlogic_deaths = [];
	// DEBUG
	level.spawnlogic_spawnkills = [];
	level.players = [];
	level.grenades = [];
	level.pipebombs = [];
	level.turrets = [];
	level.helis = [];
	level.tanks = [];
	level.scramblers = [];
	level.ims = [];
	level.ugvs = [];

	level.teamSpawnPoints["axis"] = [];
	level.teamSpawnPoints["allies"] = [];

	level thread trackGrenades();
	level thread trackMissiles();
	
	level.spawnMins = (0,0,0);
	level.spawnMaxs = (0,0,0);
	if ( isdefined( level.safespawns ) )
	{
		for( i = 0; i < level.safespawns.size; i++ )
		{
			level.safespawns[i] spawnPointInit();
		}
	}
	
	/*
	level.spawnSecondFloorTrig = getent( "spawn_second_floor", "targetname" );
	if ( isDefined( level.spawnSecondFloorTrig ) )
	{
		transitions = getentarray( level.spawnSecondFloorTrig.target, "targetname" );
		level.spawnFloorTransitions = [];
		
		foreach ( org in transitions )
		{
			level.spawnFloorTransitions[ level.spawnFloorTransitions.size ] = org.origin;
			org delete();
		}
	}
	*/
	
	// DEBUG
	/#
	if (getdvarint("scr_spawnpointdebug") > 0)
	{
		thread profileDebug();
		
		thread drawRecordedSpawnData();
	}
	thread watchSpawnProfile();
	thread spawnGraphCheck();
	thread sightCheckCost();
	thread spawnWatcher();
	
	thread spawnInfoWriter();
	level.spawnLogData = [];
	#/
}

/#
spawnWatcher()
{
	level endon("game_ended");
	
	for( ;; )
	{
		level waittill( "player_spawned", playerSpawned );
		
		if ( isDefined( playerSpawned.lastSpawnPoint ) )
		{	
			if( isDefined( playerSpawned.lastSpawnPoint.spawnCount ) )
				playerSpawned.lastSpawnPoint.spawnCount++;
			else
				playerSpawned.lastSpawnPoint.spawnCount = 1;
		}
	}
}
#/

/#
spawnInfoWriter()
{
	level waittill( "game_ended" ); 
	
	mapName = getdvar( "ui_mapname" );
	
	spawnDataFile = OpenFile( "spawn_info.txt", "append" );
	
	FPrintLn( spawnDataFile, "SPAWN DATA FOR: " + mapName );
	FPrintLn( spawnDataFile, " " );
	
	foreach( spawn in level.spawnLogData )
	{
		ResetTimeout();
		FPrintLn( spawnDataFile, "Spawn Point Origin: " + spawn.origin );
		FPrintLn( spawnDataFile, "Number of players spawned from this point: " + spawn.spawncount );
		FPrintLn( spawnDataFile, " " );
	}
	println( "File Written" );
	
	wait( 1 );
	CloseFile(spawnDataFile);
}
#/

sightCheckCost()
{
	traceCount = 30;
	
	for ( ;; )
	{
		prof_begin( "sight_check_cost" );
		
		traceType = getDvar( "scr_debugcost" );
		
		if ( traceType == "bullet" && isDefined( level.players[0] ) )
		{
			for ( i = 0; i < traceCount; i++ )
				bulletTracePassed( level.players[0].origin + (0,0,50), (0,0,0), false, undefined );		
			
		}
		else if ( traceType == "damagecone" && isDefined( level.players[0] ) )
		{
			for ( i = 0; i < traceCount; i++ )
				level.players[0] damageConeTrace( (0,0,0) );
		}
		else if ( traceType == "sightcone" && isDefined( level.players[0] ) )
		{
			for ( i = 0; i < traceCount; i++ )
				level.players[0] sightConeTrace( (0,0,0) );
		}
		else
		{
			wait ( 1.0 );
		}
				
		prof_end( "sight_check_cost" );
		
		wait ( 0.05 );
	}
}

watchSpawnProfile()
{
	while(1)
	{
		while( getDvar( "scr_spawnprofile" ) == "" || getDvar( "scr_spawnprofile" ) == "0" )
			wait ( 0.05 );
		
		thread spawnProfile();
		
		while( getDvar( "scr_spawnprofile" ) != "" && getDvar( "scr_spawnprofile" ) != "0" )
			wait ( 0.05 );
		
		level notify("stop_spawn_profile");
	}
}

spawnProfile()
{
	level endon("stop_spawn_profile");
	
	spawnObj = spawnStruct();
	
	while(1)
	{
		/*

		if ( level.players.size > 0 && level.spawnpoints.size > 0 )
		{
			playerNum = randomint(level.players.size);
			player = level.players[playerNum];
			
			if ( player.team != "allies" && player.team != "axis" )
				continue;
			
			if ( level.teamBased && (getDvar( "scr_spawnprofile" ) == "allies" || getDvar( "scr_spawnprofile" ) == "axis") && player.team != getDvar( "scr_spawnprofile" ) )
				continue;
				
			attempt = 1;
			while ( !isdefined( player ) && attempt < level.players.size )
			{
				playerNum = ( playerNum + 1 ) % level.players.size;
				attempt++;
				player = level.players[playerNum];
			}
			
			player getSpawnpoint_NearTeam(level.spawnpoints);
		}
		*/
		
		dvarString = getDvar( "scr_spawnprofile" );
		
		if ( dvarString != "allies" && dvarString != "axis" )
		{
			if ( cointoss() )
				dvarString = "allies";
			else
				dvarString = "axis";
		}
		
		spawnObj.team = dvarString;
		spawnObj.pers["team"] = dvarString;
		
		spawnObj getSpawnpoint_NearTeam(level.spawnpoints);
		wait ( 0.05 );
	}
}

spawnGraphCheck()
{
	while(1)
	{
		if ( getdvarint("scr_spawngraph") < 1 )
		{
			wait 3;
			continue;
		}
		thread spawnGraph();
		while ( getdvarint("scr_spawngraph") >= 1 )
		{
			wait .2;
			continue;
		}
		level notify( "end_spawn_graph" );
		level notify( "spawn_graph_stop_draw" );
	}
}

spawnGraph()
{
	level endon( "end_spawn_graph" );
	
	w = 20;
	h = 20;
	weightscale = .1;
	fakespawnpoints = [];
	
	corners = getentarray("minimap_corner", "targetname");
	if ( corners.size != 2 )
	{
		println("^1 can't spawn graph: no minimap corners");
		return;
	}
	min = corners[0].origin;
	max = corners[0].origin;
	if ( corners[1].origin[0] > max[0] )
		max = (corners[1].origin[0], max[1], max[2]);
	else
		min = (corners[1].origin[0], min[1], min[2]);
	if ( corners[1].origin[1] > max[1] )
		max = (max[0], corners[1].origin[1], max[2]);
	else
		min = (min[0], corners[1].origin[1], min[2]);
	
	i = 0;
	for ( y = 0; y < h; y++ )
	{
		yamnt = y / (h - 1);
		for ( x = 0; x < w; x++ )
		{
			xamnt = x / (w - 1);
			fakespawnpoints[i] = spawnstruct();
			fakespawnpoints[i].origin = (min[0] * xamnt + max[0] * (1-xamnt), min[1] * yamnt + max[1] * (1-yamnt), min[2]);
			fakespawnpoints[i].angles = (0,0,0);
			
			fakespawnpoints[i].forward = anglesToForward( fakespawnpoints[i].angles );
			fakespawnpoints[i].sightTracePoint = fakespawnpoints[i].origin;
			fakespawnpoints[i].outside = true;
			fakespawnpoints[i].secondfloor = false;
			fakespawnpoints[i].fake = true;
			
			i++;
		}
	}
	
	didweights = false;
	
	while(1)
	{
		spawni = 0;
		numiters = 10;
		for ( i = 0; i < numiters; i++ )
		{
			if ( !level.players.size || !isdefined( level.players[0].team ) || level.players[0].team == "spectator" || !isdefined( level.players[0].class ) )
				break;
			
			endspawni = spawni + fakespawnpoints.size / numiters;
			if ( i == numiters - 1 )
				endspawni = fakespawnpoints.size;
			
			for ( ; spawni < endspawni; spawni++ )
			{
				spawnPointUpdate( fakespawnpoints[spawni] );
			}
			
			wait .05;
		}
		
		if ( !level.players.size || !isdefined( level.players[0].team ) || level.players[0].team == "spectator" || !isdefined( level.players[0].class ) )
		{
			wait 1;
			continue;
		}
		
		level.players[0] getSpawnpoint_NearTeam( fakespawnpoints );
		
		for ( i = 0; i < fakespawnpoints.size; i++ )
			setupSpawnGraphPoint( fakespawnpoints[i], weightscale );
		
		didweights = true;
		
		level.players[0] drawSpawnGraph( fakespawnpoints, w, h, weightscale );
		
		wait .05;
	}
}

drawSpawnGraph( fakespawnpoints, w, h, weightscale )
{
	level notify( "spawn_graph_stop_draw" );
	
	i = 0;
	for ( y = 0; y < h; y++ )
	{
		yamnt = y / (h - 1);
		for ( x = 0; x < w; x++ )
		{
			xamnt = x / (w - 1);
			
			if ( y > 0 )
			{
				thread spawnGraphLine( fakespawnpoints[i], fakespawnpoints[i-w], weightscale );
			}
			if ( x > 0 )
			{
				thread spawnGraphLine( fakespawnpoints[i], fakespawnpoints[i-1], weightscale );
			}
			i++;
		}
	}
}

setupSpawnGraphPoint( s1, weightscale )
{
	s1.visible = true;
	if ( s1.weight < -1000/weightscale )
	{
		s1.visible = false;
	}
}

spawnGraphLine( s1, s2, weightscale )
{
	if ( !s1.visible || !s2.visible )
		return;
	
	p1 = s1.origin + (0,0,s1.weight*weightscale + 100);
	p2 = s2.origin + (0,0,s2.weight*weightscale + 100);
	
	level endon( "spawn_graph_stop_draw" );
	
	for ( ;; )
	{
		line( p1, p2, (1,1,1) );
		wait .05;
		waittillframeend;
	}
}

loopbotspawns()
{
	while(1)
	{
		if ( getdvarint("scr_killbots") < 1 )
		{
			wait 3;
			continue;
		}
		if ( !isdefined( level.players ) )
		{
			wait .05;
			continue;
		}
		
		bots = [];
		for (i = 0; i < level.players.size; i++)
		{
			if ( !isdefined( level.players[i] ) )
				continue;

			if ( level.players[i].sessionstate == "playing" && issubstr(level.players[i].name, "bot") )
			{
				bots[bots.size] = level.players[i];
			}
		}
		if ( bots.size > 0 )
		{
			if ( getdvarint( "scr_killbots" ) == 1 )
			{
				killer = bots[randomint(bots.size)];
				victim = bots[randomint(bots.size)];
				
				victim thread [[level.callbackPlayerDamage]] (
					killer, // eInflictor The entity that causes the damage.(e.g. a turret)
					killer, // eAttacker The entity that is attacking.
					1000, // iDamage Integer specifying the amount of damage done
					0, // iDFlags Integer specifying flags that are to be applied to the damage
					"MOD_RIFLE_BULLET", // sMeansOfDeath Integer specifying the method of death
					"none", // sWeapon The weapon number of the weapon used to inflict the damage
					(0,0,0), // vPoint The point the damage is from?
					(0,0,0), // vDir The direction of the damage
					"none", // sHitLoc The location of the hit
					0 // psOffsetTime The time offset for the damage
				);
			}
			else
			{
				numKills = getdvarint( "scr_killbots" );
				lastVictim = undefined;
				for ( index = 0; index < numKills; index++ )
				{
					killer = bots[randomint(bots.size)];
					victim = bots[randomint(bots.size)];
					
					while ( isDefined( lastVictim ) && victim == lastVictim )
						victim = bots[randomint(bots.size)];
					
					victim thread [[level.callbackPlayerDamage]] (
						killer, // eInflictor The entity that causes the damage.(e.g. a turret)
						killer, // eAttacker The entity that is attacking.
						1000, // iDamage Integer specifying the amount of damage done
						0, // iDFlags Integer specifying flags that are to be applied to the damage
						"MOD_RIFLE_BULLET", // sMeansOfDeath Integer specifying the method of death
						"none", // sWeapon The weapon number of the weapon used to inflict the damage
						(0,0,0), // vPoint The point the damage is from?
						(0,0,0), // vDir The direction of the damage
						"none", // sHitLoc The location of the hit
						0 // psOffsetTime The time offset for the damage
					);
					
					lastVictim = victim;
				}
			}
		}
		
		if ( getdvarfloat( "scr_killbottimer" ) > .066 )
			wait getdvarfloat( "scr_killbottimer" );
		else
			wait .05;
	}
}

/#
spawnWeightDebug(spawnpoints, winner)
{
	level notify("stop_spawn_weight_debug");
	level endon("stop_spawn_weight_debug");
	while(1)
	{		
		if ( getdvarint("scr_spawnpointdebug") == 0 ) 
		{
			wait(3);
			continue;
		}
		
		textoffset = (0,0,-12);
		for (i = 0; i < spawnpoints.size; i++)
		{
			amnt = 1 * (1 - spawnpoints[i].weight / (-100000));
			if (amnt < 0) amnt = 0;
			if (amnt > 1) amnt = 1;
			
			orig = spawnpoints[i].origin + (0,0,80);
			
			print3d(orig, int(spawnpoints[i].weight), (1,amnt,.5));
			orig += textoffset;
			
			if ( spawnpoints[i] == winner )
			{
				print3d(orig, "Spawned " + self.name + " here", (1,amnt,.5));
				orig += textoffset;
			}
			
			if (isdefined(spawnpoints[i].spawnData))
			{
				for (j = 0; j < spawnpoints[i].spawnData.size; j++)
				{
					print3d(orig, spawnpoints[i].spawnData[j], (.5,.5,.5));
					orig += textoffset;
				}
			}
			
			// "bar graph"
			height = 0;
			if ( spawnpoints[i].weight > -1000 )
				height = (spawnpoints[i].weight + 1000) / 10;
			
			amnt = spawnpoints[i].weight / 2000;
			if (amnt < 0) amnt = 0;
			if (amnt > 1) amnt = 1;
			
			color = (1 - amnt, 1, 0);
			
			pt1 = spawnpoints[i].origin + (0,0,95);
			pt2 = spawnpoints[i].origin + (30,0,95);
			pt3 = pt1 + (0,0,height);
			pt4 = pt2 + (0,0,height);
			line( pt1, pt2, color );
			line( pt1, pt3, color );
			line( pt2, pt4, color );
			line( pt3, pt4, color );
			
			if ( spawnpoints[i] == winner )
			{
				// checkmark
				checkpt1 = pt3 + (0,0,30);
				checkpt2 = pt3 + (10,0,10);
				checkpt3 = pt3 + (30,0,50);
				
				line( checkpt1, checkpt2, color );
				line( checkpt2, checkpt3, color );
			}
		}
		wait(.05);
	}
}

profileDebug()
{
	while(1)
	{
		if (getdvar("scr_spawnpointprofile") != "1") {
			wait(3);
			continue;
		}
		
		for (i = 0; i < level.spawnpoints.size; i++)
			level.spawnpoints[i].weight = randomint(10000);
		if (level.players.size > 0)
			level.players[randomint(level.players.size)] getSpawnpoint_NearTeam(level.spawnpoints);
		
		wait(.05);
	}
}

debugNearbyPlayers(players, origin)
{
	if ( getdvarint("scr_spawnpointdebug") == 0 )
		return;

	starttime = gettime();
	while(1)
	{
		for (i = 0; i < players.size; i++)
			line(players[i].origin, origin, (.5,1,.5));
		if (gettime() - starttime > 5000)
			return;
		wait .05;
	}
}
#/


trackGrenades()
{
	while ( 1 )
	{
		level.grenades = getentarray("grenade", "classname");
		wait .05;
	}
}


trackMissiles()
{
	for( ;; )
	{
		level.missiles = getentarray( "rocket", "classname" );
		wait .05;
	}
}


// used by spawning; needs to be fast.
isPointVulnerable(playerorigin)
{
	pos = self.origin + level.claymoremodelcenteroffset;
	playerpos = playerorigin + (0,0,32);
	distsqrd = distancesquared(pos, playerpos);
	
	forward = anglestoforward(self.angles);
	
	if (distsqrd < level.claymoreDetectionRadius*level.claymoreDetectionRadius)
	{
		playerdir = vectornormalize(playerpos - pos);
		angle = acos(vectordot(playerdir, forward));
		if (angle < level.claymoreDetectionConeAngle) {
			return true;
		}
	}
	return false;
}


avoidWeaponDamage(spawnpoints)
{
	//prof_begin(" spawn_complexgrenade");

	weaponDamagePenalty = 100000;
	if (getdvar("scr_spawnpointweaponpenalty") != "" && getdvar("scr_spawnpointweaponpenalty") != "0")
		weaponDamagePenalty = getdvarfloat("scr_spawnpointweaponpenalty");

	mingrenadedistsquared = 250*250; // (actual grenade radius is 220, 250 includes a safety area of 30 units)

	for (i = 0; i < spawnpoints.size; i++)
	{
		for (j = 0; j < level.grenades.size; j++)
		{
			if ( !isdefined( level.grenades[j] ) )
				continue;

			// could also do a sight check to see if it's really dangerous.
			if (distancesquared(spawnpoints[i].origin, level.grenades[j].origin) < mingrenadedistsquared)
			{
				spawnpoints[i].weight -= weaponDamagePenalty;
				/#
				spawnpoints[i].spawnData[spawnpoints[i].spawnData.size] = "Was near grenade: -" + int(weaponDamagePenalty);
				#/
			}
		}
		
		foreach( mine in level.mines )
		{
			if ( !isdefined( mine ) )
				continue;

			if ( distancesquared( spawnpoints[i].origin, mine.origin ) < mingrenadedistsquared)
			{
				spawnpoints[i].weight -= weaponDamagePenalty;
				
				/#
				spawnpoints[i].spawnData[spawnpoints[i].spawnData.size] = "Was near mine: -" + int(weaponDamagePenalty);
				#/
			}
		}
		
		if ( !isDefined( level.artilleryDangerCenters ) )
			continue;
		
		airstrikeDanger = maps\mp\killstreaks\_airstrike::getAirstrikeDanger( spawnpoints[i].origin ); // 0 = none, 1 = full, might be > 1 for more than 1 airstrike
		
		if ( airstrikeDanger > 0 )
		{
			worsen = airstrikeDanger * weaponDamagePenalty;
			spawnpoints[i].weight -= worsen;
			/#
			spawnpoints[i].spawnData[spawnpoints[i].spawnData.size] = "Was near artillery (" + int(airstrikeDanger*100) + "% danger): -" + int(worsen);
			#/
		}
	}

	//prof_end(" spawn_complexgrenade");
}

spawnPerFrameUpdate()
{
	spawnpointindex = 0;
	
	// each frame, do sight checks against a spawnpoint
	
	while(1)
	{
		wait .05;
		
		prof_begin("spawn_update");
		
		//time = gettime();
		
		if ( !isDefined( level.spawnPoints ) )
			return;
		
		spawnpointindex = (spawnpointindex + 1) % level.spawnPoints.size;
		
		if ( getdvar( "scr_spawnpoint_forceindex" ) != "" )
			spawnpointindex = getdvarint( "scr_spawnpoint_forceindex" );
		
		spawnpoint = level.spawnPoints[spawnpointindex];
		
		spawnPointUpdate( spawnpoint );
		
		prof_end("spawn_update");
	}
}

adjustSightValue( sightValue )
{
	assert( sightValue >= 0 );
	assert( sightValue <= 1 );
	if ( sightValue <= 0 )
		return 0;
	if ( sightValue >= 1 )
		return 1;
	return sightValue * 0.5 + 0.25;
}

spawnPointUpdate( spawnpoint )
{
	prof_begin( " spawn_update_init" );

	if ( level.teambased )
	{
		spawnpoint.sights["axis"] = 0;
		spawnpoint.sights["allies"] = 0;
	}
	else
	{
		spawnpoint.sights = 0;
	}
	
	spawnpointdir = spawnpoint.forward;
	
	debug = false;
	/#
	debug = (getdvarint("scr_spawnpointdebug") > 0);
	
	spawnpoint notify( "debug_stop_LOS" );
	#/
	
	spawnpoint.distSum["all"] = 0;
	spawnpoint.distSum["allies"] = 0;
	spawnpoint.distSum["axis"] = 0;

	spawnpoint.weightedDistSum["all"] = 0;	
	spawnpoint.weightedDistSum["allies"] = 0;	
	spawnpoint.weightedDistSum["axis"] = 0;	
	
	spawnpoint.minDist["all"] = 9999999;
	spawnpoint.minDist["allies"] = 9999999;
	spawnpoint.minDist["axis"] = 9999999;
	
	spawnpoint.numPlayersAtLastUpdate = 0;
	
	totalPlayers["all"] = 0;
	totalPlayers["allies"] = 0;
	totalPlayers["axis"] = 0;

	weightSum["all"] = 0;
	weightSum["allies"] = 0;
	weightSum["axis"] = 0;
	
	winner = undefined;
	
	curTime = getTime();
	
	team = "all";
	teambased = level.teambased;
	
	prof_end( " spawn_update_init" );
	
	prof_begin( " spawn_update_ploop" );
	
	foreach ( player in level.players )
	{
		//prof_begin( " spawn_update_player" );
		
		if ( player.sessionstate != "playing" )
		{
			//prof_end( " spawn_update_player" );
			continue;
		}
		
		/*
		playerSecondFloor = false;
		if ( isDefined( level.spawnSecondFloorTrig ) && player isTouching( level.spawnSecondFloorTrig ) )
			playerSecondFloor = true;
		*/
		
		//prof_begin( " spawn_update_diff" );
		
		diff = player.origin - spawnpoint.origin;
		diff = (diff[0], diff[1], 0);

		weight = 1.0; // default weight for weightedDistSum
		
		dist = length( diff ); // needs to be actual distance for distSum value
		
		//prof_end( " spawn_update_diff" );
		
		//prof_begin( " spawn_update_team" );
		
		if ( teambased )
			team = player.team;
		
		//prof_end( " spawn_update_team" );
		
		//prof_begin( " spawn_update_nearby" );
		if ( dist < spawnpoint.minDist[team] )
			spawnpoint.minDist[team] = dist;
		//prof_end( " spawn_update_nearby" );
		
		//prof_begin( " spawn_update_weight" );
		// tactical insertion weighting; players should not spawn too close to recent TI spawns
		if ( player.wasTI && curTime - player.spawnTime < 15000 )
			weight *= 0.1;
		
		// sniper weight check
		// note: weaponClass() is slow!
		if ( player.isSniper )
			weight *= 0.5;
		//prof_end( " spawn_update_weight" );
		
		//prof_begin( " spawn_update_sums" );
		weightSum[ team ] += weight;
		spawnpoint.weightedDistSum[ team ] += dist * weight;
		
		spawnpoint.distSum[ team ] += dist;
		spawnpoint.numPlayersAtLastUpdate++;
		
		totalPlayers[team]++;
		//prof_end( " spawn_update_sums" );
		
		//prof_begin( " spawn_update_dot" );
		pdir = anglestoforward(player.angles);
		if (vectordot(spawnpointdir, diff) < 0 && vectordot(pdir, diff) > 0)
		{
			//prof_end( " spawn_update_dot" );
			//prof_end( " spawn_update_player" );
			continue; // player and spawnpoint are looking in opposite directions
		}
		//prof_end( " spawn_update_dot" );
		
		/#
		if ( isDefined( spawnpoint.fake ) )
		{
			//prof_end( " spawn_update_player" );
			continue;
		}
		#/
		
		// do sight check
		/*
		prof_begin( " spawn_update_told" );
		losExists = bullettracepassed(player.origin + (0,0,50), spawnpoint.sightTracePoint, false, undefined);
		prof_end( " spawn_update_told" );
		*/
		
		prof_begin( " spawn_update_trace" );
		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, player.origin + (0,0,50) );
		prof_end( " spawn_update_trace" );
		
		//prof_begin( " spawn_update_losexists" );
		spawnpoint.lastSightTraceTime = gettime();
		
		if ( sightValue > 0 )
		{
			sightValue = adjustSightValue( sightvalue );
			if ( teamBased )
				spawnpoint.sights[team] += sightValue;
			else
				spawnpoint.sights += sightValue;
			
			/#
			if ( debug )
				spawnpoint thread spawnpointDebugLOS( player.origin + (0,0,50) );
			#/
		}
		//else
		//	line(player.origin + (0,0,50), spawnpoint.sightTracePoint, (1,.5,.5));
		
		//prof_end( " spawn_update_losexists" );
		
		//prof_end( " spawn_update_player" );
	}
	
	prof_end( " spawn_update_ploop" );
	
	prof_begin( " spawn_update_other" );
	
	nearbyEnemyRange = getFloatProperty( "scr_spawn_enemyavoiddist", 2000 );
	nearbyEnemyPenalty = 2000; // typical base weights tend to peak around 1500 or so. this is large enough to upset that while only locally dominating it.
	
	foreach ( team, value in weightSum )
	{
		if ( weightSum[team] )
			spawnpoint.weightedDistSum[team] = spawnpoint.weightedDistSum[team] / weightSum[team] * totalPlayers[team];
		
		nearbyPenalty = 0;
		if ( spawnpoint.mindist[team] < nearbyEnemyRange )
			nearbyPenalty = nearbyEnemyPenalty * (1 - spawnpoint.mindist[team] / nearbyEnemyRange);
		spawnpoint.nearbyPenalty[team] = nearbyPenalty;
	}
	
	
	foreach ( tank in level.tanks )
	{
		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, tank.origin + (0,0,50) );
		spawnpoint.lastSightTraceTime = gettime();
		
		if ( sightValue <= 0 )
			continue;
		
		sightValue = adjustSightValue( sightvalue );
		if ( teamBased )
			spawnpoint.sights[tank.team] += sightValue;
		else
			spawnpoint.sights += sightValue;
		
		/#
		if ( debug )
			spawnpoint thread spawnpointDebugLOS( tank.origin + (0,0,50) );
		#/
	}
	
	foreach ( turret in level.turrets )
	{
		if ( !isDefined( turret ) )
			continue;
		
		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, turret.origin + (0,0,50) );
		spawnpoint.lastSightTraceTime = gettime();
		
		if ( sightValue <= 0 )
			continue;
			
		sightValue = adjustSightValue( sightvalue );
		if ( teamBased )
			spawnpoint.sights[turret.team] += sightValue;
		else
			spawnpoint.sights += sightValue;
		
		/#
		if ( debug )
			spawnpoint thread spawnpointDebugLOS( turret.origin + (0,0,50) );
		#/
	}
	
	foreach ( ims in level.ims )
	{
		if ( !isDefined( ims ) )
			continue;

		if ( !isDefined( ims.attackHeightPos ) )
			continue;

		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, ims.attackHeightPos );
		spawnpoint.lastSightTraceTime = gettime();

		if ( sightValue <= 0 )
			continue;

		sightValue = adjustSightValue( sightvalue );
		if ( teamBased )
			spawnpoint.sights[ ims.team ] += sightValue;
		else
			spawnpoint.sights += sightValue;

		/#
		if( debug )
			spawnpoint thread spawnpointDebugLOS( ims.attackHeightPos );
		#/
	}

	foreach ( ugv in level.ugvs )
	{
		if ( !isDefined( ugv ) )
			continue;

		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, ugv.origin + (0,0,50) );
		spawnpoint.lastSightTraceTime = gettime();

		if ( sightValue <= 0 )
			continue;

		sightValue = adjustSightValue( sightvalue );
		if ( teamBased )
			spawnpoint.sights[ugv.team] += sightValue;
		else
			spawnpoint.sights += sightValue;

/#
		if ( debug )
			spawnpoint thread spawnpointDebugLOS( ugv.origin + (0,0,50) );
#/
	}

	// Disabled to see if removal of the red boxes upon spawn is sufficient
	// (helicopter traces also intentionally disabled)
	/*
	if ( spawnpoint.outside )
	{
		foreach ( heli in level.helis )
		{
			sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, heli.origin + (0,0,30) );
			spawnpoint.lastSightTraceTime = gettime();
			
			if ( sightValue <= 0 )
				continue;
				
			sightValue = adjustSightValue( sightvalue );
			if ( teamBased )
				spawnpoint.sights[heli.team] += sightValue;
			else
				spawnpoint.sights += sightValue;
			
			/#
			if ( debug )
				spawnpoint thread spawnpointDebugLOS( heli.origin + (0,0,30) );
			#/
		}
		
		foreach ( missile in level.missilesForSightTraces )
		{
			sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, missile.origin );
			spawnpoint.lastSightTraceTime = gettime();
			
			if ( sightValue <= 0 )
				continue;
			
			sightValue = adjustSightValue( sightvalue );
			if ( teamBased )
				spawnpoint.sights[missile.team] += sightValue;
			else
				spawnpoint.sights += sightValue;
			
			/#
			if ( debug )
				spawnpoint thread spawnpointDebugLOS( missile.origin );
			#/
		}
		
		if ( isDefined( level.ac130player ) && level.ac130player.team != "spectator" )
		{
			if ( teamBased )
				spawnpoint.sights[level.ac130player.team]++;
			else
				spawnpoint.sights++;
		}
	}
	*/
	
	prof_end( " spawn_update_other" );
}

/#
spawnpointDebugLOS( point )
{
	// g_spawndebug is better for this
	/*
	self endon( "debug_stop_LOS" );
	for ( ;; )
	{
		line( point, self.sightTracePoint, (1, .5, .5) );
		wait .05;
	}
	*/
}
#/

getLosPenalty()
{
	if (getdvar("scr_spawnpointlospenalty") != "" && getdvar("scr_spawnpointlospenalty") != "0")
		return getdvarfloat("scr_spawnpointlospenalty");
	return 100000;
}

lastMinuteSightTraces( spawnpoint )
{
	prof_begin(" spawn_final_lastminsc");
	
	closest = undefined;
	closestDistsq = 100000000.0;
	secondClosest = undefined;
	secondClosestDistsq = 100000000.0;
	foreach ( player in level.players )
	{
		if ( player.team == self.team && level.teambased )
			continue;
		if ( player.sessionstate != "playing" )
			continue;
		if ( player == self )
			continue;
		
		distsq = distanceSquared( spawnpoint.origin, player.origin );
		if ( distsq < closestDistsq )
		{
			secondClosest = closest;
			secondClosestDistsq = closestDistsq;
			
			closest = player;
			closestDistSq = distsq;
		}
		else if ( distsq < secondClosestDistSq )
		{
			secondClosest = player;
			secondClosestDistSq = distsq;
		}
	}
	
	if ( isdefined( closest ) )
	{
		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, closest.origin + (0,0,50) );
		if ( sightValue > 0 )
		{
			sightValue = adjustSightValue( sightvalue );
			prof_end(" spawn_final_lastminsc");
			return sightValue;
		}
	}
	if ( isdefined( secondClosest ) )
	{
		sightValue = SpawnSightTrace( spawnpoint, spawnpoint.sightTracePoint, secondClosest.origin + (0,0,50) );
		if ( sightValue > 0 )
		{
			sightValue = adjustSightValue( sightvalue );
			prof_end(" spawn_final_lastminsc");
			return sightValue;
		}
	}
	
	prof_end(" spawn_final_lastminsc");
	return 0;
}


getRevengeSpawnPenalty()
{
	penalty = getdvarfloat("scr_revengespawnpenalty", 25000 );
	return penalty;		
}


getRevengeSpawnDistanceSq()
{
	dist = getdvarfloat("scr_revengespawndist", 1200 );		
	return dist * dist;
}


avoidRevengeSpawn(spawnpoints, deathpos)
{
	mindistsq = getRevengeSpawnDistanceSq();
	penalty = getRevengeSpawnPenalty();
	
	foreach( spawnpoint in spawnpoints )
	{
		distsq = distanceSquared( spawnpoint.origin, deathpos );
		if ( distsq < mindistsq )
		{
			spawnpoint.weight -= penalty;
			/#
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Revenge spawn: " + int(distsq) + " < " + int(mindistsq) + ", -" + int(penalty);
			#/	
		}
	}
	
	if ( isDefined( self.lastAttacker ) && isDefined( self.lastAttacker.origin ) )
		self avoidRevengeSpawnStage2( spawnpoints, self.lastAttacker.origin );
		
}

avoidRevengeSpawnStage2( spawnpoints, attackerPos )
{
	mindistsq = getRevengeSpawnDistanceSq();
	penalty = getRevengeSpawnPenalty();
	
	foreach( spawnpoint in spawnpoints )
	{
		distsq = distanceSquared( spawnpoint.origin, attackerPos );
		if ( distsq < mindistsq )
		{
			spawnpoint.weight -= penalty;
			/#
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Revenge spawn Attacker: " + int(distsq) + " < " + int(mindistsq) + ", -" + int(penalty);
			#/
		}
	}
}

avoidVisibleEnemies(spawnpoints, teambased)
{
	//prof_begin(" spawn_complexsc");
	
	lospenalty = getLosPenalty();
	
	otherteam = "axis";
	if ( self.team == "axis" )
		otherteam = "allies";
	
	if ( teambased )
	{
		foreach ( spawnpoint in spawnpoints )
		{
			penalty = lospenalty * spawnpoint.sights[otherteam];
			spawnpoint.weight -= penalty;
			
			/#
			if ( penalty > 0 )
				spawnpoint.spawnData[spawnpoint.spawnData.size] = "Sight traces: -" + int(penalty);
			#/
		}
	}
	else
	{
		foreach ( spawnpoint in spawnpoints )
		{
			penalty = lospenalty * spawnpoint.sights;
			spawnpoint.weight -= penalty;

			/#
			if ( penalty > 0 )
				spawnpoint.spawnData[spawnpoint.spawnData.size] = "Sight traces: -" + int(penalty);
			#/
		}
		
		otherteam = "all";
	}
	
	foreach ( spawnpoint in spawnpoints )
	{
		// penalty for nearby enemies
		spawnpoint.weight -= spawnpoint.nearbyPenalty[otherteam];
		/#
		if ( spawnpoint.nearbyPenalty[otherteam] != 0 )
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Nearest enemy at " + int(spawnpoint.minDist[otherteam]) + " units: -" + int(spawnpoint.nearbyPenalty[otherteam]);
		#/
		
		if ( positionWouldTelefrag( spawnpoint.origin ) )
		{
			telefragCount = 1;
			
			foreach ( alternate in spawnpoint.alternates )
			{
				if ( positionWouldTelefrag( alternate ) )
					telefragCount++;
				else
					break;
			}
			
			penalty = 100000;
			if ( telefragCount < spawnpoint.alternates.size + 1 )
			{
				penalty = 1500 * telefragCount;
				if ( isDefined( self.forceSpawnNearTeammates ) )
					penalty = 0;
			}
			
			spawnpoint.weight -= penalty;
			/#
			spawnpoint.spawnData[spawnpoint.spawnData.size] = "Would telefrag " + telefragCount + " times: -" + penalty;
			#/
		}
	}
	
	// DEBUG
	//prof_end(" spawn_complexsc");
}

avoidSpawnReuse(spawnpoints, teambased)
{
	// DEBUG
	//prof_begin(" spawn_complexreuse");
	
	time = getTime();
	
	maxtime = 10*1000;
	maxdistSq = 1024 * 1024;
	
	foreach ( spawnpoint in spawnpoints )
	{
		lastspawnedplayer = spawnpoint.lastspawnedplayer;
		
		if ( !isalive( lastspawnedplayer ) )
			continue;
		
		if ( teambased && spawnpoint.lastspawnedplayer.team == self.team )
			continue;
		if ( spawnpoint.lastspawnedplayer == self )
			continue;
		
		timepassed = time - spawnpoint.lastspawntime;
		if ( timepassed < maxtime )
		{
			distSq = distanceSquared( spawnpoint.lastspawnedplayer.origin, spawnpoint.origin );
			if (distSq < maxdistSq)
			{
				worsen = 5000 * (1 - distSq/maxdistSq) * (1 - timepassed/maxtime);
				spawnpoint.weight -= worsen;
				/#
				spawnpoint.spawnData[spawnpoint.spawnData.size] = "Recently spawned enemy: -" + worsen;
				#/
			}
			else
				spawnpoint.lastspawnedplayer = undefined; // don't worry any more about this spawnpoint
		}
		else
			spawnpoint.lastspawnedplayer = undefined; // don't worry any more about this spawnpoint
	}
	
	//prof_end(" spawn_complexreuse");
}

avoidSameSpawn()
{
	//prof_begin(" spawn_complexsamespwn");
	
	spawnpoint = self.lastspawnpoint;

	if ( !isdefined( spawnpoint ) || !isdefined( spawnpoint.weight ) )
	{
		//prof_end(" spawn_complexsamespwn");
		return;
	}
	
	spawnpoint.weight -= 1000;
	/#
	spawnpoint.spawnData[spawnpoint.spawnData.size] = "Was last spawnpoint: -1000";
	#/
	
	//prof_end(" spawn_complexsamespwn");
}

SetupKillstreakSpawnShield()
{
	level.killstreakSpawnShield = 5000;
	if ( getDvar( "killstreakSpawnShield" ) != "" )
	{
		newLimit = getDvarInt( "killstreakSpawnShield" );
		if ( (newLimit >= 0) && (newLimit <= 10000) )
			level.killstreakSpawnShield = newLimit;
	}
}

