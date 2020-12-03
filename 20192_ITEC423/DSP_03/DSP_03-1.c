// DSP_03-1_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 201  // heap 최대 크기 200으로 가정

typedef struct {
	int key;
} element;

element heap[MAX_ELEMENTS];
int n;  // heap의 크기

short int visited[1000001];  // 수 중복체크. 수의 범위가 0~1000000이라 가정

void push(element item, int *n) {
	int i;
	if (*n == MAX_ELEMENTS - 1) {  // heap full 처리
		fprintf(stderr, "The heap is full.\n");
		exit(1);
	}

	i = ++(*n);  // heap의 크기 1 증가, i는 맨 마지막 노드 번호에서 시작
	// 입력값과 부모 노드의 key를 비교해가면서 부모 노드의 key가 더 크다면 서로 교체
	// 루트까지 올라가거나 부모 노드의 key가 더 작을 때까지 반복
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

element pop(int *n) {
	int parent, child;
	element item, temp;
	if (!(*n)) {  // heap empty 처리
		fprintf(stderr, "The heap is empty.\n");
		exit(1);
	}

	item = heap[1];  // 삭제할 원소 (루트 노드)
	temp = heap[(*n)--];  // heap의 크기 1 감소, heap의 맨 마지막 원소 임시변수에 저장
	parent = 1;
	child = 2;
	// 위에서부터 내려오면서 맨 마지막 원소 (temp)를 어디에 넣을지 결정
	while (child <= *n) {
		if ((child < *n) && (heap[child].key > heap[child + 1].key)) {
			// 왼쪽 자식(child)의 key보다 오른쪽 자식의 key가 더 작다면 오른쪽 자식 선택
			child++;  
		}
		if (temp.key <= heap[child].key) {
			// 자식의 key가 temp의 key보다 크거나 같다면, 그 부모 위치에 temp 저장
			break;
		}
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	
	visited[item.key] = 0;
	return item;
}

void print_heap(int *n) {  // heap 출력 함수
	int i, j;
	// heap의 높이 == log2(원소 개수) + 1
	// 위에서부터 각 level마다 트리 순회하며 출력
	for (i = 1; i <= *n; i <<= 1) {
		for (j = i; j < (i << 1); j++) {
			printf("%d ", heap[j].key);
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	int num;  // 입력받을 key 개수
	element tmp;  // 입력받을 때 사용할 임시변수
	int op;  // 사용자 입력 메뉴
	int i;

	FILE *fp = fopen(argv[1], "r");  // argv[1] : input filename
	fscanf(fp, "%d", &num);
	for (i = 0; i < num; i++) {
		// 하나씩 임시변수에 입력받은 후 minheap에 추가
		fscanf(fp, "%d", &tmp.key);
		if (visited[tmp.key]) {
			fprintf(stderr, "Duplicated value\n");
			exit(1);
		}
		push(tmp, &n);
		visited[tmp.key] = 1;
	}

	print_heap(&n);

	while (1) {
		printf("Select menu and input the number (1: insert, 2: delete): ");
		scanf("%d", &op);

		if (op == 1) {
			// 값을 입력받아 minheap에 추가
			scanf("%d", &tmp.key);
			if (visited[tmp.key]) {
				fprintf(stderr, "Duplicated value\n");
				exit(1);
			}
			push(tmp, &n);
			visited[tmp.key] = 1;
		} else {
			// minheap에서 값 삭제
			pop(&n);
		}
		print_heap(&n);  // 명령을 실행할 때마다 heap 출력
	}
	
	fclose(fp);  // 입력파일 스트림 close

	return 0;
}