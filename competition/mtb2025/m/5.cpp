
#include <bits/stdc++.h>
using ll = long long;
using namespace std;
constexpr int mod = 1e9 + 7;



void solve()
{
    int n,m;
    cin >> n >> m;
    vector<int> a(n);

    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    int ans = accumulate(a.begin(), a.end(), 0);
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}