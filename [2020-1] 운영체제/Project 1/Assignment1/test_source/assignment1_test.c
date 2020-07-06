#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define __NR_hello 436
#define __NR_mygetsid 437

int main() {
	int *n;
	n = (int*)calloc(1, sizeof(int));
	printf("before buffer value : %d\n", *n);
	syscall(__NR_mygetsid, n);
	printf("after buffer value : %d\n", *n);
	return 0;
}
