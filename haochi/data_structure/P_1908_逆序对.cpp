#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pair<ll, ll>> vpll;
typedef vector<vector<ll>> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 400005;
const int MAXM = 200005;

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
        for (int i = 1 << std::__lg(n); i; i >> 1)
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

int n;
vl a;
void solve()
{
    rd(n);
    a.resize(n);
    for (int i = 0; i < n; i++)
        rd(a[i]);
    auto [tmp, sz] = discretize(a);
    Fenwick<int> ft(sz);
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++)
    {
        ans -= ft.sum(tmp[i] - 1);
        ft.add(tmp[i], 1);
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
