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
    vector<int> fa, sz, spend, val;
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

void solve() {
    int n, m, w;
    cin >> n >> m >> w;
    Dsu dt(n);
    vector<int> costs(n + 1), vals(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> costs[i] >> vals[i];
    }
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        dt.mg(x, y);
    }
    vector<i64> scosts(n + 1, 0), svals(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        // 加到这个森林的根节点
        scosts[dt.find(i)] += costs[i];
        svals[dt.find(i)] += vals[i];
    }
    vector<i64> dp(w + 1);
    for (int i = 1; i <= n; ++i) {
        if (dt.find(i) == i) {
            i64 cc = scosts[i], vv = svals[i];
            for (int j = w; j >= cc; --j) {
                dp[j] = max(dp[j], dp[j - cc] + vv);
            }
        }
    }
    cout << dp[w] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}