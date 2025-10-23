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
    int v, m;
    cin >> v >> m;

    vector<i64> f(v + 1);
    for (int i = 0; i < m; ++i) {
        i64 w, im;
        cin >> w >> im;
        i64 value = (i64)w * im;
        for (int j = v; j >= w; --j) {
            f[j] = max(f[j], f[j - w] + value);
        }
    }
    cout << f[v] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}