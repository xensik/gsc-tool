// face.gsc
// Supposed to handle all facial and dialogue animations from regular scripts.
//#using_animtree ("generic_human"); - This file doesn't call animations directly.



InitCharacterFace()
{
	if ( !anim.useFacialAnims )
		return;

	// Does any per-character initialization which is required by this facial animation script.  
	// InitLevelFace must be called before this function.
	if ( !isDefined( self.a.currentDialogImportance ) )
	{
		self.a.currentDialogImportance = 0;	// Indicates that we are not currently saying anything.
		self.a.idleFace = anim.alertface;
		self.faceWaiting = [];
		self.faceLastNotifyNum = 0;
	}
}


// Makes a character say the specified line in his voice, if he's not already saying something more 
// important.  
SayGenericDialogue( typeString )
{
	// First pick a random voice number for our character.  We have to do this every time because it's 
	// possible for the character to be changed after the level loads (generally right before it starts).
	// Use (entity number) modulus (number of voices) to get a consistent result.

	voicenum = undefined;

	switch ( self.voice )
	{
		case "american":
		case "delta":
		case "czech":
		case "pmc":
		case "french":
		case "taskforce":
		case "seal":
			voiceString = "friendly";
			numVoices = anim.numFriendlyVoices;
			break;
			
		default:
			voiceString = "enemy";
			numVoices = anim.numEnemyVoices;
	}

	ASSERT( isDefined( voiceString ) );
	ASSERT( IsDefined( numVoices ) );
	
	voicenum = 1 + ( self GetEntityNumber() % numVoices );
	
	ASSERT( IsDefined( voicenum ) );
	
	voiceString = voiceString + "_" + voicenum;

	faceAnim = undefined;

	switch( typeString )
	{

	case "meleecharge":
	case "meleeattack":
//		faceAnim = animscripts\face::ChooseAnimFromSet(anim.meleeFace);
		importance = 0.5;
		break;
	case "flashbang":
//		faceAnim = animscripts\face::ChooseAnimFromSet(anim.painFace);
		importance = 0.7;
		break;
	case "pain":
//		faceAnim = animscripts\face::ChooseAnimFromSet(anim.painFace);
		importance = 0.9;
		break;
	case "death":
//		faceAnim = animscripts\face::ChooseAnimFromSet(anim.deathFace);
		importance = 1.0;
		break;
	default:
		println( "Unexpected generic dialog string: " + typeString );
		importance = 0.3;
		break;
	}
	// Now assemble the sound alias and try to play it.
	soundAlias = "generic_" + typeString + "_" + voiceString;
	// Note that faceAnim is allowed to be undefined.
	self thread PlayFaceThread( faceAnim, soundAlias, importance );
}

SetIdleFaceDelayed( facialAnimationArray )
{
	self animscripts\battleChatter::playBattleChatter();

	self.a.idleFace = facialAnimationArray;
}

// Sets the facial expression to return to when not saying dialogue.
// The array is animation1, weight1, animation2, weight2, etc.  The animations will play in turn - each time 
// one finishes a new one will be chosen randomly based on weight.
SetIdleFace( facialAnimationArray )
{
	if ( !anim.useFacialAnims )
		return;

	self animscripts\battleChatter::playBattleChatter();

	self.a.idleFace = facialAnimationArray;
	self PlayIdleFace();
}

// Makes the character play the specified sound and animation.  The anim and the sound are optional - you 
// can just defined one if you don't have both.
// Generally, importance should be in the range of 0.6-0.8 for scripted dialogue.
// Importance is a float, from 0 to 1.  
// 0.0 - Idle expressions
// 0.1-0.5 - most generic dialogue
// 0.6-0.8 - most scripted dialogue 
// 0.9 - pain
// 1.0 - death
// Importance can also be one of these strings: "any", "pain" or "death", which specfies what sounds can 
// interrupt this one.
SaySpecificDialogue( facialanim, soundAlias, importance, notifyString, waitOrNot, timeToWait )
{
	///("SaySpecificDialog, facial: ",facialanim,", sound: ",soundAlias,", importance: "+importance+", notify: ",notifyString, ", WaitOrNot: ", waitOrNot, ", timeToWait: ", timeToWait);#/
	self thread PlayFaceThread( facialanim, soundAlias, importance, notifyString, waitOrNot, timeToWait );
}

