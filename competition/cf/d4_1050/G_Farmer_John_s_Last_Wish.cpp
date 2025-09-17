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
vector<int> divisors[maxn];
int cnt[maxn];

void pre(int n) {
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<int> used;
    int g = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = a[i];
        int pre_g = g;
        g = gcd(g, x);

        for (int d : divisors[x]) {
            if (cnt[d] == 0) {
                used.push_back(d);
            }
            cnt[d]++;
        }

        for (int d : divisors[x]) {
            if (d > 1 && g % d != 0) {
                ans = max(ans, cnt[d]);
            }
        }
        if (pre_g != 0) {
            for (int d : divisors[pre_g]) {
                if (d > 1 && g % d != 0) {
                    ans = max(ans, cnt[d]);
                }
            }
        }
        cout << ans << " ";
    }
    cout << '\n';

    for (int d : used) {
        cnt[d] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    pre(maxn - 1);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}