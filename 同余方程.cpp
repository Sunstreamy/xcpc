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
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}
i64 getInv(i64 a, i64 b) {
    i64 x, y, d = exgcd(a, b, x, y);
    return (x % b + b) % b;
}

void solve() {
    i64 a, b;
    cin >> a >> b;
    cout << getInv(a, b) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}