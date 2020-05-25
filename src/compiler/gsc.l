%{
	#include <stdio.h>
	/* #include "gsc.tab.hpp" */

	#define PRINT_TOKEN(S) printf(S)
%}


%%

[ \t\n\r]				/* skip whitespace & newlines */
"//".*					/* skip single line comments */

"#include"			{ PRINT_TOKEN("INCLUDE, ");}
"#using_animtree"	{ PRINT_TOKEN("USING_ANIMTREE, ");}
"#animtree"			{ PRINT_TOKEN("ANIMTREE, ");}

"level"			{ PRINT_TOKEN("LEVEL, ");}
"game"			{ PRINT_TOKEN("GAME, ");}

.				;

%%

