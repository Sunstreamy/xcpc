#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
constexpr int MOD[] = {998244353, 1000000007};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];

    int ptr1 = 0, ptr2 = 0;
    for (int i = 0; i < n; ++i) {
        if (ptr1 < m && a[i] == b[ptr1]) {
            ptr1++;
        } else if (ptr2 < m && a[i] == b[ptr2]) {
            ptr2++;
        }
    }

    if (ptr2 == m) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}