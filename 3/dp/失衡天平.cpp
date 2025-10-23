#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    //只考虑前 i 件武器，当我们将选出的武器子集划分到天平两端后，得到的重量差恰好为 j 时，这个子集的最大总重量是多少
    vector<vector<int>> f(n + 1, vector<int>(10001, -inf));

    f[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 10001; ++j) {
            f[i][j] = max({f[i - 1][j], f[i - 1][abs(j - a[i])] + a[i], f[i - 1][j + a[i]] + a[i]});
        }
    }
    int ans = -inf;
    for (int i = 0; i <= m; ++i) {
        ans = max(f[n][i], ans);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}