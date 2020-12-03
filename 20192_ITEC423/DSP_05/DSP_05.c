// DSP_05_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 26

typedef struct node* nodePointer;
typedef struct node {
    int u, v;  // u: key, v: value
    nodePointer link;
} node;
nodePointer ht[MAX];  // bucket 개수 MAX인 hash table


int n, m;  // vertex 개수, edge 개수
FILE *fp1, *fp2;


nodePointer search(nodePointer e) {
    int home;
    nodePointer curr;

    home = e->v;  // 찾을 bucket의 번호 : 두 번째 항목
    if (ht[home] == NULL) {
        // 해당 bucket이 비어있다면 찾는 쌍 없음
        return NULL;
    } else {
        // 해당 bucket에서 첫 번째 항목을 value로 하는 node가 있다면 return
        for (curr = ht[home]; curr; curr = curr->link) {
            if (curr->v == e->u) {
                return curr;
            }
        }
    }

    return NULL;  // cannot find
}

void insert(nodePointer e) {
	int home;
    nodePointer curr;
	
    home = e->u;  // 넣을 bucket의 번호 : 첫 번째 항목
    if (ht[home] == NULL) {
        // 해당 bucket이 비어있다면 initialize
        ht[home] = e;
    } else {
        // 해당 bucket의 맨 마지막에 삽입
        for (curr = ht[home]; curr->link; curr = curr->link);
        curr->link = e;
    }
}

int main(int argc, char* argv[]) {
    int i;
    char u_t, v_t; 
    int pair_cnt = 0;  // 총 pair 개수
    nodePointer tmp;
    nodePointer res;

    fp1 = fopen(argv[1], "r");  // argv[1] : input filename
    fp2 = fopen(argv[2], "w");  // argv[2] : output filename

    fscanf(fp1, "%d %d", &n, &m);
    for (i = 0; i < m; i++) {
        tmp = (nodePointer)malloc(sizeof(*tmp));
        tmp->link = NULL;

        fscanf(fp1, " %c %c", &u_t, &v_t);
        tmp->u = u_t - 'A'; tmp->v = v_t - 'A';  // A:0 ~ Z:25

        insert(tmp);  // hash table에 삽입

        // 삽입 후 해당 쌍에 대해 바로 반대 쌍이 있는지 검색
        res = search(tmp);
        if (res == NULL) {
            continue;
        } else {
            // 검색 결과가 있다면 해당 쌍 출력 후 pair 개수 1 증가
            fprintf(fp2, "%c %c\n", res->u + 'A', res->v + 'A');
            pair_cnt++;
        }
    }

    fprintf(fp2, "pair cnt: %d\n", pair_cnt);

    fclose(fp1);
    fclose(fp2);

    return 0;
}