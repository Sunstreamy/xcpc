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
constexpr int Maxn = 6005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
int n;
i64 dp[Maxn][2];
int hi[Maxn];
vector<int> adj[Maxn];
bool hasBoss[Maxn];

void dfs(int u) {
    dp[u][1] = hi[u];
    dp[u][0] = 0;

    for (int xiaodi : adj[u]) {
        // 先递归计算下属的dp值，从下往上更新
        dfs(xiaodi);
        // 小弟去吧
        dp[u][0] += max(dp[xiaodi][0], dp[xiaodi][1]);
        // 小弟都别去了
        dp[u][1] += dp[xiaodi][0];
    }
}

void solve() {
    cin >> n;

    for (int i = 1; i <= n; ++i) {
        cin >> hi[i];
    }
    // if (n == 1) {
    //     cout << hi[1] << '\n';
    //     return;
    // }
    int u, v;
    while (cin >> u >> v && u != 0) {
        adj[v].push_back(u);
        hasBoss[u] = true;
    }
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (!hasBoss[i]) {
            root = i;
            break;
        }
    }
    dfs(root);
    cout << max(dp[root][0], dp[root][1]) << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}