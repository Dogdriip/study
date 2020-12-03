// DSP_10_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int nodeid_cnt;  // node id 설정용 (매 노드 할당마다 증가)

typedef struct node* nodeptr;
typedef struct node {  // B-Tree Node
    int id;  // node id
    int n;  // 보유 key 개수
    int keys[3];  // key 배열
    nodeptr child[4];  // child 포인터 배열
    nodeptr parent;  // 부모 노드 포인터
} node;
nodeptr root = NULL;  // B-Tree with m = 3

FILE *fp1, *fp2;

void insert_to_node(nodeptr, nodeptr, int);

nodeptr getnode() {  // 새 B-Tree 노드 할당
    nodeptr tmp = (nodeptr)malloc(sizeof(*tmp));
    tmp->id = ++nodeid_cnt;
    tmp->n = 0;
    tmp->keys[0] = tmp->keys[1] = tmp->keys[2] = -1;
    tmp->child[0] = tmp->child[1] = tmp->child[2] = tmp->child[3] = NULL;
    tmp->parent = NULL;
    
    return tmp;
}

void set_parent(nodeptr node) {  // child로 내려가면서 재귀적으로 parent 재정의
    if (node == NULL) return;
    
    int i;
    for (i = 0; i <= node->n; i++) {
        if (node->child[i]) {  // child의 parent들을 모두 node로 갱신 후, 재귀적으로 내려감
            node->child[i]->parent = node;
            set_parent(node->child[i]);
        }
    }
}

void split_node(nodeptr node) {
    int i;
    int middle_pos = 1;  // m = 3 기준으로 가운데 노드 위치
    nodeptr right_half;  // node의 중간 기준 오른쪽 노드
    nodeptr new_parent;  // 루트 split 대비
    
    right_half = getnode();
    right_half->n = 1;
    
    // 오른쪽 절반 노드에 값 복사
    right_half->keys[0] = node->keys[2];
    right_half->child[0] = node->child[2];
    right_half->child[1] = node->child[3];
    
    node->n = 1;  // node (기존 왼쪽 노드)의 key 개수는 1개

    if (node->parent) {
        // 중간 노드를 split한 경우, 부모 노드에 중간 key 하나 삽입 후 다시 split 체크해야 한다
        right_half->parent = node->parent;
        insert_to_node(node->parent, right_half, node->keys[1]);
        
        set_parent(right_half->parent);
    } else {
        // 루트 노드를 split하여 새 루트 노드가 필요한 경우
        new_parent = getnode();
        new_parent->n = 1;
        new_parent->keys[0] = node->keys[1];
        new_parent->child[0] = node;
        new_parent->child[1] = right_half;
        
        set_parent(new_parent);
        
        // 루트 노드 변수까지 새 parent로 갱신
        root = new_parent;
    }
}

void insert_to_node(nodeptr node, nodeptr child, int key) {
    // node : key가 삽입될 노드
    // child : 삽입할 key의 오른쪽 자식
    
    int i;
    int key_pos;
    
    if (node == NULL) {
        // 트리가 비어 있는 경우, 새 노드 할당 후 계속해서 삽입 필요
        node = getnode();
        root = node;
    }
    
    // 노드 내에서 key 넣을 위치 찾기
    for (key_pos = 0; key_pos < node->n; key_pos++) {
        if (key < node->keys[key_pos]) break;
    }
    
    // key를 넣어주기 위해 뒤로 한 칸씩 밀기
    node->child[node->n + 1] = node->child[node->n];
    for (i = node->n - 1; i >= key_pos; i--) {
        node->keys[i + 1] = node->keys[i];
        node->child[i + 1] = node->child[i];
    }
    
    // key 삽입
    node->keys[key_pos] = key;
    node->child[key_pos + 1] = child;  // 오른쪽 child에 삽입
    if (++(node->n) >= 3) {  // key 개수가 3이 넘었다면 split 필요
        split_node(node);
    }
}

void insert_key(nodeptr* root, int key) {  // key 삽입할 노드 찾기 (재귀적으로 호출)
    int i;

    if (*root == NULL || (*root)->child[0] == NULL) {
        // 서브트리가 비어있거나, 리프노드인 경우
        // 일단 key 삽입 후 split 판정
        insert_to_node(*root, NULL, key);
    } else {
        // 리프노드가 아닌 경우
        // key가 삽입될 위치의 child 노드 찾아서 재귀적으로 호출
        for (i = 0; i < (*root)->n; i++) {
            if (key < (*root)->keys[i]) break;
        }
        insert_key(&(*root)->child[i], key);
    }
}

void dfs(nodeptr node) {  // dfs로 트리 출력
    if (node == NULL) return;
    
    int i;
    
    fprintf(fp2, "[%2d][p%2d]: n= %d, ", node->id, (node->parent == NULL ? -1 : node->parent->id), node->n);
    fprintf(fp2, "(%2d) ", (node->child[0] == NULL ? -1 : node->child[0]->id));
    for (i = 1; i <= node->n; i++) {
        fprintf(fp2, "(%2d,%2d) ", node->keys[i - 1], (node->child[i] == NULL ? -1 : node->child[i]->id));
    }
    fprintf(fp2, "\n");
    
    for (i = 0; i <= node->n; i++) {
        dfs(node->child[i]);
    }
}

int main(int argc, char* argv[]) {
    int n;  // key 개수
    int tmp;  // 입력용 임시변수
    int i;

    fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	fp2 = fopen(argv[2], "w");  // argv[2] : output filename
    
    fscanf(fp1, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fp1, "%d", &tmp);
        
        fprintf(fp2, "Inserting %d\n", tmp);
        insert_key(&root, tmp);
        
        dfs(root);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}