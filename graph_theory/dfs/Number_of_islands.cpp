#include <bits/stdc++.h>
using namespace std;
#define int long long

int g[52][52];
int r, c;
int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
int dy[8] = {1, 1, 1, 0, -1, -1, -1, 0};

void dfs_sea(int x, int y)
{
    if (x < 0 || x > r + 1 || y < 0 || y > c + 1 || g[x][y] != 0)
        return;
    g[x][y] = 2;

    for (int i = 0; i < 8; i++)
    {
        dfs_sea(x + dx[i], y + dy[i]);
    }
}

void dfs_ground(int x, int y)
{
    if ((x >= 0 && x <= r + 1) && (y >= 0 && y <= c + 1))
    {
        if (g[x][y] == 1)
        {
            g[x][y] = 3;
            dfs_ground(x, y + 1);

            dfs_ground(x + 1, y);

            dfs_ground(x, y - 1);

            dfs_ground(x - 1, y);
        }
    }
}

void solve()
{

    cin >> r >> c;
    for (int i = 0; i < c + 2; i++)
    {
        g[0][i] = 0;
        g[r + 1][i] = 0;
    }
    for (int i = 0; i < r + 2; i++)
    {
        g[i][0] = 0;
        g[i][c + 1] = 0;
    }
    for (int i = 1; i < r + 1; i++)
    {
        for (int j = 1; j < c + 1; j++)
        {
            char c;
            cin >> c;
            g[i][j] = c - '0';
        }
    }
    dfs_sea(0, 0);

    int cnt = 0;
    for (int i = 0; i < r + 2; i++)
    {
        for (int j = 0; j < c + 2; j++)
        {
            if (g[i][j] == 1 && g[i - 1][j] == 2)
            {
                dfs_ground(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << "\n";
}

signed main()
{
    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }

    // 请在此输入您的代码
    return 0;
}

//https://www.lanqiao.cn/problems/3513/learning/