#include <unistd.h>

#define __NR_sread 439

int sread(int fd, char* buf, int len) {
	return syscall(__NR_sread, fd, buf, len);
}
