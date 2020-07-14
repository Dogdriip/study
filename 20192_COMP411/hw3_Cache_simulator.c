// cache_sim.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//some definitions
#define FALSE 0
#define TRUE 1
#define ADDR unsigned long
#define DATA unsigned long
#define BOOL char

typedef struct _MEMREQUEST{
    ADDR addr;
    BOOL is_write;
    DATA data;
} MEMREQUEST;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct _CACHELINE {
    ADDR tag;
    BOOL valid;  // isvalid
    BOOL dirty;  // isdirty
    DATA* data;  // array of WORDs
} CACHELINE;
CACHELINE* cache;

typedef struct _MEMLINE {
    ADDR addr;  // 32bit address
    DATA data;
    struct _MEMLINE* llink;
    struct _MEMLINE* rlink;
} MEMLINE;
MEMLINE* memory_list;  // MEMORY

// new node w/ given ADDR, DATA
MEMLINE* get_node(ADDR addr, DATA data) {
    MEMLINE* tmp = (MEMLINE*)malloc(sizeof(*tmp));
    tmp->addr = addr; tmp->data = data;
    return tmp;
}

// find memory info w/ given ADDR in memory_list
MEMLINE* find_node(MEMLINE* header, ADDR addr) {
    MEMLINE* curr;
    for (curr = header->rlink; curr != header; curr = curr->rlink) {
        if (curr->addr == addr) {
            return curr;
        }
    }

    return NULL;
}

// insert new memory info in memory_list
void insert_node(MEMLINE* destnode, MEMLINE* newnode) {
	newnode->llink = destnode;
	newnode->rlink = destnode->rlink;
	destnode->rlink->llink = newnode;
	destnode->rlink = newnode;
}

int n;  // index bits num
int m;
int tag_bits_num;  // 32 - (n + m + 2)

// need shiftright before masking
unsigned long bo_mask, idx_mask, tag_mask;
unsigned long bo;  // nth byte --> must be mult of 4, needed bo /= 4 cuz data[i] means ith WORD
unsigned long idx;
unsigned long tag;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//misc. function
BOOL read_new_memrequest(FILE*, MEMREQUEST*);  //read new memory request from the memory trace file (already implemented)

//TODO: implement this function
//configure a cache
void init_cache();

//TODO: implement this function
//check if the memory request hits on the cache
BOOL isHit(MEMREQUEST *mem_request);

//TODO: implement this function
//write data to the cache. Data size is 4B
void write_data(MEMREQUEST *mem_request);

//TODO: implement this function
//insert a new block into the cache
//the initial values of the block are all zeros
void insert_to_cache(MEMREQUEST *mem_request);

//TODO: implement this function
//print the contents stored in the data storage of the cache
void print_contents();

//TODO: update this function so that some simulation statistics are calculated in it
//print the simulation statistics
void print_stats();


////global variables///
int cache_size=32768;               //cache size
int block_size=32;                  //block size
int idx_size;  // height
int word_num;  // # of WORDs in cache line

long long hit_cnt=0;               //total number of cache hits
long long miss_cnt=0;              //total number of cache misses
float miss_rate=0;                 //miss rate
long long dirty_block_num=0;       //total number of dirty blocks in cache at the end of simulation
float average_mem_access_time=0; //average memory access time
long miss_penalty=200;             //miss penalty
long cache_hit_time=1;             //cache hit time


/*
 * main
 *
 */
int main(int argc, char *argv[]) {
    char trace_file[100];
	
    //Read through command-line arguments for options.
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 's') 
                cache_size = atoi(argv[i + 1]);  // -s cachesize (32B~1024B, power of 2)
            
            if (argv[i][1] == 'b')
                block_size = atoi(argv[i + 1]);  // -b blocksize (4B~256B, power of 2)
            
            if (argv[i][1] == 'f')
                strcpy(trace_file, argv[i + 1]);  // -f tracefile (Addr / RW / Data)
        }
    }
 
    //open the mem trace file
    FILE* fp = 0;
    fp = fopen(trace_file, "r");
    if (fp == NULL) {
        printf("[error] error opening file");
        fflush(stdout);
        exit(-1);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///main body of cache simulator /////////////////
    init_cache();   //configure a cache with the cache parameters specified in the input arguments
    
    // init memory
    memory_list = (MEMLINE*)malloc(sizeof(*memory_list));
    memory_list->llink = memory_list->rlink = memory_list;

    // printf("cache_size: %d\nblock_size: %d\nidx_size: %d\n", cache_size, block_size, idx_size);
    
    n = log2(idx_size);  // index bits num
    m = log2(word_num);
    tag_bits_num = 32 - (n + m + 2);

    bo_mask = (1 << (m + 2)) - 1;
    idx_mask = ((1 << n) - 1);
    tag_mask = ((1 << tag_bits_num) - 1);


    // main loop for reading trace file
    while (1) {
        MEMREQUEST new_request;
        BOOL success = read_new_memrequest(fp, &new_request);  //read a new memory request from the memory trace file
        
        if(success != TRUE)   //check the end of the trace file
            break;
        
        // addr. interpret
        bo = (new_request.addr & bo_mask);  // nth byte --> must be mult of 4
        idx = ((new_request.addr >> (m + 2)) & idx_mask);
        tag = ((new_request.addr >> (n + m + 2)) & tag_mask);
        // addr. interpret end

        // printf("bo: %08lX\nidx: %d\ntag: %08lX\n\n", bo, idx, tag);

        //check if the new memory request hits on the cache
        //if miss on the cache, insert a new block to the cache
        if (isHit(&new_request) == FALSE) {
            // printf("missed\n");
            insert_to_cache(&new_request);  
        } else {
            // printf("hit\n");
        }

        //if the request type is a write, write data to the cache
        if (new_request.is_write) {
            write_data(&new_request);
        }
    }
    print_contents();  //print the contentns (blocks) stored in the data storage of the cache
    print_stats();     //print simulation statistics
    
    fclose(fp);
    return 0;
}

