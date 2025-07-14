#include <bits/stdc++.h>
#define int long long
using namespace std;

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), tr(n + 1);

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        a[x] = i;
    }

    int num = n * (n - 1) / 2;

    for (int i = 1; i <= n; i++)
    {
        int x;
        cin >> x;
        x = a[x];

        for (int j = x; j; j -= (j & -j))
            num -= tr[j];

        for (int j = x; j <= n; j += (j & -j))
            tr[j]++;
    }

    if (num & 1)
        cout << "A";
    else
        cout << "B";

    for (int i = 1; i < n; i++)
    {
        char opt;
        int l, r, d;
        cin >> opt >> l >> r >> d;
        num += (l - r + 1 - d) * d;

        if (num & 1)
            cout << "A";
        else
            cout << "B";
    }
    cout << "\n";
}

signed main()
{
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    int T = 1;
    cin >> T;
    for (int i = 1; i <= T; i++)
        solve();
    return 0;
}