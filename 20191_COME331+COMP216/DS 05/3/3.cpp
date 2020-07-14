/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_NAME_SIZE 101
#define MAX_LINE_SIZE 151
#define EMPTY_ERR -2  // element의 id가 양수라고 가정할 때 작동

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element *queue;
int capacity = 2;
int rear = 0;
int front = 0;

element queueEmpty() {
	element tmp = { EMPTY_ERR, "" };
	return tmp;
}

element deleteq() {
	if (front == rear) {
		return queueEmpty();
	}
	front = (front + 1) % capacity;
	return queue[front];
}

void copy(element* a, element* b, element* c) {
	int diff = b - a;
	for (int i = 0; i <= diff; i++) {
		*c = *(a + i);
		c++;
	}
}

void queueFull() {
	int start;
	element* newQueue;
	
	// 저번 제출과 마찬가지로 교재에 있는 MALLOC 매크로 이용시 오류가 발생하여 직접 작성한 malloc으로 대체합니다.
	newQueue = (element*)malloc(2 * capacity * sizeof(*queue));

	start = (front + 1) % capacity;
	rear--;
	if (start < 2) {
		copy(queue + start, queue + start + capacity - 1, newQueue);
	} else {
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}

	front = 2 * capacity - 1;
	rear = capacity - 1;
	capacity *= 2;
	free(queue);
	queue = newQueue;

	printf("queue capacity is doubled.\ncurrent queue capacity is %d.\n", capacity);
}

void addq(element item) {
	rear = (rear + 1) % capacity;
	if (front == rear) {
		queueFull();
	}
	queue[rear] = item;
}

int main() {
	char line[MAX_LINE_SIZE];
	char *cmd;
	int line_len;
	element tmp;

	queue = (element*)malloc(capacity * sizeof(*queue));

	printf("<< circular queue operations where the initial capacity is %d>>\n", capacity);
	printf("add 1 Jung\ndelete\n\n");
	printf("***********************************\n");

	while (true) {
		fgets(line, MAX_LINE_SIZE, stdin);
		line_len = strlen(line);
		line[line_len - 1] = ' ';

		cmd = strtok(line, " ");
		if (!strcmp(cmd, "add")) {
			tmp.id = atoi(strtok(NULL, " "));
			strcpy(tmp.name, strtok(NULL, " "));
			addq(tmp);
		} else if (!strcmp(cmd, "delete")) {
			tmp = deleteq();
			if (tmp.id == EMPTY_ERR) {
				printf("queue is empty, cannot delete element.\n");
				exit(EXIT_FAILURE);
			}
			printf("deleted item : %d %s\n", tmp.id, tmp.name);
		} else {
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}
