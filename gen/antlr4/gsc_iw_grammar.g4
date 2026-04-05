grammar gsc_iw_grammar;

// LEXER RULES
HASH: '#';
DEVBEGIN: '/#';
DEVEND: '#/';
INLINE: '#inline';
INCLUDE: '#include';
USINGTREE: '#using_animtree';
ANIMTREE: '#animtree';
ENDON: 'endon';
NOTIFY: 'notify';
WAIT: 'wait';
WAITTILL: 'waittill';
WAITTILLMATCH: 'waittillmatch';
WAITTILLFRAMEEND: 'waittillframeend';
WAITFRAME: 'waitframe';
IF: 'if';
ELSE: 'else';
DO: 'do';
WHILE: 'while';
FOR: 'for';
FOREACH: 'foreach';
IN: 'in';
SWITCH: 'switch';
CASE: 'case';
DEFAULT: 'default';
BREAK: 'break';
CONTINUE: 'continue';
RETURN: 'return';
BREAKPOINT: 'breakpoint';
PROFBEGIN: 'prof_begin';
PROFEND: 'prof_end';
ASSERT: 'assert';
ASSERTEX: 'assertex';
ASSERTMSG: 'assertmsg';
THREAD: 'thread';
CHILDTHREAD: 'childthread';
THISTHREAD: 'thisthread';
CALL: 'call';
TRUE: 'true';
FALSE: 'false';
UNDEFINED: 'undefined';
SIZE: 'size';
GAME: 'game';
SELF: 'self';
ANIM: 'anim';
LEVEL: 'level';
ISDEFINED: 'isdefined';
ISTRUE: 'istrue';
LPAREN: '(';
RPAREN: ')';
LBRACE: '{';
RBRACE: '}';
LBRACKET: '[';
RBRACKET: ']';
COMMA: ',';
DOT: '.';
DOUBLEDOT: '..';
ELLIPSIS: '...';
DOUBLECOLON: '::';
COLON: ':';
SEMICOLON: ';';
QMARK: '?';
INCREMENT: '++';
DECREMENT: '--';
LSHIFT: '<<';
RSHIFT: '>>';
OR: '||';
AND: '&&';
EQUALITY: '==';
INEQUALITY: '!=';
LESS_EQUAL: '<=';
GREATER_EQUAL: '>=';
LESS: '<';
GREATER: '>';
NOT: '!';
COMPLEMENT: '~';
ASSIGN: '=';
AMUL: '*=';
ADIV: '/=';
AMOD: '%=';
AADD: '+=';
ASUB: '-=';
ARSH: '>>=';
ALSH: '<<=';
ABWOR: '|=';
ABWXOR: '^=';
ABWAND: '&=';
BW_OR: '|';
BW_XOR: '^';
BW_AND: '&';
ADD: '+';
SUB: '-';
MUL: '*';
DIV: '/';
MOD: '%';
FLOAT: [0-9]+ '.' [0-9]* 'f'?;
INTEGER: [0-9]+;  
STRING: '"' (~["\\] | '\\' .)* '"';
ISTRING: '&"' (~["\\] | '\\' .)* '"';  
HSTRING: '#d' (~["\\] | '\\' .)* '"';
IDENTIFIER: [a-zA-Z_][a-zA-Z_0-9]*;
PATH: IDENTIFIER ( '\\' IDENTIFIER )+;
WHITESPACE: [ \t\n\r\f]+ -> skip;
LINE_COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
GSCDOC_COMMENT: '/@' .*? '@/' -> skip;

// PARSER RULES
program
    : (include | inline | declaration | SEMICOLON)* EOF
    ;

include
    : INCLUDE expr_path SEMICOLON
    ;

inline
    : INLINE expr_path SEMICOLON
    ;

declaration
    : DEVBEGIN | DEVEND | decl_usingtree | decl_constant | decl_function
    ;

decl_usingtree
    : USINGTREE LPAREN expr_string RPAREN SEMICOLON
    ;

decl_constant
    : expr_identifier ASSIGN expr SEMICOLON
    ;

decl_function
    : expr_identifier LPAREN expr_parameters? RPAREN stmt_comp
    ;

stmt
    : stmt_comp
    | stmt_expr
    | stmt_endon
    | stmt_notify
    | stmt_wait
    | stmt_waittill
    | stmt_waittillmatch
    | stmt_waittillframeend
    | stmt_waitframe
    | stmt_if
    | stmt_while
    | stmt_dowhile
    | stmt_for
    | stmt_foreach
    | stmt_switch
    | stmt_case
    | stmt_default
    | stmt_break
    | stmt_continue
    | stmt_return
    | stmt_breakpoint
    | stmt_prof_begin
    | stmt_prof_end
    | stmt_assert
    | stmt_assertex
    | stmt_assertmsg
    ;

stmt_list
    : stmt+
    ;

stmt_or_dev_list
    : (stmt | stmt_dev)+
    ;

stmt_dev
    : DEVBEGIN stmt_list? DEVEND
    ;

stmt_comp
    : LBRACE stmt_or_dev_list? RBRACE
    ;

stmt_expr
    : (expr_call | expr_method | expr_assign)? SEMICOLON
    ;

stmt_endon
    : expr_object ENDON LPAREN expr RPAREN SEMICOLON
    ;

stmt_notify
    : expr_object NOTIFY LPAREN expr (COMMA expr_arguments)? RPAREN SEMICOLON
    ;

stmt_wait
    : WAIT expr SEMICOLON
    ;

stmt_waittill
    : expr_object WAITTILL LPAREN expr (COMMA expr_arguments)? RPAREN SEMICOLON
    ;

stmt_waittillmatch
    : expr_object WAITTILLMATCH LPAREN expr (COMMA expr_arguments)? RPAREN SEMICOLON
    ;

stmt_waittillframeend
    : WAITTILLFRAMEEND (LPAREN RPAREN)? SEMICOLON
    ;

stmt_waitframe
    : WAITFRAME (LPAREN RPAREN)? SEMICOLON
    ;

stmt_if
    : IF LPAREN expr RPAREN stmt (ELSE stmt)?
    ;

stmt_while
    : WHILE LPAREN expr RPAREN stmt
    ;

stmt_dowhile
    : DO stmt WHILE LPAREN expr RPAREN SEMICOLON
    ;

stmt_for
    : FOR LPAREN expr_assign? SEMICOLON expr? SEMICOLON expr_assign? RPAREN stmt
    ;

stmt_foreach
    : FOREACH LPAREN expr_identifier (COMMA expr_identifier)? IN expr RPAREN stmt
    ;

stmt_switch
    : SWITCH LPAREN expr RPAREN stmt_comp
    ;

stmt_case
    : CASE (expr_integer | expr_string) COLON
    ;

stmt_default
    : DEFAULT COLON
    ;

stmt_break
    : BREAK SEMICOLON
    ;

stmt_continue
    : CONTINUE SEMICOLON
    ;

stmt_return
    : RETURN expr? SEMICOLON
    ;

stmt_breakpoint
    : BREAKPOINT SEMICOLON
    ;

stmt_prof_begin
    : PROFBEGIN LPAREN expr_arguments? RPAREN SEMICOLON
    ;

stmt_prof_end
    : PROFEND LPAREN expr_arguments? RPAREN SEMICOLON
    ;

stmt_assert
    : ASSERT LPAREN expr_arguments? RPAREN SEMICOLON
    ;

stmt_assertex
    : ASSERTEX LPAREN expr_arguments? RPAREN SEMICOLON
    ;

stmt_assertmsg
    : ASSERTMSG LPAREN expr_arguments? RPAREN SEMICOLON
    ;

expr_assign
    : expr_tuple ASSIGN expr
    | expr_lvalue (ASSIGN | ABWOR | ABWXOR | ABWAND | ALSH | ARSH | AADD | ASUB | AMUL | ADIV | AMOD) expr
    | INCREMENT expr_lvalue | expr_lvalue INCREMENT
    | DECREMENT expr_lvalue | expr_lvalue DECREMENT
    ;

expr
    : expr_ternary
    ;

expr_ternary
    : expr_or (QMARK expr COLON expr_ternary)?
    ;

expr_or
    : expr_and (OR expr_and)*
    ;

expr_and
    : expr_bw_or ((AND) expr_bw_or)*
    ;

expr_bw_or
    : expr_bw_xor ((BW_OR) expr_bw_xor)*
    ;

expr_bw_xor
    : expr_bw_and ((BW_XOR) expr_bw_and)*
    ;

expr_bw_and
    : expr_equality ((BW_AND) expr_equality)*
    ;

expr_equality
    : expr_relational ((EQUALITY | INEQUALITY) expr_relational)*
    ;

expr_relational
    : expr_shift ((LESS | LESS_EQUAL | GREATER | GREATER_EQUAL) expr_shift)*
    ;

expr_shift
    : expr_additive ((LSHIFT | RSHIFT) expr_additive)*
    ;

expr_additive
    : expr_multiplicative ((ADD | SUB) expr_multiplicative)*
    ;

expr_multiplicative
    : expr_unary ((MUL | DIV | MOD) expr_unary)*
    ;

expr_unary
    : expr_complement | expr_not | expr_negate | expr_animation | expr_primary
    ;

expr_complement
    : COMPLEMENT expr_unary
    ;

expr_not
    : NOT expr_unary
    ;

expr_negate
    : SUB (expr_float | expr_integer | expr_identifier | expr_paren | expr_object_subexpr)
    ;

expr_animation
    : MOD IDENTIFIER
    ;

expr_primary
    : expr_call
    | expr_reference
    | expr_isdefined
    | expr_istrue
    | expr_add_array
    | expr_object_subexpr
    | expr_size
    | expr_paren
    | expr_thisthread
    | expr_empty_array
    | expr_undefined
    | expr_game
    | expr_self
    | expr_anim
    | expr_level
    | expr_animtree
    | expr_identifier
    | expr_istring
    | expr_string
    | expr_vector
    | expr_float
    | expr_integer
    | expr_false
    | expr_true
    ;

expr_call
    : expr_function | expr_pointer
    ;

expr_method
    : expr_object (expr_function | expr_pointer)
    ;

expr_function
    : (THREAD | CHILDTHREAD)? (expr_path DOUBLECOLON)? expr_identifier LPAREN expr_arguments? RPAREN
    ;

expr_pointer
    : (THREAD | CHILDTHREAD | CALL)? LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments? RPAREN
    ;

expr_isdefined
    : ISDEFINED LPAREN expr RPAREN
    ;

expr_istrue
    : ISTRUE LPAREN expr RPAREN
    ;

expr_reference
    : expr_path? DOUBLECOLON expr_identifier
    ;

expr_parameters
    : expr_identifier (COMMA expr_identifier)*
    ;

expr_arguments
    : expr (COMMA expr)*
    ;

expr_tuple
    : LBRACKET expr_lvalue (COMMA expr_lvalue)* RBRACKET
    ;

expr_add_array
    : LBRACKET expr_arguments RBRACKET
    ;

expr_paren
    : LPAREN expr RPAREN
    ;

expr_lvalue
    : expr_identifier | expr_lvalue_array | expr_lvalue_field
    ;

expr_lvalue_array
    : expr_object_subexpr_no_call LBRACKET expr RBRACKET
    ;

expr_lvalue_field
    : expr_object_subexpr DOT expr_identifier_field
    ;

expr_object
    : expr_call
    | expr_identifier
    | expr_game
    | expr_self
    | expr_anim
    | expr_level
    | expr_object_subexpr
    ;

expr_object_subexpr
    : expr_call expr_array_or_field_or_call*
    | expr_identifier expr_array_or_field_or_call*
    | expr_game expr_array+ expr_array_or_field_or_call*
    | expr_self expr_array_or_field_or_call+
    | expr_anim expr_field+ expr_array_or_field_or_call*
    | expr_level expr_field+ expr_array_or_field_or_call*
    ;

expr_object_subexpr_no_call
    : expr_identifier expr_array_or_field*
    | expr_game expr_array+ expr_array_or_field*
    | expr_self expr_array_or_field+
    | expr_anim expr_field+ expr_array_or_field*
    | expr_level expr_field+ expr_array_or_field*
    ;

expr_array_or_field_or_call
    : LBRACKET expr RBRACKET
    | DOT expr_identifier_field
    | expr_call
    ;

expr_array_or_field
    : LBRACKET expr RBRACKET 
    | DOT expr_identifier_field
    ;

expr_array
    : LBRACKET expr RBRACKET
    ;

expr_field
    : DOT expr_identifier_field
    ;

expr_size
    : ( expr_object | expr_string ) DOT SIZE
    ;

expr_thisthread
    : THISTHREAD
    ;

expr_empty_array
    : LBRACKET RBRACKET
    ;

expr_undefined
    : UNDEFINED
    ;

expr_game
    : GAME
    ;

expr_self
    : SELF
    ;

expr_anim
    : ANIM
    ;

expr_level
    : LEVEL
    ;

expr_animtree
    : ANIMTREE
    ;

expr_vector
    : LPAREN expr COMMA expr COMMA expr RPAREN
    ;

expr_path
    : PATH | IDENTIFIER
    ;

expr_identifier_field
    : IDENTIFIER | WAIT
    ;

expr_identifier
    : IDENTIFIER | SIZE
    ;

expr_istring
    : ISTRING
    ;

expr_string
    : STRING
    ;

expr_float
    : FLOAT
    ;

expr_integer
    : INTEGER
    ;

expr_false
    : FALSE
    ;

expr_true
    : TRUE
    ;
