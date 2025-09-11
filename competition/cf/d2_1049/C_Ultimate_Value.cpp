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
    int n;
    cin >> n;
    vector<i64> a(n + 1);
    i64 ini = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (i & 1) {
            ini += a[i];
        } else
            ini -= a[i];
    }

    i64 ans = ini;

    i64 opt = -linf;
    i64 cur = 0;
    if (n > 1) {
        int fi_odd = 1;
        int lst_odd = (n & 1) ? n : n - 1;
        cur = max(cur, (i64)lst_odd - fi_odd);

        int fi_even = 2;
        int lst_even = (n & 1) ? n - 1 : n;
        cur = max(cur, (i64)lst_even - fi_even);

        opt = max(opt, ini + cur);
    }

    i64 cur2 = linf;
    for (int i = 1; i <= n; ++i) {
        if (i & 1) {
            cur2 = min(cur2, i + 2 * a[i]);
        } else {
            if (cur2 != linf) {
                i64 delt = (i + 2 * a[i] - cur2);
                opt = max(opt, ini + delt);
            }
        }
    }

    i64 cur3 = -linf;
    for (int i = 1; i <= n; ++i) {
        if (!(i & 1)) {
            cur3 = max(cur3, 2 * a[i] - i);
        } else {
            if (cur3 != -linf) {
                i64 delt = cur3 - (2 * a[i] - i);
                opt = max(opt, ini + delt);
            }
        }
    }

    if (opt > -linf) {
        ans = max(ans, opt);
    }
    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}