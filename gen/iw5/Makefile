generate: iw5

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

iw5: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/iw5/xsk/
