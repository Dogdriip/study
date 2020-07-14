// sysprog final

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <ctype.h>

// thread argument struct
struct thread_data {
    char *buff;                 /* memory buffer pointer */
    long long start;            /* start index in the buffer */
    long long block_size;       /* block size */
    long long counter;          /* counter variable */
};

// func for child1's two threads, counting word count
void *count_words(void *a) {
    struct thread_data *args = a;
    char c, prevc = '\0';
    int i;

    for (i = args->start; i < args->start + args->block_size; i++) {
        c = args->buff[i];
        if (!isalnum(c) && isalnum(prevc)) {
            args->counter++;
        }
        prevc = c;
    }

    return NULL;
}

// func for child2's two threads, accumulating nums
void *accumulate_numbers(void *a) {
    struct thread_data *args = a;
    char c;
    int i;
    long long tmp = 0;

    for (i = args->start; i < args->start + args->block_size; i++) {
        c = args->buff[i];
        
        if (c >= 48 && c <= 57) {
            tmp *= 10;
            tmp += (c - 48);
        } else {
            args->counter += tmp;
            tmp = 0;
        }
    }

    return NULL;
}

int main(int argc, char **argv) {
    FILE *fp;
    int pid1, pid2;
    int pipe1[2], pipe2[2];
    struct timeval start_time, end_time;
    long long words, number;  // final res
    long long len, block_size;
    char* buff;

    if (argc < 2) {
        fprintf(stderr, "usage: progname filename");
        exit(1);
    }
    if ((fp = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "error opening file");
        exit(1);
    }

    // time recording start
    gettimeofday(&start_time, NULL);

    // make two pipes
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        fprintf(stderr, "pipe err");
        exit(1);
    }

    // calculate file size, size of the block. make buffer
    /* check the file size*/
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);
    block_size = len / 2;
    fseek(fp, SEEK_SET, 0);
    /* copy the contents of file to a memory buffer */
    buff = (char*)malloc(sizeof(char) * len);
    fread(buff, 1, len, fp);

    // fork first child
    if ((pid1 = fork()) == -1) {
        fprintf(stderr, "fork1 err");
        exit(1);
    }

    if (pid1 == 0) {
        // first child
        // creates two threads, word count
        pthread_t wc_threads[2];
        struct thread_data wc_data[2];
        long long total_word_count = 0;

        /* store the block information in the argument structure */
        for (int i = 0; i < 2; i++) {
            wc_data[i].buff = buff;
            wc_data[i].start = block_size * i;
            wc_data[i].block_size = block_size;
            wc_data[i].counter = 0;
        }

        /* create threads and wait until all threads complete their task */
        for (int i = 0; i < 2; i++) {
            pthread_create(&wc_threads[i], NULL, count_words, (void*)&(wc_data[i]));
        }

        for (int i = 0; i < 2; i++) {
            pthread_join(wc_threads[i], NULL);
            total_word_count += wc_data[i].counter;
        }

        write(pipe1[1], &total_word_count, sizeof(total_word_count));
        exit(0);
    } else {
        // fork second child
        if ((pid2 = fork()) == -1) {
            fprintf(stderr, "fork2 err");
            exit(1);
        }

        if (pid2 == 0) {
            // second child
            // creates two threads, accumulates number
            pthread_t num_threads[2];
            struct thread_data num_data[2];
            long long total_num = 0;
            
            /* store the block information in the argument structure */
            for (int i = 0; i < 2; i++) {
                num_data[i].buff = buff;
                num_data[i].start = block_size * i;
                num_data[i].block_size = block_size;
                num_data[i].counter = 0;
            }

            /* create threads and wait until all threads complete their task */
            for (int i = 0; i < 2; i++) {
                pthread_create(&num_threads[i], NULL, accumulate_numbers, (void*)&(num_data[i]));
            }

            for (int i = 0; i < 2; i++) {
                pthread_join(num_threads[i], NULL);
                total_num += num_data[i].counter;
            }

            write(pipe2[1], &total_num, sizeof(total_num));
            exit(0);
        } else {
            // parent
            wait(NULL);
            wait(NULL);
        }
    }

    // read from pipe
    read(pipe1[0], &words, sizeof(words));
    read(pipe2[0], &number, sizeof(number));

    // time recording end, calculate time
    gettimeofday(&end_time, NULL); 
    double operating_time = (double)(end_time.tv_sec)+(double)(end_time.tv_usec)/1000000.0-(double)(start_time.tv_sec)-(double)(start_time.tv_usec)/1000000.0;

    // print res
    printf("Elapse time : %f seconds, total number of words: %lld, accumulated number: %lld\n", operating_time, words, number);

    return 0;
}

