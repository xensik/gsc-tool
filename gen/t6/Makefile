generate: T6

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

T6: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/t6/xsk/
