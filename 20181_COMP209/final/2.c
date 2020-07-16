/***
 * 소프트웨어와 문제해결 기말고사 문제 2번 소스코드
 ***/

#include <stdio.h>

int main() {
	int n;
	int i, j;
	int cnt = 0;

	scanf("%d", &n);

	if (n == 1) {
		printf("*\n");
		cnt = 1;
	}
	else if (n == 2) {
		printf(" *\n* *\n");
		cnt = 3;
	}
	else if (n >= 3) {
		for (i = 0; i < n - 2; i++) {
			for (j = 0; j < n - 2 - i; j++) printf(" ");
			for (j = 0; j < i + 1; j++) {
				printf("* ");
				cnt++;
			}
			printf("\n");
		}
		for (i = 0; i < n - 1; i++) {
			for (j = 0; j < n - 1; j++) {
				printf("* ");
				cnt++;
			}
			printf("\n");
		}
	}

	printf("\n%d\n", cnt);
	return 0;
}