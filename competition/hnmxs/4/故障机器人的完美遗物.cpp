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
void sieve(int n = 1e6 + 5) {
    // 调整数组大小以容纳 0 到 n 的索引
    minp.resize(n + 1);
    maxp.resize(n + 1);

    for (int i = 2; i <= n; i++) {
        // 如果 minp[i] 为 0, 说明 i 没有被前面的数筛掉, 因此 i 是一个质数
        if (!minp[i]) {
            minp[i] = i;         // 质数的最小质因子是它自己
            maxp[i] = i;         // 质数的最大质因子也是它自己
            prime.push_back(i);  // 将这个质数加入质数列表
        }

        // 遍历已找到的质数列表，用来筛掉合数
        // `j` 在这里代表质数 `p`
        for (auto j : prime) {
            // 优化1: 如果当前质数 j 已经大于 i 的最小质因子,
            // 那么 i*j 的最小质因子就不是 j, 而是 minp[i]。
            // 为了保证“每个合数只被其最小质因子筛一次”的原则, 必须在此停止。
            // (但在当前代码结构下, 这个判断其实可以被 i%j==0 的判断覆盖,
            // 很多模板会省略此处的 j > minp[i])
            // 优化2: 如果 i*j 会超出范围, 那么后续的质数更大, 更会超范围, 直接退出
            if (j > minp[i] || j > n / i) break;

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
inline bool ok(int x) {
    if (x < 2) return false;
    return minp[x] == x;
}

i64 qpow(i64 n, i64 k) {
    i64 ans = 1;

    while (k) {
        if (k & 1) {
            ans = ans * n;
        }
        n = n * n;
        k >>= 1;
    }
    return ans;
}
void solve() {
    int n;
    cin >> n;
    i64 ans = 0;
    for (int i = 0; i < n; ++i) {
        i64 a;
        cin >> a;
        if (a == 1) {
            continue;
        }

        for (int k = 50; k >= 2; --k) {
            if (!ok(k + 1) || (k + 1 == 2)) {
                continue;
            }

            i64 b = round(powl(a, 1.0L / k));
            if (b <= 1) continue;

            if (qpow(b, k) == a) {
                if (ok(b)) {
                    ans += a;
                    break;
                }
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    sieve();
    solve();

    return 0;
}