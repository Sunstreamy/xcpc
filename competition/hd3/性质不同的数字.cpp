#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;

using b20 = bitset<20>;
using vi = vector<i64>;
using vii = vector<vector<i64>>;
using pii = pair<i64, i64>;
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
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

void solve()
{
    int n;
    cin >> n;

    vector<pair<int, u64>> a;
    for (int i = 0; i < n; i++)
    {
        int l, r;
        cin >> l >> r;
        u64 x = rng();
        a.emplace_back(l, x);
        a.emplace_back(r + 1, x);
    }
    sort(a.begin(), a.end());
    int lst = -1;
    u64 cur = 0;
    vi s{0};
    for (auto [i, x] : a)
    {
        if (i > lst)
        {
            s.push_back(cur);
        }
        lst = i;
        cur ^= x;
    }
    sort(s.begin(), s.end());
    int ans = unique(s.begin(), s.end()) - s.begin();
    cout << ans << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--)
        solve();

    return 0;
}
