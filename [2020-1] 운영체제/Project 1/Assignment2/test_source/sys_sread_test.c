#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define __NR_hello 436
#define __NR_mygetsid 437
#define __NR_swrite 438
#define __NR_sread 439

#define BUFSIZE 100

void to_binary(char* buf) {
	unsigned char p;
	for (int j = 0; j < strlen(buf); j++) {
		p = 0x80;
		for (int i = 0; i < 8; i++) {
			if (buf[j] & p) {
				printf("1");
			} else {
				printf("0");
			}
			p = p >> 1;
		}
		printf(" ");
	}
	printf("\n");
}

int main() {
	char *temp2;
	char *temp3;
	int fd;

	temp2 = (char*)calloc(100, sizeof(char));
	temp3 = (char*)calloc(100, sizeof(char));

	if (0 < (fd = open("./test.txt", O_RDONLY, 0644))) {
		read(fd, temp2, BUFSIZE);
		close(fd);
	} else {
		printf("Open Error\n");
		exit(-1);
	}

	printf("sys_read() data : %s\n", temp2);
	printf("sys_read() binary data : ");
	to_binary(temp2);

	if (0 < (fd = open("./test.txt", O_RDONLY, 0644))) {
		syscall(__NR_sread, fd, temp3, BUFSIZE);
		close(fd);
	} else {
		printf("Open Error\n");
		exit(-1);
	}

	printf("sys_sread() data : %s\n", temp3);
	printf("sys_sread() binary data : ");
	to_binary(temp3);
	
	return 0;
}
