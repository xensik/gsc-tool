// Generated from /Volumes/T7/development/projects/xensik/gsc-tool/gen/antlr4/GscParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link GscParser}.
 */
public interface GscParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link GscParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(GscParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(GscParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#include}.
	 * @param ctx the parse tree
	 */
	void enterInclude(GscParser.IncludeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#include}.
	 * @param ctx the parse tree
	 */
	void exitInclude(GscParser.IncludeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#inline}.
	 * @param ctx the parse tree
	 */
	void enterInline(GscParser.InlineContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#inline}.
	 * @param ctx the parse tree
	 */
	void exitInline(GscParser.InlineContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#declaration}.
	 * @param ctx the parse tree
	 */
	void enterDeclaration(GscParser.DeclarationContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#declaration}.
	 * @param ctx the parse tree
	 */
	void exitDeclaration(GscParser.DeclarationContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#decl_usingtree}.
	 * @param ctx the parse tree
	 */
	void enterDecl_usingtree(GscParser.Decl_usingtreeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#decl_usingtree}.
	 * @param ctx the parse tree
	 */
	void exitDecl_usingtree(GscParser.Decl_usingtreeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#decl_constant}.
	 * @param ctx the parse tree
	 */
	void enterDecl_constant(GscParser.Decl_constantContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#decl_constant}.
	 * @param ctx the parse tree
	 */
	void exitDecl_constant(GscParser.Decl_constantContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#decl_function}.
	 * @param ctx the parse tree
	 */
	void enterDecl_function(GscParser.Decl_functionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#decl_function}.
	 * @param ctx the parse tree
	 */
	void exitDecl_function(GscParser.Decl_functionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#decl_namespace}.
	 * @param ctx the parse tree
	 */
	void enterDecl_namespace(GscParser.Decl_namespaceContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#decl_namespace}.
	 * @param ctx the parse tree
	 */
	void exitDecl_namespace(GscParser.Decl_namespaceContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#decl_class}.
	 * @param ctx the parse tree
	 */
	void enterDecl_class(GscParser.Decl_classContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#decl_class}.
	 * @param ctx the parse tree
	 */
	void exitDecl_class(GscParser.Decl_classContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#class_list}.
	 * @param ctx the parse tree
	 */
	void enterClass_list(GscParser.Class_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#class_list}.
	 * @param ctx the parse tree
	 */
	void exitClass_list(GscParser.Class_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#class_member}.
	 * @param ctx the parse tree
	 */
	void enterClass_member(GscParser.Class_memberContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#class_member}.
	 * @param ctx the parse tree
	 */
	void exitClass_member(GscParser.Class_memberContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(GscParser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(GscParser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_list}.
	 * @param ctx the parse tree
	 */
	void enterStmt_list(GscParser.Stmt_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_list}.
	 * @param ctx the parse tree
	 */
	void exitStmt_list(GscParser.Stmt_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_or_dev_list}.
	 * @param ctx the parse tree
	 */
	void enterStmt_or_dev_list(GscParser.Stmt_or_dev_listContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_or_dev_list}.
	 * @param ctx the parse tree
	 */
	void exitStmt_or_dev_list(GscParser.Stmt_or_dev_listContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_dev}.
	 * @param ctx the parse tree
	 */
	void enterStmt_dev(GscParser.Stmt_devContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_dev}.
	 * @param ctx the parse tree
	 */
	void exitStmt_dev(GscParser.Stmt_devContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_comp}.
	 * @param ctx the parse tree
	 */
	void enterStmt_comp(GscParser.Stmt_compContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_comp}.
	 * @param ctx the parse tree
	 */
	void exitStmt_comp(GscParser.Stmt_compContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_expr}.
	 * @param ctx the parse tree
	 */
	void enterStmt_expr(GscParser.Stmt_exprContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_expr}.
	 * @param ctx the parse tree
	 */
	void exitStmt_expr(GscParser.Stmt_exprContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_const}.
	 * @param ctx the parse tree
	 */
	void enterStmt_const(GscParser.Stmt_constContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_const}.
	 * @param ctx the parse tree
	 */
	void exitStmt_const(GscParser.Stmt_constContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_endon}.
	 * @param ctx the parse tree
	 */
	void enterStmt_endon(GscParser.Stmt_endonContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_endon}.
	 * @param ctx the parse tree
	 */
	void exitStmt_endon(GscParser.Stmt_endonContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_notify}.
	 * @param ctx the parse tree
	 */
	void enterStmt_notify(GscParser.Stmt_notifyContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_notify}.
	 * @param ctx the parse tree
	 */
	void exitStmt_notify(GscParser.Stmt_notifyContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_wait}.
	 * @param ctx the parse tree
	 */
	void enterStmt_wait(GscParser.Stmt_waitContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_wait}.
	 * @param ctx the parse tree
	 */
	void exitStmt_wait(GscParser.Stmt_waitContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_waittill}.
	 * @param ctx the parse tree
	 */
	void enterStmt_waittill(GscParser.Stmt_waittillContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_waittill}.
	 * @param ctx the parse tree
	 */
	void exitStmt_waittill(GscParser.Stmt_waittillContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_waittillmatch}.
	 * @param ctx the parse tree
	 */
	void enterStmt_waittillmatch(GscParser.Stmt_waittillmatchContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_waittillmatch}.
	 * @param ctx the parse tree
	 */
	void exitStmt_waittillmatch(GscParser.Stmt_waittillmatchContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_waittillframeend}.
	 * @param ctx the parse tree
	 */
	void enterStmt_waittillframeend(GscParser.Stmt_waittillframeendContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_waittillframeend}.
	 * @param ctx the parse tree
	 */
	void exitStmt_waittillframeend(GscParser.Stmt_waittillframeendContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_waitframe}.
	 * @param ctx the parse tree
	 */
	void enterStmt_waitframe(GscParser.Stmt_waitframeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_waitframe}.
	 * @param ctx the parse tree
	 */
	void exitStmt_waitframe(GscParser.Stmt_waitframeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_waitrealtime}.
	 * @param ctx the parse tree
	 */
	void enterStmt_waitrealtime(GscParser.Stmt_waitrealtimeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_waitrealtime}.
	 * @param ctx the parse tree
	 */
	void exitStmt_waitrealtime(GscParser.Stmt_waitrealtimeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_if}.
	 * @param ctx the parse tree
	 */
	void enterStmt_if(GscParser.Stmt_ifContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_if}.
	 * @param ctx the parse tree
	 */
	void exitStmt_if(GscParser.Stmt_ifContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_while}.
	 * @param ctx the parse tree
	 */
	void enterStmt_while(GscParser.Stmt_whileContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_while}.
	 * @param ctx the parse tree
	 */
	void exitStmt_while(GscParser.Stmt_whileContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_dowhile}.
	 * @param ctx the parse tree
	 */
	void enterStmt_dowhile(GscParser.Stmt_dowhileContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_dowhile}.
	 * @param ctx the parse tree
	 */
	void exitStmt_dowhile(GscParser.Stmt_dowhileContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_for}.
	 * @param ctx the parse tree
	 */
	void enterStmt_for(GscParser.Stmt_forContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_for}.
	 * @param ctx the parse tree
	 */
	void exitStmt_for(GscParser.Stmt_forContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_foreach}.
	 * @param ctx the parse tree
	 */
	void enterStmt_foreach(GscParser.Stmt_foreachContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_foreach}.
	 * @param ctx the parse tree
	 */
	void exitStmt_foreach(GscParser.Stmt_foreachContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_switch}.
	 * @param ctx the parse tree
	 */
	void enterStmt_switch(GscParser.Stmt_switchContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_switch}.
	 * @param ctx the parse tree
	 */
	void exitStmt_switch(GscParser.Stmt_switchContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_case}.
	 * @param ctx the parse tree
	 */
	void enterStmt_case(GscParser.Stmt_caseContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_case}.
	 * @param ctx the parse tree
	 */
	void exitStmt_case(GscParser.Stmt_caseContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_default}.
	 * @param ctx the parse tree
	 */
	void enterStmt_default(GscParser.Stmt_defaultContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_default}.
	 * @param ctx the parse tree
	 */
	void exitStmt_default(GscParser.Stmt_defaultContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_break}.
	 * @param ctx the parse tree
	 */
	void enterStmt_break(GscParser.Stmt_breakContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_break}.
	 * @param ctx the parse tree
	 */
	void exitStmt_break(GscParser.Stmt_breakContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_continue}.
	 * @param ctx the parse tree
	 */
	void enterStmt_continue(GscParser.Stmt_continueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_continue}.
	 * @param ctx the parse tree
	 */
	void exitStmt_continue(GscParser.Stmt_continueContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_return}.
	 * @param ctx the parse tree
	 */
	void enterStmt_return(GscParser.Stmt_returnContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_return}.
	 * @param ctx the parse tree
	 */
	void exitStmt_return(GscParser.Stmt_returnContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_breakpoint}.
	 * @param ctx the parse tree
	 */
	void enterStmt_breakpoint(GscParser.Stmt_breakpointContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_breakpoint}.
	 * @param ctx the parse tree
	 */
	void exitStmt_breakpoint(GscParser.Stmt_breakpointContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_prof_begin}.
	 * @param ctx the parse tree
	 */
	void enterStmt_prof_begin(GscParser.Stmt_prof_beginContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_prof_begin}.
	 * @param ctx the parse tree
	 */
	void exitStmt_prof_begin(GscParser.Stmt_prof_beginContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_prof_end}.
	 * @param ctx the parse tree
	 */
	void enterStmt_prof_end(GscParser.Stmt_prof_endContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_prof_end}.
	 * @param ctx the parse tree
	 */
	void exitStmt_prof_end(GscParser.Stmt_prof_endContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_assert}.
	 * @param ctx the parse tree
	 */
	void enterStmt_assert(GscParser.Stmt_assertContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_assert}.
	 * @param ctx the parse tree
	 */
	void exitStmt_assert(GscParser.Stmt_assertContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_assertex}.
	 * @param ctx the parse tree
	 */
	void enterStmt_assertex(GscParser.Stmt_assertexContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_assertex}.
	 * @param ctx the parse tree
	 */
	void exitStmt_assertex(GscParser.Stmt_assertexContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#stmt_assertmsg}.
	 * @param ctx the parse tree
	 */
	void enterStmt_assertmsg(GscParser.Stmt_assertmsgContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#stmt_assertmsg}.
	 * @param ctx the parse tree
	 */
	void exitStmt_assertmsg(GscParser.Stmt_assertmsgContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_assign}.
	 * @param ctx the parse tree
	 */
	void enterExpr_assign(GscParser.Expr_assignContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_assign}.
	 * @param ctx the parse tree
	 */
	void exitExpr_assign(GscParser.Expr_assignContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(GscParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(GscParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_ternary}.
	 * @param ctx the parse tree
	 */
	void enterExpr_ternary(GscParser.Expr_ternaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_ternary}.
	 * @param ctx the parse tree
	 */
	void exitExpr_ternary(GscParser.Expr_ternaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_or}.
	 * @param ctx the parse tree
	 */
	void enterExpr_or(GscParser.Expr_orContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_or}.
	 * @param ctx the parse tree
	 */
	void exitExpr_or(GscParser.Expr_orContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_and}.
	 * @param ctx the parse tree
	 */
	void enterExpr_and(GscParser.Expr_andContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_and}.
	 * @param ctx the parse tree
	 */
	void exitExpr_and(GscParser.Expr_andContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_bw_or}.
	 * @param ctx the parse tree
	 */
	void enterExpr_bw_or(GscParser.Expr_bw_orContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_bw_or}.
	 * @param ctx the parse tree
	 */
	void exitExpr_bw_or(GscParser.Expr_bw_orContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_bw_xor}.
	 * @param ctx the parse tree
	 */
	void enterExpr_bw_xor(GscParser.Expr_bw_xorContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_bw_xor}.
	 * @param ctx the parse tree
	 */
	void exitExpr_bw_xor(GscParser.Expr_bw_xorContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_bw_and}.
	 * @param ctx the parse tree
	 */
	void enterExpr_bw_and(GscParser.Expr_bw_andContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_bw_and}.
	 * @param ctx the parse tree
	 */
	void exitExpr_bw_and(GscParser.Expr_bw_andContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_equality}.
	 * @param ctx the parse tree
	 */
	void enterExpr_equality(GscParser.Expr_equalityContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_equality}.
	 * @param ctx the parse tree
	 */
	void exitExpr_equality(GscParser.Expr_equalityContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_relational}.
	 * @param ctx the parse tree
	 */
	void enterExpr_relational(GscParser.Expr_relationalContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_relational}.
	 * @param ctx the parse tree
	 */
	void exitExpr_relational(GscParser.Expr_relationalContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_shift}.
	 * @param ctx the parse tree
	 */
	void enterExpr_shift(GscParser.Expr_shiftContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_shift}.
	 * @param ctx the parse tree
	 */
	void exitExpr_shift(GscParser.Expr_shiftContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_additive}.
	 * @param ctx the parse tree
	 */
	void enterExpr_additive(GscParser.Expr_additiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_additive}.
	 * @param ctx the parse tree
	 */
	void exitExpr_additive(GscParser.Expr_additiveContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_multiplicative}.
	 * @param ctx the parse tree
	 */
	void enterExpr_multiplicative(GscParser.Expr_multiplicativeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_multiplicative}.
	 * @param ctx the parse tree
	 */
	void exitExpr_multiplicative(GscParser.Expr_multiplicativeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_unary}.
	 * @param ctx the parse tree
	 */
	void enterExpr_unary(GscParser.Expr_unaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_unary}.
	 * @param ctx the parse tree
	 */
	void exitExpr_unary(GscParser.Expr_unaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_complement}.
	 * @param ctx the parse tree
	 */
	void enterExpr_complement(GscParser.Expr_complementContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_complement}.
	 * @param ctx the parse tree
	 */
	void exitExpr_complement(GscParser.Expr_complementContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_not}.
	 * @param ctx the parse tree
	 */
	void enterExpr_not(GscParser.Expr_notContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_not}.
	 * @param ctx the parse tree
	 */
	void exitExpr_not(GscParser.Expr_notContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_negate}.
	 * @param ctx the parse tree
	 */
	void enterExpr_negate(GscParser.Expr_negateContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_negate}.
	 * @param ctx the parse tree
	 */
	void exitExpr_negate(GscParser.Expr_negateContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_animation}.
	 * @param ctx the parse tree
	 */
	void enterExpr_animation(GscParser.Expr_animationContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_animation}.
	 * @param ctx the parse tree
	 */
	void exitExpr_animation(GscParser.Expr_animationContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_primary}.
	 * @param ctx the parse tree
	 */
	void enterExpr_primary(GscParser.Expr_primaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_primary}.
	 * @param ctx the parse tree
	 */
	void exitExpr_primary(GscParser.Expr_primaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_call}.
	 * @param ctx the parse tree
	 */
	void enterExpr_call(GscParser.Expr_callContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_call}.
	 * @param ctx the parse tree
	 */
	void exitExpr_call(GscParser.Expr_callContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_method}.
	 * @param ctx the parse tree
	 */
	void enterExpr_method(GscParser.Expr_methodContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_method}.
	 * @param ctx the parse tree
	 */
	void exitExpr_method(GscParser.Expr_methodContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_function}.
	 * @param ctx the parse tree
	 */
	void enterExpr_function(GscParser.Expr_functionContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_function}.
	 * @param ctx the parse tree
	 */
	void exitExpr_function(GscParser.Expr_functionContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_pointer}.
	 * @param ctx the parse tree
	 */
	void enterExpr_pointer(GscParser.Expr_pointerContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_pointer}.
	 * @param ctx the parse tree
	 */
	void exitExpr_pointer(GscParser.Expr_pointerContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_call_optimized}.
	 * @param ctx the parse tree
	 */
	void enterExpr_call_optimized(GscParser.Expr_call_optimizedContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_call_optimized}.
	 * @param ctx the parse tree
	 */
	void exitExpr_call_optimized(GscParser.Expr_call_optimizedContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_call_optimized_vector}.
	 * @param ctx the parse tree
	 */
	void enterExpr_call_optimized_vector(GscParser.Expr_call_optimized_vectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_call_optimized_vector}.
	 * @param ctx the parse tree
	 */
	void exitExpr_call_optimized_vector(GscParser.Expr_call_optimized_vectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_call_optimized_vector_array}.
	 * @param ctx the parse tree
	 */
	void enterExpr_call_optimized_vector_array(GscParser.Expr_call_optimized_vector_arrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_call_optimized_vector_array}.
	 * @param ctx the parse tree
	 */
	void exitExpr_call_optimized_vector_array(GscParser.Expr_call_optimized_vector_arrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_isdefined}.
	 * @param ctx the parse tree
	 */
	void enterExpr_isdefined(GscParser.Expr_isdefinedContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_isdefined}.
	 * @param ctx the parse tree
	 */
	void exitExpr_isdefined(GscParser.Expr_isdefinedContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_istrue}.
	 * @param ctx the parse tree
	 */
	void enterExpr_istrue(GscParser.Expr_istrueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_istrue}.
	 * @param ctx the parse tree
	 */
	void exitExpr_istrue(GscParser.Expr_istrueContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_reference}.
	 * @param ctx the parse tree
	 */
	void enterExpr_reference(GscParser.Expr_referenceContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_reference}.
	 * @param ctx the parse tree
	 */
	void exitExpr_reference(GscParser.Expr_referenceContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_parameters}.
	 * @param ctx the parse tree
	 */
	void enterExpr_parameters(GscParser.Expr_parametersContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_parameters}.
	 * @param ctx the parse tree
	 */
	void exitExpr_parameters(GscParser.Expr_parametersContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_parameters_default}.
	 * @param ctx the parse tree
	 */
	void enterExpr_parameters_default(GscParser.Expr_parameters_defaultContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_parameters_default}.
	 * @param ctx the parse tree
	 */
	void exitExpr_parameters_default(GscParser.Expr_parameters_defaultContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_arguments}.
	 * @param ctx the parse tree
	 */
	void enterExpr_arguments(GscParser.Expr_argumentsContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_arguments}.
	 * @param ctx the parse tree
	 */
	void exitExpr_arguments(GscParser.Expr_argumentsContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_arguments_waittill}.
	 * @param ctx the parse tree
	 */
	void enterExpr_arguments_waittill(GscParser.Expr_arguments_waittillContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_arguments_waittill}.
	 * @param ctx the parse tree
	 */
	void exitExpr_arguments_waittill(GscParser.Expr_arguments_waittillContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_tuple}.
	 * @param ctx the parse tree
	 */
	void enterExpr_tuple(GscParser.Expr_tupleContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_tuple}.
	 * @param ctx the parse tree
	 */
	void exitExpr_tuple(GscParser.Expr_tupleContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_add_array}.
	 * @param ctx the parse tree
	 */
	void enterExpr_add_array(GscParser.Expr_add_arrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_add_array}.
	 * @param ctx the parse tree
	 */
	void exitExpr_add_array(GscParser.Expr_add_arrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_paren}.
	 * @param ctx the parse tree
	 */
	void enterExpr_paren(GscParser.Expr_parenContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_paren}.
	 * @param ctx the parse tree
	 */
	void exitExpr_paren(GscParser.Expr_parenContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_lvalue}.
	 * @param ctx the parse tree
	 */
	void enterExpr_lvalue(GscParser.Expr_lvalueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_lvalue}.
	 * @param ctx the parse tree
	 */
	void exitExpr_lvalue(GscParser.Expr_lvalueContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_lvalue_array}.
	 * @param ctx the parse tree
	 */
	void enterExpr_lvalue_array(GscParser.Expr_lvalue_arrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_lvalue_array}.
	 * @param ctx the parse tree
	 */
	void exitExpr_lvalue_array(GscParser.Expr_lvalue_arrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_lvalue_field}.
	 * @param ctx the parse tree
	 */
	void enterExpr_lvalue_field(GscParser.Expr_lvalue_fieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_lvalue_field}.
	 * @param ctx the parse tree
	 */
	void exitExpr_lvalue_field(GscParser.Expr_lvalue_fieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_object}.
	 * @param ctx the parse tree
	 */
	void enterExpr_object(GscParser.Expr_objectContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_object}.
	 * @param ctx the parse tree
	 */
	void exitExpr_object(GscParser.Expr_objectContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_object_subexpr}.
	 * @param ctx the parse tree
	 */
	void enterExpr_object_subexpr(GscParser.Expr_object_subexprContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_object_subexpr}.
	 * @param ctx the parse tree
	 */
	void exitExpr_object_subexpr(GscParser.Expr_object_subexprContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_object_subexpr_no_call}.
	 * @param ctx the parse tree
	 */
	void enterExpr_object_subexpr_no_call(GscParser.Expr_object_subexpr_no_callContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_object_subexpr_no_call}.
	 * @param ctx the parse tree
	 */
	void exitExpr_object_subexpr_no_call(GscParser.Expr_object_subexpr_no_callContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_array_or_field_or_call}.
	 * @param ctx the parse tree
	 */
	void enterExpr_array_or_field_or_call(GscParser.Expr_array_or_field_or_callContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_array_or_field_or_call}.
	 * @param ctx the parse tree
	 */
	void exitExpr_array_or_field_or_call(GscParser.Expr_array_or_field_or_callContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_array_or_field}.
	 * @param ctx the parse tree
	 */
	void enterExpr_array_or_field(GscParser.Expr_array_or_fieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_array_or_field}.
	 * @param ctx the parse tree
	 */
	void exitExpr_array_or_field(GscParser.Expr_array_or_fieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_array}.
	 * @param ctx the parse tree
	 */
	void enterExpr_array(GscParser.Expr_arrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_array}.
	 * @param ctx the parse tree
	 */
	void exitExpr_array(GscParser.Expr_arrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_field}.
	 * @param ctx the parse tree
	 */
	void enterExpr_field(GscParser.Expr_fieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_field}.
	 * @param ctx the parse tree
	 */
	void exitExpr_field(GscParser.Expr_fieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_size}.
	 * @param ctx the parse tree
	 */
	void enterExpr_size(GscParser.Expr_sizeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_size}.
	 * @param ctx the parse tree
	 */
	void exitExpr_size(GscParser.Expr_sizeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_thisthread}.
	 * @param ctx the parse tree
	 */
	void enterExpr_thisthread(GscParser.Expr_thisthreadContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_thisthread}.
	 * @param ctx the parse tree
	 */
	void exitExpr_thisthread(GscParser.Expr_thisthreadContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_empty_array}.
	 * @param ctx the parse tree
	 */
	void enterExpr_empty_array(GscParser.Expr_empty_arrayContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_empty_array}.
	 * @param ctx the parse tree
	 */
	void exitExpr_empty_array(GscParser.Expr_empty_arrayContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_undefined}.
	 * @param ctx the parse tree
	 */
	void enterExpr_undefined(GscParser.Expr_undefinedContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_undefined}.
	 * @param ctx the parse tree
	 */
	void exitExpr_undefined(GscParser.Expr_undefinedContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_game}.
	 * @param ctx the parse tree
	 */
	void enterExpr_game(GscParser.Expr_gameContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_game}.
	 * @param ctx the parse tree
	 */
	void exitExpr_game(GscParser.Expr_gameContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_self}.
	 * @param ctx the parse tree
	 */
	void enterExpr_self(GscParser.Expr_selfContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_self}.
	 * @param ctx the parse tree
	 */
	void exitExpr_self(GscParser.Expr_selfContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_anim}.
	 * @param ctx the parse tree
	 */
	void enterExpr_anim(GscParser.Expr_animContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_anim}.
	 * @param ctx the parse tree
	 */
	void exitExpr_anim(GscParser.Expr_animContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_level}.
	 * @param ctx the parse tree
	 */
	void enterExpr_level(GscParser.Expr_levelContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_level}.
	 * @param ctx the parse tree
	 */
	void exitExpr_level(GscParser.Expr_levelContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_animtree}.
	 * @param ctx the parse tree
	 */
	void enterExpr_animtree(GscParser.Expr_animtreeContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_animtree}.
	 * @param ctx the parse tree
	 */
	void exitExpr_animtree(GscParser.Expr_animtreeContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_vector}.
	 * @param ctx the parse tree
	 */
	void enterExpr_vector(GscParser.Expr_vectorContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_vector}.
	 * @param ctx the parse tree
	 */
	void exitExpr_vector(GscParser.Expr_vectorContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_path}.
	 * @param ctx the parse tree
	 */
	void enterExpr_path(GscParser.Expr_pathContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_path}.
	 * @param ctx the parse tree
	 */
	void exitExpr_path(GscParser.Expr_pathContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_identifier_field}.
	 * @param ctx the parse tree
	 */
	void enterExpr_identifier_field(GscParser.Expr_identifier_fieldContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_identifier_field}.
	 * @param ctx the parse tree
	 */
	void exitExpr_identifier_field(GscParser.Expr_identifier_fieldContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_identifier}.
	 * @param ctx the parse tree
	 */
	void enterExpr_identifier(GscParser.Expr_identifierContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_identifier}.
	 * @param ctx the parse tree
	 */
	void exitExpr_identifier(GscParser.Expr_identifierContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_hstring}.
	 * @param ctx the parse tree
	 */
	void enterExpr_hstring(GscParser.Expr_hstringContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_hstring}.
	 * @param ctx the parse tree
	 */
	void exitExpr_hstring(GscParser.Expr_hstringContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_istring}.
	 * @param ctx the parse tree
	 */
	void enterExpr_istring(GscParser.Expr_istringContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_istring}.
	 * @param ctx the parse tree
	 */
	void exitExpr_istring(GscParser.Expr_istringContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_string}.
	 * @param ctx the parse tree
	 */
	void enterExpr_string(GscParser.Expr_stringContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_string}.
	 * @param ctx the parse tree
	 */
	void exitExpr_string(GscParser.Expr_stringContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_float}.
	 * @param ctx the parse tree
	 */
	void enterExpr_float(GscParser.Expr_floatContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_float}.
	 * @param ctx the parse tree
	 */
	void exitExpr_float(GscParser.Expr_floatContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_integer}.
	 * @param ctx the parse tree
	 */
	void enterExpr_integer(GscParser.Expr_integerContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_integer}.
	 * @param ctx the parse tree
	 */
	void exitExpr_integer(GscParser.Expr_integerContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_false}.
	 * @param ctx the parse tree
	 */
	void enterExpr_false(GscParser.Expr_falseContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_false}.
	 * @param ctx the parse tree
	 */
	void exitExpr_false(GscParser.Expr_falseContext ctx);
	/**
	 * Enter a parse tree produced by {@link GscParser#expr_true}.
	 * @param ctx the parse tree
	 */
	void enterExpr_true(GscParser.Expr_trueContext ctx);
	/**
	 * Exit a parse tree produced by {@link GscParser#expr_true}.
	 * @param ctx the parse tree
	 */
	void exitExpr_true(GscParser.Expr_trueContext ctx);
}