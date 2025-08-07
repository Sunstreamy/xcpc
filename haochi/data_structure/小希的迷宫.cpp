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
struct Dsu {
    vector<int> fa, sz, ed;
    vector<bool> cy;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1), ed(n + 1), cy(n + 1, false) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            ed[fx]++;
            cy[fx] = true;
            return false;
        }
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        ed[fx] += ed[fy];
        ed[fx]++;
        cy[fx] = cy[fx] || cy[fy];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool sc(int x) {
        return cy[find(x)];
    }
    int ecnt(int x) {
        return ed[find(x)];
    }
    int pcnt(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int u, v;
    while (cin >> u >> v && u != -1) {
        if (u == 0 && v == 0) {
            cout << "Yes" << '\n';
            continue;
        }
        set<int> nodes;
        vector<pair<int, int>> edges;
        edges.push_back({u, v});
        nodes.insert(u), nodes.insert(v);
        while (cin >> u >> v && u != 0) {
            nodes.insert(u), nodes.insert(v);
            edges.push_back({u, v});
        }
        int mxid = *nodes.rbegin();
        Dsu dt(mxid);
        for (const auto& edge : edges) {
            dt.mg(edge.first, edge.second);
        }

        // --- 最终判断：直接向 DSU 查询最终结果 ---
        int tnode = *nodes.begin();

        // 条件1: 图连通吗? -> 问 DSU 的 pcnt
        bool is_connected = (dt.pcnt(tnode) == nodes.size());

        // 条件2: 图无环吗? -> 问 DSU 的 sc
        bool is_acyclic = !dt.sc(tnode);

        // 两个条件都满足，才是树
        if (is_connected && is_acyclic) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}