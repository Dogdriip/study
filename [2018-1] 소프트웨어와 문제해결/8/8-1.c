/***
* 실습 1 : n번째로 큰 수 찾기
***/
#include <stdio.h>

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(int _l, int *_arr) {
	int _i, _j;
	int idx;
	for (_i = 0; _i < _l - 1; _i++) {
		idx = _i;
		for (_j = _i + 1; _j < _l; _j++)
			if (_arr[idx] > _arr[_j])
				idx = _j;

		swap(&_arr[_i], &_arr[idx]);
	}
}

int main() {
	int l, n, arr[100], query[100];
	int i;
	scanf("%d %d", &l, &n);
	for (i = 0; i < l; i++) scanf("%d", &arr[i]);
	for (i = 0; i < n; i++) scanf("%d", &query[i]);

	selectionSort(l, arr);

	for (i = 0; i < n; i++) printf("%d\n", arr[l - query[i]]);

	return 0;
}