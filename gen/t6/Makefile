generate: t6

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

t6: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/t6/xsk/
