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

struct Opt {
    int x, y, id;
};

void solve() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<Opt> ops(k);
    for (int i = 0; i < k; ++i) {
        cin >> ops[i].x >> ops[i].y;
        ops[i].id = i + 1;
    }

    sort(ops.begin(), ops.end(), [](const Opt& a, const Opt& b) {
        if (a.x != b.x) {
            return a.x < b.x;
        }
        return a.id < b.id;
    });

    const vector<pair<int, int>> rel = {{0, 0},  {-1, 0},  {-2, -2}, {-2, -1}, {-2, 0}, {-2, 1},
                                        {-2, 2}, {-3, -1}, {-3, 0},  {-3, 1},  {-4, 0}};

    vector<vector<int>> grid(n + 1, vector<int>(m + 1, 0));
    for (const auto& op : ops) {
        for (const auto& offset : rel) {
            int nx = op.x + offset.first;
            int ny = op.y + offset.second;

            if (nx >= 1 && nx <= n && ny >= 1 && ny <= m) {
                grid[nx][ny] = op.id;
            }
        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (grid[i][j] == 0) {
                cout << '.';
            } else {
                cout << grid[i][j];
            }
        }
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}