// Takes an array with a set of "anim" entries and a corresponding set of "weight" entries.
ChooseAnimFromSet( animSet )
{
	return;	// Facial animations are now part of full body aniamtions
/*
	if (!anim.useFacialAnims)
		return;
	// First, normalize the weights.
	totalWeight = 0;
	numAnims = animSet["anim"].size;
	for ( i=0 ; i<numAnims ; i++ )
	{
		totalWeight += animSet["weight"][i];
	}
	for ( i=0 ; i<numAnims ; i++ )
	{
		animSet["weight"][i] = animSet["weight"][i] / totalWeight;
	}

	// Now choose an animation.
	rand = randomfloat(1);
	runningTotal = 0;
	chosenAnim = undefined;
	for ( i=0 ; i<numAnims ; i++ )
	{
		runningTotal += animSet["weight"][i];
		if (runningTotal >= rand)
		{
			chosenAnim = i;
			break;
		}
	}
	assertEX(isDefined(chosenAnim), "Logic error in ChooseAnimFromSet.  Rand is " + rand + ".");
	return animSet["anim"][chosenAnim];
*/
}



//-----------------------------------------------------
// Housekeeping functions - these are for internal use
//-----------------------------------------------------

// PlayIdleFace doesn't force an idle animation to play - it will interrupt a current idle animation, but it 
// won't play over a more important animation, like dialogue.
PlayIdleFace()
{
	return;	// Idle facial animations are now in the full - body animations.
}

