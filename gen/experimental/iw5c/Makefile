generate: iw5c

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

iw5c: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../../src/experimental/iw5c/xsk/
