
// Generated from gsc_iw_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "gsc_iw_grammarParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by gsc_iw_grammarParser.
 */
class  gsc_iw_grammarListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(gsc_iw_grammarParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(gsc_iw_grammarParser::ProgramContext *ctx) = 0;

  virtual void enterInclude(gsc_iw_grammarParser::IncludeContext *ctx) = 0;
  virtual void exitInclude(gsc_iw_grammarParser::IncludeContext *ctx) = 0;

  virtual void enterInline(gsc_iw_grammarParser::InlineContext *ctx) = 0;
  virtual void exitInline(gsc_iw_grammarParser::InlineContext *ctx) = 0;

  virtual void enterDeclaration(gsc_iw_grammarParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(gsc_iw_grammarParser::DeclarationContext *ctx) = 0;

  virtual void enterDecl_usingtree(gsc_iw_grammarParser::Decl_usingtreeContext *ctx) = 0;
  virtual void exitDecl_usingtree(gsc_iw_grammarParser::Decl_usingtreeContext *ctx) = 0;

  virtual void enterDecl_constant(gsc_iw_grammarParser::Decl_constantContext *ctx) = 0;
  virtual void exitDecl_constant(gsc_iw_grammarParser::Decl_constantContext *ctx) = 0;

  virtual void enterDecl_function(gsc_iw_grammarParser::Decl_functionContext *ctx) = 0;
  virtual void exitDecl_function(gsc_iw_grammarParser::Decl_functionContext *ctx) = 0;

  virtual void enterStmt(gsc_iw_grammarParser::StmtContext *ctx) = 0;
  virtual void exitStmt(gsc_iw_grammarParser::StmtContext *ctx) = 0;

  virtual void enterStmt_list(gsc_iw_grammarParser::Stmt_listContext *ctx) = 0;
  virtual void exitStmt_list(gsc_iw_grammarParser::Stmt_listContext *ctx) = 0;

  virtual void enterStmt_or_dev_list(gsc_iw_grammarParser::Stmt_or_dev_listContext *ctx) = 0;
  virtual void exitStmt_or_dev_list(gsc_iw_grammarParser::Stmt_or_dev_listContext *ctx) = 0;

  virtual void enterStmt_dev(gsc_iw_grammarParser::Stmt_devContext *ctx) = 0;
  virtual void exitStmt_dev(gsc_iw_grammarParser::Stmt_devContext *ctx) = 0;

  virtual void enterStmt_comp(gsc_iw_grammarParser::Stmt_compContext *ctx) = 0;
  virtual void exitStmt_comp(gsc_iw_grammarParser::Stmt_compContext *ctx) = 0;

  virtual void enterStmt_expr(gsc_iw_grammarParser::Stmt_exprContext *ctx) = 0;
  virtual void exitStmt_expr(gsc_iw_grammarParser::Stmt_exprContext *ctx) = 0;

  virtual void enterStmt_endon(gsc_iw_grammarParser::Stmt_endonContext *ctx) = 0;
  virtual void exitStmt_endon(gsc_iw_grammarParser::Stmt_endonContext *ctx) = 0;

  virtual void enterStmt_notify(gsc_iw_grammarParser::Stmt_notifyContext *ctx) = 0;
  virtual void exitStmt_notify(gsc_iw_grammarParser::Stmt_notifyContext *ctx) = 0;

  virtual void enterStmt_wait(gsc_iw_grammarParser::Stmt_waitContext *ctx) = 0;
  virtual void exitStmt_wait(gsc_iw_grammarParser::Stmt_waitContext *ctx) = 0;

  virtual void enterStmt_waittill(gsc_iw_grammarParser::Stmt_waittillContext *ctx) = 0;
  virtual void exitStmt_waittill(gsc_iw_grammarParser::Stmt_waittillContext *ctx) = 0;

  virtual void enterStmt_waittillmatch(gsc_iw_grammarParser::Stmt_waittillmatchContext *ctx) = 0;
  virtual void exitStmt_waittillmatch(gsc_iw_grammarParser::Stmt_waittillmatchContext *ctx) = 0;

  virtual void enterStmt_waittillframeend(gsc_iw_grammarParser::Stmt_waittillframeendContext *ctx) = 0;
  virtual void exitStmt_waittillframeend(gsc_iw_grammarParser::Stmt_waittillframeendContext *ctx) = 0;

  virtual void enterStmt_waitframe(gsc_iw_grammarParser::Stmt_waitframeContext *ctx) = 0;
  virtual void exitStmt_waitframe(gsc_iw_grammarParser::Stmt_waitframeContext *ctx) = 0;

  virtual void enterStmt_if(gsc_iw_grammarParser::Stmt_ifContext *ctx) = 0;
  virtual void exitStmt_if(gsc_iw_grammarParser::Stmt_ifContext *ctx) = 0;

  virtual void enterStmt_while(gsc_iw_grammarParser::Stmt_whileContext *ctx) = 0;
  virtual void exitStmt_while(gsc_iw_grammarParser::Stmt_whileContext *ctx) = 0;

  virtual void enterStmt_dowhile(gsc_iw_grammarParser::Stmt_dowhileContext *ctx) = 0;
  virtual void exitStmt_dowhile(gsc_iw_grammarParser::Stmt_dowhileContext *ctx) = 0;

  virtual void enterStmt_for(gsc_iw_grammarParser::Stmt_forContext *ctx) = 0;
  virtual void exitStmt_for(gsc_iw_grammarParser::Stmt_forContext *ctx) = 0;

  virtual void enterStmt_foreach(gsc_iw_grammarParser::Stmt_foreachContext *ctx) = 0;
  virtual void exitStmt_foreach(gsc_iw_grammarParser::Stmt_foreachContext *ctx) = 0;

  virtual void enterStmt_switch(gsc_iw_grammarParser::Stmt_switchContext *ctx) = 0;
  virtual void exitStmt_switch(gsc_iw_grammarParser::Stmt_switchContext *ctx) = 0;

  virtual void enterStmt_case(gsc_iw_grammarParser::Stmt_caseContext *ctx) = 0;
  virtual void exitStmt_case(gsc_iw_grammarParser::Stmt_caseContext *ctx) = 0;

  virtual void enterStmt_default(gsc_iw_grammarParser::Stmt_defaultContext *ctx) = 0;
  virtual void exitStmt_default(gsc_iw_grammarParser::Stmt_defaultContext *ctx) = 0;

  virtual void enterStmt_break(gsc_iw_grammarParser::Stmt_breakContext *ctx) = 0;
  virtual void exitStmt_break(gsc_iw_grammarParser::Stmt_breakContext *ctx) = 0;

  virtual void enterStmt_continue(gsc_iw_grammarParser::Stmt_continueContext *ctx) = 0;
  virtual void exitStmt_continue(gsc_iw_grammarParser::Stmt_continueContext *ctx) = 0;

  virtual void enterStmt_return(gsc_iw_grammarParser::Stmt_returnContext *ctx) = 0;
  virtual void exitStmt_return(gsc_iw_grammarParser::Stmt_returnContext *ctx) = 0;

  virtual void enterStmt_breakpoint(gsc_iw_grammarParser::Stmt_breakpointContext *ctx) = 0;
  virtual void exitStmt_breakpoint(gsc_iw_grammarParser::Stmt_breakpointContext *ctx) = 0;

  virtual void enterStmt_prof_begin(gsc_iw_grammarParser::Stmt_prof_beginContext *ctx) = 0;
  virtual void exitStmt_prof_begin(gsc_iw_grammarParser::Stmt_prof_beginContext *ctx) = 0;

  virtual void enterStmt_prof_end(gsc_iw_grammarParser::Stmt_prof_endContext *ctx) = 0;
  virtual void exitStmt_prof_end(gsc_iw_grammarParser::Stmt_prof_endContext *ctx) = 0;

  virtual void enterStmt_assert(gsc_iw_grammarParser::Stmt_assertContext *ctx) = 0;
  virtual void exitStmt_assert(gsc_iw_grammarParser::Stmt_assertContext *ctx) = 0;

  virtual void enterStmt_assertex(gsc_iw_grammarParser::Stmt_assertexContext *ctx) = 0;
  virtual void exitStmt_assertex(gsc_iw_grammarParser::Stmt_assertexContext *ctx) = 0;

  virtual void enterStmt_assertmsg(gsc_iw_grammarParser::Stmt_assertmsgContext *ctx) = 0;
  virtual void exitStmt_assertmsg(gsc_iw_grammarParser::Stmt_assertmsgContext *ctx) = 0;

  virtual void enterExpr_assign(gsc_iw_grammarParser::Expr_assignContext *ctx) = 0;
  virtual void exitExpr_assign(gsc_iw_grammarParser::Expr_assignContext *ctx) = 0;

  virtual void enterExpr(gsc_iw_grammarParser::ExprContext *ctx) = 0;
  virtual void exitExpr(gsc_iw_grammarParser::ExprContext *ctx) = 0;

  virtual void enterExpr_ternary(gsc_iw_grammarParser::Expr_ternaryContext *ctx) = 0;
  virtual void exitExpr_ternary(gsc_iw_grammarParser::Expr_ternaryContext *ctx) = 0;

  virtual void enterExpr_or(gsc_iw_grammarParser::Expr_orContext *ctx) = 0;
  virtual void exitExpr_or(gsc_iw_grammarParser::Expr_orContext *ctx) = 0;

  virtual void enterExpr_and(gsc_iw_grammarParser::Expr_andContext *ctx) = 0;
  virtual void exitExpr_and(gsc_iw_grammarParser::Expr_andContext *ctx) = 0;

  virtual void enterExpr_bw_or(gsc_iw_grammarParser::Expr_bw_orContext *ctx) = 0;
  virtual void exitExpr_bw_or(gsc_iw_grammarParser::Expr_bw_orContext *ctx) = 0;

  virtual void enterExpr_bw_xor(gsc_iw_grammarParser::Expr_bw_xorContext *ctx) = 0;
  virtual void exitExpr_bw_xor(gsc_iw_grammarParser::Expr_bw_xorContext *ctx) = 0;

  virtual void enterExpr_bw_and(gsc_iw_grammarParser::Expr_bw_andContext *ctx) = 0;
  virtual void exitExpr_bw_and(gsc_iw_grammarParser::Expr_bw_andContext *ctx) = 0;

  virtual void enterExpr_equality(gsc_iw_grammarParser::Expr_equalityContext *ctx) = 0;
  virtual void exitExpr_equality(gsc_iw_grammarParser::Expr_equalityContext *ctx) = 0;

  virtual void enterExpr_relational(gsc_iw_grammarParser::Expr_relationalContext *ctx) = 0;
  virtual void exitExpr_relational(gsc_iw_grammarParser::Expr_relationalContext *ctx) = 0;

  virtual void enterExpr_shift(gsc_iw_grammarParser::Expr_shiftContext *ctx) = 0;
  virtual void exitExpr_shift(gsc_iw_grammarParser::Expr_shiftContext *ctx) = 0;

  virtual void enterExpr_additive(gsc_iw_grammarParser::Expr_additiveContext *ctx) = 0;
  virtual void exitExpr_additive(gsc_iw_grammarParser::Expr_additiveContext *ctx) = 0;

  virtual void enterExpr_multiplicative(gsc_iw_grammarParser::Expr_multiplicativeContext *ctx) = 0;
  virtual void exitExpr_multiplicative(gsc_iw_grammarParser::Expr_multiplicativeContext *ctx) = 0;

  virtual void enterExpr_unary(gsc_iw_grammarParser::Expr_unaryContext *ctx) = 0;
  virtual void exitExpr_unary(gsc_iw_grammarParser::Expr_unaryContext *ctx) = 0;

  virtual void enterExpr_complement(gsc_iw_grammarParser::Expr_complementContext *ctx) = 0;
  virtual void exitExpr_complement(gsc_iw_grammarParser::Expr_complementContext *ctx) = 0;

  virtual void enterExpr_negate(gsc_iw_grammarParser::Expr_negateContext *ctx) = 0;
  virtual void exitExpr_negate(gsc_iw_grammarParser::Expr_negateContext *ctx) = 0;

  virtual void enterExpr_animation(gsc_iw_grammarParser::Expr_animationContext *ctx) = 0;
  virtual void exitExpr_animation(gsc_iw_grammarParser::Expr_animationContext *ctx) = 0;

  virtual void enterExpr_primary(gsc_iw_grammarParser::Expr_primaryContext *ctx) = 0;
  virtual void exitExpr_primary(gsc_iw_grammarParser::Expr_primaryContext *ctx) = 0;

  virtual void enterExpr_call(gsc_iw_grammarParser::Expr_callContext *ctx) = 0;
  virtual void exitExpr_call(gsc_iw_grammarParser::Expr_callContext *ctx) = 0;

  virtual void enterExpr_method(gsc_iw_grammarParser::Expr_methodContext *ctx) = 0;
  virtual void exitExpr_method(gsc_iw_grammarParser::Expr_methodContext *ctx) = 0;

  virtual void enterExpr_function(gsc_iw_grammarParser::Expr_functionContext *ctx) = 0;
  virtual void exitExpr_function(gsc_iw_grammarParser::Expr_functionContext *ctx) = 0;

  virtual void enterExpr_pointer(gsc_iw_grammarParser::Expr_pointerContext *ctx) = 0;
  virtual void exitExpr_pointer(gsc_iw_grammarParser::Expr_pointerContext *ctx) = 0;

  virtual void enterExpr_isdefined(gsc_iw_grammarParser::Expr_isdefinedContext *ctx) = 0;
  virtual void exitExpr_isdefined(gsc_iw_grammarParser::Expr_isdefinedContext *ctx) = 0;

  virtual void enterExpr_istrue(gsc_iw_grammarParser::Expr_istrueContext *ctx) = 0;
  virtual void exitExpr_istrue(gsc_iw_grammarParser::Expr_istrueContext *ctx) = 0;

  virtual void enterExpr_reference(gsc_iw_grammarParser::Expr_referenceContext *ctx) = 0;
  virtual void exitExpr_reference(gsc_iw_grammarParser::Expr_referenceContext *ctx) = 0;

  virtual void enterExpr_parameters(gsc_iw_grammarParser::Expr_parametersContext *ctx) = 0;
  virtual void exitExpr_parameters(gsc_iw_grammarParser::Expr_parametersContext *ctx) = 0;

  virtual void enterExpr_arguments(gsc_iw_grammarParser::Expr_argumentsContext *ctx) = 0;
  virtual void exitExpr_arguments(gsc_iw_grammarParser::Expr_argumentsContext *ctx) = 0;

  virtual void enterExpr_tuple(gsc_iw_grammarParser::Expr_tupleContext *ctx) = 0;
  virtual void exitExpr_tuple(gsc_iw_grammarParser::Expr_tupleContext *ctx) = 0;

  virtual void enterExpr_add_array(gsc_iw_grammarParser::Expr_add_arrayContext *ctx) = 0;
  virtual void exitExpr_add_array(gsc_iw_grammarParser::Expr_add_arrayContext *ctx) = 0;

  virtual void enterExpr_paren(gsc_iw_grammarParser::Expr_parenContext *ctx) = 0;
  virtual void exitExpr_paren(gsc_iw_grammarParser::Expr_parenContext *ctx) = 0;

  virtual void enterExpr_lvalue(gsc_iw_grammarParser::Expr_lvalueContext *ctx) = 0;
  virtual void exitExpr_lvalue(gsc_iw_grammarParser::Expr_lvalueContext *ctx) = 0;

  virtual void enterExpr_lvalue_array(gsc_iw_grammarParser::Expr_lvalue_arrayContext *ctx) = 0;
  virtual void exitExpr_lvalue_array(gsc_iw_grammarParser::Expr_lvalue_arrayContext *ctx) = 0;

  virtual void enterExpr_lvalue_field(gsc_iw_grammarParser::Expr_lvalue_fieldContext *ctx) = 0;
  virtual void exitExpr_lvalue_field(gsc_iw_grammarParser::Expr_lvalue_fieldContext *ctx) = 0;

  virtual void enterExpr_object(gsc_iw_grammarParser::Expr_objectContext *ctx) = 0;
  virtual void exitExpr_object(gsc_iw_grammarParser::Expr_objectContext *ctx) = 0;

  virtual void enterExpr_object_subexpr(gsc_iw_grammarParser::Expr_object_subexprContext *ctx) = 0;
  virtual void exitExpr_object_subexpr(gsc_iw_grammarParser::Expr_object_subexprContext *ctx) = 0;

  virtual void enterExpr_object_subexpr_no_call(gsc_iw_grammarParser::Expr_object_subexpr_no_callContext *ctx) = 0;
  virtual void exitExpr_object_subexpr_no_call(gsc_iw_grammarParser::Expr_object_subexpr_no_callContext *ctx) = 0;

  virtual void enterExpr_array_or_field_or_call(gsc_iw_grammarParser::Expr_array_or_field_or_callContext *ctx) = 0;
  virtual void exitExpr_array_or_field_or_call(gsc_iw_grammarParser::Expr_array_or_field_or_callContext *ctx) = 0;

  virtual void enterExpr_array_or_field(gsc_iw_grammarParser::Expr_array_or_fieldContext *ctx) = 0;
  virtual void exitExpr_array_or_field(gsc_iw_grammarParser::Expr_array_or_fieldContext *ctx) = 0;

  virtual void enterExpr_array(gsc_iw_grammarParser::Expr_arrayContext *ctx) = 0;
  virtual void exitExpr_array(gsc_iw_grammarParser::Expr_arrayContext *ctx) = 0;

  virtual void enterExpr_field(gsc_iw_grammarParser::Expr_fieldContext *ctx) = 0;
  virtual void exitExpr_field(gsc_iw_grammarParser::Expr_fieldContext *ctx) = 0;

  virtual void enterExpr_size(gsc_iw_grammarParser::Expr_sizeContext *ctx) = 0;
  virtual void exitExpr_size(gsc_iw_grammarParser::Expr_sizeContext *ctx) = 0;

  virtual void enterExpr_thisthread(gsc_iw_grammarParser::Expr_thisthreadContext *ctx) = 0;
  virtual void exitExpr_thisthread(gsc_iw_grammarParser::Expr_thisthreadContext *ctx) = 0;

  virtual void enterExpr_empty_array(gsc_iw_grammarParser::Expr_empty_arrayContext *ctx) = 0;
  virtual void exitExpr_empty_array(gsc_iw_grammarParser::Expr_empty_arrayContext *ctx) = 0;

  virtual void enterExpr_undefined(gsc_iw_grammarParser::Expr_undefinedContext *ctx) = 0;
  virtual void exitExpr_undefined(gsc_iw_grammarParser::Expr_undefinedContext *ctx) = 0;

  virtual void enterExpr_game(gsc_iw_grammarParser::Expr_gameContext *ctx) = 0;
  virtual void exitExpr_game(gsc_iw_grammarParser::Expr_gameContext *ctx) = 0;

  virtual void enterExpr_self(gsc_iw_grammarParser::Expr_selfContext *ctx) = 0;
  virtual void exitExpr_self(gsc_iw_grammarParser::Expr_selfContext *ctx) = 0;

  virtual void enterExpr_anim(gsc_iw_grammarParser::Expr_animContext *ctx) = 0;
  virtual void exitExpr_anim(gsc_iw_grammarParser::Expr_animContext *ctx) = 0;

  virtual void enterExpr_level(gsc_iw_grammarParser::Expr_levelContext *ctx) = 0;
  virtual void exitExpr_level(gsc_iw_grammarParser::Expr_levelContext *ctx) = 0;

  virtual void enterExpr_animtree(gsc_iw_grammarParser::Expr_animtreeContext *ctx) = 0;
  virtual void exitExpr_animtree(gsc_iw_grammarParser::Expr_animtreeContext *ctx) = 0;

  virtual void enterExpr_vector(gsc_iw_grammarParser::Expr_vectorContext *ctx) = 0;
  virtual void exitExpr_vector(gsc_iw_grammarParser::Expr_vectorContext *ctx) = 0;

  virtual void enterExpr_path(gsc_iw_grammarParser::Expr_pathContext *ctx) = 0;
  virtual void exitExpr_path(gsc_iw_grammarParser::Expr_pathContext *ctx) = 0;

  virtual void enterExpr_identifier_field(gsc_iw_grammarParser::Expr_identifier_fieldContext *ctx) = 0;
  virtual void exitExpr_identifier_field(gsc_iw_grammarParser::Expr_identifier_fieldContext *ctx) = 0;

  virtual void enterExpr_identifier(gsc_iw_grammarParser::Expr_identifierContext *ctx) = 0;
  virtual void exitExpr_identifier(gsc_iw_grammarParser::Expr_identifierContext *ctx) = 0;

  virtual void enterExpr_istring(gsc_iw_grammarParser::Expr_istringContext *ctx) = 0;
  virtual void exitExpr_istring(gsc_iw_grammarParser::Expr_istringContext *ctx) = 0;

  virtual void enterExpr_string(gsc_iw_grammarParser::Expr_stringContext *ctx) = 0;
  virtual void exitExpr_string(gsc_iw_grammarParser::Expr_stringContext *ctx) = 0;

  virtual void enterExpr_float(gsc_iw_grammarParser::Expr_floatContext *ctx) = 0;
  virtual void exitExpr_float(gsc_iw_grammarParser::Expr_floatContext *ctx) = 0;

  virtual void enterExpr_integer(gsc_iw_grammarParser::Expr_integerContext *ctx) = 0;
  virtual void exitExpr_integer(gsc_iw_grammarParser::Expr_integerContext *ctx) = 0;

  virtual void enterExpr_false(gsc_iw_grammarParser::Expr_falseContext *ctx) = 0;
  virtual void exitExpr_false(gsc_iw_grammarParser::Expr_falseContext *ctx) = 0;

  virtual void enterExpr_true(gsc_iw_grammarParser::Expr_trueContext *ctx) = 0;
  virtual void exitExpr_true(gsc_iw_grammarParser::Expr_trueContext *ctx) = 0;


};

