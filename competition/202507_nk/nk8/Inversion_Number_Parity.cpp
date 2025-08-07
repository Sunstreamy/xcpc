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
constexpr u32 U = (1u << 30) - 1;

void solve() {
    int n;
    u32 A, B, C;
    cin >> n >> A >> B >> C;

    u32 fm3 = A & U;
    u32 fm2 = B & U;
    u32 fm1 = C & U;

    auto get = [&]() -> u32 {
        u32 g_i = fm3 ^ (((u64)fm3 << 16) & U);

        u32 h_i = g_i ^ (g_i >> 5);

        u32 fi = h_i ^ (((u64)h_i << 1) & U) ^ fm1 ^ fm2;

        fm3 = fm2;
        fm2 = fm1;
        fm1 = fi;

        return fi;
    };
    i64 cur = 0;
    string ans;
    ans.reserve(n);
    for (int i = 0; i < n; ++i) {
        u32 fi = get();
        if (n - i > 0) {
            if ((fi % (u32)(n - i)) != 0) {
                cur ^= 1;
            }
        }
    }
    ans += (cur == 0 ? '0' : '1');
    // cout << '\n';
    for (int i = 1; i < n; ++i) {
        u32 f1 = get(), f2 = get(), f3 = get();
        u32 c1 = f1 % (u32)n, c2 = f2 % (u32)n;
        u32 li = min(c1, c2), ri = max(c1, c2);
        u32 leni = ri - li + 1;
        u32 di = (f3 % (u32)n) + 1;
        // cout << '(' << li << ',' << ri << ',' << di << ')' << '\n';

        if (!(leni & 1) && di & 1) {
            cur ^= 1;
        }
        ans += ((cur % 2) != 0 ? '1' : '0');
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}