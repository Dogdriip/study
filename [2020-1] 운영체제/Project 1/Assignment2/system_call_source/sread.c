#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/fcntl.h>
#include <linux/file.h>

int sys_sread(int fd, char* buf, int len) {
	int i = 0;
	printk("sys_sread()\n");

	int n = ksys_read(fd, buf, len);
	for (i = 0; i < len; i++) {
		if (buf[i] == '\0') break;
		buf[i] = ~buf[i];
	}
	
	return n;
}

SYSCALL_DEFINE3(sread, int, fd, char*, buf, int, len) {
	return sys_sread(fd, buf, len);
}


