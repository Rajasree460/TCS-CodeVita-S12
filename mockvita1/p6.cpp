#include <stdio.h>
#include <stdbool.h>

#define N 9

bool isSafe(int grid[N][N], int row, int col, int num) {
    int i, j;

    // Check row
    for (i = 0; i < N; i++)
        if (grid[row][i] == num)
            return false;

    // Check column
    for (i = 0; i < N; i++)
        if (grid[i][col] == num)
            return false;

    // Check 3x3 sub-grid
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (i = startRow; i < startRow + 3; i++)
        for (j = startCol; j < startCol + 3; j++)
            if (grid[i][j] == num)
                return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row, col;

    // Find an empty cell
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == 0)
                break;

    // If no empty cell found, the puzzle is solved
    if (row == N || col == N)
        return true;

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;

            if (solveSudoku(grid))
                return true;

            // If placing num doesn't lead to a solution, backtrack
            grid[row][col] = 0;
        }
    }

    return false;
}

int main() {
    int grid[N][N];
    int hints[N * N], hintCount = 0;
    int k;

    // Read the puzzle from input
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
            if (grid[i][j] % 10 == 0) {
                hints[hintCount++] = grid[i][j] / 10;
                grid[i][j] = 0;
            }
        }

    // Read hints and K
    scanf("%d", &hintCount);
    for (int i = 0; i < hintCount; i++)
        scanf("%d", &hints[i]);
    scanf("%d", &k);

    // Solve the puzzle
    if (solveSudoku(grid)) {
        // Check if the solved puzzle matches the original hints
        int errors = 0;
        for (int i = 0; i < hintCount; i++) {
            int row = hints[i] / 10 - 1;
            int col = hints[i] % 10 - 1;
            if (grid[row][col] != hints[i] / 10)
                errors++;
        }

        if (errors <= k) {
            printf("Won\n");
            for (int i = 0; i < hintCount; i++) {
                int row = hints[i] / 10 - 1;
                int col = hints[i] % 10 - 1;
                if (grid[row][col] != hints[i] / 10)
                    printf("%d %d\n", row, col);
            }
        } else {
            printf("Impossible\n");
        }
    } else {
        printf("Impossible\n");
    }

    return 0;
}
