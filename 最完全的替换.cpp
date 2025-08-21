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

void solve() {
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;

    int idx = -1;
    for (int i = 0; i < m; ++i) {
        if (t[i] == '1') {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        if (s.find('1') == string::npos) {
            cout << 0 << '\n';
        } else {
            cout << -1 << '\n';
        }
        return;
    }
    int ans = 0;
    for (int i = 0; i <= n - m; ++i) {
        if (s[i + idx] == '1') {
            ans++;
            for (int j = 0; j < m; ++j) {
                s[i + j] = (((s[i + j] - '0') ^ (t[j] - '0')) + '0');
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') {
            cout << -1 << '\n';
            return;
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