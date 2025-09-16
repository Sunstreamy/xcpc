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
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    vector<int> freq(n + 1, 0);
    vector<int> mxfq(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        freq[a[i]]++;
    }
    bool flag = true;

    for (int v = 1; v <= n; ++v) {
        if (freq[v] % k != 0) {
            flag = false;
            break;
        }
        mxfq[v] = freq[v] / k;
    }

    if (!flag) {
        cout << 0 << '\n';
        return;
    }

    i64 ans = 0;

    vector<int> cur(n + 1, 0);

    int l = 0;
    for (int r = 0; r < n; ++r) {
        cur[a[r]]++;
        while (cur[a[r]] > mxfq[a[r]]) {
            cur[a[l]]--;
            l++;
        }
        ans += (r - l + 1);
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