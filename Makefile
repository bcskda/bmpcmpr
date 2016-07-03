linux:
	if [ ! -d build/linux ]; then mkdir -p build/linux ; fi
	gcc -o build/linux/bmp-compr-main -std=gnu99 src/bmp-compr-main.c
	gcc -o build/linux/bmp-decompr-main -std=gnu99 src/bmp-decompr-main.c
	cp src/bmp-compr.sh build/linux/bmp-compr.sh
	chmod +x build/linux/*

windows:
	if [ ! -d build/windows ]; then mkdir -p build/windows; fi
	gcc -o build/windows/bmp-compr-main -std=gnu99 src/bmp-compr-main.c
	gcc -o build/windows/bmp-decompr-main -std=gnu99 src/bmp-decompr-main.c
	gcc -o build/windows/bmp-compr -std=gnu99 src/bmp-compr-win.c
	chmod +x build/windows/*

clean:
	rm -r build/*
