generate: IW6

clean:
	rm -rf ./IW5
	rm -rf ./IW6
	rm -rf ./S1
	rm -rf ./S2
	rm -rf ./H1
	rm -rf ./H2

copy-IW5:
	mv -f ./IW5/* ../../IW5/

copy-IW6:
	mv -f ./IW6/* ../../IW6/

copy-S1:
	mv -f ./S1/* ../../S1/

copy-S2:
	mv -f ./S2/* ../../S2/

copy-H1:
	mv -f ./H1/* ../../H1/

copy-H2:
	mv -f ./H2/* ../../H2/

IW5: IW5.lexer.lpp IW5.parser.ypp
	mkdir -p ./IW5
	flex IW5.lexer.lpp
	bison IW5.parser.ypp
	touch ./IW5

IW6: IW6.lexer.lpp IW6.parser.ypp
	mkdir -p ./IW6
	flex IW6.lexer.lpp
	bison IW6.parser.ypp
	touch ./IW6

S1: S1.lexer.lpp S1.parser.ypp
	mkdir -p ./S1
	flex S1.lexer.lpp
	bison S1.parser.ypp
	touch ./S1

S2: S2.lexer.lpp S2.parser.ypp
	mkdir -p ./S2
	flex S2.lexer.lpp
	bison S2.parser.ypp
	touch ./S2

H1: H1.lexer.lpp H1.parser.ypp
	mkdir -p ./H1
	flex H1.lexer.lpp
	bison H1.parser.ypp
	touch ./H1

H2: H2.lexer.lpp H2.parser.ypp
	mkdir -p ./H2
	flex H2.lexer.lpp
	bison H2.parser.ypp
	touch ./H2
