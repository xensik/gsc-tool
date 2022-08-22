generate: s2

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

s2: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/s2/xsk/
