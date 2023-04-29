#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int cmp(char* filename1, char* filename2, int verbose);
int handleI(char* filename1, char* filename2, int verbose);

int main(int argc, char **argv) {
    // Check that the user provided two filenames as arguments
    if (argc < 3) {
        printf("Usage: %s <file1> <file2> optional : -v /-i\n", argv[0]);
        return 2;
    }
    int verbose = 0;
    switch(argc){
        case 3:
            cmp(argv[1], argv[2],verbose);
            break;
        case 4:
            if (!strcmp(argv[3] , "-v")){
                verbose = 1 ;
                return cmp(argv[1], argv[2],verbose);
            }
            if(!strcmp(argv[3] , "-i"))
                return handleI(argv[1], argv[2], verbose);
            break;
        case 5:
            if (!strcmp(argv[3] , "-v")){
                if(!strcmp(argv[4] , "-i")){
                 verbose = 1;
                 return handleI(argv[1], argv[2], verbose);
                }
            }
            if (!strcmp(argv[3] , "-i")){
                if(!strcmp(argv[4] , "-v")){
                    verbose = 1;
                    return handleI(argv[1], argv[2], verbose);
                }
            }
            break;
            
    }
    return 0;
}

int cmp(char* filename1, char* filename2, int verbose ){
    FILE *file1 = fopen(filename1 , "rb");

    if(file1 == NULL){
        printf("file number 1 could not open\n");
        return 2;
    }
        

    FILE *file2 = fopen(filename2 , "rb");

    if(file2 == NULL){
        printf("file number 2 could not open\n");
        fclose(file1);
        return 2;
    }
    
    int byte1, byte2;

    do {
        byte1 = fgetc(file1);
        byte2 = fgetc(file2);
        if (byte1 != byte2) {
            fclose(file1);
            fclose(file2);
            if(verbose)
                printf("destinct\n");
            return 1;
        }
    }while ((byte1 != EOF) && (byte2  != EOF));
    fclose(file1);
    fclose(file2);
    if (byte1 == EOF && byte2 == EOF) {
        if(verbose)
            printf("equal\n");
        return 0;
    }
    if(verbose)
        printf("destinct\n");
    return 1;

}

int handleI(char* filename1, char* filename2, int verbose){

        FILE *file1 = fopen(filename1, "r");
        if(file1 == NULL) {
            printf("file number 1 could not open\n");
            return -1;
        }
        FILE *filetemp1 = fopen("temp1.txt", "w");
        if(filetemp1 == NULL){
            fclose(file1);
            return -1;
        }
        char ch;
        while ( (ch = fgetc(file1)) != EOF){
            ch =tolower(ch);
            fputc(ch, filetemp1);
        }
        fclose(file1);
        fclose(filetemp1);

        FILE *file2 = fopen(filename2, "r");
        if(file2 == NULL) {
            return -1;
        }
        FILE *filetemp2 = fopen("temp2.txt", "w");
        if(filetemp2 == NULL){
            fclose(file2);
            return -1;
        }
        while ( (ch = fgetc(file2)) != EOF){
            ch =tolower(ch);
            fputc(ch, filetemp2);
        }
        fclose(file2);
        fclose(filetemp2);
        return cmp("temp1.txt" , "temp2.txt",verbose);
}
