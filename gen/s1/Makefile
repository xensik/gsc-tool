generate: S1

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

S1: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/s1/xsk/
