#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <windows.h>

const int N = 8;  // Size of the chessboard (8x8)
int board[N][N];
int movesX[] = {2, 1, -1, -2, -2, -1, 1, 2};
int movesY[] = {1, 2, 2, 1, -1, -2, -2, -1};

bool isSafe(int x, int y) {
    return (x >= 0 && y >= 0 && x < N && y < N && board[x][y] == -1);
}

void printSolution() {
    int x, y, px, py;
    int cellSize = 50;

    for (x = 0; x < N; x++) {
        for (y = 0; y < N; y++) {
            int color = (x + y) % 2 == 0 ? WHITE : BLACK;  // Alternate black and white squares
            setfillstyle(SOLID_FILL, color);
            bar(x * cellSize, y * cellSize, (x + 1) * cellSize, (y + 1) * cellSize);
            if (board[x][y] != -1) {
                px = x * cellSize + cellSize / 2;\
                py = y * cellSize + cellSize / 2;
                setfillstyle(SOLID_FILL, RED);
                setcolor(RED);
                circle(px, py, cellSize / 4);
                floodfill(px, py, RED);
            }
        }
    }
    delay(1000);  // Smooth the animation
}

bool solveKTUtil(int x, int y, int movei) {
    if (movei == N * N)
        return true;

    int k, next_x, next_y;
    for (k = 0; k < 8; k++) {
        next_x = x + movesX[k];
        next_y = y + movesY[k];
        if (isSafe(next_x, next_y)) {
            board[next_x][next_y] = movei;
            printSolution();
            if (solveKTUtil(next_x, next_y, movei + 1))
                return true;
            else
                board[next_x][next_y] = -1;
        }
    }
    return false;
}

bool solveKT() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = -1;

    int startX = 0, startY = 0;
    board[startX][startY] = 0;

    if (!solveKTUtil(startX, startY, 1)) {
        std::cout << "Solution does not exist." << std::endl;
        return false;
    } else {
        std::cout << "Knight's tour found!" << std::endl;
        return true;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\Turboc3\\BGI");

    if (solveKT()) {
        delay(2000);  // Keep the final result for a while
        getch();
        closegraph();
        return 0;
    }

    closegraph();
    return 1;
}
