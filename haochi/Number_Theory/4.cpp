#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int mod = 998244353;

i64 qpow(int n, int k) {
    i64 r = 1;
    n %= mod;
    while (k) {
        if (k & 1) {
            r = (r * n) % mod;
        }
        n = n * n % mod;
        k >>= 1;
    }
    return r;
}

void solve() {
    int n;
    cin >> n;
    i64 all = qpow(26, n);
    i64 p1 = (3 * qpow(25, n)) % mod;
    i64 p2 = (3 * qpow(24, n)) % mod;
    i64 p3 = qpow(23, n);
    i64 ans = (all - p1 + mod) % mod;
    ans = (ans + p2) % mod;
    ans = (ans - p3 + mod) % mod;
    cout << ans << '\n';
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}