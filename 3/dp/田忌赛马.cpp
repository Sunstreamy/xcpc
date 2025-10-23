#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int Inf = 0x3f3f3f3f;
constexpr i64 Linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 Dinf = 1e18;
constexpr int Maxm = 400005;
constexpr int Maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
int cal(int a, int b) {
    if (a < b) return -1;
    if (a > b) return 1;

    return 0;
}

void solve() {
    int n;
    cin >> n;
    vector<int> tian(n + 1), king(n + 1);
    vector<vector<int>> f(n + 1, vector<int>(n + 1, -Inf));

    for (int i = 1; i <= n; ++i) {
        cin >> tian[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> king[i];
    }
    sort(tian.begin() + 1, tian.end());
    sort(king.begin() + 1, king.end());
    for (int i = 1; i <= n; ++i) {
        f[i][i] = cal(tian[i], king[1]);
    }

    for (int len = 2; len <= n; ++len) {
        //tian用i～j的马对战齐王的len匹马能得到的最佳结果
        for (int i = 1, j = len; j <= n; i++, j++) {
            f[i][j] = max(f[i][j - 1] + cal(tian[j], king[len]), f[i + 1][j] + cal(tian[i], king[len]));
        }
    }
    cout << f[1][n] * 200 << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}