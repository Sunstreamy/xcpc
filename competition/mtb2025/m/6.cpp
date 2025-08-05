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
template <class T>
constexpr T mypow(T n, i64 k) {
    T r = 1;
    for (; k; k /= 2, n *= n) {
        if (k & 1) {
            r *= n;
        }
    }
    return r;
}

template <class T>
constexpr T power(int n) {
    return mypow(T(2), n);
}

template <int MOD>
struct Zmod {
    int x;
    Zmod(signed x = 0) : x(norm(x % MOD)) {}
    Zmod(i64 x) : x(norm(x % MOD)) {}

    constexpr int norm(int x) const noexcept {
        if (x < 0) [[unlikely]] {
            x += MOD;
        }
        if (x >= MOD) [[unlikely]] {
            x -= MOD;
        }
        return x;
    }
    explicit operator int() const {
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Zmod operator-() const {
        Zmod val = norm(MOD - x);
        return val;
    }
    constexpr Zmod inv() const {
        assert(x != 0);
        return mypow(*this, MOD - 2);
    }
    friend constexpr auto &operator>>(istream &in, Zmod &j) {
        int v;
        in >> v;
        j = Zmod(v);
        return in;
    }
    friend constexpr auto &operator<<(ostream &o, const Zmod &j) {
        return o << j.val();
    }
    constexpr Zmod &operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr Zmod &operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr Zmod operator++(signed) {
        Zmod res = *this;
        ++*this;
        return res;
    }
    constexpr Zmod operator--(signed) {
        Zmod res = *this;
        --*this;
        return res;
    }
    constexpr Zmod &operator+=(const Zmod &i) {
        x = norm(x + i.x);
        return *this;
    }
    constexpr Zmod &operator-=(const Zmod &i) {
        x = norm(x - i.x);
        return *this;
    }
    constexpr Zmod &operator*=(const Zmod &i) {
        x = i64(x) * i.x % MOD;
        return *this;
    }
    constexpr Zmod &operator/=(const Zmod &i) {
        return *this *= i.inv();
    }
    constexpr Zmod &operator%=(const int &i) {
        return x %= i, *this;
    }
    friend constexpr Zmod operator+(const Zmod i, const Zmod j) {
        return Zmod(i) += j;
    }
    friend constexpr Zmod operator-(const Zmod i, const Zmod j) {
        return Zmod(i) -= j;
    }
    friend constexpr Zmod operator*(const Zmod i, const Zmod j) {
        return Zmod(i) *= j;
    }
    friend constexpr Zmod operator/(const Zmod i, const Zmod j) {
        return Zmod(i) /= j;
    }
    friend constexpr Zmod operator%(const Zmod i, const int j) {
        return Zmod(i) %= j;
    }
    friend constexpr bool operator==(const Zmod i, const Zmod j) {
        return i.val() == j.val();
    }
    friend constexpr bool operator!=(const Zmod i, const Zmod j) {
        return i.val() != j.val();
    }
    friend constexpr bool operator<(const Zmod i, const Zmod j) {
        return i.val() < j.val();
    }
    friend constexpr bool operator>(const Zmod i, const Zmod j) {
        return i.val() > j.val();
    }
};
constexpr int M = MOD[1];
using Z = Zmod<M>;

// 场景: n, m 较小 (< 10^7), 模数 P 是一个大质数。
// O(N) 预处理, O(1) 查询。
struct Comb {
    int n_mx;
    vector<Z> _fac, _invfac;

    Comb() : n_mx{0}, _fac{1}, _invfac{1} {}

    // init函数实现增量式初始化, 避免重复计算
    void init(int m) {
        if (m <= n_mx) return;
        int prev_n = n_mx;
        n_mx = m;
        _fac.resize(n_mx + 1);
        _invfac.resize(n_mx + 1);
        for (int i = prev_n + 1; i <= n_mx; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[n_mx] = _fac[n_mx].inv();
        for (int i = n_mx; i > prev_n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
        }
    }

    // C 和 P 函数内部增加自动初始化
    Z C(int n, int m) {
        if (m < 0 || m > n) return 0;
        if (n > n_mx) init(n);
        return _fac[n] * _invfac[m] * _invfac[n - m];
    }

    Z P(int n, int m) {
        if (m < 0 || m > n) return 0;
        if (n > n_mx) init(n);
        return _fac[n] * _invfac[n - m];
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    vector<i64> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << __builtin_popcountll(a[0] + m) << '\n';
    }

    Comb co;
    Z ans = 0;

    Z p1 = mypow(Z(n - 1), m);
    Z inv_p1 = Z(n - 1).inv();
    for (int k = 0; k <= m; ++k) {
        Z kk = co.C(m, k) * p1;
        i64 delta = 0;
        for (int i = 0; i < n; ++i) {
            delta += __builtin_popcountll(a[i] + k);
        }
        ans += kk * delta;
        if (k < m) {
            p1 *= inv_p1;
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