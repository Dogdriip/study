// DSP_03-2_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define MAX_ELEMENTS 201  // heap 최대 크기 200으로 가정
#define MAX_QUEUE_SIZE 201

typedef struct node *nodeptr;
typedef struct node {
	int key;
	nodeptr leftChild, rightChild, parent;
} node;

int n;  // heap의 크기
nodeptr root;
int step[MAX_ELEMENTS];  // 트리에서 노드 번호로 가기 위한 경로 탐색용

short int visited[1000001];  // 수 중복체크. 수의 범위가 0~1000000이라 가정


nodeptr createNode(int key) {  // 노드 동적할당
	nodeptr tmp = (nodeptr)malloc(sizeof(*tmp));
	tmp->leftChild = NULL; tmp->rightChild = NULL; tmp->parent = NULL;
	tmp->key = key;
	return tmp;
}


// 트리 순회용 queue, bfs
nodeptr queue[MAX_QUEUE_SIZE];
int rear;
int front;

nodeptr deleteq() {
	if (front == rear) {
		return NULL;
	}
	return queue[++front];
}

void addq(nodeptr item) {
	if (rear == MAX_QUEUE_SIZE - 1) {
		fprintf(stderr, "Queue is full\n");
		exit(1);
	}
	queue[++rear] = item;
}

void bfs() {  // 루트에서 bfs 탐색으로 트리 순회 시작
	nodeptr curr;

	int cnt = 1;
	int pow2 = 2;
	rear = -1; front = -1;
	addq(root);  // queue 초기화

	while ((curr = deleteq()) != NULL) {
		printf("%d ", curr->key);
		
		if (curr->leftChild) addq(curr->leftChild);
		if (curr->rightChild) addq(curr->rightChild);

		if (++cnt == pow2) {
			printf("\n");
			pow2 <<= 1;
		}  // 트리 level마다 줄바꿈
	}
	printf("\n\n");
}


void push(nodeptr node) {
	int i;
	int nnode;
	int step_cnt;
	if (n == MAX_ELEMENTS - 1) {  // heap full 처리
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	if (root == NULL && !n) {
		// heap이 비어있다면 루트로 설정
		root = node;
		n = 1;
	} else {
		nnode = ++n;  // heap의 크기 1 증가, i는 추가될 맨 마지막 노드 번호
		
		// 루트에서 nnode로 가는 경로 탐색 (0: left, 1: right) (밑에서부터 찾으므로 실제로 탐색할 때는 데이터를 역순으로 봐야 함)
		step_cnt = 0;
		while (nnode != 1) {
			if (nnode % 2 == 0) step[step_cnt++] = 0;
			else step[step_cnt++] = 1;
			nnode /= 2;
		}

		nodeptr curr = root;
		for (i = step_cnt - 1; i >= 0; i--) {
			if (step[i] == 0) {  // left
				if (!i) {  // 마지막 원소라면 (노드를 추가해야 할 위치라면) 추가 후 break
					curr->leftChild = node;
					node->parent = curr;
					break;
				} else {
					curr = curr->leftChild;
				}
			} else {  // right
				if (!i) {
					curr->rightChild = node;
					node->parent = curr;
					break;
				} else {
					curr = curr->rightChild;
				}
			}
		}

		// node의 key와 부모 노드의 key를 비교해가면서 부모 노드의 key가 더 크다면 key값만 서로 교체
		// 루트까지 올라가거나 부모 노드의 key가 더 작을 때까지 반복
		curr = node;
		int nodekey = curr->key;
		while (curr->parent != NULL && nodekey < curr->parent->key) {
			curr->key = curr->parent->key;
			curr = curr->parent;
		}
		curr->key = nodekey;

		// bfs();
	}
}

int pop() {
	nodeptr curr;
	int nnode, step_cnt;
	int i;
	nodeptr parent, child;
	int parent_n, child_n;
	int item, temp;
	if (root == NULL && !n) {  // heap empty 처리
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}

	if (root->leftChild == NULL && root->rightChild == NULL) {  // 마지막 하나 남은 원소일 경우
		item = root->key;
		free(root);
		root = NULL;
		n--;
		return item;
	}

	item = root->key;  // 삭제할 원소 (루트 노드)의 key
	// 마지막 노드로 이동 (경로 탐색)
	nnode = n;
	step_cnt = 0;
	while (nnode != 1) {
		if (nnode % 2 == 0) step[step_cnt++] = 0;
		else step[step_cnt++] = 1;
		nnode /= 2;
	}
	curr = root;
	for (i = step_cnt - 1; i >= 0; i--) {
		if (step[i] == 0) {  // left
			curr = curr->leftChild;
		} else {  // right
			curr = curr->rightChild;
		}
	}
	temp = curr->key;  // heap의 맨 마지막 노드의 key를 임시변수에 저장
	assert(curr->leftChild == NULL && curr->rightChild == NULL);  // curr은 마지막 노드이므로 리프노드여야 함
	// 마지막 노드 삭제
	if (step[0] == 0) curr->parent->leftChild = NULL;
	else curr->parent->rightChild = NULL;  // 지나온 길에 따라 leftChild 혹은 rightChild 링크 삭제
	free(curr);  // 메모리 해제
	n--;  // heap의 크기 1 감소

	// 위에서부터 내려오면서 맨 마지막 원소 (temp)를 어디에 넣을지 결정
	curr = root;
	while (curr->leftChild != NULL) {
		if (curr->rightChild != NULL && curr->leftChild->key > curr->rightChild->key) {
			// using rightChild
			if (temp <= curr->rightChild->key) break;  // 자식의 key가 temp의 key보다 크거나 같다면, 그 부모 위치에 temp 저장
			curr->key = curr->rightChild->key;
			curr = curr->rightChild;
		} else {
			// using leftChild
			if (temp <= curr->leftChild->key) break;
			curr->key = curr->leftChild->key;
			curr = curr->leftChild;
		}
	}
	curr->key = temp;
	
	visited[item] = 0;
	return item;
}


int main(int argc, char* argv[]) {
	int num;  // 입력받을 key 개수
	nodeptr tmp;  // 입력받을 때 사용할 임시변수
	int tmp_key;
	int op;  // 사용자 입력 메뉴
	int i;

	root = NULL;

	FILE *fp = fopen(argv[1], "r");  // argv[1] : input filename
	fscanf(fp, "%d", &num);
	for (i = 0; i < num; i++) {
		// 하나씩 임시변수에 입력받은 후 minheap에 추가
		fscanf(fp, "%d", &tmp_key);
		if (visited[tmp_key]) {
			fprintf(stderr, "Duplicated value\n");
			exit(1);
		}
		tmp = createNode(tmp_key);
		push(tmp);
		visited[tmp_key] = 1;
	}

	bfs();

	while (1) {
		printf("Select menu and input the number (1: insert, 2: delete): ");
		scanf("%d", &op);

		if (op == 1) {
			// 값을 입력받아 minheap에 추가
			scanf("%d", &tmp_key);
			if (visited[tmp_key]) {
				fprintf(stderr, "Duplicated value\n");
				exit(1);
			}
			tmp = createNode(tmp_key);
			push(tmp);
			visited[tmp_key] = 1;
		}
		else {
			// minheap에서 값 삭제
			pop();
		}
		bfs();  // 명령을 실행할 때마다 heap 출력
	}

	fclose(fp);  // 입력파일 스트림 close

	return 0;
}