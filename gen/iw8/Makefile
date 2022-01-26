generate: IW8

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

IW8: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/iw8/xsk/
