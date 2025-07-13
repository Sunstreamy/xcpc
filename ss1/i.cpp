//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
typedef pair<int, int> PII;
const int M = 1e9 + 7;
#define N 200005

int r, c;
vector<string> grid;
vector<vector<int>> f_t;
vector<vector<int>> m_t;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};

void solve()
{
    queue<PII> fq;
    queue<PII> mq;
    PII pos;
    m_t.assign(r, vector<int>(c, INT_MAX));
    f_t.assign(r, vector<int>(c, -1));

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (grid[i][j] == 'F')
            {
                f_t[i][j] = 0;
                fq.push({i, j});
            }
            else if (grid[i][j] == 'J')
            {
                pos = {i, j};
            }
        }
    }
    
    while (!fq.empty())
    {
        auto [x, y] = fq.front();
        fq.pop();
        for (int i = 0; i < 4; i++)
        {
            int xx = x + dx[i], yy = y + dy[i];
            if (xx < 0 || xx >= r || yy < 0 || yy >= c)
                continue;
            if (grid[xx][yy] == '#')
                continue;
            if (f_t[xx][yy] != -1)
                continue;
            f_t[xx][yy] = f_t[x][y] + 1;
            fq.push({xx, yy});
        }
    }
    m_t[pos.first][pos.second] = 0;
    mq.push(pos);
    bool ok = false;
    int ans = -1;
    while (!mq.empty())
    {
        auto [x, y] = mq.front();
        mq.pop();
        if (x == 0 || x == r - 1 || y == 0 || y == c - 1)
        {
            ok = true;
            ans = m_t[x][y] + 1;
            break;
        }
        for (int i = 0; i < 4; i++)
        {
            int xx = dx[i] + x, yy = dy[i] + y;
            if (xx < 0 || xx >= r || yy < 0 || yy >= c)
                continue;
            if (grid[xx][yy] == '#' || m_t[xx][yy] != INT_MAX)
                continue;
            int tt = m_t[x][y] + 1;
            if (tt >= f_t[xx][yy] && f_t[xx][yy] != -1)
                continue;
            m_t[xx][yy] = tt;
            mq.push({xx, yy});
        }
    }
    if (ok)
        cout << ans << '\n';
    else
        cout << "IMPOSSIBLE" << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--)
    {
        cin >> r >> c;
        grid.resize(r);
        for (int i = 0; i < r; i++)
        {
            cin >> grid[i];
        }
        solve();
    }
    return 0;
}
