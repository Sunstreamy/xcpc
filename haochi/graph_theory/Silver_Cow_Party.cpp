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
struct Fdijkstra {
    int n;
    vector<vector<pair<int, i64>>> adj;
    vector<i64> dist;

    Fdijkstra(int n_) : n(n_), adj(n_ + 1), dist(n_ + 1) {};

    void add_edge(int u, int v, int w) {
        adj[u].push_back({v, w});
    }

    void run(int st) {
        fill(dist.begin(), dist.end(), linf);
        dist[st] = 0;

        using Node = pair<i64, int>;
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0, st});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                auto [v, w] = edge;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }
};

void solve() {
    int n, m, x;
    cin >> n >> m >> x;

    Fdijkstra dij1(n);
    Fdijkstra dij2(n);
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dij1.add_edge(u, v, w);
        dij2.add_edge(v, u, w);
    }
    dij1.run(x);  // 在正向图上跑回家的时间
    dij2.run(x);  // 在反向图上跑去农场的时间

    i64 ans = 0;
    for (int i = 1; i <= n; ++i) {
        i64 cur = dij1.dist[i] + dij2.dist[i];
        if (cur > ans) ans = cur;
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}