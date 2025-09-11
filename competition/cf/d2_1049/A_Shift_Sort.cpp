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
    string s;
    cin >> s;

    int cnt0 = 0;
    for (char c : s) {
        if (c == '0') {
            cnt0++;
        }
    }
    if (cnt0 == 0 || cnt0 == n) {
        cout << 0 << '\n';
        return;
    }

    int ans = 0;
    for (int i = 0; i < cnt0; ++i) {
        if (s[i] == '1') {
            ans++;
        }
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