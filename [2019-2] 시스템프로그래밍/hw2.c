// hw2.c

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#define BUFFERSIZE 4096
#define COPYMODE 0644

int main(int ac, char* av[]) {
    DIR *s_dir_ptr, *t_dir_ptr;  // source dir, target dir
    struct dirent *direntp;  // each entry
    struct stat info;
    int mode;  // info.st_mode

    char *filename;
    char s_fpath[BUFFERSIZE], t_fpath[BUFFERSIZE];  // source file fullpath, target file fullpath

    int in_fd, out_fd, n_chars;  // for file copy
    char buf[BUFFERSIZE];

    if (ac != 3) {
        fprintf(stderr, "usage: %s source target\n", av[0]);
        exit(1);
    }

    if ((s_dir_ptr = opendir(av[1])) == NULL) {
        fprintf(stderr, "[error] cannot open source directory : %s\n", av[1]);
        exit(1);
    }
    if ((t_dir_ptr = opendir(av[2])) == NULL) {
        fprintf(stderr, "[error] cannot open target directory : %s\n", av[2]);
        exit(1);
    }

    while ((direntp = readdir(s_dir_ptr)) != NULL) { 
        filename = direntp->d_name;

        // ignoring ".", ".."
        if (!strcmp(filename, ".") || !strcmp(filename, "..")) {
            continue;
        }

        // build source fullpath
        memset(s_fpath, 0, BUFFERSIZE);
        strcpy(s_fpath, av[1]);
        strcat(s_fpath, "/");
        strcat(s_fpath, filename);

        if (stat(s_fpath, &info) == -1) perror(s_fpath);
        else {
            mode = info.st_mode;
            
            // check if it is a directory
            if (S_ISDIR(mode)) {
                fprintf(stderr, "[error] There is a subdirectory in the source directory\n");
                exit(1);
            }

            // check if it does not have read perm (for u, g, o)
            if (!(mode & S_IRUSR) && !(mode & S_IRGRP) && !(mode & S_IROTH)) {
                continue;
            }

            // build target fullpath
            memset(t_fpath, 0, BUFFERSIZE);
            strcpy(t_fpath, av[2]);
            strcat(t_fpath, "/");
            strcat(t_fpath, filename);
            
            if ((in_fd = open(s_fpath, O_RDONLY)) == -1 || (out_fd = creat(t_fpath, mode)) == -1) {
                fprintf(stderr, "[error] error during open or creat\n");
                exit(1);
            }
            
            // copy
            while ((n_chars = read(in_fd, buf, BUFFERSIZE)) > 0) {
                if (write(out_fd, buf, n_chars) != n_chars) {
                    fprintf(stderr, "[error] Write error to %s\n", t_fpath);
                exit(1);
                }
            }
            if (n_chars == -1) {
                fprintf(stderr, "[error] Read error from %s\n", s_fpath);
                exit(1);
            }
            if (close(in_fd) == -1 || close(out_fd) == -1) {
                fprintf(stderr, "[error] Error closing files\n");
                exit(1);
            }
        }
    }

    closedir(s_dir_ptr);
    closedir(t_dir_ptr);

    return 0;
}

