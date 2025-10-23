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
constexpr int Maxn = 1510;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

int n;
vector<vector<int>> adj;
int dp[Maxn][2];

void dfs(int u, int p) {
    dp[u][1] = 1;
    dp[u][0] = 0;

    for (int v : adj[u]) {
        if (v == p) {
            continue;
        }
        dfs(v, u);
        // 如果在当前点放置，那么儿子放不放都行，只要价值最小的就ok
        dp[u][1] += min(dp[v][0], dp[v][1]);
        // 如果当前点不放，那么需要覆盖这条u-v边，必须放
        dp[u][0] += dp[v][1];
    }
}

void solve() {
    adj.assign(n, vector<int>());
    for (int i = 0; i < n; ++i) {
        int u, k, v;
        scanf("%d:(%d) ", &u, &k);
        while (k--) {
            scanf("%d", &v);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }

    dfs(0, -1);
    int ans = min(dp[0][0], dp[0][1]);
    printf("%d\n", ans);
    return;
}

int main() {
    while (scanf("%d", &n) != EOF) solve();

    return 0;
}