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

void solve() {
    i64 x;
    cin >> x;
    string str = to_string(x);
    if (x >= 0) {
        int len = str.length();
        int pos = -1;
        for (int i = 0; i < len; ++i) {
            if (str[i] < '1') {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            str.insert(pos, "1");
        } else {
            str.push_back('1');
        }
        cout << str << "\n";
        return;
    } else {
        string abss = str.substr(1);
        int len = abss.length();
        int pos = -1;
        for (int i = 0; i < len; ++i) {
            if (abss[i] > '1') {
                pos = i;
                break;
            }
        }
        if (pos != -1) {
            abss.insert(pos, "1");
        }
        else {
            abss.push_back('1');
        }
        cout << '-' << abss << '\n';
        return;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}