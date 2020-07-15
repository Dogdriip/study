#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/syscalls.h>
int sys_hello(int x, int y) {
	printk("x : %d", x);
	printk("y : %d", y);
	printk("HELLO_SYSTEMCALL_x*y = %d\n", x*y);
	return x*y;
}

SYSCALL_DEFINE2(hello, int, x, int, y) {
	return sys_hello(x, y);
}
