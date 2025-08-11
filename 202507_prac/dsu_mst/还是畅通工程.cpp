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
    vector<int> fa, sz;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }

    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }

    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        return true;
    }
};

struct Mstk {
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };
    int n;
    vector<Edge> edges;
    Mstk(int n_, int m_) : n(n_) {
        edges.reserve(m_);
    }
    void ad(int u, int v, int w) {
        edges.push_back({u, v, w});
    }
    i64 run() {
        sort(edges.begin(), edges.end());
        Dsu dt(n);
        i64 mnw = 0;

        int cnt = 0;
        for (const auto& t : edges) {
            if (dt.mg(t.u, t.v)) {
                mnw += t.w;
                ++cnt;
            }
        }
        return (cnt == n - 1) ? mnw : -1;
    }
};

void solve() {
    int n;
    while (cin >> n && n) {
        Mstk mst(n, n * (n - 1) / 2);
        for (int i = 0; i < n * (n - 1) / 2; ++i) {
            int u, v, w;
            cin >> u >> v >> w;
            mst.ad(u, v, w);
        }
        i64 ans = mst.run();
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}