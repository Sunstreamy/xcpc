#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 5
const int M = 1e9 + 7;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int g[N][N];
int sx, sy, fx, fy, bx, by;
int row, col, num;
int ans;
void dfs(int x, int y)
{
    if (x == fx && y == fy)
    {
        ans++;
        return;
    }
    for (int i = 0; i < 4; ++i)
    {
        int a = x + dx[i], b = y + dy[i];
        if (a < 1 || a > row || b < 1 || b > col)
        {
            continue;
        }
        if (g[a][b] == 1)
        {
            continue;
        }
        // 确定现场
        g[a][b] = 1;
        dfs(a, b);
        // 恢复现场
        g[a][b] = 0;
    }
}
void solve()
{
    cin >> row >> col >> num;
    cin >> sx >> sy >> fx >> fy;
    for (int i = 0; i < num; ++i)
    {
        cin >> bx >> by;
        g[bx][by] = 1;
    }
    g[sx][sy] = 1;
    dfs(sx, sy);
    cout<<ans<<endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
