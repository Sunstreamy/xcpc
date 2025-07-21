//
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
vs grid;
int r, c;
int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

void bfs()
{
    queue<pii> q;
    q.push({0, 0});
    grid[0][0] = '#';
    while (!q.empty())
    {
        auto [x, y] = q.front();
        q.pop();
        if (x == r - 1 && y == c - 1)
        {
            cout << "Yes" << '\n';
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx >= 0 && nx < r && ny >= 0 && ny < c && grid[nx][ny] == '.')
            {
                q.push({nx, ny});
                grid[nx][ny] = '#';
            }
        }
    }
    cout << "No" << '\n';
}

void solve()
{
    cin >> r >> c;
    grid.resize(r);
    for (int i = 0; i < r; i++)
    {
        cin >> grid[i];
    }
    bfs();
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
