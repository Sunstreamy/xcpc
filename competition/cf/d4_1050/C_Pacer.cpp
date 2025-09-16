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
    i64 m;
    cin >> n >> m;

    i64 cur_t = 0;
    int cur_pos = 0;
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        i64 ft;
        int fpos;
        cin >> ft >> fpos;

        i64 diff = ft - cur_t;
        i64 score = diff;
        if ((cur_pos + score) % 2 != fpos) {
            score--;
        }
        ans += score;
        cur_t = ft;
        cur_pos = fpos;
    }
    cout << ans + (m - cur_t) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}