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
    char type;
    int qpo;
    int u, v;
};

struct Edge {
    int u, v;
};

struct Dsu {
    vector<int> p, fa, sz, mx_node;

    Dsu(int n) : mx_node(n + 1), fa(n + 1), sz(n + 1, 1), p(n + 1) {
        iota(fa.begin(), fa.end(), 0);
        iota(mx_node.begin(), mx_node.end(), 0);
    }
    int find(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    void mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return;
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        mx_node[fx] = better(mx_node[fx], mx_node[fy]);
    }
    int better(int x, int y) {
        if (p[x] > p[y]) return x;
        if (p[x] < p[y]) return y;
        return min(x, y);
    }
};

void solve() {
    int n;
    while (cin >> n) {
        int m, qnum;
        Dsu dt(n);
        map<pair<int, int>, int> edge_id;
        vector<Edge> edges;
        vector<Opt> qq;
        vector<bool> ddegs;
        vector<int> ans;

        for (int i = 0; i < n; ++i) {
            cin >> dt.p[i];
        }

        cin >> m;
        edges.resize(m);
        for (int i = 0; i < m; ++i) {
            cin >> edges[i].u >> edges[i].v;
            if (edges[i].v > edges[i].u) swap(edges[i].u, edges[i].v);
            edge_id[{edges[i].u, edges[i].v}] = i;
        }
        cin >> qnum;
        qq.resize(qnum);
        ddegs.assign(m, false);
        for (int i = 0; i < qnum; ++i) {
            string str;
            cin >> str;
            if (str == "query") {
                cin >> qq[i].qpo;
                qq[i].type = 'q';
            } else {
                cin >> qq[i].u >> qq[i].v;
                if (qq[i].u < qq[i].v) swap(qq[i].u, qq[i].v);
                qq[i].type = 'd';
                ddegs[edge_id[{qq[i].u, qq[i].v}]] = true;
            }
        }
        for (int i = 0; i < m; ++i) {
            if (!ddegs[i]) {
                dt.mg(edges[i].u, edges[i].v);
            }
        }
        for (int i = qnum - 1; i >= 0; --i) {
            if (qq[i].type == 'q') {
                // 看目前时光倒流这个行星找比他强大的只能找到他自己
                int king = dt.mx_node[dt.find(qq[i].qpo)];
                if (qq[i].qpo == king) {
                    ans.push_back(-1);
                } else {
                    ans.push_back(king);
                }
            } else {
                dt.mg(qq[i].u, qq[i].v);
            }
        }
        for (int i = ans.size() - 1; i >= 0; --i) {
            cout << ans[i] << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}