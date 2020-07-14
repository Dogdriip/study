/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_ELEMENTS 100

typedef struct {
	int key;
} element;

int link[MAX_ELEMENTS];

int listMerge(element a[], int link[], int start1, int start2) {
	int last1, last2, lastResult = 0;
	for (last1 = start1, last2 = start2; last1 && last2;) {
		if (a[last1].key <= a[last2].key) {
			link[lastResult] = last1;
			lastResult = last1; last1 = link[last1];
		}
		else {
			link[lastResult] = last2;
			lastResult = last2; last2 = link[last2];
		}
	}

	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;
	return link[0];
}

int rmergeSort(element a[], int link[], int left, int right) {
	int mid;
	printf("left: %d, right: %d\n", left, right);
	if (left >= right) return left;
	mid = (left + right) / 2;
	return listMerge(a, link, rmergeSort(a, link, left, mid), rmergeSort(a, link, mid + 1, right));
}

void printList(element a[], int link[]) {
	int i;
	for (i = 0; link[i];) {
		printf("%d ", a[link[i]]);
		i = link[i];
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

	printf("\n\n<<<<< executing recursive merge sort >>>>>\n");
	rmergeSort(a, link, 1, n);

	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	printList(a, link);
	printf("\n\n");

	return 0;
}