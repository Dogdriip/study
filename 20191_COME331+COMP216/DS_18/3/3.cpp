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

void printList(element a[], int n) {
	int i;
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i].key);
	}
}

void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key)) child++;
		if (rootkey > a[child].key) break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}

void heapSort(element a[], int n) {
	int i, j;
	element temp;

	for (i = n / 2; i > 0; i--) {
		adjust(a, i, n);
	}
	printf("after initialization of max heap...\n");
	printList(a, n);
	printf("\n\n");
	for (i = n - 1; i > 0; i--) {
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);

		printf("step %2d: ", n - i);
		printList(a, n);
		printf("\n");
	}
}

int main() {
	int n;
	element a[MAX_ELEMENTS];
	int i, j;
	FILE *fp1 = fopen("input.txt", "r");
	FILE *fp2 = fopen("output.txt", "w");

	fscanf(fp1, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp1, "%d", &a[i].key);
	}

	printf("<<<<<<<<<< Input List >>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		printf("%d ", a[i].key);
	}

	printf("\n\n<<<<< executing heap sort >>>>>\n");
	heapSort(a, n);

	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	printList(a, n);
	printf("\n\n");

	for (i = 1; i <= n; i++) {
		fprintf(fp2, "%d ", a[i].key);
	}

	return 0;
}