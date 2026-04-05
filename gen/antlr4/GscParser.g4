parser grammar GscParser;

options {
    tokenVocab = GscLexer;
}

@parser::members {
    int version = 1; // Set this based on the version you want to parse
}

// PARSER RULES
program
    : (include | inline | declaration | SEMICOLON)* EOF
    ;

include
    : INCLUDE expr_path SEMICOLON { version != 3 }?
    | USING expr_path SEMICOLON { version == 3 }?
    ;

inline
    : INLINE expr_path SEMICOLON { version == 1 }?
    | INSERT expr_path SEMICOLON { version != 1 }?
    ;

declaration
    : DEVBEGIN
    | DEVEND
    | decl_usingtree
    | decl_constant { version == 1 }?
    | decl_function
    | decl_namespace { version == 3 }?
    | decl_class { version == 3 }?
    ;

decl_usingtree
    : USINGTREE LPAREN expr_string RPAREN SEMICOLON
    ;

decl_constant
    : expr_identifier ASSIGN expr SEMICOLON
    ;

decl_function
    : expr_identifier LPAREN expr_parameters? RPAREN stmt_comp { version == 1 }?
    | (AUTOEXEC | CODECALL | PRIVATE)? expr_identifier LPAREN expr_parameters? RPAREN stmt_comp { version == 2 }?
    | (AUTOEXEC | CODECALL | PRIVATE | INLINE_FLAG)? expr_identifier LPAREN expr_parameters? RPAREN stmt_comp { version == 3 }?
    ;

decl_namespace
    : NAMESPACE expr_identifier SEMICOLON
    ;

decl_class
    : CLASS expr_identifier (COLON expr_identifier)? LBRACE class_list? RBRACE
    ;

class_list
    : class_member+
    ;

class_member
    : decl_function
    | CONSTRUCTOR LPAREN RPAREN stmt_comp
    | DESTRUCTOR LPAREN RPAREN stmt_comp
    ;

stmt
    : stmt_comp
    | stmt_expr
    | stmt_const { version == 2 }?
    | stmt_endon
    | stmt_notify
    | stmt_wait
    | stmt_waittill
    | stmt_waittillmatch
    | stmt_waittillframeend
    | stmt_waitframe { version == 1 }?
    | stmt_waitrealtime { version == 2 }?
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
    | stmt_breakpoint { version == 1 }?
    | stmt_prof_begin
    | stmt_prof_end
    | stmt_assert { version == 1 }?
    | stmt_assertex { version == 1 }?
    | stmt_assertmsg { version == 1 }?
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

stmt_const
    : CONST expr_identifier ASSIGN expr SEMICOLON
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
    : expr_object WAITTILL LPAREN expr (COMMA expr_arguments_waittill)? RPAREN SEMICOLON
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

stmt_waitrealtime
    : WAITREALTIME expr SEMICOLON
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

// pre-inc/dec is not allowed in original GSC!
expr_assign
    : expr_tuple ASSIGN expr  { version == 1 }?
    | expr_lvalue (ASSIGN | ABWOR | ABWXOR | ABWAND | ALSH | ARSH | AADD | ASUB | AMUL | ADIV | AMOD) expr
    | expr_lvalue INCREMENT
    | expr_lvalue DECREMENT
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
    | BW_AND expr_reference { version == 3 }?
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
    : MOD expr_identifier
    | MOD expr_identifier DOUBLECOLON expr_identifier { version != 1 }?
    ;

expr_primary
    : expr_call
    | expr_call_optimized { version == 2 }?
    | expr_call_optimized_vector_array { version == 2 }?
    | expr_reference
    | expr_isdefined
    | expr_istrue { version == 1 }?
    | expr_add_array { version == 1 }?
    | expr_object_subexpr
    | expr_size
    | expr_paren
    | expr_thisthread { version == 1 }?
    | expr_empty_array
    | expr_undefined
    | expr_game
    | expr_self
    | expr_anim
    | expr_level
    | expr_animtree
    | expr_identifier
    | expr_hstring  { version == 2 }?
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
    : THREAD? (expr_path DOUBLECOLON)? expr_identifier LPAREN expr_arguments? RPAREN
    | CHILDTHREAD? (expr_path DOUBLECOLON)? expr_identifier LPAREN expr_arguments? RPAREN { version == 1 }?
    ;

expr_pointer
    : THREAD? LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments? RPAREN
    | (CHILDTHREAD | CALL)? LBRACKET LBRACKET expr RBRACKET RBRACKET LPAREN expr_arguments? RPAREN { version == 1 }?
    | THREAD? LBRACKET LBRACKET expr RBRACKET RBRACKET ARROW expr_identifier LPAREN expr_arguments? RPAREN { version == 3 }?
    ;

expr_call_optimized
    : GETFIRSTARRAYKEY LPAREN expr RPAREN
    | GETNEXTARRAYKEY LPAREN  expr COMMA expr RPAREN
    | GETDVAR LPAREN expr COMMA expr RPAREN
    | GETDVARINT LPAREN expr RPAREN
    | GETDVARFLOAT LPAREN expr RPAREN
    | GETDVARCOLORRED LPAREN expr RPAREN
    | GETDVARCOLORGREEN LPAREN expr RPAREN
    | GETDVARCOLORBLUE LPAREN expr RPAREN
    | GETDVARCOLORALPHA LPAREN expr RPAREN
    | GETTIME LPAREN RPAREN
    | ABS LPAREN expr RPAREN
    | expr_call_optimized_vector
    | NEW expr_identifier LPAREN expr_arguments? RPAREN { version == 3 }?
    ;

expr_call_optimized_vector
    : GETDVARVECTOR LPAREN expr RPAREN
    | VECTORTOANGLES LPAREN expr RPAREN
    | ANGLECLAMP180 LPAREN expr RPAREN
    | ANGLESTOFORWARD LPAREN expr RPAREN
    | ANGLESTORIGHT LPAREN expr RPAREN
    | ANGLESTOUP LPAREN expr RPAREN
    | VECTORSCALE LPAREN expr COMMA expr RPAREN
    ;

expr_call_optimized_vector_array
    : expr_call_optimized_vector expr_array
    ; 

expr_isdefined
    : ISDEFINED LPAREN expr RPAREN
    ;

expr_istrue
    : ISTRUE LPAREN expr RPAREN
    ;

expr_reference
    : expr_path? DOUBLECOLON expr_identifier { version != 3 }?
    | expr_identifier? DOUBLECOLON expr_identifier { version == 3 }?
    ;

expr_parameters
    : expr_identifier (COMMA expr_identifier)* { version == 1 }?
    | expr_parameters_default { version == 2 }?
    ;

expr_parameters_default
    : expr_identifier (ASSIGN expr)? (COMMA expr_identifier (ASSIGN expr)?)*
    ;

expr_arguments
    : expr (COMMA expr)*
    ;

expr_arguments_waittill
    : (expr_identifier | expr_undefined) (COMMA (expr_identifier | expr_undefined))*
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

expr_hstring
    : HSTRING
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
