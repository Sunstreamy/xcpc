#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

using b20 = bitset<20>;
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;
#define int long long

const int mod = 1e9 + 7;
const int linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxm = 400005;
const int maxn = 5010;

inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}

inline pair<vector<int>, int> discretize(const vector<int> &a)
{
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    return {c, m};
}
//------------------------------------------------------------------

int fa[maxn];
int sz[maxn];
int n, m, q;

// 初始化函数
void init(int count)
{
    for (int i = 1; i <= count; i++)
    {
        fa[i] = i;
        sz[i] = 1;
    }
}

int find(int v)
{
    if (fa[v] == v)
        return fa[v];
    else
        return find(fa[v]);
}
void mymerge(int &x, int &y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    if (sz[fx] < sz[fy])
    {
        fa[fx] = fy;
        sz[fy] += sz[fx];
    }
    else
    {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}

void solve()
{
    rd(n), rd(m), rd(q);
    init(n);
    for (int i = 0; i < m; i++)
    {
        int x, y;
        rd(x), rd(y);
        mymerge(x, y);
    }
    for (int i = 0; i < q; i++)
    {
        int x, y;
        rd(x), rd(y);
        if (find(x) == find(y))
            cout << "Yes" << '\n';
        else
            cout << "No" << '\n';
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int _;
    // cin >> _;
    // while (_--)
    solve();

    return 0;
}
