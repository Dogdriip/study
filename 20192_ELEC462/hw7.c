// hw7.c

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>

#define MAXARGS 100

int main(int argc, char* argv[]) {
    int i, j;
    int pipefd[MAXARGS][2];
    int pid;

    for (i = 1; i < argc - 2; i++) {
       pipe(pipefd[i]);
    }
    
    i = 1;
    while (i < argc - 2) {
        pid = fork();
        if (pid > 0) {  // parent
            i++;
            if (i == argc - 2) {  // last argv?
                dup2(pipefd[i - 1][0], 0);  // redirect only stdin
                
                for (j = 1; j < argc - 2; j++) {  // close all
                    close(pipefd[j][0]);
                    close(pipefd[j][1]);
                }
                
                execlp(argv[i], argv[i], NULL);

                perror("err");
                exit(1);
            }
        } else {  // child
            if (i != 1) dup2(pipefd[i - 1][0], 0);  // stdin redirecting
            dup2(pipefd[i][1], 1);  // stdout redirecting

            for (j = 1; j < argc - 2; j++) {  // close all
                close(pipefd[j][0]);
                close(pipefd[j][1]);
            }

            execlp(argv[i], argv[i], NULL);  // execute ith argv
            
            perror("err");
            exit(1);
        }
    }
    
    // exception (one argv?)
    execlp(argv[1], argv[1], NULL); 

    return 0;
}
