/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MALLOC(p, s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

void add(int **a, int **b, int **c, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			c[i][j] = a[i][j] + b[i][j];
		}
	}
}

int** make2dArray(int rows, int cols) {
	int **x, i;

	// 책에 나와 있는 MALLOC 매크로 사용 시 에러가 발생해서 직접 작성하였습니다.
	// MALLOC(x, rows * sizeof(*x));
	x = (int**)malloc(rows * sizeof(*x));

	for (i = 0; i < rows; i++) {
		// MALLOC(x[i], cols * sizeof(**x));
		x[i] = (int*)malloc(cols * sizeof(**x));
	}
	return x;
}

void init2dArray(int **arr, int rows, int cols, int k) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			arr[i][j] = i + j + k;
		}
	}
}

void print2dArray(int **arr, int rows, int cols) {
	int i, j;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%3d", arr[i][j]);
		}
		printf("\n");
	}
}

void free2dArray(int **arr, int rows) {
	int i;
	for (i = 0; i < rows; i++) {
		free(arr[i]);
	}
	free(arr);
}

int main() {
	int row, col;
	int **a;
	int **b;
	int **c;

	printf("Enter row size and column size (ex) 3 4 : ");
	scanf("%d %d", &row, &col);

	a = make2dArray(row, col);
	b = make2dArray(row, col);
	c = make2dArray(row, col);
	init2dArray(a, row, col, 1);
	init2dArray(b, row, col, 2);

	printf("matrix A\n");
	print2dArray(a, row, col);
	
	printf("\nmatrix B\n");
	print2dArray(b, row, col);

	add(a, b, c, row, col);
	
	printf("\nmatrix C\n");
	print2dArray(c, row, col);

	free2dArray(a, row);
	free2dArray(b, row);
	free2dArray(c, row);

	printf("\n2d array - free!!!\n");

	return 0;
}