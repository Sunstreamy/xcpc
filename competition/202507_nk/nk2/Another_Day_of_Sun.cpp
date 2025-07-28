#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pii;
typedef vector<long long> vi;
typedef vector<vector<long long>> vii;
typedef vector<string> vs;
typedef bitset<20> b20;
const int MOD = 998244353;
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
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vii dp_ways(n, vi(2, 0)); // dp_ways[0][val] = “有多少种方法可以填补 a[0]，使得 a[0] 的最终值是 val？”

    vii dp_sum(n, vi(2, 0));

    if (a[0] == 0 || a[0] == -1)
    {
        dp_ways[0][0] = 1;
        dp_sum[0][0] = 0;
    }
    if (a[0] == 1 || a[0] == -1)
    {
        dp_ways[0][1] = 1;
        dp_sum[0][1] = 1;
    }
    for (int i = 1; i < n; i++)
    {
        if (a[i] == 0 || a[i] == -1)
        {
            dp_ways[i][0] = (dp_ways[i - 1][0] + dp_ways[i - 1][1]) % MOD;
            dp_sum[i][0] = (dp_sum[i - 1][0] + dp_sum[i - 1][1]) % MOD;
        }
        if (a[i] == 1 || a[i] == -1)
        {
            dp_ways[i][1] = (dp_ways[i - 1][0] + dp_ways[i - 1][1]) % MOD;

            // 天数和的计算：
            // 1. 从 a[i-1]=0 转移 (0 -> 1):
            //    天数会增加。对于 dp_ways[i-1][0] 种方案中的每一种，天数都+1。
            //    所以总天数增加量为 dp_ways[i-1][0]。
            int s0 = (dp_sum[i - 1][0] + dp_ways[i - 1][0]) % MOD;

            int s1 = dp_sum[i - 1][1];

            dp_sum[i][1] = (s0 + s1) % MOD;
        }
    }
    int ans = (dp_sum[n - 1][0] + dp_sum[n - 1][1]) % MOD;
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--)
    {
        solve();
    }

    return 0;
}
