//环形数组的应用https://ac.nowcoder.com/acm/contest/108299/F
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

void solve()
{
    long long n, t;
    std::cin >> n >> t;
    std::string s;
    std::cin >> s;

    // --- 步骤 1: 预处理和环展开 ---

    // 计算初始火源总数
    long long total_fire_count = 0;
    for (char c : s)
    {
        if (c == '1')
        {
            total_fire_count++;
        }
    }

    if (total_fire_count == 0)
    {
        std::cout << n << std::endl;
        return;
    }
    if (total_fire_count == n)
    {
        std::cout << 0 << std::endl;
        return;
    }

    // “环形数组展开”技巧：复制字符串以模拟环形结构，避免取模运算
    s += s;

    // 为每个火源分配一个唯一的、递增的ID，以便追踪
    // 比如第一个火源ID为1，第二个为2...
    std::vector<long long> fire_sequence_id(2 * n, 0);
    long long fire_id_counter = 0;
    for (long long i = 0; i < 2 * n; ++i)
    {
        if (s[i] == '1')
        {
            fire_sequence_id[i] = ++fire_id_counter;
        }
    }

    // --- 步骤 2: 遍历环并初步计算 ---

    long long saved_cells_count = 0;  // 最终答案
    long long current_gap_length = 0; // 当前连续空地的长度
    long long max_gap_length = 0;     // 记录遇到的最长连续空地

    // 找到第一个火源的位置，开始遍历
    for (long long start_pos = 0; start_pos < 2 * n; ++start_pos)
    {
        if (fire_sequence_id[start_pos] == 1)
        {

            // 从第一个火源开始，遍历一整个环
            // 终止条件是再次遇到第一个火源（在展开的字符串中，它的ID是 total_fire_count + 1）
            for (long long j = start_pos; j < 2 * n; ++j)
            {
                if (s[j] == '0')
                {
                    // 如果是空地，增加当前间隙的长度
                    current_gap_length++;
                }
                else
                {
                    // 如果遇到火源，说明一个间隙结束了
                    // 假设：这个间隙两端都有火源，每个火源蔓延t
                    // 幸存的区域 = 间隙长度 - 2*t
                    saved_cells_count += std::max(0LL, current_gap_length - 2 * t);

                    // 重置间隙计数器，为下一个间隙做准备
                    current_gap_length = 0;
                }

                // 持续更新遇到的最长间隙
                max_gap_length = std::max(max_gap_length, current_gap_length);

                //**/ 如果我们已经绕完一圈，就结束循环
                if (fire_sequence_id[j] == total_fire_count + 1)
                {
                    break;
                }
            }
            break; // 找到起点后，外层循环就可以退出了
        }
    }

    // --- 步骤 3: 修正计算结果 ---

    // a. 减去最长间隙被错误计算的部分
    // 我们之前错误地假设最长间隙两端都有火源，幸存者为 max(0, max_gap_length - 2*t)
    saved_cells_count -= std::max(0LL, max_gap_length - 2 * t);

    // b. 加上最长间隙实际的幸存数量
    // 在最长间隙中，我们建立一个防火墙（花费1个区域）。
    // 这样，只有一端的火源会蔓延t个区域。
    // 实际幸存者 = 间隙长度 - 1(防火墙) - t(火灾蔓延)
    saved_cells_count += std::max(0LL, max_gap_length - t - 1);

    std::cout << saved_cells_count << std::endl;
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
