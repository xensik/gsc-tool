generate: arc

clean:
	rm -rf ./parser.hpp
	rm -rf ./parser.cpp

arc: parser.ypp
	bison parser.ypp -Wcounterexamples
	mv parser.hpp ../../include/xsk/arc/
	mv parser.cpp ../../src/arc/
