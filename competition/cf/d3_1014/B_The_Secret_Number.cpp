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
    i64 n;
    cin >> n;

    vector<i64> ans;
    i64 tt = 10;
    while (1) {
        i64 d = tt + 1;

        if (d > n) {
            break;
        }
        if (n % d == 0) {
            i64 x = n / d;
            ans.push_back(x);
        }

        tt *= 10;
    }
    sort(ans.begin(), ans.end());
    if (ans.empty()) {
        cout << 0 << '\n';
        return;
    } else {
        cout << ans.size() << '\n';
        for (i64 t : ans) {
            cout << t << ' ';
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}