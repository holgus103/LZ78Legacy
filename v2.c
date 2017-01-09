#include <stdio.h>
#include <stdlib.h>
#include "lz78.h"
#define MAX_PATH_SIZE 64


int main(int argc,char*argv){
    dict_ele head;
    head.correct=NULL;
    head.id=-1;
    head.next=NULL;

    int filesize;
    char* path, ans,*buffer,*outputpath;
    FILE* input,*output;
    printf("Shalom!\n");
    //ans='d';
    path=(char*)malloc(MAX_PATH_SIZE*sizeof(char));
    outputpath=(char*)malloc(MAX_PATH_SIZE*sizeof(char));
    //path="c:\\janusz.comp";
    //outputpath="c:\\janusz.decomp";
    if(argc==1){
    printf("What would you like to do?\n| c - compress   |\n| d - decompress |\n");
    scanf("%c",&ans);
    }
    printf("Please share your magnificent file path with me\n");
    scanf("%s",path);
    if(!(input=fopen(path,"rb"))){
        printf("File does not exist");
        getchar();
        exit(1);
        }
    printf("File opened successfully\n");
    /*fseek(input,0,SEEK_END);
    filesize=ftell(input);
    buffer=(char*)malloc(sizeof(char)*filesize);
    fseek(input,0,SEEK_SET);
    fread(buffer,sizeof(char),filesize,input);
    */
    printf("Where would you like to save?\n");
    scanf("%s",outputpath);
    if(!(output=fopen(outputpath,"wb"))){
        printf("Opening output file failed!");
        getchar();
        exit(2);
    }
    printf("Begining writing to output file...\n");
    if(ans=='d'){
    decompress(input,output);
    }
    if(ans=='c'){
    compress(&head,input,output);
    printf("Engaging disposition...\n");
    dispose_dictionary(&head);
    }
    if(ans!='d'&&ans!='c'){
        printf("Input error");
        exit(5);
    }
    /*if(!(fwrite(buffer,sizeof(char),filesize,output))){
       printf("Writing failed");
       getchar();
       exit(4);
       }

    printf("Writing completed successfully! Have a nice day!");
    do{
    sign=getc(input);
    printf("%c",sign);
    }
    while(sign!=EOF);
     */
    printf("The dictionary was safely disposed of!");
    free((void*)path);
    free((void*)outputpath);
    //free((void*)buffer);
    fclose(input);
    fclose(output);
    getchar();
    return 0;
}
