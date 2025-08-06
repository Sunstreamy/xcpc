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
    int n;
    cin >> n;
    vector<pair<int, int>> pr(n);
    for (int i = 0; i < n; i++) {
        cin >> pr[i].first >> pr[i].second;
    }
    //每次碰到一个不重叠的部分，结算上一个多组拼接结束的答案，最后循环结束再结算最后手上这跟多组拼接的答案
    sort(pr.begin(), pr.end());
    int ans = 0;
    int curl = pr[0].first;
    int curr = pr[0].second;

    for (int i = 1; i < n; i++) {
        int nxl = pr[i].first, nxr = pr[i].second;
        if (nxl <= curr) {
            curr = max(curr, nxr);
        } else {
            ans += curr - curl + 1;
            curl = nxl;
            curr = nxr;
        }
    }
    ans += curr - curl + 1;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}