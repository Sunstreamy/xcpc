#include <bits/stdc++.h>
using namespace std;
const int M = 1e9 + 7;
#define N 200005

int dx[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int n, k;
int grid[11][11];
bool vis[11][11];
bool edge[11][11][11][11];
string path;

bool solve(int x, int y)
{
    if (x == n - 1 && y == n - 1)
    {
        return path.size() == n * n - 1;
    }
    vis[x][y] = true;
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];
        if (xx < 0 || xx >= n || yy < 0 || yy >= n)
            continue;
        if (vis[xx][yy])
            continue;
        if (edge[x][yy][xx][y] || edge[xx][y][x][yy])
            continue;
        if (grid[xx][yy] != (grid[x][y] + 1) % k)
            continue;
        edge[x][y][xx][yy] = true;
        path += i + '0';
        if (solve(xx, yy))
            return true;
        // 恢复现场
        path.pop_back();
        edge[x][y][xx][yy] = false;
    }
    vis[x][y] = false;
    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];
    }
    if (solve(0, 0))
    {
        cout << path << endl;
    }
    else
    {
        cout << -1 << endl;
    }
    return 0;
}

//https://www.lanqiao.cn/problems/19712/learning/