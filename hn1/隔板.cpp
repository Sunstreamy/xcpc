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
constexpr int maxm = 5010;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
i64 fac[maxm], invfac[maxm];
constexpr int mod = MOD[0];

i64 qpow(i64 n, i64 k) {
    i64 ans = 1;
    n %= mod;
    while (k) {
        if (k & 1) {
            ans = ans * n % mod;
        }
        n = n * n % mod;
        k >>= 1;
    }
    return ans;
}

i64 inv(i64 a) {
    return qpow(a, mod - 2);
}

void init(int n) {
    fac[0] = 1;
    // 不再需要手动设置 invfac[0]
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % mod;
    }
    
    invfac[n] = inv(fac[n]);

    // !! 关键修正点 !!
    // 让循环一直计算到 i = 0
    for (int i = n - 1; i >= 0; --i) { 
        invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
}
i64 comb(int n, int m) {
    return (((fac[n] * invfac[m]) % mod) * invfac[n - m]) % mod;
}

void solve() {
    int n, m;
    cin >> n >> m;

    if (n < m) {
        cout << 0 << '\n';
        return;
    }
    i64 ans = 0;
    for (int i = 0; i <= m; ++i) {
        i64 t = (comb(m, i) * qpow((i64)(m - i), n)) % mod;
        if (i & 1) {
            ans = (ans - t + mod) % mod;
        } else
            ans = (ans + t) % mod;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init(maxm);
    solve();
    return 0;
}