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
    };
    int find(int x) {
        if (x == fa[x]) return x;
        return fa[x] = find(fa[x]);
    }
    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (sz[fx] < sz[fy]) swap(fx, fy);
        fa[fy] = fx;
        sz[fx] += sz[fy];
        return true;
    }
};
struct Mstk {
    struct Edge {
        int u, v;
        double w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };
    int n;
    vector<Edge> edges;
    Mstk(int n_) : n(n_) {};
    void ad(int u, int v, double w) {
        edges.push_back({u, v, w});
    }
    double run() {
        sort(edges.begin(), edges.end());
        Dsu dt(n);
        double mnw = 0;
        int cnt = 0;
        for (const auto& t : edges) {
            if (dt.mg(t.u, t.v)) {
                mnw += t.w;
                ++cnt;
            }
        }
        return (cnt == n - 1) ? mnw : -1.0;
    }
};
double cal(const int& p1, const int& p2, const int& p3, const int& p4) {
    double dx = p1 - p2;
    double dy = p3 - p4;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> pos;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        pos.push_back({x, y});
    }
    if (n <= 1) {
        cout << fixed << setprecision(1) << 0.0 << '\n';
        return;
    }

    Mstk mst(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double w = cal(pos[i].first, pos[j].first, pos[i].second, pos[j].second);
            if (w >= 10.0 && w <= 1000.0) {
                mst.ad(i, j, w);
            }
        }
    }
    double ans = mst.run();
    if (ans < 0) {
        cout << "oh!" << '\n';
        return;
    }
    cout << fixed << setprecision(1) << 100.0 * ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}