/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#define ELEMENTS 11

void insert(int e, int b[], int i, int *top) {
	b[0] = e;
	while (e < b[i]) {
		b[i + 1] = b[i];
		i--;
	}
	b[i + 1] = e;
	(*top)++;
}

void insertionSort(int a[], int n) {
	int j, k;
	int b[ELEMENTS + 1] = { -1, a[1] };
	int top = 1;

	for (j = 2; j <= n; j++) {
		int temp = a[j];
		insert(temp, b, j - 1, &top);

		for (k = 1; k <= top; k++) {
			printf("%d ", b[k]);
		}
		printf("\n");
	}
}

int main() {
	int a[ELEMENTS + 1] = { -1, 12, 2, 16, 30, 8, 28, 4, 10, 20, 6, 18 };

	insertionSort(a, ELEMENTS);

	return 0;
}