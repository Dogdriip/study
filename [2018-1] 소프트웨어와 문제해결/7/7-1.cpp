#include <stdio.h>

void sortArray(int _len, int _arr[]) {
	int i, j, temp, min;
	for (i = 0; i < _len; i++) {
		min = _arr[i];
		for (j = 0; j < _len; j++) {
			if (_arr[j] < min) {
				temp = _arr[j];
				_arr[j] = _arr[i];
				_arr[i] = temp;
				min = _arr[j];
			}
		}
		for (int k = 0; k < 6; k++) {
			printf("%d ", _arr[k]);
		}
		printf("\n");
	}
}

int main() {
	int i, j, k;
	int arr1[2][3] = { {10, 5, 15}, {20, 3, 2} };
	int arr2[2][4] = { {1, 10, 5, 15}, {20, 0, 2, 0} };
	int arr1_linear[6], arr2_linear[8];
	
	//////////arr1
	//정렬 전 배열 출력
	printf("정렬 전 arr1 : \n");
	for (i = 0; i < 2; i++) {
		printf("{ ");
		for (j = 0; j < 3; j++) {
			printf("%d ", arr1[i][j]);
		}
		printf("}\n");
	}

	//2차원 배열을 1차원으로 변형
	k = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			arr1_linear[k] = arr1[i][j];
			k++;
		}
	}

	//1차원 배열 정렬
	sortArray(6, arr1_linear);

	//정렬 후 배열 출력
	printf("정렬 후 arr1 : \n{ ");
	for (i = 5; i >= 0; i--) {
		printf("%d ", arr1_linear[i]);
	}
	printf("}\n");


	printf("\n");


	//////////arr2
	//정렬 전 배열 출력
	printf("정렬 전 arr2 : \n");
	for (i = 0; i < 2; i++) {
		printf("{ ");
		for (j = 0; j < 4; j++) {
			printf("%d ", arr2[i][j]);
		}
		printf("}\n");
	}

	//2차원 배열을 1차원으로 변형
	k = 0;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 4; j++) {
			arr2_linear[k] = arr2[i][j];
			k++;
		}
	}
	
	//1차원 배열 정렬
	sortArray(8, arr2_linear);

	//정렬 후 배열 출력
	printf("정렬 후 arr2 : \n{ ");
	for (i = 7; i >= 0; i--) {
		printf("%d ", arr2_linear[i]);
	}
	printf("}\n");

	return 0;
}