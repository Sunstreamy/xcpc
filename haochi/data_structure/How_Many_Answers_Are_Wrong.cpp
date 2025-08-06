//带权并查集
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
    vector<int> fa, sz, dis;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1), dis(n + 1, 0) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (x != fa[x]) {
            int ff = fa[x];
            fa[x] = find(fa[x]);
            dis[x] += dis[ff];
        }
        return fa[x];
    }
    bool mg(int x, int y, int s) {
        int fx = find(x), fy = find(y);
        if (fx == fy) return false;
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
            swap(x, y);
            s = -s;
        }

        fa[fy] = fx;
        // 为什么永远是更新 dis[fy]？
        // 因为 fy 是那个刚刚拥有了新父亲的节点！
        dis[fy] = dis[x] - dis[y] + s;

        return true;
    }
};

void solve() {
    int n, m;
    while (cin >> n >> m) {
        Dsu dt(n);
        int ans = 0;
        for (int i = 0; i < m; i++) {
            int x, y, s;
            cin >> x >> y >> s;
            --x;
            if (!dt.mg(x, y, s)) {
                if (dt.dis[y] - dt.dis[x] != s) {
                    ans++;
                }
            }
        }
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}