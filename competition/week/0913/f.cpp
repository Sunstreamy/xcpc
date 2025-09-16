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
i64 cal(i64 a, i64 b) {
    i64 diff = abs(a - b);
    return min(diff, 720 - diff);
}

void solve() {
    int x0, y0, x1, y1, x2, y2;
    cin >> x0 >> y0 >> x1 >> y1 >> x2 >> y2;

    i64 h0u = (i64)x0 * (720 / 12) + (i64)y0;
    i64 m0u = (i64)y0 * (720 / 60);

    i64 ans = linf;
    int xx = -1, yy = -1;
    for (int h = x1; h <= x2; ++h) {
        int stm = (h == x1) ? y1 : 0;
        int edm = (h == x2) ? y2 : 59;

        for (int m = stm; m <= edm; ++m) {
            i64 htu = (i64)h * (720 / 12) + i64(m);
            i64 mtu = (i64)m * (720 / 60);

            i64 cur = cal(h0u, htu) + cal(m0u, mtu);
            if (cur < ans) {
                ans = cur;
                xx = h;
                yy = m;
            }
        }
    }
    cout << xx << " " << yy << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}