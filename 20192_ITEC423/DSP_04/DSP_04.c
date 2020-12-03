// DSP_04_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PATH 10000  // 지나온 정점이 많아봐야 10000개라고 가정

typedef struct node* nodeptr;
typedef struct node {
	int data;
	nodeptr link;
} node;
nodeptr adj[26];  // 인접리스트
short int visited[26];  // 방문 여부 체크
int path[MAX_PATH];  // path, path_idx : DFS 탐색에서 지나온 정점 저장할 때 사용
int path_idx;
int path_cnt;  // start -> obj 총 path 개수

int v, e, start, obj;  // vertex 개수, edge 개수, 출발 vertex 번호, 도착 vertex 번호
FILE *fp1, *fp2;


void add_node(int u, int v) {  // u -> v 간선 추가 (adj[u]의 맨 앞에 v 노드 추가)
	nodeptr vn = (nodeptr)malloc(sizeof(*vn));
    vn->data = v;
    vn->link = adj[u];
	adj[u] = vn;
}

int dfs(int x) {  // dfs(x) : x 정점에서 DFS
    nodeptr nx;
    int i;

    if (x == obj) {  // 현재 정점이 도착 정점이라면 (탐색 완료. 새로운 path 찾음)
        path[path_idx++] = x;  // 지나온 정점 마지막에 도착 정점 저장

        // 지나온 정점 모두 출력
        for (i = 0; i < path_idx; i++) {
            fprintf(fp2, "%c", path[i] + 65);
            if (i < path_idx - 1) fprintf(fp2, " -> ");
        }
        fprintf(fp2, "\n");

        path_idx--;

        path_cnt++;

        return 1;
    }

    visited[x] = 1;
    for (nx = adj[x]; nx; nx = nx->link) {  // x와 연결된 모든 정점 확인, 방문하지 않은 정점이라면 현재 정점을 지나온 정점 리스트에 넣고 다음 정점으로 탐색
        if (!visited[nx->data]) {
            path[path_idx++] = x;
            dfs(nx->data);
            path_idx--;
        }
    }
    visited[x] = 0;  // 방문 체크 해제 (백트래킹)

    return 0;
}


int main(int argc, char* argv[]) {
    nodeptr curr;
    char tmp1, tmp2;
    int i, j;

    fp1 = fopen(argv[1], "r");  // argv[1] : input filename
    fp2 = fopen(argv[2], "w");  // argv[2] : output filename

    fscanf(fp1, " %d %d %c %c", &v, &e, &tmp1, &tmp2);
    start = tmp1 - 65;  // 정점 번호 : A(0) ~ Z(25)
    obj = tmp2 - 65;

    for (i = 0; i < e; i++) {
        fscanf(fp1, " %c %c", &tmp1, &tmp2);
        add_node(tmp1 - 65, tmp2 - 65);
    }

    dfs(start);  // 시작 정점에서 DFS
    fprintf(fp2, "%d\n", path_cnt);  // DFS 종료 후 path 개수 출력

    fclose(fp1);
    fclose(fp2);

    return 0;
}