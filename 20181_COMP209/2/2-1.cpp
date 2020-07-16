/***
 * 실습1
 ***/

#include <stdio.h>

int main() {
	int a, b, c, avg;
	printf("세 과목의 점수 각각 입력: ");
	scanf("%d %d %d", &a, &b, &c);
	
	avg = (a + b + c) / 3;
	
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