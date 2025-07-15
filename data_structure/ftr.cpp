//
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int M = 1e9 + 7;
#define N 20000
#define int long long

void solve()
{
    int n;
    cin >> n;
    // 先读入所有数据
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> b(a);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }

    VI tr(m + 1, 0);
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++)
    {
        int x = a[i];
        for (int j = x; j; j -= (j & -j))
            ans -= tr[j];
        for (int j = x; j <= m; j += (j & -j))
            tr[j]++;
    }
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}