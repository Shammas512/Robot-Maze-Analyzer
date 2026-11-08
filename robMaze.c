#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

void inputMaze(int R, int C, char maze[R][C + 1]) {
    int i, j;

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            maze[i][j] = '#';
        }
        maze[i][C] = '\0';
    }

    printf("Input the maze:\n");
    for (i = 1; i < R - 1; i++) {
        for (j = 1; j < C - 1; j++) {
            scanf(" %c", &maze[i][j]);
        }
    }
}

int isOpen(int R, int C, char maze[R][C + 1], int r, int c) {
    if (r < 0 || r >= R || c < 0 || c >= C) return 0;
    return maze[r][c] != '#';
}

void displayMaze(int R, int C, char maze[R][C + 1]) {
    int i;
    for (i = 0; i < R; i++) {
        printf("%s\n", maze[i]);
    }
    printf("\n");
}

void runRobot(int R, int C) {
    char maze[R][C + 1];
    int i, j;
    int startR = -1, startC = -1, endR = -1, endC = -1;
    int r, c, d, steps;
    int right, left, back;

    inputMaze(R, C, maze);

    for (i = 0; i < R; i++) {
        for (j = 0; j < C; j++) {
            if (maze[i][j] == 'S') { startR = i; startC = j; }
            if (maze[i][j] == 'E') { endR = i; endC = j; }
        }
    }

    if (startR == -1 || endR == -1) {
        printf("Your maze is invalid\n");
        return;
    }

    r = startR;
    c = startC;
    d = 1;
    steps = 0;

    system("cls");
    printf("Initial:\n");
    displayMaze(R, C, maze);
    Sleep(1000);

    while (!(r == endR && c == endC)) {
        if (steps > R*C) {
            printf("Your maze has no ending\n");
            return;
        }

        right = (d + 1) % 4;
        left  = (d + 3) % 4;
        back  = (d + 2) % 4;

        if (isOpen(R, C, maze, r + dr[right], c + dc[right]))      d = right;
        else if (isOpen(R, C, maze, r + dr[d], c + dc[d]))         d = d;
        else if (isOpen(R, C, maze, r + dr[left], c + dc[left]))   d = left;
        else                                                       d = back;

        r += dr[d];
        c += dc[d];
        steps++;

        if (maze[r][c] == '.') maze[r][c] = '*';

        system("cls");
        printf("Step %d: robot (%d,%d)\n", steps, r, c);
        displayMaze(R, C, maze);
        Sleep(300);
    }

    printf("Robot has reached the end: %d\n", steps);
}

int main() {
    int rows, cols;

    printf("Rows: ");
    scanf("%d", &rows);
    printf("Columns: ");
    scanf("%d", &cols);

    runRobot(rows + 2, cols + 2);
    return 0;
}
