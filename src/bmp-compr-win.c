#include <stdio.h>
#include <unistd.h>
#include <errno.h>

const int FILENAMELEN = 60;
const char *compr = "bmp-compr-main", *decompr = "bmp-decompr-main";

int main () {
  printf ("Enter full filenames.\n");
  char *source = (char*) calloc (sizeof(char), FILENAMELEN),
       *output = (char*) calloc (sizeof(char), FILENAMELEN);
       printf ("Enter source filename... ");
  scanf("%s", source);
  printf ("Enter output filename... ");
  scanf("%s", output);
  printf ("Warning: files dont't possibly exist\n");
  printf ("%s; %s\n", source, output);
  char mode;
  int modeok = 0;
  while (! modeok) {
    printf ("Enter mode: [c]ompression/[d]ecompression... ");
    scanf ("%c", &mode);
    const char *argv[4] = {"bmp-compr-*", "3", source, output};
    if (mode == 'c') {
      modeok = 1;
      printf ("Compression\n");
      execv (compr, argv);
    }
    else {
      if (mode == 'd') {
        modeok = 1;
        printf ("Decompression\n");
        execv (decompr, argv);
      }
      else {
        printf ("Error: incorrect mode");
      }
    }
  }
}
