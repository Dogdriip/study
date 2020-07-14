/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAXLEN 11
#define MAX 11

typedef struct {
	char item[MAXLEN];
	int key;
} element;

element* ht[MAX];
int b = 11;
int s = 1;
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
	int homeBucket, currentBucket;
	comp = 1;
	homeBucket = h(k);
	for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != k; comp++) {
		currentBucket = (currentBucket + 1) % b;
		if (currentBucket == homeBucket) {
			return NULL;
		}
	}
	if (ht[currentBucket] && ht[currentBucket]->key == k) {
		return ht[currentBucket];
	}
	return NULL;
}

void insert(element* e) {
	int homeBucket, currentBucket;
	homeBucket = h(e->key);
	for (currentBucket = homeBucket; ht[currentBucket] && ht[currentBucket]->key != e->key;) {
		currentBucket = (currentBucket + 1) % b;
		if (currentBucket == homeBucket) {
			if (ht[currentBucket]) {
				fprintf(stderr, "\nhash table full\n");
				exit(1);
			}
			ht[currentBucket] = e;
			return;
		}
	}

	if (ht[currentBucket] && ht[currentBucket]->key == e->key) {
		fprintf(stderr, "\nkey already exists\n");
		exit(1);
	}

	ht[currentBucket] = e;
}

int main() {
	element* tmp;
	element* res;
	int i;
	FILE *fp = fopen("input.txt", "r");

	printf(" input strings :");
	while (!feof(fp)) {
		tmp = (element*)malloc(sizeof(*tmp));
		fscanf(fp, "%s", tmp->item);
		tmp->key = stringToInt(tmp->item);

		printf(" %s", tmp->item);
		insert(tmp);
	}

	printf("\n\n                item        key\n");
	for (i = 0; i < b; i++) {
		printf("ht[%2d] : ", i);
		if (!ht[i]) printf("\n");
		else printf("%11s%11d\n", ht[i]->item, ht[i]->key);
	}

	tmp = (element*)malloc(sizeof(*tmp));
	printf("\nstring to search >> ");
	scanf("%s", tmp->item);
	tmp->key = stringToInt(tmp->item);

	res = search(tmp->key);
	
	if (!res) printf("it doesn't exist!\n");
	else printf("item: %s, key : %d, the number of comparisons : %d\n", res->item, res->key, comp);

	return 0;
}