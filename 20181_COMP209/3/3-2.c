#include <stdio.h>

int main() {
	bool isPrime;
	for (int n = 2; n <= 1000; n++) {
		isPrime = true;
		for (int i = 2; i < n; i++) {
			if (n % i == 0) {
				isPrime = false;
				break;
			}
		}
		if (isPrime)
			printf("%d\n", n);
	}
	return 0;
}