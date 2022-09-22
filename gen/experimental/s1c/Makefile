generate: s1c

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

s1c: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../../src/experimental/s1c/xsk/
