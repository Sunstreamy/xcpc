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
    vector<vector<int>> mx;

    ST(int size) : n(size), k(size > 0 ? __lg(size) : 0) {
        mx.resize(k + 1, vector<int>(n + 1));
    }

    void init(const vector<int>& arr) {
        for (int i = 1; i <= n; ++i) {
            mx[0][i] = arr[i];
        }
        // 从小区间结果推导出大区间结果
        for (int i = 0; i < k; ++i) {  // i 是当前区间的幂指数
            int t = (1 << i);          // t = 2^i
            // j 是区间的起点
            for (int j = 1; j + (t << 1) - 1 <= n; ++j) {
                mx[i + 1][j] = max(mx[i][j], mx[i][j + t]);
            }
        }
    }

    int getMax(int l, int r) {
        if (l > r) {
            return 0;
        }
        int lenLog = __lg(r - l + 1);
        return max(mx[lenLog][l], mx[lenLog][r - (1 << lenLog) + 1]);
    }
};
void solve() {
    int n, q;
    while (cin >> n >> q) {
        vector<int> arr(n + 1);
        for (int i = 1; i <= n; ++i) {
            cin >> arr[i];
        }

        vector<int> cnt(1);
        vector<int> id(n + 1);
        vector<int> blockFirst(1);
        vector<int> blockLast(1);

        int curId = 0;
        for (int i = 1; i <= n; ++i) {
            if (i == 1 || arr[i] != arr[i - 1]) {
                curId++;
                cnt.push_back(1);
                blockFirst.push_back(i);
                if (curId > 1) {
                    blockLast.push_back(i - 1);
                }
            } else {
                cnt.back()++;
            }
            id[i] = curId;
        }
        blockLast.push_back(n);

        ST st(curId);
        st.init(cnt);

        while (q--) {
            int l, r;
            cin >> l >> r;
            int blockL = id[l];
            int blockR = id[r];

            if (blockL == blockR) {
                cout << r - l + 1 << '\n';
            } else {
                int ans1 = blockLast[blockL] - l + 1;
                int ans2 = r - blockFirst[blockR] + 1;
                int ans3 = st.getMax(blockL + 1, blockR - 1);
                cout << max({ans1, ans2, ans3}) << '\n';
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();

    return 0;
}