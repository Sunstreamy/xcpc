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
    i64 sx, sy, tx, ty;
    cin >> sx >> sy >> tx >> ty;

    i64 ans = 0;
    while (1) {
        if (tx == sx && ty == sy) {
            cout << ans << '\n';
            return;
        }
        if (tx < sx || ty < sy) {
            cout << -1 << '\n';
            return;
        }
        if (tx < ty) {
            swap(tx, ty), swap(sx, sy);
        }
        if (tx > ty) {
            if (tx >= 2 * ty) {
                if (tx & 1) {
                    cout << -1 << '\n';
                    return;
                }
                tx >>= 1;
            } else {
                tx -= ty;
            }
        } else if (ty > tx) {
            if (ty >= 2 * tx) {
                if (ty & 1) {
                    cout << -1 << '\n';
                    return;
                }
                ty >>= 1;
            } else {
                ty -= tx;
            }
        } else {
            cout << -1 << '\n';
            return;
        }
        ans++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}