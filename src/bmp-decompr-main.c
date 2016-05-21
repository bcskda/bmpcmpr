#include "bmp.h"

void deCompress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int fsize);

const int MASK_FLAG = 0x8000;

int main (const int argnum, const char* args[]) {
    int err = 0;
    FILE *Source = 0, *Output = 0;
    openFiles (&Source, args[2], &Output, args[3]);

	int offBits = 0, width = 0, height = 0, fsize = 0;
	char *Headers = 0;
    err = readMeta (Source, 'd', &Headers, &offBits, &fsize);
    if (err) {
		return err;
	}

  deCompress (Source, Output, Headers, offBits, fsize);

  fclose (Source);
  fclose (Output);
  return 0;
}

void deCompress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int fsize) {
  fseek (Output, 0, SEEK_SET);//Printing all read headers except type signature into Output
	fprintf (Output, "BM");//Setting type signature: "BM"
	fwrite (Headers, sizeof(char), offBits-2, Output);
	fseek (Input, offBits, SEEK_SET);
	int spree = 0;
	int ncolor = 0;
  printf ("fsize: %d\n", fsize);
  for (int i = 1; i < fsize-1; i+=1) { //New file`s size is different.
		fread (&ncolor, SIZE_WORD, 1, Input);
    if (ncolor&MASK_FLAG) {
      spree = ncolor&(MASK_FLAG-1);
      fread (&ncolor, SIZE_WORD, 1, Input);
      for (int j = 0; j < spree; j+=1) { //Replace with this to get some lulz: for(int j = 0; j < spree; j+=1)
        fwrite (&ncolor, SIZE_WORD, 1, Output);
      }
    }
    else {
      fwrite (&ncolor, SIZE_WORD, 1, Output);
    }
	}
}
