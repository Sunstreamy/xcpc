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
constexpr int Maxn = 85;
constexpr int MOD[] = {998244353, 1000000007};

template <typename T>
inline void read(T &x) {
    x = 0;
    bool f = false;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = true;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
    if (f) x = -x;
}
template <typename T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
    return;
}
//------------------------------------------------------------------
i128 qow(i128 n, int k) {
    i128 ans = 1;
    while (k) {
        if (k & 1) {
            ans = ans * n;
        }
        n = n * n;
        k >>= 1;
    }
    return ans;
}

// 左边删i，右边删j个的价值
i128 dp[Maxn][Maxn];
i128 p[Maxn];

void solve() {
    int n, m;
    read(n);
    read(m);
    i128 ans = 0;
    vector<int> a(m + 1);

    for (int i = 1; i <= m; ++i) {
        p[i] = qow(2, i);
    }

    while (n--) {
        for (int i = 1; i <= m; ++i) {
            read(a[i]);
        }
        memset(dp, 0, sizeof(dp));
        for (int len = 1; len <= m; ++len) {
            for (int i = 0; i <= len; ++i) {
                int j = len - i;
                i128 fl = 0, fr = 0;

                if (i > 0) {
                    fl = dp[i - 1][j] + (i128)a[i] * p[len];
                }
                if (j > 0) {
                    fr = dp[i][j - 1] + (i128)a[m - j + 1] * p[len];
                }
                dp[i][j] = max(fl, fr);
            }
        }
        i128 cur = 0;
        for (int i = 0; i <= m; ++i) {
            cur = max(cur, dp[i][m - i]);
        }
        ans += cur;
    }
    write(ans);
}

int main() {
    solve();

    return 0;
}