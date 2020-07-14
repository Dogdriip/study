/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstring>
#define FALSE 0
#define TRUE 1

typedef struct {
	char name[20];
	int age;
	float salary;
} humanBeing;

int humansEqual(humanBeing *person1, humanBeing *person2) {
	if (strcmp(person1->name, person2->name))
		return FALSE;
	if (person1->age != person2->age)
		return FALSE;
	if (person1->salary != person2->salary)
		return FALSE;
	return TRUE;
}

int main() {
	int i;
	humanBeing person1, person2;

	printf("Input person1's name, age, salary :\n");
	fgets(person1.name, sizeof(person1.name), stdin);
	scanf("%d %f", &person1.age, &person1.salary);
	getchar();
	printf("Input person2's name, age, salary :\n");
	fgets(person2.name, sizeof(person2.name), stdin);
	scanf("%d %f", &person2.age, &person2.salary);

	if (humansEqual(&person1, &person2)) {
		printf("The two human beings are the same\n");
	} else {
		printf("The two human beings are not the same\n");
	}

	return 0;
}