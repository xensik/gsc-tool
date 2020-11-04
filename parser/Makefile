generate: IW6

clean:
	rm -rf ./IW5
	rm -rf ./IW6
	rm -rf ./SH1

copy-IW5:
	mv -f ./IW5/* ../src/IW5/

copy-IW6:
	mv -f ./IW6/* ../src/IW6/

copy-SH1:
	mv -f ./SH1/* ../src/SH1/

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

SH1: SH1.lexer.lpp SH1.parser.ypp
	mkdir -p ./SH1
	flex SH1.lexer.lpp
	bison SH1.parser.ypp
	touch ./SH1
