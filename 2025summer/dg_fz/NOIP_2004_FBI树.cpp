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
    int n;
    cin >> n;
    string s;
    cin >> s;

    function<void(int, int)> build = [&](int l, int r)
    {
        if (l < r)
        {
            int m = l + r >> 1;
            build(l, m);
            build(m + 1, r);
        }
        bool f0 = false;
        bool f1 = false;
        for (int i = l; i <= r; i++)
        {
            if (s[i] == '0')
                f0 = true;
            else
                f1 = true;
            if (f0 && f1)
                break;
        }
        if (f1 && f0)
            cout << 'F';
        else if (f1)
            cout << 'I';
        else
            cout << 'B';
    };

    if (!s.empty())
    {
        build(0, s.length() - 1);
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
