#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    int n, m;
    cin >> n >> m;

    vector<int> deg(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        deg[u]++, deg[v]++;
    }

    vector<int> odds;
    for (int i = 1; i <= n; ++i) {
        if (deg[i] & 1) {
            odds.push_back(i);
        }
    }
    int k = odds.size() / 2;
    cout << k << '\n';
    for (int i = 0; i < odds.size(); i += 2) {
        cout << odds[i] << " " << odds[i + 1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}