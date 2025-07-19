//https://www.lanqiao.cn/problems/1458/learning/
#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        a[i] = i;
    }
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        if (x == 0)
        {
            sort(a.begin() + 1, a.begin() + y + 1, greater<int>());
        }
        if (x == 1)
        {
            sort(a.begin() + y, a.begin() + n + 1);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        cout << a[i] << " ";
    }

    // 请在此输入您的代码
    return 0;
}