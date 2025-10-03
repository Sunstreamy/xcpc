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
constexpr int Maxn = 405;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

i64 pre[Maxn];
int a[Maxn];
i64 dpMin[Maxn][Maxn];
i64 dpMax[Maxn][Maxn];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        a[i + n] = a[i];
    }

    for (int i = 1; i <= 2 * n; ++i) {
        pre[i] = a[i] + pre[i - 1];
    }

    memset(dpMin, Inf, sizeof(dpMin));
    memset(dpMax, 0, sizeof(dpMax));
    for (int i = 1; i <= 2 * n; ++i) {
        dpMin[i][i] = 0;
    }

    // 合并区间 [i, j] 的总成本，等于先将它分裂成 [i, k] 和 [k+1,
    // j]，分别合并成两堆的成本，再加上最后一次将这两大堆合并的成本。
    for (int len = 2; len <= n; ++len) {
        for (int i = 1; i <= 2 * n - len + 1; ++i) {
            int j = i + len - 1;

            for (int k = i; k < j; ++k) {
                i64 cost = pre[j] - pre[i - 1];
                dpMin[i][j] = min(dpMin[i][j], dpMin[i][k] + dpMin[k + 1][j] + cost);
                dpMax[i][j] = max(dpMax[i][j], dpMax[i][k] + dpMax[k + 1][j] + cost);
            }
        }
    }
    i64 mnAns = Linf;
    i64 mxAns = 0;
    for (int i = 1; i <= n;++i){
        mnAns = min(mnAns, dpMin[i][i + n - 1]);
        mxAns = max(mxAns, dpMax[i][i + n - 1]);
    }
    cout << mnAns << '\n';
    cout << mxAns << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}