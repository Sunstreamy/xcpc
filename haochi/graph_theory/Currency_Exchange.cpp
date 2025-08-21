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
struct Bellman_Ford {
    int n;
    vector<tuple<int, int, f64, f64>> edges;
    vector<f64> dist;

    Bellman_Ford(int n_) : n(n_), dist(n_ + 1) {};

    void add_edge(int u, int v, f64 r, f64 c) {
        edges.push_back({u, v, r, c});
    }

    bool run(int st, f64 initval) {
        // 从S出发可以达到的位置
        fill(dist.begin(), dist.end(), -dinf);
        dist[st] = initval;
        for (int i = 1; i < n; ++i) {
            bool updated = false;
            for (const auto& edge : edges) {
                auto [u, v, r, c] = edge;
                if (dist[u] > c) {
                    if (dist[v] < (dist[u] - c) * r) {
                        dist[v] = (dist[u] - c) * r;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        for (const auto& edge : edges) {
            auto [u, v, r, c] = edge;
            if (dist[u] > c) {
                if (dist[v] < (dist[u] - c) * r) {
                    return true;
                }
            }
        }
        return false;
    }
};

void solve() {
    int n, m, s;
    f64 iniv;
    cin >> n >> m >> s >> iniv;
    Bellman_Ford bf(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        f64 rab, cab, rba, cba;
        cin >> u >> v >> rab >> cab >> rba >> cba;
        bf.add_edge(u, v, rab, cab);
        bf.add_edge(v, u, rba, cba);
    }
    if (bf.run(s, iniv) || bf.dist[s] > iniv) {
        cout << "YES" << '\n';
        return;
    }
    cout << "NO" << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}