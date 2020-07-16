/***
 * 실습 2 : 지뢰찾기 
 ***/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void set_mine(int mineset[9][9], int minecnt) { // 배열 이름은 주소값
	int rand_i, rand_j;
	int i;
	for (i = 0; i < minecnt; i++) {
		rand_i = rand() % 9, rand_j = rand() % 9;
		if (mineset[rand_i][rand_j] == 0) mineset[rand_i][rand_j] = 9;
		else i--; // 중복제거, 지뢰 갯수만큼 확실히 지뢰 생성
	}
}

void print_mineset_debug(int mineset[9][9]) {
	int i, j;
	printf("***** MINESET DEBUG *****\n");
	printf("  0 1 2 3 4 5 6 7 8 ");
	printf(" x\n");
	for (i = 0; i < 9; i++) {
		printf("%d ", i);
		for (j = 0; j < 9; j++) {
			if (mineset[i][j] == 0) printf(". ");
			else if (mineset[i][j] == 9) printf("* ");
			else printf("%d ", mineset[i][j]);
		}
		printf("\n");
	}
	printf("\ny\n\n\n");
}

void print_mineset(int mineset[9][9]) {
	int i, j;
	printf("***** MINESET *****\n");
	printf("  0 1 2 3 4 5 6 7 8 ");
	printf(" x\n");
	for (i = 0; i < 9; i++) {
		printf("%d ", i);
		for (j = 0; j < 9; j++) {
			if (mineset[i][j] == 0 || mineset[i][j] == 9) printf(". "); // 빈칸, 지뢰 모두 .으로 표시
			else if (mineset[i][j] == -1) printf("0 ");
			else printf("%d ", mineset[i][j]);
		}
		printf("\n");
	}
	printf("\ny\n\n\n");
}

void iterate(int mineset[9][9], int x, int y) {
	int i, j;
	printf("\n\n -- iterating %d %d\n", x, y);
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			printf("x: %d y: %d ", (x - 1) + j, (y - 1) + i);
			if (i == 1 && j == 1) {
				printf("breaked\n");
				
			}
			else if ((y - 1) + i < 0 || (x - 1) + j < 0) {
				printf("skipped\n");
				
			}
			else if (mineset[(y - 1) + i][(x - 1) + j] == 9) {
				printf("FOUND\n");
				mineset[y][x]++;
			}
			else if (mineset[(y - 1) + i][(x - 1) + j] == 0) {
				mineset[(y - 1) + i][(x - 1) + j] = -1;
				iterate(mineset, (x - 1) + j, (y - 1) + i);
			}
		}
	}
	printf("iterate success\n");
}

int main() {
	int mineset[9][9] = { {0,}, {0,} }; // 0 : 빈칸, 9 : 지뢰, 주변 지뢰 수 최대 8개이므로
	int x, y;

	srand(time(NULL));

	set_mine(mineset, 15);
	
	print_mineset_debug(mineset);

	for (;;) {
		print_mineset(mineset);
		printf("x, y 좌표 입력 (예시: 0 0) >> ");
		scanf("%d %d", &x, &y);
		if (mineset[y][x] == 9) {
			printf("게임 종료\n");
			print_mineset_debug(mineset);
			break;
		}
		else if (mineset[y][x] != 0) {
			printf("확인된 좌표입니다\n");
		}
		else { // 0 눌렀을때
			iterate(mineset, x, y);
			printf("exit ");
		}
	}
	
	return 0;
}