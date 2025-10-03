#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
struct Item {
    int val;
    int cost;
};

// 选择i名从者,k个礼装，总花费为j时候的最大值
int f[6][6][140];

void solve() {
    int n, m, d, val, cost;
    cin >> n >> m >> d;

    int ans = -1;
    // i 是“我们正在考虑第几个从者”。它是一个过程变量。
    // k 是“我们队伍里已经有几个从者”。它是一个状态变量。
    for (int i = 1; i <= n; ++i) {
        cin >> val >> cost;
        for (int j = d; j >= cost; --j) {
            for (int k = 1; k <= 5; ++k) {
                f[k][0][j] = max(f[k][0][j], f[k - 1][0][j - cost] + val);
                ans = max(f[k][0][j], ans);
            }
        }
    }

    for (int i = 1; i <= m; ++i) {
        cin >> val >> cost;
        for (int k = 1; k <= 5; ++k) {
            for (int j = d; j >= cost; --j) {
                for (int l = 1; l <= k; ++l) {
                    f[k][l][j] = max(f[k][l][j], f[k][l - 1][j - cost] + val);
                    ans = max(f[k][l][j], ans);
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}