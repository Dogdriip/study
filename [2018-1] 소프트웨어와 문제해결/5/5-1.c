/***
* 실습1 - 최대공약수 구하기
***/

#include <stdio.h>

int gcd_itr(int a, int b) {
	int temp;
	for (; b != 0;) {
		temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

int gcd_re(int a, int b) {
	int temp;
	if (b == 0) return a;
	else {
		temp = a % b;
		if (b > temp) return gcd_re(b, temp);
		else return gcd_re(temp, b);
	}
}

int main() {
	int arr1[10], arr2[10], i;
	int gcd_by_itr;

	printf("arr1 숫자 10개 입력 : ");
	for (i = 0; i < 10; i++) {
		scanf("%d", &arr1[i]);
	}
	printf("arr2 숫자 10개 입력 : ");
	for (i = 0; i < 10; i++) {
		scanf("%d", &arr2[i]);
	}

	// iteration
	printf("GCD by iteration: ");
	for (i = 0; i < 10; i++) {
		if (arr1[i] > arr2[i])
			gcd_by_itr = gcd_itr(arr1[i], arr2[i]);
		else
			gcd_by_itr = gcd_itr(arr2[i], arr1[i]);
		printf("%d ", gcd_by_itr);
	}
	printf("\n");

	// recursion
	printf("GCD by recursion: ");
	for (i = 0; i < 10; i++) {
		printf("%d ", gcd_re(arr1[i], arr2[i]));
	}
	printf("\n");

	return 0;
}