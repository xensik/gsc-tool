#include animscripts\utility;
#include animscripts\traverse\shared;
#using_animtree( "generic_human" );

main()
{
	if ( self.type == "dog" )
		dog_jump_up( 38.0, 5 );
	else
		low_wall_human();
}

low_wall_human()
{
	traverseData = [];
	traverseData[ "traverseAnim" ]			 = %berlin_jumping_column_sandman;
	traverseData[ "traverseHeight" ]		 = 38.0;

	DoTraverse( traverseData );
}
