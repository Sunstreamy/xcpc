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
    vector<i64> a(10);
    for (int i = 0; i < 10; ++i) {
        cin >> a[i];
    }
    i64 ans = a[0] + a[4] + a[8];
    i64 O = a[1] + a[3] + a[5] + a[7];
    i64 U = a[2];
    i64 P = a[6] + a[9];

    i64 l = 0, r = 2e10, kmx = 0;
    auto check = [&](i64 k) { return max(0LL, k - O) + max(0LL, k - U) <= P; };

    while (l <= r) {
        i64 m = l + (r - l) / 2;
        if (m == 0) {
            l = m + 1;
            continue;
        }
        if (check(m)) {
            kmx = m;
            l = m + 1;
        } else {
            r = m - 1;
        }
    }
    ans += kmx;
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