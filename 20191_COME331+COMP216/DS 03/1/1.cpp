/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>

int sumAry2D_f1(int arr[][3], int r, int c) {
	int i, j, sum = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			sum += arr[i][j];
		}
	}
	
	return sum;
}

int sumAry2D_f2(int (*arr)[3], int r, int c) {
	int i, j, sum = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			sum += arr[i][j];
		}
	}

	return sum;
}

int sumAry2D_f3(int arr[2][3], int r, int c) {
	int i, j, sum = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			sum += arr[i][j];
		}
	}

	return sum;
}

int sumAry2D_f4(int **arr, int r, int c) {
	int i, j, sum = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			sum += arr[i][j];
		}
	}

	return sum;
}

int sumAry2D_f5(int ***arr, int r, int c) {
	int i, j, sum = 0;
	for (i = 0; i < r; i++) {
		for (j = 0; j < c; j++) {
			sum += (*arr)[i][j];
		}
	}

	return sum;
}

void freeAry2D(int **arr, int r) {
	int i;
	for (i = 0; i < r; i++) {
		free(arr[i]);
	}
	free(arr);
}

int main() {
	int ary2D[][3] = { { 1, 2, 3 },
					   { 4, 5, 6 } };

	int r, c;
	int **ary = (int**)malloc(sizeof(int*) * 2);
	for (r = 0; r < 2; r++) {
		ary[r] = (int*)malloc(sizeof(int) * 3);
	}

	for (r = 0; r < 2; r++) {
		for (c = 0; c < 3; c++) {
			ary[r][c] = r + c;
		}
	}

	printf("sumAry2D_f1() %d\n", sumAry2D_f1(ary2D, 2, 3));
	printf("sumAry2D_f2() %d\n", sumAry2D_f2(ary2D, 2, 3));
	printf("sumAry2D_f3() %d\n", sumAry2D_f3(ary2D, 2, 3));

	printf("sumAry2D_f4() %d\n", sumAry2D_f4(ary, 2, 3));
	printf("sumAry2D_f5() %d\n", sumAry2D_f5(&ary, 2, 3));

	freeAry2D(ary, 2);
	printf("2d array - free!\n");

	return 0;
}