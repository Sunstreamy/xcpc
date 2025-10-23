#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using db = double;
using ldb = long double;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr db Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 3000005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
i64 inv[Maxn];
void solve() {
    int n;
    i64 p;
    cin >> n >> p;
    // 1. 基础情况
    inv[1] = 1;
    cout << inv[1] << '\n';
    // 2. 线性递推
    for (int i = 2; i <= n; ++i) {
        inv[i] = (p - p / i) * inv[p % i] % p;
        cout << inv[i] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}