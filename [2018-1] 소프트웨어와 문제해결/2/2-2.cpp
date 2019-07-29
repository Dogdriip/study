/***
 * 실습2
 ***/

#include <stdio.h>

int main() {
	int n, temp, sum = 0, avg;
	printf("과목 수 : ");
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		printf("%d번째 과목 점수 입력 : ", i + 1);
		scanf("%d", &temp);
		sum += temp;
	}

	avg = sum / n;

	if (avg >= 90)
		printf("A");
	else if (avg <= 89 && avg >= 80)
		printf("B");
	else if (avg <= 79 && avg >= 70)
		printf("C");
	else
		printf("F");
	printf("\n");
	return 0;
}