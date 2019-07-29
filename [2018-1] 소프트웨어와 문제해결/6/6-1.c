/***
 * 실습 1 : 문자열 바꾸기
 ***/
#include <stdio.h>
#define STRLEN 4

int main() {
	char str[STRLEN + 1] = "abcd", str_re[STRLEN + 1] = "", temp;
	int i;

	printf("원래 문자열 : %s\n", str);

	for (i = 0; i < STRLEN; i++)
		str_re[i] = str[STRLEN - 1 - i];

	printf("(배열 사용) 바뀐 문자열 : %s\n", str_re);

	for (i = 0; i < (STRLEN / 2); i++) {
		temp = str[i];
		str[i] = str[STRLEN - 1 - i];
		str[STRLEN - 1 - i] = temp;
	}

	printf("(배열 사용 X) 바뀐 문자열 : %s\n", str);

	return 0;
}