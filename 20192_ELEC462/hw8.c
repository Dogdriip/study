// hw8.c

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <ctype.h>

#define MAXTHREAD 8

/* structure for passing multiple arguments to thread*/
struct thread_data {
    char *buff;                 /* memory buffer pointer */
    long long start;            /* start index in the buffer */
    long long block_size;       /* block size */
    long long counter;          /* counter variable */
};


/* initialize global variables here if needed */
long long int total_count;

// funcs
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


/* main function*/
int main(int argc, char **argv) {
    FILE* fp;
    int nthreads, x, id;
    long long block_size, len;
    int i;
    struct thread_data data[MAXTHREAD];
    pthread_t *threads;  // array of pthread_t (allocated by number of thread)
    
    /* handle the program arguments */
    if (argc < 3) {
        fprintf(stderr, "Usage: ./program_name <the number of thread> <file_path>");
        exit(-1);
    }
    nthreads = atoi(argv[1]);
    
    /* open file */
    if ((fp = fopen(argv[2],"r")) == NULL) {
        printf("Error opening file!\n");
        exit(-1);
    }

    threads = malloc(nthreads * sizeof(pthread_t));
    

    /* check the file size*/
    fseek(fp, 0, SEEK_END);
    len = ftell(fp);

    /* calculate size of the block that will be assigned to each thread */
    block_size = len / nthreads;
    fseek(fp, SEEK_SET, 0);
    

    /* copy the contents of file to a memory buffer */
    char* buff = (char*)malloc(sizeof(char) * len);
    fread(buff, 1, len, fp);



    /* store the block information in the argument structure */
    for (i = 0; i < nthreads; i++) {
        data[i].buff = buff;
        data[i].start = block_size * i;
        data[i].block_size = block_size;
        data[i].counter = 0;
    }
    
    /* record the current time */
    struct timeval start_time,end_time;
	gettimeofday(&start_time, NULL);	
    


    /* create threads and wait until all threads complete their task */
    for (i = 0; i < nthreads; i++) {
        pthread_create(&threads[i], NULL, count_words, (void*)&(data[i]));
    }

    for (i = 0; i < nthreads; i++) {
        pthread_join(threads[i], NULL);
        printf("[THREAD] the number of words : %lld\n", data[i].counter);
        total_count += data[i].counter;
    }

    printf("[MAIN] total word count: %lld\n", total_count);

    fclose(fp);
    free(buff);

    /* calculate the elapsed time */
	gettimeofday(&end_time, NULL); 
	double operating_time = (double)(end_time.tv_sec)+(double)(end_time.tv_usec)/1000000.0-(double)(start_time.tv_sec)-(double)(start_time.tv_usec)/1000000.0;

    /* print the total number of words in the file */
	printf("[MAIN] Elapsed: %f seconds\n", (double)operating_time);

    return 0;
}

