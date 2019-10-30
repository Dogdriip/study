// DSP_06_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#define SWAP(a,b) {leftistTree t = a; a = b; b = t;}

typedef struct {
	int key;
	int depth;
} qelem;




typedef struct {
	int key;
} element;
typedef struct leftist *leftistTree;
struct leftist {
	leftistTree leftChild;
	element data;
	leftistTree rightChild;
	int shortest;
};



leftistTree queue[100001];
int front, rear;
void pop() {
	front++;
}
void push(leftistTree e) {
	queue[rear++] = e;
}
leftistTree first() {
	return queue[front];
}









void minUnion(leftistTree *a, leftistTree *b) {
	if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b);
	if (!(*a)->rightChild) (*a)->rightChild = *b;
	else minUnion(&(*a)->rightChild, b);

	if (!(*a)->leftChild) {
		(*a)->leftChild = (*a)->rightChild;
		(*a)->rightChild = NULL;
	}
	else if ((*a)->leftChild->shortest < (*a)->rightChild->shortest) SWAP((*a)->leftChild, (*a)->rightChild);
	(*a)->shortest = (!(*a)->rightChild) ? 1 : (*a)->rightChild->shortest + 1;
}

void minMeld(leftistTree *a, leftistTree *b) {
	if (!*a) *a = *b;
	else if (*b) minUnion(a, b);
	*b = NULL;
}

leftistTree newNode(element data) {
	leftistTree tmp = (leftistTree)malloc(sizeof(*tmp));
	tmp->data = data;
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->shortest = 0;
	return tmp;
}


void bfs(leftistTree *t) {


	leftistTree curr;
	front = rear = 0;
	push(*t);
	printf("%d\n", (*t)->data.key);

	while (front != rear) {		
		curr = first();
		pop();

		if (curr) {
			if (curr->leftChild) {
				push(curr->leftChild);
			}
			else {
				push(NULL);
			}
			if (curr->rightChild) {
				push(curr->rightChild);				
			}
			else {
				push(NULL);
			}
		}

		
	}
	
	// 출력만 잘하자
}


int main(int argc, char* argv[]) {
	int n1, n2;

	leftistTree lt1 = NULL;
	leftistTree lt2 = NULL;

	leftistTree tmp;
	element tmp_e;
	int i;


	FILE *fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	FILE *fp2 = fopen(argv[2], "w");  // argv[2] : output filename


	// 1번 min leftist tree 구성
	fscanf(fp1, "%d", &n1);
	for (i = 0; i < n1; i++) {
		fscanf(fp1, "%d", &tmp_e.key);
		tmp = newNode(tmp_e);
		if (!lt1) {
			lt1 = tmp;
		} else {			
			minMeld(&lt1, &tmp);
		}
	}

	bfs(&lt1);


	// 2번 min leftist tree 구성
	fscanf(fp1, "%d", &n2);
	for (i = 0; i < n2; i++) {
		fscanf(fp1, "%d", &tmp_e.key);
		tmp = newNode(tmp_e);
		if (!lt2) {
			lt2 = tmp;
		}
		else {
			minMeld(&lt2, &tmp);
		}
	}

	bfs(&lt2);

	

	fclose(fp1);  // 입력파일 스트림 close
	fclose(fp2);  // 출력파일 스트림 close

	return 0;
}