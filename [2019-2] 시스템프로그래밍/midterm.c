// cp_mid.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define MAXLEN 10000
#define BUFFERSIZE 4096

void err_exit(char* msg) {
    perror(msg);
    exit(1);
}

void cp_file(char* source, char* dest) {
    // printf("called filecp: %s -> %s\n", source, dest);
    
    int in_fd, out_fd, n_chars;
    struct stat source_stat;
    char buf[BUFFERSIZE];
    
    if ((in_fd = open(source, O_RDONLY)) == -1) err_exit("source file open error");
    if (stat(source, &source_stat) == -1) err_exit("source file stat error");
    
    if ((out_fd = creat(dest, source_stat.st_mode)) == -1) err_exit("dest file write error");

	  while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
		    if (write(out_fd, buf, n_chars) != n_chars) {
            err_exit("write error");
		    }
	  }
	  if (n_chars == -1) err_exit("read error");

	  if (close(in_fd) == -1 || close(out_fd) == -1) err_exit("error closing files");

    // printf("successfully copied file: %s -> %s\n", source, dest);
}

void cp_directory(char* source, char* dest) {
    // printf("called dircp: %s -> %s\n", source, dest);

    char source_tmp[MAXLEN], dest_tmp[MAXLEN];

    struct stat source_stat;
    struct stat tmp;
    struct dirent *direntp;
    DIR *s_dir_ptr;
    
    if ((s_dir_ptr = opendir(source)) == NULL) err_exit("source dir open error");
    
    // stat source directory for get mode    
    if (stat(source, &source_stat) == -1) err_exit("source dir stat error");

    // mkdir
    if (mkdir(dest, source_stat.st_mode) == -1) err_exit("mkdir for dest error");

    // source directory traversal
    while ((direntp = readdir(s_dir_ptr)) != NULL) {
        // ignoring ".", ".."
        if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..")) {
            continue;
        }       
        
        // build source, dest fullpath
        memset(source_tmp, 0, MAXLEN);
        memset(dest_tmp, 0, MAXLEN);
        sprintf(source_tmp, "%s/%s", source, direntp->d_name);
        sprintf(dest_tmp, "%s/%s", dest, direntp->d_name);

        // check if entry is directory
        if (stat(source_tmp, &tmp) == -1) err_exit("source dir entry stat error");
        if (S_ISDIR(tmp.st_mode)) {
            // is directory
            cp_directory(source_tmp, dest_tmp);
        } else {
            // is file
            cp_file(source_tmp, dest_tmp);
        }
    }

    closedir(s_dir_ptr);

    // printf("successfully copied dir: %s -> %s\n", source, dest);
}

int main(int ac, char* av[]) {
    char* source = av[1];
    char* dest = av[2];
    DIR *d_dir_ptr = opendir(dest);

    if (ac != 3) err_exit("invalid usage");

    if (d_dir_ptr == NULL) {
        // printf("dest doest not exist\n");
        cp_directory(source, dest);
    } else {
        // printf("dest exists\n");
        strcat(dest, "/");
        strcat(dest, source);
        cp_directory(source, dest);
    }

    if (d_dir_ptr != NULL) closedir(d_dir_ptr);

    return 0;
}

