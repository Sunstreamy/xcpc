// https://pintia.cn/problem-sets/994805342720868352/exam/problems/type/7?problemSetProblemId=994805507225665536&page=0
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define n 200005
const int m = 1e9 + 7;

// 获取字符串中的最大数字值
int get_max_digit(string s)
{
    int max_digit = 0;
    for (char c : s)
    {
        int d = isdigit(c) ? c - '0' : toupper(c) - 'a' + 10;
        max_digit = max(max_digit, d);
    }
    return max_digit;
}

// 安全的进制转换函数
bool from_base_to_ten(string s, i64 base, i64 &res)
{
    res = 0;
    for (char c : s)
    {
        i64 d = isdigit(c) ? c - '0' : toupper(c) - 'a' + 10;
        if (d >= base)
            return false; // 无效数字

        // 检查溢出
        if (res < 0)
            return false; // 溢出

        res = res * base + d;
    }
    return true;
}

void solve()
{
    string a, b;
    cin >> a >> b;
    int tag;
    cin >> tag;
    int radix;
    cin >> radix;
    if (tag == 2)
    {
        swap(a, b);
    }

    // 计算已知数的十进制值
    i64 n1 = 0;
    from_base_to_ten(a, radix, n1);

    // 确定搜索范围的下限
    int min_radix = get_max_digit(b) + 1;
    i64 l = max(2, min_radix) - 1; // 至少是2或者最大数字+1

    // 确定上限，上限不会超过n1+1
    i64 r = max(l, n1 + 1) + 1;

    i64 flag = 0;

    // 二分查找
    while (l + 1 < r)
    {
        i64 mid = l + (r - l) / 2;
        i64 n2 = 0;

        bool valid = from_base_to_ten(b, mid, n2);

        if (n1 == n2)
        {
            flag = mid;
            break;
        }
        else if (n1 < n2 || !valid)
        {
            r = mid;
        }
        else
        {
            l = mid;
        }
    }

    if (!flag)
        cout << "Impossible" << endl;
    else
        cout << flag << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}