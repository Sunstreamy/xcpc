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
    int n, s, t;
    cin >> n >> s >> t;

    vector<int> p1(n + 1);
    vector<int> p2(2 * n + 1);
    for (int i = 1; i <= n; ++i) {
        int p;
        cin >> p;
        p1[i] = p;
        p2[p] = i;
    }
    if (s == t) {
        cout << "Yes\n";
        return;
    }

    bool s1 = (s <= n);
    bool t1 = (t <= n);

    if (s1 == t1) {
        if (n <= 2) {
            if (s1) {
                if (p1[s] + p1[t] == n + 1 + n + 2) {
                    cout << "No\n";
                    return;
                } else {
                    cout << "Yes\n";
                    return;
                }
            } else {
                if (p2[s] + p2[t] == 3) {
                    cout << "No\n";
                    return;
                } else {
                    cout << "Yes\n";
                    return;
                }
            }
        } else {
            cout << "Yes\n";
            return;
        }
    } else {
        if (s1) {
            if (p1[s] == t) {
                cout << "No\n";
                return;
            } else {
                cout << "Yes\n";
                return;
            }
        } else {
            if (p2[s] == t) {
                cout << "No\n";
                return;
            } else {
                cout << "Yes\n";
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}