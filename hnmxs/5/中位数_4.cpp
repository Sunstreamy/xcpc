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

struct Converter {
    // mp:  用于将字符（'0'-'9', 'a'-'z', 'a'-'z'）映射为对应的整数（0-61）。
    // mp2: 用于将整数（0-61）映射回对应的字符。
    vector<int> mp;
    vector<char> mp2;

    Converter() : mp(123), mp2(62) {
        // 映射数字 '0' 到 '9'
        for (int i = 0; i < 10; ++i) {
            mp['0' + i] = i;
            mp2[i] = '0' + i;
        }
        // 映射大写字母 'A' 到 'Z'
        for (int i = 0; i < 26; ++i) {
            mp['A' + i] = i + 10;
            mp2[i + 10] = 'A' + i;
        }
        // 映射小写字母 'a' 到 'z'
        for (int i = 0; i < 26; ++i) {
            mp['a' + i] = i + 36;
            mp2[i + 36] = 'a' + i;
        }
    }

    // 转换前进制 转换后进制 要转换的数据
    string solve(int a, int b, const string &s) {
        vector<int> nums, ans;
        for (auto c : s) {
            nums.push_back(mp[c]);
        }
        reverse(nums.begin(), nums.end());
        while (nums.size()) {  // 短除法，将整个大数一直除 b ，取余数
            int remainder = 0;
            for (int i = nums.size() - 1; i >= 0; i--) {
                nums[i] += remainder * a;
                remainder = nums[i] % b;
                nums[i] /= b;
            }
            ans.push_back(remainder);  // 得到余数
            while (nums.size() && nums.back() == 0) {
                nums.pop_back();  // 去掉前导 0
            }
        }
        reverse(ans.begin(), ans.end());

        string restr;
        for (int i : ans) restr += mp2[i];
        return restr;
    }
};

void solve() {
    i64 n, k;
    cin >> n >> k;
    Converter con;
    string num = to_string(n);
    string ans = con.solve(10, k, num);
    int cnt = 0;
    for (int i = ans.length() - 1; i >= 0; --i) {
        if (ans[i] == '0') {
            cnt++;
        } else {
            // 一旦遇到非'0'字符，就停止计数
            break;
        }
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}