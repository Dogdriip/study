#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <deque>
#define INF 987654321
using namespace std;

typedef long long ll;
typedef struct node {
	int cnt;
	int par;
} node;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

FILE* fp, *fp2;
int n, cnt;
deque<ll> dq;
char** arr;
node** bf;

void print(int i, int j) {
	if (i == 1 && j == 1) {
		fprintf(fp2, "%d %d\n", i, j);
		return;
	}

	if (bf[i][j].par == 1) {
		print(i, j - 1);
	}
	else if (bf[i][j].par == 2) {
		print(i - 1, j);
	}
	else if (bf[i][j].par == 3) {
		print(i, j + 1);
	}
	else {
		print(i + 1, j);
	}

	fprintf(fp2, "%d %d\n", i, j);
}

void solve() {
	while (!dq.empty()) {
		ll tmp = dq.back(); dq.pop_back();
		int x = tmp / cnt;
		int y = tmp % cnt;
		
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i], ny = y + dy[i];

			if (!(nx >= 1 && nx <= n && ny >= 1 && ny <= n)) {
				continue;
			}

			if (arr[nx][ny] == '2') {
				continue;
			}
			else if (arr[nx][ny] == '1') {
				dq.push_back(nx * cnt + ny);
				bf[nx][ny].cnt = bf[x][y].cnt;
			}
			else {
				dq.push_front(nx * cnt + ny);
				bf[nx][ny].cnt = bf[x][y].cnt + 1;
			}

			bf[nx][ny].par = i + 1;
			arr[nx][ny] = '2';
		}
	}
}

void countt(int num) {
	while (num) {
		num /= 10;
		cnt++;
	}
	cnt = (int)pow(10, cnt);
	return;
}

int main() {
	char filename[50];
	char tmp;

	printf("input file name?\n");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	fp2 = fopen("output.txt", "w");

	fscanf(fp, "%d", &n);
	countt(n);

	bf = (node**)malloc(sizeof(node*) * (n + 1));
	arr = (char**)malloc(sizeof(char*) * (n + 1));

	for (int i = 1; i <= n; i++) {
		fscanf(fp, "%c", &tmp);
		bf[i] = (node*)malloc(sizeof(node) * (n + 1));
		arr[i] = (char*)malloc(sizeof(char**) * (n + 1));

		for (int j = 1; j <= n; j++) {
			fscanf(fp, "%c", &arr[i][j]);

			bf[i][j].cnt = INF; bf[i][j].par = 0;
		}
	}

	bf[1][1].cnt = 0;
	arr[1][1] = '2';
	dq.push_back(1 * cnt + 1);

	solve();
	fprintf(fp2, "%d\n", bf[n][n].cnt);

	print(n, n);

	fclose(fp);
	fclose(fp2);
	
	return 0;
}
