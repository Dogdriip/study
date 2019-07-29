#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

/* 섭씨 -> 화씨 */
int main() {
	int c_temp;
	scanf("%d", &c_temp);
	printf("%d\n", c_temp * 9 / 5 + 32);
	return 0;
}

/* 화씨 -> 섭씨 */
/*
int main() {
	int f_temp;
	scanf("%d", &f_temp);
	printf("%d", (f_temp - 32) * 5 / 9);
	return 0;
}
*/