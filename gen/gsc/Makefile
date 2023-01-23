generate: gsc

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

gsc: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/gsc/
