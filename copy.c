#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copy(FILE * file1 , FILE* file2);
int openFiles(char* filename1, char* filename2);
int handleF(char* filename1 , char* filename2);

int main(int argc, char **argv) {
    // Check that the user provided two filenames as arguments
    if (argc < 3) {
        printf("Usage: %s <file1> <file2>\n , optional : -v /-f", argv[0]);
        return 1;
    }
    switch(argc){
        case 3:
            return openFiles(argv[1], argv[2]);
            break;
        case 4:
            if (!strcmp(argv[3] , "-v")){
                int result = openFiles(argv[1], argv[2]);
                if(result == 2){
                    printf("general failure\n");
                    return 2;
                }
                if(result == 1){
                    printf("target file exist\n");
                    return 1;
                }
                printf("success\n");
                return 0;
            }
            if(!strcmp(argv[3] , "-f"))
                return handleF(argv[1] , argv[2]);
            break;
        case 5:
            if (!strcmp(argv[3] , "-v")){
                if(!strcmp(argv[4] , "-f")){
                    if(handleF(argv[1], argv[2]) == 2){
                        printf("general failure\n");
                        return 2;
                    }
                    printf("success\n");
                    return 0;
                }
            }
            if (!strcmp(argv[3] , "-f")){
                if(!strcmp(argv[4] , "-v")){
                     if(handleF(argv[1], argv[2]) == 2){
                        printf("general failure\n");
                        return 2;
                    }
                    printf("success\n");
                    return 0;
                }
            }
            break;
    }
    
}

int copy(FILE * file1 , FILE* file2){
    int byte;
    int success = 0;

    while ((byte = fgetc(file1)) != EOF) {
        if (fputc(byte, file2) == EOF) {
            success = 2;
            break;
        }
    }
    fclose(file1);
    fclose(file2);
    return success;
}

int handleF(char* filename1 , char* filename2){
    FILE *file1 = fopen(filename1 , "rb");

    if(file1 == NULL){
        printf("file number 1 could not open\n");
        return 2;
    }
        

    FILE *file2 = fopen(filename2 , "wb");

    if(file2 == NULL){
        printf("file number 2 could not open\n");
        fclose(file1);
        return 2;
    }
    return copy(file1,file2);
}
int openFiles(char* filename1, char* filename2){
    FILE *file1 ,*file2;    
    file2 = fopen(filename2 , "r");

    if(file2 == NULL){
        file2 = fopen(filename2 , "wb");

        if(file2 == NULL){
            printf("couldnt create file 2\n");
            return 2;
        }
        file1 = fopen(filename1 , "rb");

        if(file1 == NULL){
            printf("file number 1 could not open\n");
            fclose(file2);
            return 2;
        }

        return copy(file1 , file2);
    }
    fclose(file2);
    return 1;
}