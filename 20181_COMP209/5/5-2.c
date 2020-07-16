/***
* 실습2 - 비선형 방정식 해 구하기
***/

#include <stdio.h>

double f1(double x) {
	return (x * x * x) - (4 * x) - 9;
}

double f2(double x) {
	return (x * x * x) - (2 * x * x) + x - 8;
}

void bisection_method_f1(double x1, double x2, double err) {
	if (f1(x1) * f1(x2) > 0) {
		printf("근이 없습니다.");
	}
	else if (f1(x1) == 0) {
		printf("%lf", x1);
	}
	else if (f1(x2) == 0) {
		printf("%lf", x2);
	}
	else {
		double abs, x = (x1 + x2) / 2;

		if (f1(x) * f1(x1) >= 0) x1 = x;
		else x2 = x;

		if (x1 - x2 >= 0) abs = x1 - x2;
		else abs = x2 - x1;

		if (abs >= err) bisection_method_f1(x1, x2, err);
		else printf("%lf ", x);
	}
}

void bisection_method_f2(double x1, double x2, double err) {
	if (f2(x1) * f2(x2) > 0) {
		printf("근이 없습니다.");
	}
	else if (f2(x1) == 0) {
		printf("%lf", x1);
	}
	else if (f2(x2) == 0) {
		printf("%lf", x2);
	}
	else {
		double abs, x = (x1 + x2) / 2;

		if (f2(x) * f2(x1) >= 0) x1 = x;
		else x2 = x;

		if (x1 - x2 >= 0) abs = x1 - x2;
		else abs = x2 - x1;

		if (abs >= err) bisection_method_f2(x1, x2, err);
		else printf("%lf ", x);
	}
}

int main() {
	double a, b, err;

	printf("a, b, err: ");
	scanf("%lf %lf %lf", &a, &b, &err);

	printf("Test1 - f1(x) = x^3 - 4x - 9의 구간 [%lf, %lf]에서의 근 : \n  >> ", a, b);
	bisection_method_f1(a, b, err);
	printf("\n");

	printf("Test2 - f2(x) = x^3 - 2x^2 + x - 8의 구간 [%lf, %lf]에서의 근 : \n  >> ", a, b);
	bisection_method_f2(a, b, err);
	printf("\n");

	return 0;
}