// PlayFaceThread is the workhorse of the system - it checks the importance, and if it's high enough, it 
// plays the animation and/or sound specified.
// The waitOrNot parameter specifies what to do if another animation/sound is already playing.
// Options: "wait" or undefined.  TimeToWait is an optional timeout time for waiting.
// Waiting faces are queued.
PlayFaceThread( facialanim, soundAlias, importance, notifyString, waitOrNot, timeToWait )
{
	self.a.facialAnimDone = true;
	self.a.facialSoundDone = true;
	
	if ( isdefined( notifyString ) )
	{
		if ( isDefined( soundAlias ) )
		{
			self playSoundAtViewHeight( soundAlias, "animscript facesound" + notifyString, true );
			// so placefacethread doesnt block
			self thread WaitForFaceSound( notifyString );
		}
	}
	else
		self playSoundAtViewHeight( soundAlias );

	if ( !anim.useFacialAnims )
		return;

	InitCharacterFace();

	if ( !isDefined( facialanim ) && !isDefined( soundAlias ) )
	{
		// This is not actually an error condition but it might mess up the calling script, so better to catch it now.
		assertEX( 0, "Either facialanim or soundAlias should be defined when calling PlayFaceThread or SaySpecificDialogue" );
		if ( isDefined( notifyString ) )
		{
			wait( 0 );	// This allows the calling script to get to a point where it's waiting for the notify
			self.faceResult = "failed";
			self notify( notifyString );
		}
		return;
	}

	self endon( "death" );

	if ( isString( importance ) )
	{
		switch( importance )
		{
		case "any":
			importance = 0.1;
			break;

		case "pain":
			importance = 0.9;
			break;

		case "death":
			importance = 1.0;
			break;
		}
	}

	if ( ( importance <= self.a.currentDialogImportance ) && ( isDefined( waitOrNot ) && ( waitOrNot == "wait" ) ) )
	{
		//("Face: Waiting to play sound: ",soundAlias,", anim: ",facialanim,", ", notifyString,(", importance "+importance+", old one "+self.a.currentDialogImportance));#/
		// Put this face at the end of the queue
		thisEntryNum = self.faceWaiting.size;
		thisNotifyNum = self.faceLastNotifyNum + 1;
		self.faceWaiting[ thisEntryNum ][ "facialanim" ]	 = facialanim;
		self.faceWaiting[ thisEntryNum ][ "soundAlias" ]	 = soundAlias;
		self.faceWaiting[ thisEntryNum ][ "importance" ]	 = importance;
		self.faceWaiting[ thisEntryNum ][ "notifyString" ]	 = notifyString;
		self.faceWaiting[ thisEntryNum ][ "waitOrNot" ]		 = waitOrNot;
		self.faceWaiting[ thisEntryNum ][ "timeToWait" ]	 = timeToWait;
		self.faceWaiting[ thisEntryNum ][ "notifyNum" ]		 = thisNotifyNum;	// Unique identifier.

		// What we do now is, wait for both the notify and the time.  If the time expires first, we give 
		// up and remove this entry from the queue.  If the notify happens first, we stop waiting for the 
		// time and we play the face.
		self thread PlayFace_WaitForNotify( ( "animscript face stop waiting " + self.faceWaiting[ thisEntryNum ][ "notifyNum" ] ), "Face done waiting", "Face done waiting" );
		if ( isDefined( timeToWait ) )
			self thread PlayFace_WaitForTime( timeToWait, "Face done waiting", "Face done waiting" );
		self waittill( "Face done waiting" );

		// First, find the entry, since it may have been moved.
		thisEntryNum = undefined;
		for ( i = 0 ; i < self.faceWaiting.size ; i++ )
		{
			if ( self.faceWaiting[ i ][ "notifyNum" ] == thisNotifyNum )
			{
				thisEntryNum = i;
				break;
			}
		}
		assertEX( isDefined( thisEntryNum ) );

		if ( self.a.faceWaitForResult == "notify" )
		{
			// Play the face.
			PlayFaceThread( 	self.faceWaiting[ thisEntryNum ][ "facialanim" ],
							self.faceWaiting[ thisEntryNum ][ "soundAlias" ],
							self.faceWaiting[ thisEntryNum ][ "importance" ],
							self.faceWaiting[ thisEntryNum ][ "notifyString" ]
							 );
		}
		else	// ie We timed out.
		{
			if ( isDefined( notifyString ) )
			{
				self.faceResult = "failed";
				self notify( notifyString );
			}
		}

		// Remove this entry from the queue.  If any entries have been added after this one, move them 
		// forward.  
		for ( i = thisEntryNum + 1 ; i < self.faceWaiting.size ; i++ )
		{
			self.faceWaiting[ i - 1 ][ "facialanim" ]		 = self.faceWaiting[ i ][ "facialanim" ];
			self.faceWaiting[ i - 1 ][ "soundAlias" ]		 = self.faceWaiting[ i ][ "soundAlias" ];
			self.faceWaiting[ i - 1 ][ "importance" ]		 = self.faceWaiting[ i ][ "importance" ];
			self.faceWaiting[ i - 1 ][ "notifyString" ]	 = self.faceWaiting[ i ][ "notifyString" ];
			self.faceWaiting[ i - 1 ][ "waitOrNot" ]		 = self.faceWaiting[ i ][ "waitOrNot" ];
			self.faceWaiting[ i - 1 ][ "timeToWait" ]		 = self.faceWaiting[ i ][ "timeToWait" ];
			self.faceWaiting[ i - 1 ][ "notifyNum" ]		 = self.faceWaiting[ i ][ "notifyNum" ];
		}
		self.faceWaiting[ self.faceWaiting.size - 1 ] = undefined;

	}
	else if ( importance >= self.a.currentDialogImportance )
	{
		// End any threads that are waiting on current facial animations or sounds.
		self notify( "end current face" );
		self endon( "end current face" );
		//("Face: Playing facial sound/animation: ", facialanim, ", ",soundAlias,", ",notifyString, ", ",importance);#/
		//if (self.a.currentDialogImportance > 0)
		//{	
			//("Face: Interrupted facial sound/animation: ",self.a.currentDialogSound,", ",self.a.currentDialogNotifyString, ", ",self.a.currentDialogImportance);#/
		//}
		if ( isDefined( notifyString ) )
		{
			if ( isDefined( self.a.currentDialogNotifyString ) )
			{
				self.faceResult = "interrupted";
				self notify( self.a.currentDialogNotifyString );
			}
		}
		// Remember what we're doing, so we can decide what to do if another face tries to interrupt this one.
		self.a.currentDialogImportance = importance;
		self.a.currentDialogSound = soundAlias;	// ( This one is only used for debugging. )
		self.a.currentDialogNotifyString = notifyString;

		// Set finished to true so that if we don't play one of these, we don't have to wait for it to finish.
		self.a.facialAnimDone = true;
		self.a.facialSoundDone = true;
		// Play the anim and sound, if they are defined.
		if ( isDefined( facialanim ) )
		{
//			self setanim(%facial, 0.01, .1, 1);	// This doesn't work for non-AI
			self setflaggedanimknobrestart( "animscript faceanim", facialanim, 1, .1, 1 );
			self.a.facialAnimDone = false;
			self thread WaitForFacialAnim();
			//("Face: Waiting for facial animation ", facialanim);#/
		}
		//else TODO play a generic, looping facial animation.
		if ( isDefined( soundAlias ) )
		{
// TEMP These lines break sound for most lines because of a bug in facial animation (code bug?).  When that 
// bug is fixed, put these lines back in.
//			if ( isDefined(facialanim) && animhasnotetrack(facialanim, "dialogue"))
//			{
//				self waittillmatch ("animscript faceanim", "dialogue");
//			}
			self playSoundAtViewHeight( soundAlias, "animscript facesound", true );
			self.a.facialSoundDone = false;
			self thread WaitForFaceSound();
			//("Face: Waiting for sound ",soundAlias);#/
		}
		// Now wait until both animation and sound are finished
		while ( ( !self.a.facialAnimDone ) || ( !self.a.facialSoundDone ) )
		{
			self waittill( "animscript facedone" );
		}
		// Set importance to 0 so that other facial anims (like the idle) can play.
		//("Face: Finished facial sound: ",soundAlias,", animation: ",facialanim," notify: ",notifyString,", importance ",importance);#/
		self.a.currentDialogImportance = 0;
		self.a.currentDialogSound = undefined;
		self.a.currentDialogNotifyString = undefined;
		if ( isDefined( notifyString ) )
		{
			self.faceResult = "finished";
			self notify( notifyString );
		}
		if ( isDefined( self.faceWaiting ) && ( self.faceWaiting.size > 0 ) )
		{
			// Find out which face we want to play next.  Look through the queue for the highest priority 
			// face.  If we find more than one with the same importance, choose the one that was added first.
			maxImportance = 0;
			nextFaceNum = 1;
			//("Choosing next face.  List is:");#/
			for ( i = 0 ; i < self.faceWaiting.size ; i++ )
			{
				/*
				println]](" ",i," ",	(self.faceWaiting[i]["facialanim"]),", ",
											(self.faceWaiting[i]["soundAlias"]),", ",
											(self.faceWaiting[i]["importance"]),", ",
											(self.faceWaiting[i]["notifyString"])
											);#/
				*/
				if ( self.faceWaiting[ i ][ "importance" ] > maxImportance )
				{
					maxImportance = self.faceWaiting[ i ][ "importance" ];
					nextFaceNum = i;
				}
			}
			//("Chose ", nextFaceNum);#/
			// Notify the entry in the queue, to play.
			self notify( "animscript face stop waiting " + self.faceWaiting[ nextFaceNum ][ "notifyNum" ] );
		}
		else
		{
			// We're done.  Set an idle face going before we exit.
			// TODO Make the idle face play whenever the animation finishes, for cases when it finishes before the sound.
			if ( IsAI( self ) )
			{
				self PlayIdleFace();
			}
		}
	}
	else
	{
		if ( isDefined( notifyString ) )
		{
			self.faceResult = "failed";
			self notify( notifyString );
		}
		//("Face: Didn't play facial sound: ",soundAlias,", animation: ",facialanim," notify: ",notifyString,", importance ",importance,", old one ",self.a.currentDialogImportance);#/
	}
}

