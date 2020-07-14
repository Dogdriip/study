/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 101
#define MAX_LINE_SIZE 151
#define EMPTY_ERR -2  // element의 id가 양수라고 가정할 때 작동

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAX_STACK_SIZE];
int top = -1;

element stackEmpty() {
	element tmp = { EMPTY_ERR, "" };
	return tmp;
}

element pop() {
	if (top == -1) {
		return stackEmpty();
	}
	return stack[top--];
}

void stackFull() {
	element tmp;
	fprintf(stderr, "Stack is full, cannot add element\n");
	printf("current stack elements :\n");
	while (true) {
		tmp = pop();
		if (tmp.id == EMPTY_ERR) break;
		printf("%d %s\n", tmp.id, tmp.name);
	}

	exit(EXIT_FAILURE);
}

void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		stackFull();
	}
	stack[++top] = item;
}

int main() {
	char line[MAX_LINE_SIZE];
	char *cmd;
	int line_len;
	element tmp;

	printf("<< stack operations where MAX_STACK_SIZE is %d>>\n", MAX_STACK_SIZE);
	printf("push 1 Jung\npop\n\n");
	printf("***********************************\n");

	while (true) {
		fgets(line, MAX_LINE_SIZE, stdin);
		line_len = strlen(line);
		line[line_len - 1] = ' ';

		cmd = strtok(line, " ");
		if (!strcmp(cmd, "push")) {
			tmp.id = atoi(strtok(NULL, " "));
			strcpy(tmp.name, strtok(NULL, " "));
			push(tmp);
		} else if (!strcmp(cmd, "pop")) {
			if (pop().id == EMPTY_ERR) {
				printf("stack is empty, cannot delete element.\n");
				exit(EXIT_FAILURE);
			}
		} else {
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}
