#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 30
const int M = 1e9 + 7;
int n, ans;
int c[N], pos[N], col[N], pie[N], na[N];
void print_()
{
    if (ans <= 3)
    {
        for (int i = 1; i <= n; i++)
        {
            cout << pos[i] << " ";
        }
        cout << endl;
    }
}
void dfs(int d)
{
    if (d > n)
    {
        ans++;
        print_();
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        if (col[i] || pie[i + d] || na[i - d + n])
            continue;
        pos[d] = i;
        col[i] = pie[i + d] = na[i - d + n] = 1;
        dfs(d + 1);
        col[i] = pie[i + d] = na[i - d + n] = 0;
    }
}
void solve()
{
    cin >> n;
    dfs(1);
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
