#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 987654321
#define MAX 1001

typedef long long ll;

FILE* fp, *fp2;
int n, m;
int comp_res;
ll dp[MAX][MAX][2];
int par[MAX][MAX][2];
ll d[MAX], w[MAX], psum[MAX];

ll comp(ll a, ll b) {
	if (a < b) {
		comp_res = 0;
		return a;
	}
	else {
		comp_res = 1;
		return b;
	}
}

void print(int l, int r, int flag) {
	int tmp = par[l][r][flag];

	if (l >= m && r <= m) {
		fprintf(fp2, "%d\n", m);
		return;
	}

	if (!flag) {
		if (tmp == r) {
			print(l + 1, r, 1);
		}
		else {
			print(l + 1, r, 0);
		}

		fprintf(fp2, "%d\n", l);
	}
	else {
		if (tmp == l) {
			print(l, r - 1, 0);
		}
		else {
			print(l, r - 1, 1);
		}

		fprintf(fp2, "%d\n", r);
	}
}

ll solution(int l, int r, int flag) {
	if (l > r) {
		return INF;
	}

	if (dp[l][r][flag] != INF) {
		return dp[l][r][flag];
	}

	if (!flag) {
		ll res1 = solution(l + 1, r, 0) + (d[l + 1] - d[l]) * (psum[n] - (psum[r] - psum[l]));
		ll res2 = solution(l + 1, r, 1) + (d[r] - d[l]) * (psum[n] - (psum[r] - psum[l]));
		
		dp[l][r][0] = comp(res1, res2);
		if (!comp_res) {
			par[l][r][0] = l + 1;
		}
		else {
			par[l][r][0] = r;
		}

		return dp[l][r][0];
	}
	else {
		ll res1 = solution(l, r - 1, 0) + (d[r] - d[l]) * (psum[n] - (psum[r - 1] - psum[l - 1]));
		ll res2 = solution(l, r - 1, 1) + (d[r] - d[r - 1]) * (psum[n] - (psum[r - 1] - psum[l - 1]));
		
		dp[l][r][1] = comp(res1, res2);
		if (!comp_res) {
			par[l][r][1] = l;
		}
		else {
			par[l][r][1] = r - 1;
		}

		return dp[l][r][1];
	}
}

int main() {
	char filename[50];

	printf("input file name?\n");
	scanf("%s", filename);

	fp = fopen(filename, "r");
	fp2 = fopen("output.txt", "w");

	fscanf(fp, "%d %d", &n, &m);

	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX; j++) {
			dp[i][j][0] = dp[i][j][1] = INF;
		}
	}
	for (int i = 1; i <= n; i++) {
		fscanf(fp, "%lld %lld", &d[i], &w[i]);
		par[i][i][0] = par[i][i][1] = 0;
		psum[i] = psum[i - 1] + w[i];
	}

	dp[m][m][0] = dp[m][m][1] = 0;

	ll res1 = solution(1, n, 0);
	ll res2 = solution(1, n, 1);
	fprintf(fp2, "%lld\n", comp(res1, res2));
	if (!comp_res) {
		print(1, n, 0);
	}
	else {
		print(1, n, 1);
	}

	fclose(fp);
	fclose(fp2);

	return 0;
}