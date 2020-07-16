/***
 * 실습3
 ***/

#include <stdio.h>
#include <math.h>

int main() {
	int a, b, c;
	double d;
	printf("a, b, c 정수 입력 (ax^2 + bx + c = 0) : ");
	scanf("%d %d %d", &a, &b, &c);

	d = b * b - 4 * a * c;
	printf("D = %lf\n", d);

	if (d > 0) {
		double root1 = (-b + sqrt(d)) / (2 * a);
		double root2 = (-b - sqrt(d)) / (2 * a);
		printf("방정식의 두 근 : %lf, %lf", root1, root2);
	}
	else if (d == 0) {
		double root = -b / (2 * a);
		printf("방정식의 중근 : %lf", root);
	}
	else if (d < 0) {
		printf("근 없음");
	}
	printf("\n");
	return 0;
}