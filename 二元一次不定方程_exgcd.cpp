#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using db = double;
using ldb = long double;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr db Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
i64 exgcd(i64 a, i64 b, i64& x, i64& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    i64 res = exgcd(b, a % b, y, x);
    y -= a / b * x;
    return res;
}
// C++ 整数除法对于负数的处理方式可能不同，
// 为了确保 floor 和 ceil 的正确性，可以写两个辅助函数
// 计算 floor(num / den)
i64 floor_div(i64 num, i64 den) {
    i64 res = num / den;
    // 如果除不尽且结果为负，需要向更小的整数调整
    if (num % den != 0 && (num > 0) != (den > 0)) {
        res--;
    }
    return res;
}

// 计算 ceil(num / den)
i64 ceil_div(i64 num, i64 den) {
    i64 res = num / den;
    // 如果除不尽且结果为正，需要向更大的整数调整
    if (num % den != 0 && (num > 0) == (den > 0)) {
        res++;
    }
    return res;
}

void solve() {
    i64 a, b, c;
    cin >> a >> b >> c;
    i64 x, y;
    i64 d = exgcd(a, b, x, y);
    if (c % d != 0) {
        cout << -1 << '\n';
        return;
    }
    // 步骤 2: 求解特解和通解参数
    // 注意：x * (c/d) 可能会溢出，但在此题 10^9 的数据范围内，
    // x 最大约为 b(10^9), c/d 最大约为 10^9, 乘积约为 10^18，在 long long 范围内。
    x *= c / d;
    y *= c / d;

    i64 dx = b / d;
    i64 dy = a / d;

    // 步骤 3: 分析 k 的范围以寻找正整数解
    // k >= (1 - x) / dx
    // k <= (y - 1) / dy
    i64 k_min = ceil_div(1 - x, dx);
    i64 k_max = floor_div(y - 1, dy);

    if (k_min <= k_max) {
        // 情况一：有正整数解
        i64 count = k_max - k_min + 1;
        i64 x_min = x + k_min * dx;
        i64 y_min = y - k_max * dy;
        i64 x_max = x + k_max * dx;
        i64 y_max = y - k_min * dy;
        cout << count << " " << x_min << " " << y_min << " " << x_max << " " << y_max << "\n";
        return;
    } else {
        // 情况二：无正整数解
        i64 min_pos_x = ((x - 1) % dx + dx) % dx + 1;
        i64 min_pos_y = ((y - 1) % dy + dy) % dy + 1;
        cout << min_pos_x << " " << min_pos_y << "\n";
        return;
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