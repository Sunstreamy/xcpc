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
constexpr int Maxn = 110;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

bool f[Maxn][Maxn][Maxn][Maxn];

void solve() {
    string a, b;
    cin >> a >> b;

    int La = a.length(), Lb = b.length(), ans = 1;
    a = '#' + a;
    b = '#' + b;

    for (int lena = 0; lena <= La; ++lena) {
        for (int lenb = 0; lenb <= Lb; ++lenb) {
            for (int la = 1, ra = la + lena - 1; ra <= La; ++la, ++ra) {
                for (int lb = 1, rb = lb + lenb - 1; rb <= Lb; ++lb, ++rb) {
                    if (lena + lenb <= 1) {
                        f[la][ra][lb][rb] = true;
                    } else {
                        f[la][ra][lb][rb] = false;
                        if (lena > 1 && a[la] == a[ra]) {
                            f[la][ra][lb][rb] |= f[la + 1][ra - 1][lb][rb];
                        }
                        if (lenb > 1 && b[lb] == b[rb]) {
                            f[la][ra][lb][rb] |= f[la][ra][lb + 1][rb - 1];
                        }
                        if (lena != 0 && lenb != 0 && a[la] == b[rb]) {
                            f[la][ra][lb][rb] |= f[la + 1][ra][lb][rb - 1];
                        }
                        if (lena != 0 && lenb != 0 && b[lb] == a[ra]) {
                            f[la][ra][lb][rb] |= f[la][ra - 1][lb + 1][rb];
                        }
                    }
                    if (f[la][ra][lb][rb]) {
                        ans = max(ans, lena + lenb);
                    }
                }
            }
        }
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