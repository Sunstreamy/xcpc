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
struct Prod {
    int pri;
    int ddl;
    bool operator<(const Prod& other) const {
        return pri > other.pri;
    }
};

void solve() {
    int n;
    while (cin >> n) {
        int mxd = 0;
        vector<Prod> items(n);
        for (int i = 0; i < n; ++i) {
            cin >> items[i].pri >> items[i].ddl;
            if (items[i].ddl > mxd) {
                mxd = items[i].ddl;
            }
        }
        sort(items.begin(), items.end());

        Dsu dt(mxd);
        i64 ans = 0;
        for (int i = 0; i < n; ++i) {
            int avad = dt.find(items[i].ddl);
            if (avad > 0) {
                ans += items[i].pri;

                // 相当于你在日程表上把 avad 这一天划掉，并做了一个标记：“avad 日已占用！如果以后再有人想预定
                // avad，请直接让他去查询 avad-1 的情况。”
                dt.mg(avad - 1, avad);
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