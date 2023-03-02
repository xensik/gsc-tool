generate: t6

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

t6: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp ../../include/xsk/t6/
	mv parser.cpp ../../src/t6/
