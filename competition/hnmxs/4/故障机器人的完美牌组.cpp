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
    vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (n <= 1) {
        cout << n << '\n';
        if (n == 1) {
            cout << a[0] << '\n';
        }
        return;
    }
    int idx = -1;
    i64 mx = -1;
    for (int i = 1; i < n; ++i) {
        if (a[i] >= mx) {
            mx = a[i];
            idx = i;
        }
    }
    if (mx > 0) {
        cout << n - 1 << '\n';
        cout << a[0] + mx << ' ';
        for (int i = 1; i < n; ++i) {
            if (i != idx) {
                cout << a[i] << ' ';
            }
        }
        cout << '\n';
        return;
    }
    cout << n << '\n';
    for (int i = 0; i < n;++i){
        cout << a[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}