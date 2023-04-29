#include <stdio.h>
#include "partB.h"


void encode(char* str){
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] ==  ' ')
            str[i] = ' ';
        else{
            str[i] = (char)(((int)str[i] + 3) % 256);
        }
    }
    printf("%s\n",str);

}
void decode(char* str){
     for(int i = 0; str[i] != '\0'; i++){
        if(str[i] ==  ' ')
            str[i] = ' ';
        else{
            str[i] = (char)(((int)str[i] - 3 + 256) % 256);
        }
    }
    printf("%s\n",str);

}