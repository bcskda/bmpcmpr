#include <stdio.h>
#include <stdlib.h>

bool FileExists (const char *filename);
void open_files (FILE **input, const char *input_name, FILE **output, const char *output_name);
void getSourceExtent (FILE *source, int *Sz_x, int *Sz_y);
int readMeta (FILE *Input, char **Headers, int *bfOffBits, int *biWidth, int *biHeight);
void Compress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int width, const int height);
void printColor (FILE *output, char r, char g, char b);

const int BISIZE_CORE = 12, BISIZE_V3 = 40, BISIZE_V4 = 108, BISIZE_V5 = 124,
		  SIZE_DWORD = 4, SIZE_WORD = 2, BIBITCOUNT = 16,
		  MASK_1ST4 = 0x00FF, MASK_2ND4 = 0xFF00;

int main (const int argnum, const char* args[]) {
    int err = 0;
    FILE *Source = 0, *Output = 0;
    open_files (&Source, args[2], &Output, args[3]);
    
	int offBits = 0, width = 0, height = 0;
	char *Headers = 0;
    err = readMeta (Source, &Headers, &offBits, &width, &height);
    if (err) {
		return err;
	}
    
    Compress (Source, Output, Headers, offBits, width, height);
    
    fclose (Source);
    fclose (Output);
    return 0;
}

void open_files (FILE **input, const char* input_name, FILE **output, const char* output_name) {
    *input = fopen (input_name, "r");
    *output = fopen (output_name, "w");
    }

int readMeta (FILE *Input, char** Headers, int *bfOffBits, int *biWidth, int *biHeight) {
	fseek (Input, 0, SEEK_SET);
	
	if (! (getc(Input)=='B' && getc(Input)=='M') ) {
		printf ("Error 0x1: undefined type signature.\n");
		return 1;
	}

	int bfSize = 0; fread (&bfSize, SIZE_DWORD, 1, Input);
	fseek (Input, 2*SIZE_WORD, SEEK_CUR); //Skipping struct`s reserved variables
	fread (bfOffBits, SIZE_DWORD, 1, Input);
	
	int biSize = 0; fread (&biSize, SIZE_DWORD, 1, Input);
	switch (biSize) {
		case BISIZE_CORE:
			break;
		case BISIZE_V3:
			break;
		case BISIZE_V4:
			break;
		case BISIZE_V5:
			break;
		default:
			printf ("Error 0x2: unknown version.\n");
			return 2;
	}
	
	if (biSize == BISIZE_CORE) {
		fread (biWidth, SIZE_WORD, 1, Input); fread (biHeight, SIZE_WORD, 1, Input);
	}
	else {
		if (biSize == BISIZE_V3 || biSize == BISIZE_V4 || biSize == BISIZE_V5) {
			fread (biWidth, SIZE_DWORD, 1, Input); fread (biHeight, SIZE_DWORD, 1, Input);
		}
	}
	if ((!*biWidth) || (!*biHeight)) {
		printf ("Error 0x3: invalid width/heigth (input file format).\n");
		return 3;
	}
	
	fseek (Input, 2, SEEK_SET);
	*Headers = (char*) calloc (*bfOffBits-2, sizeof(char));//Reading all headers except
	fread (*Headers, sizeof(char), *bfOffBits-2, Input);   //type signeture into a buffer.
	
	return 0;
}

void Compress (FILE *Input, FILE *Output, char *Headers, const int offBits, const int width, const int height) {
	fseek (Output, 0, SEEK_SET);//Printing all read headers except type signature into Output
	fprintf (Output, "CM");//New type signature: "CM"
	fwrite (Headers, sizeof(char), offBits-2, Output);//Spaces and over 'stop-symbols' possible
	
	fseek (Input, offBits, SEEK_SET);
	int spree = 1;
	int ccolor = 0, ncolor = 0;
	fread (&ccolor, SIZE_WORD, 1, Input);

	for (int i = 1; i < height*width; i++) {
		fread (&ncolor, SIZE_WORD, 1, Input);
		if ((ncolor != ccolor) || (spree == 0x0FFFFFFF)) {//Maximal int without using reserved 15th bit
			if (spree > 1) {
				spree |= 0x8000;
				fprintf (Output, "%c%c%c%c", (spree&MASK_2ND4)/256, spree&MASK_1ST4,
						 (ccolor&MASK_2ND4)/256, ccolor&MASK_1ST4);
			}
			else {
				fprintf (Output, "%c%c", (ccolor&MASK_2ND4)/256, ccolor&MASK_1ST4);
			}
			ccolor = ncolor;
			spree = 1;
		}
		else {
			spree++;
		}
	}
}
