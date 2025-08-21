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
//-----------------------------------------------------------------
struct Bellman_Ford {
    int n;
    vector<tuple<int, int, i64>> edges;
    vector<i64> dist;

    Bellman_Ford(int n_) : n(n_), dist(n_ + 1, linf) {};

    void ad(int u, int v, i64 w) {
        edges.push_back({u, v, w});
    }

    bool run(int st) {
        dist[st] = 0;

        for (int i = 1; i < n; ++i) {
            bool upd = false;
            for (const auto& edge : edges) {
                auto [u, v, w] = edge;
                if (dist[u] != linf && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    upd = true;
                }
            }
            if (!upd) break;
        }

        for (const auto& edge : edges) {
            auto [u, v, w] = edge;
            if (dist[u] != linf && dist[v] > dist[u] + w) {
                return false;
            }
        }
        return true;
    }
};

void solve() {
    int n, m, c;
    cin >> n >> m >> c;
    Bellman_Ford bf(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        bf.ad(u, v, w);
        bf.ad(v, u, w);
    }
    for (int i = 0; i < c; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        bf.ad(u, v, -w);
    }
    bool flag = false;
    for (int i = 1; i <= n; ++i) {
        if (bf.dist[i] == linf) {
            if (!bf.run(i)) {
                flag = true;
                break;
            }
        }
    }
    if (flag) {
        cout << "YES" << '\n';
        return;
    }
    cout << "NO" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}