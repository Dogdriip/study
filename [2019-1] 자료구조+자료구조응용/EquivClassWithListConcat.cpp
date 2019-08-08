/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1

typedef struct node *nodePointer;
typedef struct node {
    int data;
    nodePointer link;
} node;

void ldelete(nodePointer *first, nodePointer trail, nodePointer x) {
    if (trail) trail->link = x->link;
    else *first = (*first)->link;
    free(x);
}

nodePointer concatenate(nodePointer ptr1, nodePointer ptr2) {
    nodePointer temp;
    if (!ptr1) return ptr2;
    if (!ptr2) return ptr1;
    
    for (temp = ptr1->link; temp->link; temp = temp->link);
    
    temp->link = ptr2->link; return ptr1;
}

int main() {
    short int out[MAX_SIZE], start[MAX_SIZE] = {FALSE, };
    nodePointer seq[MAX_SIZE];
    nodePointer x;
    nodePointer curr, prev;
    int i, j, n;
    
    FILE *fp = fopen("input.txt", "r");
    
    printf("/* MAX_SIZE of a set S : %d */\n", MAX_SIZE);
    
    fscanf(fp, "%d", &n);
    printf("current size of S : %d\n", n);
    printf("S = { ");
    for (i = 0; i < n; i++) {
        out[i] = FALSE;
        seq[i] = (nodePointer)malloc(sizeof(*seq[i]));
        seq[i]->link = NULL;
        printf("%d", i);
        if (i == n - 1) printf(" }\n");
        else printf(", ");
    }
    
    printf("input pairs : ");
    for (i = 0; i < n; i++) {
        fscanf(fp, "%d %d", &i, &j);
        printf("%dR%d ", i, j);
        x = (nodePointer)malloc(sizeof(*x));
        x->data = j; x->link = seq[i]->link; seq[i]->link = x;
        x = (nodePointer)malloc(sizeof(*x));
        x->data = i; x->link = seq[j]->link; seq[j]->link = x;
    }
    printf("\n");
    
    for (i = 0; i < n; i++) {
        if (!out[i]) {
            out[i] = TRUE;
            start[i] = TRUE;
            
            prev = NULL;
            for (curr = seq[i]->link; curr; curr = curr->link) {
                if (!out[curr->data]) {
                    out[curr->data] = TRUE;
                    concatenate(seq[i], seq[curr->data]);
                } else {
                    ldelete(&seq[i], prev, curr);
                    curr = prev;
                }
                prev = curr;
            }
        }
    }
    
    printf("\n");
    for (i = 0; i < n; i++) {
        if (start[i]) {
            printf("%d ", i);
            for (curr = seq[i]->link; curr; curr = curr->link) {
                printf("%d ", curr->data);
            }
            printf("\n");
        }
    }
    printf("\n");
    
    return 0;
}
