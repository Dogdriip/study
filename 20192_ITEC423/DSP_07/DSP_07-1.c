// DSP_07-1_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

FILE *fp1;
FILE *fp2;

// tree node
typedef struct tNode* tNodeptr;
typedef struct tNode {
    int data;
    int degree;  // 자식의 수
    tNodeptr child;  // 자식 중의 하나
    tNodeptr link;  // sibiling
    tNodeptr parent;
} tNode;

// doubly circular linked list node
typedef struct node *nodeptr;
typedef struct node {
	nodeptr llink;
	tNodeptr data;  // tNodeptr에 대한 linked list
	nodeptr rlink;
} node;

//////////////////////////////////////////////
void dinsert(nodeptr node, nodeptr newnode) {
	newnode->llink = node;
	newnode->rlink = node->rlink;
	node->rlink->llink = newnode;
	node->rlink = newnode;
}

void ddelete(nodeptr node, nodeptr deleted) {
	if (node == deleted) {
		fprintf(fp2, "Deletion of header node not permitted.\n");
	}
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}
//////////////////////////////////////////////

//////////////////////////////////////////////
tNodeptr new_tNode(int data) {  // 동적할당된 tree node 반환
    tNodeptr tmp = (tNodeptr)malloc(sizeof(*tmp));
    tmp->data = data;
    tmp->degree = 0;
    tmp->child = NULL; tmp->link = NULL; tmp->parent = NULL;

    return tmp;
}

tNodeptr merge(tNodeptr bt1, tNodeptr bt2) {  // 두 Binomial tree merge
    if (bt1->data > bt2->data) {  // 일관성을 위해 1번 트리가 2번 트리보다 항상 작게
        tNodeptr tmp = bt1;
        bt1 = bt2;
        bt2 = tmp;
    }

    assert(bt1->data <= bt2->data);

    // 1번 트리의 밑으로 2번 트리 내리기
    bt2->parent = bt1;
    bt2->link = bt1->child;
    bt1->child = bt2;
    bt1->degree++;

    return bt1;
}

nodeptr adjust(nodeptr head) {  // degree순 정렬, 같은 degree 없도록 조절
    nodeptr curr;
    nodeptr curr1 = head->rlink;
    nodeptr curr2 = head->rlink;
    nodeptr curr3 = head->rlink;

    // heap size 측정
    int size = 0;
    for (curr = head->rlink; curr != head; curr = curr->rlink) {
        size++;
    }

    if (size <= 1) {  // head has zero or one node
        return head;
    } else if (size == 2) {
        curr2 = curr1;
        curr2 = curr2->rlink;
        curr3 = head;
    } else {
        curr2 = curr2->rlink;
        curr3 = curr2;
        curr3 = curr3->rlink;
    }

    while (curr1 != head) {
        if (curr2 == head) {  // 처리할 게 하나만 남았을 경우
            // puts("1");
            curr1 = curr1->rlink;
        } else if (curr1->data->degree < curr2->data->degree) {  // pass
            // puts("2"); 
            curr1 = curr1->rlink;
            curr2 = curr2->rlink;
            if (curr3 != head) {
                curr3 = curr3->rlink;
            }
        } else if (curr3 != head && curr1->data->degree == curr2->data->degree && curr1->data->degree == curr3->data->degree) {  // 트리 세 개의 degree가 같을 경우
            // puts("3");
            curr1 = curr1->rlink;
            curr2 = curr2->rlink;
            curr3 = curr3->rlink;
        } else if (curr1->data->degree == curr2->data->degree) {  // 트리 두 개의 degree가 같을 경우
            // puts("4");
            curr1->data = merge(curr1->data, curr2->data);
            curr = curr2->rlink;  // curr2 노드 백업
            ddelete(head, curr2);  // Linked list에서 노드 delete
            curr2 = curr;
            // curr = curr2->llink;
            // ddelete(head, curr2);
            // curr2 = curr->rlink;
            if (curr3 != head) {
                curr3 = curr3->rlink;
            }
        } else {  // 해당되지 않는 경우 진행
            curr1 = curr1->rlink;
            curr2 = curr2->rlink;
            if (curr3 != head) curr3 = curr3->rlink;
        }
    }

    return head;
}

// 두 Heap union
nodeptr union_heap(nodeptr head1, nodeptr head2) {
    nodeptr new_heap = (nodeptr)malloc(sizeof(*new_heap));  // 결과 저장할 새 heap
    new_heap->llink = new_heap; new_heap->rlink = new_heap;

    nodeptr curr1 = head1->rlink;
    nodeptr curr2 = head2->rlink;

    nodeptr tmp;

    // 두 heap의 degree를 비교하며 union 수행
    while (curr1 != head1 && curr2 != head2) {
        if (curr1->data->degree <= curr2->data->degree) {
            tmp = (nodeptr)malloc(sizeof(*tmp));
            tmp->data = curr1->data;
            dinsert(new_heap->llink, tmp);

            curr1 = curr1->rlink;
        } else {
            tmp = (nodeptr)malloc(sizeof(*tmp));
            tmp->data = curr2->data;
            dinsert(new_heap->llink, tmp);

            curr2 = curr2->rlink;
        }
    }

    // heap에 남아있는 원소 처리
    while (curr1 != head1) {
        tmp = (nodeptr)malloc(sizeof(*tmp));
        tmp->data = curr1->data;
        dinsert(new_heap->llink, tmp);

        curr1 = curr1->rlink;
    }
    while (curr2 != head2) {
        tmp = (nodeptr)malloc(sizeof(*tmp));
        tmp->data = curr2->data;
        dinsert(new_heap->llink, tmp);

        curr2 = curr2->rlink;
    }

    return new_heap;
}

