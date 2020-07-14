/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstring>
#include <cstdlib>
#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
	float coef;
	int expon;
} term;

term terms[MAX_TERMS];
int avail;

void attach(float coefficient, int exponent) {
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}

void padd(int startA, int finishA, int startB, int finishB, int *startD, int *finishD) {
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
		case -1:
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;
		case 0:
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case 1:
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
		}
	}

	for (; startA <= finishA; startA++) {
		attach(terms[startA].coef, terms[startA].expon);
	}
	for (; startB <= finishB; startB++) {
		attach(terms[startB].coef, terms[startB].expon);
	}
	*finishD = avail - 1;
}

void printPoly(int start, int finish) {
	int i;
	for (i = start; i <= finish; i++) {
		printf("%f", terms[i].coef);
		if (terms[i].expon != 0) printf("x^%d", terms[i].expon);
		if (i == finish) printf("\n");
		else printf(" + ");
	}
}

int main() {
	int a_cnt, b_cnt;
	int i;
	char suffix[3];
	float co;
	int ex;
	int sd, fd;

	printf("<< D(x) = A(x) + B(x) >>\n");
	printf("Input the number of items of A(x) : ");
	scanf("%d", &a_cnt);
	printf("Input the number of items of B(x) : ");
	scanf("%d", &b_cnt);

	printf("\ninput in descending order\n");
	for (i = 0; i < a_cnt; i++) {
		switch (i + 1) {
		case 1:
			strcpy(suffix, "st"); break;
		case 2:
			strcpy(suffix, "nd"); break;
		case 3:
			strcpy(suffix, "rd"); break;
		default:
			strcpy(suffix, "th");
		}
		printf("the %d%s coefficient and exponent of A(x), (ex)10 3 : ", i + 1, suffix);
		scanf("%f %d", &co, &ex);
		
		attach(co, ex);
	}

	printf("\n");
	for (i = 0; i < b_cnt; i++) {
		switch (i + 1) {
		case 1:
			strcpy(suffix, "st"); break;
		case 2:
			strcpy(suffix, "nd"); break;
		case 3:
			strcpy(suffix, "rd"); break;
		default:
			strcpy(suffix, "th");
		}
		printf("the %d%s coefficient and exponent of B(x), (ex)10 3 : ", i + 1, suffix);
		scanf("%f %d", &co, &ex);

		attach(co, ex);
	}

	padd(0, a_cnt - 1, a_cnt, a_cnt + b_cnt - 1, &sd, &fd);

	printf("\n");
	printf("A(x) = ");
	printPoly(0, a_cnt - 1);
	printf("B(x) = ");
	printPoly(a_cnt, a_cnt + b_cnt - 1);
	printf("D(x) = ");
	printPoly(sd, fd);

	return 0;
}