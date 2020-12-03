// DSP_06_2018112749.c
// 2018112749 전현승

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define SWAP(a,b) {leftistTree t = a; a = b; b = t;}
#define NUMSIZE 100001

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

int tr1_num[NUMSIZE], tr2_num[NUMSIZE];  // 노드 출력을 위한 key값 저장
int max_num;  // 방문한 노드 번호 중 최대치 (출력시 트리 최대 깊이 판단을 위함)

void minUnion(leftistTree *a, leftistTree *b) {	
	if ((*a)->data.key > (*b)->data.key) SWAP(*a, *b);
	
	if (!(*a)->rightChild) (*a)->rightChild = *b;
	else minUnion(&(*a)->rightChild, b);
	
	if (!(*a)->leftChild) {
		(*a)->leftChild = (*a)->rightChild;
		(*a)->rightChild = NULL;
	}
	else if((*a)->leftChild->shortest < (*a)->rightChild->shortest) SWAP((*a)->leftChild, (*a)->rightChild);
	(*a)->shortest = (!(*a)->rightChild) ? 1 : (*a)->rightChild->shortest +1;
}

void minMeld(leftistTree *a, leftistTree *b) {
	if (!*a) *a = *b;
	else if (*b) minUnion(a, b);
	*b = NULL;
}

leftistTree newNode(int key) {  // 동적할당된 트리 노드 반환
	leftistTree tmp = (leftistTree)malloc(sizeof(*tmp));
	tmp->data.key = key;
	tmp->leftChild = NULL; tmp->rightChild = NULL;
	tmp->shortest = 1;  // 왼쪽, 오른쪽 자식 NULL로 초기화, shortest는 1
	return tmp;
}

void dfs(leftistTree *t, int num, int treenum) {
	if (treenum == 1) tr1_num[num] = (*t)->data.key;
	else if (treenum == 2) tr2_num[num] = (*t)->data.key;

	if (max_num < num) max_num = num;  // max_num 갱신

	// tree에서 왼쪽, 오른쪽 자식으로 dfs
	if ((*t)->leftChild) {
		dfs(&(*t)->leftChild, num * 2, treenum);
	}
	if ((*t)->rightChild) {
		dfs(&(*t)->rightChild, num * 2 + 1, treenum);
	}
}


int main(int argc, char* argv[]) {
	int n1, n2;  // 각각 1번, 2번 min leftist tree의 key 개수
	leftistTree lt1 = NULL;  // 1번 MLT
	leftistTree lt2 = NULL;  // 2번 MLT

	leftistTree tmp;
	int tmp_key;
	int i, j;

	FILE *fp1 = fopen(argv[1], "r");  // argv[1] : input filename
	FILE *fp2 = fopen(argv[2], "w");  // argv[2] : output filename

	// 1번 MLT 구성
	fscanf(fp1, "%d", &n1);
	for (i = 0; i < n1; i++) {
		// 매번 key 입력받아서 트리 노드 동적할당 후 기존 MLT에 meld
		fscanf(fp1, "%d", &tmp_key);
		tmp = newNode(tmp_key);
		minMeld(&lt1, &tmp);
	}

	// 1번 MLT 출력
	fprintf(fp2, "1st tree :\n");
	memset(tr1_num, -1, NUMSIZE);  // key 저장 배열 -1로 초기화 (비어있는 노드 위치 판별 위함)
	max_num = 0;
	dfs(&lt1, 1, 1);
	for (i = 1; i <= max_num; i <<= 1) {  // dfs 후 최대 깊이를 이용해서 기록된 level까지 완전히 출력
		for (j = i; j < (i << 1); j++) {
			if (tr1_num[j] == -1) fprintf(fp2, "- ");
			else fprintf(fp2, "%d ", tr1_num[j]);
		}
		fprintf(fp2, "\n");
	}
	fprintf(fp2, "\n");

	// 2번 min leftist tree 구성
	fscanf(fp1, "%d", &n2);
	for (i = 0; i < n2; i++) {
		fscanf(fp1, "%d", &tmp_key);
		tmp = newNode(tmp_key);
		minMeld(&lt2, &tmp);
	}

	// 2번 MLT 출력
	fprintf(fp2, "2nd tree :\n");
	memset(tr2_num, -1, NUMSIZE);
	max_num = 0;
	dfs(&lt2, 1, 2);
	for (i = 1; i <= max_num; i <<= 1) {
		for (j = i; j < (i << 1); j++) {
			if (tr2_num[j] == -1) fprintf(fp2, "- ");
			else fprintf(fp2, "%d ", tr2_num[j]);
		}
		fprintf(fp2, "\n");
	}
	fprintf(fp2, "\n");

	// 1, 2번 MLT meld
	minMeld(&lt1, &lt2);

	// 최종 합병된 MLT 출력
	fprintf(fp2, "after meld :\n");
	memset(tr1_num, -1, NUMSIZE);
	max_num = 0;
	dfs(&lt1, 1, 1);
	for (i = 1; i <= max_num; i <<= 1) {
		for (j = i; j < (i << 1); j++) {
			if (tr1_num[j] == -1) fprintf(fp2, "- ");
			else fprintf(fp2, "%d ", tr1_num[j]);
		}
		fprintf(fp2, "\n");
	}
	fprintf(fp2, "\n");

	fclose(fp1);  // 입력파일 스트림 close
	fclose(fp2);  // 출력파일 스트림 close

	return 0;
}