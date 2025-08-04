#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;
#define fo(i, l, r) for (int i = (l); i <= (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)

constexpr int M = 1e9 + 7;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }

    if (k >= m) {
        vector<i64> mxc(m, 0);
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                mxc[j] = max(mxc[j], 1LL * a[i][j]);
            }
        }

        i64 ans = accumulate(mxc.begin(), mxc.end(), 0LL);
        cout << ans << '\n';
        return;
    }
    int t = 1 << m;
    vector<vector<i64>> dp(k + 1, vector<i64>(t, 0));

    // // 目标：填充 dp[1] 数组 n*2^m*m
    // for (int i = 0; i < n; ++i) {  // i 是行号
    //     for (int mask = 0; mask < t; ++mask) {
    //         i64 cur_sum = 0;
    //         for (int j = 0; j < m; ++j) {
    //             if ((mask >> j) & 1) {
    //                 cur_sum += a[i][j];
    //             }
    //         }
    //         dp[1][mask] = max(dp[1][mask], cur_sum);
    //     }
    // }

    vector<i64> rsum(t, 0);
    for (int i = 0; i < n; ++i) {
        fill(rsum.begin(), rsum.end(), 0LL);
        for (int mask = 1; mask < t; ++mask) {
            // O(1) 地找到 mask 最低位的1是在第几位（从0开始数）。比如 __builtin_ctz(0b1100) 的结果是 2
            int lsone_idx = __builtin_ctz(mask);
            // 把 mask 的最低位的1变成0，从而得到那个比它小的 prev_mask
            int pre_mask = mask ^ (1 << lsone_idx);
            rsum[mask] = rsum[pre_mask] + a[i][lsone_idx];
        }
        for (int mask = 0; mask < t; ++mask) {
            dp[1][mask] = max(dp[1][mask], rsum[mask]);
        }
    }

    for (int i = 2; i <= k; ++i) {
        for (int mask = 0; mask < t; ++mask) {
            // 遍历一个给定 mask 的所有子集 sub
            for (int sub = mask;; sub = (sub - 1) & mask) {
                int ssub = mask ^ sub;
                dp[i][mask] = max(dp[i][mask], dp[i - 1][sub] + dp[1][ssub]);
                if (sub == 0) break;
            }
        }
    }
    cout << dp[k][t - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}