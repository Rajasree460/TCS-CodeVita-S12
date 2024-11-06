#include <iostream>
#include <vector>
using namespace std;
void Solve(int i, int j, vector<vector<int>> &table, vector<vector<int>> &count)
{
    int n = table.size(), m = table[0].size();
    if (i >= n || j >= m)
        return;
    // For down
    if (i + 1 < n && table[i + 1][j] >= table[i][j])
    {
        count[i + 1][j]++;
        Solve(i + 1, j, table, count);
    }
    // For right
    if (j + 1 < m && table[i][j + 1] >= table[i][j])
    {
        count[i][j + 1]++;
        Solve(i, j + 1, table, count);
    }
}
int main()
{
    int n, m, k;
    cin >> n >> m;

    // Read the table
    vector<vector<int>> table(n, vector<int>(m));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> table[i][j];
        }
    }

    // Read the value of k
    cin >> k;
    vector<vector<int>> count(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            Solve(i, j, table, count);
        }
    }
    bool found = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (count[i][j] == k)
            {
                cout << i << " " << j << endl;
                found = true;
            }
        }
    }
    if (!found)
        cout << "NO";
    return 0;
}
