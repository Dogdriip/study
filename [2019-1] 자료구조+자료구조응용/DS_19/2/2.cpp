/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_ELEMENTS 100

typedef struct {
	int key;
} element;

const int r = 10;
int d, n;

int digit(int val, int pos, int r) {
	int i;
	for (i = 0; i < d - pos - 1; i++) {
		val /= r;
	}
	return val % r;
}

void printList(element a[], int link[], int first) {
	int i;

	printf("%9s", "");
	for (i = 1; i <= n; i++) printf("[%2d]", i);
	printf("\n%9s", "link: ");
	for (i = 1; i <= n; i++) printf("%4d", link[i]);
	printf("\n%9s", "a: ");
	for (i = 1; i <= n; i++) printf("%4d", a[i].key);
	printf("\n%9s%4d\n", "first: ", first);
	printf("\n%9s", "result: ");
	for (; first; first = link[first]) {
		printf("%4d", a[first].key);
	}
	printf("\n\n");
}

void printQueues(int front[], int rear[]) {
	int i;

	printf("%9s", "");
	for (i = 0; i < r; i++) printf("[%2d]", i);
	printf("\n%9s", "rear: ");
	for (i = 0; i < r; i++) printf("%4d", rear[i]);
	printf("\n%9s", "front: ");
	for (i = 0; i < r; i++) printf("%4d", front[i]);
	printf("\n\n");
}

int radixSort(element a[], int link[], int d, int r, int n) {
	int *front, *rear;
	front = (int*)malloc(sizeof(int) * r);
	rear = (int*)malloc(sizeof(int) * r);
	memset(front, 0, sizeof(int) * r);
	memset(rear, 0, sizeof(int) * r);

	int i, bin, current, first, last;
	first = 1;
	for (i = 1; i < n; i++) link[i] = i + 1;
	link[n] = 0;

	printf("*************** initial chain ***************\n");
	printList(a, link, first);

	for (i = d - 1; i >= 0; i--) {
		for (bin = 0; bin < r; bin++) front[bin] = 0;

		for (current = first; current; current = link[current]) {
			bin = digit(a[current].key, i, r);
			if (front[bin] == 0) front[bin] = current;
			else link[rear[bin]] = current;
			rear[bin] = current;
		}

		for (bin = 0; !front[bin]; bin++);
		first = front[bin]; last = rear[bin];

		for (bin++; bin < r; bin++) {
			if (front[bin]) {
				link[last] = front[bin];
				last = rear[bin];
			}
		}
		link[last] = 0;

		printf("*************** pass %d ***************\n", d - i);
		printList(a, link, first);
		printQueues(front, rear);
	}

	return first;
}

int main() {
	element a[MAX_ELEMENTS];
	int link[MAX_ELEMENTS];
	int i;
	int res;
	FILE *fp1 = fopen("input.txt", "r");
	FILE *fp2 = fopen("output.txt", "w");

	fscanf(fp1, "%d %d", &d, &n);
	for (i = 1; i <= n; i++) {
		fscanf(fp1, "%d", &a[i].key);
	}

	res = radixSort(a, link, d, r, n);
	
	for (; res; res = link[res]) {
		fprintf(fp2, "%d ", a[res].key);
	}

	return 0;
}