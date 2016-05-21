#include <stdio.h>
#include <stdlib.h>

const int BISIZE_CORE = 12, BISIZE_V3 = 40, BISIZE_V4 = 108, BISIZE_V5 = 124,
		  SIZE_DWORD = 4, SIZE_WORD = 2, BIBITCOUNT = 16;

void openFiles (FILE **input, const char *input_name, FILE **output, const char *output_name);
int readMeta (FILE *Input, int mode, char **Headers, int *bfOffBits, int *fsize);

int readMeta (FILE *Input, int mode, char **Headers, int *bfOffBits, int *fsize) {
	fseek (Input, 0, SEEK_SET);
	char f1 = getc(Input), f2 = getc(Input);
	//printf ("%c%c(%d%d)/%c%c(%d%d)", f1,f2,f1,f2,'C','M','C','M');
	switch (mode) {
		case 'c': if (! (f1=='B' && f2=='M') ) {
								printf ("Error 0x1: undefined type signature. Expected \"BM\"\n");
								return 1;
							} break;
		case 'd': if (! (f1=='C' && f2=='M') ) {
								printf ("Error 0x1: undefined type signature. Expected \"CM\"\n");
								return 1;
							} break;
		default: return 1; break;
		}
	int bfSize = 0; fread (&bfSize, SIZE_DWORD, 1, Input);
	fseek (Input, 2*SIZE_WORD, SEEK_CUR); //Skipping struct`s reserved variables
	fread (bfOffBits, SIZE_DWORD, 1, Input);
	int biSize = 0; fread (&biSize, SIZE_DWORD, 1, Input);
	int biHeight, biWidth = 0;
	if (biSize == BISIZE_CORE) { //Used instead of switch
		fread (&biWidth, SIZE_WORD, 1, Input);
		fread (&biHeight, SIZE_WORD, 1, Input);
	}
	else {
		if (biSize == BISIZE_V3 || biSize == BISIZE_V4 || biSize == BISIZE_V5) {
			fread (&biWidth, SIZE_DWORD, 1, Input);
			fread (&biHeight, SIZE_DWORD, 1, Input);
		}
		else {
			printf ("Error 0x2: unknown version.\n");
			return 2;
		}
	}
	if ((!biWidth) || (!biHeight)) {
		printf ("Error 0x3: invalid width/heigth (input file format).\n");
		return 3;
	}
	*fsize = biHeight*biWidth;
	fseek (Input, 2, SEEK_SET);
	*Headers = (char*) calloc (*bfOffBits-2, sizeof(char));//Reading all headers except
	fread (*Headers, sizeof(char), *bfOffBits-2, Input);   //+type signature into a buffer.
	if (mode == 'd') {
		fseek (Input, sizeof(int), SEEK_END);
		fread (fsize, sizeof(int), 1, Input);
		printf ("Mode: %c. Fsize: %d\n", mode, *fsize);
	}
	return 0;
}

void openFiles (FILE **input, const char* input_name, FILE **output, const char* output_name) {
    *input = fopen (input_name, "r");
    *output = fopen (output_name, "w");
}
