generate: IW8

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp
	rm -rf ./lexer.hpp
	rm -rf ./lexer.cpp

IW8: lexer.lpp parser.ypp
	flex lexer.lpp
	bison parser.ypp -Wcounterexamples
	mv lexer.hpp lexer.cpp parser.hpp parser.cpp ../../src/iw8/xsk/
