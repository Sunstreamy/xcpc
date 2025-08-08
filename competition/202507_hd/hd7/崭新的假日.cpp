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
constexpr int mxyear = 2100;
int jan11[mxyear + 10];
bool ok(int y) {
    return ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0);
}
void pre() {
    jan11[2025] = 2;  // 周三

    for (int y = 2025; y <= 2075; ++y) {
        int dd = ok(y) ? 366 : 365;
        jan11[y + 1] = (jan11[y] + dd) % 7;
    }
}

void solve() {
    int k, l, r;
    cin >> k >> l >> r;

    vector<i64> costs(367, 0);

    for (int y = l; y <= r; ++y) {
        int st = jan11[y];
        bool flag = ok(y);

        for (int d = 1; d <= 59; ++d) {
            int cur = (st + d - 1) % 7;
            if (cur < 5) {
                costs[d]++;
            }
        }

        if (flag) {
            int d = 60;
            int cur = (st + d - 1) % 7;
            if (cur < 5) {
                costs[d]++;
            }
        }

        for (int d = 61; d <= 366; ++d) {
            int dd = flag ? d : (d - 1);

            int cur = (st + dd - 1) % 7;
            if (cur < 5) {
                costs[d]++;
            }
        }
    }

    sort(costs.begin() + 1, costs.end());
    i64 ans = 0;
    for (int i = 1; i <= k; ++i) {
        ans += costs[i];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    pre();
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}