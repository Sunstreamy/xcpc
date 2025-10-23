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
constexpr int Maxn = 10005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

int dp[Maxn][3];
// 0 u放; 1 u不放，子节点放; 2 u不放，父节点放
vector<vector<int>> adj;

void dfs(int u, int p) {
    dp[u][0] = 1;
    dp[u][1] = 0;
    dp[u][2] = 0;

    int extra = Inf;
    int s = 0;
    bool isLeaf = true;

    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        isLeaf = false;
        dfs(v, u);
        dp[u][0] += min({dp[v][0], dp[v][1], dp[v][2]});
        dp[u][1] += min(dp[v][1], dp[v][0]);
        // 为了让总数最小，我们先假设所有子节点 v 都选择 min(dp[v][0], dp[v][1])这种更优的方式。
        // 然后，我们必须强制其中一个子节点 v
        // 必须选择dp[v][0]（如果它之前没选的话）。我们选择那个“额外代价”最小的子节点来做这件事。
        extra = min(extra, dp[v][0] - min(dp[v][0], dp[v][1]));
        s += min(dp[v][0], dp[v][1]);
    }
    if (isLeaf) {
        dp[u][1] = Inf;
    } else {
        dp[u][1] += extra;
    }
    dp[u][2] += s;
}

void solve() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << '\n';
        return;
    }
    adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1, -1);
    int ans = min(dp[1][0], dp[1][1]);
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}