#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------

void solve() {
    string s;
    cin >> s;
    int len = s.length();

    // rr[j] 表示以 j 结尾的括号串的最晚（最大）起始位置
    vector<int> rr(len, -1);
    for (int i = 0; i < len; ++i) {
        int balan = 0;
        bool alp = false;
        for (int j = i; j < len; ++j) {
            if (s[j] == '(') {
                balan++;
            } else if (s[j] == ')') {
                balan--;
            } else {
                alp = true;
            }

            if (alp || balan < 0) {
                break;
            }
            if (balan == 0) {
                rr[j] = max(rr[j], i);
            }
        }
    }

    vector<int> ll(len, -1);
    ll[0] = rr[0];
    for (int j = 1; j < len; ++j) {
        ll[j] = max(ll[j - 1], rr[j]);
    }

    i64 ans = 0;
    //odd
    for (int i = 0; i < len; ++i) {
        for (int l = i, r = i; l >= 0 && r < len && s[l] == s[r]; --l, ++r) {
            if (ll[r] >= l) {
                ans++;
            }
        }
    }
    
    for (int i = 0; i < len - 1; ++i) {
        for (int l = i, r = i + 1; l >= 0 && r < len && s[l] == s[r]; --l, ++r) {
            if (ll[r] >= l) {
                ans++;
            }
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}