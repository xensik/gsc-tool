generate: IW6

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

IW6: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/iw6/xsk/
