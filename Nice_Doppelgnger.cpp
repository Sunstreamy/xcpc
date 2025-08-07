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

// prime: 存储找到的所有质数
// minp[i]: 存储数字 i 的最小质因子
// maxp[i]: 存储数字 i 的最大质因子
vector<int> prime, minp, maxp;

/**
 * @brief 线性筛 (欧拉筛)
 * @param n 筛选的上限，默认为 10^7
 * @note  该函数用于预处理 1 到 n 范围内所有数的最小和最大质因子。
 *        时间复杂度为 O(n)。
 */
void sieve(int n = 1e7) {
    minp.resize(n + 1);
    maxp.resize(n + 1);

    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = maxp[i] = i;
            prime.push_back(i);
        }

        // 遍历已找到的质数列表，用来筛掉合数
        // `j` 在这里代表质数 `p`
        for (auto j : prime) {
            // 如果 i*j 会超出范围, 那么后续的质数更大, 更会超范围, 直接退出
            if ((i64)i * j > n) break;
            // 标记合数 i*j:
            // 因为 j 是从小到大遍历的, 且 j <= minp[i], 所以 j 一定是 i*j 的最小质因子
            minp[i * j] = j;

            // 计算 i*j 的最大质因子:
            // 因为 j <= minp[i], i 的所有质因子都大于等于 j。
            // 所以 i*j 的最大质因子和 i 的最大质因子是相同的。
            // 例如: i=10(2*5), j=2. i*j=20(2*2*5). maxp(10)=5, maxp(20)=5.
            maxp[i * j] = maxp[i];

            // 线性筛的核心: 保证每个合数只被其最小质因子筛一次
            // 如果 j 是 i 的最小质因子, 说明我们已经处理完了所有以 j 为最小质因子的 i*j 类型合数。
            // 为了避免重复筛 (比如用 3*6 来筛 18, 而不是用 2*9), 必须在这里停止。
            if (i % j == 0) break;
        }
    }
}

/**
 * @brief 对整数 n 进行质因数分解
 * @param n 需要分解的整数
 * @return  一个 vector, 包含 {质因子, 次数} 的 array 对。
 * @note    时间复杂度为 O(log n)。
 */
vector<array<int, 2>> factorize(int n) {
    vector<array<int, 2>> ans;
    // 循环直到 n 被分解为 1
    while (n > 1) {
        // 获取 n 当前的最小质因子
        int now = minp[n];
        int cnt = 0;  // 用于计算该质因子的出现次数

        // 不断从 n 中除去这个最小质因子, 并计数
        while (n > 1 && n % now == 0) {  // n>1 的检查是可选的, 但更稳健
            n /= now;
            cnt++;
        }
        // 将 {质因子, 次数} 这个数对存入结果
        ans.push_back({now, cnt});
    }
    return ans;
}

// 这是一个使用示例, 计算一个数总质因子个数
int getTotalPrimeFactors(int n) {
    auto factors = factorize(n);
    int total_count = 0;
    for (const auto& pair : factors) {
        // pair[0] 是质因子, pair[1] 是次数
        total_count += pair[1];
    }
    return total_count;
}

void solve() {
    int n;
    cin >> n;
    vector<int> ans;
    for (int i = 2; i <= n; ++i) {
        int t = getTotalPrimeFactors(i);
        if (t & 1)
            ans.push_back(i);
        else
            continue;
    }
    for (int i = 0; i < (n >> 1); ++i) {
        cout << ans[i] << ' ';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    sieve();
    int _;
    cin >> _;
    while (_--) solve();
    return 0;
}