/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_VERTICES 100
#define TRUE 1
#define FALSE 0

int n, m;
int cost[MAX_VERTICES][MAX_VERTICES];
int dist[MAX_VERTICES][MAX_VERTICES];

void allCosts() {
	int i, j, k;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			dist[i][j] = cost[i][j];
		}
	}

	printf("k = -1\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%6d", dist[i][j]);
		}
		printf("\n");
	}

	for (k = 0; k < n; k++) {
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
				}
			}
		}

		printf("k = %d\n", k);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				printf("%6d", dist[i][j]);
			}
			printf("\n");
		}
	}
}

int main() {
	int i, j;
	int u, v, w;

	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &n, &m);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (i == j) cost[i][j] = 0;
			else cost[i][j] = 10000;
		}
	}

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		cost[u][v] = w;
	}

	allCosts();

	return 0;
}