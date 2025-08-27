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
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fll;
constexpr f64 dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int mod[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    int n;
    cin >> n;
    vector<int> L(n + 1);
    vector<int> all(n);
    iota(all.begin(), all.end(), 1);

    for (int i = 1; i <= n; ++i) {
        cout << "? " << i << " " << n;
        for (int node : all) {
            cout << " " << node;
        }
        cout << endl;
        cin >> L[i];
    }

    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    sort(p.begin(), p.end(), [&](int a, int b) { return L[a] > L[b]; });

    vector<int> path;
    path.push_back(p[0]);
    vector<bool> vis(n + 1, false);

    vis[p[0]] = true;

    int mxlen = L[p[0]];
    while (path.size() < mxlen) {
        int cur = path.back();
        for (int cand : p) {
            if (vis[cand]) {
                continue;
            }

            if (L[cand] != L[cur] - 1) {
                continue;
            }
            vector<int> qnodes = path;
            qnodes.push_back(cand);
            cout << "? " << cur << " " << qnodes.size();
            for (int node : qnodes) {
                cout << " " << node;
            }
            cout << endl;
            int qres;
            cin >> qres;
            if (qres > 1) {
                path.push_back(cand);
                vis[cand] = true;
                break;
            }
        }
    }

    cout << "! " << path.size();
    for (int node : path) {
        cout << " " << node;
    }
    cout << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}