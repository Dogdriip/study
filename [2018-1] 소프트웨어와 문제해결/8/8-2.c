/***
* 실습 2 : 짝 찾기
***/
#include <stdio.h>
#include <math.h>

int main() {
	int n, d, arr[100];
	int i, j;
	int cnt = 0;

	scanf("%d %d", &n, &d);
	for (i = 0; i < n; i++) scanf("%d", &arr[i]);

	for (i = 0; i < n - 1; i++)
		for (j = i; j < n; j++)
			if (abs(arr[i] - arr[j]) == d)
				cnt++;

	printf("%d\n", cnt);

	return 0;
}