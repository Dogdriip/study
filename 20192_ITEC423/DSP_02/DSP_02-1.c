// DSP_02-1_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define SIZE 8

int p, q;  // Tour 시작 위치 : (p, q)
int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};  // 세로 이동
int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};  // 가로 이동
int map[SIZE][SIZE];  // 각 칸의 방문 순서

int border(int y, int x) {  // 해당 좌표가 보드를 벗어나는지 판단
	return (y >= 0 && y < SIZE && x >= 0 && x < SIZE);
}

int backtrack(int y, int x) {
	int min_cnt = 9, min_idx = -1;  // 주변 8칸 중 출구가 가장 적은 칸의 출구 개수와 그 칸으로 가는 dy, dx 인덱스
	int cnt, idx;
	int ny, nx;  // 다음에 최종적으로 이동할 좌표 (ny, nx)
	int i, j;

	if (map[y][x] == SIZE * SIZE - 1) {  // 모든 칸을 방문했다면 true 리턴 후 종료
		return 1;
	}

	for (i = 0; i < 8; i++) { 
		ny = y + dy[i]; nx = x + dx[i]; 

		if (border(ny, nx) && map[ny][nx] == -1) {
			// 보드를 벗어나지 않고 아직 방문하지 않은 칸이라면 출구 개수 계산
			cnt = 0; 
			for (j = 0; j < 8; j++) { 
				if (border(ny + dy[j], nx + dx[j]) && map[ny + dy[j]][nx + dx[j]] == -1) {
					cnt++;
				}
			}

			// 출구 개수의 최솟값과 그의 dy, dx 인덱스 갱신
			if (min_cnt > cnt) {
				min_cnt = cnt;
				min_idx = i;
			}
		} 
	} 

	// 다음으로 가는 칸을 찾을 수 없을 경우 중도 종료
	if (min_idx == -1) return 0; 

	// 다음 좌표로 이동
	ny = y + dy[min_idx]; nx = x + dx[min_idx]; 
	map[ny][nx] = map[y][x] + 1;  // 다음 좌표의 방문순서 설정
	if (!backtrack(ny, nx)) return 0;  // 모든 좌표 방문 성공/실패 여부
	else return 1;
}

int main(int argc, char* argv[]) {
	int i, j;

	FILE *fp = fopen(argv[3], "w");  // argv[3] : output filename
	p = atoi(argv[1]); q = atoi(argv[2]);
	assert(border(q, p));  // p, q가 0보다 작거나 7보다 크면 (보드를 벗어나면) Assertion fail (Runtime error)

	// 보드 -1으로 초기화 (미방문 상태)
	for (i = 0; i < SIZE; i++) for (j = 0; j < SIZE; j++) map[i][j] = -1;

	// 내부 기준 : map[y][x] == (y, x) == (r, c)
	// Tour 시작 위치 (p, q)를 의도대로 생각하면 map[q][p]로 받아야 함
	map[q][p] = 0;
	if (!backtrack(q, p)) {
		// 모든 칸 방문하기 전에 종료됨
		fprintf(fp, "failed\n");
	} else {
		// 모든 칸 방문 성공
		fprintf(fp, "succeed\n");
	}

	// 최종 결과 출력
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			fprintf(fp, "%4d", map[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fclose(fp);  // 출력파일 스트림 close

	return 0;
}
