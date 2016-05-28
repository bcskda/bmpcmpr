linux:
	if [ ! -d build/linux ]; then mkdir -p build/linux ; fi
	gcc -o build/bmp-compr-main -std=gnu99 src/bmp-compr-main.c
	gcc -o build/bmp-decompr-main -std=gnu99 src/bmp-decompr-main.c
	cp src/bmp-compr.sh build/bmp-compr
	chmod +x build/linux*

windows:
	if [ ! -d build/windows ]; then mkdir -p build/windows; fi
	gcc -o build/bmp-compr-main -std=gnu99 src/bmp-compr-main.c
	gcc -o build/bmp-decompr-main -std=gnu99 src/bmp-decompr-main.c
	gcc -o build/bmp-compr -std=gnu99 src/bmp-compr-win.c
	chmod +x build/windows*

clean:
	rm -r build/
