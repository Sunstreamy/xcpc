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
    vector<int> fa, sz, ed;
    vector<bool> cy;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1), ed(n + 1), cy(n + 1, false) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            ed[fx]++;
            cy[fx] = true;
            return false;
        }
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        ed[fx] += ed[fy];
        ed[fx]++;
        cy[fx] = cy[fx] || cy[fy];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool sc(int x) {
        return cy[find(x)];
    }
    int ecnt(int x) {
        return ed[find(x)];
    }
    int pcnt(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    Dsu dt(3 * n);
    int ans = 0;
    for (int i = 1; i <= m; ++i) {
        int d, x, y;
        cin >> d >> x >> y;
        if (x > n || y > n) {
            ans++;
            continue;
        }
        if (d == 1) {
            if (dt.same(x, y + n) || dt.same(x, y + 2 * n)) {
                ans++;
                continue;
            }
            dt.mg(x, y);
            dt.mg(x + n, y + n);
            dt.mg(x + 2 * n, y + 2 * n);
        } else if (d == 2) {
            if (dt.same(x, y) || dt.same(x, y + 2 * n)) {
                ans++;
                continue;
            }
            dt.mg(x, y + n);
            dt.mg(x + 2 * n, y);
            dt.mg(x + n, y + 2 * n);
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}