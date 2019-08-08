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
polyPointer c, lastA, lastB, avail = NULL;

polyPointer getNode() {
	polyPointer node;
	if (avail) {
		node = avail;
		avail = avail->link;
	}
	else {
		node = (polyPointer)malloc(sizeof(*node));
	}
	return node;
}

void retNode(polyPointer node) {
	node->link = avail;
	avail = node;
}

void insertFront2(polyPointer *last, polyPointer node) {
	if (!(*last)) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
	}
}

void insertLast(polyPointer *last, polyPointer node) {
	if (!(*last)) {
		*last = node;
		node->link = node;
	}
	else {
		node->link = (*last)->link;
		(*last)->link = node;
		*last = node;
	}
}

void inputPolyCL(FILE *fp, polyPointer *last) {
	char ord;
	int coef, expon;
	polyPointer tmp;

	fscanf(fp, "%c", &ord);
	while (1) {
		fscanf(fp, "%d %d", &coef, &expon);
		if (feof(fp)) break;

		tmp = getNode();
		tmp->coef = coef; tmp->expon = expon;
		if (ord == 'a') insertFront2(last, tmp);
		else insertLast(last, tmp);
	}
}

void printCList(polyPointer last) {
	polyPointer temp;
	
	if (last) {
		temp = last->link;
		do {
			printf("%+5dx^%d", temp->coef, temp->expon);
			temp = temp->link;
		} while (temp != last);
	}
	printf("\n");
}

void attach(float coefficient, int exponent, polyPointer *ptr) {
	polyPointer temp = getNode();
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

void cerase(polyPointer *ptr) {
	polyPointer temp;
	if (*ptr) {
		temp = (*ptr)->link;
		(*ptr)->link = avail;
		avail = temp;
		*ptr = NULL;
	}
}

polyPointer cpadd(polyPointer a, polyPointer b) {
	polyPointer startA, c, lastC;
	int sum, done = 0;
	startA = a;
	a = a->link;
	b = b->link;
	c = getNode();
	c->expon = -1; lastC = c;
	do {
		if (a->expon < b->expon) {
			attach(b->coef, b->expon, &lastC);
			b = b->link;
		}
		else if (a->expon == b->expon) {
			if (startA == a) done = 1;
			else {
				sum = a->coef + b->coef;
				if (sum) attach(sum, a->expon, &lastC);
				a = a->link;
				b = b->link;
			}
		}
		else {
			attach(a->coef, a->expon, &lastC);
			a = a->link;
		}
	} while (!done);
	lastC->link = c;
	return c;
}

int main() {
	FILE *fa = fopen("a.txt", "r");
	FILE *fb = fopen("b.txt", "r");
	polyPointer headera = getNode();
	polyPointer headerb = getNode();

	a = NULL; b = NULL;

	headera->coef = -1; headera->expon = -1;
	headerb->coef = -1; headerb->expon = -1;
	insertLast(&a, headera);
	insertLast(&b, headerb);

	insertLast(&lastA, a);
	insertLast(&lastB, b);

	inputPolyCL(fa, &lastA);
	inputPolyCL(fb, &lastB);

	printf("%10s", "a :");
	printCList(a);
	printf("%10s", "b :");
	printCList(b);
	
	polyPointer c = cpadd(a, b);
	printf("%10s", "a+b=c :");
	printCList(c);

	cerase(&a);
	cerase(&b);
	cerase(&c);
	
	erase(&avail);

	retNode(headera);
	retNode(headerb);

	return 0;
}