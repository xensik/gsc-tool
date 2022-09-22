generate: iw9

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

iw9: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/iw9/xsk/
