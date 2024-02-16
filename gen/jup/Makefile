generate: arc

clean:
	rm -rf ./parser2.hpp
	rm -rf ./parser2.cpp

arc: parser.ypp
	bison parser2.ypp -Wcounterexamples
	mv parser2.hpp ../../include/xsk/arc/
	mv parser2.cpp ../../src/arc/
