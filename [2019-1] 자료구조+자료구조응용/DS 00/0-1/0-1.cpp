/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>

void hanoi_move(int n, int from, int to) {
	if (n == 1) {
		printf("%d -> %d\n", from, to);
		return;
	}

	hanoi_move(n - 1, from, 6 - from - to);
	hanoi_move(1, from, to);
	hanoi_move(n - 1, 6 - from - to, to);
}

int main() {
	int n; scanf("%d", &n);
	hanoi_move(n, 1, 3);

	return 0;
}