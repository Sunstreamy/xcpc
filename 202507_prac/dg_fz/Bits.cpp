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
int n;
vl a, b, c;
string pp(int x)
{
    if (x == 0)
    {
        return string(n + 1, '.') + "|" + string(n, '.');
    }
    else
        return string(n + 1 - x, '.') + string(2 * x + 1, '*') + string(n - x, '.');
}
void p()
{
    cout << string(3 * (2 * n + 1) + 4, '.') << '\n';
    for (int i = n; i >= 0; i--)
    {
        cout << pp(i < a.size() ? a[i] : 0);
        cout << pp(i < b.size() ? b[i] : 0);
        cout << pp(i < c.size() ? c[i] : 0);
        cout << '.' << '\n';
    }
}
void hanoi(int s, vl &a, vl &b, vl &c)
{
    if (s == 0)
        return;
    hanoi(s - 1, a, c, b);
    c.push_back(a.back());
    a.pop_back();

    cout << string(3 * (2 * n + 1) + 4, '-') << endl;
    p();

    hanoi(s - 1, b, a, c);
}

void solve()
{
    rd(n);
    for (int i = n; i >= 1; i--)
        a.push_back(i);
    p();
    if (n & 1)
        hanoi(n, a, c, b);
    else
        hanoi(n, a, b, c);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
