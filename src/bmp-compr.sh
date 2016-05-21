#!/bin/bash
compr="./bmp-compr-main"
dcompr="./bmp-decompr-main"
ifile="bmp-compr-s.bmp"
ofile="bmp-compr-o"
mode=c
def=0

if [ $1 = "-h" ]; then
  echo "A simple .bmp compression utility."
  echo "Usage:"
  echo "  bmp-compr [-h] [-i | -m mode -s source [ -o output]]"
  echo "Arguments:"
  echo "  -h: Display this help"
  echo "  -i: Use post-launch interface - must be the only key"
  echo "  -m mode: Set mode: [c]ompress/[d]ecompress"
  echo "  -s source: Set source file"
  echo "  -o output: Set output file"

else

if [ $1 = "-i" ]; then
  echo "Compress or decompress? c/d"
  read mode
  echo "Use default files? (\"$ifile\", \"$ofile\")? Y/N"
  read def
  if [ $def = N ]; then
    echo "All filenames from this directory: ./input -> input"
    echo "Enter input filename.. "
    read ifile
    echo "Enter output filename.. "
    read ofile
  fi
  if [ -f $ifile ]; then
    if ! [ -f $ofile ]; then
      if [ $mode = c ]; then
        $compr 3 $ifile $ofile
      else
        $dcompr 3 $ifile $ofile
      fi
    else
      echo "Output file $ofile already exists. Overecho? Y/N"
      rewrt=0
      read rewrt
      if [ $rewrt = Y ]; then
        fin=1
        echo "Rewriting output file."
        if [ $mode = c ]; then
          $compr 3 $ifile $ofile
        else
          $dcompr 3 $ifile $ofile
        fi
      else
        echo "Error: cannot overwrite existing file. Choose another filename. Exiting in 5 sec."
        fin=1
        sleep 5
        exit 2
      fi
    fi
  else
    echo "Error: input file does not exist. Choose another filename. Exiting in 5 sec."
    sleep 5
    exit 1
  fi
  echo "Done. Result in ./$ofile. Exiting in 5 sec."
  sleep 5

else
  if [ $# = 1 ]; then
    $ifile=1
  else
    flag=0
    for x in $@
    do
      case $flag in
        0) if [ $x = "-s" ]; then
           flag=s
           fi
           if [ $x = "-o" ]; then
             flag=o
           fi
           if [ $x = "-m" ]; then
             flag=m
           fi;;
        s) ifile=$x
           flag=0;;
        o) ofile=$x
           flag=0;;
        m) mode=$x
           flag=0;;
      esac
    done
  fi
  if [ $mode = c ]; then
    $compr 3 $ifile $ofile
  else
    $dcompr 3 $ifile $ofile
  fi

fi

fi
