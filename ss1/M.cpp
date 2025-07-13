// bfs,两单源最短和。https://vjudge.net/contest/729445#problem/M
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005

vector<string> grid;
int n, m;
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

vector<vector<int>> bfs(int cx, int cy)
{
    vector<vector<int>> dis(n, vector<int>(m, -1));
    queue<pair<int, int>> q;
    q.push({cx, cy});
    dis[cx][cy] = 0;
    while (!q.empty())
    {
        auto cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || xx >= n || yy < 0 || yy >= m)
                continue;
            if (grid[xx][yy] == '#')
                continue;
            if (dis[xx][yy] != -1)
                continue;
            dis[xx][yy] = dis[x][y] + 1;
            q.push({xx, yy});
        }
    }
    return dis;
}

void solve()
{
    grid.resize(n);
    pair<int, int> sy, sm;
    for (int i = 0; i < n; i++)
    {
        cin >> grid[i];
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'Y')
                sy = {i, j};
            else if (grid[i][j] == 'M')
                sm = {i, j};
        }
    }
    vector<vector<int>> disy = bfs(sy.first, sy.second);
    vector<vector<int>> dism = bfs(sm.first, sm.second);

    int ans = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '@')
                if (disy[i][j] != -1 && dism[i][j] != -1)
                {
                    ans = min(ans, disy[i][j] + dism[i][j]);
                }
        }
    }
    cout << ans * 11 << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> m)
    {
        solve();
    }

    return 0;
}
