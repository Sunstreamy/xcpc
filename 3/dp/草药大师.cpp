#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    int n;
    i64 S;
    cin >> n >> S;
    map<i64, i64> f;
    f[0] = 0;
    for (int i = 0; i < n; ++i) {
        i64 t, v;
        cin >> t >> v;

        vector<pair<i64, i64>> newStates;
        for (auto const& [curVal, curTime] : f) {
            i64 nextTime = curTime + t;
            if (nextTime <= S) {
                i64 nextVal = curVal + v;
                newStates.push_back({nextVal, nextTime});
            }
        }

        for (auto const& [nextVal, nextTime] : newStates) {
            auto it = f.find(nextVal);
            // 如果这个价值是第一次达到，或者我们找到了一个更省时的方法来达到这个价值
            if (it == f.end() || nextTime < it->second) {
                f[nextVal] = nextTime;
            }
        }
    }

    // 遍历完所有草药后，dp中所有键都是在S时间内可以获得的总价值
    // 我们需要找到其中最大的一个。
    // 由于std::map按键自动排序，最后一个元素的键就是最大价值。
    i64 ans = 0;
    ans = f.rbegin()->first;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}