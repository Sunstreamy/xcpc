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

constexpr int M = MOD[0];
bool isleap(int yy) {
    if (yy == 0) return false;
    return (yy % 4 == 0 && yy % 100 != 0) || (yy % 400 == 0);
}

int ddinmm(int yy, int mon) {
    if (mon < 1 || mon > 12) return 0;
    if (mon == 2) return isleap(yy) ? 29 : 28;
    if (mon == 4 || mon == 6 || mon == 9 || mon == 11) {
        return 30;
    }
    return 31;
}
vector<unordered_map<i64, bool>> memo(9);

bool ok(i64 ss, int len) {
    if (memo[len].count(ss)) {
        return memo[len][ss];
    }
    bool flag = false;
    if (len <= 3) {
        flag = true;
    } else if (len == 4) {
        flag = (ss >= 1);
    } else if (len == 5) {
        int yy = ss / 10;
        int mm = ss % 10;
        flag = (yy >= 1 && mm <= 1);
    } else if (len == 6) {
        int yy = ss / 100;
        int mm = ss % 100;
        flag = (yy >= 1 && mm >= 1 && mm <= 12);
    } else if (len == 7) {
        int yy = ss / 1000;
        int mm = (ss / 10) % 100;
        int dd = ss % 10;
        if (yy >= 1 && mm >= 1 && mm <= 12) {
            int mxd = ddinmm(yy, mm);
            flag = (dd <= mxd / 10);
        }
    } else if (len == 8) {
        int yy = ss / 10000;
        int mm = (ss / 100) % 100;
        int dd = ss % 100;
        if (yy >= 1 && mm >= 1 && mm <= 12) {
            int mxd = ddinmm(yy, mm);
            flag = (dd >= 1 && dd <= mxd);
        }
    }
    return memo[len][ss] = flag;
}
void solve() {
    int len;
    cin >> len;
    string str;
    cin >> str;
    if (len < 8) {
        cout << 0 << '\n';
        return;
    }

    vector<unordered_map<i64, i64>> dp(9);
    dp[0][0] = 1;
    for (char ch : str) {
        int d = ch - '0';
        for (int k = 8; k >= 1; --k) {
            for (auto const& [pre, cnt] : dp[k - 1]) {
                if (cnt == 0) continue;
                i64 cur = pre * 10 + d;

                if (ok(cur, k)) {
                    dp[k][cur] = (dp[k][cur] + cnt) % M;
                }
            }
        }
    }
    i64 ans = 0;
    if (!dp[8].empty()) {
        for (auto const& [finals, cnt] : dp[8]) {
            ans = (ans + cnt) % M;
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