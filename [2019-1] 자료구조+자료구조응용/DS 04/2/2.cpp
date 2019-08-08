/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#define MAX_TERMS 101
#define MAX_COL 11

typedef struct {
	int col;
	int row;
	int value;
} term;

void fastTranspose1(term *a, term *b) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = a->col, numTerms = a->value;
	b->row = numCols;
	b->col = a->row;
	b->value = numTerms;
	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) {
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; i++) {
			rowTerms[(a + i)->col]++;
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[(a + i)->col]++;
			(b + j)->row = (a + i)->col;
			(b + j)->col = (a + i)->row;
			(b + j)->value = (a + i)->value;
		}
	}
}

void fastTranspose2(term *a, term *b) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];
	int i, j, numCols = (*a).col, numTerms = (*a).value;
	(*b).row = numCols;
	(*b).col = (*a).row;
	(*b).value = numTerms;
	if (numTerms > 0) {
		for (i = 0; i < numCols; i++) {
			rowTerms[i] = 0;
		}
		for (i = 1; i <= numTerms; i++) {
			rowTerms[(*(a + i)).col]++;
		}
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++) {
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
		}
		for (i = 1; i <= numTerms; i++) {
			j = startingPos[(*(a + i)).col]++;
			(*(b + j)).row = (*(a + i)).col;
			(*(b + j)).col = (*(a + i)).row;
			(*(b + j)).value = (*(a + i)).value;
		}
	}
}

void printMatrix(term m[]) {
	int row = m[0].row, col = m[0].col, num = m[0].value;
	int ptr = 1;
	int i, j;

	// m[]이 col 기준 오름차순 정렬되어 있을 때만 작동
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			if (ptr <= num && m[ptr].row == i && m[ptr].col == j) {
				printf("%4d", m[ptr++].value);
			}
			else {
				printf("%4d", 0);
			}
		}
		printf("\n");
	}
}

int main() {
	int i;
	term a[MAX_TERMS], b[MAX_TERMS];
	FILE *fp1 = fopen("a.txt", "r");
	FILE *fp2 = fopen("b.txt", "w");

	fscanf(fp1, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
	for (i = 1; i <= a[0].value; i++) {
		fscanf(fp1, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);
	}

	// fastTranspose1(a, b);
	fastTranspose2(a, b);
	printf("A\n");
	printMatrix(a);
	printf("B\n");
	printMatrix(b);

	for (i = 0; i <= b[0].value; i++) {
		fprintf(fp2, "%d %d %d\n", b[i].row, b[i].col, b[i].value);
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}