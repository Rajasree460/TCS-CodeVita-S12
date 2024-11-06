#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 50

//structure to rep. ecah point in the grid
typedef struct{
    int row, col, dist;
} Point;

//dire:fwd,r,l,bkwd
int dir[4][2];

//set the move rules based on the i/p moves
void setMoveRule(int x, int y){
    //fwd
    dir[0][0]=x;
    dir[0][1]=y;

    //r(90)
    dir[1][0]=y;
    dir[1][1]=-x;

    //l(-90)
    dir[2][0]=-y;
    dir[2][1]=x;

    //bkwd(180)
    dir[3][0]=-x;
    dir[3][1]=-y;
}

//check if the move is valid(within bounds & cell=0)
bool isValidMove(int grid[MAX][MAX], int row, int col, int m, int n){
    return (row>=0 && row<m && col>=0 && col<n && grid[row][col]==0);
}

//BFS to find the shortest path
int bfs(int grid[MAX][MAX], int m, int n, int srcX, int srcY, int destX, int destY, int x, int y){
    //set the move rule
    setMoveRule(x, y);

    //queue for bfs
    Point queue[MAX* MAX];
    int front=0, rear=0;

    //visited array
    bool visited[MAX][MAX]={false};

    //start from the src point
    queue[rear++]=(Point){srcX, srcY, 0};
    // queue[rear].row=srcX;
    // queue[rear].col=srcY;
    // queue[rear].dist=0;
    // rear++;

    visited[srcX][srcY]=true;

    
    //BFS Loop
    while(front<rear){
        //pop the front element
        Point curr=queue[front]; // 2 lines in 1 line=Point curr=queue[front++];
        front++;

        //if destination is reached,return the distance
        if(curr.row==destX && curr.col==destY){
            return curr.dist;
        }

        //check for all 4 possible moves
        for(int i=0; i<4; i++){
            int newRow=curr.row+dir[i][0];
            int newCol=curr.col+dir[i][1];

            //if the move is valid & not visited yet
            if(isValidMove(grid, newRow, newCol, m, n) && !visited[newRow][newCol]){
                //mark the cell as visited
                visited[newRow][newCol]=true;

                //push the cell into the queue
                queue[rear].row=newRow;
                queue[rear].col=newCol;
                queue[rear].dist=curr.dist+1;
                rear++;

                //queue[rear++]=(Point){newRow, newCol, curr.dist+1};
            }
        }
    }

    //if destination is not reachable
    return -1;
}

int main(){
    int m, n;
    int grid[MAX][MAX];

    printf("Enter the number of rows and columns: ");
    scanf("%d %d", &m, &n);

    printf("\nEnter the grid: \n");
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            scanf("%d", &grid[i][j]);
        }
    }

    //input source & destination coordinates
    int srcX, srcY, destX, destY;
    printf("\nEnter the source coordinates: ");
    scanf("%d %d", &srcX, &srcY);
    printf("\nEnter the destination coordinates: ");
    scanf("%d %d", &destX, &destY);


    //input the move rule
    int x, y;
    printf("\nEnter the move rule coordinates: ");
    scanf("%d %d", &x, &y);

    //call bfs function
    int res=bfs(grid, m, n, srcX, srcY, destX, destY, x, y);
    printf("\nMinimum number of moves required: %d\n", res);

    return 0;
}
