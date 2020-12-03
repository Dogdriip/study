// DSP_09_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define BLACK 0
#define RED 1

typedef struct node* nodeptr;
typedef struct node {
    nodeptr left;
    nodeptr right;
    nodeptr parent;
    int data;
    short int color;  // 0: BLACK, 1: RED
} node;

FILE *fp1, *fp2;

void inorder(nodeptr node) {
    if (node == NULL) return;
  
    inorder(node->left);
    fprintf(fp2, "%d(%c) ", node->data, (node->color ? 'R' : 'B'));
    inorder(node->right);
}

void preorder(nodeptr node) {
    if (node == NULL) return;
  
    fprintf(fp2, "%d(%c) ", node->data, (node->color ? 'R' : 'B'));
    preorder(node->left);
    preorder(node->right);
}

// base를 parent로 하여 rotation 수행 (parent 노드 고려)
void left_rotation(nodeptr *root, nodeptr base) {
    // base \ base_right
    // ==> base / base_right
    nodeptr base_right = base->right;  // 백업용
    
    base->right = base_right->left;
    if (base->right != NULL) {  // parent 설정
        base->right->parent = base;
    }
    base_right->parent = base->parent;

    if (base->parent == NULL) {  // root이면 root노드 갱신
        *root = base_right;
    } else  {
        if (base == base->parent->left) {
            base->parent->left = base_right;  // 왼쪽 자식을 갱신
        } else {
            base->parent->right = base_right;  // 오른쪽 자식을 갱신
        }
    }

    // base와 base_right 상하관계 변경
    base_right->left = base;
    base->parent = base_right;
}

void right_rotation(nodeptr *root, nodeptr base) {
    nodeptr base_left = base->left;
    
    base->left = base_left->right;
    if (base->left != NULL) {
        base->left->parent = base;
    }
    base_left->parent = base->parent;

    if (base->parent == NULL) {
        *root = base_left;
    } else  {
        if (base == base->parent->left) {
            base->parent->left = base_left;
        } else {
            base->parent->right = base_left;
        }
    }

    base_left->right = base;
    base->parent = base_left;
}

void rbtree_scan(nodeptr *root, nodeptr u) {
    nodeptr pu = NULL;  // parent
    nodeptr gu = NULL;  // grandparent
    
    if (*root == u) {  // root일 경우 BLACK으로 만들고 종료
        u->color = BLACK;
        return;
    }
    
    // assert(u->parent != NULL);
    while (u != *root && u->color == RED && u->parent->color == RED) {  // RED, RED, BLACK
        pu = u->parent; gu = pu->parent;
        
        if (u == pu->left) {  // _L_
            if (pu == gu->left) {  // LL_
                // LL_: gu의 오른쪽 색깔을 본다
                
                if (gu->right != NULL && gu->right->color == RED) {  // LLr: 3개 color change
                    pu->color = BLACK; gu->color = RED; gu->right->color = BLACK;
                    u = gu;  // color change는 grandparent부터 다시 올라가면서 봐야 함
                } else {  // LLb: RR rotation + 2개 color change
                    right_rotation(root, gu);
                    pu->color = BLACK; gu->color = RED;
                    break;  // b계열은 바로 종료
                }
            } else {  // RL_
                // RL_: gu의 왼쪽 색깔을 본다
                
                if (gu->left != NULL && gu->left->color == RED) {  // RLr: 3개 color change
                    pu->color = BLACK; gu->color = RED; gu->left->color = BLACK;
                    u = gu;
                } else {  // RLb: LR rotation + 2개 color change
                    right_rotation(root, pu);
                    left_rotation(root, gu);
                    u->color = BLACK; gu->color = RED;
                    break;
                }
            }
        } else {  // _R_
            if (pu == gu->left) {  // LR_
                // LR_: gu의 오른쪽 색깔을 본다
                
                if (gu->right != NULL && gu->right->color == RED) {  // LRr: 3개 color change
                    pu->color = BLACK; gu->color = RED; gu->right->color = BLACK;
                    u = gu;
                } else {  // LRb: RL rotation + 2개 color change
                    left_rotation(root, pu);
                    right_rotation(root, gu);
                    u->color = BLACK; gu->color = RED;
                    break;
                }
            } else {  // RR_
                // RR_: gu의 왼쪽 색깔을 본다
                
                if (gu->left != NULL && gu->left->color == RED) {  // RRr: 3개 color change
                    pu->color = BLACK; gu->color = RED; gu->left->color = BLACK;
                    u = gu;  // color change는 grandparent부터 다시 올라가면서 봐야 함
                } else {  // RRb: LL rotation + 2개 color change
                    left_rotation(root, gu);
                    pu->color = BLACK; gu->color = RED;
                    break;
                }
            }
        }
    }  // while end
    
    (*root)->color = BLACK;  // root 색깔은 무조건 BLACK으로 만들어주고 종료
}

void insert_node(nodeptr *root, nodeptr node) {
    // 일반적인 bst insert 수행
    if (*root == NULL) {
        *root = node;
    } else {
        nodeptr curr = *root;
        nodeptr trail = NULL;  // bst 탐색 시 curr 바로 직전 노드 (parent 설정시 사용)
        while (curr != NULL) {
            trail = curr;
            if (node->data < curr->data) {  // left
                curr = curr->left;
            } else {  // right
                curr = curr->right;
            }
        }
        node->parent = trail;
        if (node->data < trail->data) {  // left에 노드 삽입
            trail->left = node;
        } else {  // right에 노드 삽입
            trail->right = node;
        }
    }
    
    // 삽입한 노드부터 위로 올라가면서 불균형 해결
    rbtree_scan(root, node);
}

int main(int argc, char* argv[]) {
    int n;  // 노드 갯수
    int i;
    nodeptr tmp;  // 입력용 임시변수
    nodeptr root = NULL;  //  Red-Black Tree

    fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	fp2 = fopen(argv[2], "w");  // argv[2] : output filename
    
    fscanf(fp1, "%d", &n);
    for (i = 0; i < n; i++) {
        tmp = (nodeptr)malloc(sizeof(*tmp));
        fscanf(fp1, "%d", &(tmp->data));
        tmp->left = tmp->right = tmp->parent = NULL;
        tmp->color = RED;  // 새 노드의 색깔은 일단 RED로 설정
        
        fprintf(fp2, "Inserting %d\n", tmp->data);
        insert_node(&root, tmp);
        
        fprintf(fp2, "INORDER: ");
        inorder(root);
        fprintf(fp2, "\nPREORDER: ");
        preorder(root);
        fprintf(fp2, "\n\n");
    }
    
    fclose(fp1);
    fclose(fp2);
    
    return 0;
}
