#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int M = 1e9 + 7;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------

void solve() {
    int n;
    cin >> n;
    vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    bool flag = true;
    for (int i = 1; i < n; ++i) {
        if (a[i] != a[0]) {
            flag = false;
            break;
        }
    }
    if(flag){
        cout << 0 << '\n';
        return;
    }
    cout << n - 1 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}