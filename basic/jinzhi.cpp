#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005

// 通用模板（支持2-36进制）
int to_decimal(const string &s, int base)
{
    int res = 0;
    for (char c : s)
    {
        int digit = isdigit(c) ? c - '0' : toupper(c) - 'A' + 10;
        res = res * base + digit;
    }
    return res;
}
// 返回逆序字符串（需要reverse得到正确顺序）
string from_decimal(int n, int base)
{
    if (n == 0)
        return "0";
    string res;
    while (n > 0)
    {
        int digit = n % base;
        res += (digit < 10) ? '0' + digit : 'A' + digit - 10;
        n /= base;
    }
    reverse(res.begin(), res.end());
    return res;
}


void solve()
{
    string a;
    cin >> a;
    int t = to_decimal(a, 16);
    string ans = from_decimal(t, 8);
    cout << ans << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--)
        solve();

    return 0;
}
