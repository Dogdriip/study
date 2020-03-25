// hw6.c

#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#define SIZE 20000

unsigned int arr[SIZE];  // orig
unsigned int asc[SIZE], desc[SIZE];  // asc sorted, desc sorted

void bubble_sort_asc() {
    int i, j, temp;

    for (i = 0; i < SIZE; i++) {
        asc[i] = arr[i];
    }

    for (i = SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (asc[j] > asc[j + 1]) {
                temp = asc[j];
                asc[j] = asc[j + 1];
                asc[j + 1] = temp;
            }
        }
    }
}

void bubble_sort_desc() {
    int i, j, temp;

    for (i = 0; i < SIZE; i++) {
        desc[i] = arr[i];
    }

    for (i = SIZE - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (desc[j] < desc[j + 1]) {
                temp = desc[j];
                desc[j] = desc[j + 1];
                desc[j + 1] = temp;
            }
        }
    }
}

void arr_write(unsigned int a[], char *filename) {
    FILE *fp = fopen(filename, "w");
    int i;
    
    for (i = 0; i < SIZE; i++) {
        fprintf(fp, "%d ", a[i]);
    }
    fprintf(fp, "\n");

    fclose(fp);
}

int main(int argc, char* argv[]) {
    int i;
    struct timeval start_time, end_time;
    
    srand(time(NULL));
    for (i = 0; i < SIZE; i++) {
        arr[i] = rand() % 20000;
    }

    arr_write(arr, "1");    
    
    if (strcmp(argv[1], "0") == 0) {
        // parallel using fork()
        gettimeofday(&start_time, NULL);
        
        //// start
        int fork_rv1, fork_rv2;
        fork_rv1 = fork();
        if (fork_rv1 == 0) {
            bubble_sort_asc();
            arr_write(asc, "2");
            exit(0);
        } else {
            fork_rv2 = fork();
            if (fork_rv2 == 0) {
                bubble_sort_desc();
                arr_write(desc, "3");
                exit(0);
            } else {
                wait(NULL);
                wait(NULL);        
            }
        }
        //// fin

        gettimeofday(&end_time, NULL);
        double operating_time = (double)(end_time.tv_sec) + (double)(end_time.tv_usec) / 1000000.0 - (double)(start_time.tv_sec) - (double)(start_time.tv_usec) / 1000000.0;
        printf("Elapsed: %f seconds\n", (double)operating_time); 
    } else {
        // sequential
        gettimeofday(&start_time, NULL);

        //// start
        bubble_sort_asc();
        arr_write(asc, "2");
        bubble_sort_desc();
        arr_write(desc, "3");
        //// fin

        gettimeofday(&end_time, NULL);
        double operating_time = (double)(end_time.tv_sec) + (double)(end_time.tv_usec) / 1000000.0 - (double)(start_time.tv_sec) - (double)(start_time.tv_usec) / 1000000.0;
        printf("Elapsed: %f seconds\n", (double)operating_time); 
    }

    return 0;
}
