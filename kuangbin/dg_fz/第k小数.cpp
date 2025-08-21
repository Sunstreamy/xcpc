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
        rex = rex * 10 + c - '0',
        c = getchar();
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
vl a;
int sel(int l, int r, int k)
{
    if (l >= r)
        return a[l];
    // 随机选择一个基准点, 并交换到末尾, 以获得O(N)的平均复杂度
    // swap(a[l + rand() % (r - l + 1)], a[r]);
    int p = a[r];
    int i = l - 1; // i 指向小于等于pivot区域的末尾
    for (int j = l; j < r; j++)
    {
        if (a[j] <= p)
            swap(a[++i], a[j]);
    }
    swap(a[i + 1], a[r]);
    int p_idx = i + 1;
    int count = p_idx - l + 1;
    if (count == k)
        return a[p_idx];
    if (count > k)
        return sel(l, p_idx - 1, k);
    return sel(p_idx + 1, r, k - count);
}

void solve()
{
    int n, k;
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << sel(0, n - 1, k) << '\n';

    // nth_element(arr.begin(), arr.begin() + k - 1, arr.end());
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // srand(time(0));

    int _;
    cin >> _;
    while (_--)
        solve();

    return 0;
}