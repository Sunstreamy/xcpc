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
i64 p10[18];

// 修正后的 calc 函数
i64 calc(i64 n) {
    if (n <= 0) {
        return 0;
    }
    string s = to_string(n);
    int len = s.length();
    i64 ans = 0;

    // 第一部分：计算所有位数小于 len 的数的数字和 (使用迭代和公式)
    for (int i = 1; i < len; ++i) {
        // 计算所有 i 位数的数字和
        // (1到10^i-1的和) - (1到10^(i-1)-1的和)
        i64 sum_up_to_i_digits = i * 45LL * p10[i - 1];
        i64 sum_up_to_i_minus_1_digits = (i > 1) ? (i - 1) * 45LL * p10[i - 2] : 0;
        ans += sum_up_to_i_digits - sum_up_to_i_minus_1_digits;
    }

    // 第二部分：计算所有位数为 len 的数，从 10^(len-1) 到 n 的数字和
    // 这部分你的代码是完全正确的，无需改动
    i64 pre_s = 0;
    for (int i = 0; i < len; ++i) {
        int digit = s[i] - '0';
        int rem_len = len - 1 - i;

        int st_d = (i == 0) ? 1 : 0;
        for (int d = st_d; d < digit; ++d) {
            i64 count = p10[rem_len];
            ans += (pre_s + d) * count;
            if (rem_len > 0) {
                ans += 45LL * rem_len * p10[rem_len - 1]; // 加上 LL 避免溢出是个好习惯
            }
        }
        pre_s += digit;
    }

    // 最后，加上数字 n 本身的数字和
    ans += pre_s;

    return ans;
}

void solve() {
    i64 k;
    cin >> k;

    i64 ans = 0;
    int len = 1;

    while (1) {
        i64 cnt = 9 * p10[len - 1];

        i64 dd = cnt * len;

        if (k > dd) {
            k -= dd;

            i64 st = p10[len - 1];
            i64 ed = p10[len] - 1;
            ans += calc(ed) - calc(st - 1);
            len++;
        } else {
            break;
        }
    }

    i64 st = p10[len - 1];

    i64 full_n = k / len;

    i64 ed = st + full_n - 1;

    if (full_n > 0) {
        ans += calc(ed) - calc(st - 1);
    }

    i64 rem = k % len;
    if (rem > 0) {
        i64 nxt = ed + 1;
        string s = to_string(nxt);
        for (int i = 0; i < rem; ++i) {
            ans += s[i] - '0';
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    p10[0] = 1;
    for (int i = 1; i < 18; ++i) {
        p10[i] = p10[i - 1] * 10;
    }

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}