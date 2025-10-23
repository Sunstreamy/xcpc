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
int n, m, mod;
i64 fac[Maxn], invfac[Maxn];

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
// 费马小定理求逆元（mod必须是质数，且需要满足 x 与mod互质
i64 inv(i64 a) {
    return qpow(a, mod - 2);
}

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % mod;
    }
    // 计算最大阶乘的逆元，然后递推
    invfac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i) {
        invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
}

i64 comb(int n, int m) {
    return (((fac[n] * invfac[m]) % mod) * invfac[n - m]) % mod;
}
i64 lucas(i64 n, i64 m) {
    return m ? comb(n % mod, m % mod) * lucas(n / mod, m / mod) % mod : 1;
}

void solve() {
    cin >> n >> m >> mod;
    init(mod - 1);
    cout << lucas(n + m, m) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}