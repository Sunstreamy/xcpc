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
    vector<int> a;
    int t;
    while (cin >> t) {
        a.push_back(t);
    }
    int n = a.size();

    vector<int> f(n), g(n);
    int ans1 = 0, ans2 = 0;
    for (int i = 0; i < n; ++i) {
        f[i] = g[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (a[j] >= a[i]) {
                f[i] = max(f[i], f[j] + 1);
            } else {
                g[i] = max(g[i], g[j] + 1);
            }
        }
        ans1 = max(ans1, f[i]);
        ans2 = max(ans2, g[i]);
    }
    cout << ans1 << '\n';
    cout << ans2 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}