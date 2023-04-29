#include <stdio.h>
#include <ctype.h>
#include "partB.h"


void encode(char* str){
    for(int i = 0; str[i] != '\0'; i++){
        if(isupper(str[i])){
            str[i] = tolower(str[i]);
        }else if(islower(str[i])){
            str[i] = toupper(str[i]);
        }
    }
    printf("%s\n",str);
}

void decode(char* str){
    for(int i = 0; str[i] != '\0'; i++){
        if(isupper(str[i])){
            str[i] = tolower(str[i]);
        }else if(islower(str[i])){
            str[i] = toupper(str[i]);
        }
    }
    printf("%s\n",str);

}
