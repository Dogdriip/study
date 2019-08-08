/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>

typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
} polyNode;
polyPointer a, b;

polyPointer invert(polyPointer first) {
	polyPointer middle, trail;
	middle = NULL;
	while (first) {
		trail = middle;
		middle = first;
		first = first->link;
		middle->link = trail;
	}
	return middle;
}

polyPointer findLast(polyPointer first) {
	for (; first->link; first = first->link) {
		
	}
	return first;
}

void insert(polyPointer *first, polyPointer x) {
	polyPointer temp = (polyPointer)malloc(sizeof(*temp));
	temp->coef = x->coef;
	temp->expon = x->expon;

	if (*first) {
		temp->link = NULL;
		findLast(*first)->link = temp;
	}
	else {
		temp->link = NULL;
		*first = temp;
	}
}

void inputPoly(FILE *fp, polyPointer *first) {
	char ord;
	int coef, expon;
	polyNode tmp;

	fscanf(fp, "%c", &ord);
	while (1) {
		fscanf(fp, "%d %d", &coef, &expon);
		if (feof(fp)) break;

		tmp.coef = coef; tmp.expon = expon;
		insert(first, &tmp);
	}

	if (ord == 'a') *first = invert(*first);
}

void printList(polyPointer first) {
	for (; first; first = first->link) {
		printf("%+5dx^%d", first->coef, first->expon);
	}
	printf("\n");
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
	polyPointer temp = (polyPointer)malloc(sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}

void erase(polyPointer *ptr) {
	polyPointer temp;
	while (*ptr) {
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}

polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	rear = (polyPointer)malloc(sizeof(*rear));
	c = rear;
	while (a != NULL && b != NULL) {
		if (a->expon < b->expon) {
			attach(b->coef, b->expon, &rear);
			b = b->link;
		}
		else if (a->expon == b->expon) {
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link;
			b = b->link;
		}
		else {
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}

int main() {
	FILE *fa = fopen("a.txt", "r");
	FILE *fb = fopen("b.txt", "r");

	a = NULL; b = NULL;

	inputPoly(fa, &a);
	inputPoly(fb, &b);

	printf("%10s", "a :");
	printList(a);
	printf("%10s", "b :");
	printList(b);
	
	polyPointer c = padd(a, b);
	printf("%10s", "a+b=c :");
	printList(c);

	erase(&a);
	erase(&b);
	erase(&c);
	
	return 0;
}