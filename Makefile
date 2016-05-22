default:
	if [ -d build ]; then mkdir build; fi
	gcc -o build/bmp-compr-main -std=gnu99 src/bmp-compr-main.c
	gcc -o build/bmp-decompr-main -std=gnu99 src/bmp-decompr-main.c
	cp src/bmp-compr.sh build/bmp-compr
	chmod +x bin/*

clean:
	rm -r bin/
