#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 200005
const int M = 1e9 + 7;

int n, m;
int ans;
int dx[4] = {2, 1, -1, -2};
int dy[4] = {1, 2, 2, 1};
void dfs(int x, int y)
{
    if (x == n && y == m)
    {
        ans++;
        return;
    }
    for (int i = 0; i < 4; i++)
    {
        int a = x + dx[i], b = y + dy[i];
        if (a < 0 || a > n || b > m)
        {
            continue;
        }
        dfs(a, b);
    }
}
void solve()
{
    cin >> n >> m;
    dfs(0, 0);
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
