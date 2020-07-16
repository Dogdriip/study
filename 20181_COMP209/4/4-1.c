#include <stdio.h>
#include <stdlib.h>

int main() {
	int random = rand() % 100 + 1;
	int n, i;
	printf("1~100까지의 숫자 중 하나를 입력해 주세요.\n");
	for (i = 0; i < 10; i++) {
		printf("> ");
		scanf("%d", &n);
		if (n < random)
			printf("아닙니다. 더 높습니다.\n");
		else if (n > random)
			printf("아닙니다. 더 낮습니다.\n");
		else
			break;
	}
	if (i < 10)
		printf("축하합니다. %d번만에 정답을 맞췄습니다.\n", i + 1);
	else
		printf("정답을 맞추지 못했습니다.\n");

	return 0;
}