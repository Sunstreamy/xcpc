#include <bits/stdc++.h>
using namespace std;
typedef pair<long long, long long> pii;
typedef vector<long long> vi;
typedef vector<vector<long long>> vii;
typedef vector<string> vs;
typedef bitset<20> b20;
const int M = 998244353;
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
int a[500001];
bool vis[500001];
inline void solve()
{
    int f[3] = {1, 0, 0};
    int n;
    rd(n);
    for (int i = 1; i <= n; i++)
    {
        rd(a[i]);
        vis[i] = false;
    }
    for (int i = 1; i <= n; i++)
    {
        if (!vis[i])
        {
            int curt = 0;
            for (int j = i; vis[j] == false; j = a[j])
            {
                vis[j] = true;
                curt++;
            }
            if ((curt & 1) == 1)
            {
                f[2] = f[1] * curt % M;
                f[1] = f[0] * curt % M;
                f[0] = 0;
            }
            else
            {
                f[2] = ((curt * curt >> 2) % M * f[0] + f[2] * (2 - (curt == 2))) % M;
                f[1] = f[1] * (2 - (curt == 2)) % M;
                f[0] = f[0] * (2 - (curt == 2)) % M;
            }
        }
    }
    cout << f[2] << '\n';
}
// 1 (2) 3 (4) 5  6 1
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
