#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 50

// Structure to represent each point in the grid
typedef struct {
    int row, col, dist;
} Point;

// Directions: forward, right, left, and backward
int directions[4][2];

// Set the movement rules based on the input move (x, y)
void setMoveRules(int x, int y) {
    directions[0][0] = x;   directions[0][1] = y;   // Forward
    directions[1][0] = y;   directions[1][1] = -x;  // Right (90 degrees)
    directions[2][0] = -y;  directions[2][1] = x;   // Left (-90 degrees)
    directions[3][0] = -x;  directions[3][1] = -y;  // Backward (180 degrees)
}

// Check if the move is valid (within bounds and the cell is 0)
bool isValidMove(int grid[MAX][MAX], int row, int col, int M, int N) {
    return (row >= 0 && row < M && col >= 0 && col < N && grid[row][col] == 0);
}

// BFS function to find the shortest path
int bfs(int grid[MAX][MAX], int M, int N, int srcRow, int srcCol, int destRow, int destCol, int x, int y) {
    setMoveRules(x, y);  // Set up movement rules

    // Queue for BFS
    Point queue[MAX * MAX];
    int front = 0, rear = 0;
    
    // Visited array
    bool visited[MAX][MAX] = { false };

    // Start from the source point
    queue[rear++] = (Point){srcRow, srcCol, 0};
    visited[srcRow][srcCol] = true;

    // BFS Loop
    while (front < rear) {
        Point current = queue[front++];

        // If destination is reached, return the distance (number of moves)
        if (current.row == destRow && current.col == destCol) {
            return current.dist;
        }

        // Try all 4 possible moves
        for (int i = 0; i < 4; i++) {
            int newRow = current.row + directions[i][0];
            int newCol = current.col + directions[i][1];

            // If the move is valid and not visited yet
            if (isValidMove(grid, newRow, newCol, M, N) && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                queue[rear++] = (Point){newRow, newCol, current.dist + 1};  // Move and increment distance
            }
        }
    }

    // Return -1 if destination can't be reached
    return -1;
}

int main() {
    int M, N;
    int grid[MAX][MAX];

    // Input grid dimensions M and N
    scanf("%d %d", &M, &N);

    // Input the grid
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    // Input source and destination coordinates
    int srcRow, srcCol, destRow, destCol;
    scanf("%d %d", &srcRow, &srcCol);
    scanf("%d %d", &destRow, &destCol);

    // Input the move rule
    int x, y;
    scanf("%d %d", &x, &y);

    // Call BFS to find the minimum moves and print the result
    int result = bfs(grid, M, N, srcRow, srcCol, destRow, destCol, x, y);
    printf("%d\n", result);

    return 0;
}

