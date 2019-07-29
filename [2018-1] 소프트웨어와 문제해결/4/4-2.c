#include <stdio.h>
#include <string.h>

int main() {
	char str[11];
	bool isDuplicated = false;

	printf("문자열 입력: ");
	scanf("%s", str);
	
	for (int i = 0; i < strlen(str); i++) {
		for (int j = 0; j < strlen(str); j++) {
			if (i != j && str[i] == str[j]) {
				isDuplicated = true;
				break;
			}
		}
	}

	if (isDuplicated)
		printf("중복된 문자가 있습니다.\n");
	else
		printf("중복된 문자가 없습니다.\n");

	return 0;
}