generate: H2

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

H2: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/h2/xsk/
