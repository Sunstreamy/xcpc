#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int MOD[] = {998244353, 1000000007};
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------
constexpr i64 M = MOD[0];

map<int, int> ok(const vector<int>& a) {
    int n = a.size();
    if (n == 0) {
        return {};
    }
    vector<int> lless(n);
    vector<int> rless(n);
    stack<int> s;

    for (int i = 0; i < n; ++i) {
        while (!s.empty() && a[s.top()] > a[i]) {
            s.pop();
        }
        lless[i] = s.empty() ? -1 : s.top();
        s.push(i);
    }

    while (!s.empty()) {
        s.pop();
    }

    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && a[s.top()] > a[i]) {
            s.pop();
        }
        rless[i] = s.empty() ? n : s.top();
        s.push(i);
    }

    map<int, int> res;
    for (int i = 0; i < n; ++i) {
        int val = a[i];
        int mxlen = rless[i] - lless[i] - 1;
        int deletions = n - mxlen;
        res[val] = deletions;
    }

    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    i64 ans = 1;
    map<int, int> mp;
    mp = ok(a);

    for (int i = 1; i <= n; ++i) {
        ans = (ans + n - mp[i]) % M;

        if (mp[i] < n - 1) {
            ans = (ans + mp[i]) % M;
        }

        if (mp[i] < n - 1 && i != 1) {
            ans = (ans + 1) % M;
        }
    }

    cout << (ans % M + M) % M << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}