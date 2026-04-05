// Generated from /Volumes/T7/development/projects/xensik/gsc-tool/new_parser/gsc_grammar.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class gsc_grammarParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		HASH=1, DEVBEGIN=2, DEVEND=3, INLINE=4, INCLUDE=5, USINGTREE=6, ANIMTREE=7, 
		ENDON=8, NOTIFY=9, WAIT=10, WAITTILL=11, WAITTILLMATCH=12, WAITTILLFRAMEEND=13, 
		WAITFRAME=14, IF=15, ELSE=16, DO=17, WHILE=18, FOR=19, FOREACH=20, IN=21, 
		SWITCH=22, CASE=23, DEFAULT=24, BREAK=25, CONTINUE=26, RETURN=27, BREAKPOINT=28, 
		PROFBEGIN=29, PROFEND=30, ASSERT=31, ASSERTEX=32, ASSERTMSG=33, THREAD=34, 
		CHILDTHREAD=35, THISTHREAD=36, CALL=37, TRUE=38, FALSE=39, UNDEFINED=40, 
		SIZE=41, GAME=42, SELF=43, ANIM=44, LEVEL=45, ISDEFINED=46, ISTRUE=47, 
		LPAREN=48, RPAREN=49, LBRACE=50, RBRACE=51, LBRACKET=52, RBRACKET=53, 
		COMMA=54, DOT=55, DOUBLEDOT=56, ELLIPSIS=57, DOUBLECOLON=58, COLON=59, 
		SEMICOLON=60, QMARK=61, INCREMENT=62, DECREMENT=63, LSHIFT=64, RSHIFT=65, 
		OR=66, AND=67, EQUALITY=68, INEQUALITY=69, LESS_EQUAL=70, GREATER_EQUAL=71, 
		LESS=72, GREATER=73, NOT=74, COMPLEMENT=75, ASSIGN=76, AMUL=77, ADIV=78, 
		AMOD=79, AADD=80, ASUB=81, ARSH=82, ALSH=83, ABWOR=84, ABWXOR=85, ABWAND=86, 
		BW_OR=87, BW_XOR=88, BW_AND=89, ADD=90, SUB=91, MUL=92, DIV=93, MOD=94, 
		FLOAT=95, INTEGER=96, STRING=97, ISTRING=98, HSTRING=99, IDENTIFIER=100, 
		PATH=101, WHITESPACE=102, LINE_COMMENT=103, BLOCK_COMMENT=104, GSCDOC_COMMENT=105, 
		AUTOEXEC=106, CODECALL=107, PRIVATE=108, CONST=109, WAITREALTIME=110, 
		GETNEXTARRAYKEY=111, GETFIRSTARRAYKEY=112, GETDVARCOLORALPHA=113, GETDVARCOLORBLUE=114, 
		GETDVARCOLORGREEN=115, GETDVARCOLORRED=116, GETDVARVECTOR=117, GETDVARFLOAT=118, 
		GETDVARINT=119, GETDVAR=120, GETTIME=121, ABS=122, VECTORTOANGLES=123, 
		ANGLECLAMP180=124, ANGLESTOFORWARD=125, ANGLESTORIGHT=126, ANGLESTOUP=127, 
		VECTORSCALE=128;
	public static final int
		RULE_program = 0, RULE_include = 1, RULE_inline = 2, RULE_declaration = 3, 
		RULE_decl_usingtree = 4, RULE_decl_constant = 5, RULE_decl_function = 6, 
		RULE_stmt = 7, RULE_stmt_list = 8, RULE_stmt_or_dev_list = 9, RULE_stmt_dev = 10, 
		RULE_stmt_comp = 11, RULE_stmt_expr = 12, RULE_stmt_const = 13, RULE_stmt_endon = 14, 
		RULE_stmt_notify = 15, RULE_stmt_wait = 16, RULE_stmt_waittill = 17, RULE_stmt_waittillmatch = 18, 
		RULE_stmt_waittillframeend = 19, RULE_stmt_waitframe = 20, RULE_stmt_waitrealtime = 21, 
		RULE_stmt_if = 22, RULE_stmt_while = 23, RULE_stmt_dowhile = 24, RULE_stmt_for = 25, 
		RULE_stmt_foreach = 26, RULE_stmt_switch = 27, RULE_stmt_case = 28, RULE_stmt_default = 29, 
		RULE_stmt_break = 30, RULE_stmt_continue = 31, RULE_stmt_return = 32, 
		RULE_stmt_breakpoint = 33, RULE_stmt_prof_begin = 34, RULE_stmt_prof_end = 35, 
		RULE_stmt_assert = 36, RULE_stmt_assertex = 37, RULE_stmt_assertmsg = 38, 
		RULE_expr_assign = 39, RULE_expr = 40, RULE_expr_ternary = 41, RULE_expr_or = 42, 
		RULE_expr_and = 43, RULE_expr_bw_or = 44, RULE_expr_bw_xor = 45, RULE_expr_bw_and = 46, 
		RULE_expr_equality = 47, RULE_expr_relational = 48, RULE_expr_shift = 49, 
		RULE_expr_additive = 50, RULE_expr_multiplicative = 51, RULE_expr_unary = 52, 
		RULE_expr_complement = 53, RULE_expr_not = 54, RULE_expr_negate = 55, 
		RULE_expr_animation = 56, RULE_expr_primary = 57, RULE_expr_call = 58, 
		RULE_expr_method = 59, RULE_expr_function = 60, RULE_expr_pointer = 61, 
		RULE_expr_call_optimized = 62, RULE_expr_call_optimized_vector = 63, RULE_expr_call_optimized_vector_array = 64, 
		RULE_expr_isdefined = 65, RULE_expr_istrue = 66, RULE_expr_reference = 67, 
		RULE_expr_parameters = 68, RULE_expr_parameters_default = 69, RULE_expr_arguments = 70, 
		RULE_expr_tuple = 71, RULE_expr_add_array = 72, RULE_expr_paren = 73, 
		RULE_expr_lvalue = 74, RULE_expr_lvalue_array = 75, RULE_expr_lvalue_field = 76, 
		RULE_expr_object = 77, RULE_expr_object_subexpr = 78, RULE_expr_object_subexpr_no_call = 79, 
		RULE_expr_array_or_field_or_call = 80, RULE_expr_array_or_field = 81, 
		RULE_expr_array = 82, RULE_expr_field = 83, RULE_expr_size = 84, RULE_expr_thisthread = 85, 
		RULE_expr_empty_array = 86, RULE_expr_undefined = 87, RULE_expr_game = 88, 
		RULE_expr_self = 89, RULE_expr_anim = 90, RULE_expr_level = 91, RULE_expr_animtree = 92, 
		RULE_expr_vector = 93, RULE_expr_path = 94, RULE_expr_identifier_field = 95, 
		RULE_expr_identifier = 96, RULE_expr_hstring = 97, RULE_expr_istring = 98, 
		RULE_expr_string = 99, RULE_expr_float = 100, RULE_expr_integer = 101, 
		RULE_expr_false = 102, RULE_expr_true = 103;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "include", "inline", "declaration", "decl_usingtree", "decl_constant", 
			"decl_function", "stmt", "stmt_list", "stmt_or_dev_list", "stmt_dev", 
			"stmt_comp", "stmt_expr", "stmt_const", "stmt_endon", "stmt_notify", 
			"stmt_wait", "stmt_waittill", "stmt_waittillmatch", "stmt_waittillframeend", 
			"stmt_waitframe", "stmt_waitrealtime", "stmt_if", "stmt_while", "stmt_dowhile", 
			"stmt_for", "stmt_foreach", "stmt_switch", "stmt_case", "stmt_default", 
			"stmt_break", "stmt_continue", "stmt_return", "stmt_breakpoint", "stmt_prof_begin", 
			"stmt_prof_end", "stmt_assert", "stmt_assertex", "stmt_assertmsg", "expr_assign", 
			"expr", "expr_ternary", "expr_or", "expr_and", "expr_bw_or", "expr_bw_xor", 
			"expr_bw_and", "expr_equality", "expr_relational", "expr_shift", "expr_additive", 
			"expr_multiplicative", "expr_unary", "expr_complement", "expr_not", "expr_negate", 
			"expr_animation", "expr_primary", "expr_call", "expr_method", "expr_function", 
			"expr_pointer", "expr_call_optimized", "expr_call_optimized_vector", 
			"expr_call_optimized_vector_array", "expr_isdefined", "expr_istrue", 
			"expr_reference", "expr_parameters", "expr_parameters_default", "expr_arguments", 
			"expr_tuple", "expr_add_array", "expr_paren", "expr_lvalue", "expr_lvalue_array", 
			"expr_lvalue_field", "expr_object", "expr_object_subexpr", "expr_object_subexpr_no_call", 
			"expr_array_or_field_or_call", "expr_array_or_field", "expr_array", "expr_field", 
			"expr_size", "expr_thisthread", "expr_empty_array", "expr_undefined", 
			"expr_game", "expr_self", "expr_anim", "expr_level", "expr_animtree", 
			"expr_vector", "expr_path", "expr_identifier_field", "expr_identifier", 
			"expr_hstring", "expr_istring", "expr_string", "expr_float", "expr_integer", 
			"expr_false", "expr_true"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, "'#'", "'/#'", "'#/'", "'#inline'", "'#include'", "'#using_animtree'", 
			"'#animtree'", "'endon'", "'notify'", "'wait'", "'waittill'", "'waittillmatch'", 
			"'waittillframeend'", "'waitframe'", "'if'", "'else'", "'do'", "'while'", 
			"'for'", "'foreach'", "'in'", "'switch'", "'case'", "'default'", "'break'", 
			"'continue'", "'return'", "'breakpoint'", "'prof_begin'", "'prof_end'", 
			"'assert'", "'assertex'", "'assertmsg'", "'thread'", "'childthread'", 
			"'thisthread'", "'call'", "'true'", "'false'", "'undefined'", "'size'", 
			"'game'", "'self'", "'anim'", "'level'", "'isdefined'", "'istrue'", "'('", 
			"')'", "'{'", "'}'", "'['", "']'", "','", "'.'", "'..'", "'...'", "'::'", 
			"':'", "';'", "'?'", "'++'", "'--'", "'<<'", "'>>'", "'||'", "'&&'", 
			"'=='", "'!='", "'<='", "'>='", "'<'", "'>'", "'!'", "'~'", "'='", "'*='", 
			"'/='", "'%='", "'+='", "'-='", "'>>='", "'<<='", "'|='", "'^='", "'&='", 
			"'|'", "'^'", "'&'", "'+'", "'-'", "'*'", "'/'", "'%'", null, null, null, 
			null, null, null, null, null, null, null, null, "'autoexec'", "'codecall'", 
			"'private'", "'const'", "'waitrealtime'", "'getnextarraykey'", "'getfirstarraykey'", 
			"'getdvarcoloralpha'", "'getdvarcolorblue'", "'getdvarcolorgreen'", "'getdvarcolorred'", 
			"'getdvarvector'", "'getdvarfloat'", "'getdvarint'", "'getdvar'", "'gettime'", 
			"'abs'", "'vectortoangles'", "'angleclamp180'", "'anglestoforward'", 
			"'anglestoright'", "'anglestoup'", "'vectorscale'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "HASH", "DEVBEGIN", "DEVEND", "INLINE", "INCLUDE", "USINGTREE", 
			"ANIMTREE", "ENDON", "NOTIFY", "WAIT", "WAITTILL", "WAITTILLMATCH", "WAITTILLFRAMEEND", 
			"WAITFRAME", "IF", "ELSE", "DO", "WHILE", "FOR", "FOREACH", "IN", "SWITCH", 
			"CASE", "DEFAULT", "BREAK", "CONTINUE", "RETURN", "BREAKPOINT", "PROFBEGIN", 
			"PROFEND", "ASSERT", "ASSERTEX", "ASSERTMSG", "THREAD", "CHILDTHREAD", 
			"THISTHREAD", "CALL", "TRUE", "FALSE", "UNDEFINED", "SIZE", "GAME", "SELF", 
			"ANIM", "LEVEL", "ISDEFINED", "ISTRUE", "LPAREN", "RPAREN", "LBRACE", 
			"RBRACE", "LBRACKET", "RBRACKET", "COMMA", "DOT", "DOUBLEDOT", "ELLIPSIS", 
			"DOUBLECOLON", "COLON", "SEMICOLON", "QMARK", "INCREMENT", "DECREMENT", 
			"LSHIFT", "RSHIFT", "OR", "AND", "EQUALITY", "INEQUALITY", "LESS_EQUAL", 
			"GREATER_EQUAL", "LESS", "GREATER", "NOT", "COMPLEMENT", "ASSIGN", "AMUL", 
			"ADIV", "AMOD", "AADD", "ASUB", "ARSH", "ALSH", "ABWOR", "ABWXOR", "ABWAND", 
			"BW_OR", "BW_XOR", "BW_AND", "ADD", "SUB", "MUL", "DIV", "MOD", "FLOAT", 
			"INTEGER", "STRING", "ISTRING", "HSTRING", "IDENTIFIER", "PATH", "WHITESPACE", 
			"LINE_COMMENT", "BLOCK_COMMENT", "GSCDOC_COMMENT", "AUTOEXEC", "CODECALL", 
			"PRIVATE", "CONST", "WAITREALTIME", "GETNEXTARRAYKEY", "GETFIRSTARRAYKEY", 
			"GETDVARCOLORALPHA", "GETDVARCOLORBLUE", "GETDVARCOLORGREEN", "GETDVARCOLORRED", 
			"GETDVARVECTOR", "GETDVARFLOAT", "GETDVARINT", "GETDVAR", "GETTIME", 
			"ABS", "VECTORTOANGLES", "ANGLECLAMP180", "ANGLESTOFORWARD", "ANGLESTORIGHT", 
			"ANGLESTOUP", "VECTORSCALE"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "gsc_grammar.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }


	    int version = 1; // Set this based on the version you want to parse

	public gsc_grammarParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(gsc_grammarParser.EOF, 0); }
		public List<IncludeContext> include() {
			return getRuleContexts(IncludeContext.class);
		}
		public IncludeContext include(int i) {
			return getRuleContext(IncludeContext.class,i);
		}
		public List<InlineContext> inline() {
			return getRuleContexts(InlineContext.class);
		}
		public InlineContext inline(int i) {
			return getRuleContext(InlineContext.class,i);
		}
		public List<DeclarationContext> declaration() {
			return getRuleContexts(DeclarationContext.class);
		}
		public DeclarationContext declaration(int i) {
			return getRuleContext(DeclarationContext.class,i);
		}
		public List<TerminalNode> SEMICOLON() { return getTokens(gsc_grammarParser.SEMICOLON); }
		public TerminalNode SEMICOLON(int i) {
			return getToken(gsc_grammarParser.SEMICOLON, i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(214);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 1152923703630102652L) != 0) || ((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & 449L) != 0)) {
				{
				setState(212);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case INCLUDE:
					{
					setState(208);
					include();
					}
					break;
				case INLINE:
					{
					setState(209);
					inline();
					}
					break;
				case DEVBEGIN:
				case DEVEND:
				case USINGTREE:
				case SIZE:
				case IDENTIFIER:
				case AUTOEXEC:
				case CODECALL:
				case PRIVATE:
					{
					setState(210);
					declaration();
					}
					break;
				case SEMICOLON:
					{
					setState(211);
					match(SEMICOLON);
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(216);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(217);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IncludeContext extends ParserRuleContext {
		public TerminalNode INCLUDE() { return getToken(gsc_grammarParser.INCLUDE, 0); }
		public Expr_pathContext expr_path() {
			return getRuleContext(Expr_pathContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public IncludeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_include; }
	}

	public final IncludeContext include() throws RecognitionException {
		IncludeContext _localctx = new IncludeContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_include);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(219);
			match(INCLUDE);
			setState(220);
			expr_path();
			setState(221);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class InlineContext extends ParserRuleContext {
		public TerminalNode INLINE() { return getToken(gsc_grammarParser.INLINE, 0); }
		public Expr_pathContext expr_path() {
			return getRuleContext(Expr_pathContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public InlineContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_inline; }
	}

	public final InlineContext inline() throws RecognitionException {
		InlineContext _localctx = new InlineContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_inline);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(223);
			match(INLINE);
			setState(224);
			expr_path();
			setState(225);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class DeclarationContext extends ParserRuleContext {
		public TerminalNode DEVBEGIN() { return getToken(gsc_grammarParser.DEVBEGIN, 0); }
		public TerminalNode DEVEND() { return getToken(gsc_grammarParser.DEVEND, 0); }
		public Decl_usingtreeContext decl_usingtree() {
			return getRuleContext(Decl_usingtreeContext.class,0);
		}
		public Decl_constantContext decl_constant() {
			return getRuleContext(Decl_constantContext.class,0);
		}
		public Decl_functionContext decl_function() {
			return getRuleContext(Decl_functionContext.class,0);
		}
		public DeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_declaration; }
	}

	public final DeclarationContext declaration() throws RecognitionException {
		DeclarationContext _localctx = new DeclarationContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_declaration);
		try {
			setState(234);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(227);
				match(DEVBEGIN);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(228);
				match(DEVEND);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(229);
				decl_usingtree();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(230);
				decl_constant();
				setState(231);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(233);
				decl_function();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Decl_usingtreeContext extends ParserRuleContext {
		public TerminalNode USINGTREE() { return getToken(gsc_grammarParser.USINGTREE, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public Expr_stringContext expr_string() {
			return getRuleContext(Expr_stringContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Decl_usingtreeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl_usingtree; }
	}

	public final Decl_usingtreeContext decl_usingtree() throws RecognitionException {
		Decl_usingtreeContext _localctx = new Decl_usingtreeContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_decl_usingtree);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(236);
			match(USINGTREE);
			setState(237);
			match(LPAREN);
			setState(238);
			expr_string();
			setState(239);
			match(RPAREN);
			setState(240);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Decl_constantContext extends ParserRuleContext {
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(gsc_grammarParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Decl_constantContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl_constant; }
	}

	public final Decl_constantContext decl_constant() throws RecognitionException {
		Decl_constantContext _localctx = new Decl_constantContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_decl_constant);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(242);
			expr_identifier();
			setState(243);
			match(ASSIGN);
			setState(244);
			expr();
			setState(245);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Decl_functionContext extends ParserRuleContext {
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Stmt_compContext stmt_comp() {
			return getRuleContext(Stmt_compContext.class,0);
		}
		public Expr_parametersContext expr_parameters() {
			return getRuleContext(Expr_parametersContext.class,0);
		}
		public TerminalNode AUTOEXEC() { return getToken(gsc_grammarParser.AUTOEXEC, 0); }
		public TerminalNode CODECALL() { return getToken(gsc_grammarParser.CODECALL, 0); }
		public TerminalNode PRIVATE() { return getToken(gsc_grammarParser.PRIVATE, 0); }
		public Decl_functionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_decl_function; }
	}

	public final Decl_functionContext decl_function() throws RecognitionException {
		Decl_functionContext _localctx = new Decl_functionContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_decl_function);
		int _la;
		try {
			setState(268);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(247);
				expr_identifier();
				setState(248);
				match(LPAREN);
				setState(250);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SIZE || _la==IDENTIFIER) {
					{
					setState(249);
					expr_parameters();
					}
				}

				setState(252);
				match(RPAREN);
				setState(253);
				stmt_comp();
				setState(254);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(257);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (((((_la - 106)) & ~0x3f) == 0 && ((1L << (_la - 106)) & 7L) != 0)) {
					{
					setState(256);
					_la = _input.LA(1);
					if ( !(((((_la - 106)) & ~0x3f) == 0 && ((1L << (_la - 106)) & 7L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
				}

				setState(259);
				expr_identifier();
				setState(260);
				match(LPAREN);
				setState(262);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==SIZE || _la==IDENTIFIER) {
					{
					setState(261);
					expr_parameters();
					}
				}

				setState(264);
				match(RPAREN);
				setState(265);
				stmt_comp();
				setState(266);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtContext extends ParserRuleContext {
		public Stmt_compContext stmt_comp() {
			return getRuleContext(Stmt_compContext.class,0);
		}
		public Stmt_exprContext stmt_expr() {
			return getRuleContext(Stmt_exprContext.class,0);
		}
		public Stmt_constContext stmt_const() {
			return getRuleContext(Stmt_constContext.class,0);
		}
		public Stmt_endonContext stmt_endon() {
			return getRuleContext(Stmt_endonContext.class,0);
		}
		public Stmt_notifyContext stmt_notify() {
			return getRuleContext(Stmt_notifyContext.class,0);
		}
		public Stmt_waitContext stmt_wait() {
			return getRuleContext(Stmt_waitContext.class,0);
		}
		public Stmt_waittillContext stmt_waittill() {
			return getRuleContext(Stmt_waittillContext.class,0);
		}
		public Stmt_waittillmatchContext stmt_waittillmatch() {
			return getRuleContext(Stmt_waittillmatchContext.class,0);
		}
		public Stmt_waittillframeendContext stmt_waittillframeend() {
			return getRuleContext(Stmt_waittillframeendContext.class,0);
		}
		public Stmt_waitframeContext stmt_waitframe() {
			return getRuleContext(Stmt_waitframeContext.class,0);
		}
		public Stmt_waitrealtimeContext stmt_waitrealtime() {
			return getRuleContext(Stmt_waitrealtimeContext.class,0);
		}
		public Stmt_ifContext stmt_if() {
			return getRuleContext(Stmt_ifContext.class,0);
		}
		public Stmt_whileContext stmt_while() {
			return getRuleContext(Stmt_whileContext.class,0);
		}
		public Stmt_dowhileContext stmt_dowhile() {
			return getRuleContext(Stmt_dowhileContext.class,0);
		}
		public Stmt_forContext stmt_for() {
			return getRuleContext(Stmt_forContext.class,0);
		}
		public Stmt_foreachContext stmt_foreach() {
			return getRuleContext(Stmt_foreachContext.class,0);
		}
		public Stmt_switchContext stmt_switch() {
			return getRuleContext(Stmt_switchContext.class,0);
		}
		public Stmt_caseContext stmt_case() {
			return getRuleContext(Stmt_caseContext.class,0);
		}
		public Stmt_defaultContext stmt_default() {
			return getRuleContext(Stmt_defaultContext.class,0);
		}
		public Stmt_breakContext stmt_break() {
			return getRuleContext(Stmt_breakContext.class,0);
		}
		public Stmt_continueContext stmt_continue() {
			return getRuleContext(Stmt_continueContext.class,0);
		}
		public Stmt_returnContext stmt_return() {
			return getRuleContext(Stmt_returnContext.class,0);
		}
		public Stmt_breakpointContext stmt_breakpoint() {
			return getRuleContext(Stmt_breakpointContext.class,0);
		}
		public Stmt_prof_beginContext stmt_prof_begin() {
			return getRuleContext(Stmt_prof_beginContext.class,0);
		}
		public Stmt_prof_endContext stmt_prof_end() {
			return getRuleContext(Stmt_prof_endContext.class,0);
		}
		public Stmt_assertContext stmt_assert() {
			return getRuleContext(Stmt_assertContext.class,0);
		}
		public Stmt_assertexContext stmt_assertex() {
			return getRuleContext(Stmt_assertexContext.class,0);
		}
		public Stmt_assertmsgContext stmt_assertmsg() {
			return getRuleContext(Stmt_assertmsgContext.class,0);
		}
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_stmt);
		try {
			setState(312);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(270);
				stmt_comp();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(271);
				stmt_expr();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(272);
				stmt_const();
				setState(273);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(275);
				stmt_endon();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(276);
				stmt_notify();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(277);
				stmt_wait();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(278);
				stmt_waittill();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(279);
				stmt_waittillmatch();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(280);
				stmt_waittillframeend();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(281);
				stmt_waitframe();
				setState(282);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(284);
				stmt_waitrealtime();
				setState(285);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(287);
				stmt_if();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(288);
				stmt_while();
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(289);
				stmt_dowhile();
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(290);
				stmt_for();
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(291);
				stmt_foreach();
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(292);
				stmt_switch();
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(293);
				stmt_case();
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(294);
				stmt_default();
				}
				break;
			case 20:
				enterOuterAlt(_localctx, 20);
				{
				setState(295);
				stmt_break();
				}
				break;
			case 21:
				enterOuterAlt(_localctx, 21);
				{
				setState(296);
				stmt_continue();
				}
				break;
			case 22:
				enterOuterAlt(_localctx, 22);
				{
				setState(297);
				stmt_return();
				}
				break;
			case 23:
				enterOuterAlt(_localctx, 23);
				{
				setState(298);
				stmt_breakpoint();
				setState(299);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 24:
				enterOuterAlt(_localctx, 24);
				{
				setState(301);
				stmt_prof_begin();
				}
				break;
			case 25:
				enterOuterAlt(_localctx, 25);
				{
				setState(302);
				stmt_prof_end();
				}
				break;
			case 26:
				enterOuterAlt(_localctx, 26);
				{
				setState(303);
				stmt_assert();
				setState(304);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 27:
				enterOuterAlt(_localctx, 27);
				{
				setState(306);
				stmt_assertex();
				setState(307);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 28:
				enterOuterAlt(_localctx, 28);
				{
				setState(309);
				stmt_assertmsg();
				setState(310);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_listContext extends ParserRuleContext {
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public Stmt_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_list; }
	}

	public final Stmt_listContext stmt_list() throws RecognitionException {
		Stmt_listContext _localctx = new Stmt_listContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_stmt_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(315); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(314);
				stmt();
				}
				}
				setState(317); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & -3453066638409145344L) != 0) || ((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & 1539L) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_or_dev_listContext extends ParserRuleContext {
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public List<Stmt_devContext> stmt_dev() {
			return getRuleContexts(Stmt_devContext.class);
		}
		public Stmt_devContext stmt_dev(int i) {
			return getRuleContext(Stmt_devContext.class,i);
		}
		public Stmt_or_dev_listContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_or_dev_list; }
	}

	public final Stmt_or_dev_listContext stmt_or_dev_list() throws RecognitionException {
		Stmt_or_dev_listContext _localctx = new Stmt_or_dev_listContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_stmt_or_dev_list);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(321); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				setState(321);
				_errHandler.sync(this);
				switch (_input.LA(1)) {
				case WAIT:
				case WAITTILLFRAMEEND:
				case WAITFRAME:
				case IF:
				case DO:
				case WHILE:
				case FOR:
				case FOREACH:
				case SWITCH:
				case CASE:
				case DEFAULT:
				case BREAK:
				case CONTINUE:
				case RETURN:
				case BREAKPOINT:
				case PROFBEGIN:
				case PROFEND:
				case ASSERT:
				case ASSERTEX:
				case ASSERTMSG:
				case THREAD:
				case CHILDTHREAD:
				case CALL:
				case SIZE:
				case GAME:
				case SELF:
				case ANIM:
				case LEVEL:
				case LBRACE:
				case LBRACKET:
				case SEMICOLON:
				case INCREMENT:
				case DECREMENT:
				case IDENTIFIER:
				case PATH:
				case CONST:
				case WAITREALTIME:
					{
					setState(319);
					stmt();
					}
					break;
				case DEVBEGIN:
					{
					setState(320);
					stmt_dev();
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				}
				setState(323); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & -3453066638409145340L) != 0) || ((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & 1539L) != 0) );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_devContext extends ParserRuleContext {
		public TerminalNode DEVBEGIN() { return getToken(gsc_grammarParser.DEVBEGIN, 0); }
		public TerminalNode DEVEND() { return getToken(gsc_grammarParser.DEVEND, 0); }
		public Stmt_listContext stmt_list() {
			return getRuleContext(Stmt_listContext.class,0);
		}
		public Stmt_devContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_dev; }
	}

	public final Stmt_devContext stmt_dev() throws RecognitionException {
		Stmt_devContext _localctx = new Stmt_devContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_stmt_dev);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(325);
			match(DEVBEGIN);
			setState(327);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -3453066638409145344L) != 0) || ((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & 1539L) != 0)) {
				{
				setState(326);
				stmt_list();
				}
			}

			setState(329);
			match(DEVEND);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_compContext extends ParserRuleContext {
		public TerminalNode LBRACE() { return getToken(gsc_grammarParser.LBRACE, 0); }
		public TerminalNode RBRACE() { return getToken(gsc_grammarParser.RBRACE, 0); }
		public Stmt_or_dev_listContext stmt_or_dev_list() {
			return getRuleContext(Stmt_or_dev_listContext.class,0);
		}
		public Stmt_compContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_comp; }
	}

	public final Stmt_compContext stmt_comp() throws RecognitionException {
		Stmt_compContext _localctx = new Stmt_compContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_stmt_comp);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(331);
			match(LBRACE);
			setState(333);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -3453066638409145340L) != 0) || ((((_la - 100)) & ~0x3f) == 0 && ((1L << (_la - 100)) & 1539L) != 0)) {
				{
				setState(332);
				stmt_or_dev_list();
				}
			}

			setState(335);
			match(RBRACE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_exprContext extends ParserRuleContext {
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_callContext expr_call() {
			return getRuleContext(Expr_callContext.class,0);
		}
		public Expr_methodContext expr_method() {
			return getRuleContext(Expr_methodContext.class,0);
		}
		public Expr_assignContext expr_assign() {
			return getRuleContext(Expr_assignContext.class,0);
		}
		public Stmt_exprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_expr; }
	}

	public final Stmt_exprContext stmt_expr() throws RecognitionException {
		Stmt_exprContext _localctx = new Stmt_exprContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_stmt_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(340);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				{
				setState(337);
				expr_call();
				}
				break;
			case 2:
				{
				setState(338);
				expr_method();
				}
				break;
			case 3:
				{
				setState(339);
				expr_assign();
				}
				break;
			}
			setState(342);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_constContext extends ParserRuleContext {
		public TerminalNode CONST() { return getToken(gsc_grammarParser.CONST, 0); }
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(gsc_grammarParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_constContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_const; }
	}

	public final Stmt_constContext stmt_const() throws RecognitionException {
		Stmt_constContext _localctx = new Stmt_constContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_stmt_const);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(344);
			match(CONST);
			setState(345);
			expr_identifier();
			setState(346);
			match(ASSIGN);
			setState(347);
			expr();
			setState(348);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_endonContext extends ParserRuleContext {
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public TerminalNode ENDON() { return getToken(gsc_grammarParser.ENDON, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_endonContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_endon; }
	}

	public final Stmt_endonContext stmt_endon() throws RecognitionException {
		Stmt_endonContext _localctx = new Stmt_endonContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_stmt_endon);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(350);
			expr_object();
			setState(351);
			match(ENDON);
			setState(352);
			match(LPAREN);
			setState(353);
			expr();
			setState(354);
			match(RPAREN);
			setState(355);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_notifyContext extends ParserRuleContext {
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public TerminalNode NOTIFY() { return getToken(gsc_grammarParser.NOTIFY, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_notifyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_notify; }
	}

	public final Stmt_notifyContext stmt_notify() throws RecognitionException {
		Stmt_notifyContext _localctx = new Stmt_notifyContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_stmt_notify);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(357);
			expr_object();
			setState(358);
			match(NOTIFY);
			setState(359);
			match(LPAREN);
			setState(360);
			expr();
			setState(363);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(361);
				match(COMMA);
				setState(362);
				expr_arguments();
				}
			}

			setState(365);
			match(RPAREN);
			setState(366);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waitContext extends ParserRuleContext {
		public TerminalNode WAIT() { return getToken(gsc_grammarParser.WAIT, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_waitContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_wait; }
	}

	public final Stmt_waitContext stmt_wait() throws RecognitionException {
		Stmt_waitContext _localctx = new Stmt_waitContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_stmt_wait);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(368);
			match(WAIT);
			setState(369);
			expr();
			setState(370);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waittillContext extends ParserRuleContext {
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public TerminalNode WAITTILL() { return getToken(gsc_grammarParser.WAITTILL, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_waittillContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_waittill; }
	}

	public final Stmt_waittillContext stmt_waittill() throws RecognitionException {
		Stmt_waittillContext _localctx = new Stmt_waittillContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_stmt_waittill);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(372);
			expr_object();
			setState(373);
			match(WAITTILL);
			setState(374);
			match(LPAREN);
			setState(375);
			expr();
			setState(378);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(376);
				match(COMMA);
				setState(377);
				expr_arguments();
				}
			}

			setState(380);
			match(RPAREN);
			setState(381);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waittillmatchContext extends ParserRuleContext {
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public TerminalNode WAITTILLMATCH() { return getToken(gsc_grammarParser.WAITTILLMATCH, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_waittillmatchContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_waittillmatch; }
	}

	public final Stmt_waittillmatchContext stmt_waittillmatch() throws RecognitionException {
		Stmt_waittillmatchContext _localctx = new Stmt_waittillmatchContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_stmt_waittillmatch);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(383);
			expr_object();
			setState(384);
			match(WAITTILLMATCH);
			setState(385);
			match(LPAREN);
			setState(386);
			expr();
			setState(389);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(387);
				match(COMMA);
				setState(388);
				expr_arguments();
				}
			}

			setState(391);
			match(RPAREN);
			setState(392);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waittillframeendContext extends ParserRuleContext {
		public TerminalNode WAITTILLFRAMEEND() { return getToken(gsc_grammarParser.WAITTILLFRAMEEND, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Stmt_waittillframeendContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_waittillframeend; }
	}

	public final Stmt_waittillframeendContext stmt_waittillframeend() throws RecognitionException {
		Stmt_waittillframeendContext _localctx = new Stmt_waittillframeendContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_stmt_waittillframeend);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(394);
			match(WAITTILLFRAMEEND);
			setState(397);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(395);
				match(LPAREN);
				setState(396);
				match(RPAREN);
				}
			}

			setState(399);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waitframeContext extends ParserRuleContext {
		public TerminalNode WAITFRAME() { return getToken(gsc_grammarParser.WAITFRAME, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Stmt_waitframeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_waitframe; }
	}

	public final Stmt_waitframeContext stmt_waitframe() throws RecognitionException {
		Stmt_waitframeContext _localctx = new Stmt_waitframeContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_stmt_waitframe);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(401);
			match(WAITFRAME);
			setState(404);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==LPAREN) {
				{
				setState(402);
				match(LPAREN);
				setState(403);
				match(RPAREN);
				}
			}

			setState(406);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_waitrealtimeContext extends ParserRuleContext {
		public TerminalNode WAITREALTIME() { return getToken(gsc_grammarParser.WAITREALTIME, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_waitrealtimeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_waitrealtime; }
	}

	public final Stmt_waitrealtimeContext stmt_waitrealtime() throws RecognitionException {
		Stmt_waitrealtimeContext _localctx = new Stmt_waitrealtimeContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_stmt_waitrealtime);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(408);
			match(WAITREALTIME);
			setState(409);
			expr();
			setState(410);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_ifContext extends ParserRuleContext {
		public TerminalNode IF() { return getToken(gsc_grammarParser.IF, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public TerminalNode ELSE() { return getToken(gsc_grammarParser.ELSE, 0); }
		public Stmt_ifContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_if; }
	}

	public final Stmt_ifContext stmt_if() throws RecognitionException {
		Stmt_ifContext _localctx = new Stmt_ifContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_stmt_if);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(412);
			match(IF);
			setState(413);
			match(LPAREN);
			setState(414);
			expr();
			setState(415);
			match(RPAREN);
			setState(416);
			stmt();
			setState(419);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				{
				setState(417);
				match(ELSE);
				setState(418);
				stmt();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_whileContext extends ParserRuleContext {
		public TerminalNode WHILE() { return getToken(gsc_grammarParser.WHILE, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public Stmt_whileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_while; }
	}

	public final Stmt_whileContext stmt_while() throws RecognitionException {
		Stmt_whileContext _localctx = new Stmt_whileContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_stmt_while);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(421);
			match(WHILE);
			setState(422);
			match(LPAREN);
			setState(423);
			expr();
			setState(424);
			match(RPAREN);
			setState(425);
			stmt();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_dowhileContext extends ParserRuleContext {
		public TerminalNode DO() { return getToken(gsc_grammarParser.DO, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public TerminalNode WHILE() { return getToken(gsc_grammarParser.WHILE, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_dowhileContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_dowhile; }
	}

	public final Stmt_dowhileContext stmt_dowhile() throws RecognitionException {
		Stmt_dowhileContext _localctx = new Stmt_dowhileContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_stmt_dowhile);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(427);
			match(DO);
			setState(428);
			stmt();
			setState(429);
			match(WHILE);
			setState(430);
			match(LPAREN);
			setState(431);
			expr();
			setState(432);
			match(RPAREN);
			setState(433);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_forContext extends ParserRuleContext {
		public TerminalNode FOR() { return getToken(gsc_grammarParser.FOR, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public List<TerminalNode> SEMICOLON() { return getTokens(gsc_grammarParser.SEMICOLON); }
		public TerminalNode SEMICOLON(int i) {
			return getToken(gsc_grammarParser.SEMICOLON, i);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public List<Expr_assignContext> expr_assign() {
			return getRuleContexts(Expr_assignContext.class);
		}
		public Expr_assignContext expr_assign(int i) {
			return getRuleContext(Expr_assignContext.class,i);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Stmt_forContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_for; }
	}

	public final Stmt_forContext stmt_for() throws RecognitionException {
		Stmt_forContext _localctx = new Stmt_forContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_stmt_for);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(435);
			match(FOR);
			setState(436);
			match(LPAREN);
			setState(438);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -4607114060100534272L) != 0) || _la==IDENTIFIER || _la==PATH) {
				{
				setState(437);
				expr_assign();
				}
			}

			setState(440);
			match(SEMICOLON);
			setState(442);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(441);
				expr();
				}
			}

			setState(444);
			match(SEMICOLON);
			setState(446);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & -4607114060100534272L) != 0) || _la==IDENTIFIER || _la==PATH) {
				{
				setState(445);
				expr_assign();
				}
			}

			setState(448);
			match(RPAREN);
			setState(449);
			stmt();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_foreachContext extends ParserRuleContext {
		public TerminalNode FOREACH() { return getToken(gsc_grammarParser.FOREACH, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public List<Expr_identifierContext> expr_identifier() {
			return getRuleContexts(Expr_identifierContext.class);
		}
		public Expr_identifierContext expr_identifier(int i) {
			return getRuleContext(Expr_identifierContext.class,i);
		}
		public TerminalNode IN() { return getToken(gsc_grammarParser.IN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public StmtContext stmt() {
			return getRuleContext(StmtContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public Stmt_foreachContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_foreach; }
	}

	public final Stmt_foreachContext stmt_foreach() throws RecognitionException {
		Stmt_foreachContext _localctx = new Stmt_foreachContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_stmt_foreach);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(451);
			match(FOREACH);
			setState(452);
			match(LPAREN);
			setState(453);
			expr_identifier();
			setState(456);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(454);
				match(COMMA);
				setState(455);
				expr_identifier();
				}
			}

			setState(458);
			match(IN);
			setState(459);
			expr();
			setState(460);
			match(RPAREN);
			setState(461);
			stmt();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_switchContext extends ParserRuleContext {
		public TerminalNode SWITCH() { return getToken(gsc_grammarParser.SWITCH, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Stmt_compContext stmt_comp() {
			return getRuleContext(Stmt_compContext.class,0);
		}
		public Stmt_switchContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_switch; }
	}

	public final Stmt_switchContext stmt_switch() throws RecognitionException {
		Stmt_switchContext _localctx = new Stmt_switchContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_stmt_switch);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(463);
			match(SWITCH);
			setState(464);
			match(LPAREN);
			setState(465);
			expr();
			setState(466);
			match(RPAREN);
			setState(467);
			stmt_comp();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_caseContext extends ParserRuleContext {
		public TerminalNode CASE() { return getToken(gsc_grammarParser.CASE, 0); }
		public TerminalNode COLON() { return getToken(gsc_grammarParser.COLON, 0); }
		public Expr_integerContext expr_integer() {
			return getRuleContext(Expr_integerContext.class,0);
		}
		public Expr_stringContext expr_string() {
			return getRuleContext(Expr_stringContext.class,0);
		}
		public Stmt_caseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_case; }
	}

	public final Stmt_caseContext stmt_case() throws RecognitionException {
		Stmt_caseContext _localctx = new Stmt_caseContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_stmt_case);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(469);
			match(CASE);
			setState(472);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case INTEGER:
				{
				setState(470);
				expr_integer();
				}
				break;
			case STRING:
				{
				setState(471);
				expr_string();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(474);
			match(COLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_defaultContext extends ParserRuleContext {
		public TerminalNode DEFAULT() { return getToken(gsc_grammarParser.DEFAULT, 0); }
		public TerminalNode COLON() { return getToken(gsc_grammarParser.COLON, 0); }
		public Stmt_defaultContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_default; }
	}

	public final Stmt_defaultContext stmt_default() throws RecognitionException {
		Stmt_defaultContext _localctx = new Stmt_defaultContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_stmt_default);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(476);
			match(DEFAULT);
			setState(477);
			match(COLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_breakContext extends ParserRuleContext {
		public TerminalNode BREAK() { return getToken(gsc_grammarParser.BREAK, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_breakContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_break; }
	}

	public final Stmt_breakContext stmt_break() throws RecognitionException {
		Stmt_breakContext _localctx = new Stmt_breakContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_stmt_break);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(479);
			match(BREAK);
			setState(480);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_continueContext extends ParserRuleContext {
		public TerminalNode CONTINUE() { return getToken(gsc_grammarParser.CONTINUE, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_continueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_continue; }
	}

	public final Stmt_continueContext stmt_continue() throws RecognitionException {
		Stmt_continueContext _localctx = new Stmt_continueContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_stmt_continue);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(482);
			match(CONTINUE);
			setState(483);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_returnContext extends ParserRuleContext {
		public TerminalNode RETURN() { return getToken(gsc_grammarParser.RETURN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Stmt_returnContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_return; }
	}

	public final Stmt_returnContext stmt_return() throws RecognitionException {
		Stmt_returnContext _localctx = new Stmt_returnContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_stmt_return);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(485);
			match(RETURN);
			setState(487);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(486);
				expr();
				}
			}

			setState(489);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_breakpointContext extends ParserRuleContext {
		public TerminalNode BREAKPOINT() { return getToken(gsc_grammarParser.BREAKPOINT, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Stmt_breakpointContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_breakpoint; }
	}

	public final Stmt_breakpointContext stmt_breakpoint() throws RecognitionException {
		Stmt_breakpointContext _localctx = new Stmt_breakpointContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_stmt_breakpoint);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(491);
			match(BREAKPOINT);
			setState(492);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_prof_beginContext extends ParserRuleContext {
		public TerminalNode PROFBEGIN() { return getToken(gsc_grammarParser.PROFBEGIN, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_prof_beginContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_prof_begin; }
	}

	public final Stmt_prof_beginContext stmt_prof_begin() throws RecognitionException {
		Stmt_prof_beginContext _localctx = new Stmt_prof_beginContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_stmt_prof_begin);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(494);
			match(PROFBEGIN);
			setState(495);
			match(LPAREN);
			setState(497);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(496);
				expr_arguments();
				}
			}

			setState(499);
			match(RPAREN);
			setState(500);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_prof_endContext extends ParserRuleContext {
		public TerminalNode PROFEND() { return getToken(gsc_grammarParser.PROFEND, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_prof_endContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_prof_end; }
	}

	public final Stmt_prof_endContext stmt_prof_end() throws RecognitionException {
		Stmt_prof_endContext _localctx = new Stmt_prof_endContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_stmt_prof_end);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(502);
			match(PROFEND);
			setState(503);
			match(LPAREN);
			setState(505);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(504);
				expr_arguments();
				}
			}

			setState(507);
			match(RPAREN);
			setState(508);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_assertContext extends ParserRuleContext {
		public TerminalNode ASSERT() { return getToken(gsc_grammarParser.ASSERT, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_assertContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_assert; }
	}

	public final Stmt_assertContext stmt_assert() throws RecognitionException {
		Stmt_assertContext _localctx = new Stmt_assertContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_stmt_assert);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(510);
			match(ASSERT);
			setState(511);
			match(LPAREN);
			setState(513);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(512);
				expr_arguments();
				}
			}

			setState(515);
			match(RPAREN);
			setState(516);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_assertexContext extends ParserRuleContext {
		public TerminalNode ASSERTEX() { return getToken(gsc_grammarParser.ASSERTEX, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_assertexContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_assertex; }
	}

	public final Stmt_assertexContext stmt_assertex() throws RecognitionException {
		Stmt_assertexContext _localctx = new Stmt_assertexContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_stmt_assertex);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(518);
			match(ASSERTEX);
			setState(519);
			match(LPAREN);
			setState(521);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(520);
				expr_arguments();
				}
			}

			setState(523);
			match(RPAREN);
			setState(524);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Stmt_assertmsgContext extends ParserRuleContext {
		public TerminalNode ASSERTMSG() { return getToken(gsc_grammarParser.ASSERTMSG, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode SEMICOLON() { return getToken(gsc_grammarParser.SEMICOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public Stmt_assertmsgContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt_assertmsg; }
	}

	public final Stmt_assertmsgContext stmt_assertmsg() throws RecognitionException {
		Stmt_assertmsgContext _localctx = new Stmt_assertmsgContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_stmt_assertmsg);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(526);
			match(ASSERTMSG);
			setState(527);
			match(LPAREN);
			setState(529);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
				{
				setState(528);
				expr_arguments();
				}
			}

			setState(531);
			match(RPAREN);
			setState(532);
			match(SEMICOLON);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_assignContext extends ParserRuleContext {
		public Expr_tupleContext expr_tuple() {
			return getRuleContext(Expr_tupleContext.class,0);
		}
		public TerminalNode ASSIGN() { return getToken(gsc_grammarParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public Expr_lvalueContext expr_lvalue() {
			return getRuleContext(Expr_lvalueContext.class,0);
		}
		public TerminalNode ABWOR() { return getToken(gsc_grammarParser.ABWOR, 0); }
		public TerminalNode ABWXOR() { return getToken(gsc_grammarParser.ABWXOR, 0); }
		public TerminalNode ABWAND() { return getToken(gsc_grammarParser.ABWAND, 0); }
		public TerminalNode ALSH() { return getToken(gsc_grammarParser.ALSH, 0); }
		public TerminalNode ARSH() { return getToken(gsc_grammarParser.ARSH, 0); }
		public TerminalNode AADD() { return getToken(gsc_grammarParser.AADD, 0); }
		public TerminalNode ASUB() { return getToken(gsc_grammarParser.ASUB, 0); }
		public TerminalNode AMUL() { return getToken(gsc_grammarParser.AMUL, 0); }
		public TerminalNode ADIV() { return getToken(gsc_grammarParser.ADIV, 0); }
		public TerminalNode AMOD() { return getToken(gsc_grammarParser.AMOD, 0); }
		public TerminalNode INCREMENT() { return getToken(gsc_grammarParser.INCREMENT, 0); }
		public TerminalNode DECREMENT() { return getToken(gsc_grammarParser.DECREMENT, 0); }
		public Expr_assignContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_assign; }
	}

	public final Expr_assignContext expr_assign() throws RecognitionException {
		Expr_assignContext _localctx = new Expr_assignContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_expr_assign);
		int _la;
		try {
			setState(553);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,31,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(534);
				expr_tuple();
				setState(535);
				match(ASSIGN);
				setState(536);
				expr();
				setState(537);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(539);
				expr_lvalue();
				setState(540);
				_la = _input.LA(1);
				if ( !(((((_la - 76)) & ~0x3f) == 0 && ((1L << (_la - 76)) & 2047L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(541);
				expr();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(543);
				match(INCREMENT);
				setState(544);
				expr_lvalue();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(545);
				expr_lvalue();
				setState(546);
				match(INCREMENT);
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(548);
				match(DECREMENT);
				setState(549);
				expr_lvalue();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(550);
				expr_lvalue();
				setState(551);
				match(DECREMENT);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public Expr_ternaryContext expr_ternary() {
			return getRuleContext(Expr_ternaryContext.class,0);
		}
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_expr);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(555);
			expr_ternary();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_ternaryContext extends ParserRuleContext {
		public Expr_orContext expr_or() {
			return getRuleContext(Expr_orContext.class,0);
		}
		public TerminalNode QMARK() { return getToken(gsc_grammarParser.QMARK, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode COLON() { return getToken(gsc_grammarParser.COLON, 0); }
		public Expr_ternaryContext expr_ternary() {
			return getRuleContext(Expr_ternaryContext.class,0);
		}
		public Expr_ternaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_ternary; }
	}

	public final Expr_ternaryContext expr_ternary() throws RecognitionException {
		Expr_ternaryContext _localctx = new Expr_ternaryContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_expr_ternary);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(557);
			expr_or();
			setState(563);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,32,_ctx) ) {
			case 1:
				{
				setState(558);
				match(QMARK);
				setState(559);
				expr();
				setState(560);
				match(COLON);
				setState(561);
				expr_ternary();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_orContext extends ParserRuleContext {
		public List<Expr_andContext> expr_and() {
			return getRuleContexts(Expr_andContext.class);
		}
		public Expr_andContext expr_and(int i) {
			return getRuleContext(Expr_andContext.class,i);
		}
		public List<TerminalNode> OR() { return getTokens(gsc_grammarParser.OR); }
		public TerminalNode OR(int i) {
			return getToken(gsc_grammarParser.OR, i);
		}
		public Expr_orContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_or; }
	}

	public final Expr_orContext expr_or() throws RecognitionException {
		Expr_orContext _localctx = new Expr_orContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_expr_or);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(565);
			expr_and();
			setState(570);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,33,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(566);
					match(OR);
					setState(567);
					expr_and();
					}
					} 
				}
				setState(572);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,33,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_andContext extends ParserRuleContext {
		public List<Expr_bw_orContext> expr_bw_or() {
			return getRuleContexts(Expr_bw_orContext.class);
		}
		public Expr_bw_orContext expr_bw_or(int i) {
			return getRuleContext(Expr_bw_orContext.class,i);
		}
		public List<TerminalNode> AND() { return getTokens(gsc_grammarParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(gsc_grammarParser.AND, i);
		}
		public Expr_andContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_and; }
	}

	public final Expr_andContext expr_and() throws RecognitionException {
		Expr_andContext _localctx = new Expr_andContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_expr_and);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(573);
			expr_bw_or();
			setState(578);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,34,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					{
					setState(574);
					match(AND);
					}
					setState(575);
					expr_bw_or();
					}
					} 
				}
				setState(580);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,34,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_bw_orContext extends ParserRuleContext {
		public List<Expr_bw_xorContext> expr_bw_xor() {
			return getRuleContexts(Expr_bw_xorContext.class);
		}
		public Expr_bw_xorContext expr_bw_xor(int i) {
			return getRuleContext(Expr_bw_xorContext.class,i);
		}
		public List<TerminalNode> BW_OR() { return getTokens(gsc_grammarParser.BW_OR); }
		public TerminalNode BW_OR(int i) {
			return getToken(gsc_grammarParser.BW_OR, i);
		}
		public Expr_bw_orContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_bw_or; }
	}

	public final Expr_bw_orContext expr_bw_or() throws RecognitionException {
		Expr_bw_orContext _localctx = new Expr_bw_orContext(_ctx, getState());
		enterRule(_localctx, 88, RULE_expr_bw_or);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(581);
			expr_bw_xor();
			setState(586);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,35,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					{
					setState(582);
					match(BW_OR);
					}
					setState(583);
					expr_bw_xor();
					}
					} 
				}
				setState(588);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,35,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_bw_xorContext extends ParserRuleContext {
		public List<Expr_bw_andContext> expr_bw_and() {
			return getRuleContexts(Expr_bw_andContext.class);
		}
		public Expr_bw_andContext expr_bw_and(int i) {
			return getRuleContext(Expr_bw_andContext.class,i);
		}
		public List<TerminalNode> BW_XOR() { return getTokens(gsc_grammarParser.BW_XOR); }
		public TerminalNode BW_XOR(int i) {
			return getToken(gsc_grammarParser.BW_XOR, i);
		}
		public Expr_bw_xorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_bw_xor; }
	}

	public final Expr_bw_xorContext expr_bw_xor() throws RecognitionException {
		Expr_bw_xorContext _localctx = new Expr_bw_xorContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_expr_bw_xor);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(589);
			expr_bw_and();
			setState(594);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,36,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					{
					setState(590);
					match(BW_XOR);
					}
					setState(591);
					expr_bw_and();
					}
					} 
				}
				setState(596);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,36,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_bw_andContext extends ParserRuleContext {
		public List<Expr_equalityContext> expr_equality() {
			return getRuleContexts(Expr_equalityContext.class);
		}
		public Expr_equalityContext expr_equality(int i) {
			return getRuleContext(Expr_equalityContext.class,i);
		}
		public List<TerminalNode> BW_AND() { return getTokens(gsc_grammarParser.BW_AND); }
		public TerminalNode BW_AND(int i) {
			return getToken(gsc_grammarParser.BW_AND, i);
		}
		public Expr_bw_andContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_bw_and; }
	}

	public final Expr_bw_andContext expr_bw_and() throws RecognitionException {
		Expr_bw_andContext _localctx = new Expr_bw_andContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_expr_bw_and);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(597);
			expr_equality();
			setState(602);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					{
					setState(598);
					match(BW_AND);
					}
					setState(599);
					expr_equality();
					}
					} 
				}
				setState(604);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,37,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_equalityContext extends ParserRuleContext {
		public List<Expr_relationalContext> expr_relational() {
			return getRuleContexts(Expr_relationalContext.class);
		}
		public Expr_relationalContext expr_relational(int i) {
			return getRuleContext(Expr_relationalContext.class,i);
		}
		public List<TerminalNode> EQUALITY() { return getTokens(gsc_grammarParser.EQUALITY); }
		public TerminalNode EQUALITY(int i) {
			return getToken(gsc_grammarParser.EQUALITY, i);
		}
		public List<TerminalNode> INEQUALITY() { return getTokens(gsc_grammarParser.INEQUALITY); }
		public TerminalNode INEQUALITY(int i) {
			return getToken(gsc_grammarParser.INEQUALITY, i);
		}
		public Expr_equalityContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_equality; }
	}

	public final Expr_equalityContext expr_equality() throws RecognitionException {
		Expr_equalityContext _localctx = new Expr_equalityContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_expr_equality);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(605);
			expr_relational();
			setState(610);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,38,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(606);
					_la = _input.LA(1);
					if ( !(_la==EQUALITY || _la==INEQUALITY) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(607);
					expr_relational();
					}
					} 
				}
				setState(612);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,38,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_relationalContext extends ParserRuleContext {
		public List<Expr_shiftContext> expr_shift() {
			return getRuleContexts(Expr_shiftContext.class);
		}
		public Expr_shiftContext expr_shift(int i) {
			return getRuleContext(Expr_shiftContext.class,i);
		}
		public List<TerminalNode> LESS() { return getTokens(gsc_grammarParser.LESS); }
		public TerminalNode LESS(int i) {
			return getToken(gsc_grammarParser.LESS, i);
		}
		public List<TerminalNode> LESS_EQUAL() { return getTokens(gsc_grammarParser.LESS_EQUAL); }
		public TerminalNode LESS_EQUAL(int i) {
			return getToken(gsc_grammarParser.LESS_EQUAL, i);
		}
		public List<TerminalNode> GREATER() { return getTokens(gsc_grammarParser.GREATER); }
		public TerminalNode GREATER(int i) {
			return getToken(gsc_grammarParser.GREATER, i);
		}
		public List<TerminalNode> GREATER_EQUAL() { return getTokens(gsc_grammarParser.GREATER_EQUAL); }
		public TerminalNode GREATER_EQUAL(int i) {
			return getToken(gsc_grammarParser.GREATER_EQUAL, i);
		}
		public Expr_relationalContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_relational; }
	}

	public final Expr_relationalContext expr_relational() throws RecognitionException {
		Expr_relationalContext _localctx = new Expr_relationalContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_expr_relational);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(613);
			expr_shift();
			setState(618);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,39,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(614);
					_la = _input.LA(1);
					if ( !(((((_la - 70)) & ~0x3f) == 0 && ((1L << (_la - 70)) & 15L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(615);
					expr_shift();
					}
					} 
				}
				setState(620);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,39,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_shiftContext extends ParserRuleContext {
		public List<Expr_additiveContext> expr_additive() {
			return getRuleContexts(Expr_additiveContext.class);
		}
		public Expr_additiveContext expr_additive(int i) {
			return getRuleContext(Expr_additiveContext.class,i);
		}
		public List<TerminalNode> LSHIFT() { return getTokens(gsc_grammarParser.LSHIFT); }
		public TerminalNode LSHIFT(int i) {
			return getToken(gsc_grammarParser.LSHIFT, i);
		}
		public List<TerminalNode> RSHIFT() { return getTokens(gsc_grammarParser.RSHIFT); }
		public TerminalNode RSHIFT(int i) {
			return getToken(gsc_grammarParser.RSHIFT, i);
		}
		public Expr_shiftContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_shift; }
	}

	public final Expr_shiftContext expr_shift() throws RecognitionException {
		Expr_shiftContext _localctx = new Expr_shiftContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_expr_shift);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(621);
			expr_additive();
			setState(626);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(622);
					_la = _input.LA(1);
					if ( !(_la==LSHIFT || _la==RSHIFT) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(623);
					expr_additive();
					}
					} 
				}
				setState(628);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,40,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_additiveContext extends ParserRuleContext {
		public List<Expr_multiplicativeContext> expr_multiplicative() {
			return getRuleContexts(Expr_multiplicativeContext.class);
		}
		public Expr_multiplicativeContext expr_multiplicative(int i) {
			return getRuleContext(Expr_multiplicativeContext.class,i);
		}
		public List<TerminalNode> ADD() { return getTokens(gsc_grammarParser.ADD); }
		public TerminalNode ADD(int i) {
			return getToken(gsc_grammarParser.ADD, i);
		}
		public List<TerminalNode> SUB() { return getTokens(gsc_grammarParser.SUB); }
		public TerminalNode SUB(int i) {
			return getToken(gsc_grammarParser.SUB, i);
		}
		public Expr_additiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_additive; }
	}

	public final Expr_additiveContext expr_additive() throws RecognitionException {
		Expr_additiveContext _localctx = new Expr_additiveContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_expr_additive);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(629);
			expr_multiplicative();
			setState(634);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,41,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(630);
					_la = _input.LA(1);
					if ( !(_la==ADD || _la==SUB) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(631);
					expr_multiplicative();
					}
					} 
				}
				setState(636);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,41,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_multiplicativeContext extends ParserRuleContext {
		public List<Expr_unaryContext> expr_unary() {
			return getRuleContexts(Expr_unaryContext.class);
		}
		public Expr_unaryContext expr_unary(int i) {
			return getRuleContext(Expr_unaryContext.class,i);
		}
		public List<TerminalNode> MUL() { return getTokens(gsc_grammarParser.MUL); }
		public TerminalNode MUL(int i) {
			return getToken(gsc_grammarParser.MUL, i);
		}
		public List<TerminalNode> DIV() { return getTokens(gsc_grammarParser.DIV); }
		public TerminalNode DIV(int i) {
			return getToken(gsc_grammarParser.DIV, i);
		}
		public List<TerminalNode> MOD() { return getTokens(gsc_grammarParser.MOD); }
		public TerminalNode MOD(int i) {
			return getToken(gsc_grammarParser.MOD, i);
		}
		public Expr_multiplicativeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_multiplicative; }
	}

	public final Expr_multiplicativeContext expr_multiplicative() throws RecognitionException {
		Expr_multiplicativeContext _localctx = new Expr_multiplicativeContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_expr_multiplicative);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(637);
			expr_unary();
			setState(642);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,42,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(638);
					_la = _input.LA(1);
					if ( !(((((_la - 92)) & ~0x3f) == 0 && ((1L << (_la - 92)) & 7L) != 0)) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(639);
					expr_unary();
					}
					} 
				}
				setState(644);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,42,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_unaryContext extends ParserRuleContext {
		public Expr_complementContext expr_complement() {
			return getRuleContext(Expr_complementContext.class,0);
		}
		public Expr_notContext expr_not() {
			return getRuleContext(Expr_notContext.class,0);
		}
		public Expr_negateContext expr_negate() {
			return getRuleContext(Expr_negateContext.class,0);
		}
		public Expr_animationContext expr_animation() {
			return getRuleContext(Expr_animationContext.class,0);
		}
		public Expr_primaryContext expr_primary() {
			return getRuleContext(Expr_primaryContext.class,0);
		}
		public Expr_unaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_unary; }
	}

	public final Expr_unaryContext expr_unary() throws RecognitionException {
		Expr_unaryContext _localctx = new Expr_unaryContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_expr_unary);
		try {
			setState(650);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case COMPLEMENT:
				enterOuterAlt(_localctx, 1);
				{
				setState(645);
				expr_complement();
				}
				break;
			case NOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(646);
				expr_not();
				}
				break;
			case SUB:
				enterOuterAlt(_localctx, 3);
				{
				setState(647);
				expr_negate();
				}
				break;
			case MOD:
				enterOuterAlt(_localctx, 4);
				{
				setState(648);
				expr_animation();
				}
				break;
			case ANIMTREE:
			case THREAD:
			case CHILDTHREAD:
			case THISTHREAD:
			case CALL:
			case TRUE:
			case FALSE:
			case UNDEFINED:
			case SIZE:
			case GAME:
			case SELF:
			case ANIM:
			case LEVEL:
			case ISDEFINED:
			case ISTRUE:
			case LPAREN:
			case LBRACKET:
			case DOUBLECOLON:
			case FLOAT:
			case INTEGER:
			case STRING:
			case ISTRING:
			case HSTRING:
			case IDENTIFIER:
			case PATH:
			case GETNEXTARRAYKEY:
			case GETFIRSTARRAYKEY:
			case GETDVARCOLORALPHA:
			case GETDVARCOLORBLUE:
			case GETDVARCOLORGREEN:
			case GETDVARCOLORRED:
			case GETDVARVECTOR:
			case GETDVARFLOAT:
			case GETDVARINT:
			case GETDVAR:
			case GETTIME:
			case ABS:
			case VECTORTOANGLES:
			case ANGLECLAMP180:
			case ANGLESTOFORWARD:
			case ANGLESTORIGHT:
			case ANGLESTOUP:
			case VECTORSCALE:
				enterOuterAlt(_localctx, 5);
				{
				setState(649);
				expr_primary();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_complementContext extends ParserRuleContext {
		public TerminalNode COMPLEMENT() { return getToken(gsc_grammarParser.COMPLEMENT, 0); }
		public Expr_unaryContext expr_unary() {
			return getRuleContext(Expr_unaryContext.class,0);
		}
		public Expr_complementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_complement; }
	}

	public final Expr_complementContext expr_complement() throws RecognitionException {
		Expr_complementContext _localctx = new Expr_complementContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_expr_complement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(652);
			match(COMPLEMENT);
			setState(653);
			expr_unary();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_notContext extends ParserRuleContext {
		public TerminalNode NOT() { return getToken(gsc_grammarParser.NOT, 0); }
		public Expr_unaryContext expr_unary() {
			return getRuleContext(Expr_unaryContext.class,0);
		}
		public Expr_notContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_not; }
	}

	public final Expr_notContext expr_not() throws RecognitionException {
		Expr_notContext _localctx = new Expr_notContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_expr_not);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(655);
			match(NOT);
			setState(656);
			expr_unary();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_negateContext extends ParserRuleContext {
		public TerminalNode SUB() { return getToken(gsc_grammarParser.SUB, 0); }
		public Expr_floatContext expr_float() {
			return getRuleContext(Expr_floatContext.class,0);
		}
		public Expr_integerContext expr_integer() {
			return getRuleContext(Expr_integerContext.class,0);
		}
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_parenContext expr_paren() {
			return getRuleContext(Expr_parenContext.class,0);
		}
		public Expr_object_subexprContext expr_object_subexpr() {
			return getRuleContext(Expr_object_subexprContext.class,0);
		}
		public Expr_negateContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_negate; }
	}

	public final Expr_negateContext expr_negate() throws RecognitionException {
		Expr_negateContext _localctx = new Expr_negateContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_expr_negate);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(658);
			match(SUB);
			setState(664);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,44,_ctx) ) {
			case 1:
				{
				setState(659);
				expr_float();
				}
				break;
			case 2:
				{
				setState(660);
				expr_integer();
				}
				break;
			case 3:
				{
				setState(661);
				expr_identifier();
				}
				break;
			case 4:
				{
				setState(662);
				expr_paren();
				}
				break;
			case 5:
				{
				setState(663);
				expr_object_subexpr();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_animationContext extends ParserRuleContext {
		public TerminalNode MOD() { return getToken(gsc_grammarParser.MOD, 0); }
		public TerminalNode IDENTIFIER() { return getToken(gsc_grammarParser.IDENTIFIER, 0); }
		public Expr_animationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_animation; }
	}

	public final Expr_animationContext expr_animation() throws RecognitionException {
		Expr_animationContext _localctx = new Expr_animationContext(_ctx, getState());
		enterRule(_localctx, 112, RULE_expr_animation);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(666);
			match(MOD);
			setState(667);
			match(IDENTIFIER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_primaryContext extends ParserRuleContext {
		public Expr_callContext expr_call() {
			return getRuleContext(Expr_callContext.class,0);
		}
		public Expr_call_optimizedContext expr_call_optimized() {
			return getRuleContext(Expr_call_optimizedContext.class,0);
		}
		public Expr_call_optimized_vector_arrayContext expr_call_optimized_vector_array() {
			return getRuleContext(Expr_call_optimized_vector_arrayContext.class,0);
		}
		public Expr_referenceContext expr_reference() {
			return getRuleContext(Expr_referenceContext.class,0);
		}
		public Expr_isdefinedContext expr_isdefined() {
			return getRuleContext(Expr_isdefinedContext.class,0);
		}
		public Expr_istrueContext expr_istrue() {
			return getRuleContext(Expr_istrueContext.class,0);
		}
		public Expr_add_arrayContext expr_add_array() {
			return getRuleContext(Expr_add_arrayContext.class,0);
		}
		public Expr_object_subexprContext expr_object_subexpr() {
			return getRuleContext(Expr_object_subexprContext.class,0);
		}
		public Expr_sizeContext expr_size() {
			return getRuleContext(Expr_sizeContext.class,0);
		}
		public Expr_parenContext expr_paren() {
			return getRuleContext(Expr_parenContext.class,0);
		}
		public Expr_thisthreadContext expr_thisthread() {
			return getRuleContext(Expr_thisthreadContext.class,0);
		}
		public Expr_empty_arrayContext expr_empty_array() {
			return getRuleContext(Expr_empty_arrayContext.class,0);
		}
		public Expr_undefinedContext expr_undefined() {
			return getRuleContext(Expr_undefinedContext.class,0);
		}
		public Expr_gameContext expr_game() {
			return getRuleContext(Expr_gameContext.class,0);
		}
		public Expr_selfContext expr_self() {
			return getRuleContext(Expr_selfContext.class,0);
		}
		public Expr_animContext expr_anim() {
			return getRuleContext(Expr_animContext.class,0);
		}
		public Expr_levelContext expr_level() {
			return getRuleContext(Expr_levelContext.class,0);
		}
		public Expr_animtreeContext expr_animtree() {
			return getRuleContext(Expr_animtreeContext.class,0);
		}
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_hstringContext expr_hstring() {
			return getRuleContext(Expr_hstringContext.class,0);
		}
		public Expr_istringContext expr_istring() {
			return getRuleContext(Expr_istringContext.class,0);
		}
		public Expr_stringContext expr_string() {
			return getRuleContext(Expr_stringContext.class,0);
		}
		public Expr_vectorContext expr_vector() {
			return getRuleContext(Expr_vectorContext.class,0);
		}
		public Expr_floatContext expr_float() {
			return getRuleContext(Expr_floatContext.class,0);
		}
		public Expr_integerContext expr_integer() {
			return getRuleContext(Expr_integerContext.class,0);
		}
		public Expr_falseContext expr_false() {
			return getRuleContext(Expr_falseContext.class,0);
		}
		public Expr_trueContext expr_true() {
			return getRuleContext(Expr_trueContext.class,0);
		}
		public Expr_primaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_primary; }
	}

	public final Expr_primaryContext expr_primary() throws RecognitionException {
		Expr_primaryContext _localctx = new Expr_primaryContext(_ctx, getState());
		enterRule(_localctx, 114, RULE_expr_primary);
		try {
			setState(708);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,45,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(669);
				expr_call();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(670);
				expr_call_optimized();
				setState(671);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(673);
				expr_call_optimized_vector_array();
				setState(674);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(676);
				expr_reference();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(677);
				expr_isdefined();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(678);
				expr_istrue();
				setState(679);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(681);
				expr_add_array();
				setState(682);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(684);
				expr_object_subexpr();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(685);
				expr_size();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(686);
				expr_paren();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(687);
				expr_thisthread();
				setState(688);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(690);
				expr_empty_array();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(691);
				expr_undefined();
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(692);
				expr_game();
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(693);
				expr_self();
				}
				break;
			case 16:
				enterOuterAlt(_localctx, 16);
				{
				setState(694);
				expr_anim();
				}
				break;
			case 17:
				enterOuterAlt(_localctx, 17);
				{
				setState(695);
				expr_level();
				}
				break;
			case 18:
				enterOuterAlt(_localctx, 18);
				{
				setState(696);
				expr_animtree();
				}
				break;
			case 19:
				enterOuterAlt(_localctx, 19);
				{
				setState(697);
				expr_identifier();
				}
				break;
			case 20:
				enterOuterAlt(_localctx, 20);
				{
				setState(698);
				expr_hstring();
				setState(699);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			case 21:
				enterOuterAlt(_localctx, 21);
				{
				setState(701);
				expr_istring();
				}
				break;
			case 22:
				enterOuterAlt(_localctx, 22);
				{
				setState(702);
				expr_string();
				}
				break;
			case 23:
				enterOuterAlt(_localctx, 23);
				{
				setState(703);
				expr_vector();
				}
				break;
			case 24:
				enterOuterAlt(_localctx, 24);
				{
				setState(704);
				expr_float();
				}
				break;
			case 25:
				enterOuterAlt(_localctx, 25);
				{
				setState(705);
				expr_integer();
				}
				break;
			case 26:
				enterOuterAlt(_localctx, 26);
				{
				setState(706);
				expr_false();
				}
				break;
			case 27:
				enterOuterAlt(_localctx, 27);
				{
				setState(707);
				expr_true();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_callContext extends ParserRuleContext {
		public Expr_functionContext expr_function() {
			return getRuleContext(Expr_functionContext.class,0);
		}
		public Expr_pointerContext expr_pointer() {
			return getRuleContext(Expr_pointerContext.class,0);
		}
		public Expr_callContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_call; }
	}

	public final Expr_callContext expr_call() throws RecognitionException {
		Expr_callContext _localctx = new Expr_callContext(_ctx, getState());
		enterRule(_localctx, 116, RULE_expr_call);
		try {
			setState(712);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,46,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(710);
				expr_function();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(711);
				expr_pointer();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_methodContext extends ParserRuleContext {
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public Expr_functionContext expr_function() {
			return getRuleContext(Expr_functionContext.class,0);
		}
		public Expr_pointerContext expr_pointer() {
			return getRuleContext(Expr_pointerContext.class,0);
		}
		public Expr_methodContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_method; }
	}

	public final Expr_methodContext expr_method() throws RecognitionException {
		Expr_methodContext _localctx = new Expr_methodContext(_ctx, getState());
		enterRule(_localctx, 118, RULE_expr_method);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(714);
			expr_object();
			setState(717);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,47,_ctx) ) {
			case 1:
				{
				setState(715);
				expr_function();
				}
				break;
			case 2:
				{
				setState(716);
				expr_pointer();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_functionContext extends ParserRuleContext {
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode THREAD() { return getToken(gsc_grammarParser.THREAD, 0); }
		public Expr_pathContext expr_path() {
			return getRuleContext(Expr_pathContext.class,0);
		}
		public TerminalNode DOUBLECOLON() { return getToken(gsc_grammarParser.DOUBLECOLON, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public TerminalNode CHILDTHREAD() { return getToken(gsc_grammarParser.CHILDTHREAD, 0); }
		public Expr_functionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_function; }
	}

	public final Expr_functionContext expr_function() throws RecognitionException {
		Expr_functionContext _localctx = new Expr_functionContext(_ctx, getState());
		enterRule(_localctx, 120, RULE_expr_function);
		int _la;
		try {
			setState(750);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,54,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(720);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==THREAD) {
					{
					setState(719);
					match(THREAD);
					}
				}

				setState(725);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,49,_ctx) ) {
				case 1:
					{
					setState(722);
					expr_path();
					setState(723);
					match(DOUBLECOLON);
					}
					break;
				}
				setState(727);
				expr_identifier();
				setState(728);
				match(LPAREN);
				setState(730);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
					{
					setState(729);
					expr_arguments();
					}
				}

				setState(732);
				match(RPAREN);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(735);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==CHILDTHREAD) {
					{
					setState(734);
					match(CHILDTHREAD);
					}
				}

				setState(740);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,52,_ctx) ) {
				case 1:
					{
					setState(737);
					expr_path();
					setState(738);
					match(DOUBLECOLON);
					}
					break;
				}
				setState(742);
				expr_identifier();
				setState(743);
				match(LPAREN);
				setState(745);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
					{
					setState(744);
					expr_arguments();
					}
				}

				setState(747);
				match(RPAREN);
				setState(748);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_pointerContext extends ParserRuleContext {
		public List<TerminalNode> LBRACKET() { return getTokens(gsc_grammarParser.LBRACKET); }
		public TerminalNode LBRACKET(int i) {
			return getToken(gsc_grammarParser.LBRACKET, i);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public List<TerminalNode> RBRACKET() { return getTokens(gsc_grammarParser.RBRACKET); }
		public TerminalNode RBRACKET(int i) {
			return getToken(gsc_grammarParser.RBRACKET, i);
		}
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode THREAD() { return getToken(gsc_grammarParser.THREAD, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public TerminalNode CHILDTHREAD() { return getToken(gsc_grammarParser.CHILDTHREAD, 0); }
		public TerminalNode CALL() { return getToken(gsc_grammarParser.CALL, 0); }
		public Expr_pointerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_pointer; }
	}

	public final Expr_pointerContext expr_pointer() throws RecognitionException {
		Expr_pointerContext _localctx = new Expr_pointerContext(_ctx, getState());
		enterRule(_localctx, 122, RULE_expr_pointer);
		int _la;
		try {
			setState(781);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,59,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(753);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==THREAD) {
					{
					setState(752);
					match(THREAD);
					}
				}

				setState(755);
				match(LBRACKET);
				setState(756);
				match(LBRACKET);
				setState(757);
				expr();
				setState(758);
				match(RBRACKET);
				setState(759);
				match(RBRACKET);
				setState(760);
				match(LPAREN);
				setState(762);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
					{
					setState(761);
					expr_arguments();
					}
				}

				setState(764);
				match(RPAREN);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(767);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==CHILDTHREAD || _la==CALL) {
					{
					setState(766);
					_la = _input.LA(1);
					if ( !(_la==CHILDTHREAD || _la==CALL) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					}
				}

				setState(769);
				match(LBRACKET);
				setState(770);
				match(LBRACKET);
				setState(771);
				expr();
				setState(772);
				match(RBRACKET);
				setState(773);
				match(RBRACKET);
				setState(774);
				match(LPAREN);
				setState(776);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 293296908552634496L) != 0) || ((((_la - 74)) & ~0x3f) == 0 && ((1L << (_la - 74)) & 36028659847528451L) != 0)) {
					{
					setState(775);
					expr_arguments();
					}
				}

				setState(778);
				match(RPAREN);
				setState(779);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_call_optimizedContext extends ParserRuleContext {
		public TerminalNode GETFIRSTARRAYKEY() { return getToken(gsc_grammarParser.GETFIRSTARRAYKEY, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode GETNEXTARRAYKEY() { return getToken(gsc_grammarParser.GETNEXTARRAYKEY, 0); }
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public TerminalNode GETDVAR() { return getToken(gsc_grammarParser.GETDVAR, 0); }
		public TerminalNode GETDVARINT() { return getToken(gsc_grammarParser.GETDVARINT, 0); }
		public TerminalNode GETDVARFLOAT() { return getToken(gsc_grammarParser.GETDVARFLOAT, 0); }
		public TerminalNode GETDVARCOLORRED() { return getToken(gsc_grammarParser.GETDVARCOLORRED, 0); }
		public TerminalNode GETDVARCOLORGREEN() { return getToken(gsc_grammarParser.GETDVARCOLORGREEN, 0); }
		public TerminalNode GETDVARCOLORBLUE() { return getToken(gsc_grammarParser.GETDVARCOLORBLUE, 0); }
		public TerminalNode GETDVARCOLORALPHA() { return getToken(gsc_grammarParser.GETDVARCOLORALPHA, 0); }
		public TerminalNode GETTIME() { return getToken(gsc_grammarParser.GETTIME, 0); }
		public TerminalNode ABS() { return getToken(gsc_grammarParser.ABS, 0); }
		public Expr_call_optimized_vectorContext expr_call_optimized_vector() {
			return getRuleContext(Expr_call_optimized_vectorContext.class,0);
		}
		public Expr_call_optimizedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_call_optimized; }
	}

	public final Expr_call_optimizedContext expr_call_optimized() throws RecognitionException {
		Expr_call_optimizedContext _localctx = new Expr_call_optimizedContext(_ctx, getState());
		enterRule(_localctx, 124, RULE_expr_call_optimized);
		try {
			setState(841);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case GETFIRSTARRAYKEY:
				enterOuterAlt(_localctx, 1);
				{
				setState(783);
				match(GETFIRSTARRAYKEY);
				setState(784);
				match(LPAREN);
				setState(785);
				expr();
				setState(786);
				match(RPAREN);
				}
				break;
			case GETNEXTARRAYKEY:
				enterOuterAlt(_localctx, 2);
				{
				setState(788);
				match(GETNEXTARRAYKEY);
				setState(789);
				match(LPAREN);
				setState(790);
				expr();
				setState(791);
				match(COMMA);
				setState(792);
				expr();
				setState(793);
				match(RPAREN);
				}
				break;
			case GETDVAR:
				enterOuterAlt(_localctx, 3);
				{
				setState(795);
				match(GETDVAR);
				setState(796);
				match(LPAREN);
				setState(797);
				expr();
				setState(798);
				match(COMMA);
				setState(799);
				expr();
				setState(800);
				match(RPAREN);
				}
				break;
			case GETDVARINT:
				enterOuterAlt(_localctx, 4);
				{
				setState(802);
				match(GETDVARINT);
				setState(803);
				match(LPAREN);
				setState(804);
				expr();
				setState(805);
				match(RPAREN);
				}
				break;
			case GETDVARFLOAT:
				enterOuterAlt(_localctx, 5);
				{
				setState(807);
				match(GETDVARFLOAT);
				setState(808);
				match(LPAREN);
				setState(809);
				expr();
				setState(810);
				match(RPAREN);
				}
				break;
			case GETDVARCOLORRED:
				enterOuterAlt(_localctx, 6);
				{
				setState(812);
				match(GETDVARCOLORRED);
				setState(813);
				match(LPAREN);
				setState(814);
				expr();
				setState(815);
				match(RPAREN);
				}
				break;
			case GETDVARCOLORGREEN:
				enterOuterAlt(_localctx, 7);
				{
				setState(817);
				match(GETDVARCOLORGREEN);
				setState(818);
				match(LPAREN);
				setState(819);
				expr();
				setState(820);
				match(RPAREN);
				}
				break;
			case GETDVARCOLORBLUE:
				enterOuterAlt(_localctx, 8);
				{
				setState(822);
				match(GETDVARCOLORBLUE);
				setState(823);
				match(LPAREN);
				setState(824);
				expr();
				setState(825);
				match(RPAREN);
				}
				break;
			case GETDVARCOLORALPHA:
				enterOuterAlt(_localctx, 9);
				{
				setState(827);
				match(GETDVARCOLORALPHA);
				setState(828);
				match(LPAREN);
				setState(829);
				expr();
				setState(830);
				match(RPAREN);
				}
				break;
			case GETTIME:
				enterOuterAlt(_localctx, 10);
				{
				setState(832);
				match(GETTIME);
				setState(833);
				match(LPAREN);
				setState(834);
				match(RPAREN);
				}
				break;
			case ABS:
				enterOuterAlt(_localctx, 11);
				{
				setState(835);
				match(ABS);
				setState(836);
				match(LPAREN);
				setState(837);
				expr();
				setState(838);
				match(RPAREN);
				}
				break;
			case GETDVARVECTOR:
			case VECTORTOANGLES:
			case ANGLECLAMP180:
			case ANGLESTOFORWARD:
			case ANGLESTORIGHT:
			case ANGLESTOUP:
			case VECTORSCALE:
				enterOuterAlt(_localctx, 12);
				{
				setState(840);
				expr_call_optimized_vector();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_call_optimized_vectorContext extends ParserRuleContext {
		public TerminalNode GETDVARVECTOR() { return getToken(gsc_grammarParser.GETDVARVECTOR, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public TerminalNode VECTORTOANGLES() { return getToken(gsc_grammarParser.VECTORTOANGLES, 0); }
		public TerminalNode ANGLECLAMP180() { return getToken(gsc_grammarParser.ANGLECLAMP180, 0); }
		public TerminalNode ANGLESTOFORWARD() { return getToken(gsc_grammarParser.ANGLESTOFORWARD, 0); }
		public TerminalNode ANGLESTORIGHT() { return getToken(gsc_grammarParser.ANGLESTORIGHT, 0); }
		public TerminalNode ANGLESTOUP() { return getToken(gsc_grammarParser.ANGLESTOUP, 0); }
		public TerminalNode VECTORSCALE() { return getToken(gsc_grammarParser.VECTORSCALE, 0); }
		public TerminalNode COMMA() { return getToken(gsc_grammarParser.COMMA, 0); }
		public Expr_call_optimized_vectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_call_optimized_vector; }
	}

	public final Expr_call_optimized_vectorContext expr_call_optimized_vector() throws RecognitionException {
		Expr_call_optimized_vectorContext _localctx = new Expr_call_optimized_vectorContext(_ctx, getState());
		enterRule(_localctx, 126, RULE_expr_call_optimized_vector);
		try {
			setState(880);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case GETDVARVECTOR:
				enterOuterAlt(_localctx, 1);
				{
				setState(843);
				match(GETDVARVECTOR);
				setState(844);
				match(LPAREN);
				setState(845);
				expr();
				setState(846);
				match(RPAREN);
				}
				break;
			case VECTORTOANGLES:
				enterOuterAlt(_localctx, 2);
				{
				setState(848);
				match(VECTORTOANGLES);
				setState(849);
				match(LPAREN);
				setState(850);
				expr();
				setState(851);
				match(RPAREN);
				}
				break;
			case ANGLECLAMP180:
				enterOuterAlt(_localctx, 3);
				{
				setState(853);
				match(ANGLECLAMP180);
				setState(854);
				match(LPAREN);
				setState(855);
				expr();
				setState(856);
				match(RPAREN);
				}
				break;
			case ANGLESTOFORWARD:
				enterOuterAlt(_localctx, 4);
				{
				setState(858);
				match(ANGLESTOFORWARD);
				setState(859);
				match(LPAREN);
				setState(860);
				expr();
				setState(861);
				match(RPAREN);
				}
				break;
			case ANGLESTORIGHT:
				enterOuterAlt(_localctx, 5);
				{
				setState(863);
				match(ANGLESTORIGHT);
				setState(864);
				match(LPAREN);
				setState(865);
				expr();
				setState(866);
				match(RPAREN);
				}
				break;
			case ANGLESTOUP:
				enterOuterAlt(_localctx, 6);
				{
				setState(868);
				match(ANGLESTOUP);
				setState(869);
				match(LPAREN);
				setState(870);
				expr();
				setState(871);
				match(RPAREN);
				}
				break;
			case VECTORSCALE:
				enterOuterAlt(_localctx, 7);
				{
				setState(873);
				match(VECTORSCALE);
				setState(874);
				match(LPAREN);
				setState(875);
				expr();
				setState(876);
				match(COMMA);
				setState(877);
				expr();
				setState(878);
				match(RPAREN);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_call_optimized_vector_arrayContext extends ParserRuleContext {
		public Expr_call_optimized_vectorContext expr_call_optimized_vector() {
			return getRuleContext(Expr_call_optimized_vectorContext.class,0);
		}
		public Expr_arrayContext expr_array() {
			return getRuleContext(Expr_arrayContext.class,0);
		}
		public Expr_call_optimized_vector_arrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_call_optimized_vector_array; }
	}

	public final Expr_call_optimized_vector_arrayContext expr_call_optimized_vector_array() throws RecognitionException {
		Expr_call_optimized_vector_arrayContext _localctx = new Expr_call_optimized_vector_arrayContext(_ctx, getState());
		enterRule(_localctx, 128, RULE_expr_call_optimized_vector_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(882);
			expr_call_optimized_vector();
			setState(883);
			expr_array();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_isdefinedContext extends ParserRuleContext {
		public TerminalNode ISDEFINED() { return getToken(gsc_grammarParser.ISDEFINED, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Expr_isdefinedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_isdefined; }
	}

	public final Expr_isdefinedContext expr_isdefined() throws RecognitionException {
		Expr_isdefinedContext _localctx = new Expr_isdefinedContext(_ctx, getState());
		enterRule(_localctx, 130, RULE_expr_isdefined);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(885);
			match(ISDEFINED);
			setState(886);
			match(LPAREN);
			setState(887);
			expr();
			setState(888);
			match(RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_istrueContext extends ParserRuleContext {
		public TerminalNode ISTRUE() { return getToken(gsc_grammarParser.ISTRUE, 0); }
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Expr_istrueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_istrue; }
	}

	public final Expr_istrueContext expr_istrue() throws RecognitionException {
		Expr_istrueContext _localctx = new Expr_istrueContext(_ctx, getState());
		enterRule(_localctx, 132, RULE_expr_istrue);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(890);
			match(ISTRUE);
			setState(891);
			match(LPAREN);
			setState(892);
			expr();
			setState(893);
			match(RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_referenceContext extends ParserRuleContext {
		public TerminalNode DOUBLECOLON() { return getToken(gsc_grammarParser.DOUBLECOLON, 0); }
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_pathContext expr_path() {
			return getRuleContext(Expr_pathContext.class,0);
		}
		public Expr_referenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_reference; }
	}

	public final Expr_referenceContext expr_reference() throws RecognitionException {
		Expr_referenceContext _localctx = new Expr_referenceContext(_ctx, getState());
		enterRule(_localctx, 134, RULE_expr_reference);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(896);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER || _la==PATH) {
				{
				setState(895);
				expr_path();
				}
			}

			setState(898);
			match(DOUBLECOLON);
			setState(899);
			expr_identifier();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_parametersContext extends ParserRuleContext {
		public List<Expr_identifierContext> expr_identifier() {
			return getRuleContexts(Expr_identifierContext.class);
		}
		public Expr_identifierContext expr_identifier(int i) {
			return getRuleContext(Expr_identifierContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(gsc_grammarParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(gsc_grammarParser.COMMA, i);
		}
		public Expr_parameters_defaultContext expr_parameters_default() {
			return getRuleContext(Expr_parameters_defaultContext.class,0);
		}
		public Expr_parametersContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_parameters; }
	}

	public final Expr_parametersContext expr_parameters() throws RecognitionException {
		Expr_parametersContext _localctx = new Expr_parametersContext(_ctx, getState());
		enterRule(_localctx, 136, RULE_expr_parameters);
		try {
			int _alt;
			setState(914);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,64,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(901);
				expr_identifier();
				setState(906);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,63,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(902);
						match(COMMA);
						setState(903);
						expr_identifier();
						}
						} 
					}
					setState(908);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,63,_ctx);
				}
				setState(909);
				if (!( version == 1 )) throw new FailedPredicateException(this, " version == 1 ");
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(911);
				expr_parameters_default();
				setState(912);
				if (!( version == 2 )) throw new FailedPredicateException(this, " version == 2 ");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_parameters_defaultContext extends ParserRuleContext {
		public List<Expr_identifierContext> expr_identifier() {
			return getRuleContexts(Expr_identifierContext.class);
		}
		public Expr_identifierContext expr_identifier(int i) {
			return getRuleContext(Expr_identifierContext.class,i);
		}
		public List<TerminalNode> ASSIGN() { return getTokens(gsc_grammarParser.ASSIGN); }
		public TerminalNode ASSIGN(int i) {
			return getToken(gsc_grammarParser.ASSIGN, i);
		}
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(gsc_grammarParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(gsc_grammarParser.COMMA, i);
		}
		public Expr_parameters_defaultContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_parameters_default; }
	}

	public final Expr_parameters_defaultContext expr_parameters_default() throws RecognitionException {
		Expr_parameters_defaultContext _localctx = new Expr_parameters_defaultContext(_ctx, getState());
		enterRule(_localctx, 138, RULE_expr_parameters_default);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(916);
			expr_identifier();
			setState(919);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,65,_ctx) ) {
			case 1:
				{
				setState(917);
				match(ASSIGN);
				setState(918);
				expr();
				}
				break;
			}
			setState(929);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,67,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(921);
					match(COMMA);
					setState(922);
					expr_identifier();
					setState(925);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,66,_ctx) ) {
					case 1:
						{
						setState(923);
						match(ASSIGN);
						setState(924);
						expr();
						}
						break;
					}
					}
					} 
				}
				setState(931);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,67,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_argumentsContext extends ParserRuleContext {
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(gsc_grammarParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(gsc_grammarParser.COMMA, i);
		}
		public Expr_argumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_arguments; }
	}

	public final Expr_argumentsContext expr_arguments() throws RecognitionException {
		Expr_argumentsContext _localctx = new Expr_argumentsContext(_ctx, getState());
		enterRule(_localctx, 140, RULE_expr_arguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(932);
			expr();
			setState(937);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(933);
				match(COMMA);
				setState(934);
				expr();
				}
				}
				setState(939);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_tupleContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public List<Expr_lvalueContext> expr_lvalue() {
			return getRuleContexts(Expr_lvalueContext.class);
		}
		public Expr_lvalueContext expr_lvalue(int i) {
			return getRuleContext(Expr_lvalueContext.class,i);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public List<TerminalNode> COMMA() { return getTokens(gsc_grammarParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(gsc_grammarParser.COMMA, i);
		}
		public Expr_tupleContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_tuple; }
	}

	public final Expr_tupleContext expr_tuple() throws RecognitionException {
		Expr_tupleContext _localctx = new Expr_tupleContext(_ctx, getState());
		enterRule(_localctx, 142, RULE_expr_tuple);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(940);
			match(LBRACKET);
			setState(941);
			expr_lvalue();
			setState(946);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COMMA) {
				{
				{
				setState(942);
				match(COMMA);
				setState(943);
				expr_lvalue();
				}
				}
				setState(948);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(949);
			match(RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_add_arrayContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public Expr_argumentsContext expr_arguments() {
			return getRuleContext(Expr_argumentsContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public Expr_add_arrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_add_array; }
	}

	public final Expr_add_arrayContext expr_add_array() throws RecognitionException {
		Expr_add_arrayContext _localctx = new Expr_add_arrayContext(_ctx, getState());
		enterRule(_localctx, 144, RULE_expr_add_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(951);
			match(LBRACKET);
			setState(952);
			expr_arguments();
			setState(953);
			match(RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_parenContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Expr_parenContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_paren; }
	}

	public final Expr_parenContext expr_paren() throws RecognitionException {
		Expr_parenContext _localctx = new Expr_parenContext(_ctx, getState());
		enterRule(_localctx, 146, RULE_expr_paren);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(955);
			match(LPAREN);
			setState(956);
			expr();
			setState(957);
			match(RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_lvalueContext extends ParserRuleContext {
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_lvalue_arrayContext expr_lvalue_array() {
			return getRuleContext(Expr_lvalue_arrayContext.class,0);
		}
		public Expr_lvalue_fieldContext expr_lvalue_field() {
			return getRuleContext(Expr_lvalue_fieldContext.class,0);
		}
		public Expr_lvalueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_lvalue; }
	}

	public final Expr_lvalueContext expr_lvalue() throws RecognitionException {
		Expr_lvalueContext _localctx = new Expr_lvalueContext(_ctx, getState());
		enterRule(_localctx, 148, RULE_expr_lvalue);
		try {
			setState(962);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,70,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(959);
				expr_identifier();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(960);
				expr_lvalue_array();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(961);
				expr_lvalue_field();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_lvalue_arrayContext extends ParserRuleContext {
		public Expr_object_subexpr_no_callContext expr_object_subexpr_no_call() {
			return getRuleContext(Expr_object_subexpr_no_callContext.class,0);
		}
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public Expr_lvalue_arrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_lvalue_array; }
	}

	public final Expr_lvalue_arrayContext expr_lvalue_array() throws RecognitionException {
		Expr_lvalue_arrayContext _localctx = new Expr_lvalue_arrayContext(_ctx, getState());
		enterRule(_localctx, 150, RULE_expr_lvalue_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(964);
			expr_object_subexpr_no_call();
			setState(965);
			match(LBRACKET);
			setState(966);
			expr();
			setState(967);
			match(RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_lvalue_fieldContext extends ParserRuleContext {
		public Expr_object_subexprContext expr_object_subexpr() {
			return getRuleContext(Expr_object_subexprContext.class,0);
		}
		public TerminalNode DOT() { return getToken(gsc_grammarParser.DOT, 0); }
		public Expr_identifier_fieldContext expr_identifier_field() {
			return getRuleContext(Expr_identifier_fieldContext.class,0);
		}
		public Expr_lvalue_fieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_lvalue_field; }
	}

	public final Expr_lvalue_fieldContext expr_lvalue_field() throws RecognitionException {
		Expr_lvalue_fieldContext _localctx = new Expr_lvalue_fieldContext(_ctx, getState());
		enterRule(_localctx, 152, RULE_expr_lvalue_field);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(969);
			expr_object_subexpr();
			setState(970);
			match(DOT);
			setState(971);
			expr_identifier_field();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_objectContext extends ParserRuleContext {
		public Expr_callContext expr_call() {
			return getRuleContext(Expr_callContext.class,0);
		}
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_gameContext expr_game() {
			return getRuleContext(Expr_gameContext.class,0);
		}
		public Expr_selfContext expr_self() {
			return getRuleContext(Expr_selfContext.class,0);
		}
		public Expr_animContext expr_anim() {
			return getRuleContext(Expr_animContext.class,0);
		}
		public Expr_levelContext expr_level() {
			return getRuleContext(Expr_levelContext.class,0);
		}
		public Expr_object_subexprContext expr_object_subexpr() {
			return getRuleContext(Expr_object_subexprContext.class,0);
		}
		public Expr_objectContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_object; }
	}

	public final Expr_objectContext expr_object() throws RecognitionException {
		Expr_objectContext _localctx = new Expr_objectContext(_ctx, getState());
		enterRule(_localctx, 154, RULE_expr_object);
		try {
			setState(980);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,71,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(973);
				expr_call();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(974);
				expr_identifier();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(975);
				expr_game();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(976);
				expr_self();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(977);
				expr_anim();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(978);
				expr_level();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(979);
				expr_object_subexpr();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_object_subexprContext extends ParserRuleContext {
		public Expr_callContext expr_call() {
			return getRuleContext(Expr_callContext.class,0);
		}
		public List<Expr_array_or_field_or_callContext> expr_array_or_field_or_call() {
			return getRuleContexts(Expr_array_or_field_or_callContext.class);
		}
		public Expr_array_or_field_or_callContext expr_array_or_field_or_call(int i) {
			return getRuleContext(Expr_array_or_field_or_callContext.class,i);
		}
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public Expr_gameContext expr_game() {
			return getRuleContext(Expr_gameContext.class,0);
		}
		public List<Expr_arrayContext> expr_array() {
			return getRuleContexts(Expr_arrayContext.class);
		}
		public Expr_arrayContext expr_array(int i) {
			return getRuleContext(Expr_arrayContext.class,i);
		}
		public Expr_selfContext expr_self() {
			return getRuleContext(Expr_selfContext.class,0);
		}
		public Expr_animContext expr_anim() {
			return getRuleContext(Expr_animContext.class,0);
		}
		public List<Expr_fieldContext> expr_field() {
			return getRuleContexts(Expr_fieldContext.class);
		}
		public Expr_fieldContext expr_field(int i) {
			return getRuleContext(Expr_fieldContext.class,i);
		}
		public Expr_levelContext expr_level() {
			return getRuleContext(Expr_levelContext.class,0);
		}
		public Expr_object_subexprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_object_subexpr; }
	}

	public final Expr_object_subexprContext expr_object_subexpr() throws RecognitionException {
		Expr_object_subexprContext _localctx = new Expr_object_subexprContext(_ctx, getState());
		enterRule(_localctx, 156, RULE_expr_object_subexpr);
		try {
			int _alt;
			setState(1038);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,81,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(982);
				expr_call();
				setState(986);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,72,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(983);
						expr_array_or_field_or_call();
						}
						} 
					}
					setState(988);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,72,_ctx);
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(989);
				expr_identifier();
				setState(993);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,73,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(990);
						expr_array_or_field_or_call();
						}
						} 
					}
					setState(995);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,73,_ctx);
				}
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(996);
				expr_game();
				setState(998); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(997);
						expr_array();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1000); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,74,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1005);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,75,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1002);
						expr_array_or_field_or_call();
						}
						} 
					}
					setState(1007);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,75,_ctx);
				}
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(1008);
				expr_self();
				setState(1010); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1009);
						expr_array_or_field_or_call();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1012); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,76,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(1014);
				expr_anim();
				setState(1016); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1015);
						expr_field();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1018); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,77,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1023);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,78,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1020);
						expr_array_or_field_or_call();
						}
						} 
					}
					setState(1025);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,78,_ctx);
				}
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(1026);
				expr_level();
				setState(1028); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1027);
						expr_field();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1030); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,79,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1035);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,80,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1032);
						expr_array_or_field_or_call();
						}
						} 
					}
					setState(1037);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,80,_ctx);
				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_object_subexpr_no_callContext extends ParserRuleContext {
		public Expr_identifierContext expr_identifier() {
			return getRuleContext(Expr_identifierContext.class,0);
		}
		public List<Expr_array_or_fieldContext> expr_array_or_field() {
			return getRuleContexts(Expr_array_or_fieldContext.class);
		}
		public Expr_array_or_fieldContext expr_array_or_field(int i) {
			return getRuleContext(Expr_array_or_fieldContext.class,i);
		}
		public Expr_gameContext expr_game() {
			return getRuleContext(Expr_gameContext.class,0);
		}
		public List<Expr_arrayContext> expr_array() {
			return getRuleContexts(Expr_arrayContext.class);
		}
		public Expr_arrayContext expr_array(int i) {
			return getRuleContext(Expr_arrayContext.class,i);
		}
		public Expr_selfContext expr_self() {
			return getRuleContext(Expr_selfContext.class,0);
		}
		public Expr_animContext expr_anim() {
			return getRuleContext(Expr_animContext.class,0);
		}
		public List<Expr_fieldContext> expr_field() {
			return getRuleContexts(Expr_fieldContext.class);
		}
		public Expr_fieldContext expr_field(int i) {
			return getRuleContext(Expr_fieldContext.class,i);
		}
		public Expr_levelContext expr_level() {
			return getRuleContext(Expr_levelContext.class,0);
		}
		public Expr_object_subexpr_no_callContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_object_subexpr_no_call; }
	}

	public final Expr_object_subexpr_no_callContext expr_object_subexpr_no_call() throws RecognitionException {
		Expr_object_subexpr_no_callContext _localctx = new Expr_object_subexpr_no_callContext(_ctx, getState());
		enterRule(_localctx, 158, RULE_expr_object_subexpr_no_call);
		try {
			int _alt;
			setState(1089);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case SIZE:
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(1040);
				expr_identifier();
				setState(1044);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,82,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1041);
						expr_array_or_field();
						}
						} 
					}
					setState(1046);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,82,_ctx);
				}
				}
				break;
			case GAME:
				enterOuterAlt(_localctx, 2);
				{
				setState(1047);
				expr_game();
				setState(1049); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1048);
						expr_array();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1051); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,83,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1056);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,84,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1053);
						expr_array_or_field();
						}
						} 
					}
					setState(1058);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,84,_ctx);
				}
				}
				break;
			case SELF:
				enterOuterAlt(_localctx, 3);
				{
				setState(1059);
				expr_self();
				setState(1061); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1060);
						expr_array_or_field();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1063); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,85,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				}
				break;
			case ANIM:
				enterOuterAlt(_localctx, 4);
				{
				setState(1065);
				expr_anim();
				setState(1067); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1066);
						expr_field();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1069); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,86,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1074);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,87,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1071);
						expr_array_or_field();
						}
						} 
					}
					setState(1076);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,87,_ctx);
				}
				}
				break;
			case LEVEL:
				enterOuterAlt(_localctx, 5);
				{
				setState(1077);
				expr_level();
				setState(1079); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(1078);
						expr_field();
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(1081); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,88,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				setState(1086);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,89,_ctx);
				while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
					if ( _alt==1 ) {
						{
						{
						setState(1083);
						expr_array_or_field();
						}
						} 
					}
					setState(1088);
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,89,_ctx);
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_array_or_field_or_callContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public TerminalNode DOT() { return getToken(gsc_grammarParser.DOT, 0); }
		public Expr_identifier_fieldContext expr_identifier_field() {
			return getRuleContext(Expr_identifier_fieldContext.class,0);
		}
		public Expr_callContext expr_call() {
			return getRuleContext(Expr_callContext.class,0);
		}
		public Expr_array_or_field_or_callContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_array_or_field_or_call; }
	}

	public final Expr_array_or_field_or_callContext expr_array_or_field_or_call() throws RecognitionException {
		Expr_array_or_field_or_callContext _localctx = new Expr_array_or_field_or_callContext(_ctx, getState());
		enterRule(_localctx, 160, RULE_expr_array_or_field_or_call);
		try {
			setState(1098);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,91,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(1091);
				match(LBRACKET);
				setState(1092);
				expr();
				setState(1093);
				match(RBRACKET);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(1095);
				match(DOT);
				setState(1096);
				expr_identifier_field();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(1097);
				expr_call();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_array_or_fieldContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public TerminalNode DOT() { return getToken(gsc_grammarParser.DOT, 0); }
		public Expr_identifier_fieldContext expr_identifier_field() {
			return getRuleContext(Expr_identifier_fieldContext.class,0);
		}
		public Expr_array_or_fieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_array_or_field; }
	}

	public final Expr_array_or_fieldContext expr_array_or_field() throws RecognitionException {
		Expr_array_or_fieldContext _localctx = new Expr_array_or_fieldContext(_ctx, getState());
		enterRule(_localctx, 162, RULE_expr_array_or_field);
		try {
			setState(1106);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case LBRACKET:
				enterOuterAlt(_localctx, 1);
				{
				setState(1100);
				match(LBRACKET);
				setState(1101);
				expr();
				setState(1102);
				match(RBRACKET);
				}
				break;
			case DOT:
				enterOuterAlt(_localctx, 2);
				{
				setState(1104);
				match(DOT);
				setState(1105);
				expr_identifier_field();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_arrayContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public Expr_arrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_array; }
	}

	public final Expr_arrayContext expr_array() throws RecognitionException {
		Expr_arrayContext _localctx = new Expr_arrayContext(_ctx, getState());
		enterRule(_localctx, 164, RULE_expr_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1108);
			match(LBRACKET);
			setState(1109);
			expr();
			setState(1110);
			match(RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_fieldContext extends ParserRuleContext {
		public TerminalNode DOT() { return getToken(gsc_grammarParser.DOT, 0); }
		public Expr_identifier_fieldContext expr_identifier_field() {
			return getRuleContext(Expr_identifier_fieldContext.class,0);
		}
		public Expr_fieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_field; }
	}

	public final Expr_fieldContext expr_field() throws RecognitionException {
		Expr_fieldContext _localctx = new Expr_fieldContext(_ctx, getState());
		enterRule(_localctx, 166, RULE_expr_field);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1112);
			match(DOT);
			setState(1113);
			expr_identifier_field();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_sizeContext extends ParserRuleContext {
		public TerminalNode DOT() { return getToken(gsc_grammarParser.DOT, 0); }
		public TerminalNode SIZE() { return getToken(gsc_grammarParser.SIZE, 0); }
		public Expr_objectContext expr_object() {
			return getRuleContext(Expr_objectContext.class,0);
		}
		public Expr_stringContext expr_string() {
			return getRuleContext(Expr_stringContext.class,0);
		}
		public Expr_sizeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_size; }
	}

	public final Expr_sizeContext expr_size() throws RecognitionException {
		Expr_sizeContext _localctx = new Expr_sizeContext(_ctx, getState());
		enterRule(_localctx, 168, RULE_expr_size);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1117);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case THREAD:
			case CHILDTHREAD:
			case CALL:
			case SIZE:
			case GAME:
			case SELF:
			case ANIM:
			case LEVEL:
			case LBRACKET:
			case IDENTIFIER:
			case PATH:
				{
				setState(1115);
				expr_object();
				}
				break;
			case STRING:
				{
				setState(1116);
				expr_string();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			setState(1119);
			match(DOT);
			setState(1120);
			match(SIZE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_thisthreadContext extends ParserRuleContext {
		public TerminalNode THISTHREAD() { return getToken(gsc_grammarParser.THISTHREAD, 0); }
		public Expr_thisthreadContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_thisthread; }
	}

	public final Expr_thisthreadContext expr_thisthread() throws RecognitionException {
		Expr_thisthreadContext _localctx = new Expr_thisthreadContext(_ctx, getState());
		enterRule(_localctx, 170, RULE_expr_thisthread);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1122);
			match(THISTHREAD);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_empty_arrayContext extends ParserRuleContext {
		public TerminalNode LBRACKET() { return getToken(gsc_grammarParser.LBRACKET, 0); }
		public TerminalNode RBRACKET() { return getToken(gsc_grammarParser.RBRACKET, 0); }
		public Expr_empty_arrayContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_empty_array; }
	}

	public final Expr_empty_arrayContext expr_empty_array() throws RecognitionException {
		Expr_empty_arrayContext _localctx = new Expr_empty_arrayContext(_ctx, getState());
		enterRule(_localctx, 172, RULE_expr_empty_array);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1124);
			match(LBRACKET);
			setState(1125);
			match(RBRACKET);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_undefinedContext extends ParserRuleContext {
		public TerminalNode UNDEFINED() { return getToken(gsc_grammarParser.UNDEFINED, 0); }
		public Expr_undefinedContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_undefined; }
	}

	public final Expr_undefinedContext expr_undefined() throws RecognitionException {
		Expr_undefinedContext _localctx = new Expr_undefinedContext(_ctx, getState());
		enterRule(_localctx, 174, RULE_expr_undefined);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1127);
			match(UNDEFINED);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_gameContext extends ParserRuleContext {
		public TerminalNode GAME() { return getToken(gsc_grammarParser.GAME, 0); }
		public Expr_gameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_game; }
	}

	public final Expr_gameContext expr_game() throws RecognitionException {
		Expr_gameContext _localctx = new Expr_gameContext(_ctx, getState());
		enterRule(_localctx, 176, RULE_expr_game);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1129);
			match(GAME);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_selfContext extends ParserRuleContext {
		public TerminalNode SELF() { return getToken(gsc_grammarParser.SELF, 0); }
		public Expr_selfContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_self; }
	}

	public final Expr_selfContext expr_self() throws RecognitionException {
		Expr_selfContext _localctx = new Expr_selfContext(_ctx, getState());
		enterRule(_localctx, 178, RULE_expr_self);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1131);
			match(SELF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_animContext extends ParserRuleContext {
		public TerminalNode ANIM() { return getToken(gsc_grammarParser.ANIM, 0); }
		public Expr_animContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_anim; }
	}

	public final Expr_animContext expr_anim() throws RecognitionException {
		Expr_animContext _localctx = new Expr_animContext(_ctx, getState());
		enterRule(_localctx, 180, RULE_expr_anim);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1133);
			match(ANIM);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_levelContext extends ParserRuleContext {
		public TerminalNode LEVEL() { return getToken(gsc_grammarParser.LEVEL, 0); }
		public Expr_levelContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_level; }
	}

	public final Expr_levelContext expr_level() throws RecognitionException {
		Expr_levelContext _localctx = new Expr_levelContext(_ctx, getState());
		enterRule(_localctx, 182, RULE_expr_level);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1135);
			match(LEVEL);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_animtreeContext extends ParserRuleContext {
		public TerminalNode ANIMTREE() { return getToken(gsc_grammarParser.ANIMTREE, 0); }
		public Expr_animtreeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_animtree; }
	}

	public final Expr_animtreeContext expr_animtree() throws RecognitionException {
		Expr_animtreeContext _localctx = new Expr_animtreeContext(_ctx, getState());
		enterRule(_localctx, 184, RULE_expr_animtree);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1137);
			match(ANIMTREE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_vectorContext extends ParserRuleContext {
		public TerminalNode LPAREN() { return getToken(gsc_grammarParser.LPAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(gsc_grammarParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(gsc_grammarParser.COMMA, i);
		}
		public TerminalNode RPAREN() { return getToken(gsc_grammarParser.RPAREN, 0); }
		public Expr_vectorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_vector; }
	}

	public final Expr_vectorContext expr_vector() throws RecognitionException {
		Expr_vectorContext _localctx = new Expr_vectorContext(_ctx, getState());
		enterRule(_localctx, 186, RULE_expr_vector);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1139);
			match(LPAREN);
			setState(1140);
			expr();
			setState(1141);
			match(COMMA);
			setState(1142);
			expr();
			setState(1143);
			match(COMMA);
			setState(1144);
			expr();
			setState(1145);
			match(RPAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_pathContext extends ParserRuleContext {
		public TerminalNode PATH() { return getToken(gsc_grammarParser.PATH, 0); }
		public TerminalNode IDENTIFIER() { return getToken(gsc_grammarParser.IDENTIFIER, 0); }
		public Expr_pathContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_path; }
	}

	public final Expr_pathContext expr_path() throws RecognitionException {
		Expr_pathContext _localctx = new Expr_pathContext(_ctx, getState());
		enterRule(_localctx, 188, RULE_expr_path);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1147);
			_la = _input.LA(1);
			if ( !(_la==IDENTIFIER || _la==PATH) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_identifier_fieldContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(gsc_grammarParser.IDENTIFIER, 0); }
		public TerminalNode WAIT() { return getToken(gsc_grammarParser.WAIT, 0); }
		public Expr_identifier_fieldContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_identifier_field; }
	}

	public final Expr_identifier_fieldContext expr_identifier_field() throws RecognitionException {
		Expr_identifier_fieldContext _localctx = new Expr_identifier_fieldContext(_ctx, getState());
		enterRule(_localctx, 190, RULE_expr_identifier_field);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1149);
			_la = _input.LA(1);
			if ( !(_la==WAIT || _la==IDENTIFIER) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_identifierContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(gsc_grammarParser.IDENTIFIER, 0); }
		public TerminalNode SIZE() { return getToken(gsc_grammarParser.SIZE, 0); }
		public Expr_identifierContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_identifier; }
	}

	public final Expr_identifierContext expr_identifier() throws RecognitionException {
		Expr_identifierContext _localctx = new Expr_identifierContext(_ctx, getState());
		enterRule(_localctx, 192, RULE_expr_identifier);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1151);
			_la = _input.LA(1);
			if ( !(_la==SIZE || _la==IDENTIFIER) ) {
			_errHandler.recoverInline(this);
			}
			else {
				if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
				_errHandler.reportMatch(this);
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_hstringContext extends ParserRuleContext {
		public TerminalNode HSTRING() { return getToken(gsc_grammarParser.HSTRING, 0); }
		public Expr_hstringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_hstring; }
	}

	public final Expr_hstringContext expr_hstring() throws RecognitionException {
		Expr_hstringContext _localctx = new Expr_hstringContext(_ctx, getState());
		enterRule(_localctx, 194, RULE_expr_hstring);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1153);
			match(HSTRING);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_istringContext extends ParserRuleContext {
		public TerminalNode ISTRING() { return getToken(gsc_grammarParser.ISTRING, 0); }
		public Expr_istringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_istring; }
	}

	public final Expr_istringContext expr_istring() throws RecognitionException {
		Expr_istringContext _localctx = new Expr_istringContext(_ctx, getState());
		enterRule(_localctx, 196, RULE_expr_istring);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1155);
			match(ISTRING);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_stringContext extends ParserRuleContext {
		public TerminalNode STRING() { return getToken(gsc_grammarParser.STRING, 0); }
		public Expr_stringContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_string; }
	}

	public final Expr_stringContext expr_string() throws RecognitionException {
		Expr_stringContext _localctx = new Expr_stringContext(_ctx, getState());
		enterRule(_localctx, 198, RULE_expr_string);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1157);
			match(STRING);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_floatContext extends ParserRuleContext {
		public TerminalNode FLOAT() { return getToken(gsc_grammarParser.FLOAT, 0); }
		public Expr_floatContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_float; }
	}

	public final Expr_floatContext expr_float() throws RecognitionException {
		Expr_floatContext _localctx = new Expr_floatContext(_ctx, getState());
		enterRule(_localctx, 200, RULE_expr_float);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1159);
			match(FLOAT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_integerContext extends ParserRuleContext {
		public TerminalNode INTEGER() { return getToken(gsc_grammarParser.INTEGER, 0); }
		public Expr_integerContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_integer; }
	}

	public final Expr_integerContext expr_integer() throws RecognitionException {
		Expr_integerContext _localctx = new Expr_integerContext(_ctx, getState());
		enterRule(_localctx, 202, RULE_expr_integer);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1161);
			match(INTEGER);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_falseContext extends ParserRuleContext {
		public TerminalNode FALSE() { return getToken(gsc_grammarParser.FALSE, 0); }
		public Expr_falseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_false; }
	}

	public final Expr_falseContext expr_false() throws RecognitionException {
		Expr_falseContext _localctx = new Expr_falseContext(_ctx, getState());
		enterRule(_localctx, 204, RULE_expr_false);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1163);
			match(FALSE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class Expr_trueContext extends ParserRuleContext {
		public TerminalNode TRUE() { return getToken(gsc_grammarParser.TRUE, 0); }
		public Expr_trueContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr_true; }
	}

	public final Expr_trueContext expr_true() throws RecognitionException {
		Expr_trueContext _localctx = new Expr_trueContext(_ctx, getState());
		enterRule(_localctx, 206, RULE_expr_true);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(1165);
			match(TRUE);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 3:
			return declaration_sempred((DeclarationContext)_localctx, predIndex);
		case 6:
			return decl_function_sempred((Decl_functionContext)_localctx, predIndex);
		case 7:
			return stmt_sempred((StmtContext)_localctx, predIndex);
		case 39:
			return expr_assign_sempred((Expr_assignContext)_localctx, predIndex);
		case 57:
			return expr_primary_sempred((Expr_primaryContext)_localctx, predIndex);
		case 60:
			return expr_function_sempred((Expr_functionContext)_localctx, predIndex);
		case 61:
			return expr_pointer_sempred((Expr_pointerContext)_localctx, predIndex);
		case 68:
			return expr_parameters_sempred((Expr_parametersContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean declaration_sempred(DeclarationContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return  version == 1 ;
		}
		return true;
	}
	private boolean decl_function_sempred(Decl_functionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return  version == 1 ;
		case 2:
			return  version == 2 ;
		}
		return true;
	}
	private boolean stmt_sempred(StmtContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return  version == 2 ;
		case 4:
			return  version == 1 ;
		case 5:
			return  version == 2 ;
		case 6:
			return  version == 1 ;
		case 7:
			return  version == 1 ;
		case 8:
			return  version == 1 ;
		case 9:
			return  version == 1 ;
		}
		return true;
	}
	private boolean expr_assign_sempred(Expr_assignContext _localctx, int predIndex) {
		switch (predIndex) {
		case 10:
			return  version == 1 ;
		}
		return true;
	}
	private boolean expr_primary_sempred(Expr_primaryContext _localctx, int predIndex) {
		switch (predIndex) {
		case 11:
			return  version == 2 ;
		case 12:
			return  version == 2 ;
		case 13:
			return  version == 1 ;
		case 14:
			return  version == 1 ;
		case 15:
			return  version == 1 ;
		case 16:
			return  version == 2 ;
		}
		return true;
	}
	private boolean expr_function_sempred(Expr_functionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 17:
			return  version == 1 ;
		}
		return true;
	}
	private boolean expr_pointer_sempred(Expr_pointerContext _localctx, int predIndex) {
		switch (predIndex) {
		case 18:
			return  version == 1 ;
		}
		return true;
	}
	private boolean expr_parameters_sempred(Expr_parametersContext _localctx, int predIndex) {
		switch (predIndex) {
		case 19:
			return  version == 1 ;
		case 20:
			return  version == 2 ;
		}
		return true;
	}

	public static final String _serializedATN =
		"\u0004\u0001\u0080\u0490\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001"+
		"\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004"+
		"\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007"+
		"\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b"+
		"\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007"+
		"\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007"+
		"\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007"+
		"\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002\u0018\u0007"+
		"\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002\u001b\u0007"+
		"\u001b\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002\u001e\u0007"+
		"\u001e\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007!\u0002\"\u0007"+
		"\"\u0002#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007&\u0002\'\u0007"+
		"\'\u0002(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007+\u0002,\u0007"+
		",\u0002-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u00070\u00021\u0007"+
		"1\u00022\u00072\u00023\u00073\u00024\u00074\u00025\u00075\u00026\u0007"+
		"6\u00027\u00077\u00028\u00078\u00029\u00079\u0002:\u0007:\u0002;\u0007"+
		";\u0002<\u0007<\u0002=\u0007=\u0002>\u0007>\u0002?\u0007?\u0002@\u0007"+
		"@\u0002A\u0007A\u0002B\u0007B\u0002C\u0007C\u0002D\u0007D\u0002E\u0007"+
		"E\u0002F\u0007F\u0002G\u0007G\u0002H\u0007H\u0002I\u0007I\u0002J\u0007"+
		"J\u0002K\u0007K\u0002L\u0007L\u0002M\u0007M\u0002N\u0007N\u0002O\u0007"+
		"O\u0002P\u0007P\u0002Q\u0007Q\u0002R\u0007R\u0002S\u0007S\u0002T\u0007"+
		"T\u0002U\u0007U\u0002V\u0007V\u0002W\u0007W\u0002X\u0007X\u0002Y\u0007"+
		"Y\u0002Z\u0007Z\u0002[\u0007[\u0002\\\u0007\\\u0002]\u0007]\u0002^\u0007"+
		"^\u0002_\u0007_\u0002`\u0007`\u0002a\u0007a\u0002b\u0007b\u0002c\u0007"+
		"c\u0002d\u0007d\u0002e\u0007e\u0002f\u0007f\u0002g\u0007g\u0001\u0000"+
		"\u0001\u0000\u0001\u0000\u0001\u0000\u0005\u0000\u00d5\b\u0000\n\u0000"+
		"\f\u0000\u00d8\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0003\u0003\u00eb\b\u0003\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006"+
		"\u00fb\b\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0003\u0006\u0102\b\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006"+
		"\u0107\b\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0003\u0006"+
		"\u010d\b\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0003\u0007\u0139\b\u0007\u0001\b\u0004\b\u013c\b\b\u000b"+
		"\b\f\b\u013d\u0001\t\u0001\t\u0004\t\u0142\b\t\u000b\t\f\t\u0143\u0001"+
		"\n\u0001\n\u0003\n\u0148\b\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0003"+
		"\u000b\u014e\b\u000b\u0001\u000b\u0001\u000b\u0001\f\u0001\f\u0001\f\u0003"+
		"\f\u0155\b\f\u0001\f\u0001\f\u0001\r\u0001\r\u0001\r\u0001\r\u0001\r\u0001"+
		"\r\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0001\u000e\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0001\u000f\u0003\u000f\u016c\b\u000f\u0001\u000f\u0001\u000f\u0001\u000f"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011"+
		"\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0011\u0003\u0011\u017b\b\u0011"+
		"\u0001\u0011\u0001\u0011\u0001\u0011\u0001\u0012\u0001\u0012\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0001\u0012\u0003\u0012\u0186\b\u0012\u0001\u0012"+
		"\u0001\u0012\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0003\u0013"+
		"\u018e\b\u0013\u0001\u0013\u0001\u0013\u0001\u0014\u0001\u0014\u0001\u0014"+
		"\u0003\u0014\u0195\b\u0014\u0001\u0014\u0001\u0014\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016"+
		"\u0001\u0016\u0001\u0016\u0001\u0016\u0003\u0016\u01a4\b\u0016\u0001\u0017"+
		"\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0001\u0018"+
		"\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018\u0001\u0018"+
		"\u0001\u0018\u0001\u0019\u0001\u0019\u0001\u0019\u0003\u0019\u01b7\b\u0019"+
		"\u0001\u0019\u0001\u0019\u0003\u0019\u01bb\b\u0019\u0001\u0019\u0001\u0019"+
		"\u0003\u0019\u01bf\b\u0019\u0001\u0019\u0001\u0019\u0001\u0019\u0001\u001a"+
		"\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0003\u001a\u01c9\b\u001a"+
		"\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001a\u0001\u001b"+
		"\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001c"+
		"\u0001\u001c\u0001\u001c\u0003\u001c\u01d9\b\u001c\u0001\u001c\u0001\u001c"+
		"\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001e\u0001\u001e\u0001\u001e"+
		"\u0001\u001f\u0001\u001f\u0001\u001f\u0001 \u0001 \u0003 \u01e8\b \u0001"+
		" \u0001 \u0001!\u0001!\u0001!\u0001\"\u0001\"\u0001\"\u0003\"\u01f2\b"+
		"\"\u0001\"\u0001\"\u0001\"\u0001#\u0001#\u0001#\u0003#\u01fa\b#\u0001"+
		"#\u0001#\u0001#\u0001$\u0001$\u0001$\u0003$\u0202\b$\u0001$\u0001$\u0001"+
		"$\u0001%\u0001%\u0001%\u0003%\u020a\b%\u0001%\u0001%\u0001%\u0001&\u0001"+
		"&\u0001&\u0003&\u0212\b&\u0001&\u0001&\u0001&\u0001\'\u0001\'\u0001\'"+
		"\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001"+
		"\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'\u0003\'\u022a"+
		"\b\'\u0001(\u0001(\u0001)\u0001)\u0001)\u0001)\u0001)\u0001)\u0003)\u0234"+
		"\b)\u0001*\u0001*\u0001*\u0005*\u0239\b*\n*\f*\u023c\t*\u0001+\u0001+"+
		"\u0001+\u0005+\u0241\b+\n+\f+\u0244\t+\u0001,\u0001,\u0001,\u0005,\u0249"+
		"\b,\n,\f,\u024c\t,\u0001-\u0001-\u0001-\u0005-\u0251\b-\n-\f-\u0254\t"+
		"-\u0001.\u0001.\u0001.\u0005.\u0259\b.\n.\f.\u025c\t.\u0001/\u0001/\u0001"+
		"/\u0005/\u0261\b/\n/\f/\u0264\t/\u00010\u00010\u00010\u00050\u0269\b0"+
		"\n0\f0\u026c\t0\u00011\u00011\u00011\u00051\u0271\b1\n1\f1\u0274\t1\u0001"+
		"2\u00012\u00012\u00052\u0279\b2\n2\f2\u027c\t2\u00013\u00013\u00013\u0005"+
		"3\u0281\b3\n3\f3\u0284\t3\u00014\u00014\u00014\u00014\u00014\u00034\u028b"+
		"\b4\u00015\u00015\u00015\u00016\u00016\u00016\u00017\u00017\u00017\u0001"+
		"7\u00017\u00017\u00037\u0299\b7\u00018\u00018\u00018\u00019\u00019\u0001"+
		"9\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u0001"+
		"9\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u0001"+
		"9\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u00019\u0001"+
		"9\u00019\u00019\u00019\u00019\u00019\u00019\u00039\u02c5\b9\u0001:\u0001"+
		":\u0003:\u02c9\b:\u0001;\u0001;\u0001;\u0003;\u02ce\b;\u0001<\u0003<\u02d1"+
		"\b<\u0001<\u0001<\u0001<\u0003<\u02d6\b<\u0001<\u0001<\u0001<\u0003<\u02db"+
		"\b<\u0001<\u0001<\u0001<\u0003<\u02e0\b<\u0001<\u0001<\u0001<\u0003<\u02e5"+
		"\b<\u0001<\u0001<\u0001<\u0003<\u02ea\b<\u0001<\u0001<\u0001<\u0003<\u02ef"+
		"\b<\u0001=\u0003=\u02f2\b=\u0001=\u0001=\u0001=\u0001=\u0001=\u0001=\u0001"+
		"=\u0003=\u02fb\b=\u0001=\u0001=\u0001=\u0003=\u0300\b=\u0001=\u0001=\u0001"+
		"=\u0001=\u0001=\u0001=\u0001=\u0003=\u0309\b=\u0001=\u0001=\u0001=\u0003"+
		"=\u030e\b=\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001"+
		">\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001"+
		">\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001"+
		">\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001"+
		">\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001"+
		">\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0001>\u0003"+
		">\u034a\b>\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001"+
		"?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001"+
		"?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001"+
		"?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0001?\u0003?\u0371"+
		"\b?\u0001@\u0001@\u0001@\u0001A\u0001A\u0001A\u0001A\u0001A\u0001B\u0001"+
		"B\u0001B\u0001B\u0001B\u0001C\u0003C\u0381\bC\u0001C\u0001C\u0001C\u0001"+
		"D\u0001D\u0001D\u0005D\u0389\bD\nD\fD\u038c\tD\u0001D\u0001D\u0001D\u0001"+
		"D\u0001D\u0003D\u0393\bD\u0001E\u0001E\u0001E\u0003E\u0398\bE\u0001E\u0001"+
		"E\u0001E\u0001E\u0003E\u039e\bE\u0005E\u03a0\bE\nE\fE\u03a3\tE\u0001F"+
		"\u0001F\u0001F\u0005F\u03a8\bF\nF\fF\u03ab\tF\u0001G\u0001G\u0001G\u0001"+
		"G\u0005G\u03b1\bG\nG\fG\u03b4\tG\u0001G\u0001G\u0001H\u0001H\u0001H\u0001"+
		"H\u0001I\u0001I\u0001I\u0001I\u0001J\u0001J\u0001J\u0003J\u03c3\bJ\u0001"+
		"K\u0001K\u0001K\u0001K\u0001K\u0001L\u0001L\u0001L\u0001L\u0001M\u0001"+
		"M\u0001M\u0001M\u0001M\u0001M\u0001M\u0003M\u03d5\bM\u0001N\u0001N\u0005"+
		"N\u03d9\bN\nN\fN\u03dc\tN\u0001N\u0001N\u0005N\u03e0\bN\nN\fN\u03e3\t"+
		"N\u0001N\u0001N\u0004N\u03e7\bN\u000bN\fN\u03e8\u0001N\u0005N\u03ec\b"+
		"N\nN\fN\u03ef\tN\u0001N\u0001N\u0004N\u03f3\bN\u000bN\fN\u03f4\u0001N"+
		"\u0001N\u0004N\u03f9\bN\u000bN\fN\u03fa\u0001N\u0005N\u03fe\bN\nN\fN\u0401"+
		"\tN\u0001N\u0001N\u0004N\u0405\bN\u000bN\fN\u0406\u0001N\u0005N\u040a"+
		"\bN\nN\fN\u040d\tN\u0003N\u040f\bN\u0001O\u0001O\u0005O\u0413\bO\nO\f"+
		"O\u0416\tO\u0001O\u0001O\u0004O\u041a\bO\u000bO\fO\u041b\u0001O\u0005"+
		"O\u041f\bO\nO\fO\u0422\tO\u0001O\u0001O\u0004O\u0426\bO\u000bO\fO\u0427"+
		"\u0001O\u0001O\u0004O\u042c\bO\u000bO\fO\u042d\u0001O\u0005O\u0431\bO"+
		"\nO\fO\u0434\tO\u0001O\u0001O\u0004O\u0438\bO\u000bO\fO\u0439\u0001O\u0005"+
		"O\u043d\bO\nO\fO\u0440\tO\u0003O\u0442\bO\u0001P\u0001P\u0001P\u0001P"+
		"\u0001P\u0001P\u0001P\u0003P\u044b\bP\u0001Q\u0001Q\u0001Q\u0001Q\u0001"+
		"Q\u0001Q\u0003Q\u0453\bQ\u0001R\u0001R\u0001R\u0001R\u0001S\u0001S\u0001"+
		"S\u0001T\u0001T\u0003T\u045e\bT\u0001T\u0001T\u0001T\u0001U\u0001U\u0001"+
		"V\u0001V\u0001V\u0001W\u0001W\u0001X\u0001X\u0001Y\u0001Y\u0001Z\u0001"+
		"Z\u0001[\u0001[\u0001\\\u0001\\\u0001]\u0001]\u0001]\u0001]\u0001]\u0001"+
		"]\u0001]\u0001]\u0001^\u0001^\u0001_\u0001_\u0001`\u0001`\u0001a\u0001"+
		"a\u0001b\u0001b\u0001c\u0001c\u0001d\u0001d\u0001e\u0001e\u0001f\u0001"+
		"f\u0001g\u0001g\u0001g\u0000\u0000h\u0000\u0002\u0004\u0006\b\n\f\u000e"+
		"\u0010\u0012\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.02468:<>@BDF"+
		"HJLNPRTVXZ\\^`bdfhjlnprtvxz|~\u0080\u0082\u0084\u0086\u0088\u008a\u008c"+
		"\u008e\u0090\u0092\u0094\u0096\u0098\u009a\u009c\u009e\u00a0\u00a2\u00a4"+
		"\u00a6\u00a8\u00aa\u00ac\u00ae\u00b0\u00b2\u00b4\u00b6\u00b8\u00ba\u00bc"+
		"\u00be\u00c0\u00c2\u00c4\u00c6\u00c8\u00ca\u00cc\u00ce\u0000\u000b\u0001"+
		"\u0000jl\u0001\u0000LV\u0001\u0000DE\u0001\u0000FI\u0001\u0000@A\u0001"+
		"\u0000Z[\u0001\u0000\\^\u0002\u0000##%%\u0001\u0000de\u0002\u0000\n\n"+
		"dd\u0002\u0000))dd\u04e6\u0000\u00d6\u0001\u0000\u0000\u0000\u0002\u00db"+
		"\u0001\u0000\u0000\u0000\u0004\u00df\u0001\u0000\u0000\u0000\u0006\u00ea"+
		"\u0001\u0000\u0000\u0000\b\u00ec\u0001\u0000\u0000\u0000\n\u00f2\u0001"+
		"\u0000\u0000\u0000\f\u010c\u0001\u0000\u0000\u0000\u000e\u0138\u0001\u0000"+
		"\u0000\u0000\u0010\u013b\u0001\u0000\u0000\u0000\u0012\u0141\u0001\u0000"+
		"\u0000\u0000\u0014\u0145\u0001\u0000\u0000\u0000\u0016\u014b\u0001\u0000"+
		"\u0000\u0000\u0018\u0154\u0001\u0000\u0000\u0000\u001a\u0158\u0001\u0000"+
		"\u0000\u0000\u001c\u015e\u0001\u0000\u0000\u0000\u001e\u0165\u0001\u0000"+
		"\u0000\u0000 \u0170\u0001\u0000\u0000\u0000\"\u0174\u0001\u0000\u0000"+
		"\u0000$\u017f\u0001\u0000\u0000\u0000&\u018a\u0001\u0000\u0000\u0000("+
		"\u0191\u0001\u0000\u0000\u0000*\u0198\u0001\u0000\u0000\u0000,\u019c\u0001"+
		"\u0000\u0000\u0000.\u01a5\u0001\u0000\u0000\u00000\u01ab\u0001\u0000\u0000"+
		"\u00002\u01b3\u0001\u0000\u0000\u00004\u01c3\u0001\u0000\u0000\u00006"+
		"\u01cf\u0001\u0000\u0000\u00008\u01d5\u0001\u0000\u0000\u0000:\u01dc\u0001"+
		"\u0000\u0000\u0000<\u01df\u0001\u0000\u0000\u0000>\u01e2\u0001\u0000\u0000"+
		"\u0000@\u01e5\u0001\u0000\u0000\u0000B\u01eb\u0001\u0000\u0000\u0000D"+
		"\u01ee\u0001\u0000\u0000\u0000F\u01f6\u0001\u0000\u0000\u0000H\u01fe\u0001"+
		"\u0000\u0000\u0000J\u0206\u0001\u0000\u0000\u0000L\u020e\u0001\u0000\u0000"+
		"\u0000N\u0229\u0001\u0000\u0000\u0000P\u022b\u0001\u0000\u0000\u0000R"+
		"\u022d\u0001\u0000\u0000\u0000T\u0235\u0001\u0000\u0000\u0000V\u023d\u0001"+
		"\u0000\u0000\u0000X\u0245\u0001\u0000\u0000\u0000Z\u024d\u0001\u0000\u0000"+
		"\u0000\\\u0255\u0001\u0000\u0000\u0000^\u025d\u0001\u0000\u0000\u0000"+
		"`\u0265\u0001\u0000\u0000\u0000b\u026d\u0001\u0000\u0000\u0000d\u0275"+
		"\u0001\u0000\u0000\u0000f\u027d\u0001\u0000\u0000\u0000h\u028a\u0001\u0000"+
		"\u0000\u0000j\u028c\u0001\u0000\u0000\u0000l\u028f\u0001\u0000\u0000\u0000"+
		"n\u0292\u0001\u0000\u0000\u0000p\u029a\u0001\u0000\u0000\u0000r\u02c4"+
		"\u0001\u0000\u0000\u0000t\u02c8\u0001\u0000\u0000\u0000v\u02ca\u0001\u0000"+
		"\u0000\u0000x\u02ee\u0001\u0000\u0000\u0000z\u030d\u0001\u0000\u0000\u0000"+
		"|\u0349\u0001\u0000\u0000\u0000~\u0370\u0001\u0000\u0000\u0000\u0080\u0372"+
		"\u0001\u0000\u0000\u0000\u0082\u0375\u0001\u0000\u0000\u0000\u0084\u037a"+
		"\u0001\u0000\u0000\u0000\u0086\u0380\u0001\u0000\u0000\u0000\u0088\u0392"+
		"\u0001\u0000\u0000\u0000\u008a\u0394\u0001\u0000\u0000\u0000\u008c\u03a4"+
		"\u0001\u0000\u0000\u0000\u008e\u03ac\u0001\u0000\u0000\u0000\u0090\u03b7"+
		"\u0001\u0000\u0000\u0000\u0092\u03bb\u0001\u0000\u0000\u0000\u0094\u03c2"+
		"\u0001\u0000\u0000\u0000\u0096\u03c4\u0001\u0000\u0000\u0000\u0098\u03c9"+
		"\u0001\u0000\u0000\u0000\u009a\u03d4\u0001\u0000\u0000\u0000\u009c\u040e"+
		"\u0001\u0000\u0000\u0000\u009e\u0441\u0001\u0000\u0000\u0000\u00a0\u044a"+
		"\u0001\u0000\u0000\u0000\u00a2\u0452\u0001\u0000\u0000\u0000\u00a4\u0454"+
		"\u0001\u0000\u0000\u0000\u00a6\u0458\u0001\u0000\u0000\u0000\u00a8\u045d"+
		"\u0001\u0000\u0000\u0000\u00aa\u0462\u0001\u0000\u0000\u0000\u00ac\u0464"+
		"\u0001\u0000\u0000\u0000\u00ae\u0467\u0001\u0000\u0000\u0000\u00b0\u0469"+
		"\u0001\u0000\u0000\u0000\u00b2\u046b\u0001\u0000\u0000\u0000\u00b4\u046d"+
		"\u0001\u0000\u0000\u0000\u00b6\u046f\u0001\u0000\u0000\u0000\u00b8\u0471"+
		"\u0001\u0000\u0000\u0000\u00ba\u0473\u0001\u0000\u0000\u0000\u00bc\u047b"+
		"\u0001\u0000\u0000\u0000\u00be\u047d\u0001\u0000\u0000\u0000\u00c0\u047f"+
		"\u0001\u0000\u0000\u0000\u00c2\u0481\u0001\u0000\u0000\u0000\u00c4\u0483"+
		"\u0001\u0000\u0000\u0000\u00c6\u0485\u0001\u0000\u0000\u0000\u00c8\u0487"+
		"\u0001\u0000\u0000\u0000\u00ca\u0489\u0001\u0000\u0000\u0000\u00cc\u048b"+
		"\u0001\u0000\u0000\u0000\u00ce\u048d\u0001\u0000\u0000\u0000\u00d0\u00d5"+
		"\u0003\u0002\u0001\u0000\u00d1\u00d5\u0003\u0004\u0002\u0000\u00d2\u00d5"+
		"\u0003\u0006\u0003\u0000\u00d3\u00d5\u0005<\u0000\u0000\u00d4\u00d0\u0001"+
		"\u0000\u0000\u0000\u00d4\u00d1\u0001\u0000\u0000\u0000\u00d4\u00d2\u0001"+
		"\u0000\u0000\u0000\u00d4\u00d3\u0001\u0000\u0000\u0000\u00d5\u00d8\u0001"+
		"\u0000\u0000\u0000\u00d6\u00d4\u0001\u0000\u0000\u0000\u00d6\u00d7\u0001"+
		"\u0000\u0000\u0000\u00d7\u00d9\u0001\u0000\u0000\u0000\u00d8\u00d6\u0001"+
		"\u0000\u0000\u0000\u00d9\u00da\u0005\u0000\u0000\u0001\u00da\u0001\u0001"+
		"\u0000\u0000\u0000\u00db\u00dc\u0005\u0005\u0000\u0000\u00dc\u00dd\u0003"+
		"\u00bc^\u0000\u00dd\u00de\u0005<\u0000\u0000\u00de\u0003\u0001\u0000\u0000"+
		"\u0000\u00df\u00e0\u0005\u0004\u0000\u0000\u00e0\u00e1\u0003\u00bc^\u0000"+
		"\u00e1\u00e2\u0005<\u0000\u0000\u00e2\u0005\u0001\u0000\u0000\u0000\u00e3"+
		"\u00eb\u0005\u0002\u0000\u0000\u00e4\u00eb\u0005\u0003\u0000\u0000\u00e5"+
		"\u00eb\u0003\b\u0004\u0000\u00e6\u00e7\u0003\n\u0005\u0000\u00e7\u00e8"+
		"\u0004\u0003\u0000\u0000\u00e8\u00eb\u0001\u0000\u0000\u0000\u00e9\u00eb"+
		"\u0003\f\u0006\u0000\u00ea\u00e3\u0001\u0000\u0000\u0000\u00ea\u00e4\u0001"+
		"\u0000\u0000\u0000\u00ea\u00e5\u0001\u0000\u0000\u0000\u00ea\u00e6\u0001"+
		"\u0000\u0000\u0000\u00ea\u00e9\u0001\u0000\u0000\u0000\u00eb\u0007\u0001"+
		"\u0000\u0000\u0000\u00ec\u00ed\u0005\u0006\u0000\u0000\u00ed\u00ee\u0005"+
		"0\u0000\u0000\u00ee\u00ef\u0003\u00c6c\u0000\u00ef\u00f0\u00051\u0000"+
		"\u0000\u00f0\u00f1\u0005<\u0000\u0000\u00f1\t\u0001\u0000\u0000\u0000"+
		"\u00f2\u00f3\u0003\u00c0`\u0000\u00f3\u00f4\u0005L\u0000\u0000\u00f4\u00f5"+
		"\u0003P(\u0000\u00f5\u00f6\u0005<\u0000\u0000\u00f6\u000b\u0001\u0000"+
		"\u0000\u0000\u00f7\u00f8\u0003\u00c0`\u0000\u00f8\u00fa\u00050\u0000\u0000"+
		"\u00f9\u00fb\u0003\u0088D\u0000\u00fa\u00f9\u0001\u0000\u0000\u0000\u00fa"+
		"\u00fb\u0001\u0000\u0000\u0000\u00fb\u00fc\u0001\u0000\u0000\u0000\u00fc"+
		"\u00fd\u00051\u0000\u0000\u00fd\u00fe\u0003\u0016\u000b\u0000\u00fe\u00ff"+
		"\u0004\u0006\u0001\u0000\u00ff\u010d\u0001\u0000\u0000\u0000\u0100\u0102"+
		"\u0007\u0000\u0000\u0000\u0101\u0100\u0001\u0000\u0000\u0000\u0101\u0102"+
		"\u0001\u0000\u0000\u0000\u0102\u0103\u0001\u0000\u0000\u0000\u0103\u0104"+
		"\u0003\u00c0`\u0000\u0104\u0106\u00050\u0000\u0000\u0105\u0107\u0003\u0088"+
		"D\u0000\u0106\u0105\u0001\u0000\u0000\u0000\u0106\u0107\u0001\u0000\u0000"+
		"\u0000\u0107\u0108\u0001\u0000\u0000\u0000\u0108\u0109\u00051\u0000\u0000"+
		"\u0109\u010a\u0003\u0016\u000b\u0000\u010a\u010b\u0004\u0006\u0002\u0000"+
		"\u010b\u010d\u0001\u0000\u0000\u0000\u010c\u00f7\u0001\u0000\u0000\u0000"+
		"\u010c\u0101\u0001\u0000\u0000\u0000\u010d\r\u0001\u0000\u0000\u0000\u010e"+
		"\u0139\u0003\u0016\u000b\u0000\u010f\u0139\u0003\u0018\f\u0000\u0110\u0111"+
		"\u0003\u001a\r\u0000\u0111\u0112\u0004\u0007\u0003\u0000\u0112\u0139\u0001"+
		"\u0000\u0000\u0000\u0113\u0139\u0003\u001c\u000e\u0000\u0114\u0139\u0003"+
		"\u001e\u000f\u0000\u0115\u0139\u0003 \u0010\u0000\u0116\u0139\u0003\""+
		"\u0011\u0000\u0117\u0139\u0003$\u0012\u0000\u0118\u0139\u0003&\u0013\u0000"+
		"\u0119\u011a\u0003(\u0014\u0000\u011a\u011b\u0004\u0007\u0004\u0000\u011b"+
		"\u0139\u0001\u0000\u0000\u0000\u011c\u011d\u0003*\u0015\u0000\u011d\u011e"+
		"\u0004\u0007\u0005\u0000\u011e\u0139\u0001\u0000\u0000\u0000\u011f\u0139"+
		"\u0003,\u0016\u0000\u0120\u0139\u0003.\u0017\u0000\u0121\u0139\u00030"+
		"\u0018\u0000\u0122\u0139\u00032\u0019\u0000\u0123\u0139\u00034\u001a\u0000"+
		"\u0124\u0139\u00036\u001b\u0000\u0125\u0139\u00038\u001c\u0000\u0126\u0139"+
		"\u0003:\u001d\u0000\u0127\u0139\u0003<\u001e\u0000\u0128\u0139\u0003>"+
		"\u001f\u0000\u0129\u0139\u0003@ \u0000\u012a\u012b\u0003B!\u0000\u012b"+
		"\u012c\u0004\u0007\u0006\u0000\u012c\u0139\u0001\u0000\u0000\u0000\u012d"+
		"\u0139\u0003D\"\u0000\u012e\u0139\u0003F#\u0000\u012f\u0130\u0003H$\u0000"+
		"\u0130\u0131\u0004\u0007\u0007\u0000\u0131\u0139\u0001\u0000\u0000\u0000"+
		"\u0132\u0133\u0003J%\u0000\u0133\u0134\u0004\u0007\b\u0000\u0134\u0139"+
		"\u0001\u0000\u0000\u0000\u0135\u0136\u0003L&\u0000\u0136\u0137\u0004\u0007"+
		"\t\u0000\u0137\u0139\u0001\u0000\u0000\u0000\u0138\u010e\u0001\u0000\u0000"+
		"\u0000\u0138\u010f\u0001\u0000\u0000\u0000\u0138\u0110\u0001\u0000\u0000"+
		"\u0000\u0138\u0113\u0001\u0000\u0000\u0000\u0138\u0114\u0001\u0000\u0000"+
		"\u0000\u0138\u0115\u0001\u0000\u0000\u0000\u0138\u0116\u0001\u0000\u0000"+
		"\u0000\u0138\u0117\u0001\u0000\u0000\u0000\u0138\u0118\u0001\u0000\u0000"+
		"\u0000\u0138\u0119\u0001\u0000\u0000\u0000\u0138\u011c\u0001\u0000\u0000"+
		"\u0000\u0138\u011f\u0001\u0000\u0000\u0000\u0138\u0120\u0001\u0000\u0000"+
		"\u0000\u0138\u0121\u0001\u0000\u0000\u0000\u0138\u0122\u0001\u0000\u0000"+
		"\u0000\u0138\u0123\u0001\u0000\u0000\u0000\u0138\u0124\u0001\u0000\u0000"+
		"\u0000\u0138\u0125\u0001\u0000\u0000\u0000\u0138\u0126\u0001\u0000\u0000"+
		"\u0000\u0138\u0127\u0001\u0000\u0000\u0000\u0138\u0128\u0001\u0000\u0000"+
		"\u0000\u0138\u0129\u0001\u0000\u0000\u0000\u0138\u012a\u0001\u0000\u0000"+
		"\u0000\u0138\u012d\u0001\u0000\u0000\u0000\u0138\u012e\u0001\u0000\u0000"+
		"\u0000\u0138\u012f\u0001\u0000\u0000\u0000\u0138\u0132\u0001\u0000\u0000"+
		"\u0000\u0138\u0135\u0001\u0000\u0000\u0000\u0139\u000f\u0001\u0000\u0000"+
		"\u0000\u013a\u013c\u0003\u000e\u0007\u0000\u013b\u013a\u0001\u0000\u0000"+
		"\u0000\u013c\u013d\u0001\u0000\u0000\u0000\u013d\u013b\u0001\u0000\u0000"+
		"\u0000\u013d\u013e\u0001\u0000\u0000\u0000\u013e\u0011\u0001\u0000\u0000"+
		"\u0000\u013f\u0142\u0003\u000e\u0007\u0000\u0140\u0142\u0003\u0014\n\u0000"+
		"\u0141\u013f\u0001\u0000\u0000\u0000\u0141\u0140\u0001\u0000\u0000\u0000"+
		"\u0142\u0143\u0001\u0000\u0000\u0000\u0143\u0141\u0001\u0000\u0000\u0000"+
		"\u0143\u0144\u0001\u0000\u0000\u0000\u0144\u0013\u0001\u0000\u0000\u0000"+
		"\u0145\u0147\u0005\u0002\u0000\u0000\u0146\u0148\u0003\u0010\b\u0000\u0147"+
		"\u0146\u0001\u0000\u0000\u0000\u0147\u0148\u0001\u0000\u0000\u0000\u0148"+
		"\u0149\u0001\u0000\u0000\u0000\u0149\u014a\u0005\u0003\u0000\u0000\u014a"+
		"\u0015\u0001\u0000\u0000\u0000\u014b\u014d\u00052\u0000\u0000\u014c\u014e"+
		"\u0003\u0012\t\u0000\u014d\u014c\u0001\u0000\u0000\u0000\u014d\u014e\u0001"+
		"\u0000\u0000\u0000\u014e\u014f\u0001\u0000\u0000\u0000\u014f\u0150\u0005"+
		"3\u0000\u0000\u0150\u0017\u0001\u0000\u0000\u0000\u0151\u0155\u0003t:"+
		"\u0000\u0152\u0155\u0003v;\u0000\u0153\u0155\u0003N\'\u0000\u0154\u0151"+
		"\u0001\u0000\u0000\u0000\u0154\u0152\u0001\u0000\u0000\u0000\u0154\u0153"+
		"\u0001\u0000\u0000\u0000\u0154\u0155\u0001\u0000\u0000\u0000\u0155\u0156"+
		"\u0001\u0000\u0000\u0000\u0156\u0157\u0005<\u0000\u0000\u0157\u0019\u0001"+
		"\u0000\u0000\u0000\u0158\u0159\u0005m\u0000\u0000\u0159\u015a\u0003\u00c0"+
		"`\u0000\u015a\u015b\u0005L\u0000\u0000\u015b\u015c\u0003P(\u0000\u015c"+
		"\u015d\u0005<\u0000\u0000\u015d\u001b\u0001\u0000\u0000\u0000\u015e\u015f"+
		"\u0003\u009aM\u0000\u015f\u0160\u0005\b\u0000\u0000\u0160\u0161\u0005"+
		"0\u0000\u0000\u0161\u0162\u0003P(\u0000\u0162\u0163\u00051\u0000\u0000"+
		"\u0163\u0164\u0005<\u0000\u0000\u0164\u001d\u0001\u0000\u0000\u0000\u0165"+
		"\u0166\u0003\u009aM\u0000\u0166\u0167\u0005\t\u0000\u0000\u0167\u0168"+
		"\u00050\u0000\u0000\u0168\u016b\u0003P(\u0000\u0169\u016a\u00056\u0000"+
		"\u0000\u016a\u016c\u0003\u008cF\u0000\u016b\u0169\u0001\u0000\u0000\u0000"+
		"\u016b\u016c\u0001\u0000\u0000\u0000\u016c\u016d\u0001\u0000\u0000\u0000"+
		"\u016d\u016e\u00051\u0000\u0000\u016e\u016f\u0005<\u0000\u0000\u016f\u001f"+
		"\u0001\u0000\u0000\u0000\u0170\u0171\u0005\n\u0000\u0000\u0171\u0172\u0003"+
		"P(\u0000\u0172\u0173\u0005<\u0000\u0000\u0173!\u0001\u0000\u0000\u0000"+
		"\u0174\u0175\u0003\u009aM\u0000\u0175\u0176\u0005\u000b\u0000\u0000\u0176"+
		"\u0177\u00050\u0000\u0000\u0177\u017a\u0003P(\u0000\u0178\u0179\u0005"+
		"6\u0000\u0000\u0179\u017b\u0003\u008cF\u0000\u017a\u0178\u0001\u0000\u0000"+
		"\u0000\u017a\u017b\u0001\u0000\u0000\u0000\u017b\u017c\u0001\u0000\u0000"+
		"\u0000\u017c\u017d\u00051\u0000\u0000\u017d\u017e\u0005<\u0000\u0000\u017e"+
		"#\u0001\u0000\u0000\u0000\u017f\u0180\u0003\u009aM\u0000\u0180\u0181\u0005"+
		"\f\u0000\u0000\u0181\u0182\u00050\u0000\u0000\u0182\u0185\u0003P(\u0000"+
		"\u0183\u0184\u00056\u0000\u0000\u0184\u0186\u0003\u008cF\u0000\u0185\u0183"+
		"\u0001\u0000\u0000\u0000\u0185\u0186\u0001\u0000\u0000\u0000\u0186\u0187"+
		"\u0001\u0000\u0000\u0000\u0187\u0188\u00051\u0000\u0000\u0188\u0189\u0005"+
		"<\u0000\u0000\u0189%\u0001\u0000\u0000\u0000\u018a\u018d\u0005\r\u0000"+
		"\u0000\u018b\u018c\u00050\u0000\u0000\u018c\u018e\u00051\u0000\u0000\u018d"+
		"\u018b\u0001\u0000\u0000\u0000\u018d\u018e\u0001\u0000\u0000\u0000\u018e"+
		"\u018f\u0001\u0000\u0000\u0000\u018f\u0190\u0005<\u0000\u0000\u0190\'"+
		"\u0001\u0000\u0000\u0000\u0191\u0194\u0005\u000e\u0000\u0000\u0192\u0193"+
		"\u00050\u0000\u0000\u0193\u0195\u00051\u0000\u0000\u0194\u0192\u0001\u0000"+
		"\u0000\u0000\u0194\u0195\u0001\u0000\u0000\u0000\u0195\u0196\u0001\u0000"+
		"\u0000\u0000\u0196\u0197\u0005<\u0000\u0000\u0197)\u0001\u0000\u0000\u0000"+
		"\u0198\u0199\u0005n\u0000\u0000\u0199\u019a\u0003P(\u0000\u019a\u019b"+
		"\u0005<\u0000\u0000\u019b+\u0001\u0000\u0000\u0000\u019c\u019d\u0005\u000f"+
		"\u0000\u0000\u019d\u019e\u00050\u0000\u0000\u019e\u019f\u0003P(\u0000"+
		"\u019f\u01a0\u00051\u0000\u0000\u01a0\u01a3\u0003\u000e\u0007\u0000\u01a1"+
		"\u01a2\u0005\u0010\u0000\u0000\u01a2\u01a4\u0003\u000e\u0007\u0000\u01a3"+
		"\u01a1\u0001\u0000\u0000\u0000\u01a3\u01a4\u0001\u0000\u0000\u0000\u01a4"+
		"-\u0001\u0000\u0000\u0000\u01a5\u01a6\u0005\u0012\u0000\u0000\u01a6\u01a7"+
		"\u00050\u0000\u0000\u01a7\u01a8\u0003P(\u0000\u01a8\u01a9\u00051\u0000"+
		"\u0000\u01a9\u01aa\u0003\u000e\u0007\u0000\u01aa/\u0001\u0000\u0000\u0000"+
		"\u01ab\u01ac\u0005\u0011\u0000\u0000\u01ac\u01ad\u0003\u000e\u0007\u0000"+
		"\u01ad\u01ae\u0005\u0012\u0000\u0000\u01ae\u01af\u00050\u0000\u0000\u01af"+
		"\u01b0\u0003P(\u0000\u01b0\u01b1\u00051\u0000\u0000\u01b1\u01b2\u0005"+
		"<\u0000\u0000\u01b21\u0001\u0000\u0000\u0000\u01b3\u01b4\u0005\u0013\u0000"+
		"\u0000\u01b4\u01b6\u00050\u0000\u0000\u01b5\u01b7\u0003N\'\u0000\u01b6"+
		"\u01b5\u0001\u0000\u0000\u0000\u01b6\u01b7\u0001\u0000\u0000\u0000\u01b7"+
		"\u01b8\u0001\u0000\u0000\u0000\u01b8\u01ba\u0005<\u0000\u0000\u01b9\u01bb"+
		"\u0003P(\u0000\u01ba\u01b9\u0001\u0000\u0000\u0000\u01ba\u01bb\u0001\u0000"+
		"\u0000\u0000\u01bb\u01bc\u0001\u0000\u0000\u0000\u01bc\u01be\u0005<\u0000"+
		"\u0000\u01bd\u01bf\u0003N\'\u0000\u01be\u01bd\u0001\u0000\u0000\u0000"+
		"\u01be\u01bf\u0001\u0000\u0000\u0000\u01bf\u01c0\u0001\u0000\u0000\u0000"+
		"\u01c0\u01c1\u00051\u0000\u0000\u01c1\u01c2\u0003\u000e\u0007\u0000\u01c2"+
		"3\u0001\u0000\u0000\u0000\u01c3\u01c4\u0005\u0014\u0000\u0000\u01c4\u01c5"+
		"\u00050\u0000\u0000\u01c5\u01c8\u0003\u00c0`\u0000\u01c6\u01c7\u00056"+
		"\u0000\u0000\u01c7\u01c9\u0003\u00c0`\u0000\u01c8\u01c6\u0001\u0000\u0000"+
		"\u0000\u01c8\u01c9\u0001\u0000\u0000\u0000\u01c9\u01ca\u0001\u0000\u0000"+
		"\u0000\u01ca\u01cb\u0005\u0015\u0000\u0000\u01cb\u01cc\u0003P(\u0000\u01cc"+
		"\u01cd\u00051\u0000\u0000\u01cd\u01ce\u0003\u000e\u0007\u0000\u01ce5\u0001"+
		"\u0000\u0000\u0000\u01cf\u01d0\u0005\u0016\u0000\u0000\u01d0\u01d1\u0005"+
		"0\u0000\u0000\u01d1\u01d2\u0003P(\u0000\u01d2\u01d3\u00051\u0000\u0000"+
		"\u01d3\u01d4\u0003\u0016\u000b\u0000\u01d47\u0001\u0000\u0000\u0000\u01d5"+
		"\u01d8\u0005\u0017\u0000\u0000\u01d6\u01d9\u0003\u00cae\u0000\u01d7\u01d9"+
		"\u0003\u00c6c\u0000\u01d8\u01d6\u0001\u0000\u0000\u0000\u01d8\u01d7\u0001"+
		"\u0000\u0000\u0000\u01d9\u01da\u0001\u0000\u0000\u0000\u01da\u01db\u0005"+
		";\u0000\u0000\u01db9\u0001\u0000\u0000\u0000\u01dc\u01dd\u0005\u0018\u0000"+
		"\u0000\u01dd\u01de\u0005;\u0000\u0000\u01de;\u0001\u0000\u0000\u0000\u01df"+
		"\u01e0\u0005\u0019\u0000\u0000\u01e0\u01e1\u0005<\u0000\u0000\u01e1=\u0001"+
		"\u0000\u0000\u0000\u01e2\u01e3\u0005\u001a\u0000\u0000\u01e3\u01e4\u0005"+
		"<\u0000\u0000\u01e4?\u0001\u0000\u0000\u0000\u01e5\u01e7\u0005\u001b\u0000"+
		"\u0000\u01e6\u01e8\u0003P(\u0000\u01e7\u01e6\u0001\u0000\u0000\u0000\u01e7"+
		"\u01e8\u0001\u0000\u0000\u0000\u01e8\u01e9\u0001\u0000\u0000\u0000\u01e9"+
		"\u01ea\u0005<\u0000\u0000\u01eaA\u0001\u0000\u0000\u0000\u01eb\u01ec\u0005"+
		"\u001c\u0000\u0000\u01ec\u01ed\u0005<\u0000\u0000\u01edC\u0001\u0000\u0000"+
		"\u0000\u01ee\u01ef\u0005\u001d\u0000\u0000\u01ef\u01f1\u00050\u0000\u0000"+
		"\u01f0\u01f2\u0003\u008cF\u0000\u01f1\u01f0\u0001\u0000\u0000\u0000\u01f1"+
		"\u01f2\u0001\u0000\u0000\u0000\u01f2\u01f3\u0001\u0000\u0000\u0000\u01f3"+
		"\u01f4\u00051\u0000\u0000\u01f4\u01f5\u0005<\u0000\u0000\u01f5E\u0001"+
		"\u0000\u0000\u0000\u01f6\u01f7\u0005\u001e\u0000\u0000\u01f7\u01f9\u0005"+
		"0\u0000\u0000\u01f8\u01fa\u0003\u008cF\u0000\u01f9\u01f8\u0001\u0000\u0000"+
		"\u0000\u01f9\u01fa\u0001\u0000\u0000\u0000\u01fa\u01fb\u0001\u0000\u0000"+
		"\u0000\u01fb\u01fc\u00051\u0000\u0000\u01fc\u01fd\u0005<\u0000\u0000\u01fd"+
		"G\u0001\u0000\u0000\u0000\u01fe\u01ff\u0005\u001f\u0000\u0000\u01ff\u0201"+
		"\u00050\u0000\u0000\u0200\u0202\u0003\u008cF\u0000\u0201\u0200\u0001\u0000"+
		"\u0000\u0000\u0201\u0202\u0001\u0000\u0000\u0000\u0202\u0203\u0001\u0000"+
		"\u0000\u0000\u0203\u0204\u00051\u0000\u0000\u0204\u0205\u0005<\u0000\u0000"+
		"\u0205I\u0001\u0000\u0000\u0000\u0206\u0207\u0005 \u0000\u0000\u0207\u0209"+
		"\u00050\u0000\u0000\u0208\u020a\u0003\u008cF\u0000\u0209\u0208\u0001\u0000"+
		"\u0000\u0000\u0209\u020a\u0001\u0000\u0000\u0000\u020a\u020b\u0001\u0000"+
		"\u0000\u0000\u020b\u020c\u00051\u0000\u0000\u020c\u020d\u0005<\u0000\u0000"+
		"\u020dK\u0001\u0000\u0000\u0000\u020e\u020f\u0005!\u0000\u0000\u020f\u0211"+
		"\u00050\u0000\u0000\u0210\u0212\u0003\u008cF\u0000\u0211\u0210\u0001\u0000"+
		"\u0000\u0000\u0211\u0212\u0001\u0000\u0000\u0000\u0212\u0213\u0001\u0000"+
		"\u0000\u0000\u0213\u0214\u00051\u0000\u0000\u0214\u0215\u0005<\u0000\u0000"+
		"\u0215M\u0001\u0000\u0000\u0000\u0216\u0217\u0003\u008eG\u0000\u0217\u0218"+
		"\u0005L\u0000\u0000\u0218\u0219\u0003P(\u0000\u0219\u021a\u0004\'\n\u0000"+
		"\u021a\u022a\u0001\u0000\u0000\u0000\u021b\u021c\u0003\u0094J\u0000\u021c"+
		"\u021d\u0007\u0001\u0000\u0000\u021d\u021e\u0003P(\u0000\u021e\u022a\u0001"+
		"\u0000\u0000\u0000\u021f\u0220\u0005>\u0000\u0000\u0220\u022a\u0003\u0094"+
		"J\u0000\u0221\u0222\u0003\u0094J\u0000\u0222\u0223\u0005>\u0000\u0000"+
		"\u0223\u022a\u0001\u0000\u0000\u0000\u0224\u0225\u0005?\u0000\u0000\u0225"+
		"\u022a\u0003\u0094J\u0000\u0226\u0227\u0003\u0094J\u0000\u0227\u0228\u0005"+
		"?\u0000\u0000\u0228\u022a\u0001\u0000\u0000\u0000\u0229\u0216\u0001\u0000"+
		"\u0000\u0000\u0229\u021b\u0001\u0000\u0000\u0000\u0229\u021f\u0001\u0000"+
		"\u0000\u0000\u0229\u0221\u0001\u0000\u0000\u0000\u0229\u0224\u0001\u0000"+
		"\u0000\u0000\u0229\u0226\u0001\u0000\u0000\u0000\u022aO\u0001\u0000\u0000"+
		"\u0000\u022b\u022c\u0003R)\u0000\u022cQ\u0001\u0000\u0000\u0000\u022d"+
		"\u0233\u0003T*\u0000\u022e\u022f\u0005=\u0000\u0000\u022f\u0230\u0003"+
		"P(\u0000\u0230\u0231\u0005;\u0000\u0000\u0231\u0232\u0003R)\u0000\u0232"+
		"\u0234\u0001\u0000\u0000\u0000\u0233\u022e\u0001\u0000\u0000\u0000\u0233"+
		"\u0234\u0001\u0000\u0000\u0000\u0234S\u0001\u0000\u0000\u0000\u0235\u023a"+
		"\u0003V+\u0000\u0236\u0237\u0005B\u0000\u0000\u0237\u0239\u0003V+\u0000"+
		"\u0238\u0236\u0001\u0000\u0000\u0000\u0239\u023c\u0001\u0000\u0000\u0000"+
		"\u023a\u0238\u0001\u0000\u0000\u0000\u023a\u023b\u0001\u0000\u0000\u0000"+
		"\u023bU\u0001\u0000\u0000\u0000\u023c\u023a\u0001\u0000\u0000\u0000\u023d"+
		"\u0242\u0003X,\u0000\u023e\u023f\u0005C\u0000\u0000\u023f\u0241\u0003"+
		"X,\u0000\u0240\u023e\u0001\u0000\u0000\u0000\u0241\u0244\u0001\u0000\u0000"+
		"\u0000\u0242\u0240\u0001\u0000\u0000\u0000\u0242\u0243\u0001\u0000\u0000"+
		"\u0000\u0243W\u0001\u0000\u0000\u0000\u0244\u0242\u0001\u0000\u0000\u0000"+
		"\u0245\u024a\u0003Z-\u0000\u0246\u0247\u0005W\u0000\u0000\u0247\u0249"+
		"\u0003Z-\u0000\u0248\u0246\u0001\u0000\u0000\u0000\u0249\u024c\u0001\u0000"+
		"\u0000\u0000\u024a\u0248\u0001\u0000\u0000\u0000\u024a\u024b\u0001\u0000"+
		"\u0000\u0000\u024bY\u0001\u0000\u0000\u0000\u024c\u024a\u0001\u0000\u0000"+
		"\u0000\u024d\u0252\u0003\\.\u0000\u024e\u024f\u0005X\u0000\u0000\u024f"+
		"\u0251\u0003\\.\u0000\u0250\u024e\u0001\u0000\u0000\u0000\u0251\u0254"+
		"\u0001\u0000\u0000\u0000\u0252\u0250\u0001\u0000\u0000\u0000\u0252\u0253"+
		"\u0001\u0000\u0000\u0000\u0253[\u0001\u0000\u0000\u0000\u0254\u0252\u0001"+
		"\u0000\u0000\u0000\u0255\u025a\u0003^/\u0000\u0256\u0257\u0005Y\u0000"+
		"\u0000\u0257\u0259\u0003^/\u0000\u0258\u0256\u0001\u0000\u0000\u0000\u0259"+
		"\u025c\u0001\u0000\u0000\u0000\u025a\u0258\u0001\u0000\u0000\u0000\u025a"+
		"\u025b\u0001\u0000\u0000\u0000\u025b]\u0001\u0000\u0000\u0000\u025c\u025a"+
		"\u0001\u0000\u0000\u0000\u025d\u0262\u0003`0\u0000\u025e\u025f\u0007\u0002"+
		"\u0000\u0000\u025f\u0261\u0003`0\u0000\u0260\u025e\u0001\u0000\u0000\u0000"+
		"\u0261\u0264\u0001\u0000\u0000\u0000\u0262\u0260\u0001\u0000\u0000\u0000"+
		"\u0262\u0263\u0001\u0000\u0000\u0000\u0263_\u0001\u0000\u0000\u0000\u0264"+
		"\u0262\u0001\u0000\u0000\u0000\u0265\u026a\u0003b1\u0000\u0266\u0267\u0007"+
		"\u0003\u0000\u0000\u0267\u0269\u0003b1\u0000\u0268\u0266\u0001\u0000\u0000"+
		"\u0000\u0269\u026c\u0001\u0000\u0000\u0000\u026a\u0268\u0001\u0000\u0000"+
		"\u0000\u026a\u026b\u0001\u0000\u0000\u0000\u026ba\u0001\u0000\u0000\u0000"+
		"\u026c\u026a\u0001\u0000\u0000\u0000\u026d\u0272\u0003d2\u0000\u026e\u026f"+
		"\u0007\u0004\u0000\u0000\u026f\u0271\u0003d2\u0000\u0270\u026e\u0001\u0000"+
		"\u0000\u0000\u0271\u0274\u0001\u0000\u0000\u0000\u0272\u0270\u0001\u0000"+
		"\u0000\u0000\u0272\u0273\u0001\u0000\u0000\u0000\u0273c\u0001\u0000\u0000"+
		"\u0000\u0274\u0272\u0001\u0000\u0000\u0000\u0275\u027a\u0003f3\u0000\u0276"+
		"\u0277\u0007\u0005\u0000\u0000\u0277\u0279\u0003f3\u0000\u0278\u0276\u0001"+
		"\u0000\u0000\u0000\u0279\u027c\u0001\u0000\u0000\u0000\u027a\u0278\u0001"+
		"\u0000\u0000\u0000\u027a\u027b\u0001\u0000\u0000\u0000\u027be\u0001\u0000"+
		"\u0000\u0000\u027c\u027a\u0001\u0000\u0000\u0000\u027d\u0282\u0003h4\u0000"+
		"\u027e\u027f\u0007\u0006\u0000\u0000\u027f\u0281\u0003h4\u0000\u0280\u027e"+
		"\u0001\u0000\u0000\u0000\u0281\u0284\u0001\u0000\u0000\u0000\u0282\u0280"+
		"\u0001\u0000\u0000\u0000\u0282\u0283\u0001\u0000\u0000\u0000\u0283g\u0001"+
		"\u0000\u0000\u0000\u0284\u0282\u0001\u0000\u0000\u0000\u0285\u028b\u0003"+
		"j5\u0000\u0286\u028b\u0003l6\u0000\u0287\u028b\u0003n7\u0000\u0288\u028b"+
		"\u0003p8\u0000\u0289\u028b\u0003r9\u0000\u028a\u0285\u0001\u0000\u0000"+
		"\u0000\u028a\u0286\u0001\u0000\u0000\u0000\u028a\u0287\u0001\u0000\u0000"+
		"\u0000\u028a\u0288\u0001\u0000\u0000\u0000\u028a\u0289\u0001\u0000\u0000"+
		"\u0000\u028bi\u0001\u0000\u0000\u0000\u028c\u028d\u0005K\u0000\u0000\u028d"+
		"\u028e\u0003h4\u0000\u028ek\u0001\u0000\u0000\u0000\u028f\u0290\u0005"+
		"J\u0000\u0000\u0290\u0291\u0003h4\u0000\u0291m\u0001\u0000\u0000\u0000"+
		"\u0292\u0298\u0005[\u0000\u0000\u0293\u0299\u0003\u00c8d\u0000\u0294\u0299"+
		"\u0003\u00cae\u0000\u0295\u0299\u0003\u00c0`\u0000\u0296\u0299\u0003\u0092"+
		"I\u0000\u0297\u0299\u0003\u009cN\u0000\u0298\u0293\u0001\u0000\u0000\u0000"+
		"\u0298\u0294\u0001\u0000\u0000\u0000\u0298\u0295\u0001\u0000\u0000\u0000"+
		"\u0298\u0296\u0001\u0000\u0000\u0000\u0298\u0297\u0001\u0000\u0000\u0000"+
		"\u0299o\u0001\u0000\u0000\u0000\u029a\u029b\u0005^\u0000\u0000\u029b\u029c"+
		"\u0005d\u0000\u0000\u029cq\u0001\u0000\u0000\u0000\u029d\u02c5\u0003t"+
		":\u0000\u029e\u029f\u0003|>\u0000\u029f\u02a0\u00049\u000b\u0000\u02a0"+
		"\u02c5\u0001\u0000\u0000\u0000\u02a1\u02a2\u0003\u0080@\u0000\u02a2\u02a3"+
		"\u00049\f\u0000\u02a3\u02c5\u0001\u0000\u0000\u0000\u02a4\u02c5\u0003"+
		"\u0086C\u0000\u02a5\u02c5\u0003\u0082A\u0000\u02a6\u02a7\u0003\u0084B"+
		"\u0000\u02a7\u02a8\u00049\r\u0000\u02a8\u02c5\u0001\u0000\u0000\u0000"+
		"\u02a9\u02aa\u0003\u0090H\u0000\u02aa\u02ab\u00049\u000e\u0000\u02ab\u02c5"+
		"\u0001\u0000\u0000\u0000\u02ac\u02c5\u0003\u009cN\u0000\u02ad\u02c5\u0003"+
		"\u00a8T\u0000\u02ae\u02c5\u0003\u0092I\u0000\u02af\u02b0\u0003\u00aaU"+
		"\u0000\u02b0\u02b1\u00049\u000f\u0000\u02b1\u02c5\u0001\u0000\u0000\u0000"+
		"\u02b2\u02c5\u0003\u00acV\u0000\u02b3\u02c5\u0003\u00aeW\u0000\u02b4\u02c5"+
		"\u0003\u00b0X\u0000\u02b5\u02c5\u0003\u00b2Y\u0000\u02b6\u02c5\u0003\u00b4"+
		"Z\u0000\u02b7\u02c5\u0003\u00b6[\u0000\u02b8\u02c5\u0003\u00b8\\\u0000"+
		"\u02b9\u02c5\u0003\u00c0`\u0000\u02ba\u02bb\u0003\u00c2a\u0000\u02bb\u02bc"+
		"\u00049\u0010\u0000\u02bc\u02c5\u0001\u0000\u0000\u0000\u02bd\u02c5\u0003"+
		"\u00c4b\u0000\u02be\u02c5\u0003\u00c6c\u0000\u02bf\u02c5\u0003\u00ba]"+
		"\u0000\u02c0\u02c5\u0003\u00c8d\u0000\u02c1\u02c5\u0003\u00cae\u0000\u02c2"+
		"\u02c5\u0003\u00ccf\u0000\u02c3\u02c5\u0003\u00ceg\u0000\u02c4\u029d\u0001"+
		"\u0000\u0000\u0000\u02c4\u029e\u0001\u0000\u0000\u0000\u02c4\u02a1\u0001"+
		"\u0000\u0000\u0000\u02c4\u02a4\u0001\u0000\u0000\u0000\u02c4\u02a5\u0001"+
		"\u0000\u0000\u0000\u02c4\u02a6\u0001\u0000\u0000\u0000\u02c4\u02a9\u0001"+
		"\u0000\u0000\u0000\u02c4\u02ac\u0001\u0000\u0000\u0000\u02c4\u02ad\u0001"+
		"\u0000\u0000\u0000\u02c4\u02ae\u0001\u0000\u0000\u0000\u02c4\u02af\u0001"+
		"\u0000\u0000\u0000\u02c4\u02b2\u0001\u0000\u0000\u0000\u02c4\u02b3\u0001"+
		"\u0000\u0000\u0000\u02c4\u02b4\u0001\u0000\u0000\u0000\u02c4\u02b5\u0001"+
		"\u0000\u0000\u0000\u02c4\u02b6\u0001\u0000\u0000\u0000\u02c4\u02b7\u0001"+
		"\u0000\u0000\u0000\u02c4\u02b8\u0001\u0000\u0000\u0000\u02c4\u02b9\u0001"+
		"\u0000\u0000\u0000\u02c4\u02ba\u0001\u0000\u0000\u0000\u02c4\u02bd\u0001"+
		"\u0000\u0000\u0000\u02c4\u02be\u0001\u0000\u0000\u0000\u02c4\u02bf\u0001"+
		"\u0000\u0000\u0000\u02c4\u02c0\u0001\u0000\u0000\u0000\u02c4\u02c1\u0001"+
		"\u0000\u0000\u0000\u02c4\u02c2\u0001\u0000\u0000\u0000\u02c4\u02c3\u0001"+
		"\u0000\u0000\u0000\u02c5s\u0001\u0000\u0000\u0000\u02c6\u02c9\u0003x<"+
		"\u0000\u02c7\u02c9\u0003z=\u0000\u02c8\u02c6\u0001\u0000\u0000\u0000\u02c8"+
		"\u02c7\u0001\u0000\u0000\u0000\u02c9u\u0001\u0000\u0000\u0000\u02ca\u02cd"+
		"\u0003\u009aM\u0000\u02cb\u02ce\u0003x<\u0000\u02cc\u02ce\u0003z=\u0000"+
		"\u02cd\u02cb\u0001\u0000\u0000\u0000\u02cd\u02cc\u0001\u0000\u0000\u0000"+
		"\u02cew\u0001\u0000\u0000\u0000\u02cf\u02d1\u0005\"\u0000\u0000\u02d0"+
		"\u02cf\u0001\u0000\u0000\u0000\u02d0\u02d1\u0001\u0000\u0000\u0000\u02d1"+
		"\u02d5\u0001\u0000\u0000\u0000\u02d2\u02d3\u0003\u00bc^\u0000\u02d3\u02d4"+
		"\u0005:\u0000\u0000\u02d4\u02d6\u0001\u0000\u0000\u0000\u02d5\u02d2\u0001"+
		"\u0000\u0000\u0000\u02d5\u02d6\u0001\u0000\u0000\u0000\u02d6\u02d7\u0001"+
		"\u0000\u0000\u0000\u02d7\u02d8\u0003\u00c0`\u0000\u02d8\u02da\u00050\u0000"+
		"\u0000\u02d9\u02db\u0003\u008cF\u0000\u02da\u02d9\u0001\u0000\u0000\u0000"+
		"\u02da\u02db\u0001\u0000\u0000\u0000\u02db\u02dc\u0001\u0000\u0000\u0000"+
		"\u02dc\u02dd\u00051\u0000\u0000\u02dd\u02ef\u0001\u0000\u0000\u0000\u02de"+
		"\u02e0\u0005#\u0000\u0000\u02df\u02de\u0001\u0000\u0000\u0000\u02df\u02e0"+
		"\u0001\u0000\u0000\u0000\u02e0\u02e4\u0001\u0000\u0000\u0000\u02e1\u02e2"+
		"\u0003\u00bc^\u0000\u02e2\u02e3\u0005:\u0000\u0000\u02e3\u02e5\u0001\u0000"+
		"\u0000\u0000\u02e4\u02e1\u0001\u0000\u0000\u0000\u02e4\u02e5\u0001\u0000"+
		"\u0000\u0000\u02e5\u02e6\u0001\u0000\u0000\u0000\u02e6\u02e7\u0003\u00c0"+
		"`\u0000\u02e7\u02e9\u00050\u0000\u0000\u02e8\u02ea\u0003\u008cF\u0000"+
		"\u02e9\u02e8\u0001\u0000\u0000\u0000\u02e9\u02ea\u0001\u0000\u0000\u0000"+
		"\u02ea\u02eb\u0001\u0000\u0000\u0000\u02eb\u02ec\u00051\u0000\u0000\u02ec"+
		"\u02ed\u0004<\u0011\u0000\u02ed\u02ef\u0001\u0000\u0000\u0000\u02ee\u02d0"+
		"\u0001\u0000\u0000\u0000\u02ee\u02df\u0001\u0000\u0000\u0000\u02efy\u0001"+
		"\u0000\u0000\u0000\u02f0\u02f2\u0005\"\u0000\u0000\u02f1\u02f0\u0001\u0000"+
		"\u0000\u0000\u02f1\u02f2\u0001\u0000\u0000\u0000\u02f2\u02f3\u0001\u0000"+
		"\u0000\u0000\u02f3\u02f4\u00054\u0000\u0000\u02f4\u02f5\u00054\u0000\u0000"+
		"\u02f5\u02f6\u0003P(\u0000\u02f6\u02f7\u00055\u0000\u0000\u02f7\u02f8"+
		"\u00055\u0000\u0000\u02f8\u02fa\u00050\u0000\u0000\u02f9\u02fb\u0003\u008c"+
		"F\u0000\u02fa\u02f9\u0001\u0000\u0000\u0000\u02fa\u02fb\u0001\u0000\u0000"+
		"\u0000\u02fb\u02fc\u0001\u0000\u0000\u0000\u02fc\u02fd\u00051\u0000\u0000"+
		"\u02fd\u030e\u0001\u0000\u0000\u0000\u02fe\u0300\u0007\u0007\u0000\u0000"+
		"\u02ff\u02fe\u0001\u0000\u0000\u0000\u02ff\u0300\u0001\u0000\u0000\u0000"+
		"\u0300\u0301\u0001\u0000\u0000\u0000\u0301\u0302\u00054\u0000\u0000\u0302"+
		"\u0303\u00054\u0000\u0000\u0303\u0304\u0003P(\u0000\u0304\u0305\u0005"+
		"5\u0000\u0000\u0305\u0306\u00055\u0000\u0000\u0306\u0308\u00050\u0000"+
		"\u0000\u0307\u0309\u0003\u008cF\u0000\u0308\u0307\u0001\u0000\u0000\u0000"+
		"\u0308\u0309\u0001\u0000\u0000\u0000\u0309\u030a\u0001\u0000\u0000\u0000"+
		"\u030a\u030b\u00051\u0000\u0000\u030b\u030c\u0004=\u0012\u0000\u030c\u030e"+
		"\u0001\u0000\u0000\u0000\u030d\u02f1\u0001\u0000\u0000\u0000\u030d\u02ff"+
		"\u0001\u0000\u0000\u0000\u030e{\u0001\u0000\u0000\u0000\u030f\u0310\u0005"+
		"p\u0000\u0000\u0310\u0311\u00050\u0000\u0000\u0311\u0312\u0003P(\u0000"+
		"\u0312\u0313\u00051\u0000\u0000\u0313\u034a\u0001\u0000\u0000\u0000\u0314"+
		"\u0315\u0005o\u0000\u0000\u0315\u0316\u00050\u0000\u0000\u0316\u0317\u0003"+
		"P(\u0000\u0317\u0318\u00056\u0000\u0000\u0318\u0319\u0003P(\u0000\u0319"+
		"\u031a\u00051\u0000\u0000\u031a\u034a\u0001\u0000\u0000\u0000\u031b\u031c"+
		"\u0005x\u0000\u0000\u031c\u031d\u00050\u0000\u0000\u031d\u031e\u0003P"+
		"(\u0000\u031e\u031f\u00056\u0000\u0000\u031f\u0320\u0003P(\u0000\u0320"+
		"\u0321\u00051\u0000\u0000\u0321\u034a\u0001\u0000\u0000\u0000\u0322\u0323"+
		"\u0005w\u0000\u0000\u0323\u0324\u00050\u0000\u0000\u0324\u0325\u0003P"+
		"(\u0000\u0325\u0326\u00051\u0000\u0000\u0326\u034a\u0001\u0000\u0000\u0000"+
		"\u0327\u0328\u0005v\u0000\u0000\u0328\u0329\u00050\u0000\u0000\u0329\u032a"+
		"\u0003P(\u0000\u032a\u032b\u00051\u0000\u0000\u032b\u034a\u0001\u0000"+
		"\u0000\u0000\u032c\u032d\u0005t\u0000\u0000\u032d\u032e\u00050\u0000\u0000"+
		"\u032e\u032f\u0003P(\u0000\u032f\u0330\u00051\u0000\u0000\u0330\u034a"+
		"\u0001\u0000\u0000\u0000\u0331\u0332\u0005s\u0000\u0000\u0332\u0333\u0005"+
		"0\u0000\u0000\u0333\u0334\u0003P(\u0000\u0334\u0335\u00051\u0000\u0000"+
		"\u0335\u034a\u0001\u0000\u0000\u0000\u0336\u0337\u0005r\u0000\u0000\u0337"+
		"\u0338\u00050\u0000\u0000\u0338\u0339\u0003P(\u0000\u0339\u033a\u0005"+
		"1\u0000\u0000\u033a\u034a\u0001\u0000\u0000\u0000\u033b\u033c\u0005q\u0000"+
		"\u0000\u033c\u033d\u00050\u0000\u0000\u033d\u033e\u0003P(\u0000\u033e"+
		"\u033f\u00051\u0000\u0000\u033f\u034a\u0001\u0000\u0000\u0000\u0340\u0341"+
		"\u0005y\u0000\u0000\u0341\u0342\u00050\u0000\u0000\u0342\u034a\u00051"+
		"\u0000\u0000\u0343\u0344\u0005z\u0000\u0000\u0344\u0345\u00050\u0000\u0000"+
		"\u0345\u0346\u0003P(\u0000\u0346\u0347\u00051\u0000\u0000\u0347\u034a"+
		"\u0001\u0000\u0000\u0000\u0348\u034a\u0003~?\u0000\u0349\u030f\u0001\u0000"+
		"\u0000\u0000\u0349\u0314\u0001\u0000\u0000\u0000\u0349\u031b\u0001\u0000"+
		"\u0000\u0000\u0349\u0322\u0001\u0000\u0000\u0000\u0349\u0327\u0001\u0000"+
		"\u0000\u0000\u0349\u032c\u0001\u0000\u0000\u0000\u0349\u0331\u0001\u0000"+
		"\u0000\u0000\u0349\u0336\u0001\u0000\u0000\u0000\u0349\u033b\u0001\u0000"+
		"\u0000\u0000\u0349\u0340\u0001\u0000\u0000\u0000\u0349\u0343\u0001\u0000"+
		"\u0000\u0000\u0349\u0348\u0001\u0000\u0000\u0000\u034a}\u0001\u0000\u0000"+
		"\u0000\u034b\u034c\u0005u\u0000\u0000\u034c\u034d\u00050\u0000\u0000\u034d"+
		"\u034e\u0003P(\u0000\u034e\u034f\u00051\u0000\u0000\u034f\u0371\u0001"+
		"\u0000\u0000\u0000\u0350\u0351\u0005{\u0000\u0000\u0351\u0352\u00050\u0000"+
		"\u0000\u0352\u0353\u0003P(\u0000\u0353\u0354\u00051\u0000\u0000\u0354"+
		"\u0371\u0001\u0000\u0000\u0000\u0355\u0356\u0005|\u0000\u0000\u0356\u0357"+
		"\u00050\u0000\u0000\u0357\u0358\u0003P(\u0000\u0358\u0359\u00051\u0000"+
		"\u0000\u0359\u0371\u0001\u0000\u0000\u0000\u035a\u035b\u0005}\u0000\u0000"+
		"\u035b\u035c\u00050\u0000\u0000\u035c\u035d\u0003P(\u0000\u035d\u035e"+
		"\u00051\u0000\u0000\u035e\u0371\u0001\u0000\u0000\u0000\u035f\u0360\u0005"+
		"~\u0000\u0000\u0360\u0361\u00050\u0000\u0000\u0361\u0362\u0003P(\u0000"+
		"\u0362\u0363\u00051\u0000\u0000\u0363\u0371\u0001\u0000\u0000\u0000\u0364"+
		"\u0365\u0005\u007f\u0000\u0000\u0365\u0366\u00050\u0000\u0000\u0366\u0367"+
		"\u0003P(\u0000\u0367\u0368\u00051\u0000\u0000\u0368\u0371\u0001\u0000"+
		"\u0000\u0000\u0369\u036a\u0005\u0080\u0000\u0000\u036a\u036b\u00050\u0000"+
		"\u0000\u036b\u036c\u0003P(\u0000\u036c\u036d\u00056\u0000\u0000\u036d"+
		"\u036e\u0003P(\u0000\u036e\u036f\u00051\u0000\u0000\u036f\u0371\u0001"+
		"\u0000\u0000\u0000\u0370\u034b\u0001\u0000\u0000\u0000\u0370\u0350\u0001"+
		"\u0000\u0000\u0000\u0370\u0355\u0001\u0000\u0000\u0000\u0370\u035a\u0001"+
		"\u0000\u0000\u0000\u0370\u035f\u0001\u0000\u0000\u0000\u0370\u0364\u0001"+
		"\u0000\u0000\u0000\u0370\u0369\u0001\u0000\u0000\u0000\u0371\u007f\u0001"+
		"\u0000\u0000\u0000\u0372\u0373\u0003~?\u0000\u0373\u0374\u0003\u00a4R"+
		"\u0000\u0374\u0081\u0001\u0000\u0000\u0000\u0375\u0376\u0005.\u0000\u0000"+
		"\u0376\u0377\u00050\u0000\u0000\u0377\u0378\u0003P(\u0000\u0378\u0379"+
		"\u00051\u0000\u0000\u0379\u0083\u0001\u0000\u0000\u0000\u037a\u037b\u0005"+
		"/\u0000\u0000\u037b\u037c\u00050\u0000\u0000\u037c\u037d\u0003P(\u0000"+
		"\u037d\u037e\u00051\u0000\u0000\u037e\u0085\u0001\u0000\u0000\u0000\u037f"+
		"\u0381\u0003\u00bc^\u0000\u0380\u037f\u0001\u0000\u0000\u0000\u0380\u0381"+
		"\u0001\u0000\u0000\u0000\u0381\u0382\u0001\u0000\u0000\u0000\u0382\u0383"+
		"\u0005:\u0000\u0000\u0383\u0384\u0003\u00c0`\u0000\u0384\u0087\u0001\u0000"+
		"\u0000\u0000\u0385\u038a\u0003\u00c0`\u0000\u0386\u0387\u00056\u0000\u0000"+
		"\u0387\u0389\u0003\u00c0`\u0000\u0388\u0386\u0001\u0000\u0000\u0000\u0389"+
		"\u038c\u0001\u0000\u0000\u0000\u038a\u0388\u0001\u0000\u0000\u0000\u038a"+
		"\u038b\u0001\u0000\u0000\u0000\u038b\u038d\u0001\u0000\u0000\u0000\u038c"+
		"\u038a\u0001\u0000\u0000\u0000\u038d\u038e\u0004D\u0013\u0000\u038e\u0393"+
		"\u0001\u0000\u0000\u0000\u038f\u0390\u0003\u008aE\u0000\u0390\u0391\u0004"+
		"D\u0014\u0000\u0391\u0393\u0001\u0000\u0000\u0000\u0392\u0385\u0001\u0000"+
		"\u0000\u0000\u0392\u038f\u0001\u0000\u0000\u0000\u0393\u0089\u0001\u0000"+
		"\u0000\u0000\u0394\u0397\u0003\u00c0`\u0000\u0395\u0396\u0005L\u0000\u0000"+
		"\u0396\u0398\u0003P(\u0000\u0397\u0395\u0001\u0000\u0000\u0000\u0397\u0398"+
		"\u0001\u0000\u0000\u0000\u0398\u03a1\u0001\u0000\u0000\u0000\u0399\u039a"+
		"\u00056\u0000\u0000\u039a\u039d\u0003\u00c0`\u0000\u039b\u039c\u0005L"+
		"\u0000\u0000\u039c\u039e\u0003P(\u0000\u039d\u039b\u0001\u0000\u0000\u0000"+
		"\u039d\u039e\u0001\u0000\u0000\u0000\u039e\u03a0\u0001\u0000\u0000\u0000"+
		"\u039f\u0399\u0001\u0000\u0000\u0000\u03a0\u03a3\u0001\u0000\u0000\u0000"+
		"\u03a1\u039f\u0001\u0000\u0000\u0000\u03a1\u03a2\u0001\u0000\u0000\u0000"+
		"\u03a2\u008b\u0001\u0000\u0000\u0000\u03a3\u03a1\u0001\u0000\u0000\u0000"+
		"\u03a4\u03a9\u0003P(\u0000\u03a5\u03a6\u00056\u0000\u0000\u03a6\u03a8"+
		"\u0003P(\u0000\u03a7\u03a5\u0001\u0000\u0000\u0000\u03a8\u03ab\u0001\u0000"+
		"\u0000\u0000\u03a9\u03a7\u0001\u0000\u0000\u0000\u03a9\u03aa\u0001\u0000"+
		"\u0000\u0000\u03aa\u008d\u0001\u0000\u0000\u0000\u03ab\u03a9\u0001\u0000"+
		"\u0000\u0000\u03ac\u03ad\u00054\u0000\u0000\u03ad\u03b2\u0003\u0094J\u0000"+
		"\u03ae\u03af\u00056\u0000\u0000\u03af\u03b1\u0003\u0094J\u0000\u03b0\u03ae"+
		"\u0001\u0000\u0000\u0000\u03b1\u03b4\u0001\u0000\u0000\u0000\u03b2\u03b0"+
		"\u0001\u0000\u0000\u0000\u03b2\u03b3\u0001\u0000\u0000\u0000\u03b3\u03b5"+
		"\u0001\u0000\u0000\u0000\u03b4\u03b2\u0001\u0000\u0000\u0000\u03b5\u03b6"+
		"\u00055\u0000\u0000\u03b6\u008f\u0001\u0000\u0000\u0000\u03b7\u03b8\u0005"+
		"4\u0000\u0000\u03b8\u03b9\u0003\u008cF\u0000\u03b9\u03ba\u00055\u0000"+
		"\u0000\u03ba\u0091\u0001\u0000\u0000\u0000\u03bb\u03bc\u00050\u0000\u0000"+
		"\u03bc\u03bd\u0003P(\u0000\u03bd\u03be\u00051\u0000\u0000\u03be\u0093"+
		"\u0001\u0000\u0000\u0000\u03bf\u03c3\u0003\u00c0`\u0000\u03c0\u03c3\u0003"+
		"\u0096K\u0000\u03c1\u03c3\u0003\u0098L\u0000\u03c2\u03bf\u0001\u0000\u0000"+
		"\u0000\u03c2\u03c0\u0001\u0000\u0000\u0000\u03c2\u03c1\u0001\u0000\u0000"+
		"\u0000\u03c3\u0095\u0001\u0000\u0000\u0000\u03c4\u03c5\u0003\u009eO\u0000"+
		"\u03c5\u03c6\u00054\u0000\u0000\u03c6\u03c7\u0003P(\u0000\u03c7\u03c8"+
		"\u00055\u0000\u0000\u03c8\u0097\u0001\u0000\u0000\u0000\u03c9\u03ca\u0003"+
		"\u009cN\u0000\u03ca\u03cb\u00057\u0000\u0000\u03cb\u03cc\u0003\u00be_"+
		"\u0000\u03cc\u0099\u0001\u0000\u0000\u0000\u03cd\u03d5\u0003t:\u0000\u03ce"+
		"\u03d5\u0003\u00c0`\u0000\u03cf\u03d5\u0003\u00b0X\u0000\u03d0\u03d5\u0003"+
		"\u00b2Y\u0000\u03d1\u03d5\u0003\u00b4Z\u0000\u03d2\u03d5\u0003\u00b6["+
		"\u0000\u03d3\u03d5\u0003\u009cN\u0000\u03d4\u03cd\u0001\u0000\u0000\u0000"+
		"\u03d4\u03ce\u0001\u0000\u0000\u0000\u03d4\u03cf\u0001\u0000\u0000\u0000"+
		"\u03d4\u03d0\u0001\u0000\u0000\u0000\u03d4\u03d1\u0001\u0000\u0000\u0000"+
		"\u03d4\u03d2\u0001\u0000\u0000\u0000\u03d4\u03d3\u0001\u0000\u0000\u0000"+
		"\u03d5\u009b\u0001\u0000\u0000\u0000\u03d6\u03da\u0003t:\u0000\u03d7\u03d9"+
		"\u0003\u00a0P\u0000\u03d8\u03d7\u0001\u0000\u0000\u0000\u03d9\u03dc\u0001"+
		"\u0000\u0000\u0000\u03da\u03d8\u0001\u0000\u0000\u0000\u03da\u03db\u0001"+
		"\u0000\u0000\u0000\u03db\u040f\u0001\u0000\u0000\u0000\u03dc\u03da\u0001"+
		"\u0000\u0000\u0000\u03dd\u03e1\u0003\u00c0`\u0000\u03de\u03e0\u0003\u00a0"+
		"P\u0000\u03df\u03de\u0001\u0000\u0000\u0000\u03e0\u03e3\u0001\u0000\u0000"+
		"\u0000\u03e1\u03df\u0001\u0000\u0000\u0000\u03e1\u03e2\u0001\u0000\u0000"+
		"\u0000\u03e2\u040f\u0001\u0000\u0000\u0000\u03e3\u03e1\u0001\u0000\u0000"+
		"\u0000\u03e4\u03e6\u0003\u00b0X\u0000\u03e5\u03e7\u0003\u00a4R\u0000\u03e6"+
		"\u03e5\u0001\u0000\u0000\u0000\u03e7\u03e8\u0001\u0000\u0000\u0000\u03e8"+
		"\u03e6\u0001\u0000\u0000\u0000\u03e8\u03e9\u0001\u0000\u0000\u0000\u03e9"+
		"\u03ed\u0001\u0000\u0000\u0000\u03ea\u03ec\u0003\u00a0P\u0000\u03eb\u03ea"+
		"\u0001\u0000\u0000\u0000\u03ec\u03ef\u0001\u0000\u0000\u0000\u03ed\u03eb"+
		"\u0001\u0000\u0000\u0000\u03ed\u03ee\u0001\u0000\u0000\u0000\u03ee\u040f"+
		"\u0001\u0000\u0000\u0000\u03ef\u03ed\u0001\u0000\u0000\u0000\u03f0\u03f2"+
		"\u0003\u00b2Y\u0000\u03f1\u03f3\u0003\u00a0P\u0000\u03f2\u03f1\u0001\u0000"+
		"\u0000\u0000\u03f3\u03f4\u0001\u0000\u0000\u0000\u03f4\u03f2\u0001\u0000"+
		"\u0000\u0000\u03f4\u03f5\u0001\u0000\u0000\u0000\u03f5\u040f\u0001\u0000"+
		"\u0000\u0000\u03f6\u03f8\u0003\u00b4Z\u0000\u03f7\u03f9\u0003\u00a6S\u0000"+
		"\u03f8\u03f7\u0001\u0000\u0000\u0000\u03f9\u03fa\u0001\u0000\u0000\u0000"+
		"\u03fa\u03f8\u0001\u0000\u0000\u0000\u03fa\u03fb\u0001\u0000\u0000\u0000"+
		"\u03fb\u03ff\u0001\u0000\u0000\u0000\u03fc\u03fe\u0003\u00a0P\u0000\u03fd"+
		"\u03fc\u0001\u0000\u0000\u0000\u03fe\u0401\u0001\u0000\u0000\u0000\u03ff"+
		"\u03fd\u0001\u0000\u0000\u0000\u03ff\u0400\u0001\u0000\u0000\u0000\u0400"+
		"\u040f\u0001\u0000\u0000\u0000\u0401\u03ff\u0001\u0000\u0000\u0000\u0402"+
		"\u0404\u0003\u00b6[\u0000\u0403\u0405\u0003\u00a6S\u0000\u0404\u0403\u0001"+
		"\u0000\u0000\u0000\u0405\u0406\u0001\u0000\u0000\u0000\u0406\u0404\u0001"+
		"\u0000\u0000\u0000\u0406\u0407\u0001\u0000\u0000\u0000\u0407\u040b\u0001"+
		"\u0000\u0000\u0000\u0408\u040a\u0003\u00a0P\u0000\u0409\u0408\u0001\u0000"+
		"\u0000\u0000\u040a\u040d\u0001\u0000\u0000\u0000\u040b\u0409\u0001\u0000"+
		"\u0000\u0000\u040b\u040c\u0001\u0000\u0000\u0000\u040c\u040f\u0001\u0000"+
		"\u0000\u0000\u040d\u040b\u0001\u0000\u0000\u0000\u040e\u03d6\u0001\u0000"+
		"\u0000\u0000\u040e\u03dd\u0001\u0000\u0000\u0000\u040e\u03e4\u0001\u0000"+
		"\u0000\u0000\u040e\u03f0\u0001\u0000\u0000\u0000\u040e\u03f6\u0001\u0000"+
		"\u0000\u0000\u040e\u0402\u0001\u0000\u0000\u0000\u040f\u009d\u0001\u0000"+
		"\u0000\u0000\u0410\u0414\u0003\u00c0`\u0000\u0411\u0413\u0003\u00a2Q\u0000"+
		"\u0412\u0411\u0001\u0000\u0000\u0000\u0413\u0416\u0001\u0000\u0000\u0000"+
		"\u0414\u0412\u0001\u0000\u0000\u0000\u0414\u0415\u0001\u0000\u0000\u0000"+
		"\u0415\u0442\u0001\u0000\u0000\u0000\u0416\u0414\u0001\u0000\u0000\u0000"+
		"\u0417\u0419\u0003\u00b0X\u0000\u0418\u041a\u0003\u00a4R\u0000\u0419\u0418"+
		"\u0001\u0000\u0000\u0000\u041a\u041b\u0001\u0000\u0000\u0000\u041b\u0419"+
		"\u0001\u0000\u0000\u0000\u041b\u041c\u0001\u0000\u0000\u0000\u041c\u0420"+
		"\u0001\u0000\u0000\u0000\u041d\u041f\u0003\u00a2Q\u0000\u041e\u041d\u0001"+
		"\u0000\u0000\u0000\u041f\u0422\u0001\u0000\u0000\u0000\u0420\u041e\u0001"+
		"\u0000\u0000\u0000\u0420\u0421\u0001\u0000\u0000\u0000\u0421\u0442\u0001"+
		"\u0000\u0000\u0000\u0422\u0420\u0001\u0000\u0000\u0000\u0423\u0425\u0003"+
		"\u00b2Y\u0000\u0424\u0426\u0003\u00a2Q\u0000\u0425\u0424\u0001\u0000\u0000"+
		"\u0000\u0426\u0427\u0001\u0000\u0000\u0000\u0427\u0425\u0001\u0000\u0000"+
		"\u0000\u0427\u0428\u0001\u0000\u0000\u0000\u0428\u0442\u0001\u0000\u0000"+
		"\u0000\u0429\u042b\u0003\u00b4Z\u0000\u042a\u042c\u0003\u00a6S\u0000\u042b"+
		"\u042a\u0001\u0000\u0000\u0000\u042c\u042d\u0001\u0000\u0000\u0000\u042d"+
		"\u042b\u0001\u0000\u0000\u0000\u042d\u042e\u0001\u0000\u0000\u0000\u042e"+
		"\u0432\u0001\u0000\u0000\u0000\u042f\u0431\u0003\u00a2Q\u0000\u0430\u042f"+
		"\u0001\u0000\u0000\u0000\u0431\u0434\u0001\u0000\u0000\u0000\u0432\u0430"+
		"\u0001\u0000\u0000\u0000\u0432\u0433\u0001\u0000\u0000\u0000\u0433\u0442"+
		"\u0001\u0000\u0000\u0000\u0434\u0432\u0001\u0000\u0000\u0000\u0435\u0437"+
		"\u0003\u00b6[\u0000\u0436\u0438\u0003\u00a6S\u0000\u0437\u0436\u0001\u0000"+
		"\u0000\u0000\u0438\u0439\u0001\u0000\u0000\u0000\u0439\u0437\u0001\u0000"+
		"\u0000\u0000\u0439\u043a\u0001\u0000\u0000\u0000\u043a\u043e\u0001\u0000"+
		"\u0000\u0000\u043b\u043d\u0003\u00a2Q\u0000\u043c\u043b\u0001\u0000\u0000"+
		"\u0000\u043d\u0440\u0001\u0000\u0000\u0000\u043e\u043c\u0001\u0000\u0000"+
		"\u0000\u043e\u043f\u0001\u0000\u0000\u0000\u043f\u0442\u0001\u0000\u0000"+
		"\u0000\u0440\u043e\u0001\u0000\u0000\u0000\u0441\u0410\u0001\u0000\u0000"+
		"\u0000\u0441\u0417\u0001\u0000\u0000\u0000\u0441\u0423\u0001\u0000\u0000"+
		"\u0000\u0441\u0429\u0001\u0000\u0000\u0000\u0441\u0435\u0001\u0000\u0000"+
		"\u0000\u0442\u009f\u0001\u0000\u0000\u0000\u0443\u0444\u00054\u0000\u0000"+
		"\u0444\u0445\u0003P(\u0000\u0445\u0446\u00055\u0000\u0000\u0446\u044b"+
		"\u0001\u0000\u0000\u0000\u0447\u0448\u00057\u0000\u0000\u0448\u044b\u0003"+
		"\u00be_\u0000\u0449\u044b\u0003t:\u0000\u044a\u0443\u0001\u0000\u0000"+
		"\u0000\u044a\u0447\u0001\u0000\u0000\u0000\u044a\u0449\u0001\u0000\u0000"+
		"\u0000\u044b\u00a1\u0001\u0000\u0000\u0000\u044c\u044d\u00054\u0000\u0000"+
		"\u044d\u044e\u0003P(\u0000\u044e\u044f\u00055\u0000\u0000\u044f\u0453"+
		"\u0001\u0000\u0000\u0000\u0450\u0451\u00057\u0000\u0000\u0451\u0453\u0003"+
		"\u00be_\u0000\u0452\u044c\u0001\u0000\u0000\u0000\u0452\u0450\u0001\u0000"+
		"\u0000\u0000\u0453\u00a3\u0001\u0000\u0000\u0000\u0454\u0455\u00054\u0000"+
		"\u0000\u0455\u0456\u0003P(\u0000\u0456\u0457\u00055\u0000\u0000\u0457"+
		"\u00a5\u0001\u0000\u0000\u0000\u0458\u0459\u00057\u0000\u0000\u0459\u045a"+
		"\u0003\u00be_\u0000\u045a\u00a7\u0001\u0000\u0000\u0000\u045b\u045e\u0003"+
		"\u009aM\u0000\u045c\u045e\u0003\u00c6c\u0000\u045d\u045b\u0001\u0000\u0000"+
		"\u0000\u045d\u045c\u0001\u0000\u0000\u0000\u045e\u045f\u0001\u0000\u0000"+
		"\u0000\u045f\u0460\u00057\u0000\u0000\u0460\u0461\u0005)\u0000\u0000\u0461"+
		"\u00a9\u0001\u0000\u0000\u0000\u0462\u0463\u0005$\u0000\u0000\u0463\u00ab"+
		"\u0001\u0000\u0000\u0000\u0464\u0465\u00054\u0000\u0000\u0465\u0466\u0005"+
		"5\u0000\u0000\u0466\u00ad\u0001\u0000\u0000\u0000\u0467\u0468\u0005(\u0000"+
		"\u0000\u0468\u00af\u0001\u0000\u0000\u0000\u0469\u046a\u0005*\u0000\u0000"+
		"\u046a\u00b1\u0001\u0000\u0000\u0000\u046b\u046c\u0005+\u0000\u0000\u046c"+
		"\u00b3\u0001\u0000\u0000\u0000\u046d\u046e\u0005,\u0000\u0000\u046e\u00b5"+
		"\u0001\u0000\u0000\u0000\u046f\u0470\u0005-\u0000\u0000\u0470\u00b7\u0001"+
		"\u0000\u0000\u0000\u0471\u0472\u0005\u0007\u0000\u0000\u0472\u00b9\u0001"+
		"\u0000\u0000\u0000\u0473\u0474\u00050\u0000\u0000\u0474\u0475\u0003P("+
		"\u0000\u0475\u0476\u00056\u0000\u0000\u0476\u0477\u0003P(\u0000\u0477"+
		"\u0478\u00056\u0000\u0000\u0478\u0479\u0003P(\u0000\u0479\u047a\u0005"+
		"1\u0000\u0000\u047a\u00bb\u0001\u0000\u0000\u0000\u047b\u047c\u0007\b"+
		"\u0000\u0000\u047c\u00bd\u0001\u0000\u0000\u0000\u047d\u047e\u0007\t\u0000"+
		"\u0000\u047e\u00bf\u0001\u0000\u0000\u0000\u047f\u0480\u0007\n\u0000\u0000"+
		"\u0480\u00c1\u0001\u0000\u0000\u0000\u0481\u0482\u0005c\u0000\u0000\u0482"+
		"\u00c3\u0001\u0000\u0000\u0000\u0483\u0484\u0005b\u0000\u0000\u0484\u00c5"+
		"\u0001\u0000\u0000\u0000\u0485\u0486\u0005a\u0000\u0000\u0486\u00c7\u0001"+
		"\u0000\u0000\u0000\u0487\u0488\u0005_\u0000\u0000\u0488\u00c9\u0001\u0000"+
		"\u0000\u0000\u0489\u048a\u0005`\u0000\u0000\u048a\u00cb\u0001\u0000\u0000"+
		"\u0000\u048b\u048c\u0005\'\u0000\u0000\u048c\u00cd\u0001\u0000\u0000\u0000"+
		"\u048d\u048e\u0005&\u0000\u0000\u048e\u00cf\u0001\u0000\u0000\u0000^\u00d4"+
		"\u00d6\u00ea\u00fa\u0101\u0106\u010c\u0138\u013d\u0141\u0143\u0147\u014d"+
		"\u0154\u016b\u017a\u0185\u018d\u0194\u01a3\u01b6\u01ba\u01be\u01c8\u01d8"+
		"\u01e7\u01f1\u01f9\u0201\u0209\u0211\u0229\u0233\u023a\u0242\u024a\u0252"+
		"\u025a\u0262\u026a\u0272\u027a\u0282\u028a\u0298\u02c4\u02c8\u02cd\u02d0"+
		"\u02d5\u02da\u02df\u02e4\u02e9\u02ee\u02f1\u02fa\u02ff\u0308\u030d\u0349"+
		"\u0370\u0380\u038a\u0392\u0397\u039d\u03a1\u03a9\u03b2\u03c2\u03d4\u03da"+
		"\u03e1\u03e8\u03ed\u03f4\u03fa\u03ff\u0406\u040b\u040e\u0414\u041b\u0420"+
		"\u0427\u042d\u0432\u0439\u043e\u0441\u044a\u0452\u045d";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}