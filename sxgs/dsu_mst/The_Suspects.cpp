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
};

void solve() {
    int n, m;
    while (cin >> n >> m && n != 0) {
        if (m == 0) {
            cout << 1 << '\n';
            continue;
        }
        Dsu dt(n);
        int cnt = 0;
        for (int i = 0; i < m; ++i) {
            int num;
            cin >> num;
            int fi;
            cin >> fi;

            for (int j = 1; j < num; ++j) {
                int t;
                cin >> t;
                dt.mg(fi, t);
            }
        }
        cout << dt.sz[dt.find(0)] << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}