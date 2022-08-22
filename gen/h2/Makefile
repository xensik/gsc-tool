generate: h2

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

h2: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp parser.cpp ../../src/h2/xsk/
