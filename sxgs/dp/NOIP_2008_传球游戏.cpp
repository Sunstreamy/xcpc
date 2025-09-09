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
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<i64>> f(m + 1, vector<i64>(n, 0));
    f[0][0] = 1;
    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j < n; ++j) {
            f[i][j] = f[i - 1][(j - 1 + n) % n] + f[i - 1][(j + 1) % n];
        }
    }
    cout << f[m][0] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}