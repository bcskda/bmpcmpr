#include <stdio.h>
#include <unistd.h>

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
  const char *argv[4] = {"bmp-compr-*", "3", source, output};
  char mode = 0;
  int modeok = 0;
  do {
    printf ("Enter mode: [c]ompression/[d]ecompression...\n");
    scanf ("%c", &mode);
    switch (mode) {
      case 'c': case 'C':
        modeok = 1;
        printf ("Compression\n");
        execv (compr, argv);
        break;
      case 'd': case 'D':
        modeok = 1;
        printf ("Decompression\n");
        execv (decompr, argv);
        break;
      default:
        printf ("Error: invalid mode. ");
    }

  } while (! modeok);
}
