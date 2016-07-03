#include "bmp.h"

void compress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int fsize);

const int MASK_FLAG = 0x8000;

int main (const int argc, const char* argv[]) {
  /*
  FILE *T = fopen ("/home/kda/Git/test", "w");
  fprintf (T, "%s; %s; %s; %s", argv[0], argv[1], argv[2], argv[3]);
  fclose (T);
  */

  int err = 0;
  FILE *Source = 0, *Output = 0;
  openFiles (&Source, argv[2], &Output, argv[3]);

	int offBits = 0, fsize = 0;
	char *Headers = 0;
    err = readMeta (Source, 'c', &Headers, &offBits, &fsize);
    if (err) {
		return err;
	}

    compress (Source, Output, Headers, offBits, fsize);

    fclose (Source);
    fclose (Output);
    return 0;
}

void compress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int fsize) {
	fseek (Output, 0, SEEK_SET);//Printing all read headers except type signature into Output
	fprintf (Output, "CM");//New type signature: "CM"
	fwrite (Headers, sizeof(char), offBits-2, Output);//Spaces and over 'stop-symbols' possible

	fseek (Input, offBits, SEEK_SET);
	int spree = 1, fsize_new = 0;
  int ccolor = 0, ncolor = 0;
	fread (&ccolor, SIZE_WORD, 1, Input);

	for (int i = 1; i < fsize; i+=1) {
		fread (&ncolor, SIZE_WORD, 1, Input);
		if ((ncolor != ccolor) || (spree == MASK_FLAG-1)) {//Maximal int without using reserved 15th bit
			if (spree > 1) {
				spree |= MASK_FLAG;
        fwrite (&spree, SIZE_WORD, 1, Output);
        fwrite (&ccolor, SIZE_WORD, 1, Output);
			}
			else {
        fwrite (&ccolor, SIZE_WORD, 1, Output);
			}
			ccolor = ncolor;
			spree = 1;
      fsize_new+=1;
		}
		else {
			spree+=1;
		}
	}
  fwrite (&fsize_new, sizeof(int), 1, Output);
  printf ("New fsize: %d\n", fsize_new);
}
