#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <dlfcn.h>
#include "partB.h"
#include <ctype.h>

void (*encodeFunc)(const char *);

int main(int argc, char **argv){
    if(argc < 3){
        printf("Usage: %s <codec> <message>\n ", argv[0]);
        return 1;
    }
    void *hdl;
    if(!strcmp(argv[1] , "codecA")){
        hdl = dlopen("./libcodecA.so",RTLD_LAZY);
    }
    else if(!strcmp(argv[1], "codecB")){
        hdl = dlopen("./libcodecB.so",RTLD_LAZY);
    }
    else{
        printf("You need to choose between codecA vs codecB");
        return 1;
    }
    if(hdl == NULL){
        printf("dlopen did not work\n");
        return 1;
    }
    encodeFunc = (void(*)(const char *))dlsym(hdl,"encode");

	if (NULL == encodeFunc){
        return 1;
    }
    
    encodeFunc(argv[2]);
	return 0;

}
