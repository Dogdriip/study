/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_ELEMENTS 100

typedef struct {
	int key;
	char name[20];
	int grade;
} element;

void insert(element e, element a[], int i) {
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}

void insertionSort(element a[], int n) {
	int j, k;
	for (j = 2; j <= n; j++) {
		element temp = a[j];
		insert(temp, a, j - 1);
	}
}

int main() {
	int n;
	int i, j;
	element a[MAX_ELEMENTS];
	FILE *fp = fopen("input.txt", "r");
	FILE* os[2] = { fopen("output.txt", "w"), stdout };

	fscanf(fp, "%d", &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp, "%d %s %d", &a[i].key, a[i].name, &a[i].grade);
	}

	printf("<<<<<<<<<<<<< Input List >>>>>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		printf("( %d, %s, %d )\n", a[i].key, a[i].name, a[i].grade);
	}
	printf("\n");

	insertionSort(a, n);

	printf("<<<<<<<<<<<<< Sorted List >>>>>>>>>>>>>\n");
	for (i = 1; i <= n; i++) {
		for (j = 0; j < 2; j++) {
			fprintf(os[j], "( %d, %s, %d )\n", a[i].key, a[i].name, a[i].grade);
		}
	}
	printf("\n");

	return 0;
}