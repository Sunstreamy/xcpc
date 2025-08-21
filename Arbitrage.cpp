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
    vector<tuple<int, int, f64>> edges;
    vector<f64> dist;

    Bellman_Ford(int n_) : n(n_), dist(n_ + 1) {};
    void ad(int u, int v, f64 r) {
        edges.push_back({u, v, r});
    }
    bool run() {
        // 图中任意位置(可能存在多个联通区域,如果从某个起点开始找，可能会漏掉答案)
        fill(dist.begin(), dist.end(), 1.0);
        dist[1] = 1.0;
        for (int i = 1; i < n; ++i) {
            bool upd = false;
            for (const auto& edge : edges) {
                auto [u, v, r] = edge;
                if (dist[v] < dist[u] * r) {
                    dist[v] = dist[u] * r;
                    upd = true;
                }
            }
            if (!upd) break;
        }

        for (const auto& edge : edges) {
            auto [u, v, r] = edge;
            if (dist[v] < dist[u] * r) {
                return true;
            }
        }
        return false;
    }
};

void solve() {
    int n;
    int cnt = 1;
    while (cin >> n && n != 0) {
        map<string, int> id;
        for (int i = 1; i <= n; ++i) {
            string str;
            cin >> str;
            id[str] = i;
        }
        Bellman_Ford bf(n);
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            string u, v;
            f64 r;
            cin >> u >> r >> v;
            bf.ad(id[u], id[v], r);
        }
        cout << "Case " << cnt << ": ";
        if (bf.run()) {
            cout << "Yes" << '\n';
        } else
            cout << "No" << '\n';
        cnt++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}