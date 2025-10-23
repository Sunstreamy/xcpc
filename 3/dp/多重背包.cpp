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
struct Item {
    int w, v;
};

void solve() {
    int n, t;
    cin >> n >> t;

    vector<Item> items;
    for (int i = 0; i < n; ++i) {
        int x, w, v;
        cin >> x >> w >> v;

        for (int j = 0; j < x; ++j) {
            items.push_back({w, v});
        }
    }

    vector<int> f(t + 1, 0);
    for (const auto& tep : items) {
        for (int j = t; j >= tep.w; --j) {
            f[j] = max(f[j], f[j - tep.w] + tep.v);
        }
    }
    cout << f[t] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}