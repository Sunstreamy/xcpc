//
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
typedef pair<int, int> PII;
typedef vector<int> VI;
const int M = 1e9 + 7;
#define N 200005
#define int long long
struct BIT {
    int n;
    // 用于存储区间频率
    vector<int> tree;
    BIT(int n) : n(n), tree(n + 1, 0) {}
    
    // 单点更新：在位置 idx 加上 delta
    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }
    
    // 前缀和查询：查询区间 [1, idx] 内的和
    int query(int idx) {
        int sum = 0;
        for (; idx; idx -= idx & -idx)
            sum += tree[idx];
        return sum;
    }
    
    // 二分查找：返回最小的 idx 使得 query(idx) >= target
    int lower_bound(int target) {
        int idx = 0;
        // 这里取足够大的最高位（2^20=1048576即可，保证 n 不超过 5e5）
        for (int bit = 1 << 20; bit; bit >>= 1) {
            int next = idx + bit;
            if (next <= n && tree[next] < target) {
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
    // 先读入所有数据
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    vector<int> b(a);
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    for (int i = 0; i < n; i++)
    {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }

    VI tr(m + 1, 0);
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++)
    {
        int x = a[i];
        for (int j = x; j; j -= (j & -j))
            ans -= tr[j];
        for (int j = x; j <= m; j += (j & -j))
            tr[j]++;
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