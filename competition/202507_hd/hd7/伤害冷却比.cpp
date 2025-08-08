#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int MOD[] = {998244353, 1000000007};
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------
struct Frac {
    i64 p, q;
    Frac(i64 p_, i64 q_) : p(p_), q(q_) {}
    bool operator<(const Frac& other) const {
        return (i128)p * other.q < (i128)q * other.p;
    }
};

void solve() {
    int k, n, a, b, c, d;
    cin >> k >> n >> a >> b >> c >> d;
    i64 il = 1LL * (k * b) / (n * a);
    i64 ir = 1LL * (k * d) / (n * c);

    Frac p1((ir + 1) * c, d);
    if (ir < il) {
        i64 i = ir + 1;
        Frac p2((i + 1) * k, n * i);
        if (p1 < p2) {
            p1 = p2;
        }
    }
    i64 tt = gcd(p1.p, p1.q);
    p1.p /= tt;
    p1.q /= tt;

    cout << p1.p << '/' << p1.q << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}