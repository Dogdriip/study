/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstring>
#define MAX_STRLEN 101
#define MAX_PATLEN 101

int fail[MAX_PATLEN];

void failure(char *pat) {
	int i = 0, j;
	int n = strlen(pat);
	fail[0] = -1;
	for (j = 1; j < n; j++) {
		i = fail[j - 1];
		while ((pat[j] != pat[i + 1]) && (i >= 0)) {
			i = fail[i];
		}
		if (pat[j] == pat[i + 1]) {
			fail[j] = i + 1;
		} else {
			fail[j] = -1;
		}
	}
}

int pmatch(char *string, char *pat) {
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);
	while (i < lens && j < lenp) {
		if (string[i] == pat[j]) {
			i++; j++;
		} else if (j == 0) {
			i++;
		} else {
			j = fail[j - 1] + 1;
		}
	}
	return ((j == lenp) ? (i - lenp) : -1);
}

int main() {
	char str[MAX_STRLEN], p[MAX_PATLEN];
	int res, i, pat_len;
	FILE *fp = fopen("input.txt", "r");
	fgets(str, MAX_STRLEN, fp);
	fgets(p, MAX_PATLEN, fp);

	failure(p);  // 함수명

	pat_len = strlen(p);
	printf("Failure function:\n");
	printf("j\t");
	for (i = 0; i < pat_len; i++) printf("%3d", i);
	printf("\npat\t");
	for (i = 0; i < pat_len; i++) printf("%3c", p[i]);
	printf("\nf\t");
	for (i = 0; i < pat_len; i++) printf("%3d", fail[i]);
	printf("\n");

	res = pmatch(str, p);
	if (res != -1) {
		printf("The pattern %s is found at the position %d\n", p, res);
	} else {
		printf("Not found\n");
	}

	fclose(fp);

	return 0;
}