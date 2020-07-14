/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>

int sumAry3D_f1(int arr[][3][4], int z, int r, int c) {
	int i, j, k, sum = 0;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum += arr[i][j][k];
			}
		}
	}

	return sum;
}

int sumAry3D_f2(int(*arr)[3][4], int z, int r, int c) {
	int i, j, k, sum = 0;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum += arr[i][j][k];
			}
		}
	}

	return sum;
}

int sumAry3D_f3(int arr[2][3][4], int z, int r, int c) {
	int i, j, k, sum = 0;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum += arr[i][j][k];
			}
		}
	}

	return sum;
}

int sumAry3D_f4(int ***arr, int z, int r, int c) {
	int i, j, k, sum = 0;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum += arr[i][j][k];
			}
		}
	}

	return sum;
}

int sumAry3D_f5(int ****arr, int z, int r, int c) {
	int i, j, k, sum = 0;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			for (k = 0; k < c; k++) {
				sum += (*arr)[i][j][k];
			}
		}
	}

	return sum;
}

void freeAry3D(int ***arr, int z, int r) {
	int i, j;
	for (i = 0; i < z; i++) {
		for (j = 0; j < r; j++) {
			free(arr[i][j]);
		}
		free(arr[i]);
	}
	free(arr);
}

int main() {
	int ary3D[][3][4] = { { { 1, 2, 3, 4 },
							{ 2, 3, 4, 5 },
							{ 3, 4, 5, 6 } },
						  { { 1, 2, 3, 4 },
							{ 2, 3, 4, 5 },
							{ 3, 4, 5, 6 } } };

	int z, r, c;
	int ***ary = (int***)malloc(sizeof(int**) * 2);
	for (z = 0; z < 2; z++) {
		ary[z] = (int**)malloc(sizeof(int*) * 3);
		for (r = 0; r < 3; r++) {
			ary[z][r] = (int*)malloc(sizeof(int) * 4);
		}
	}

	for (z = 0; z < 2; z++) {
		for (r = 0; r < 3; r++) {
			for (c = 0; c < 4; c++) {
				ary[z][r][c] = r + c + 1;
			}
		}
	}

	printf("sumAry3D_f1() %d\n", sumAry3D_f1(ary3D, 2, 3, 4));
	printf("sumAry3D_f2() %d\n", sumAry3D_f2(ary3D, 2, 3, 4));
	printf("sumAry3D_f3() %d\n", sumAry3D_f3(ary3D, 2, 3, 4));

	printf("sumAry3D_f4() %d\n", sumAry3D_f4(ary, 2, 3, 4));
	printf("sumAry3D_f5() %d\n", sumAry3D_f5(&ary, 2, 3, 4));

	freeAry3D(ary, 2, 3);
	printf("3d array - free!\n");

	return 0;
}