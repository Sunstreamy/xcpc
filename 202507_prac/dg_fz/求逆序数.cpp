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
//------------------------------------------------------------------

int a[maxn], b[maxn], n;
// void msort(int l, int r)
// {

//     if (l == r)
//         return;
//     int m = l + r >> 1;
//     msort(l, m);
//     msort(m + 1, r);
//     int i = l, j = m + 1, k = l;
//     while (i <= m && j <= r)
//     {
//         if (a[i] <= a[j])
//             b[k++] = a[i++];
//         else
//             b[k++] = a[j++];
//     }
//     while (i <= m)
//         b[k++] = a[i++];
//     while (j <= r)
//         b[k++] = a[j++];
//     for (i = l; i <= r; i++)
//         a[i] = b[i];
// }
ll count(int lo, int hi)
{
    if (lo >= hi)
        return 0;
    int m = lo + hi >> 1;
    ll res = count(lo, m) + count(m + 1, hi);

    int i = lo, j = m + 1, k = lo;
    while (i <= m && j <= hi)
    {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
        {
            b[k++] = a[j++];
            res += (m - i + 1);
        }
    }
    while (i <= m)
        b[k++] = a[i++];
    while (j <= hi)
        b[k++] = a[j++];
    for (int i = lo; i <= hi; i++)
        a[i] = b[i];
    return res;
}

void solve()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << count(0, n - 1) << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
