/***
 * 실습 3 : 프로그램 분석
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void bubbleSort(int len, int *_arr) {
	int _i, j;
	for (_i = 0; _i < len - 1; _i++) {
		for (j = 0; j < len - 1 - _i; j++) {
			if (_arr[j] > _arr[j + 1]) {
				swap(&_arr[j], &_arr[j + 1]);
			}
		}
	}
}

void selectionSort(int len, int *_arr) {
	int _i, j;
	int idx;
	for (_i = 0; _i < len - 1; _i++) {
		idx = _i;
		for (j = _i + 1; j < len; j++)
			if (_arr[idx] > _arr[j])
				idx = j;

		swap(&_arr[_i], &_arr[idx]);
	}
}

int main() {
	int arr1[10000], arr2[10000];
	int i;
	clock_t t;

	srand(time(NULL));

	for (i = 0; i < 10000; i++) arr1[i] = rand();
	for (i = 0; i < 10000; i++) arr2[i] = rand();

	printf("Bubble sort : ");
	t = clock();
	bubbleSort(10000, arr1);
	t = clock() - t;
	printf("%lfs elapsed\n", ((double)t) / CLOCKS_PER_SEC);
	
	printf("Selection sort : ");
	t = clock();
	selectionSort(10000, arr2);
	t = clock() - t;
	printf("%lfs elapsed\n", ((double)t) / CLOCKS_PER_SEC);
	
	return 0;
}