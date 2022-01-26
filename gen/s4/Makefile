generate: S4

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

S4: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/s4/xsk/
