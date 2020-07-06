#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>

int sys_mygetsid(int *n) {
	printk("system call : sys_mygetsid()");
	printk("system call : sys_mygetsid() : 2018112749\n");
	*n = 2018112749;
	return *n;
}

SYSCALL_DEFINE1(mygetsid, int*, n) {
	return sys_mygetsid(n);
}
