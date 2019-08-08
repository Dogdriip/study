/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_ELEMENTS 100

typedef struct {
	int key;
} element;

void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j, k, t;
	j = m + 1;
	k = i;

	while (i <= m && j <= n) {
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m) {
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	}
	else {
		for (t = i; t <= m; t++)
			mergedList[k + t - i] = initList[t];
	}
}

void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i += 2 * s) 
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	
	if (i + s - 1 < n) {
		merge(initList, mergedList, i, i + s - 1, n);
	}
	else {
		for (j = i; j <= n; j++)
			mergedList[j] = initList[j];
	}
}

void mergeSort(element a[], int n) {
	int s = 1;
	int i;
	element extra[MAX_ELEMENTS];

	while (s < n) {
		mergePass(a, extra, n, s);
		printf("segment size : %d\n", s);
		printf("           a : ");
		for (i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n");
		printf("       extra : ");
		for (i = 1; i <= n; i++) printf("%d ", extra[i]); printf("\n\n");
		s *= 2;

		mergePass(extra, a, n, s);
		printf("segment size : %d\n", s);
		printf("       extra : ");
		for (i = 1; i <= n; i++) printf("%d ", extra[i]); printf("\n");
		printf("           a : ");
		for (i = 1; i <= n; i++) printf("%d ", a[i]); printf("\n\n");
		s *= 2;
	}
}

int main() {
	int n;
	element a[MAX_ELEMENTS];
	int i, j;
	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp, "%d", &a[i].key);
	}

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i].key);
	}

	printf("\n\n<<<<< executing iterative merge sort >>>>>\n");
	mergeSort(a, n);

	printf("<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i].key);
	}
	printf("\n\n");

	return 0;
}