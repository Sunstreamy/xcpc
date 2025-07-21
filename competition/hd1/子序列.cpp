#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vii;
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

// 封装离散化：返回排好序且唯一的元素数组（不含哨兵）
// 注意 a 的下标从 1 到 n 有效
vi discretize(const vi &a)
{
    vi b(a.begin() + 1, a.end());
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    return b;
}

// 通用树状数组（用于求前缀和），支持单点更新与前缀查询，索引从 1 开始
struct fwt
{
    int n;
    vi tree;
    fwt(int n) : n(n), tree(n + 1, 0) {}
    void update(int idx, int delta)
    {
        for (; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }
    int query(int idx)
    {
        int sum = 0;
        for (; idx; idx -= idx & -idx)
            sum += tree[idx];
        return sum;
    }
};

// 这里实现一个针对“找伙伴”的 BIT，用于维护最大值查询。
// 由于我们需要查询区间 [a[i], m] 的最大下标，我们采用反转离散化后的下标，即使用 pos = m - a[i] + 1。

// BIT_max 的通用实现：支持单点更新取最大值和前缀最大值查询，下标从1开始
struct BIT_max
{
    int n;
    vector<int> tree;
    BIT_max(int n) : n(n), tree(n + 1, 0) {}
    void update(int idx, int val)
    {
        for (; idx <= n; idx += idx & -idx)
            tree[idx] = max(tree[idx], val);
    }
    int query(int idx)
    {
        int res = 0;
        for (; idx; idx -= idx & -idx)
            res = max(res, tree[idx]);
        return res;
    }
};

// 过程函数：对给定数组 a（下标 1..n, 离散化后取值在 [1, m]）
// 计算每个 i 的 partner、统计 BIT1 得到 second[i] 与 BIT2 离线得到 first[i]，最后返回 max{2 + (first[i] - second[i])}.
// 若没有 partner 则不构成答案。
int process(const vi &a, int n, int m)
{
    vector<int> partner(n + 1, 0);
    // 利用 BIT_max（建立在反向下标上）求 partner
    BIT_max bitmax(m);
    // 注意：遍历顺序从 n 到 1，这样 BIT_max 中只含 j > i 的信息
    for (int i = n; i >= 1; i--)
    {
        int pos = m - a[i] + 1;    // 转换下标
        int p = bitmax.query(pos); // 查询在值区间 [a[i], 最大] 对应反向区间 [1, m - a[i] + 1]
        partner[i] = p;
        bitmax.update(pos, i);
    }

    // BIT1：从左向右扫描，统计 second[i] = |{ k ≤ i, a[k] < a[i] }|
    vector<int> second(n + 1, 0);
    {
        fwt bit(m);
        for (int i = 1; i <= n; i++)
        {
            second[i] = bit.query(a[i] - 1);
            bit.update(a[i], 1);
        }
    }

    // BIT2 离线回答查询：对每个 i，如果存在 partner[i]（即 partner[i] > i），
    // 查询 first[i] = |{ k < partner[i], a[k] < a[i] }|
    vector<int> first(n + 1, 0);
    // 收集所有查询，每个查询为 (r, a_val, idx) 代表查询区间 [1, r]，条件 a < a_val
    vector<tuple<int, int, int>> queries;
    for (int i = 1; i <= n; i++)
    {
        if (partner[i] > i)
            queries.push_back({partner[i] - 1, a[i], i});
    }
    sort(queries.begin(), queries.end(), [](auto &x, auto &y)
         { return get<0>(x) < get<0>(y); });
    fwt bit2(m);
    int cur = 1;
    for (auto &q : queries)
    {
        int r, a_val, idx;
        tie(r, a_val, idx) = q;
        while (cur <= r)
        {
            bit2.update(a[cur], 1);
            cur++;
        }
        first[idx] = bit2.query(a_val - 1);
    }

    int ret = 0;
    for (int i = 1; i <= n; i++)
    {
        if (partner[i] > i)
        {
            ret = max(ret, 2 + (first[i] - second[i]));
        }
    }
    return ret;
}

// solve 函数：同时处理两种子问题：A[i] <= A[j] 与 A[i] > A[j]（后者通过翻转数组实现）
inline void solve()
{
    int n;
    rd(n);
    vi a(n + 1);
    for (int i = 1; i <= n; i++)
        rd(a[i]);

    // 离散化
    vi b = discretize(a);
    int m = b.size();
    // 把 a[i] 变为离散化后的编号（从 1 开始）
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }

    // 处理子问题 1：A[i] <= A[j]
    int candidate1 = process(a, n, m);

    // 处理子问题 2：A[i] > A[j] => 翻转数组再处理
    vi a_rev(n + 1);
    for (int i = 1; i <= n; i++)
    {
        a_rev[i] = a[n - i + 1];
    }
    int candidate2 = process(a_rev, n, m);

    int ans = max(candidate1, candidate2);
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
