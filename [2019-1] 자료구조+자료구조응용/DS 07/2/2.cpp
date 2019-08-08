/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */


#include <cstdio>
#include <cstdlib>

typedef struct listNode {
	int data;
	struct listNode *link;
} listNode;
listNode *first = NULL;

void del(listNode *first, listNode *trail, listNode *x) {
	if (trail) trail->link = x->link;
	else first = first->link;
	free(x);
}

void printList(listNode *first) {
	int cnt = 0;
	first = first->link;
	for (; first; first = first->link) {
		printf("%4d", first->data);
		cnt++;
		if (cnt % 10 == 0) printf("\n");
	}
	printf("\n");
}

void insert(listNode *first, listNode *x, int data) {
	listNode *temp = (listNode*)malloc(sizeof(*temp));
	temp->data = data;
	if (first->link) {
		temp->link = x->link;
		x->link = temp;
	}
	else {
		temp->link = NULL;
		first->link = temp;
	}
}

listNode* find(listNode *first, int data) {
	listNode *ptr = first;
	for (; ptr->link; ptr = ptr->link) {
		if (ptr->data <= data && data <= ptr->link->data) {
			return ptr;
		}
	}

	return ptr;
}

int main() {
	int tmp;
	listNode *ptr;
	listNode *trail;
	FILE *fp = fopen("input.txt", "r");

	first = (listNode*)malloc(sizeof(*first));
	first->data = NULL;
	first->link = NULL;

	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);

		ptr = find(first, tmp);
		insert(first, ptr, tmp);
	}

	printf("The ordered list contains:\n");
	printList(first);
	
	ptr = first;
	for (; ptr->link;) {
		if (ptr->link->data <= 50) del(first, ptr, ptr->link);
		else ptr = ptr->link;
	}

	printf("After deleting nodes with data less than and equal to 50\n");
	printf("The ordered list contains:\n");
	printList(first);
	
	ptr = first->link;
	if (ptr) {
		for (; ptr->link;) {
			del(first, ptr, ptr->link);
		}
		free(ptr);
	}

	return 0;
}