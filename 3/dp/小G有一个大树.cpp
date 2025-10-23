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

int n;
vector<vector<int>> adj;
vector<int> sz;
// u: 当前节点, p: u的父节点 (防止往回走)
void dfs(int u, int p) {
    sz[u] = 1;

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

void solve() {
    cin >> n;
    adj.assign(n + 1, vector<int>());
    sz.assign(n + 1, 0);

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    int balancedNode = -1;
    int mnSize = Inf;

    for (int u = 1; u <= n; ++u) {
        int curMax = n - sz[u];

        for (int v : adj[u]) {
            if (sz[v] < sz[u]) {
                curMax = max(curMax, sz[v]);
            }
        }
        if (curMax < mnSize) {
            mnSize = curMax;
            balancedNode = u;
        } else if (curMax == mnSize) {
            if (u < balancedNode) {
                balancedNode = u;
            }
        }
    }
    cout << balancedNode << " " << mnSize << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}