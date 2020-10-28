generate: iw6

clean:
	rm -f lexer.cpp lexer.hpp parser.cpp parser.hpp

iw6: iw6.lexer.lpp iw6.parser.ypp
	flex iw6.lexer.lpp
	bison iw6.parser.ypp
	