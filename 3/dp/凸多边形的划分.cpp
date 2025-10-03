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
const i128 Inf128 = (i128(1) << 120);
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

// 将 __int128 转换为十进制字符串，避免 64 位溢出
static inline string to_string_i128(i128 x) {
    if (x == 0) return "0";
    bool neg = x < 0;
    if (neg) x = -x;
    string s;
    while (x > 0) {
        int digit = int(x % 10);
        s.push_back(char('0' + digit));
        x /= 10;
    }
    if (neg) s.push_back('-');
    reverse(s.begin(), s.end());
    return s;
}

void solve() {
    // 题意：给定凸 N 边形，顶点权值为正整数。将其剖分成 N-2 个三角形，
    // 每个三角形的代价为三个顶点权值的乘积，求所有三角形代价之和的最小值。
    // 经典区间 DP（最小三角剖分）：
    // dp[l][r] = min_{l<k<r} { dp[l][k] + dp[k][r] + w[l]*w[k]*w[r] }
    // 初始：区间长度 < 3 的代价为 0。

    int n;
    if (!(cin >> n)) return;
    vector<i128> w(n + 1);
    for (int i = 1; i <= n; i++) {
        i64 x;
        cin >> x;
        w[i] = (i128)x;
    }

    vector<vector<i128>> dp(n + 2, vector<i128>(n + 2, 0));
    for (int len = 3; len <= n; len++) {
        for (int l = 1; l + len - 1 <= n; l++) {
            int r = l + len - 1;
            i128 best = Inf128;
            for (int k = l + 1; k <= r - 1; k++) {
                i128 cost = dp[l][k] + dp[k][r] + w[l] * w[k] * w[r];
                if (cost < best) best = cost;
            }
            dp[l][r] = best;
        }
    }

    cout << to_string_i128(dp[1][n]) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 单组数据：按题意只需调用一次 solve()
    solve();

    return 0;
}