/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define STRING_MAX 11
#define BUCKET_SIZE 11

typedef struct {
	char item[STRING_MAX];
	int key;
} element;
typedef struct node {
	element data;
	node* link;
} node;
typedef node* nodePointer;

nodePointer ht[BUCKET_SIZE];
int b = 11;
int comp;

unsigned int stringToInt(char *key) {
	int number = 0;
	while (*key) {
		number += *key++;
	}
	return number;
}

unsigned int h(int k) {
	return k % b;
}

element* search(int k) {
	nodePointer current;
	int homeBucket = h(k);
	comp = 1;
	for (current = ht[homeBucket]; current; current = current->link, comp++) {
		if (current->data.key == k) return &current->data;
	}
	return NULL;
}

void insert(element e) {
	int homeBucket = h(e.key);
	nodePointer current;
	nodePointer tmp = (nodePointer)malloc(sizeof(*tmp));
	strcpy(tmp->data.item, e.item);
	tmp->data.key = e.key;
	tmp->link = NULL;

	if (!ht[homeBucket]) {
		ht[homeBucket] = tmp;
		return;
	}

	if (ht[homeBucket]->data.key == tmp->data.key) {
		fprintf(stderr, "\nkey already exists\n");
		exit(1);
	}
	
	for (current = ht[homeBucket]; current->link; current = current->link) {
		if (current->data.key == tmp->data.key) {
			fprintf(stderr, "\nkey already exists\n");
			exit(1);
		}
	}
	current->link = tmp;
}

int main() {
	element tmp;
	element* res;
	nodePointer current;
	int i;
	FILE *fp = fopen("input.txt", "r");

	printf(" input strings :");
	while (!feof(fp)) {
		fscanf(fp, "%s", tmp.item);
		tmp.key = stringToInt(tmp.item);

		printf(" %s", tmp.item);
		insert(tmp);
	}

	printf("\n\n          item  key\n");
	for (i = 0; i < b; i++) {
		printf("ht[%2d] : ", i);
		for (current = ht[i]; current; current = current->link) {
			printf("(%s %d)  ", current->data.item, current->data.key);
		}
		printf("\n");
	}

	printf("\n");
	while (true) {
		printf("input ^Z to quit\n");
		printf("string to search >> ");
		if (fgets(tmp.item, STRING_MAX, stdin) == NULL) break;
		tmp.item[strlen(tmp.item) - 1] = '\0';
		tmp.key = stringToInt(tmp.item);

		res = search(tmp.key);

		if (!res) printf("it doesn't exist!\n\n");
		else printf("item: %s, key : %d, the number of comparisons : %d\n\n", res->item, res->key, comp);
	}

	return 0;
}