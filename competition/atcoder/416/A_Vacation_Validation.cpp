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
using vpii = vector<pair<int, int>>;
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

void solve()
{
    int n, l, r;
    cin >> n >> l >> r;
    string s;
    cin >> s;
    bool flag = true;
    for (int i = l - 1; i < r; i++)
    {
        if (s[i] == 'x')
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << "Yes\n";
        return;
    }
    else
        cout << "No\n";
    return;
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
