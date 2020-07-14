/* 
 * 본인은 이 소스파일을 다른 사람의 소스를 복사하지 않고 직접 작성하였습니다.
 */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MAX_STACK_SIZE 500
#define TRUE 1
#define FALSE 0
int EXIT_ROW, EXIT_COL;

int maze[13][13];
int st[13][13];

typedef struct {
    short int vert;
    short int horiz;
} offsets;
offsets move[8] = { {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

typedef struct {
    short int row;
    short int col;
    short int dir;
    short int step;
} element;
element stack[MAX_STACK_SIZE];
element paths[MAX_STACK_SIZE];
int top = -1;
int p_top = -1;

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
    int i, row, col, step, nextRow, nextCol, nextStep, dir;
    int min_step = 10000;
    element position;
    st[1][1] = 1; top = 0;
    stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1; stack[0].step = 1;
    while (top > -1) {
        position = pop();
        row = position.row; col = position.col; dir = position.dir; step = position.step;
        while (dir < 8) {
            nextRow = row + move[dir].vert;
            nextCol = col + move[dir].horiz;
            nextStep = step + 1;
            if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
                if (nextStep < min_step) {
                    p_top = -1;
                    for (i = 0; i <= top; i++) {
                        paths[++p_top] = stack[i];
                    }
                    paths[++p_top].row = row; paths[p_top].col = col;
                    paths[p_top].dir = dir; paths[p_top].step = step;
                    min_step = nextStep;
                } else if (nextStep == min_step) {
                    for (i = 0; i <= top; i++) {
                        paths[++p_top] = stack[i];
                    }
                    paths[++p_top].row = row; paths[p_top].col = col;
                    paths[p_top].dir = dir; paths[p_top].step = step;
                }
                ++dir;
            } else if (!maze[nextRow][nextCol] && (!st[nextRow][nextCol] || st[nextRow][nextCol] > nextStep)) {
                st[nextRow][nextCol] = nextStep;
                position.row = row; position.col = col; position.dir = ++dir; position.step = step;
                push(position);
                row = nextRow; col = nextCol; dir = 0; step = nextStep;
            } else {
                ++dir;
            }
        }
    }
    
    if (p_top == -1) {
        printf("The maze does not have a path\n");
    } else {
        printf("Shortest path length : %d\n", min_step);
        printf("row col\n");
        printf("------\n");
        for (i = 0; i <= p_top; i++) {
            printf("%d %d\n", paths[i].row, paths[i].col);
            if (i % (min_step - 1) == min_step - 2) {
                printf("%d %d\n", EXIT_ROW, EXIT_COL);
                printf("------\n");
            }
        }
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
