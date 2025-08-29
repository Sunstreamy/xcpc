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
    vector<int> cnt(5001, 0);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        cnt[x]++;
    }
    int ans = 0;

    for (int s = 2; s <= 10000; ++s) {
        int cur = 0;
        for (int i = 1; i <= s / 2; ++i) {
            int j = s - i;
            if (j > 5000) {
                continue;
            }
            if (i < j) {
                cur += min(cnt[i], cnt[j]);
            } else if (i == j) {
                cur += cnt[i] / 2;
            }
            ans = max(ans, cur * 2);
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