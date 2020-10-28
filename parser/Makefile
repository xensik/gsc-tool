
clean:
	rm -rf ./iw6

iw6: iw6.lexer.lpp iw6.parser.ypp
	mkdir -p ./iw6
	flex --header-file=./iw6/lexer.hpp --outfile=./iw6/lexer.cpp iw6.lexer.lpp
	bison --defines=./iw6/parser.hpp --output=./iw6/parser.cpp iw6.parser.ypp
	touch ./iw6