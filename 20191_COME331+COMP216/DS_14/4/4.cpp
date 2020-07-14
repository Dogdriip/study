/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICIES 100
#define MAX_EDGES 10000
#define MIN2(x, y) ((x) < (y) ? (x) : (y))

int n, m;
typedef struct node *nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} node;

nodePointer graph[MAX_VERTICIES];
short int visited[MAX_VERTICIES];

short int dfn[MAX_VERTICIES];
short int low[MAX_VERTICIES];
int num;

typedef struct edge {
	int u, v;
} edge;

edge stack[MAX_EDGES];
int top = -1;

void push(int u, int v) {
	stack[++top] = {u, v};
}

void pop(int* u, int* v) {
	*u = stack[top].u;
	*v = stack[top].v;
	top--;
}

void init() {
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

short int row[MAX_VERTICIES];

void bicon(int u, int v) {
	nodePointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u]; ptr; ptr = ptr->link) {
		w = ptr->vertex;
		if (v != w && dfn[w] < dfn[u]) {
			push(u, w);
			if (dfn[w] < 0) {
				bicon(w, u);
				low[u] = MIN2(low[u], low[w]);
				if (low[w] >= dfn[u]) {
					memset(row, FALSE, sizeof(row));
					do {
						pop(&x, &y);
						row[x] = row[y] = TRUE;
					} while (!((x == u) && (y == w)));
					
					for (int i = 0; i < n; i++) if (row[i]) printf("%d ", i);
					printf("\n");
				}
			}
			else if (w != v) low[u] = MIN2(low[u], dfn[w]);
		}
	}
}

void add_node(int a, int b) {
	nodePointer an, bn;
	an = (nodePointer)malloc(sizeof(*an)); an->vertex = a; an->link = NULL;
	bn = (nodePointer)malloc(sizeof(*bn)); bn->vertex = b; bn->link = NULL;

	bn->link = graph[a];
	graph[a] = bn;

	an->link = graph[b];
	graph[b] = an;
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	nodePointer curr;
	int i, a, b;
	short int first;

	fscanf(fp, "%d %d", &n, &m);

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d", &a, &b);
		add_node(a, b);
	}

	printf("New biconnected component:\n");
	init();
	bicon(n - 2, n - 1);

	return 0;
}