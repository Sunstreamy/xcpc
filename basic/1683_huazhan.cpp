#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 200005
void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int num = 1;
    map<int, int> cnt;
    cnt[a[1]] = 1;
    int len = 1e6 + 1;
    int l = 1, r = 1;
    for (int i = 1, j = 1; j <= n;)
    {
        if (num < m)
        {
            j++;
            cnt[a[j]]++;
            if (cnt[a[j]] == 1)
                num++;
        }
        if (num == m)
        {
            if (len > j - i + 1)
            {
                len = j - i + 1;
                l = i, r = j;
            }
            cnt[a[i]]--;
            if (cnt[a[i]] == 0)
            {
                num--;
            }
            i++;
        }
    }
    cout << l << " " << r << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
