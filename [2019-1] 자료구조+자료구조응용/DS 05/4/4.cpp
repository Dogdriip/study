/*
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
int EXIT_ROW, EXIT_COL;

int maze[13][13];
int mark[13][13];

typedef struct {
	short int vert;
	short int horiz;
} offsets;
offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

typedef struct {
	short int row;
	short int col;
	short int dir;
} element;
element stack[MAX_STACK_SIZE];
int top = -1;

element pop() {
	if (top == -1) {
		fprintf(stderr, "stack is empty, cannot delete element.\n");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}

void push(element item) {
	if (top >= MAX_STACK_SIZE - 1) {
		fprintf(stderr, "Stack is full, cannot add element\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}

void path() {
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = TRUE;
			} else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			} else {
				++dir;
			}
		}
	}
	if (found) {
		printf("The path is:\n");
		printf("row col\n");
		for (i = 0; i <= top; i++) {
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		}
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	} else {
		printf("The maze does not have a path\n");
	}
}

int main() {
	FILE *fp = fopen("input.txt", "r");
	int i, j;

	fscanf(fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	for (i = 0; i <= EXIT_ROW + 1; i++) {
		for (j = 0; j <= EXIT_COL + 1; j++) {
			if (i == 0 || i == EXIT_ROW + 1 || j == 0 || j == EXIT_COL + 1) maze[i][j] = 1;
			else {
				fscanf(fp, "%d", &maze[i][j]);
			}
		}
	}
	
	path();

	return 0;
}
