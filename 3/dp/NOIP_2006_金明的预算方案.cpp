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
struct Item {
    int v, p;
};

void solve() {
    int n, m;
    cin >> n >> m;

    vector<Item> mainItems(m + 1, {0, 0});
    vector<vector<Item>> attachmentsItems(m + 1);
    for (int i = 1; i <= m; ++i) {
        int v, p, q;
        cin >> v >> p >> q;
        if (q == 0) {
            mainItems[i] = {v, p};
        } else {
            attachmentsItems[q].push_back({v, p});
        }
    }

    vector<i64> f(n + 1, 0);

    for (int i = 1; i <= m; ++i) {
        if (mainItems[i].v == 0) {
            continue;
        }

        vector<int> costs;
        vector<i64> values;

        // 1.only main
        int curMainPrice = mainItems[i].v;
        i64 curMainValue = (i64)mainItems[i].v * mainItems[i].p;
        costs.push_back(curMainPrice);
        values.push_back(curMainValue);

        if (!attachmentsItems[i].empty()) {
            int attachment1Price = attachmentsItems[i][0].v;
            i64 attachment1Value = (i64)attachmentsItems[i][0].v * attachmentsItems[i][0].p;

            // 2.main+att1
            costs.push_back(curMainPrice + attachment1Price);
            values.push_back(curMainValue + attachment1Value);
        }
        if (attachmentsItems[i].size() >= 2) {
            int attachment2Price = attachmentsItems[i][1].v;
            i64 attachment2Value = (i64)attachmentsItems[i][1].v * attachmentsItems[i][1].p;

            // 3.main+att2

            costs.push_back(curMainPrice + attachment2Price);
            values.push_back(curMainValue + attachment2Value);

            // 4.main+att1+att2

            int attachment1Price = attachmentsItems[i][0].v;
            i64 attachment1Value = (i64)attachmentsItems[i][0].v * attachmentsItems[i][0].p;

            costs.push_back(curMainPrice + attachment1Price + attachment2Price);
            values.push_back(curMainValue + attachment1Value+ attachment2Value);
        }

        for (int j = n; j >= 0; --j) {
            for (size_t k = 0; k < costs.size(); ++k) {
                if (j >= costs[k]) {
                    f[j] = max(f[j], f[j - costs[k]] + values[k]);
                }
            }
        }
    }
    cout << f[n] << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}