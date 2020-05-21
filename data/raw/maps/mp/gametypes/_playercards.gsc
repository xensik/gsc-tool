#include common_scripts\utility;
#include maps\mp\_utility;


init()
{	
	level thread onPlayerConnect();
}


onPlayerConnect()
{
	for(;;)
	{
		level waittill( "connected", player );

		//@NOTE: Should we make sure they're really unlocked before setting them? Catch cheaters...
		//			e.g. isItemUnlocked( iconHandle )

		iconIndex = player maps\mp\gametypes\_persistence::statGet( "cardIcon" );
		iconHandle = TableLookupByRow( "mp/cardIconTable_strm.csv", iconIndex, 0 );
		player SetCardIcon( iconHandle );
		
		titleIndex = player maps\mp\gametypes\_persistence::statGet( "cardTitle" );
		titleHandle = TableLookupByRow( "mp/cardTitleTable_strm.csv", titleIndex, 0 );
		player SetCardTitle( titleHandle );
		
		nameplateHandle = player maps\mp\gametypes\_persistence::statGet( "cardNameplate" );
		player SetCardNameplate( nameplateHandle );
	}
}