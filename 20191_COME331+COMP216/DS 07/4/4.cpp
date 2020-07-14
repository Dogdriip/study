/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_QUEUES 3

typedef struct {
	int id;  // 학번
	int grade;  // 성적
} element;
typedef struct queue *queuePointer;
typedef struct queue {
	element data;
	queuePointer link;
}Node;
queuePointer front[MAX_QUEUES], rear[MAX_QUEUES];

void addq(int i, element item) {
	queuePointer temp = (queuePointer)malloc(sizeof(*temp));
	temp->data = item;
	temp->link = NULL;
	if (front[i]) rear[i]->link = temp;
	else front[i] = temp;
	rear[i] = temp;
}

element queueEmpty() {
	element tmp = { -1, -1 };
	return tmp;
}

element deleteq(int i) {
	queuePointer temp = front[i];
	element item;
	if (!temp) return queueEmpty();
	item = temp->data;
	front[i] = temp->link;
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
		addq(num, tmp);
	}

	printf("과목번호, 학번, 성적\n");
	for (i = 0; i < 3; i++) {
		printf("**********************\n");
		while (true) {
			element top = deleteq(i);
			if (top.id == -1 && top.grade == -1) break;
			printf("%8d%6d%6d\n", i, top.id, top.grade);
		}
	}

	return 0;
}