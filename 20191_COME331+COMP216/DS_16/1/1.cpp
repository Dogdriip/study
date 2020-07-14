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
int dist[MAX_VERTICES];
short int found[MAX_VERTICES];
int path[MAX_VERTICES];

int choose() {
	int i, min, minpos;
	min = (1 << 31) - 1;
	minpos = -1;
	for (i = 0; i < n; i++) {
		if (dist[i] < min && !found[i]) {
			min = dist[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortestPath(int v) {
	int i, u, w;
	for (i = 0; i < n; i++) {
		found[i] = FALSE;
		dist[i] = cost[v][i];
	}
	found[v] = TRUE;
	dist[v] = 0;
	for (i = 0; i < n - 2; i++) {
		u = choose();
		found[u] = TRUE;
		for (w = 0; w < n; w++) {
			if (!found[w]) {
				if (dist[u] + cost[u][w] < dist[w]) {
					dist[w] = dist[u] + cost[u][w];
					path[w] = u;
				}
			}
		}
	}
}

void backtrack(int dest, int v) {
	if (path[v] == -1) return;

	backtrack(dest, path[v]);
	if (v != dest) printf("%d> <%d->", v, v);
	else printf("%d>\n", v);
}

int main() {
	int start;
	int i, j;
	int u, v, w;

	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &n, &m);

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			cost[i][j] = 10000;
		}
	}

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		cost[u][v] = cost[v][u] = w;
	}

	start = 0;
	path[start] = -1;
	shortestPath(start);

	for (i = 0; i < n; i++) {
		if (i == start) continue;
		printf("distance[%d-%d]=%d \t: ", start, i, dist[i]);
		printf("<%d->", start);
		backtrack(i, i);
	}

	return 0;
}