/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_QUEUE_SIZE 5
#define MAX_NAME_SIZE 101
#define MAX_LINE_SIZE 151
#define EMPTY_ERR -2  // element의 id가 양수라고 가정할 때 작동

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

element queueEmpty() {
	element tmp = { EMPTY_ERR, "" };
	return tmp;
}

element deleteq() {
	if (front == rear) {
		return queueEmpty();
	}
	return queue[++front];
}

void queueFull() {
	element tmp;

	if (front == -1 && rear == MAX_QUEUE_SIZE - 1) {
		fprintf(stderr, "Queue is full, cannot add element!\n");
		printf("current queue elements :\n");
		while (true) {
			tmp = deleteq();
			if (tmp.id == EMPTY_ERR) break;
			printf("%d %s\n", tmp.id, tmp.name);
		}

		exit(EXIT_FAILURE);
	} else {
		printf("array shifting...\n");

		/*
		printf("debug\n");
		for (int i = 0; i < MAX_QUEUE_SIZE; i++) {
			printf("%d ", queue[i].id);
		}
		printf("\n");
		printf("front: %d, rear: %d\n", front, rear);
		*/

		for (int i = front + 1; i < MAX_QUEUE_SIZE; i++) {
			queue[i - front - 1] = queue[i];
		}

		while (front > -1) {
			front--; rear--;
		}
	}
}

void addq(element item) {
	if (rear == MAX_QUEUE_SIZE - 1) {
		queueFull();
	}
	queue[++rear] = item;
}

int main() {
	char line[MAX_LINE_SIZE];
	char *cmd;
	int line_len;
	element tmp;

	printf("<< linear queue operations where MAX_QUEUE_SIZE is %d>>\n", MAX_QUEUE_SIZE);
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
			if (deleteq().id == EMPTY_ERR) {
				printf("queue is empty, cannot delete element.\n");
				exit(EXIT_FAILURE);
			}
		} else {
			printf("wrong command! try again!\n");
		}
	}

	return 0;
}
