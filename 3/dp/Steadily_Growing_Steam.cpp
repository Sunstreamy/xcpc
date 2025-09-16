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
constexpr int OFFSET = 2600;

struct Card {
    int v, t;
};
void solve() {
    int n, k;
    cin >> n >> k;

    vector<Card> cards(n);
    for (int i = 0; i < n; ++i) {
        cin >> cards[i].v >> cards[i].t;
    }

    vector<vector<i64>> f(k + 1, vector<i64>(5210, -linf));

    f[0][OFFSET] = 0;
    for (int i = 0; i < n; ++i) {
        int curv = cards[i].v;
        int curt = cards[i].t;

        vector<vector<i64>> tmp = f;

        for (int j = 0; j <= k; ++j) {
            for (int d_idx = 0; d_idx < 5210; ++d_idx) {
                if (f[j][d_idx] == -linf) {
                    continue;
                }

                i64 cur_val = f[j][d_idx];
                int diff = d_idx - OFFSET;

                // 不加倍放入S
                int ds = diff + curt;

                if (abs(ds) <= OFFSET) {
                    tmp[j][ds + OFFSET] = max(tmp[j][ds + OFFSET], cur_val + curv);
                }

                // 不加倍放入T

                int dt = diff - curt;
                if (abs(dt) <= OFFSET) {
                    tmp[j][dt + OFFSET] = max(tmp[j][dt + OFFSET], cur_val + curv);
                }

                // 加倍放入S
                if (j < k) {
                    int dss = diff + 2 * curt;
                    if (abs(dss) <= OFFSET) {
                        tmp[j + 1][dss + OFFSET] = max(tmp[j + 1][dss + OFFSET], cur_val + curv);
                    }
                    // 加倍放入T
                    int dtt = diff - 2 * curt;
                    if (abs(dtt) <= OFFSET) {
                        tmp[j + 1][dtt + OFFSET] = max(tmp[j + 1][dtt + OFFSET], cur_val + curv);
                    }
                }
            }
        }
        f = tmp;
    }

    i64 ans = 0;

    for (int j = 0; j <= k; ++j) {
        if (f[j][OFFSET] != -linf) {
            ans = max(ans, f[j][OFFSET]);
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