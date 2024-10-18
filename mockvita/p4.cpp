#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  

#define MAX_EMPLOYEES 1000  
#define MAX_CONFLICTS 100  

int expertise[MAX_EMPLOYEES + 1];  
int conflicts[MAX_EMPLOYEES + 1][MAX_EMPLOYEES + 1];  
int visited[MAX_EMPLOYEES + 1];  
int n, c;  

// Function to perform DFS and collect the set of employees  
void dfs(int node, int* current_set, int* current_expertise, int* current_index) {  
    visited[node] = 1;  
    current_set[*current_index] = node;  
    (*current_expertise) += expertise[node];  
    (*current_index)++;  

    for (int i = 1; i <= n; i++) {  
        if (conflicts[node][i] && !visited[i]) {  
            dfs(i, current_set, current_expertise, current_index);  
        }  
    }  
}  

// Function to find the maximum independent set's expertise  
int findMaxIndependentSet() {  
    int max_expertise = 0;  
    for (int i = 1; i <= n; i++) {  
        memset(visited, 0, sizeof(visited)); // Reset visited for each component  
        if (!visited[i]) {  
            int current_set[MAX_EMPLOYEES + 1] = {0};  
            int current_expertise = 0;  
            int current_index = 0;  

            dfs(i, current_set, &current_expertise, &current_index);  
            // Update max_expertise for the component  
            if (current_expertise > max_expertise) {  
                max_expertise = current_expertise;  
            }  
        }  
    }  
    return max_expertise;  
}  

// Main function  
int main() {  
    scanf("%d %d", &n, &c);  

    // Read conflict pairs  
    for (int i = 0; i < c; i++) {  
        int a, b;  
        scanf("%d %d", &a, &b);  
        conflicts[a][b] = 1; // Mark conflict between a and b  
        conflicts[b][a] = 1; // Undirected conflict  
    }  

    // Read expertise values  
    for (int i = 1; i <= n; i++) {  
        scanf("%d", &expertise[i]);  
    }  

    // Find the maximum expertise of conflict-free teams  
    int result = findMaxIndependentSet();  

    // Output the result  
    printf("%d\n", result);  
    return 0;  
}
