/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>

typedef struct node *nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
} node;
nodePointer header = NULL;

void dinsert(nodePointer node, nodePointer newnode) {
	newnode->llink = node;
	newnode->rlink = node->rlink;
	node->rlink->llink = newnode;
	node->rlink = newnode;
}

void ddelete(nodePointer node, nodePointer deleted) {
	if (node == deleted) {
		printf("Deletion of header node not permitted.\n");
	}
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}

void dprint(nodePointer node, int sw) {
	nodePointer curr;
	int i = -1;
	if (sw == 0) {
		printf("forward\n");
		for (curr = node->rlink; curr != node; curr = curr->rlink) {
			if (i++ % 10 == 9) printf("\n");
			printf("%3d", curr->data);
		}
	}
	else {
		printf("backward\n");
		for (curr = node->llink; curr != node; curr = curr->llink) {
			if (i++ % 10 == 9) printf("\n");
			printf("%3d", curr->data);
		}
	}
	printf("\n\n");
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	nodePointer tmp;
	nodePointer curr;
	nodePointer temp;
	int inp;

	header = (nodePointer)malloc(sizeof(*header));
	header->llink = header;
	header->rlink = header;

	while (!feof(fp)) {
		fscanf(fp, "%d", &inp);

		tmp = (nodePointer)malloc(sizeof(*tmp));
		tmp->llink = NULL;
		tmp->rlink = NULL;
		tmp->data = inp;
		dinsert(header->llink, tmp);
	}

	printf("After creating a doubly linked circular list with a head node :\n");
	dprint(header, 0);
	dprint(header, 1);

	for (curr = header->rlink; curr != header; curr = curr->rlink) {
		if (curr->data <= 50) {
			temp = curr->llink;
			ddelete(header, curr);
			curr = temp;
		}
	}

	printf("After deleting numbers less than and equal to 50 :\n");
	dprint(header, 0);
	dprint(header, 1);

	for (curr = header->rlink; curr != header; curr = curr->rlink) {
		temp = curr->llink;
		ddelete(header, curr);
		curr = temp;
	}

	printf("After deleting all nodes except for the header node :\n");
	dprint(header, 0);
	dprint(header, 1);

	return 0;
}