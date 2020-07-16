/***
 * 소프트웨어와 문제해결 기말고사 문제 1번 소스코드
 ***/

#include <stdio.h>

int main() {
	char strarr[20][257]; // 문자열을 저장하는 2차원 배열
	int alphabet_count[20][27] = { { 0, }, }; // 알파벳 26개
	int anagram_cnt[20] = { 0, }; // n번재 문자열의 애너그램 개수
	int n; // 입력받을 문자열의 개수
	int i, j, k; // iterator
	bool isDiff; // alphabet 확인 loop에 사용되는 boolean
	int max_idx = 0; // 애너그램 개수가 가장 많은 문자열의 index값

	scanf("%d", &n);
	for (i = 0; i < n; i++) scanf("%s", strarr[i]);

	// 'A' : 65, 'a' : 97 ~ 'z' : 122 (26개)
	// 소문자만 들어온다고 가정

	for (i = 0; i < n; i++) {
		j = 0;
		while (strarr[i][j] != NULL) {
			alphabet_count[i][strarr[i][j] - 97]++;
			j++;
		}
	}

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			isDiff = false;
			for (k = 0; k < 26; k++) {
				if (alphabet_count[i][k] != alphabet_count[j][k]) {
					isDiff = true;
					break;
				}
			}
			if (!isDiff) anagram_cnt[i]++; // 두 문자열이 똑같다.
		}
	}

	for (i = 0; i < n; i++)
		if (anagram_cnt[i] > anagram_cnt[max_idx]) max_idx = i;

	printf("\n%s, %d\n", strarr[max_idx], anagram_cnt[max_idx]);

	return 0;
}