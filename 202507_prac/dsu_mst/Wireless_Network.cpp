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
    vector<int> fa, sz;
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
    bool same(int x, int y) {
        return find(x) == find(y);
    }
};

void solve() {
    int n, d;
    cin >> n >> d;
    vector<pair<int, int>> pos(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> pos[i].first >> pos[i].second;
    }
    Dsu dt(n);
    vector<bool> repa(n + 1, false);
    char op;
    while (cin >> op) {
        if (op == 'O') {
            int p;
            cin >> p;
            repa[p] = true;

            for (int i = 1; i <= n; ++i) {
                if (i != p && repa[i] == true) {
                    i64 dx = (i64)pos[p].first - pos[i].first;
                    i64 dy = (i64)pos[p].second - pos[i].second;
                    i64 dis = dx * dx + dy * dy;
                    if (dis <= (i64)d * d) {
                        dt.mg(i, p);
                    }
                }
            }
        } else if (op == 'S') {
            int p, q;
            cin >> p >> q;
            if (dt.same(p, q)) {
                cout << "SUCCESS" << '\n';
            } else
                cout << "FAIL" << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}