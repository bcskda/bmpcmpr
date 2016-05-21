# bmpcmpr
A simple C-written .bmp compression and decompression utility.

For now works only with 16bit .bmp.
# Dependencies:
gcc compiler
# Installation
```sh
git clone bcskda/bmpcmpr
cd bmpcmpr
make default
```
# Usage:
```sh
$ bmp-compr [-h] [ -i | -m mode -s source [-o output] ]
```
-h: Display help

-i: Use post-launch interface

-m mode: Set mode: [c]ompress/[d]ecompress

-s source: Set source file

-o output: Set output file
