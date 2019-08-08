/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_STACKS 3

typedef struct {
	int id;  // 학번
	int grade;  // 성적
} element;
typedef struct stack *stackPointer;
typedef struct stack {
	element data;
	stackPointer link;
}Node;
stackPointer top[MAX_STACKS];

void push(int i, element item) {
	stackPointer temp = (stackPointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = top[i];
	top[i] = temp;
}

element stackEmpty() {
	element tmp = { -1, -1 };
	return tmp;
}

element pop(int i) {
	stackPointer temp = top[i];
	element item;
	if (!temp) {
		return stackEmpty();
	}
	item = temp->data;
	top[i] = temp->link;
	free(temp);
	return item;
}

int main() {
	int num, id, grade;
	int i;
	element tmp, top;
	FILE *fp = fopen("input.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &num, &tmp.id, &tmp.grade);
		push(num, tmp);
	}

	printf("과목번호, 학번, 성적\n");
	for (i = 0; i < 3; i++) {
		printf("**********************\n");
		while (true) {
			element top = pop(i);
			if (top.id == -1 && top.grade == -1) break;
			printf("%8d%6d%6d\n", i, top.id, top.grade);
		}
	}

	return 0;
}