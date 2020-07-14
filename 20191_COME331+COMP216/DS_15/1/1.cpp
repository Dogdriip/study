/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_VERTICES 100
#define MAX_EDGES 10000
#define HEAP_FULL(n) (n == MAX_EDGES - 1)
#define HEAP_EMPTY(n) (!n)

typedef struct {
	int u;
	int v;
	int weight;
} edge;
edge graph[MAX_EDGES];
edge heap[MAX_EDGES];
int heap_t;

void push(edge item, int *heap_t) {
	int i;
	if (HEAP_FULL(*heap_t)) exit(EXIT_FAILURE);
	i = ++(*heap_t);
	while ((i != 1) && (item.weight < heap[i / 2].weight)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

edge pop(int *heap_t) {
	int parent, child;
	edge item, temp;
	if (HEAP_EMPTY(*heap_t)) exit(EXIT_FAILURE);

	item = heap[1];
	temp = heap[(*heap_t)--];
	parent = 1;
	child = 2;
	while (child <= *heap_t) {
		if ((child < *heap_t) && (heap[child].weight > heap[child + 1].weight)) {
			child++;
		}
		if (temp.weight <= heap[child].weight) {
			break;
		}
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}


int parent[MAX_VERTICES];

void Union(int i, int j) {
	parent[i] = j;
}

int Find(int i) {
	for (; parent[i] >= 0; i = parent[i]);
	return i;
}


int kruskal(int n) {
	int edge_accepted = 0;
	int uset, vset;
	int total_cost = 0;
	edge e;

	memset(parent, -1, sizeof(parent));

	while (edge_accepted < (n - 1) && !HEAP_EMPTY(heap_t)) {
		e = pop(&heap_t);
		printf("(%d,%d) %d : ", e.u, e.v, e.weight);

		uset = Find(e.u); vset = Find(e.v);
		if (uset != vset) {
			edge_accepted++;
			Union(uset, vset);
			total_cost += e.weight;
			printf("added\n");
		}
		else {
			printf("discarded\n");
		}
	}

	while (!HEAP_EMPTY(heap_t)) {
		e = pop(&heap_t);
		printf("(%d,%d) %d : not considered\n", e.u, e.v, e.weight);
	}

	return total_cost;
}


int main() {
	int i;
	int n, m;
	int min_cost;
	edge tmp;
	int edge_accepted = 0;
	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%d %d", &n, &m);
	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d %d", &tmp.u, &tmp.v, &tmp.weight);
		push(tmp, &heap_t);
	}

	min_cost = kruskal(n);
	printf("\n최소비용 : %d\n\n", min_cost);

	return 0;
}