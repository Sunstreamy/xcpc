#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 200005
const int M = 1e9 + 7;

int f[110][1010];
int w[110], c[110];
void solve()
{
    int time;
    int num;
    cin >> time >> num;
    for (int i = 1; i <= num; i++)
    {
        cin >> w[i] >> c[i];
    }
    for (int i = 1; i <= num; i++)
    {
        for (int j = 1; j <= time; j++)
        {
            if (j < w[i])
            {
                f[i][j] = f[i - 1][j];
            }
            else
                f[i][j] = max(f[i - 1][j], f[i - 1][j - w[i]] + c[i]);
        }
    }
    cout << f[num][time] << endl;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
