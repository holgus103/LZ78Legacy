#include "lz78.h"
#define MAX_DICTIONARY_SIZE 65534//16777216 // 16M

int compress(dict_ele* dictionary, FILE* input,FILE* output){
    unsigned char sign;
    short j=0,i=0;
    int k,filesize;
    dict_ele* temp=dictionary;
    printf("COMPRESSING...\n");
    filesize=check_file_size(input);
for(k=0;k<filesize;k++){
    sign=getc(input);
    //getchar();
    //printf("sign: %c\n",sign);
    //printf("i: %d\n",i);
    if(temp->id==0){
        //printf("id=-1\n");
        temp->key=sign;
        temp->id=i+1;
        //printf("%d\n",j);
        //printf("%c\n",sign);
        fwrite(&j,sizeof(short),1,output);
        putc(sign,output);
        i++;
        temp=dictionary;
        j=0;
    }
    else{
        while(temp->key!=sign&&temp->next){
            //printf("jest while\n");
            temp=temp->next;
            //printf("szukamy");
            }
        if(!(temp->next)&&temp->key!=sign){
            //printf("j:%d\n",j);
            //printf("sign%c\n",sign);
            //printf("nowy ziomek");
            fwrite(&j,sizeof(short),1,output);
            putc(sign,output);
            temp->next=malloc(sizeof(dict_ele));
            temp->next->key=sign;
            temp->next->next=NULL;
            temp->next->correct=NULL;
            temp->next->id=i+1;
            i++;
            temp=dictionary;
            j=0;
            }
        else{
            j=temp->id;
            //printf("elo ziomsy");
            if(k==filesize-1){
            //printf("supersyf");
            fwrite(&j,sizeof(short),1,output);
            }
            if(!(temp->correct)){
                temp->correct=malloc(sizeof(dict_ele));
                temp->correct->next=NULL;
                temp->correct->correct=NULL;
                temp->correct->id=0;
                temp=temp->correct;
                }
            else
            temp=temp->correct;
            }
    }
            if(i==MAX_DICTIONARY_SIZE){
            //printf("RESET");
            i=j=0;
            dispose_dictionary(dictionary);
            dictionary->correct=NULL;
            dictionary->id=0;
            dictionary->next=NULL;
            temp=dictionary;
            //printf("wielkismutek");
            }
            //getchar();
        }
    return 0;
}

int dispose_dictionary(dict_ele* dictionary){
    if(dictionary->correct){
        dispose_dictionary(dictionary->correct);
        }
    if(dictionary->next){
        dispose_dictionary(dictionary->next);
    }
    free(dictionary);
    return 0;
}

int check_file_size(FILE* input){
    int filesize;
    fseek(input,0,SEEK_END);
    filesize=ftell(input);
    fseek(input,0,SEEK_SET);
    return filesize;
}

void find_output(short temp,short* pointers, char* dictionary,FILE* output){
  if(temp>=0){
    find_output(pointers[temp]-1,pointers,dictionary,output);
    fwrite(dictionary+temp,sizeof(char),1,output);
    //printf("%c",dictionary[temp]);
  }
}

int decompress(FILE* input,FILE* output){
    unsigned    char* dictionary;
    int i,limit,filesize;
    short *pointers;
    filesize=check_file_size(input);
    pointers=malloc(MAX_DICTIONARY_SIZE*sizeof(short));
    dictionary=malloc(MAX_DICTIONARY_SIZE*sizeof(char));

    printf("DECOMPRESSING...\n");
    if(!(filesize%(sizeof(short)+sizeof(char)))){
        limit=filesize/5;
        }
    else{
        limit=(filesize-4)/5;
    }
    for(i=0;i<limit;i++){
        fread(pointers+(i%MAX_DICTIONARY_SIZE),sizeof(short),1,input);
        //printf("%d",i);
        if(pointers[i%MAX_DICTIONARY_SIZE]){
        find_output(pointers[i%MAX_DICTIONARY_SIZE]-1,pointers,dictionary,output);
        }
        //printf("%d",pointers[i]);
        //dictionary[i]=getc(input);
        fread(dictionary+(i%MAX_DICTIONARY_SIZE),sizeof(char),1,input);
        //printf("%c",dictionary[i%MAX_DICTIONARY_SIZE]);
        fwrite(dictionary+(i%MAX_DICTIONARY_SIZE),sizeof(char),1,output);
        //getchar();
    }
    //fread(pointers+i,sizeof(int),1,input);
    //if(pointers[i+1])
        //find_output(pointers[i+1],pointers,dictionary,output);
    if(limit==((filesize-4)/5)){
    //printf("EXTRAMODE");
    fread(pointers+(i%MAX_DICTIONARY_SIZE),sizeof(short),1,input);
    //printf("%d",i);
    find_output(pointers[i%MAX_DICTIONARY_SIZE]-1,pointers,dictionary,output);
    }
    free(dictionary);
    free(pointers);
    return 0;
}


