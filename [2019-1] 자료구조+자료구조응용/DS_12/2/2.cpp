/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#define MAX_SIZE 100
#define INF_NUM 10000
#define MIN(x, y) ((x) > (y) ? (y) : (x))

int nums[MAX_SIZE + 1] = { 0 };
int winTree[2 * MAX_SIZE] = { NULL };
int sorted[MAX_SIZE + 1] = { 0 };
int k;

int initWinner(int cur, int winTree[]) {
	if (winTree[cur] != 0) return nums[winTree[cur]];

	int left = initWinner(cur * 2, winTree);
	int right = initWinner(cur * 2 + 1, winTree);
	if (left < right) {
		winTree[cur] = winTree[cur * 2];
		return nums[winTree[cur * 2]];
	}
	else {
		winTree[cur] = winTree[cur * 2 + 1];
		return nums[winTree[cur * 2 + 1]];
	}
}

void adjustWinner(int cur, int min, int winTree[]) {
	if (cur * 2 + 1 >= 2 * k) return;

	adjustWinner(cur * 2, min, winTree);
	adjustWinner(cur * 2 + 1, min, winTree);
	if ((winTree[cur * 2] == INF_NUM && winTree[cur * 2 + 1] == INF_NUM)) return;
	else if (winTree[cur * 2] == INF_NUM) {
		winTree[cur] = winTree[cur * 2 + 1];
	}
	else if (winTree[cur * 2 + 1] == INF_NUM) {
		winTree[cur] = winTree[cur * 2];
	}
	else {
		if (nums[winTree[cur * 2]] < nums[winTree[cur * 2 + 1]]) {
			winTree[cur] = winTree[cur * 2];
		}
		else {
			winTree[cur] = winTree[cur * 2 + 1];
		}
	}
}

void inorder(int root, int winTree[]) {
	if (root >= 2 * k) return;
	
	inorder(root * 2, winTree);
	printf("%3d", nums[winTree[root]]);
	inorder(root * 2 + 1, winTree);
}

int main() {
	int sd, i;
	int min, start;

	printf("<<<<<<<<<<<<<< sorting with winner tree >>>>>>>>>>>>>>>>\n\n");
	printf("the number of keys ( 8, 16, or 32 as a power of 2 )  >> ");
	scanf("%d", &k);
	printf("random numbers to use as key values (1 ~ 100)\nseed >> ");
	scanf("%d", &sd);

	srand(sd);
	for (i = 1; i <= k; i++) {
		nums[i] = rand() % 100 + 1;
		printf("%3d", nums[i]);
	}

	printf("\n\ninitialization of min-winner tree\n\n");
	for (i = k; i <= 2 * k - 1; i++) {
		winTree[i] = i - k + 1;
	}
	initWinner(1, winTree);

	printf("inorder traversal for min-winner tree\n");
	inorder(1, winTree);
	
	printf("\n\nsorting with min-winner tree...\n\n");
	for (i = 1; i <= k; i++) {
		min = winTree[1];
		sorted[i] = min;
		winTree[1] = INF_NUM;
		start = k - 1 + min;
		while (1) {
			if (winTree[start] == min) {
				winTree[start] = INF_NUM;
				start /= 2;
			}
			else {
				break;
			}
		}
		adjustWinner(1, 1, winTree);
	}

	printf("sorted result\n");
	for (i = 1; i <= k; i++) {
		printf("%3d", nums[sorted[i]]);
	}
	printf("\n");

	return 0;
}