#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int M = 1e9 + 7;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;

bool ok(int num) {
    // 步骤 1: 处理边界情况。质数是大于1的整数，所以 num <= 1 都不满足。
    if (num <= 1) {
        return false;
    }

    // 步骤 2: 迭代寻找最小的质因数。
    // 循环到 sqrt(num) 即可。如果 num 在 [2, sqrt(num)] 之间没有因数，它本身就是质数。
    for (int i = 2; i * i <= num; ++i) {
        // 如果 i 是 num 的一个因数
        if (num % i == 0) {
            // 步骤 3: 分解这个质因数 i，并计算其指数 k
            int k = 0;  // 指数计数器
            while (num % i == 0) {
                k++;
                num /= i;
            }

            // 除完所有 i 因子后，如果 num 不为 1，说明 num 还有其他质因数。
            // 例如 num = 12 = 2^2 * 3。除完 2 后，num 剩下 3。
            // 此时它不是单个质数的幂，不满足条件。
            if (num != 1) {
                return false;
            }

            // 如果 num 为 1，说明原始数字就是 i^k 的形式。
            // 现在只需要判断指数 k 是否为奇数。
            return (k % 2 != 0);
        }
    }

    // 步骤 4: 如果循环结束都没有找到因数，说明 num 本身就是一个质数。
    // 任何质数 p 都可以写成 p^1 的形式，指数 1 是奇数，满足条件。
    return true;
}

void solve() {
    int n;
    cin >> n;
    vector<int> s, used;
    for (int i = 2; i < n; ++i) {
        if (ok(i)) s.push_back(i);
    }
    for (int i = 0; i < n / 2; i++) {
        cout << s[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}