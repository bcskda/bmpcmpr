#!bin/bash
main="./bmp-compr-main"
ifile="bmp-compr-s.bmp"
ofile="bmp-compr-o"
def=0

# echo $# : $@

if [ $1 = "-i" ]; then

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
  $main 3 $ifile $ofile
 else
  echo "Output file $ofile already exists. Overwrite? Y/N"
  rewrt=0
  read rewrt
  if [ $rewrt = Y ]; then
   fin=1
   echo "Rewriting output file."
   $main 3 $ifile $ofile
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

if [ $# = "1" ]; then
 ifile=$1
else
 if [ $# = "2" ]; then
 if [ $1 = "-s" ]; then
  ifile=$2
 else
  echo "Error: unknown key $1"
 fi
 else
  if [ $# = "4" ]; then
   f=0
   for x in $@
   do
    case $f in
     0) if [ $x = "-s" ]; then
         f=s
        fi
        if [ $x = "-o" ]; then
         f=o
        fi;;
     s) ifile=$x
        f=0;;
     o) ofile=$x
        f=0;;
    esac
   done
  else
   echo "Error: wrong number of arguments"
  fi
 fi
fi

exec $main 3 $ifile $ofile

fi
