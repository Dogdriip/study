/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_CNT 100

typedef int iType;
typedef struct {
	int key;
	iType item;
} element;
typedef struct node *treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
} tNode;

element* search(treePointer root, int k) {
	if (!root) return NULL;
	if (k == root->data.key) return &(root->data);
	if (k < root->data.key) return search(root->leftChild, k);
	return search(root->rightChild, k);
}

treePointer modifiedSearch(treePointer tree, int k) {
	treePointer root = tree, prev = NULL;

	while (root) {
		prev = root;
		if (k == root->data.key) root = NULL;
		else if (k < root->data.key) root = root->leftChild;
		else root = root->rightChild;
	}
	
	return prev;
}

void insert(treePointer *node, int k, iType theItem) {
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		ptr = (treePointer)malloc(sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = ptr->rightChild = NULL;
		if (*node) {
			if (k < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
		}
		else *node = ptr;
	}
}

void inorder(treePointer node) {
	if (node == NULL) return;

	inorder(node->leftChild);
	printf("%4d", node->data.key);
	inorder(node->rightChild);
}

int main() {
	int n, sd, item;
	int i, j;
	int arr[MAX_CNT];
	treePointer tree = NULL;
	element* res;
	
	printf("random number generation (1 ~ 500)\n");
	printf("the number of nodes in BST (less than and equal to 50) : ");
	scanf("%d", &n);
	printf("seed : ");
	scanf("%d", &sd);

	printf("\ncreating a BST from random numbers\n");
	srand(sd);
	for (i = 0; i < n; i++) {
		arr[i] = rand() % 500 + 1;
		for (j = 0; j < i; j++) {
			if (arr[j] == arr[i]) {
				i--;
				break;
			}
		}
	}

	for (i = 0; i < n; i++) {
		insert(&tree, arr[i], arr[i]);
	}

	printf("the key to search : ");
	scanf("%d", &item);
	res = search(tree, item);
	if (res == NULL) {
		printf("there is no such an element\n\n");
	}
	else {
		printf("the element's item is %d\n\n", res->item);
	}

	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(tree);
	printf("\n");

	return 0;
}