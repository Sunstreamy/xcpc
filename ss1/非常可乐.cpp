// https://vjudge.net/problem/HDU-1495
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vector<int>> vii;
typedef vector<string> vs;
typedef bitset<20> b20;
const int M = 1e9 + 7;
#define N 200005
#define int long long

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

int ls, la, lb;
int ans;
vii vis(105, vi(105));

void dfs(int nla, int nlb, int cnt)
{
    // exit
    int nls = ls - nla - nlb;
    if (nls == ls / 2)
    {
        ans = min(cnt, ans);
        return;
    }
    // 剪枝
    if (vis[nla][nlb] != -1 && cnt >= vis[nla][nlb])
        return;
    vis[nla][nlb] = cnt;
    if (cnt >= ans)
        return;
    // caps数组维护当前两个杯子完成选择倒水的情况
    int caps[3] = {la, lb, ls};
    // cur数组维护dfs的nxt的情况
    int cur[3] = {nla, nlb, nls};
    int nxt[3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
                continue;
            if (cur[i] == 0 || cur[j] == caps[j])
                continue;
            int val = min(cur[i], caps[j] - cur[j]);
            memcpy(nxt, cur, sizeof(cur));
            nxt[i] -= val;
            nxt[j] += val;
            dfs(nxt[0], nxt[1], cnt + 1);
        }
}

void solve()
{
    if (ls % 2 == 1)
    {
        cout << "NO" << '\n';
        return;
    }
    ans = M;
    vis.assign(105, vi(105, -1));
    dfs(0, 0, 0);
    if (ans == M)
    {
        cout << "NO" << '\n';
        return;
    }
    cout <<ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    while (cin >> ls >> la >> lb && ls)
    {
        solve();
    }

    return 0;
}

/*就是要看能不能用a和b两个杯子把s中的水变为剩下一半,
1.所以杯子中的水必须是偶数

2.对于偶数情况，则两层循环搜索三个杯子互相倒水（要么把倒水的杯子倒光，要么把接水的杯子填满，不必考虑微小水量的变化，多次倒少量水最后等价于这两种情况）的六种情况并用vis数组记录当前分配情况的最小步数进行剪枝。

3.三个杯子互相倒水的代码实现可以在六种情况的循环中每次init一个nxt数组记录进入下一轮dfs的新分配情况，然后需要注意的是如果当前的cap[i]中没水或者
*/