/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_QUEUE_SIZE 100

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}tNode;
treePointer root;
treePointer queue[MAX_QUEUE_SIZE];
int front, rear;

void queueFull() {
	fprintf(stderr, "Queue is full\n");
	exit(EXIT_FAILURE);
}

treePointer deleteEmpty() {
	printf("Queue is empty\n");
	return NULL;
}

treePointer getFront() {
	return queue[front];
}

void addq(treePointer item) {
	if (rear == MAX_QUEUE_SIZE) queueFull();
	queue[rear++] = item;
}

treePointer deleteq() {
	if (front == rear) return deleteEmpty();
	return queue[front++];
}


int hasBothChild(treePointer pNode) {
	return pNode->leftChild != NULL && pNode->rightChild != NULL;
}

void insert(treePointer *pRoot, treePointer pNode) {
	treePointer tmp;

	if (*pRoot == NULL) {
		(*pRoot) = pNode;
	}
	else {
		while (1) {
			tmp = getFront();
			if (hasBothChild(tmp)) {
				deleteq();
				continue;
			}

			if (tmp->leftChild == NULL) {
				tmp->leftChild = pNode;
				break;
			}
			else if (tmp->rightChild == NULL) {
				tmp->rightChild = pNode;
				break;
			}
		}
	}

	addq(pNode);
}

treePointer createNode(char data) {
	treePointer tmp = (treePointer)malloc(sizeof(*tmp));
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->data = data;
	return tmp;
}

void createCompBinTree(FILE *fp) {
	char data;
	treePointer tmp;

	while (1) {
		fscanf(fp, "%c", &data);
		if (feof(fp)) break;

		tmp = createNode(data);
		insert(&root, tmp);
	}
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}

int main() {
	FILE *fp = fopen("input.txt", "r");

	printf("creating a complete binary tree\n\n");
	createCompBinTree(fp);

	printf("three binray tree traversals\n");
	printf("inorder traversal\t: "); inorder(root);
	printf("\npreorder traversal\t: "); preorder(root);
	printf("\npostorder traversal\t: "); postorder(root);
	printf("\n\n");

	return 0;
}