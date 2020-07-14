/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_STRLEN 100
#define MAX_STACK_SIZE 100

typedef struct node *treePointer;
typedef struct node {
	char data;
	treePointer leftChild, rightChild;
}tNode;
treePointer stack[MAX_STACK_SIZE];
int top = -1;

treePointer createNode(char data) {
	treePointer tmp = (treePointer)malloc(sizeof(*tmp));
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->data = data;
	return tmp;
}

void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}

void st_push(treePointer e) {
	if (top == MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack full\n");
		exit(1);
	}

	stack[++top] = e;
}

treePointer st_pop() {
	if (top == -1) {
		fprintf(stderr, "Stack empty\n");
		exit(1);
	}

	return stack[top--];
}

int main() {
	char s[MAX_STRLEN];
	int len, i;
	treePointer tmp;
	FILE *fp = fopen("postfix.txt", "r");

	fscanf(fp, "%s", s);
	printf("input string(postfix)\t: %s\n", s);
	printf("creating its binary tree\n");

	len = strlen(s);
	for (i = 0; i < len; i++) {
		if (s[i] == '~') {
			tmp = createNode(s[i]);
			tmp->rightChild = st_pop();
			st_push(tmp);
		}
		else if (s[i] == '&' || s[i] == '|') {
			tmp = createNode(s[i]);
			tmp->rightChild = st_pop();
			tmp->leftChild = st_pop();
			st_push(tmp);
		}
		else {
			st_push(createNode(s[i]));
		}
	}

	printf("inorder traversal\t: ");
	inorder(stack[0]);
	printf("\n");

	return 0;
}