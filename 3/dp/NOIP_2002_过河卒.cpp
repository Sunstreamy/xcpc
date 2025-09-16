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
int dx[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};

void solve() {
    int n, m, hx, hy;
    cin >> n >> m >> hx >> hy;

    vector<vector<i64>> f(n + 1, vector<i64>(m + 1, 0));
    vector<vector<bool>> con(n + 1, vector<bool>(m + 1, false));

    if (!con[0][0]) f[0][0] = 1;
    con[hx][hy] = true;

    for (int i = 0; i < 8; i++) {
        int nx = hx + dx[i];
        int ny = hy + dy[i];

        if (nx >= 0 && nx <= n && ny >= 0 && ny <= m) {
            con[nx][ny] = true;
        }
    }

    if (!con[0][0]) f[0][0] = 1;
    con[hx][hy] = true;

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (con[i][j]) {
                continue;
            }
            if (i > 0) {
                f[i][j] += f[i - 1][j];
            }
            if (j > 0) {
                f[i][j] += f[i][j - 1];
            }
        }
    }
    cout << f[n][m] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}