#bin/bash
main="./bmpcmpr_main"
ifile="bmpcmpr-i.bmp"
ofile="bmpcmpr-o"
def=0

echo "Use default files? (\"$ifile\", \"$ofile\")? Y/N"
read def
if [ $def = N ]; then
 echo "Enter input filename (short).. "
 read ifile
 echo "Enter output filename (short).. "
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
