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
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    i64 all = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all += a[i];
    }
    if (n == 0) {
        cout << 0 << '\n';
        return;
    }
    vector<i64> cost_lr(n - 1);
    vector<i64> cost_rl(n - 1);

    i64 cur = 0;
    for (int i = 0; i < n - 1; ++i) {
        cur += a[i];
        cost_lr[i] = (cur + k - 1) / k;

        cost_rl[i] = ((all - cur) + k - 1) / k;
    }
    i64 ans = 0;
    for (i64 t : cost_rl) {
        ans += t;
    }
    i64 curc = ans;
    for (int p = 1; p < n; ++p) {
        curc = curc + (cost_lr[p - 1] - cost_rl[p - 1]);
        ans = min(ans, curc);
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}