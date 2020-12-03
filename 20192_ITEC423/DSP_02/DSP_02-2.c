// DSP_02-2_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define SIZE 8

int p, q;  // Tour 시작 위치 : (p, q)
int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2};  // 세로 이동
int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1};  // 가로 이동
int order[SIZE * SIZE];  // 각 노드의 방문 순서

short int adj[SIZE * SIZE][SIZE * SIZE];  // 인접행렬 (왼쪽 위 노드부터 0번 ~ SIZE * SIZE - 1번)
										  // adj[u][v] == 1 : u->v 간선이 존재한다


int border(int y, int x) {  // 해당 좌표가 보드를 벗어나는지 판단
	return (y >= 0 && y < SIZE && x >= 0 && x < SIZE);
}

int dfs(int node) {
	int min_cnt = 9, min_dnode = -1;  // 주변 8칸 중 출구가 가장 적은 칸의 출구 개수와 그 칸의 노드 번호
	int cnt, idx;
	int y, x;  // 현재 (y, x) 좌표
	int ny, nx;  // 다음에 최종적으로 이동할 좌표 (ny, nx)
	int i, j;

	int dnode;

	if (order[node] == SIZE * SIZE - 1) {  // 모든 칸을 방문했다면 true 리턴 후 종료
		return 1;
	}

	y = node / SIZE; x = node % SIZE;  // 현재 노드 번호로부터 현재 좌표 계산

	for (dnode = 0; dnode < SIZE * SIZE; dnode++) {  // 현재 노드의 인접행렬 행 모두 확인
		if (adj[node][dnode] && order[dnode] == -1) {
			// 현재 노드에서 가는 간선이 있고(연결되어 있고), 방문하지 않은 노드라면 출구 개수 계산
			cnt = 0;
			for (i = 0; i < SIZE * SIZE; i++) {
				if (adj[dnode][i] && order[i] == -1) {
					cnt++;
				}
			}
			// 출구 개수의 최솟값과 그의 dy, dx 인덱스 갱신
			if (min_cnt > cnt) {
				min_cnt = cnt;
				min_dnode = dnode;
			}
		}
	} 

	// 다음으로 가는 칸을 찾을 수 없을 경우 중도 종료
	if (min_dnode == -1) return 0; 

	// 다음 좌표로 이동
	order[min_dnode] = order[node] + 1;  // 다음 좌표의 방문순서 설정
	if (!dfs(min_dnode)) return 0;  // 모든 좌표 방문 성공/실패 여부
	else return 1;
}

int main(int argc, char* argv[]) {
	int i, j, k;
	int ny, nx;
	int cnode, dnode;  // 현재 노드 번호, 목적지 노드 번호
	
	FILE *fp = fopen(argv[3], "w");  // argv[3] : output filename
	p = atoi(argv[1]); q = atoi(argv[2]);
	assert(border(q, p));  // p, q가 0보다 작거나 7보다 크면 (보드를 벗어나면) Assertion fail (Runtime error)

	// 그래프(인접 행렬) 구성
	// SIZE * SIZE개의 모든 노드를 왼쪽 위부터 순회하면서, 나이트의 이동으로 갈 수 있는 곳에 인접행렬 1 체크
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			cnode = i * SIZE + j;  // 현재 노드 번호
			for (k = 0; k < 8; k++) {
				ny = i + dy[k]; nx = j + dx[k];
				if (border(ny, nx)) {  // 보드를 벗어나지만 않는다면 나이트의 이동으로 갈 수 있다는 것
					dnode = ny * SIZE + nx;  // 목적지 노드 번호
					adj[cnode][dnode] = 1;  // 인접행렬 1 체크
				}
			}
		}
	}

	// 방문 순서 배열 -1으로 초기화 (미방문 상태)
	for (i = 0; i < SIZE * SIZE; i++) order[i] = -1;

	// 내부 기준 : map[y][x] == (y, x) == (r, c)
	// Tour 시작 위치 (p, q)를 의도대로 생각하면 노드 번호는 q * SIZE + p가 되어야 함
	order[q * SIZE + p] = 0;
	if (!dfs(q * SIZE + p)) {  // y = q, x = p;
		// 모든 칸 방문하기 전에 종료됨
		fprintf(fp, "failed\n");
	} else {
		// 모든 칸 방문 성공
		fprintf(fp, "succeed\n");
	}

	// 최종 결과 출력
	for (i = 0; i < SIZE; i++) {
		for (j = 0; j < SIZE; j++) {
			fprintf(fp, "%4d", order[i * SIZE + j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "\n");

	fclose(fp);  // 출력파일 스트림 close

	return 0;
}
