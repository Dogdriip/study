/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

char expr[MAX_EXPR_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = -1;

precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void printToken(precedence item) {
	char c;
	switch (item) {
	case lparen: c = '('; break;
	case rparen: c = ')'; break;
	case plus: c = '+'; break;
	case minus: c = '-'; break;
	case divide: c = '/'; break;
	case times: c = '*'; break;
	case mod: c = '%';
	}
	
	printf("%c", c);
}

precedence pop() {
	if (top == -1) {
		fprintf(stderr, "Stack is empty, cannot pop element\n");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}

void push(precedence item) {
	if (top >= MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack is full, cannot add element\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}

void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c", symbol);
		} else if (token == rparen) {
			while (stack[top] != lparen) {
				printToken(pop());
			}
			pop();
		} else {
			while (isp[stack[top]] >= icp[token]) {
				printToken(pop());
			}
			push(token);
		}
	}
	while ((token = pop()) != eos) {
		printToken(token);
	}
	printf("\n");
}


int main() {
	FILE *fp = fopen("input.txt", "r");

	fscanf(fp, "%s", expr);
	postfix();

	return 0;
}
