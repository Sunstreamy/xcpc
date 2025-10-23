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

vector<int> prime, maxp, minp;
i64 factor[30], fSize, factorExp[30];
void sieve(int n) {
    minp.resize(n + 1);
    maxp.resize(n + 1);

    for (int i = 2; i <= n; ++i) {
        if (!minp[i]) {
            minp[i] = i;
            maxp[i] = i;
            prime.push_back(i);
        }
        for (auto p : prime) {
            if (p > minp[i] || p > n / i) {
                break;
            }
            minp[i * p] = p;
            maxp[i * p] = maxp[i];
        }
    }
}
void getFactor(i64 x) {
    fSize = 0;
    i64 t = sqrt(x + 0.5);
    for (i64 i = 0; i < prime.size() && prime[i] <= t; ++i)
        if (x % prime[i] == 0) {
            factor[fSize++] = prime[i];
            while (x % prime[i] == 0) {
                x /= prime[i];
            }
        }
    if (x > 1) {
        factor[fSize++] = x;
    }
}

void solve() {
    i64 n;
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }

    sieve(sqrt(n + 0.5));
    getFactor(n);
    cout << factor[fSize - 1] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}