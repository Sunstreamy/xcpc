#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int mod = 1e9 + 7;
const int linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxm = 400005;
const int maxn = 200005;

inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}

inline pair<vl, int> discretize(const vl &a)
{
    vl b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    vl c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    return {c, m};
}
template <typename T>
struct Fenwick
{
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n + 1, T{});
    }

    void add(int x, const T &v)
    {
        for (int i = x; i <= n; i += i & -i)
        {
            a[i] = a[i] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i)
        {
            ans = ans + a[i];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    int select(const T &k)
    {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i >>= 1)
        {
            if (x + i <= n && cur + a[x + i] <= k)
            {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};
//------------------------------------------------------------------

void solve()
{
    int n;
    rd(n);
    vl a(n + 1), b(n + 1), posa(n + 1), posb(n + 1);
    for (int i = 1; i <= n; i++)
    {
        rd(a[i]);
        posa[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
    {
        rd(b[i]);
        posb[b[i]] = i;
    }
    Fenwick<int> ft(n);
    vl ans(n + 1);
    for (int i = 1; i <= n; i++)
    {
        // 当前处理的是 A 排名第 i 的选手，我们称他为 p
        int p = a[i];

        // p 的 B 排名是多少？
        int rank_in_b = posb[p];

        // 关键一步：计算重叠人数
        // “重叠”的人是指在 a 和 b 中排名都比 p 高的人。
        // 因为我们是按 a 的排名顺序处理的，所以到目前为止，我们已经处理过的所有选手 (a[1]...a[i-1]) 在 a 中的排名都比 p 高。
        // 所以，我们只需要在这些已经处理过的人里面，再找出 b 排名也比 p 高的人。
        // p 在 b 中的排名是 rank_in_b。比他高，意味着 b 排名在 [1, rank_in_b - 1] 区间内。
        // 这个人数恰好就是 ft.sum(rank_in_b - 1)！
        int overlap_count = ft.sum(rank_in_b - 1);

        // 使用容斥原理计算最终答案
        // 在 a 中比 p 排名高的人数：i - 1
        // 在 b 中比 p 排名高的人数：rank_in_b - 1
        ans[p] = (i - 1) + (rank_in_b - 1) - overlap_count;

        // 处理完选手 p，我们需要更新树状数组，为后续计算做准备。
        // 我们把 p 的 b 排名信息加入树状数组。
        // 表示“我们又发现了一个 b 排名为 rank_in_b 的选手”。
        ft.add(rank_in_b, 1);
    }
    for (int i = 1; i <= n; i++)
    {
        cout << ans[i];
        if (i < n)
            cout << " ";
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _;
    rd(_);
    while (_--)
        solve();

    return 0;
}
