/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXLEN 10

struct element {
	char item[MAXLEN];
	int key;
};
typedef struct element element;
typedef struct node {
	element data;
	node* link;
} node;

node** dt;
int u = 2;
int b = 8;
int depth = 2;
int comp;

int key_oct(char *item) {
	int res = 0;
	res += (item[0] - 65) + 4;
	res *= 8;
	res += (item[1] - 48);
	return res;
}

unsigned int h(int k) {
	return k % b;
}

void print_dt() {
	node* curr;
	int i;
	
	printf("\n         item  key\n");
	for (i = 0; i < (1 << u); i++) {
		printf("dt[%2d] : ", i);
		for (curr = dt[i]; curr; curr = curr->link) {
			printf("(%s  %o)  ", curr->data.item, curr->data.key);
		}
		printf("\n");
	}
	printf("\n");
}

void insert(element e) {
	short int extened = 0, succeed = 0;
	int bucket;
	int i;
	int cnt;
	node* n = (node*)malloc(sizeof(*n));
	node* curr;
	node* tmp;

	strcpy(n->data.item, e.item);
	n->data.key = e.key;
	n->link = NULL;

	bucket = h(e.key);
	if (bucket >= (1 << u)) {
		printf("\nextened directory -- ");
		dt = (node**)realloc(dt, (1 << (++u)) * sizeof(node*));
		for (i = (1 << (u - 1)); i < (1 << u); i++) {
			dt[i] = NULL;
		}
		extened = 1;
	}
	
	if (!dt[bucket]) {  // first elem 
		dt[bucket] = n;
		printf("insert item = %s, key octal = %o, ht=%d\n", dt[bucket]->data.item, dt[bucket]->data.key, h(dt[bucket]->data.key));
		if (extened) print_dt();
		return;
	}
	
	cnt = 0;
	for (curr = dt[bucket]; curr->link; curr = curr->link, cnt++);
	if (cnt == depth - 1) {
		tmp = (node*)malloc(sizeof(*tmp));
		strcpy(tmp->data.item, curr->data.item);
		tmp->data.key = curr->data.key;
		tmp->link = NULL;

		strcpy(curr->data.item, n->data.item);
		curr->data.key = n->data.key;

		printf("\nextened directory -- ");
		dt = (node**)realloc(dt, (1 << (++u)) * sizeof(node*));
		for (i = (1 << (u - 1)); i < (1 << u); i++) {
			dt[i] = NULL;
		}
		b *= 2;

		bucket = h(tmp->data.key);
		if (!dt[bucket]) {
			dt[bucket] = tmp;
			printf("insert item = %s, key octal = %o, ht=%d\n", n->data.item, n->data.key, h(n->data.key));
		}
		else {
			for (curr = dt[bucket]; curr->link; curr = curr->link);
			curr->link = tmp;
			printf("insert item = %s, key octal = %o, ht=%d\n", n->data.item, n->data.key, h(n->data.key));
		}

		print_dt();
		return;
	}
	
	curr->link = n;
	printf("insert item = %s, key octal = %o, ht=%d\n", curr->link->data.item, curr->link->data.key, h(curr->link->data.key));
	if (extened) print_dt();
}

element* search(int k) {
	node* current;
	int homeBucket = h(k);
	comp = 1;
	for (current = dt[homeBucket]; current; current = current->link, comp++) {
		if (current->data.key == k) return &current->data;
	}
	return NULL;
}

int main() {
	element data;
	element* res;
	char temp[MAXLEN];
	int i;
	FILE *fp = fopen("input.txt", "r");

	dt = (node**)calloc((1 << u), sizeof(node*));

	while (!feof(fp)) {
		fscanf(fp, "%s", data.item);
		data.key = key_oct(data.item);
		insert(data);
	}

	print_dt();
	printf("\n\n input strings : ");
	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%s", temp);
		printf("%s ", temp);
	}
	printf("\n");
	while (true) {
		printf("input ^Z to quit\n");
		printf("string to search >> ");
		if (fgets(data.item, MAXLEN, stdin) == NULL) break;
		data.item[strlen(data.item) - 1] = '\0';
		data.key = key_oct(data.item);

		res = search(data.key);

		if (!res) printf("it doesn't exist!\n\n");
		else printf("item: %s, key octal: %o, the number of comparisons : %d\n\n", res->item, res->key, comp);
	}
	
	return 0;
}
