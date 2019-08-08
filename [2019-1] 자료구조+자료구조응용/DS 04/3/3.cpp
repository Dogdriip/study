/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstring>
#define MAX_LEN 101

int nfind(char *string, char *pat) {
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;

	for (i = 0; endmatch <= lasts; endmatch++, start++) {
		if (string[endmatch] == pat[lastp]) {
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
		}
		if (j == lastp) {
			return start;
		}
	}
	return -1;
}

int main() {
	char str[MAX_LEN], p[MAX_LEN];
	int res;
	FILE *fp = fopen("input.txt", "r");
	fgets(str, MAX_LEN, fp);
	fgets(p, MAX_LEN, fp);

	res = nfind(str, p);
	if (res != -1) {
		printf("The pattern test is found at the position %d\n", res);
	} else {
		printf("Not found\n");
	}

	fclose(fp);

	return 0;
}