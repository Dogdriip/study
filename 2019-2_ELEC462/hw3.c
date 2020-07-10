// hw3.c

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAXLEN 10001
#define MAXENT 10001

ino_t get_inode(char *);
void printpathto(ino_t);
void inum_to_name(ino_t, char *, int);


typedef struct {
    ino_t ino;
    char name[MAXLEN];
} dirrow;

dirrow a[MAXENT], tmp[MAXENT];
char currpath[MAXLEN];
int depth;
ino_t lastdir;

void mg(int start, int end) {
    int mid = (start + end) / 2;
    int i = start, j = mid + 1, k = 0;

    while (i <= mid && j <= end) {
        if (a[i].ino <= a[j].ino) tmp[k++] = a[i++];
        else tmp[k++] = a[j++];
    }

    while (i <= mid) tmp[k++] = a[i++];
    while (j <= end) tmp[k++] = a[j++];

    for (int i = start; i <= end; i++) {
        a[i] = tmp[i - start];
    }
}

void msort(int start, int end) {
    if (start == end) return;

    int mid = (start + end) / 2;
    msort(start, mid);
    msort(mid + 1, end);
    mg(start, end);
}


void print_dirrow(ino_t ino, char* name) {
    int i;
    printf("%-12ld", ino);
    for (i = 0; i < depth; i++) printf("\t");
    printf("%s\n", name);
}

void print_dir(char *dirpath) {
    DIR *dir_ptr;
    struct dirent *direntp;
    int i;
    int cnt = 0;
   
    dir_ptr = opendir(dirpath);
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }
    while ((direntp = readdir(dir_ptr)) != NULL) {
        // ignoring ".", ".."
        if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, "..")) continue;
        
        memset(a[cnt].name, 0, MAXLEN);
        memset(tmp[cnt].name, 0, MAXLEN);

        a[cnt].ino = direntp->d_ino;
        strcpy(a[cnt].name, direntp->d_name);
        cnt++;
    }
   
    // sort rows by inode
    msort(0, cnt - 1);
    // print
    for (i = 0; i < cnt; i++) {
        print_dirrow(a[i].ino, a[i].name);
    }
}

int main() {
    lastdir = get_inode(".");
    printpathto(lastdir);
    printf("The current working directory: %s\n", (!strcmp(currpath, "") ? "/" : currpath));
    return 0;
}

ino_t get_inode(char *fname) {  // find inode with filename
    struct stat info;
    if (stat(fname, &info) == -1) {
        fprintf(stderr, "Cannot stat\n");
        perror(fname);
        exit(1);
    }
    return info.st_ino;
}

void printpathto(ino_t this_inode) {
    ino_t my_inode;
    char its_name[BUFSIZ];
    if (get_inode("..") != this_inode) {
        chdir("..");
        inum_to_name(this_inode, its_name, BUFSIZ);
        my_inode = get_inode(".");

        printpathto(my_inode);
        
        // after recursion
        strcat(currpath, "/");
        strcat(currpath, its_name);
        // do not print last dir's files
        if (this_inode == lastdir) return;

        print_dir(currpath); depth++;
    } else {  // approached root
        // print "/"
        print_dirrow(this_inode, "/"); depth++;

        print_dir("/"); depth++;
        return;
    }
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen) {
    DIR *dir_ptr;
    struct dirent *direntp;
    dir_ptr = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        exit(1);
    }
    while ((direntp = readdir(dir_ptr)) != NULL) {
        if (direntp->d_ino == inode_to_find) {
            strncpy(namebuf, direntp->d_name, buflen);
            namebuf[buflen - 1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }
    fprintf(stderr, "error looking for inum %ld\n", inode_to_find);
    exit(1);
}