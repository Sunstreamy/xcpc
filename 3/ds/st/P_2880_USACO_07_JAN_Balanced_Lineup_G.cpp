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
struct ST {
    const int n, k;
    vector<vector<int>> mx, mn;

    ST(int size) : n(size), k(size > 0 ? __lg(size) : 0) {
        mx.resize(k + 1, vector<int>(n + 1));
        mn.resize(k + 1, vector<int>(n + 1));
    }
    void ini(const vector<int>& arr) {
        for (int i = 1; i <= n; ++i) {
            mx[0][i] = arr[i];
            mn[0][i] = arr[i];
        }
        for (int i = 0; i < k; ++i) {
            int t = (1 << i);
            for (int j = 1; j + (t << 1) - 1 <= n; ++j) {
                mx[i + 1][j] = max(mx[i][j], mx[i][j + t]);
                mn[i + 1][j] = min(mn[i][j], mn[i][j + t]);
            }
        }
    }
    int getMax(int l, int r) {
        int lenLog = __lg(r - l + 1);
        return max(mx[lenLog][l], mx[lenLog][r - (1 << lenLog) + 1]);
    }
    int getMin(int l, int r) {
        int lenLog = __lg(r - l + 1);
        return min(mn[lenLog][l], mn[lenLog][r - (1 << lenLog) + 1]);
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> arr[i];
    }
    ST st(n);
    st.ini(arr);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << st.getMax(l, r) - st.getMin(l, r) << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}