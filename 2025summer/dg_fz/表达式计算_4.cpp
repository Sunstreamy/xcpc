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
string s;

int num(int l, int r)
{
    int res = 0;
    for (int i = l; i <= r; i++)
        res = res * 10 + (s[i] - '0');
    return res;
}

int cal(int l, int r)
{
    if (l > r)
        return 0;
    int posj = -1, posc = -1, posp = -1;
    int cnt = 0;
    // 从外层开始进入递归，使用cnt计数器控制先记录括号外的运算符号
    for (int i = l; i <= r; i++)
    {
        if (s[i] == '(')
            cnt++;
        if (s[i] == ')')
            cnt--;
        if ((s[i] == '+' || s[i] == '-') && cnt == 0)
            posj = i;
        if ((s[i] == '*' || s[i] == '/') && cnt == 0)
            posc = i;
        if ((s[i] == '^') && cnt == 0)
            posp = i;
    }
    // 在当前范围内没有符号的情况下，进行条件判断
    if (posj == -1 && posc == -1 && posp == -1)
    {
        // 多余括号情况
        // 左括号多余
        if (cnt > 0 && s[l] == '(')
            return cal(l + 1, r);
        // 右括号多余
        else if (cnt < 0 && s[r] == ')')
            return cal(l, r - 1);
        else if (cnt == 0 && s[l] == '(' && s[r] == ')')
        {
            return cal(l + 1, r - 1);
        }
        else
            return num(l, r);
    }
    if (posj != -1)
    {
        if (s[posj] == '+')
            return cal(l, posj - 1) + cal(posj + 1, r);
        if (s[posj] == '-')
            return cal(l, posj - 1) - cal(posj + 1, r);
    }
    else if (posc != -1)
    {
        if (s[posc] == '*')
            return cal(l, posc - 1) * cal(posc + 1, r);
        if (s[posc] == '/')
            return cal(l, posc - 1) / cal(posc + 1, r);
    }
    else if (posp != -1)
        return (int)pow(cal(l, posp - 1), cal(posp + 1, r));
    return 0;
}

void solve()
{
    cin >> s;
    cout << cal(0, s.size() - 1);
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
