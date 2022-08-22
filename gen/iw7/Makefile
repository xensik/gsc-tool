generate: iw7

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

iw7: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/iw7/xsk/
