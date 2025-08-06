#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int MOD[] = {998244353, 1000000007};
constexpr int mod = MOD[1];

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<int> b(n + 1);
    vector<i64> pres(n + 1, 0), prex(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> b[i];
    }
    for (int i = 1; i <= n; ++i) {
        pres[i] = pres[i - 1] + b[i];
        prex[i] = prex[i - 1] ^ a[i];
    }
    i64 ans = 0;
    // 对于一个固定的位 k，计算 TotalSum_k = Σ_{i,j} ( bit_k(X(i,j)) * S(i, j) )。
    for (int k = 0; k < 30; ++k) {
        // 存贮当前这一位k的总贡献值
        i64 cur_ksum = 0;
        i64 cnt0 = 1, sum0 = 0;
        i64 cnt1 = 0, sum1 = 0;

        for (int j = 1; j <= n; ++j) {
            if ((prex[j] >> k) & 1) {
                // 如果当前这一位是1，那么需要与其他第k位为0的pre配对才能产生贡献
                //  贡献 = cnt0 * pres[j] - sum0
                i64 p1 = cnt0 * pres[j] % mod;
                i64 contri = (p1 - sum0 + mod) % mod;
                cur_ksum = (cur_ksum + contri) % mod;
            } else {
                i64 p1 = cnt1 * pres[j] % mod;
                i64 contri = (p1 - sum1 + mod) % mod;
                cur_ksum = (cur_ksum + contri) % mod;
            }

            if ((prex[j] >> k) & 1) {
                cnt1++;
                sum1 = (sum1 + pres[j]) % mod;
            } else {
                cnt0++;
                sum0 = (sum0 + pres[j]) % mod;
            }
        }
        i64 q = 1LL << k;
        ans = (ans + (q % mod * cur_ksum) % mod) % mod;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}
