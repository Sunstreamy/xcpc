//https://www.luogu.com.cn/problem/P12349
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define int long long

int n, m;
int grid[1010][1010];
int dp[1010][2][2];
int dx[] = {0, 0, 1, 1};
int dy[] = {0, 1, 0, 1};

// 计算第 x 行硬币的贡献，
// pre 表示上一行的状态，now 表示本行的状态，nex 表示下一行的状态。
// 若相邻两行翻转状态相同，则两行硬币在该方向应相同，否则应不同，满足条件则计数。
int com(int x, int pre, int now, int nex)
{
    int res = 0;
    for (int r = 1; r <= m; r++)
    {
        int t = 0;
        // 左侧判断：若存在左邻则判断是否相同
        if (grid[x][r] == grid[x][r - 1])
            t++;
        // 右侧判断
        if (grid[x][r] == grid[x][r + 1])
            t++;
        if (x - 1 > 0)
            if (!(now == pre ^ grid[x][r] == grid[x - 1][r]))
                t++;
        if (x + 1 <= n)
            if (!(now == nex ^ grid[x][r] == grid[x + 1][r]))
                t++;
        res += t * t;
    }
    return res;
}

void solve()
{
    cin >> n >> m;
    memset(grid, -1, sizeof(grid));
    for (int i = 1; i <= n; i++)
    {
        string s;
        cin >> s;
        for (int j = 1; j <= m; j++)
        {
            grid[i][j] = s[j - 1] - '0';
        }
    }
    // 初始化第一行（由于第一行上无上一行，用 0 作为默认状态）
    // 枚举第一行与第二行状态的四种组合
    for (int i = 0; i < 4; i++)
    {
        dp[2][dx[i]][dy[i]] = com(1, 0, dy[i], dx[i]);
    }
    for (int i = 3; i <= n + 1; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            dp[i][dx[j]][dy[j]] = max(dp[i - 1][dy[j]][0] + com(i - 1, 0, dy[j], dx[j]), dp[i - 1][dy[j]][1] + com(i - 1, 1, dy[j], dx[j]));
        }
    }
    cout << max({dp[n + 1][0][0], dp[n + 1][0][1], dp[n + 1][1][0], dp[n + 1][1][1]});
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}