/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_ELEMENTS 100
#define SWAP(x, y, temp) (temp = x, x = y, y = temp)

typedef struct {
	int key;
} element;

int n;
int cnt;

void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;

	cnt++;
	for (i = 1; i <= n; i++) {
		printf("%2d ", a[i].key);
	}
	printf("\n");

	if (left < right) {
		i = left; j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot);
			do j--; while (a[j].key > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}

int main() {
	int i, j;
	element a[MAX_ELEMENTS];
	FILE *fp = fopen("input.txt", "r");
	FILE* os[2] = { fopen("output.txt", "w"), stdout };

	fscanf(fp, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp, "%d", &a[i].key);
	}

	printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		printf("%2d ", a[i].key);
	}
	printf("\n");

	printf("\nexecution of quick sort ...\n");
	quickSort(a, 1, n);
	printf("calls of quick sort: %d\n\n", cnt);

	printf("<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
	fprintf(os[0], "%d\n", n);
	for (i = 1; i <= n; i++) {
		fprintf(os[0], "%d ", a[i].key);
		fprintf(os[1], "%2d ", a[i].key);
	}
	printf("\n");
	
	return 0;
}