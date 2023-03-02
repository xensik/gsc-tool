generate: gsc

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

gsc: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp ../../include/xsk/gsc/
	mv parser.cpp ../../src/gsc/
