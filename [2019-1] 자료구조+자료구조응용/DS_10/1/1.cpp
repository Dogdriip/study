/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>

typedef struct node *treePointer;
typedef struct node {
	char data; 
	treePointer leftChild, rightChild;
}tNode;
treePointer root;

treePointer createNode(char data) {
	treePointer tmp = (treePointer)malloc(sizeof(*tmp));
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->data = data;
	return tmp;
}

void createBinTree(treePointer *root) {
	treePointer b, c, d, e;

	*root = createNode('A');
	b = createNode('B');
	c = createNode('C');
	d = createNode('D');
	e = createNode('E');

	(*root)->leftChild = b; (*root)->rightChild = c;
	b->leftChild = d; b->rightChild = e;
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
	printf("creating a binary tree\n\n");
	createBinTree(&root);

	printf("three binray tree traversals\n");
	printf("inorder traversal\t: "); inorder(root);
	printf("\npreorder traversal\t: "); preorder(root);
	printf("\npostorder traversal\t: "); postorder(root);
	printf("\n\n");

	return 0;
}