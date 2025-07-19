// https://www.luogu.com.cn/problem/P1908
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int M = 1e9 + 7;
#define N 200005
#define int long long

vi discretize(vi &all)
{
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    return all;
}

struct fwt
{
    int n;
    // 用于存储区间频率
    vector<int> tree;
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
        // 这里取足够大的最高位（2^20=1048576即可，保证 n 不超过 5e5）
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

void solve()
{
    int n;
    cin >> n;
    vi a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vi b = a;
    vi pot = discretize(b);
    int m = pot.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = lower_bound(pot.begin(), pot.end(), a[i]) - pot.begin() + 1;
    }

    fwt tr(m);
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++)
    {
        ans -= tr.query(a[i]);
        tr.update(a[i], 1);
    }
    cout << ans << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}