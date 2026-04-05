
// Generated from gsc_iw_grammar.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  gsc_iw_grammarLexer : public antlr4::Lexer {
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

  explicit gsc_iw_grammarLexer(antlr4::CharStream *input);

  ~gsc_iw_grammarLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

