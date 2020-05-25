#pragma once

// mapping this to check later inside yyparse() what type of nodes are created for each statement
enum node_type 
{
					// re: type  2 assignment statement
					// re: type  5 local variable
					// re: type  7 EmitOrEvalExpression
					// re: type  8 EmitOrEvalPrimitiveExpression
					// re: type 15 array variable
					// re: type 15 field variable
					// re: type 19 variable expresion
					// re: type 20 get function
					// re: type 21 call expression
					// re: type 22 ENUM_local_function ? not sure
					// re: type 23 ENUM_far_function
					// re: type 25 builtin call
					// re: type 26 builtin method
					// re: type 27 call expression
					// re: type 29 return statement
					// re: type 30 end statement
					// re: type 31 wait statement
					// re: type 34 self keyword
					// re: type 36 level keyword
					// re: type 37 game keyword
					// re: type 38 anim keyword
					// re: type 39 if statement
					// re: type 40 if-else statement
					// re: type 41 while statement
					// re: type 42 for statement
					// re: type 43 increment statement
					// re: type 44 decrement statement
					// re: type 45 binary eq operator expression
					// re: type 46 statement list
					// re: type 47 dev statement list
					// re: type 48  field object expresion list
					// re: type 49 bool_or statement
					// re: type 50 bool_and statement list
					// re: type 51 EmitOrEvalBinaryOperatorExpression
					// re: type 52 expresion and EmitBoolNot 
					// re: type 52 expresion and EmitBoolComplement
					// re: type 54 size  '.size'
					// re: type 55 self field assignment
					// re: type 57 waittill statement
					// re: type 58 waittillmatch statement
					// re: type 59 waittillframeend statement
					// re: type 60 notify statement   'notify' 'STRING' EXPR
					// re: type 61 endon statement    'endon' 'B' 'STRING' 'B'
					// re: type 62 switch statement    'switch' STMT_LIST
					// re: type 63 case statement     'case'
					// re: type 64 default statement  'default'
					// re: type 65 break statement    'break;'
					// re: type 66 continue statement 'continue;'
					// re: type 70 something bout thread position. seems like 'function type' func name regex?
					// re: type 71 is '/#' dev_block start
					// re: type 72 is '#/' dev_block end
					// re: type 73 is ' #using_animtree'
					// re: type 78 breakpoint statement
					// re: type 79 profbegin statement
					// re: type 80 profend statement
					// re: type 82 object emit
	NODE_INCLUDE,	// re: type 88 '#include'
};

union sval_u
{
	sval_u* node;
	uint8_t type;
};

class parsetree
{
	static sval_u* alloc_node(size_t size);
	static sval_u node1_(std::int32_t val1);
	static sval_u node2_(sval_u val1, sval_u val2);
	static sval_u node0(uint8_t type);
	static sval_u node1(uint8_t type, sval_u val1);
	static sval_u node2(uint8_t type, sval_u val1, sval_u val2);
	static sval_u node3(uint8_t type, sval_u val1, sval_u val2, sval_u val3);
	static sval_u node4(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4);
	static sval_u node5(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5);
	static sval_u node6(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6);
	static sval_u node7(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7);
	static sval_u node8(uint8_t type, sval_u val1, sval_u val2, sval_u val3, sval_u val4, sval_u val5, sval_u val6, sval_u val7, sval_u val8);
	static sval_u linked_list(sval_u val);
	static sval_u prepend_node(sval_u val1, sval_u val2);
	static sval_u append_node(sval_u val1, sval_u val2);
};
