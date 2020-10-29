generate: iw6

clean:
	rm -rf ./IW6

copy:
	mv -f ./IW6/* ../src/IW6/

iw6: iw6.lexer.lpp iw6.parser.ypp
	mkdir -p ./IW6
	flex iw6.lexer.lpp
	bison iw6.parser.ypp
	touch ./IW6
	