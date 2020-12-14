#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define INF 987654321

FILE* fp, *fp2;
int* arr;
int** dp, ** par;

void print(int i, int j) {
	int k;

	if (i == j) {
		fprintf(fp2, "%d ", i);
		return;
	}

	k = par[i][j];

	fprintf(fp2, "( ");
	print(i, k);
	print(k + 1, j);
	fprintf(fp2, ") ");
}

int main() {
	char filename[50];
	int n;

	printf("input file name?\n");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	fp2 = fopen("output.txt", "w");

	fscanf(fp, "%d", &n);
	if (n <= 1) {
		return 0;
	}

	arr = (int*)malloc(sizeof(int) * n);
	dp = (int**)malloc(sizeof(int*) * (n + 1));
	par = (int**)malloc(sizeof(int*) * (n + 1));
	for (int i = 0; i < n; i++) {
		dp[i] = (int*)calloc(n + 1, sizeof(int**));
		par[i] = (int*)calloc(n + 1, sizeof(int**));
	}

	for (int i = 0; i < n; i++) {
		fscanf(fp, "%d", &arr[i]);
	}

	for (int d = 1; d <= n - 1; d++) {
		for (int i = 1; i < n - d; i++) {
			int j = i + d;
			printf("%d %d\n", i, j);
			dp[i][j] = INF;

			for (int k = i; k < j; k++) {
				int res = dp[i][k] + dp[k + 1][j] + (arr[i - 1] * arr[k] * arr[j]);
				if (dp[i][j] > res) {
					dp[i][j] = res;
					par[i][j] = k;
				}
			}
		}
	}

	print(1, n - 1);

	fclose(fp);
	fclose(fp2);

	return 0;
}
