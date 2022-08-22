generate: h1

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

h1: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/h1/xsk/
