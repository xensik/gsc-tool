generate: iw6c

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

iw6c: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../../src/experimental/iw6c/xsk/
