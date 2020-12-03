// DSP_01_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

int m, n;  // m : rows, n : cols
int imove[8] = {-1, 0, 1, 1, 1, 0, -1, -1};  // 가로 이동
int jmove[8] = {1, 1, 1, 0, -1, -1, -1, 0};  // 세로 이동
int** map;  // 각 칸의 방문횟수
int remain_zero;  // 한 번도 방문하지 않은 칸 수 (0이 되면 Backtracking 종료)
int final_x, final_y;  // 최종 방문 위치

void backtrack(int x, int y) {
	int nx, ny;  // 다음에 이동할 좌표 (nx, ny)
	int rd;  // 0~7 사이의 랜덤값

	if(map[x][y]++ == 0) remain_zero--;  // 현재 방문한 위치의 방문횟수 1 증가 (한 번도 방문하지 않은 칸이였다면 remain_zero 1 감소)
	if (!remain_zero) {  // 모든 칸을 방문했다면 최종 방문 위치 기록 후 종료
		final_x = x; final_y = y;
		return;  
	}

	do {
		rd = rand() % 8;
		nx = x + imove[rd]; ny = y + jmove[rd];
	} while (!(nx >= 0 && nx < m && ny >= 0 && ny < n));  // 경계를 벗어나지 않는 다음 좌표 (nx, ny) 설정

	backtrack(nx, ny);  // 다음 좌표로 이동
}

int main(int argc, char* argv[]) {
	int i, j;
	FILE *fp = fopen(argv[3], "w");  // argv[3] : output filename

	m = atoi(argv[1]); n = atoi(argv[2]);
	assert(m > 0 && n > 0);  // m, n이 0보다 작거나 같으면 Assertion fail (Runtime error)

	// 2차원 배열 동적할당
	map = (int**)malloc(sizeof(int*) * m);
	for (i = 0; i < m; i++) {
		map[i] = (int*)malloc(sizeof(int) * n);
	}

	srand(time(NULL));  // 랜덤 시드값 설정
	// 초기 방문횟수 0으로 초기화
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			map[i][j] = 0;
		}
	}
	remain_zero = m * n;
	
	backtrack(m / 2, n / 2);  // 시작 위치 (m / 2, n / 2)에서 Backtracking 시작

	fprintf(fp, "(%d, %d)\n", final_x, final_y);  // 최종 방문 위치 출력
	// 각 칸의 방문횟수 출력
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			fprintf(fp, "%4d", map[i][j]);
		}
		fprintf(fp, "\n");
	}

	// 2차원 배열 할당 해제
	for (i = 0; i < m; i++) {
		free(map[i]);
	}
	free(map);
	
	fclose(fp);  // 출력파일 스트림 close

	return 0;
}