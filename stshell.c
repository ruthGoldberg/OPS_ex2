#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

void handlerSignal(int signal){
    printf("\nYou typed Control-C!\n");
}

int main() {

    char command[1024];
    char *token;
    int i;
    char *outfile;

    char last_command[100]="";
    int fd, amper, redirect,append=0,useLastCommend=0,input=0, piping , status =0, argc1=0 ;
    int fd1[2] , fd2[2];
    char *argv1[10], *argv2[10] , *argv3[10];

    signal(SIGINT,handlerSignal);
    while (1)
    {
        for (int i = 0; i < 10; i++) {
            argv1[i] = NULL;
            argv2[i] = NULL;
            argv3[i] = NULL;
        }
        printf("BeniAndRutiShell$ ");
        fflush(stdout);
        if(!useLastCommend){
            if(fgets(command, 1024, stdin) == NULL)
                return -1;
            command[strlen(command) - 1] = '\0';

        }else{
            strcpy(command,last_command);
            useLastCommend=0;
            memset(last_command,0,sizeof(last_command));
        }

        piping = 0;
        /* parse command line */
        i = 0;
        token = strtok (command," ");
        while (token != NULL)
        {
            argv1[i] = token;
            token = strtok (NULL, " ");
            i++;
            if (token && ! strcmp(token, "|")) {
                piping ++;
                break;
            }
        }
        argv1[i] = NULL;
        argc1 = i;

        /* Is command empty */
        if (argv1[0] == NULL)
            continue;


        if(argc1 >=2 && !strcmp(argv1[0],"cd")) {
            chdir(argv1[1]);                   // exe 6
            continue;
        }


        if(argc1 >=1 && !strcmp(argv1[0],"exit")) {
            exit(0);                      // exe 8
        }

        /* Does command contain pipe */
        if (piping == 1) {
            i = 0;
            token = strtok (NULL, " ");
            while (token!= NULL)
            {
                argv2[i] = token;
                token = strtok (NULL, " ");
                i++;
                if (token && ! strcmp(token, "|")) {
                    piping ++;
                    break;
                }
            }
            argv2[i] = NULL;
        }
        if (piping == 2) {
            i = 0;
            token = strtok (NULL, " ");
            while (token!= NULL)
            {
                argv3[i] = token;
                token = strtok (NULL, " ");
                i++;

            }
            argv3[i] = NULL;
        }
        amper = 0;
        //printf("%d, %s, %s ,%s\n",argc1,argv1[0],argv1[1],argv1[2]);
        if (argc1 > 1 && !strcmp(argv1[argc1 - 2], ">")) {
            redirect = 1;
            argv1[argc1 - 2] = NULL;
            outfile = argv1[argc1 - 1];
            //printf("1:%d ,2: %d,3:%s ,4:%s\n",redirect,argc1,argv1[0], outfile);

        }
        else {
            redirect = 0;
            // Append
            if (argc1 > 1 && ! strcmp(argv1[argc1 - 2], ">>")) {
                append = 1;
                argv1[argc1 - 2] = NULL;
                outfile = argv1[argc1 - 1];
            }
            else
            {
                append = 0;
                // Input
                if (argc1 > 1 && ! strcmp(argv1[argc1 - 2], "<")) {
                    input = 1;
                    argv1[argc1 - 2] = NULL;
                    outfile = argv1[argc1 - 1];
                }
                else
                    input = 0;
            }
        }
        /* for commands not part of the shell command language */

        if (fork() == 0) {
            /* redirection of IO ? */
            if (redirect) {
                fd = creat(outfile, 0660);
                close (STDOUT_FILENO) ;
                dup(fd);
                close(fd);
                /* stdout is now redirected */
            }
            if (append) {
                fd = open(outfile, O_WRONLY|O_CREAT|O_APPEND, 0660); // check if works  and not -1
                close (STDOUT_FILENO);
                dup(fd);
                close(fd);
                /* stdout is now appended */
            }
            if (input) {
                fd = open(outfile, O_RDONLY, 0660); // check if works  and not -1
                close (STDIN_FILENO);
                dup(fd);
                close(fd);
                /* stdin is now redirected */
            }
            if (piping == 1) {
                pipe (fd1);

                if (fork() == 0) {
                    /* first component of command line */
                    close(STDOUT_FILENO);
                    dup2(fd1[1],STDOUT_FILENO);
                    close(fd1[1]);
                    close(fd1[0]);
                    /* stdout now goes to pipe */
                    /* child process does command */
                    execvp(argv1[0], argv1);
                }else {
                    /* 2nd command component of command line */
                    close(STDIN_FILENO);
                    dup2(fd1[0],STDIN_FILENO);
                    close(fd1[0]);
                    close(fd1[1]);
                    /* standard input now comes from pipe */
                    execvp(argv2[0], argv2);
                }
            }
            if (piping == 2) {
                pipe (fd1);

                if (fork() == 0) {
                    /* first component of command line */
                    close(STDOUT_FILENO);
                    dup2(fd1[1], STDOUT_FILENO);
                    close(fd1[1]);
                    close(fd1[0]);

                    execvp(argv1[0], argv1);
                }else {
                    pipe(fd2);
                    if (fork() == 0) {
                        close(STDIN_FILENO);
                        dup2(fd1[0], STDIN_FILENO);
                        close(fd1[0]);
                        close(fd1[1]);

                        close(STDOUT_FILENO);
                        dup2(fd2[1], STDOUT_FILENO);
                        close(fd2[1]);
                        close(fd2[0]);
                        execvp(argv2[0], argv2);
                    }else{
                        close(STDIN_FILENO);
                        dup2(fd2[0], STDIN_FILENO);
                        close(fd1[0]);
                        close(fd1[1]);
                        close(fd2[0]);
                        close(fd2[1]);

                        execvp(argv3[0], argv3);
                        wait(NULL);

                    }
                    wait(NULL);

                    execvp(argv2[0], argv2);
                }
            }
            else
                execvp(argv1[0], argv1);
        }

        if (amper == 0) {
            wait(&status);
        }
        strcpy(last_command,command);
    }
}