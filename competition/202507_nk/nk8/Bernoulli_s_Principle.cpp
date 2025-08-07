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
struct Hole {
    int id;
    i64 val;
};
void solve() {
    int n, H;
    cin >> n >> H;
    vector<Hole> holes(n);
    for (int i = 0; i < n; ++i) {
        i64 h;
        cin >> h;
        holes[i].id = i + 1;
        holes[i].val = (H - h) * h;
    }
    sort(holes.begin(), holes.end(), [](const Hole& a, const Hole& b) {
        if (a.val != b.val) {
            return a.val < b.val;
        }
        return a.id < b.id;
    });
    for (int i = 0; i < n; ++i) {
        cout << holes[i].id << " ";
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}