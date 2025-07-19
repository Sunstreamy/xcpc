#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 200005
const int M = 1e9 + 7;
void solve()
{
    int n;
    cin >> n;
    priority_queue<int,vector<int>, greater<int>> pq;
    while (n--)
    {
        int op, x;
        cin >> op;
        if (op == 1)
        {
            cin >> x;
            pq.push(x);
        }
        else if (op == 2)
        {
            cout << pq.top() << endl;
        }
        else
            pq.pop();
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();
    return 0;
}
