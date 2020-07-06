#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
#include <linux/module.h>
#include <linux/fcntl.h>
#include <linux/file.h>

int sys_swrite(int fd, char* buf, int len) {
	int i;	
	printk("sys_swrite()\n");

	for (i = 0; i < len; i++) {
		buf[i] = ~buf[i];
	}
	
	int n = ksys_write(fd, buf, len);
	return n;
}

SYSCALL_DEFINE3(swrite, int, fd, char*, buf, int, len) {
	return sys_swrite(fd, buf, len);
}

