/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define FALSE 0
#define TRUE 1
#define MAX_VERTICIES 100

typedef struct qNode *queuePointer;
typedef struct qNode {
	int vertex;
	queuePointer link;
} tQNode;
queuePointer front, rear;

void addq(int item) {
	queuePointer temp = (queuePointer)malloc(sizeof(*temp));
	temp->vertex = item; temp->link = NULL;
	if (front) rear->link = temp;
	else front = temp;
	rear = temp;
}

int deleteq() {
	queuePointer temp = front;
	int item;
	if (!temp) exit(EXIT_FAILURE);
	item = temp->vertex;
	front = temp->link;
	free(temp);
	return item;
}

typedef struct node *nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
} node;

nodePointer graph[MAX_VERTICIES];
short int visited[MAX_VERTICIES];

void bfs(int v) {
	nodePointer w;
	front = rear = NULL;
	printf("%5d", v);
	visited[v] = TRUE;
	addq(v);
	while (front) {
		v = deleteq();
		for (w = graph[v]; w; w = w->link) {
			if (!visited[w->vertex]) {
				printf("%5d", w->vertex);
				addq(w->vertex);
				visited[w->vertex] = TRUE;
			}
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
	int n, m;
	int i, a, b;

	fscanf(fp, "%d %d", &n, &m);

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d", &a, &b);
		add_node(a, b);
	}

	printf("<<<<<<<<<<<<<< Adjacency List >>>>>>>>>>>>>>\n");
	for (i = 0; i < n; i++) {
		printf("graph[%d] : ", i);
		for (curr = graph[i]; curr; curr = curr->link) {
			printf("%5d", curr->vertex);
		}
		printf("\n");
	}

	printf("\n<<<<<<<<<<<<<< Breadth First Search >>>>>>>>>>>>>>\n");
	for (i = 0; i < n; i++) {
		memset(visited, FALSE, sizeof(visited));
		printf("bfs(%d) : ", i);
		bfs(i);
		printf("\n");
	}

	return 0;
}