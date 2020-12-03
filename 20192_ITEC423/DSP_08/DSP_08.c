// DSP_08_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

FILE *fp1, *fp2;

typedef struct element {
	int key;
} element;

typedef struct treeNode* treePointer;
typedef struct treeNode {
	treePointer leftChild;
	treePointer rightChild;
	int bf;
	element data;
} treeNode;

void inorder(treePointer ptr) {  // inorder traversal
	if (ptr) {
		inorder(ptr->leftChild);
		fprintf(fp2, "%d(%d) ", ptr->data.key, ptr->bf);
		inorder(ptr->rightChild);
	}
}

void preorder(treePointer ptr) {  // preorder traversal
	if (ptr) {
		fprintf(fp2, "%d(%d) ", ptr->data.key, ptr->bf);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void leftRotation(treePointer *parent, int *unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->leftChild;  // child: 현재 노드의 왼쪽 자식
	if (child->bf == 1) {  // 왼쪽 자식도 left에 하나가 더 있을 경우
		// LL Rotation
		(*parent)->leftChild = child->rightChild;
		child->rightChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {  // 왼쪽 자식은 right로 하나 더 가지고 있을 경우
		// LR Rotation
		grandChild = child->rightChild;
		child->rightChild = grandChild->leftChild;
		grandChild->leftChild = child;
		(*parent)->leftChild = grandChild->rightChild;
		grandChild->rightChild = *parent;  // PPT에 없음
		
		switch (grandChild->bf) {
		case 1:
			(*parent)->bf = -1;
			child->bf = 0;
			break;
		case 0:
			(*parent)->bf = 0;
			child->bf = 0;
			break;
		case -1:
			(*parent)->bf = 0;
			child->bf = 1;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

// leftRotation과 원리는 똑같고 방향만 달라 주석을 생략합니다.
void rightRotation(treePointer *parent, int *unbalanced) {
	treePointer grandChild, child;
	child = (*parent)->rightChild;
	if (child->bf == -1) {
		(*parent)->rightChild = child->leftChild;
		child->leftChild = *parent;
		(*parent)->bf = 0;
		(*parent) = child;
	}
	else {
		grandChild = child->leftChild;
		child->leftChild = grandChild->rightChild;
		grandChild->rightChild = child;
		(*parent)->rightChild = grandChild->leftChild;
		grandChild->leftChild = *parent;  // PPT에 없음

		switch (grandChild->bf) {
		case 1:
			(*parent)->bf = -1;
			child->bf = 0;
			break;
		case 0:
			(*parent)->bf = 0;
			child->bf = 0;
			break;
		case -1:
			(*parent)->bf = 0;
			child->bf = 1;
		}
		*parent = grandChild;
	}
	(*parent)->bf = 0;
	*unbalanced = FALSE;
}

void avlInsert(treePointer *parent, element x, int *unbalanced) {
	if (!*parent) {  // 그 자리에 노드가 없을 경우
		*unbalanced = TRUE;
		*parent = (treePointer)malloc(sizeof(treeNode));
		(*parent)->leftChild = (*parent)->rightChild = NULL;
		(*parent)->bf = 0; (*parent)->data = x;
	}
	else if (x.key < (*parent)->data.key) {
		// 삽입하려는 key가 더 작을 경우, leftChild에 insert
		avlInsert(&(*parent)->leftChild, x, unbalanced);
		if (*unbalanced) {  // 올라가면서 부모 노드의 bf 갱신
			switch ((*parent)->bf) {
			case -1: 
				(*parent)->bf = 0;
				*unbalanced = FALSE;  // bf가 0이 되었으므로 unbalanced = FALSE;
				break;
			case 0:
				(*parent)->bf = 1;
				break;
			case 1:  // bf가 2가 되므로 leftRotation
				leftRotation(parent, unbalanced);
			}
		}
	}
	else if (x.key > (*parent)->data.key) {
		// 삽입하려는 key가 더 클 경우, rightChild에 insert
		avlInsert(&(*parent)->rightChild, x, unbalanced);
		if (*unbalanced) {
			switch ((*parent)->bf) {
			case 1:
				(*parent)->bf = 0;
				*unbalanced = FALSE;
				break;
			case 0:
				(*parent)->bf = -1;
				break;
			case -1:  // bf가 -2가 되므로 rightRotation
				rightRotation(parent, unbalanced);
			}
		}
	}
	else {
		*unbalanced = FALSE;
		printf("The key is already in the tree\n");
	}
}

int main(int argc, char* argv[]) {
	int n;  // key 개수
	int i;
	element tmp;  // 입력받는 용도
	int ub_tmp;
	treePointer tree = NULL;  // AVL tree

	fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	fp2 = fopen(argv[2], "w");  // argv[2] : output filename

	fscanf(fp1, "%d", &n);
	for (i = 0; i < n; i++) {
		fscanf(fp1, "%d", &tmp.key);
		avlInsert(&tree, tmp, &ub_tmp);

		fprintf(fp2, "AVL Tree:\n");
		fprintf(fp2, "Preorder: ");
		preorder(tree);
		fprintf(fp2, "\nInorder: ");
		inorder(tree);
		fprintf(fp2, "\n");
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}