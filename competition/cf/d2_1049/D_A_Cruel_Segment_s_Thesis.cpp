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
struct Seg {
    int l, r;
};

void solve() {
    int n;
    cin >> n;

    vector<Seg> segs(n);
    i64 ini = 0;
    i64 S_all_l = 0;
    for (int i = 0; i < n; ++i) {
        cin >> segs[i].l >> segs[i].r;
        ini += segs[i].r - segs[i].l;
        S_all_l += segs[i].l;
    }

    if (n == 1) {
        cout << ini << '\n';
        return;
    }

    i64 cur = 0;
    if (!(n & 1)) {
        int k = n / 2;
        vector<i64> vlr(n);
        for (int i = 0; i < n; ++i) {
            vlr[i] = segs[i].l + segs[i].r;
        }
        sort(vlr.rbegin(), vlr.rend());
        i64 slr = 0;
        for (int i = 0; i < k; ++i) {
            slr += vlr[i];
        }
        cur = slr - S_all_l;
    } else {
        // n为奇数时情况
        // 1（抛弃优等生）.需要抛弃前k个vlr中的一名，经过分析，需要最小化抛弃的那一名的r,也就是前k大vlr中，r最小的那项

        // 1. 准备数据：我们需要同时根据 (l+r) 排序，并能随时访问到原始的 l 和 r
        //    所以我们用一个 tuple (元组) 来打包这三个值
        int k = (n - 1) / 2;
        vector<tuple<i64, i64, i64>> vlr(n);
        for (int i = 0; i < n; ++i) {
            vlr[i] = {segs[i].l + segs[i].r, segs[i].l, segs[i].r};
        }
        sort(vlr.rbegin(), vlr.rend());

        i64 slr = 0;
        for (int i = 0; i < k; ++i) {
            slr += get<0>(vlr[i]);
        }

        // 寻找优等生中最小的r
        i64 mnr = linf, mxl = -linf;
        for (int i = 0; i < k; ++i) {
            mnr = min(mnr, get<2>(vlr[i]));
        }
        // 第k+1大的l+r
        i64 kp1 = get<0>(vlr[k]);

        // 第一种情况
        i64 cand1 = slr - mnr + kp1;

        // 2.抛弃差生,理所当然需要让l尽量大，进入S_U的ld才会给出更大的贡献
        for (int i = k; i < n; ++i) {
            mxl = max(mxl, get<1>(vlr[i]));
        }
        i64 cand2 = slr + mxl;

        cur = max(cand1, cand2) - S_all_l;
    }
    cout << ini + cur << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}