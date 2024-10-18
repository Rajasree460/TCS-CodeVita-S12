import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;

class SimpleGame {
    // Class to represent each position in the grid
    static class Point {
        int row, col, dist;

        Point(int r, int c, int d) {
            row = r;
            col = c;
            dist = d;
        }
    }

    // Directions: forward, right, left, and backward
    static int[][] directions = new int[4][2];

    // Set the movement rules based on the input move (x, y)
    static void setMoveRules(int x, int y) {
        directions[0] = new int[]{x, y};     // Forward
        directions[1] = new int[]{y, -x};    // Right (90 degrees)
        directions[2] = new int[]{-y, x};    // Left (-90 degrees)
        directions[3] = new int[]{-x, -y};   // Backward (180 degrees)
    }

    // Check if the move is valid (within bounds and the cell is 0)
    static boolean isValidMove(int[][] grid, int row, int col) {
        return (row >= 0 && row < grid.length && col >= 0 && col < grid[0].length && grid[row][col] == 0);
    }

    // BFS function to find the shortest path
    static int bfs(int[][] grid, int[] src, int[] dest, int x, int y) {
        setMoveRules(x, y);  // Set up movement rules

        Queue<Point> queue = new LinkedList<>();
        boolean[][] visited = new boolean[grid.length][grid[0].length];
        
        queue.add(new Point(src[0], src[1], 0)); // Start from source
        visited[src[0]][src[1]] = true;          // Mark source as visited

        while (!queue.isEmpty()) {
            Point current = queue.poll();

            // If destination is reached, return the distance (number of moves)
            if (current.row == dest[0] && current.col == dest[1]) {
                return current.dist;
            }

            // Try all 4 possible moves
            for (int[] move : directions) {
                int newRow = current.row + move[0];
                int newCol = current.col + move[1];

                // If the move is valid and not visited yet
                if (isValidMove(grid, newRow, newCol) && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    queue.add(new Point(newRow, newCol, current.dist + 1)); // Move and increment distance
                }
            }
        }

        // Return -1 if destination can't be reached
        return -1;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input grid dimensions M and N
        int M = sc.nextInt();
        int N = sc.nextInt();

        // Input the grid
        int[][] grid = new int[M][N];
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                grid[i][j] = sc.nextInt();
            }
        }

        // Input source and destination coordinates
        int[] src = new int[]{sc.nextInt(), sc.nextInt()};
        int[] dest = new int[]{sc.nextInt(), sc.nextInt()};

        // Input the move rule
        int x = sc.nextInt();
        int y = sc.nextInt();

        // Call BFS to find the minimum moves and print the result
        int result = bfs(grid, src, dest, x, y);
        System.out.println(result);

        sc.close();
    }
}

