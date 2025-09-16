//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
typedef pair<int, int> PII;
const int M = 1e9 + 7;
#define N 200005

int a, b;
vector<int> dist(200005, -1);

void solve()
{
    queue<int> q;
    dist[a] = 0;
    q.push(a);
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        if (cur == b)
            break;
        int nxts[] = {cur - 1, cur + 1, cur * 2};
        for (int i = 0; i < 3; i++)
        {
            int nxt = nxts[i];
            if (nxt >= 0 && nxt <= 200000 && dist[nxt] == -1)
            {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    cout << dist[b] << '\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> a >> b;
    solve();

    return 0;
}