//configure a cache
void init_cache() {
    idx_size = cache_size / block_size;
    word_num = block_size / 4;
    cache = (CACHELINE*)malloc(sizeof(CACHELINE) * idx_size);
    
    for (int i = 0; i < idx_size; i++) {
        cache[i].tag = 0;
        cache[i].valid = cache[i].dirty = FALSE;
        cache[i].data = (DATA*)malloc(sizeof(DATA) * word_num);
        for (int j = 0; j < word_num; j++) {
            cache[i].data[j] = 0;
        }
    }
}

//check if the memory request hits on the cache
BOOL isHit(MEMREQUEST *mem_request) {
    // hit check : valid && tag eq.
    if (cache[idx].valid && cache[idx].tag == tag) {
        hit_cnt++;
        return TRUE;
    } else {
        miss_cnt++;
        return FALSE;
    }
}

//insert a new block into the cache
//the initial values of the block are all zeros
void insert_to_cache(MEMREQUEST *mem_request) {
    // missed. need to copy from memory to cache
    // overwrite (get out) cache[idx].data[bo] (bo /= 4 needed)

    MEMLINE* memline;

    // first, chk if it's dirty
    if (cache[idx].dirty) {
        // if dirty, write its data to memory
        // need to recover original addr.
        ADDR orig = 0;
        orig += (cache[idx].tag << (n + m + 2));
        orig += (idx << (m + 2));

        for (int i = 0; i < word_num; i++) {
            memline = find_node(memory_list, orig);
            if (memline == NULL) {
                // need to insert
                MEMLINE* newnode = get_node(orig, cache[idx].data[i]);
                insert_node(memory_list, newnode);
            } else {
                // need to overwrite
                memline->data = cache[idx].data[i];
            }

            orig += 4;
        }
    }

    memline = find_node(memory_list, mem_request->addr);
    if (memline == NULL) {
        cache[idx].data[bo / 4] = 0;
    } else {
        cache[idx].data[bo / 4] = memline->data;
    }
    cache[idx].tag = tag;
    cache[idx].valid = TRUE;
    cache[idx].dirty = FALSE;
}

//write data to the cache. Data size is 4B
void write_data(MEMREQUEST *mem_request) {
    cache[idx].tag = tag;
    cache[idx].valid = TRUE;
    cache[idx].dirty = TRUE;
    cache[idx].data[bo / 4] = mem_request->data;
}






/*
 * Function: read_new_memrequest
 * ____________________________
 * read a new memory request from the memory trace file
 *
 */
BOOL read_new_memrequest(FILE* fp, MEMREQUEST* mem_request)
{
    // ADDR request_addr;
    // DATA data;
    // char request_type[5];
    char str_read[100];
    
    if(mem_request==NULL)
    {
        fprintf(stderr,"MEMREQUEST pointer is null!");
        exit(2);
    }

    if(fgets(str_read,100,fp))
    {
        str_read[strlen(str_read) - 1] = '\0';
        char *token = strtok(str_read," ");
        if(token)
        {
            mem_request->addr=strtol(token,NULL,16);

            token=strtok(NULL," ");
            if(strcmp(token,"R")==0)
                mem_request->is_write=FALSE;
            else if(strcmp(token,"W")==0){
                mem_request->is_write=TRUE;
                token= strtok(NULL, " ");
                if(token)
                    mem_request->data=atoi(token);
                else
                { 
                    fprintf(stderr,"[error] write request with no data!!\n");
                    exit(-1);
                }
            }
            else
            {
                printf("[error] unsupported request type!:%s\n",token);
                fflush(stdout);
                exit(-1);
            }
            return TRUE;
            
        }
    }       
    
    return FALSE;
}


/*
 * Function: print_contents
 * --------------------------
 * print the contents (blocks) stored in the cache
 *
 */
void print_contents(){
    printf("\n1.Cache contents");
    printf("\nindex contents ");
    printf("\n----------------------------------------------\n");
    
    //TODO: print contents (blocks) stored in the data storage of the cache
    //for all blocks
    //   printf("%d: ", index)
    //   for all words in each block
    //      printf("%lu ", word)
    //   print("\n");
    //

    for (int i = 0; i < idx_size; i++) {
        printf("%d:", i);
        for (int j = 0; j < word_num; j++) {
            // printf("bo: %08lX\nidx: %d\ntag: %08lX\n\n", bo, idx, tag);
            printf(" %08lX", cache[i].data[j]);
        }
        printf("\n");
    }
}


/*
 * Function: print_stat
 * --------------------------
 * print the simulation statistics
 *
 */
void print_stats() {
    //TODO: Calculate some simulation statistics
    miss_rate = (float)miss_cnt / (float)(hit_cnt + miss_cnt);
    for (int i = 0; i < idx_size; i++) {
        if (cache[i].dirty) {
            dirty_block_num++;
        }
    }
    // average_mem_access_time
    average_mem_access_time = (1.0 * cache_hit_time) + (miss_rate * miss_penalty);

    //print the simualtion statistics
    printf("\n2.Simulation statistics\n");
    printf("total number of hits: %lld\n", hit_cnt);
    printf("total number of misses: %lld\n", miss_cnt);
    printf("miss rate: %f\n",miss_rate);
    printf("total number of dirty blocks: %lld\n",dirty_block_num);
    printf("average memory access time: %f\n",average_mem_access_time);
}
