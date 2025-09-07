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
    int n;
    cin >> n;
    priority_queue<int> lo;                             // 大顶堆 (存较小一半)
    priority_queue<int, vector<int>, greater<int>> hi;  // 小顶堆 (存较大一半)

    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;

        lo.push(x);
        hi.push(lo.top());
        lo.pop();

        // 保证 lo 的大小 >= hi 的大小
        if (lo.size() < hi.size()) {
            lo.push(hi.top());
            hi.pop();
        }

        if(i&1){
            cout << lo.top() << ' ';
        }
        else {
            cout << (lo.top() + hi.top()) / 2 << ' ';
        }
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}