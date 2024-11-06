#include <stdio.h>
#include <string.h>
#include <corecrt_malloc.h>


// Function to find if x can be formed from y
int can_form(char* x, char* y, int lenX, int lenY, int S, int R, int* res) {
  int* dp = (int*)malloc((lenX + 1) * sizeof(int)); // Dynamic programming array to store the minimum number of substrings needed
    int* path = (int*)malloc((lenX + 1) * sizeof(int)); // To track from where the substring is taken (0 = from Y, 1 = from reversed Y)
    
    dp[0] = 0; // No substrings needed to form an empty string
    
    // Iterate over the length of X
    for (int i = 1; i <= lenX; i++) {
        dp[i] = 1000000000; // Set to a large value initially
        
        // Try matching a substring from Y
        for (int j = 1; j <= lenY && j <= i; j++) {
            if (strncmp(x+ i - j, y + lenY - j, j) == 0) {
                if (dp[i - j] + 1 < dp[i]) {
                    dp[i] = dp[i - j] + 1;
                    path[i] = 0; // From Y
                }
            }
            // Try matching a substring from reversed Y
            if (strncmp(x + i - j, y, j) == 0) {
                if (dp[i - j] + 1 < dp[i]) {
                    dp[i] = dp[i - j] + 1;
                    path[i] = 1; // From reversed Y
                }
            }
        }
    }
    
    if (dp[lenX] == 1000000000) return 0; // If dp[lenX] is unchanged, X cannot be formed from Y

    int subY = 0, subRevY = 0;
    for (int i = lenX; i > 0;) {
        if (path[i] == 0) subY++;
        else subRevY++;
        i -= (subY + subRevY); // Move back by the number of substrings
    }

    *res = subY * S + subRevY * R; // Calculate the String Factor
    free(dp);
    free(path);
    return 1;
}


int main() {
    char x[10001], y[10001], revY[10001];
    int S, R;
    int lenX=0,lenY=0;
    // Input strings X and Y
    scanf("%s", x);
    scanf("%s", y);

    // Input S and R
    scanf("%d %d", &S, &R);

    int lenX = strlen(x);
    int lenY = strlen(y);

    int res=0;
    if(can_form(x, y, lenX, lenY, S, R,&res)) {
        printf("%d\n", res);
    } else{
        printf("-1\n");
    }
    return 0;
}
