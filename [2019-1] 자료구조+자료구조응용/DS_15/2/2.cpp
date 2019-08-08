/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_VERTICES 100
#define MAX_EDGES 10000
#define INF ((1 << 31) - 1)
#define TRUE 1
#define FALSE 0

typedef struct {
	int u;
	int v;
	int weight;
} edge;
edge graph[MAX_EDGES];

int weight[MAX_VERTICES][MAX_VERTICES];
int dist[MAX_VERTICES];
short int selected[MAX_VERTICES];

int get_min_vertex(int n) {
	int v, i;
	for (i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	}

	return v;
}

void prim(int s, int n) {
	int i, u, v;
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;

	for (i = 0; i < n; i++) {
		u = get_min_vertex(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		// printf("%d", u);
		for (v = 0; v < n; v++) {
			if (weight[u][v] != INF) {
				printf("(%d,%d) %d : ", u, v, weight[u][v]);
				if (!selected[v]) {
					if (dist[v] == INF) {
						printf("added\n");
						dist[v] = weight[u][v];
					}
					else if (weight[u][v] < dist[v]) {
						printf("updated (%d->%d)\n", dist[v], weight[u][v]);
						dist[v] = weight[u][v];
					}
					else printf("discarded\n");
				}
				else printf("already selected\n");
			}
		}
	}
}

int main() {
	int i, j;
	int n, m;
	int u, v, w;
	int min_cost = 0;

	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			weight[i][j] = INF;
		}
	}
	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d %d", &u, &v, &w);
		weight[u][v] = weight[v][u] = w;
	}

	prim(0, n);  // 시작점, 노드 개수

	for (i = 0; i < n; i++) {
		min_cost += dist[i];
	}
	printf("\n최소비용 : %d\n\n", min_cost);

	return 0;
}