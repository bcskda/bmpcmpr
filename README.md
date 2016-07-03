# bmpcmpr
A simple C-written .bmp compression and decompression utility.

For now works only with 16bit image/bmp.
# Dependencies:
gcc
### Windows special:
MinGW *(only for building)*
# Installation
### Linux:
```sh
git clone bcskda/bmpcmpr
cd bmpcmpr
make linux
```
### Windows:
```sh
git clone bcskda/bmpcmpr
cd bmpcmpr
make windows
```
# Usage:
```sh
$ bmp-compr [-h] [ -i | -m mode -s source [-o output] ]
```
-h: Display help and exit

-i: Enter arguments in running front-end

-m mode: Set mode: [c]ompress/[d]ecompress

-s source: Set source file

-o output: Set output file
