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

constexpr int MX = 26;
i64 cost[MX], p[MX];

void pre() {
    p[0] = 1;
    for (int i = 1; i < MX; ++i) {
        p[i] = p[i - 1] * 3;
    }

    cost[0] = 3;
    for (int i = 1; i < MX; ++i) {
        cost[i] = p[i + 1] + (i64)i * p[i - 1];
    }
}

void solve() {
    i64 n, k;
    cin >> n >> k;
    i64 ez = 0;

    vector<int> cnt(MX, 0);
    i64 t = n;
    for (int i = 0; t > 0 && i < MX; ++i) {
        cnt[i] = t % 3;
        t /= 3;
        ez += cnt[i];
    }
    if (ez > k) {
        cout << -1 << '\n';
        return;
    }

    i64 ava = (k - ez) / 2;

    for (int i = MX - 1; i >= 1; --i) {
        if (ava == 0) break;

        i64 curspl = min((i64)cnt[i], ava);

        if (curspl > 0) {
            cnt[i] -= curspl;
            cnt[i - 1] += curspl * 3;
            ava -= curspl;
        }
    }
    i64 ans = 0;
    for (int i = 0; i < MX; ++i) {
        if (cnt[i] > 0) {
            ans += (i64)cnt[i] * cost[i];
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pre();

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}