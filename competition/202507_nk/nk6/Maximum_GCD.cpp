#pragma GCC optimize(2)
#include <bits/stdc++.h>
namespace IO {
constexpr int BUF_SIZE = 1 << 22;
char in_buf[BUF_SIZE], out_buf[BUF_SIZE], *p_in = in_buf + BUF_SIZE, *p_out = out_buf;
char stk[50];

#define gc() (p_in == in_buf + BUF_SIZE ? (fread(in_buf, 1, BUF_SIZE, stdin), p_in = in_buf, *p_in++) : *p_in++)
#define pc(x) \
    (*p_out++ = (x), p_out == out_buf + BUF_SIZE ? (fwrite(out_buf, 1, BUF_SIZE, stdout), p_out = out_buf) : 0)

template <typename T>
inline void read(T &x) {
    x = 0;
    bool f = false;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f = true;
        c = gc();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = gc();
    }
    if (f) x = -x;
}
inline void read(char &c) {
    c = gc();
    while (!isgraph(c)) c = gc();
}
inline void read(std::string &s) {
    s.clear();
    char c = gc();
    while (!isgraph(c)) c = gc();
    while (isgraph(c)) {
        s += c;
        c = gc();
    }
}
inline void getline(std::string &s) {
    s.clear();
    char c = gc();
    while (c == '\n' || c == '\r') {
        c = gc();
    }
    while (c != '\n' && c != '\r' && c != EOF) {
        s += c;
        c = gc();
    }
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args) {
    read(x);
    read(args...);
}
template <typename T>
inline void write(T x) {
    if (x < 0) {
        pc('-');
        x = -x;
    }
    if (x == 0) {
        pc('0');
        return;
    }
    int top = 0;
    while (x) {
        stk[++top] = (x % 10) ^ 48;
        x /= 10;
    }
    while (top) pc(stk[top--]);
}
inline void write(char c) {
    pc(c);
}
inline void write(const char *s) {
    while (*s) pc(*s++);
}
inline void write(const std::string &s) {
    for (char c : s) pc(c);
}
template <typename T, typename... Args>
inline void write(T x, Args... args) {
    write(x);
    write(args...);
}
struct Flusher {
    ~Flusher() {
        if (p_out != out_buf) {
            fwrite(out_buf, 1, p_out - out_buf, stdout);
            p_out = out_buf;
        }
    }
} flusher;

#undef gc
#undef pc
}  // namespace IO
using namespace std;
using namespace IO;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;
using vi = vector<i64>;
using vii = vector<vector<i64>>;
using pii = pair<i64, i64>;
using vp = vector<pair<i64, i64>>;
using vvp = vector<vector<pair<i64, i64>>>;
#define fo(i, l, r) for (int i = (l); i <= (r); ++i)
#define fu(i, l, r) for (int i = (l); i < (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)
#define int long long

constexpr int M = 998244353;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------

vi get_divs(int n) {
    vi divs;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            divs.push_back(i);
            if (i * i != n) {
                divs.push_back(n / i);
            }
        }
    }
    return divs;
}

bool is_achievable(int d, int n, const vector<int> &a) {
    int fit_fail = -1, lst_fail = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] % d != 0) {
            if (fit_fail == -1) {
                fit_fail = i;
            }
            lst_fail = i;
        }
    }

    // all eles are d's div
    if (fit_fail == -1) return true;

    int yu = a[fit_fail] % d;
    for (int i = fit_fail; i <= lst_fail; ++i) {
        if (a[i] % d != yu) {
            return false;
        }
    }
    return true;
}

void solve() {
    int n;
    read(n);
    vi a(n);
    bool flag = true;
    for (int i = 0; i < n; ++i) {
        read(a[i]);
        if (i > 0 && a[i] != a[0]) {
            flag = false;
        }
    }

    if (n <= 1 || (n > 1 && flag)) {
        write(0, '\n');
        return;
    }

    int ans = 1;

    // op1 all
    int g_full = 0;
    for (int i = 1; i < n; ++i) {
        g_full = gcd(g_full, abs(a[i] - a[0]));
    }
    ans = max(ans, g_full);

    // op2
    // must be divs
    set<int> cand_st;
    vi divs1 = get_divs(a[0]);
    vi divsn = get_divs(a[n - 1]);
    for (int d : divs1) cand_st.insert(d);
    for (int d : divsn) cand_st.insert(d);

    vi alcand(cand_st.begin(), cand_st.end());
    sort(alcand.rbegin(), alcand.rend());

    for (int d : alcand) {
        if (d <= ans) break;
        if (is_achievable(d, n, a)) ans = d;
    }
    write(ans, '\n');
}

signed main() {
    int _;
    read(_);
    while (_--) solve();
    return 0;
}