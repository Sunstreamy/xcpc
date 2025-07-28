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
const int linf = 0x3f3f3f3f3f3f3f3fll;
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
//------------------------------------------------------------------

void solve()
{
    int n, m;
    rd(n), rd(m);
    vl b(n), c(n);
    vl bb(n), cc(n);
    int mx = 0, mn = 0;
    for (int i = 0; i < n; i++)
        rd(b[i]);
    for (int i = 0; i < n; i++)
        rd(c[i]);
    bb[0] = b[0];
    for (int i = 1; i < n; i++)
    {
        bb[i] = max(b[i], bb[i - 1]);
    }
    cc[n - 1] = c[n - 1];
    for (int i = n - 2; i >= 0; i--)
    {
        cc[i] = min(cc[i + 1], c[i]);
    }
    for (int i = 0; i < n; ++i)
    {
        if (bb[i] > cc[i])
        {
            cout << "NO\n";
            return;
        }
        mn += bb[i];
        mx += cc[i];
    }

    if (m >= mn && m <= mx)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
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
