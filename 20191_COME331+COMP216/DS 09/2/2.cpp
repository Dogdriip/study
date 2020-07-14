/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} node;

int main() {
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n;

	FILE *fp = fopen("input.txt", "r");

	printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
	
	fscanf(fp, "%d", &n);
	printf("current size of S : %d\n", n);
	printf("S = { ");
	for (i = 0; i < n; i++) {
		out[i] = FALSE; seq[i] = NULL;
		printf("%d", i);
		if (i == n - 1) printf(" }\n");
		else printf(", ");
	}

	printf("input pairs : ");
	for (i = 0; i < n; i++) {
		fscanf(fp, "%d %d", &i, &j);
		printf("%dR%d ", i, j);
		x = (nodePointer)malloc(sizeof(*x));
		x->data = j; x->link = seq[i]; seq[i] = x;
		x = (nodePointer)malloc(sizeof(*x));
		x->data = i; x->link = seq[j]; seq[j] = x;
	}
	printf("\n");

	for (i = 0; i < n; i++) {
		if (out[i] == FALSE) {
			printf("\nNew class: %5d", i);
			out[i] = TRUE;
			x = seq[i]; top = NULL;
			for (;;) {
				while (x) {
					j = x->data;
					if (out[j] == FALSE) {
						printf("%5d", j); out[j] = TRUE;
						y = x->link; x->link = top; top = x; x = y;
					}
					else x = x->link;
				}
				if (!top) break;
				x = seq[top->data]; top = top->link;
			}
		}
	}

	printf("\n");

	return 0;
}