
// Generated from gsc_iw_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  gsc_iw_grammarParser : public antlr4::Parser {
public:
  enum {
    HASH = 1, DEVBEGIN = 2, DEVEND = 3, INLINE = 4, INCLUDE = 5, USINGTREE = 6, 
    ANIMTREE = 7, ENDON = 8, NOTIFY = 9, WAIT = 10, WAITTILL = 11, WAITTILLMATCH = 12, 
    WAITTILLFRAMEEND = 13, WAITFRAME = 14, IF = 15, ELSE = 16, DO = 17, 
    WHILE = 18, FOR = 19, FOREACH = 20, IN = 21, SWITCH = 22, CASE = 23, 
    DEFAULT = 24, BREAK = 25, CONTINUE = 26, RETURN = 27, BREAKPOINT = 28, 
    PROFBEGIN = 29, PROFEND = 30, ASSERT = 31, ASSERTEX = 32, ASSERTMSG = 33, 
    THREAD = 34, CHILDTHREAD = 35, THISTHREAD = 36, CALL = 37, TRUE = 38, 
    FALSE = 39, UNDEFINED = 40, SIZE = 41, GAME = 42, SELF = 43, ANIM = 44, 
    LEVEL = 45, ISDEFINED = 46, ISTRUE = 47, LPAREN = 48, RPAREN = 49, LBRACE = 50, 
    RBRACE = 51, LBRACKET = 52, RBRACKET = 53, COMMA = 54, DOT = 55, DOUBLEDOT = 56, 
    ELLIPSIS = 57, DOUBLECOLON = 58, COLON = 59, SEMICOLON = 60, QMARK = 61, 
    INCREMENT = 62, DECREMENT = 63, LSHIFT = 64, RSHIFT = 65, OR = 66, AND = 67, 
    EQUALITY = 68, INEQUALITY = 69, LESS_EQUAL = 70, GREATER_EQUAL = 71, 
    LESS = 72, GREATER = 73, NOT = 74, COMPLEMENT = 75, ASSIGN = 76, AMUL = 77, 
    ADIV = 78, AMOD = 79, AADD = 80, ASUB = 81, ARSH = 82, ALSH = 83, ABWOR = 84, 
    ABWXOR = 85, ABWAND = 86, BW_OR = 87, BW_XOR = 88, BW_AND = 89, ADD = 90, 
    SUB = 91, MUL = 92, DIV = 93, MOD = 94, FLOAT = 95, INTEGER = 96, STRING = 97, 
    ISTRING = 98, HSTRING = 99, IDENTIFIER = 100, PATH = 101, WHITESPACE = 102, 
    LINE_COMMENT = 103, BLOCK_COMMENT = 104, GSCDOC_COMMENT = 105
  };

  enum {
    RuleProgram = 0, RuleInclude = 1, RuleInline = 2, RuleDeclaration = 3, 
    RuleDecl_usingtree = 4, RuleDecl_constant = 5, RuleDecl_function = 6, 
    RuleStmt = 7, RuleStmt_list = 8, RuleStmt_or_dev_list = 9, RuleStmt_dev = 10, 
    RuleStmt_comp = 11, RuleStmt_expr = 12, RuleStmt_endon = 13, RuleStmt_notify = 14, 
    RuleStmt_wait = 15, RuleStmt_waittill = 16, RuleStmt_waittillmatch = 17, 
    RuleStmt_waittillframeend = 18, RuleStmt_waitframe = 19, RuleStmt_if = 20, 
    RuleStmt_while = 21, RuleStmt_dowhile = 22, RuleStmt_for = 23, RuleStmt_foreach = 24, 
    RuleStmt_switch = 25, RuleStmt_case = 26, RuleStmt_default = 27, RuleStmt_break = 28, 
    RuleStmt_continue = 29, RuleStmt_return = 30, RuleStmt_breakpoint = 31, 
    RuleStmt_prof_begin = 32, RuleStmt_prof_end = 33, RuleStmt_assert = 34, 
    RuleStmt_assertex = 35, RuleStmt_assertmsg = 36, RuleExpr_assign = 37, 
    RuleExpr = 38, RuleExpr_ternary = 39, RuleExpr_or = 40, RuleExpr_and = 41, 
    RuleExpr_bw_or = 42, RuleExpr_bw_xor = 43, RuleExpr_bw_and = 44, RuleExpr_equality = 45, 
    RuleExpr_relational = 46, RuleExpr_shift = 47, RuleExpr_additive = 48, 
    RuleExpr_multiplicative = 49, RuleExpr_unary = 50, RuleExpr_complement = 51, 
    RuleExpr_negate = 52, RuleExpr_animation = 53, RuleExpr_primary = 54, 
    RuleExpr_call = 55, RuleExpr_method = 56, RuleExpr_function = 57, RuleExpr_pointer = 58, 
    RuleExpr_isdefined = 59, RuleExpr_istrue = 60, RuleExpr_reference = 61, 
    RuleExpr_parameters = 62, RuleExpr_arguments = 63, RuleExpr_tuple = 64, 
    RuleExpr_add_array = 65, RuleExpr_paren = 66, RuleExpr_lvalue = 67, 
    RuleExpr_lvalue_array = 68, RuleExpr_lvalue_field = 69, RuleExpr_object = 70, 
    RuleExpr_object_subexpr = 71, RuleExpr_object_subexpr_no_call = 72, 
    RuleExpr_array_or_field_or_call = 73, RuleExpr_array_or_field = 74, 
    RuleExpr_array = 75, RuleExpr_field = 76, RuleExpr_size = 77, RuleExpr_thisthread = 78, 
    RuleExpr_empty_array = 79, RuleExpr_undefined = 80, RuleExpr_game = 81, 
    RuleExpr_self = 82, RuleExpr_anim = 83, RuleExpr_level = 84, RuleExpr_animtree = 85, 
    RuleExpr_vector = 86, RuleExpr_path = 87, RuleExpr_identifier_field = 88, 
    RuleExpr_identifier = 89, RuleExpr_istring = 90, RuleExpr_string = 91, 
    RuleExpr_float = 92, RuleExpr_integer = 93, RuleExpr_false = 94, RuleExpr_true = 95
  };

  explicit gsc_iw_grammarParser(antlr4::TokenStream *input);

  gsc_iw_grammarParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~gsc_iw_grammarParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class IncludeContext;
  class InlineContext;
  class DeclarationContext;
  class Decl_usingtreeContext;
  class Decl_constantContext;
  class Decl_functionContext;
  class StmtContext;
  class Stmt_listContext;
  class Stmt_or_dev_listContext;
  class Stmt_devContext;
  class Stmt_compContext;
  class Stmt_exprContext;
  class Stmt_endonContext;
  class Stmt_notifyContext;
  class Stmt_waitContext;
  class Stmt_waittillContext;
  class Stmt_waittillmatchContext;
  class Stmt_waittillframeendContext;
  class Stmt_waitframeContext;
  class Stmt_ifContext;
  class Stmt_whileContext;
  class Stmt_dowhileContext;
  class Stmt_forContext;
  class Stmt_foreachContext;
  class Stmt_switchContext;
  class Stmt_caseContext;
  class Stmt_defaultContext;
  class Stmt_breakContext;
  class Stmt_continueContext;
  class Stmt_returnContext;
  class Stmt_breakpointContext;
  class Stmt_prof_beginContext;
  class Stmt_prof_endContext;
  class Stmt_assertContext;
  class Stmt_assertexContext;
  class Stmt_assertmsgContext;
  class Expr_assignContext;
  class ExprContext;
  class Expr_ternaryContext;
  class Expr_orContext;
  class Expr_andContext;
  class Expr_bw_orContext;
  class Expr_bw_xorContext;
  class Expr_bw_andContext;
  class Expr_equalityContext;
  class Expr_relationalContext;
  class Expr_shiftContext;
  class Expr_additiveContext;
  class Expr_multiplicativeContext;
  class Expr_unaryContext;
  class Expr_complementContext;
  class Expr_negateContext;
  class Expr_animationContext;
  class Expr_primaryContext;
  class Expr_callContext;
  class Expr_methodContext;
  class Expr_functionContext;
  class Expr_pointerContext;
  class Expr_isdefinedContext;
  class Expr_istrueContext;
  class Expr_referenceContext;
  class Expr_parametersContext;
  class Expr_argumentsContext;
  class Expr_tupleContext;
  class Expr_add_arrayContext;
  class Expr_parenContext;
  class Expr_lvalueContext;
  class Expr_lvalue_arrayContext;
  class Expr_lvalue_fieldContext;
  class Expr_objectContext;
  class Expr_object_subexprContext;
  class Expr_object_subexpr_no_callContext;
  class Expr_array_or_field_or_callContext;
  class Expr_array_or_fieldContext;
  class Expr_arrayContext;
  class Expr_fieldContext;
  class Expr_sizeContext;
  class Expr_thisthreadContext;
  class Expr_empty_arrayContext;
  class Expr_undefinedContext;
  class Expr_gameContext;
  class Expr_selfContext;
  class Expr_animContext;
  class Expr_levelContext;
  class Expr_animtreeContext;
  class Expr_vectorContext;
  class Expr_pathContext;
  class Expr_identifier_fieldContext;
  class Expr_identifierContext;
  class Expr_istringContext;
  class Expr_stringContext;
  class Expr_floatContext;
  class Expr_integerContext;
  class Expr_falseContext;
  class Expr_trueContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<IncludeContext *> include();
    IncludeContext* include(size_t i);
    std::vector<InlineContext *> inline_();
    InlineContext* inline_(size_t i);
    std::vector<DeclarationContext *> declaration();
    DeclarationContext* declaration(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ProgramContext* program();

  class  IncludeContext : public antlr4::ParserRuleContext {
  public:
    IncludeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INCLUDE();
    Expr_pathContext *expr_path();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IncludeContext* include();

  class  InlineContext : public antlr4::ParserRuleContext {
  public:
    InlineContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INLINE();
    Expr_pathContext *expr_path();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InlineContext* inline_();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEVBEGIN();
    antlr4::tree::TerminalNode *DEVEND();
    Decl_usingtreeContext *decl_usingtree();
    Decl_constantContext *decl_constant();
    Decl_functionContext *decl_function();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeclarationContext* declaration();

  class  Decl_usingtreeContext : public antlr4::ParserRuleContext {
  public:
    Decl_usingtreeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *USINGTREE();
    antlr4::tree::TerminalNode *LPAREN();
    Expr_stringContext *expr_string();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Decl_usingtreeContext* decl_usingtree();

  class  Decl_constantContext : public antlr4::ParserRuleContext {
  public:
    Decl_constantContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_identifierContext *expr_identifier();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Decl_constantContext* decl_constant();

  class  Decl_functionContext : public antlr4::ParserRuleContext {
  public:
    Decl_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_identifierContext *expr_identifier();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Stmt_compContext *stmt_comp();
    Expr_parametersContext *expr_parameters();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Decl_functionContext* decl_function();

  class  StmtContext : public antlr4::ParserRuleContext {
  public:
    StmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Stmt_compContext *stmt_comp();
    Stmt_exprContext *stmt_expr();
    Stmt_endonContext *stmt_endon();
    Stmt_notifyContext *stmt_notify();
    Stmt_waitContext *stmt_wait();
    Stmt_waittillContext *stmt_waittill();
    Stmt_waittillmatchContext *stmt_waittillmatch();
    Stmt_waittillframeendContext *stmt_waittillframeend();
    Stmt_waitframeContext *stmt_waitframe();
    Stmt_ifContext *stmt_if();
    Stmt_whileContext *stmt_while();
    Stmt_dowhileContext *stmt_dowhile();
    Stmt_forContext *stmt_for();
    Stmt_foreachContext *stmt_foreach();
    Stmt_switchContext *stmt_switch();
    Stmt_caseContext *stmt_case();
    Stmt_defaultContext *stmt_default();
    Stmt_breakContext *stmt_break();
    Stmt_continueContext *stmt_continue();
    Stmt_returnContext *stmt_return();
    Stmt_breakpointContext *stmt_breakpoint();
    Stmt_prof_beginContext *stmt_prof_begin();
    Stmt_prof_endContext *stmt_prof_end();
    Stmt_assertContext *stmt_assert();
    Stmt_assertexContext *stmt_assertex();
    Stmt_assertmsgContext *stmt_assertmsg();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StmtContext* stmt();

  class  Stmt_listContext : public antlr4::ParserRuleContext {
  public:
    Stmt_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_listContext* stmt_list();

  class  Stmt_or_dev_listContext : public antlr4::ParserRuleContext {
  public:
    Stmt_or_dev_listContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    std::vector<Stmt_devContext *> stmt_dev();
    Stmt_devContext* stmt_dev(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_or_dev_listContext* stmt_or_dev_list();

  class  Stmt_devContext : public antlr4::ParserRuleContext {
  public:
    Stmt_devContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEVBEGIN();
    antlr4::tree::TerminalNode *DEVEND();
    Stmt_listContext *stmt_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_devContext* stmt_dev();

  class  Stmt_compContext : public antlr4::ParserRuleContext {
  public:
    Stmt_compContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACE();
    antlr4::tree::TerminalNode *RBRACE();
    Stmt_or_dev_listContext *stmt_or_dev_list();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_compContext* stmt_comp();

  class  Stmt_exprContext : public antlr4::ParserRuleContext {
  public:
    Stmt_exprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_callContext *expr_call();
    Expr_methodContext *expr_method();
    Expr_assignContext *expr_assign();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_exprContext* stmt_expr();

  class  Stmt_endonContext : public antlr4::ParserRuleContext {
  public:
    Stmt_endonContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_objectContext *expr_object();
    antlr4::tree::TerminalNode *ENDON();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_endonContext* stmt_endon();

  class  Stmt_notifyContext : public antlr4::ParserRuleContext {
  public:
    Stmt_notifyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_objectContext *expr_object();
    antlr4::tree::TerminalNode *NOTIFY();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *COMMA();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_notifyContext* stmt_notify();

  class  Stmt_waitContext : public antlr4::ParserRuleContext {
  public:
    Stmt_waitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WAIT();
    ExprContext *expr();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_waitContext* stmt_wait();

  class  Stmt_waittillContext : public antlr4::ParserRuleContext {
  public:
    Stmt_waittillContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_objectContext *expr_object();
    antlr4::tree::TerminalNode *WAITTILL();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *COMMA();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_waittillContext* stmt_waittill();

  class  Stmt_waittillmatchContext : public antlr4::ParserRuleContext {
  public:
    Stmt_waittillmatchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_objectContext *expr_object();
    antlr4::tree::TerminalNode *WAITTILLMATCH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *COMMA();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_waittillmatchContext* stmt_waittillmatch();

  class  Stmt_waittillframeendContext : public antlr4::ParserRuleContext {
  public:
    Stmt_waittillframeendContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WAITTILLFRAMEEND();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_waittillframeendContext* stmt_waittillframeend();

  class  Stmt_waitframeContext : public antlr4::ParserRuleContext {
  public:
    Stmt_waitframeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WAITFRAME();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_waitframeContext* stmt_waitframe();

  class  Stmt_ifContext : public antlr4::ParserRuleContext {
  public:
    Stmt_ifContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<StmtContext *> stmt();
    StmtContext* stmt(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_ifContext* stmt_if();

  class  Stmt_whileContext : public antlr4::ParserRuleContext {
  public:
    Stmt_whileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    StmtContext *stmt();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_whileContext* stmt_while();

  class  Stmt_dowhileContext : public antlr4::ParserRuleContext {
  public:
    Stmt_dowhileContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DO();
    StmtContext *stmt();
    antlr4::tree::TerminalNode *WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_dowhileContext* stmt_dowhile();

  class  Stmt_forContext : public antlr4::ParserRuleContext {
  public:
    Stmt_forContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    StmtContext *stmt();
    std::vector<Expr_assignContext *> expr_assign();
    Expr_assignContext* expr_assign(size_t i);
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_forContext* stmt_for();

  class  Stmt_foreachContext : public antlr4::ParserRuleContext {
  public:
    Stmt_foreachContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOREACH();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<Expr_identifierContext *> expr_identifier();
    Expr_identifierContext* expr_identifier(size_t i);
    antlr4::tree::TerminalNode *IN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    StmtContext *stmt();
    antlr4::tree::TerminalNode *COMMA();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_foreachContext* stmt_foreach();

  class  Stmt_switchContext : public antlr4::ParserRuleContext {
  public:
    Stmt_switchContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SWITCH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    Stmt_compContext *stmt_comp();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_switchContext* stmt_switch();

  class  Stmt_caseContext : public antlr4::ParserRuleContext {
  public:
    Stmt_caseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CASE();
    antlr4::tree::TerminalNode *COLON();
    Expr_integerContext *expr_integer();
    Expr_stringContext *expr_string();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_caseContext* stmt_case();

  class  Stmt_defaultContext : public antlr4::ParserRuleContext {
  public:
    Stmt_defaultContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *COLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_defaultContext* stmt_default();

  class  Stmt_breakContext : public antlr4::ParserRuleContext {
  public:
    Stmt_breakContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_breakContext* stmt_break();

  class  Stmt_continueContext : public antlr4::ParserRuleContext {
  public:
    Stmt_continueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_continueContext* stmt_continue();

  class  Stmt_returnContext : public antlr4::ParserRuleContext {
  public:
    Stmt_returnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RETURN();
    antlr4::tree::TerminalNode *SEMICOLON();
    ExprContext *expr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_returnContext* stmt_return();

  class  Stmt_breakpointContext : public antlr4::ParserRuleContext {
  public:
    Stmt_breakpointContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BREAKPOINT();
    antlr4::tree::TerminalNode *SEMICOLON();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_breakpointContext* stmt_breakpoint();

  class  Stmt_prof_beginContext : public antlr4::ParserRuleContext {
  public:
    Stmt_prof_beginContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROFBEGIN();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_prof_beginContext* stmt_prof_begin();

  class  Stmt_prof_endContext : public antlr4::ParserRuleContext {
  public:
    Stmt_prof_endContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROFEND();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_prof_endContext* stmt_prof_end();

  class  Stmt_assertContext : public antlr4::ParserRuleContext {
  public:
    Stmt_assertContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSERT();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_assertContext* stmt_assert();

  class  Stmt_assertexContext : public antlr4::ParserRuleContext {
  public:
    Stmt_assertexContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSERTEX();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_assertexContext* stmt_assertex();

  class  Stmt_assertmsgContext : public antlr4::ParserRuleContext {
  public:
    Stmt_assertmsgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSERTMSG();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMICOLON();
    Expr_argumentsContext *expr_arguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Stmt_assertmsgContext* stmt_assertmsg();

  class  Expr_assignContext : public antlr4::ParserRuleContext {
  public:
    Expr_assignContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_tupleContext *expr_tuple();
    antlr4::tree::TerminalNode *ASSIGN();
    ExprContext *expr();
    Expr_lvalueContext *expr_lvalue();
    antlr4::tree::TerminalNode *ABWOR();
    antlr4::tree::TerminalNode *ABWXOR();
    antlr4::tree::TerminalNode *ABWAND();
    antlr4::tree::TerminalNode *ALSH();
    antlr4::tree::TerminalNode *ARSH();
    antlr4::tree::TerminalNode *AADD();
    antlr4::tree::TerminalNode *ASUB();
    antlr4::tree::TerminalNode *AMUL();
    antlr4::tree::TerminalNode *ADIV();
    antlr4::tree::TerminalNode *AMOD();
    antlr4::tree::TerminalNode *INCREMENT();
    antlr4::tree::TerminalNode *DECREMENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_assignContext* expr_assign();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_ternaryContext *expr_ternary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExprContext* expr();

  class  Expr_ternaryContext : public antlr4::ParserRuleContext {
  public:
    Expr_ternaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_orContext *expr_or();
    antlr4::tree::TerminalNode *QMARK();
    ExprContext *expr();
    antlr4::tree::TerminalNode *COLON();
    Expr_ternaryContext *expr_ternary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_ternaryContext* expr_ternary();

  class  Expr_orContext : public antlr4::ParserRuleContext {
  public:
    Expr_orContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_andContext *> expr_and();
    Expr_andContext* expr_and(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_orContext* expr_or();

  class  Expr_andContext : public antlr4::ParserRuleContext {
  public:
    Expr_andContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_bw_orContext *> expr_bw_or();
    Expr_bw_orContext* expr_bw_or(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_andContext* expr_and();

  class  Expr_bw_orContext : public antlr4::ParserRuleContext {
  public:
    Expr_bw_orContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_bw_xorContext *> expr_bw_xor();
    Expr_bw_xorContext* expr_bw_xor(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BW_OR();
    antlr4::tree::TerminalNode* BW_OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_bw_orContext* expr_bw_or();

  class  Expr_bw_xorContext : public antlr4::ParserRuleContext {
  public:
    Expr_bw_xorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_bw_andContext *> expr_bw_and();
    Expr_bw_andContext* expr_bw_and(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BW_XOR();
    antlr4::tree::TerminalNode* BW_XOR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_bw_xorContext* expr_bw_xor();

  class  Expr_bw_andContext : public antlr4::ParserRuleContext {
  public:
    Expr_bw_andContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_equalityContext *> expr_equality();
    Expr_equalityContext* expr_equality(size_t i);
    std::vector<antlr4::tree::TerminalNode *> BW_AND();
    antlr4::tree::TerminalNode* BW_AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_bw_andContext* expr_bw_and();

  class  Expr_equalityContext : public antlr4::ParserRuleContext {
  public:
    Expr_equalityContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_relationalContext *> expr_relational();
    Expr_relationalContext* expr_relational(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQUALITY();
    antlr4::tree::TerminalNode* EQUALITY(size_t i);
    std::vector<antlr4::tree::TerminalNode *> INEQUALITY();
    antlr4::tree::TerminalNode* INEQUALITY(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_equalityContext* expr_equality();

  class  Expr_relationalContext : public antlr4::ParserRuleContext {
  public:
    Expr_relationalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_shiftContext *> expr_shift();
    Expr_shiftContext* expr_shift(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS();
    antlr4::tree::TerminalNode* LESS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LESS_EQUAL();
    antlr4::tree::TerminalNode* LESS_EQUAL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER();
    antlr4::tree::TerminalNode* GREATER(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GREATER_EQUAL();
    antlr4::tree::TerminalNode* GREATER_EQUAL(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_relationalContext* expr_relational();

  class  Expr_shiftContext : public antlr4::ParserRuleContext {
  public:
    Expr_shiftContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_additiveContext *> expr_additive();
    Expr_additiveContext* expr_additive(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LSHIFT();
    antlr4::tree::TerminalNode* LSHIFT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RSHIFT();
    antlr4::tree::TerminalNode* RSHIFT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_shiftContext* expr_shift();

  class  Expr_additiveContext : public antlr4::ParserRuleContext {
  public:
    Expr_additiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_multiplicativeContext *> expr_multiplicative();
    Expr_multiplicativeContext* expr_multiplicative(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ADD();
    antlr4::tree::TerminalNode* ADD(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SUB();
    antlr4::tree::TerminalNode* SUB(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_additiveContext* expr_additive();

  class  Expr_multiplicativeContext : public antlr4::ParserRuleContext {
  public:
    Expr_multiplicativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_unaryContext *> expr_unary();
    Expr_unaryContext* expr_unary(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MUL();
    antlr4::tree::TerminalNode* MUL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIV();
    antlr4::tree::TerminalNode* DIV(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MOD();
    antlr4::tree::TerminalNode* MOD(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_multiplicativeContext* expr_multiplicative();

  class  Expr_unaryContext : public antlr4::ParserRuleContext {
  public:
    Expr_unaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_complementContext *expr_complement();
    Expr_negateContext *expr_negate();
    Expr_animationContext *expr_animation();
    Expr_primaryContext *expr_primary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_unaryContext* expr_unary();

  class  Expr_complementContext : public antlr4::ParserRuleContext {
  public:
    Expr_complementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COMPLEMENT();
    Expr_unaryContext *expr_unary();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_complementContext* expr_complement();

  class  Expr_negateContext : public antlr4::ParserRuleContext {
  public:
    Expr_negateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SUB();
    Expr_floatContext *expr_float();
    Expr_integerContext *expr_integer();
    Expr_identifierContext *expr_identifier();
    Expr_parenContext *expr_paren();
    Expr_object_subexprContext *expr_object_subexpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_negateContext* expr_negate();

  class  Expr_animationContext : public antlr4::ParserRuleContext {
  public:
    Expr_animationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MOD();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_animationContext* expr_animation();

  class  Expr_primaryContext : public antlr4::ParserRuleContext {
  public:
    Expr_primaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_callContext *expr_call();
    Expr_referenceContext *expr_reference();
    Expr_isdefinedContext *expr_isdefined();
    Expr_istrueContext *expr_istrue();
    Expr_add_arrayContext *expr_add_array();
    Expr_object_subexprContext *expr_object_subexpr();
    Expr_sizeContext *expr_size();
    Expr_parenContext *expr_paren();
    Expr_thisthreadContext *expr_thisthread();
    Expr_empty_arrayContext *expr_empty_array();
    Expr_undefinedContext *expr_undefined();
    Expr_gameContext *expr_game();
    Expr_selfContext *expr_self();
    Expr_animContext *expr_anim();
    Expr_levelContext *expr_level();
    Expr_animtreeContext *expr_animtree();
    Expr_identifierContext *expr_identifier();
    Expr_istringContext *expr_istring();
    Expr_stringContext *expr_string();
    Expr_vectorContext *expr_vector();
    Expr_floatContext *expr_float();
    Expr_integerContext *expr_integer();
    Expr_falseContext *expr_false();
    Expr_trueContext *expr_true();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_primaryContext* expr_primary();

  class  Expr_callContext : public antlr4::ParserRuleContext {
  public:
    Expr_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_functionContext *expr_function();
    Expr_pointerContext *expr_pointer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_callContext* expr_call();

  class  Expr_methodContext : public antlr4::ParserRuleContext {
  public:
    Expr_methodContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_objectContext *expr_object();
    Expr_functionContext *expr_function();
    Expr_pointerContext *expr_pointer();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_methodContext* expr_method();

  class  Expr_functionContext : public antlr4::ParserRuleContext {
  public:
    Expr_functionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_identifierContext *expr_identifier();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Expr_pathContext *expr_path();
    antlr4::tree::TerminalNode *DOUBLECOLON();
    Expr_argumentsContext *expr_arguments();
    antlr4::tree::TerminalNode *THREAD();
    antlr4::tree::TerminalNode *CHILDTHREAD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_functionContext* expr_function();

  class  Expr_pointerContext : public antlr4::ParserRuleContext {
  public:
    Expr_pointerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> LBRACKET();
    antlr4::tree::TerminalNode* LBRACKET(size_t i);
    ExprContext *expr();
    std::vector<antlr4::tree::TerminalNode *> RBRACKET();
    antlr4::tree::TerminalNode* RBRACKET(size_t i);
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    Expr_argumentsContext *expr_arguments();
    antlr4::tree::TerminalNode *THREAD();
    antlr4::tree::TerminalNode *CHILDTHREAD();
    antlr4::tree::TerminalNode *CALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_pointerContext* expr_pointer();

  class  Expr_isdefinedContext : public antlr4::ParserRuleContext {
  public:
    Expr_isdefinedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ISDEFINED();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_isdefinedContext* expr_isdefined();

  class  Expr_istrueContext : public antlr4::ParserRuleContext {
  public:
    Expr_istrueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ISTRUE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_istrueContext* expr_istrue();

  class  Expr_referenceContext : public antlr4::ParserRuleContext {
  public:
    Expr_referenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOUBLECOLON();
    Expr_identifierContext *expr_identifier();
    Expr_pathContext *expr_path();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_referenceContext* expr_reference();

  class  Expr_parametersContext : public antlr4::ParserRuleContext {
  public:
    Expr_parametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<Expr_identifierContext *> expr_identifier();
    Expr_identifierContext* expr_identifier(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_parametersContext* expr_parameters();

  class  Expr_argumentsContext : public antlr4::ParserRuleContext {
  public:
    Expr_argumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_argumentsContext* expr_arguments();

  class  Expr_tupleContext : public antlr4::ParserRuleContext {
  public:
    Expr_tupleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    std::vector<Expr_lvalueContext *> expr_lvalue();
    Expr_lvalueContext* expr_lvalue(size_t i);
    antlr4::tree::TerminalNode *RBRACKET();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_tupleContext* expr_tuple();

  class  Expr_add_arrayContext : public antlr4::ParserRuleContext {
  public:
    Expr_add_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    Expr_argumentsContext *expr_arguments();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_add_arrayContext* expr_add_array();

  class  Expr_parenContext : public antlr4::ParserRuleContext {
  public:
    Expr_parenContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_parenContext* expr_paren();

  class  Expr_lvalueContext : public antlr4::ParserRuleContext {
  public:
    Expr_lvalueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_identifierContext *expr_identifier();
    Expr_lvalue_arrayContext *expr_lvalue_array();
    Expr_lvalue_fieldContext *expr_lvalue_field();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_lvalueContext* expr_lvalue();

  class  Expr_lvalue_arrayContext : public antlr4::ParserRuleContext {
  public:
    Expr_lvalue_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_object_subexpr_no_callContext *expr_object_subexpr_no_call();
    antlr4::tree::TerminalNode *LBRACKET();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_lvalue_arrayContext* expr_lvalue_array();

  class  Expr_lvalue_fieldContext : public antlr4::ParserRuleContext {
  public:
    Expr_lvalue_fieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_object_subexprContext *expr_object_subexpr();
    antlr4::tree::TerminalNode *DOT();
    Expr_identifier_fieldContext *expr_identifier_field();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_lvalue_fieldContext* expr_lvalue_field();

  class  Expr_objectContext : public antlr4::ParserRuleContext {
  public:
    Expr_objectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_callContext *expr_call();
    Expr_identifierContext *expr_identifier();
    Expr_gameContext *expr_game();
    Expr_selfContext *expr_self();
    Expr_animContext *expr_anim();
    Expr_levelContext *expr_level();
    Expr_object_subexprContext *expr_object_subexpr();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_objectContext* expr_object();

  class  Expr_object_subexprContext : public antlr4::ParserRuleContext {
  public:
    Expr_object_subexprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_callContext *expr_call();
    std::vector<Expr_array_or_field_or_callContext *> expr_array_or_field_or_call();
    Expr_array_or_field_or_callContext* expr_array_or_field_or_call(size_t i);
    Expr_identifierContext *expr_identifier();
    Expr_gameContext *expr_game();
    std::vector<Expr_arrayContext *> expr_array();
    Expr_arrayContext* expr_array(size_t i);
    Expr_selfContext *expr_self();
    Expr_animContext *expr_anim();
    std::vector<Expr_fieldContext *> expr_field();
    Expr_fieldContext* expr_field(size_t i);
    Expr_levelContext *expr_level();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_object_subexprContext* expr_object_subexpr();

  class  Expr_object_subexpr_no_callContext : public antlr4::ParserRuleContext {
  public:
    Expr_object_subexpr_no_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    Expr_identifierContext *expr_identifier();
    std::vector<Expr_array_or_fieldContext *> expr_array_or_field();
    Expr_array_or_fieldContext* expr_array_or_field(size_t i);
    Expr_gameContext *expr_game();
    std::vector<Expr_arrayContext *> expr_array();
    Expr_arrayContext* expr_array(size_t i);
    Expr_selfContext *expr_self();
    Expr_animContext *expr_anim();
    std::vector<Expr_fieldContext *> expr_field();
    Expr_fieldContext* expr_field(size_t i);
    Expr_levelContext *expr_level();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_object_subexpr_no_callContext* expr_object_subexpr_no_call();

  class  Expr_array_or_field_or_callContext : public antlr4::ParserRuleContext {
  public:
    Expr_array_or_field_or_callContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *DOT();
    Expr_identifier_fieldContext *expr_identifier_field();
    Expr_callContext *expr_call();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_array_or_field_or_callContext* expr_array_or_field_or_call();

  class  Expr_array_or_fieldContext : public antlr4::ParserRuleContext {
  public:
    Expr_array_or_fieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RBRACKET();
    antlr4::tree::TerminalNode *DOT();
    Expr_identifier_fieldContext *expr_identifier_field();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_array_or_fieldContext* expr_array_or_field();

  class  Expr_arrayContext : public antlr4::ParserRuleContext {
  public:
    Expr_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_arrayContext* expr_array();

  class  Expr_fieldContext : public antlr4::ParserRuleContext {
  public:
    Expr_fieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    Expr_identifier_fieldContext *expr_identifier_field();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_fieldContext* expr_field();

  class  Expr_sizeContext : public antlr4::ParserRuleContext {
  public:
    Expr_sizeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *SIZE();
    Expr_objectContext *expr_object();
    Expr_stringContext *expr_string();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_sizeContext* expr_size();

  class  Expr_thisthreadContext : public antlr4::ParserRuleContext {
  public:
    Expr_thisthreadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *THISTHREAD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_thisthreadContext* expr_thisthread();

  class  Expr_empty_arrayContext : public antlr4::ParserRuleContext {
  public:
    Expr_empty_arrayContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACKET();
    antlr4::tree::TerminalNode *RBRACKET();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_empty_arrayContext* expr_empty_array();

  class  Expr_undefinedContext : public antlr4::ParserRuleContext {
  public:
    Expr_undefinedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNDEFINED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_undefinedContext* expr_undefined();

  class  Expr_gameContext : public antlr4::ParserRuleContext {
  public:
    Expr_gameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GAME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_gameContext* expr_game();

  class  Expr_selfContext : public antlr4::ParserRuleContext {
  public:
    Expr_selfContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_selfContext* expr_self();

  class  Expr_animContext : public antlr4::ParserRuleContext {
  public:
    Expr_animContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANIM();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_animContext* expr_anim();

  class  Expr_levelContext : public antlr4::ParserRuleContext {
  public:
    Expr_levelContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LEVEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_levelContext* expr_level();

  class  Expr_animtreeContext : public antlr4::ParserRuleContext {
  public:
    Expr_animtreeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANIMTREE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_animtreeContext* expr_animtree();

  class  Expr_vectorContext : public antlr4::ParserRuleContext {
  public:
    Expr_vectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_vectorContext* expr_vector();

  class  Expr_pathContext : public antlr4::ParserRuleContext {
  public:
    Expr_pathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PATH();
    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_pathContext* expr_path();

  class  Expr_identifier_fieldContext : public antlr4::ParserRuleContext {
  public:
    Expr_identifier_fieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *WAIT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_identifier_fieldContext* expr_identifier_field();

  class  Expr_identifierContext : public antlr4::ParserRuleContext {
  public:
    Expr_identifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *SIZE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_identifierContext* expr_identifier();

  class  Expr_istringContext : public antlr4::ParserRuleContext {
  public:
    Expr_istringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ISTRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_istringContext* expr_istring();

  class  Expr_stringContext : public antlr4::ParserRuleContext {
  public:
    Expr_stringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_stringContext* expr_string();

  class  Expr_floatContext : public antlr4::ParserRuleContext {
  public:
    Expr_floatContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLOAT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_floatContext* expr_float();

  class  Expr_integerContext : public antlr4::ParserRuleContext {
  public:
    Expr_integerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_integerContext* expr_integer();

  class  Expr_falseContext : public antlr4::ParserRuleContext {
  public:
    Expr_falseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_falseContext* expr_false();

  class  Expr_trueContext : public antlr4::ParserRuleContext {
  public:
    Expr_trueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Expr_trueContext* expr_true();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

