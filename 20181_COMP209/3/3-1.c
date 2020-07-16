#include <stdio.h>

int main() {
	int n;
	bool isPrime = true;
	scanf("%d", &n);
	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			isPrime = false;
			break;
		}
	}
	if (isPrime)
		printf("%d is a prime number\n", n);
	else
		printf("%d is not a prime number\n", n);
	return 0;
}