
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zconf.h>
#include <sys/wait.h>

void print_dirc(){
    char dir[1024];
    getcwd(dir, sizeof(dir));
    printf("\n %s:", dir);

}

int split(char cmd[],char*parsed[],char splitter[]){
    char *ptr = strtok(cmd, splitter);
    int i = 0;
    while (ptr != NULL) {
        parsed[i] = ptr;
        ptr = strtok(NULL, splitter);
        i = i + 1;
    }
    return i;
}

void main () {

while (1) {
// variables declaration
    char command[50];
    char delim[] = " ";
    char *stri[10] = {'\0'};
    pid_t pid;

    print_dirc();
    // taking the user input
    scanf("%[^\n]%*c", command);


    // splitting the input string
    int num_words = split(command, stri, delim); // number of splitted words

    if (!strcmp(stri[0], "exit") || !strcmp(stri[0], "\001")) {
        exit(0);
    } else if (!strcmp(stri[0], "cd")) {
        if(chdir(stri[1])<0){
            printf("\nnot found directory");
        }
    } else {

        pid = fork();
        if (!strcmp(stri[num_words-1],"&")) {
            stri[num_words-1]='\0';
            if (pid == 0) {                    // child is created
                if (execvp(stri[0], stri) < 0) {
                    printf("\nCould not execute command..");
                    exit(0);
                    // wait(NULL);
                }

            } else {
              //  wait(NULL);

            }

        } else{


            if (pid == 0) {                    // child is created
                if (execvp(stri[0], stri) < 0) {
                    printf("\nCould not execute command..");
                    exit(0);
                    // wait(NULL);
                }

            } else {
                wait(NULL);

            }
        }

    }
}

}