WaitForFacialAnim()	// Used solely by PlayFaceThread
{
	self endon( "death" );
	self endon( "end current face" );
	self animscripts\shared::DoNoteTracks( "animscript faceanim" );
	self.a.facialAnimDone = true;
	self notify( "animscript facedone" );
}

WaitForFaceSound( msg )	// Used solely by PlayFaceThread
{
	self endon( "death" );
	self waittill( "animscript facesound" + msg );
	self notify( msg );
}

PlayFace_WaitForNotify( waitForString, notifyString, killmeString )
{
	self endon( "death" );
	self endon( killmeString );
	self waittill( waitForString );
	self.a.faceWaitForResult = "notify";
	self notify( notifyString );
}

PlayFace_WaitForTime( time, notifyString, killmeString )
{
	self endon( "death" );
	self endon( killmeString );
	wait( time );
	self.a.faceWaitForResult = "time";
	self notify( notifyString );
}


#using_animtree( "generic_human" );// This section of the file calls animations directly since it's only used on AI.
InitLevelFace()
{
	// Does per-level initialization of facial stuff.

	// These numbers indicate how many different sound aliases there are in dialog_generic.csv for each 
	// nationality.  This script will assign each guy a random voice number from 1 to the number indicated 
	// for his voice nationality below.  If we add a new voice type to sound_generic.csv, we need to update 
	// these numbers accordingly.
	/* anim.numAmericanVoices = 8;
	anim.numDeltaForceVoices = 8;
	anim.numNavySealVoices = 8;
	anim.numTaskForceVoices = 8;
	anim.numSecretServiceVoices = 8;
	anim.numBritishVoices = 8;
	anim.numRussianVoices = 8;
	anim.numArabVoices = 8;
	anim.numPortugueseVoices = 8;
	anim.numShadowCompanyVoices = 8; */
	anim.numFriendlyVoices = 8;
	anim.numEnemyVoices = 8;
}
