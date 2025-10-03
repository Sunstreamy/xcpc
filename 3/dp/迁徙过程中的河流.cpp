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
    cin >> n;
    vector<int> time(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> time[i];
    }
    sort(time.begin() + 1, time.end());
    vector<int> f(n + 1, Inf);
    f[1] = time[1];
    f[2] = time[2];
    for (int i = 3; i <= n; ++i) {
        f[i] = min(f[i - 1] + time[1] + time[i], f[i - 2] + time[1] + 2 * time[2] + time[i]);
    }
    cout << f[n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    return 0;
}