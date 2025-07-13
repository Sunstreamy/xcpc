//摆放所有棋子的可能https://vjudge.net/problem/POJ-1321
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
typedef pair<int, int> PII;
const int M = 1e9 + 7;
#define N 200005

int n, k;
vector<string> grid;
int used[10];
int ans;

void dfs(int r, int placed)
{
    if (r == n)
    {
        if (placed == k)
        {
            ans++;
        }
        return;
    }
    if (n - r < k - placed)
        return;
    dfs(r + 1, placed);
    for (int j = 0; j < n;j++){
        if(grid[r][j]=='#' && !used[j]){
            used[j] = 1;
            dfs(r + 1, placed + 1);
            used[j] = 0;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> n >> k && n!=-1)
    {
        grid.resize(n);
        for (int i = 0; i < n; i++)
        {
            cin >> grid[i];
        }
        ans = 0;
        memset(used, 0, sizeof(used));
        dfs(0, 0);
        cout << ans << '\n';
    }

    return 0;
}
