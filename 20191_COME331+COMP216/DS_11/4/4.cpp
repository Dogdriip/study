/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_STRLEN 100
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int operand_num;
int comb;  // 상위비트부터 a

typedef enum {not, and, or, tr, fa} logical;
typedef struct node *treePointer;
typedef struct node {
	treePointer leftChild;
	char ch;
	logical data;
	short int value;
	treePointer rightChild;
} node;
treePointer stack[MAX_STACK_SIZE];
int top = -1;

logical ctol(char ch) {
	switch (ch) {
	case '~': return not;
	case '&': return and;
	case '|': return or ;
	default: return tr;  // operands default
	}
}

void postOrderEval(treePointer node) {
	if (node) {
		postOrderEval(node->leftChild);
		postOrderEval(node->rightChild);
		switch (node->data) {
		case not:
			node->value = !node->rightChild->value;
			break;
		case and:
			node->value = node->rightChild->value && node->leftChild->value;
			break;
		case or:
			node->value = node->rightChild->value || node->leftChild->value;
			break;
		case tr:
			node->value = TRUE;
			break;
		case fa:
			node->value = FALSE;
		}
	}
}

treePointer createNode(char ch) {
	treePointer tmp = (treePointer)malloc(sizeof(*tmp));
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->ch = ch;
	tmp->data = ctol(ch);
	return tmp;
}

void replace_operands(treePointer ptr) {
	if (ptr) {
		if (ptr->ch >= 97 && ptr->ch <= 122) {
			ptr->data = (comb & (1 << (operand_num - (ptr->ch - 97)))) ? tr : fa;
		}
		replace_operands(ptr->leftChild);
		replace_operands(ptr->rightChild);
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
			operand_num = MAX(operand_num, s[i] - 97);
		}
	}

	printf("satisfiability = ");
	for (comb = 0; comb < (1 << (operand_num + 1)); comb++) {
		// printf("%d\n", comb);
		replace_operands(stack[0]);
		postOrderEval(stack[0]);
		if (stack[0]->value) {
			printf("TRUE\n");
			printf("when ");
			for (i = 0; i <= operand_num; i++) {
				printf("%c = %c", i + 97, (comb & (1 << (operand_num - i)) ? 'T' : 'F'));
				if (i == operand_num) printf(".\n");
				else printf(", ");
			}
			exit(0);
		}
	}
	
	printf("FALSE\n");

	return 0;
}