//
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef bitset<20> b20;
const int M = 1e9 + 7;
#define N 200005
#define int long long

// 树状数组（BIT）模板：维护一个区间频率
struct BIT
{
    int n;
    // 初始化一个可以容纳 n 个数据（外加一个额外索引）的树状数组
    vector<int>
        tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
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

vector<int> discretize(vector<int> &all)
{
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    return all;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
    {
        int n, q;
        cin >> n >> q;
        vector<int> arr(n);
        // 读取初始 n 数字
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        // 为离散化构造所有可能出现的数值
        // 由于每次更新是累加，且数字只会增大，
        // 故所有初始值以及更新后的值都可能出现
        vector<int> all;
        // 放入初始数值
        for (int i = 0; i < n; i++)
        {
            all.push_back(arr[i]);
        }

        // 保存 q 次更新数据，以便离散化时加入更新后的值
        // 同时模拟更新（不改变 arr，只用于预计算所有可能数值）
        vector<pair<int, int>> queries(q);
        // 用一个副本 cur 模拟更新过程，并记录每次新值
        vector<int> cur = arr;
        for (int i = 0; i < q; i++)
        {
            int p, v;
            cin >> p >> v;
            p--; // 下标转换为 0-indexed
            queries[i] = {p, v};
            cur[p] += v;
            all.push_back(cur[p]);
        }

        // 离散化 all
        vector<int> allVals = discretize(all);
        int sz = allVals.size();

        // 辅助 lambda：给定数值 x 返回离散编号（1-indexed）
        auto getID = [&](int x) -> int
        {
            int id = (lower_bound(allVals.begin(), allVals.end(), x) - allVals.begin()) + 1;
            return id;
        };

        // 构建 BIT，大小为 sz
        BIT bit(sz);
        // 初始化 BIT：对每个 arr[i]将其离散编号位置加 1
        for (int i = 0; i < n; i++)
        {
            int id = getID(arr[i]);
            bit.update(id, 1);
        }

        int Tloss = n / 2;
        int r = n - Tloss;

        // 下面每次更新后输出当前麻木数字个数。
        // 麻木数字定义：一个数字 x 是麻木当且仅当 BIT.query(getID(x)) <= r
        // 我们将利用 BIT 进行二分——找到第一个离散下标 d0 使得 BIT.query(d0) >= r+1，
        // 则所有离散编号 < d0 的数字完全计入麻木数字个数 (因为其前缀和 <= r)。
        // 答案 = BIT.query(d0 - 1).（注意若 d0 = 1，则答案 = 0）

        // 模拟 q 次更新
        for (int i = 0; i < q; i++)
        {
            int p = queries[i].first;
            int v = queries[i].second;
            // 先删除原本 arr[p] 在 BIT 中的贡献
            int id_old = getID(arr[p]);
            bit.update(id_old, -1);
            // 更新 arr[p]
            arr[p] += v;
            int id_new = getID(arr[p]);
            bit.update(id_new, 1);

            // 通过 BIT.lower_bound 找到最小离散编号 d0
            int d0 = bit.lower_bound(r + 1);
            int numbCount = 0;
            // 如果 d0 > 1，则前 d0-1 离散值中的数字都肯定满足前缀和 <= r
            numbCount = bit.query(d0 - 1);
            // 输出当前“麻木”数字个数
            cout << numbCount << "\n";
        }
    }
    return 0;
}
