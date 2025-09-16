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
struct Cell {
    int h, x, y;
};

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m, 0));
    vector<Cell> cells;
    cells.reserve(n * m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> h[i][j];
            cells.push_back({h[i][j], i, j});
        }
    }
    sort(cells.begin(), cells.end(), [](Cell &a, Cell &b) { return a.h < b.h; });

    vector<vector<int>> f(n, vector<int>(m, 1));
    int ans = 1;

    for (const auto &t : cells) {
        int x = t.x;
        int y = t.y;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                if (h[nx][ny] > h[x][y]) {
                    f[nx][ny] = max(f[nx][ny], 1 + f[x][y]);
                    ans = max(ans, f[nx][ny]);
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}