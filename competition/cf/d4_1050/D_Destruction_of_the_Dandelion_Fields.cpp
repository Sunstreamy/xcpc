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
    int n;
    cin >> n;
    vector<i64> odds;
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        i64 x;
        cin >> x;
        if (x & 1) {
            odds.push_back(x);
        }
        ans += x; 
    }
    if (odds.empty()) {
        cout << 0 << '\n';
        return;
    }
    sort(odds.begin(), odds.end());
    int num = odds.size() / 2;
    for (int i = 0; i < num; ++i) {
        ans -= odds[i];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}