nodeptr insert(nodeptr head, tNodeptr node) {
    nodeptr tmp_heap = (nodeptr)malloc(sizeof(*tmp_heap));  // 결과 저장할 새 heap
    tmp_heap->llink = tmp_heap; tmp_heap->rlink = tmp_heap;
    
    nodeptr tmp_node = (nodeptr)malloc(sizeof(*tmp_node));
    tmp_node->llink = NULL; tmp_node->rlink = NULL; tmp_node->data = node;

    dinsert(tmp_heap->llink, tmp_node);  // tmp_node 하나 들어간 tmp_heap 구성

    // 노드 하나짜리 임시 heap과 기존 heap union 수행
    tmp_heap = union_heap(head, tmp_heap);
    // adjust 수행
    tmp_heap = adjust(tmp_heap);

    return tmp_heap;
}

tNodeptr get_minval(nodeptr head) {  // Heap 루트 원소들 중 최솟값 반환
    nodeptr curr = head->rlink;
    tNodeptr tmp = curr->data;
    while (curr != head) {
        if (curr->data->data < tmp->data) tmp = curr->data;
        curr = curr->rlink;
    }

    return tmp;
}

nodeptr removed_heap(tNodeptr n) {  // 원소가 제거된 새 heap 반환
    nodeptr new_heap = (nodeptr)malloc(sizeof(*new_heap));  // 결과 저장할 새 heap
    new_heap->llink = new_heap; new_heap->rlink = new_heap;
    nodeptr tmp_node;
    tNodeptr tmp = n->child;
    tNodeptr res;

    while (tmp != NULL) {  // 밑으로 내려가면서 heap을 새로 구성
        res = tmp;
        tmp = tmp->link;
        res->link = NULL;
        tmp_node = (nodeptr)malloc(sizeof(*tmp_node));
        tmp_node->data = res;
        dinsert(new_heap->rlink, tmp_node);
    }

    return new_heap;
}

nodeptr pop(nodeptr head) {  // heap에서의 pop
    nodeptr new_heap = (nodeptr)malloc(sizeof(*new_heap));  // 결과 저장할 새 heap
    new_heap->llink = new_heap; new_heap->rlink = new_heap;
    nodeptr res;

    nodeptr curr = head->rlink;
    nodeptr tmp_node;
    tNodeptr tmp = get_minval(head);  // 최솟값 찾아오기

    // 최솟값 노드를 제외한 노드들로 다시 heap 구성
    while (curr != head) {
        if (curr->data != tmp) {
            tmp_node = (nodeptr)malloc(sizeof(*tmp_node));
            tmp_node->data = curr->data;
            dinsert(new_heap->llink, tmp_node);
        }
        curr = curr->rlink;
    }

    res = removed_heap(tmp);
    new_heap = union_heap(new_heap, res);
    new_heap = adjust(new_heap);

    return new_heap;
}

void print_subtree(tNodeptr curr) {  // heap 아래의 tree들 재귀적으로 출력
    while (curr != NULL) {
        fprintf(fp2, "%d(%d) ", curr->data, curr->degree);
        print_subtree(curr->child);
        curr = curr->link;
    }   
}

void print_heap(nodeptr head) {  // BHeap 출력
    nodeptr curr = head->rlink;
    while (curr != head) {
        fprintf(fp2, "B[%d]: ", curr->data->degree);
        print_subtree(curr->data);
        fprintf(fp2, "\n");
        curr = curr->rlink;
    }
}
//////////////////////////////////////////////


int main(int argc, char* argv[]) {
    int n, m;  // bt1 size, bt2 size
    int data;  // tmp data
    int i, j;

    fp1 = fopen(argv[1], "r");  // argv[1] : input filename
    fp2 = fopen(argv[2], "w");  // argv[2] : output filename

    // BHeap A, B 초기화 (circular doubly linked list 이용)
    nodeptr bt1 = (nodeptr)malloc(sizeof(*bt1));
    bt1->llink = bt1; bt1->rlink = bt1;
    nodeptr bt2 = (nodeptr)malloc(sizeof(*bt2));
    bt2->llink = bt2; bt2->rlink = bt2;

    tNodeptr tmp;  // tmp for input
    
    fprintf(fp2, "Building BHeap of A:\n");
    fscanf(fp1, "%d", &n);
    for (i = 0; i < n; i++) {
        fscanf(fp1, "%d", &data);
        tmp = new_tNode(data);  // tree node 동적할당
        fprintf(fp2, "Inserting %d\n", data);
        bt1 = insert(bt1, tmp);  // heap에 insert
        print_heap(bt1);
    }
    fprintf(fp2, "\n\n");

    fprintf(fp2, "Building BHeap of B:\n");
    fscanf(fp1, "%d", &m);
    for (i = 0; i < m; i++) {
        fscanf(fp1, "%d", &data);
        tmp = new_tNode(data);
        fprintf(fp2, "Inserting %d\n", data);
        bt2 = insert(bt2, tmp);
        print_heap(bt2);
    }
    fprintf(fp2, "\n\n");
    
    fprintf(fp2, "Merging two BHeaps of A and B:\n");
    bt1 = union_heap(bt1, bt2);
    bt1 = adjust(bt1);
    print_heap(bt1);
    fprintf(fp2, "\n\n");

    fprintf(fp2, "After deleting two min values:\n");
    bt1 = pop(bt1);
    bt1 = pop(bt1);
    print_heap(bt1);
    fprintf(fp2, "\n");
	
	fclose(fp1);  // 입력파일 스트림 close
    fclose(fp2);  // 출력파일 스트림 close

	return 0;
}