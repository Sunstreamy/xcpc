#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pii;
typedef vector<long long> vi;
typedef vector<vector<long long>> vii;
typedef vector<string> vs;
typedef bitset<20> b20;
const int M = 1e9 + 7;
#define N 200005
#define int long long
inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}

struct fwt
{
    int n;
    // 初始化一个可以容纳 n 个数据（外加一个额外索引）的树状数组
    vi tree;
    fwt(int n) : n(n), tree(n + 1, 0) {}
    // 单点更新：在位置 idx 加上 delta
    void update(int idx, int delta)
    {
        for (; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }
    // 前缀和查询：查询区间 [1, idx] 内的和
    int query(int idx)
    {
        int sum = 0;
        for (; idx; idx -= idx & -idx)
            sum += tree[idx];
        return sum;
    }
    // 二分查找：返回最小的 idx 使得 query(idx) >= target
    int lower_bound(int target)
    {
        int idx = 0;
        // 假设 n 不超过 2*10^5+q总数可能接近 5e5
        // 所以取足够大的最高位（2^20=1048576即可）
        for (int bit = 1 << 20; bit; bit >>= 1)
        {
            int next = idx + bit;
            if (next <= n && tree[next] < target)
            {
                target -= tree[next];
                idx = next;
            }
        }
        return idx + 1;
    }
};

//------------------------------------------------------------------

inline void solve()
{
    int n;
    rd(n);
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++)
    {
        rd(p[i]);
    }
    int ans = 0;
    // 枚举每一个位置 k, 假设 p[k] 是中位数
    for (int k = 1; k <= n; ++k)
    {
        int median_val = p[k];

        // 前缀和：p[k] 是子数组 p[i...j] 的中位数，当且仅当 s[j] - s[i-1] == 0，即 s[j] == s[i-1]。
        //  题目要求子数组长度为奇数，即 j-i+1 为奇数，这等价于 i 和 j 的奇偶性相同。这进一步等价于 i-1 和 j 的奇偶性不同。
        vi s(n + 1, 0);
        for (int i = 1; i <= n; ++i)
        {
            s[i] = s[i - 1];
            if (p[i] > median_val)
            {
                s[i]++;
            }
            else if (p[i] < median_val)
            {
                s[i]--;
            }
        }
        // 2. 准备累加器
        // 前缀和 s[i] 的范围是 [-n, n]。为了用数组下标，我们加上偏移量 n。
        // 数组大小设为 2*n+5 以确保安全。
        int offset = n;
        vi sum_i_even(2 * n + 5, 0); // i-1 为偶数时, i 的和
        vi sum_i_odd(2 * n + 5, 0);  // i-1 为奇数时, i 的和

        vi sum_j_even(2 * n + 5, 0); // j 为偶数时, j 的和
        vi sum_j_odd(2 * n + 5, 0);  // j 为奇数时, j 的和

        // 3. 计算左半部分 (i 的贡献)
        // 遍历所有可能的 i-1 (记为 x), 范围是 [0, k-1]
        // 注意 s[0] = 0, 对应 i=1 的情况
        for (int x = 0; x < k; ++x)
        {
            int s_val_idx = s[x] + offset;
            if (x % 2 == 0)
            {
                sum_i_even[s_val_idx] += (x + 1);
            }
            else
            { 
                sum_i_odd[s_val_idx] += (x + 1);
            }
        }

        // 4. 计算右半部分 (j 的贡献)
        // 遍历所有可能的 j, 范围是 [k, n]
        for (int j = k; j <= n; ++j)
        {
            int s_val_idx = s[j] + offset;
            if (j % 2 == 0)
            { 
                sum_j_even[s_val_idx] += j;
            }
            else
            { 
                sum_j_odd[s_val_idx] += j;
            }
        }

        // 5. 组合计算对答案的贡献
        // 遍历所有可能的前缀和值
        int current_k_contrib = 0;
        for (int s_val = -n; s_val <= n; ++s_val)
        {
            int s_val_idx = s_val + offset;

            // 条件: s[i-1] == s[j] 且 i-1 和 j 的奇偶性不同

            // Case 1: i-1 是偶数, j 是奇数
            current_k_contrib += sum_i_even[s_val_idx] * sum_j_odd[s_val_idx];

            // Case 2: i-1 是奇数, j 是偶数
            current_k_contrib += sum_i_odd[s_val_idx] * sum_j_even[s_val_idx];
        }

        ans += median_val * current_k_contrib;
    }

    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _;
    rd(_);
    while (_--)
    {
        solve();
    }

    return 0;
}
