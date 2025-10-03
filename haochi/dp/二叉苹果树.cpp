#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
int n, q;
vector<vector<pair<int, int>>> adj, tree;
vector<vector<int>> dp;
vector<int> sz;
void build(int u, int p) {
    for (auto &edge : adj[u]) {
        int v = edge.first;
        int w = edge.second;
        if (v == p) {
            continue;
        }
        tree[u].push_back({v, w});
        build(v, u);
    }
}

void dfs(int u) {
    for (auto &edge : tree[u]) {
        int v = edge.first;
        int w = edge.second;

        dfs(v);

        for (int i = sz[u]; i >= 0; --i) {
            for (int k = sz[v]; k >= 0; --k) {
                if (1 + i + k <= q) {
                    dp[u][i + k + 1] = max(dp[u][i + k + 1], dp[u][i] + dp[v][k] + w);
                }
            }
        }
        sz[u] += sz[v] + 1;
    }
}

void solve() {
    cin >> n >> q;
    adj.resize(n + 1);
    tree.resize(n + 1);
    sz.resize(n + 1);
    dp.assign(n + 1, vector<int>(q + 1, 0));
    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    build(1, 0);
    dfs(1);
    cout << dp[1][q] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}