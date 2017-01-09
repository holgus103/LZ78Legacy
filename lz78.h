#ifndef LZ78
#define LZ78
#include <stdio.h>
#include <stdlib.h>

typedef struct dict_ele{
unsigned char key;
int id;
struct dict_ele* next,*correct;
}dict_ele;


int compress(dict_ele* dictionary,FILE* input,FILE* output);

int dispose_dictionary(dict_ele* dictionary);

int decompress(FILE* input,FILE* output);

int check_file_size(FILE* input);

void find_output(short temp,short* pointers,char* dictionary,FILE* output);

#endif //LZ78
