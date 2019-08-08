/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <ctime>
#define REP 100
#define INNERREP 5
using namespace std;

int fibonacci(int n) {
	if (n <= 2) return 1;
	return fibonacci(n - 1) + fibonacci(n - 2);
}

int fibo_iter(int n) {
	int res = 1;
	int prev[2] = { 1, 1 };
	for (int i = 2; i < n; i++) {
		res = prev[0] + prev[1];
		prev[0] = prev[1];
		prev[1] = res;
	}

	return res;
}

int fibo_tail(int n, int prev0, int prev1) {
	if (n <= 2) return prev1;
	return fibo_tail(n - 1, prev1, prev0 + prev1);
}

int main() {
	clock_t start;
	double duration, duration_sum;

	printf("          fibonacci()       fibo_iter()       fibo_tail()\n");
	printf("     n    실행 시간 평균    실행 시간 평균    실행 시간 평균\n");
	for (int n = 5; n <= REP; n += 5) {
		printf("%6d  ", n);
		
		// fibonacci()
		if (n <= 40) {
			duration_sum = 0;
			for (int j = 0; j < INNERREP; j++) {
				start = clock();
				fibonacci(n);
				duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
				duration_sum += duration;
			}
			printf("%10lf        ", duration_sum / INNERREP);
		} else {
			printf("  -               ");
		}

		// fibo_iter()
		duration_sum = 0;
		for (int j = 0; j < INNERREP; j++) {
			start = clock();
			fibo_iter(n);
			duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
			duration_sum += duration;
		}
		printf("%10lf        ", duration_sum / INNERREP);

		// fibo_tail()
		duration_sum = 0;
		for (int j = 0; j < INNERREP; j++) {
			start = clock();
			fibo_tail(n, 1, 1);
			duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
			duration_sum += duration;
		}
		printf("%10lf", duration_sum / INNERREP);

		printf("\n");
	}

	return 0;
}