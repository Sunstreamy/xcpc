//
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
int r, c;
int grid[20][20], tmp[20][20], ans[20][20];
b20 b;

inline void flip(int x, int y)
{
    tmp[x][y] ^= 1;
    tmp[x][y + 1] ^= 1;
    tmp[x][y - 1] ^= 1;
    tmp[x - 1][y] ^= 1;
    tmp[x + 1][y] ^= 1;
}

inline void go()
{
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
            cout << ans[i][j] << " ";
        cout << '\n';
    }
    exit(0); // 非主函数中使用exit(0)直接结束程序 ，因为判断字典序时，\
	优先第一行，	所以只要有序枚举第一行， 第一次得到的答案就是最优解
}

inline void check()
{
    //注意只需遍历到倒数第二行，最后一行单独检查就行了。
    for (int i = 1; i < r; i++)
        for (int j = 1; j <= c; j++)
        {
            if (tmp[i][j] == 1)
            {
                flip(i + 1, j);
                ans[i + 1][j] = 1;
            }
        }
    for (int j = 1; j <= c; j++)
    {
        if (tmp[r][j] == 1)
            return;
    }
    go();
}

inline void solve()
{
    rd(r), rd(c);
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
            rd(grid[i][j]);
    }
    memcpy(tmp, grid, sizeof(grid));
    int k = 0;
    while (b[c] != 1)
    {
        b = k++;
        for (int i = 0; i < c; i++)
        { // 枚举第一行情况
            if (b[i])
            {
                flip(1, i + 1), ans[1][i + 1] = 1;
            }
        }
        check();
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
            {
                tmp[i][j] = grid[i][j];
                ans[i][j] = 0;
            }
    }
    cout << "IMPOSSIBLE" << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}

/*
1.枚举第一行的2^c种情况，然后从第二行开始贪心反转每一行中上一行为1的情况，O（2^r*r*c）
2.代码实现思路：使用bitset存储20位0，然后从b[0]-b[c]模拟第一行的2^c种情况,中途使用tmp存储好一开始数组的状态，维护棋盘的初始状态，同时还原ans为全0数组。
*/