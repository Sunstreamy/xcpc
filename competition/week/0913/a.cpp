#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename T>
T myGcd(T a, T b) {
    return b == T(0) ? a : myGcd(b, a % b);
}

template <typename T>
struct ST {
    const int n, k;
    vector<vector<T>> Max, Min, Gcd;

    ST(int size) : n(size), k(size > 0 ? __lg(size) : 0) {
        Max.resize(k + 1, vector<T>(n + 1));
        Min.resize(k + 1, vector<T>(n + 1));
        Gcd.resize(k + 1, vector<T>(n + 1));
    }

    void init(const vector<T>& arr) {
        for (int i = 1; i <= n; ++i) {
            Max[0][i] = arr[i];
            Min[0][i] = arr[i];
            Gcd[0][i] = arr[i];
        }

        for (int i = 0; i < k; ++i) {
            int t = (1 << i);
            for (int j = 1; j + (t << 1) - 1 <= n; ++j) {
                Max[i + 1][j] = max(Max[i][j], Max[i][j + t]);
                Min[i + 1][j] = min(Min[i][j], Min[i][j + t]);
                // 调用模板化的 gcd 函数
                Gcd[i + 1][j] = myGcd(Gcd[i][j], Gcd[i][j + t]);
            }
        }
    }

    // 5. 查询函数的返回值变为 T
    T getMax(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return max(Max[len_log][l], Max[len_log][r - (1 << len_log) + 1]);
    }

    T getMin(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return min(Min[len_log][l], Min[len_log][r - (1 << len_log) + 1]);
    }

    T getGcd(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return myGcd(Gcd[len_log][l], Gcd[len_log][r - (1 << len_log) + 1]);
    }
};

void solve() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }

    ST<int> st(n);
    st.init(a);

    i64 ans = 0;
    //  主循环，遍历每个 a[i]
    for (int i = 1; i <= n; ++i) {
        //  用二分+st_min 查找左边界 L
        // 目标: 在 [1, i] 中找到最靠左的 L, 使得 [L, i-1] 的最小值都 > a[i]
        int L = i;
        int lo = 1, hi = i - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (st.getMin(mid, i - 1) > a[i]) {
                L = mid;  // mid 是一个可能的 L, 尝试向左寻找更好的
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        // 步骤 3.2: 用二分+st_min 查找右边界 R
        // 目标: 在 [i, n] 中找到最靠右的 R, 使得 [i+1, R] 的最小值都 >= a[i]
        // (用 >= 是为了确保 a[i] 是最左边的最小值，避免重复计数)
        int R = i;
        lo = i + 1, hi = n;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (st.getMin(i + 1, mid) >= a[i]) {
                R = mid;  // mid 是一个可能的 R, 尝试向右寻找更好的
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        // 步骤 4.1: 在 [L, i] 范围内, 二分+st_gcd 查找整除的左边界 segL
        int segL = i;
        lo = L, hi = i - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (st.getGcd(mid, i) % a[i] == 0) {
                segL = mid;  // mid 是一个可能的 segL, 尝试更左
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }

        // 步骤 4.2: 在 [i, R] 范围内, 二分+st_gcd 查找整除的右边界 segR
        int segR = i;
        lo = i + 1, hi = R;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (st.getGcd(i, mid) % a[i] == 0) {
                segR = mid;  // mid 是一个可能的 segR, 尝试更右
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }

        // 步骤 5: 计算贡献
        i64 leftChoices = (i64)i - segL + 1;
        i64 rightChoices = (i64)segR - i + 1;
        ans += leftChoices * rightChoices;
    }

    cout << ans << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}