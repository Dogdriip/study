#include <unistd.h>

#define __NR_swrite 438

int swrite(int fd, char* buf, int len) {
	return syscall(__NR_swrite, fd, buf, len);
}
