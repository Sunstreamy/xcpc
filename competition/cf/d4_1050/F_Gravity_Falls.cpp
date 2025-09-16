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
    vector<vector<int>> a;

    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        vector<int> cur(k);
        for (int j = 0; j < k; ++j) {
            cin >> cur[j];
        }
        a.push_back(cur);
    }

    vector<int> res;
    while (!a.empty()) {
        vector<int> best = a[0];
        for (auto& t : a) {
            if (t < best) {
                best = t;
            }
        }

        for (int x : best) {
            res.push_back(x);
        }
        vector<vector<int>> nxt;
        for (auto& t : a) {
            vector<int> rem;
            for (int i = best.size(); i < t.size(); ++i) {
                rem.push_back(t[i]);
            }
            if (!rem.empty()) {
                nxt.push_back(rem);
            }
        }
        a = nxt;
    }
    for (int x : res) {
        cout << x << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}