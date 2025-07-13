//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005

int c, r;
vector<string> grid;
int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void dfs(int x, int y)
{
    grid[x][y] = '*';
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i], yy = y + dy[i];

        if (xx >= 0 && xx < r && yy >= 0 && grid[xx][yy] == '@')
        {
            dfs(xx, yy);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> r >> c && r)
    {
        grid.resize(r);
        for (int i = 0; i < r; i++)
        {
            cin >> grid[i];
        }
        int cnt = 0;
        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                if (grid[i][j] == '@')
                {
                    dfs(i, j);
                    cnt++;
                }
            }
        }
        cout << cnt << '\n';
    }

    return 0;
}
