#include common_scripts\utility;
#include maps\mp\_utility;
main()
{
//	thread windController();
	level.inc = 0;
	
	array_levelthread (getentarray("wire","targetname"), ::wireWander);

	leftShutters = getentarray ("shutter_left","targetname");
	addShutters = getentarray ("shutter_right_open","targetname");
	for (i=0;i<addShutters.size;i++)
		leftShutters[leftShutters.size] = addShutters[i];
	addShutters = getentarray ("shutter_left_closed","targetname");
	for (i=0;i<addShutters.size;i++)
		leftShutters[leftShutters.size] = addShutters[i];
		
	for (i=0;i<leftShutters.size;i++)
	{
		shutter = leftShutters[i];
		shutter rotateto((shutter.angles[0], shutter.angles[1] + 180, shutter.angles[2]), 0.1);
	}
	wait (0.2);

	for (i=0;i<leftShutters.size;i++)
		leftShutters[i].startYaw = leftShutters[i].angles[1];

	rightShutters = getentarray ("shutter_right","targetname");
	addShutters = getentarray ("shutter_left_open","targetname");
	for (i=0;i<addShutters.size;i++)
		rightShutters[rightShutters.size] = addShutters[i];
	addShutters = getentarray ("shutter_right_closed","targetname");
	for (i=0;i<addShutters.size;i++)
		rightShutters[rightShutters.size] = addShutters[i];
	
	for (i=0;i<rightShutters.size;i++)
		rightShutters[i].startYaw = rightShutters[i].angles[1];

	addShutters = undefined;	

	windDirection = "left";
	for (;;)
	{
		array_levelthread (leftShutters, ::shutterWanderLeft, windDirection);
		array_levelthread (rightShutters, ::shutterWanderRight, windDirection);
		level waittill ("wind blows", windDirection);
	}
}

windController()
{
	for (;;)
	{
		windDirection = "left";
		if (randomint(100) > 50)
			windDirection = "right";
		level notify ("wind blows", windDirection);
		wait (2 + randomfloat(10));
	}
}

shutterWanderLeft(shutter, windDirection)
{
//	println ("shutter angles ", shutter.angles[1]);
//	assert (shutter.angles[1] >= shutter.startYaw);
//	assert (shutter.angles[1] < shutter.startYaw + 180);
	
//	println ("Wind + ", level.inc);
	level.inc++;
	level endon ("wind blows");

	newYaw = shutter.startYaw;
	if (windDirection == "left")
		newYaw += 179.9;
			
	newTime = 0.2;
	shutter rotateto((shutter.angles[0], newYaw, shutter.angles[2]), newTime);
	wait (newTime + 0.1);
	
	for (;;)
	{
		rot = randomint(80);
		if (randomint(100) > 50)
			rot *= -1;
			
		newYaw = shutter.angles[1] + rot;
		altYaw = shutter.angles[1] + (rot*-1);
		if ((newYaw < shutter.startYaw) || (newYaw > shutter.startYaw + 179))
		{
			newYaw = altYaw;
		}
			
		dif = abs(shutter.angles[1] - newYaw);
		
		newTime = dif*0.02 + randomfloat(2);
		if (newTime < 0.3)
			newTime = 0.3;
//		println ("startyaw " + shutter.startyaw + " newyaw " + newYaw);
		
//		assert (newYaw >= shutter.startYaw);
//		assert (newYaw < shutter.startYaw + 179);
		
		shutter rotateto((shutter.angles[0], newYaw, shutter.angles[2]), newTime, newTime * 0.5, newTime * 0.5);
		wait (newTime);
	}
}

shutterWanderRight(shutter, windDirection)
{
//	println ("shutter angles ", shutter.angles[1]);
//	assert (shutter.angles[1] >= shutter.startYaw);
//	assert (shutter.angles[1] < shutter.startYaw + 180);
	
//	println ("Wind + ", level.inc);
	level.inc++;
	level endon ("wind blows");

	newYaw = shutter.startYaw;
	if (windDirection == "left")
		newYaw += 179.9;
			
	newTime = 0.2;
	shutter rotateto((shutter.angles[0], newYaw, shutter.angles[2]), newTime);
	wait (newTime + 0.1);
	
	for (;;)
	{
		rot = randomint(80);
		if (randomint(100) > 50)
			rot *= -1;
			
		newYaw = shutter.angles[1] + rot;
		altYaw = shutter.angles[1] + (rot*-1);
		if ((newYaw < shutter.startYaw) || (newYaw > shutter.startYaw + 179))
		{
			newYaw = altYaw;
		}
			
		dif = abs(shutter.angles[1] - newYaw);
		
		newTime = dif*0.02 + randomfloat(2);
		if (newTime < 0.3)
			newTime = 0.3;
//		println ("startyaw " + shutter.startyaw + " newyaw " + newYaw);
		
//		assert (newYaw >= shutter.startYaw);
//		assert (newYaw < shutter.startYaw + 179);
		
		shutter rotateto((shutter.angles[0], newYaw, shutter.angles[2]), newTime, newTime * 0.5, newTime * 0.5);
		wait (newTime);
	}
}

wireWander (wire)
{
	origins = getentarray (wire.target,"targetname");
	org1 = origins[0].origin;
	org2 = origins[1].origin;
	
	angles = vectortoangles (org1 - org2);
	ent = spawn ("script_model",(0,0,0));
	ent.origin = ( org1 * 0.5 ) + ( org2 * 0.5 );
//	ent setmodel ("temp");
	ent.angles = angles;
	wire linkto (ent);
	rottimer = 2;
	rotrange = 0.9;
	dist = 4 + randomfloat(2);
	ent rotateroll(dist*0.5,0.2);
	wait (0.2);
	for (;;)
	{
		rottime = rottimer + randomfloat (rotRange) - (rotRange * 0.5);
		ent rotateroll(dist,rottime, rottime*0.5, rottime*0.5);
		wait (rottime);
		ent rotateroll(dist * -1,rottime, rottime*0.5, rottime*0.5);
		wait (rottime);
	}
}
