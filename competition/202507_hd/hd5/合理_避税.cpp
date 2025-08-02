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
using u128 = __uint128_t;  // 使用无符号128位整数
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

constexpr int M = 1e9 + 7;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------

i64 n, m, k, p;
vi a;

bool check(i64 D) {
    if (D == 0) return m <= 0;

    // pay times
    u128 all = (u128)D * p;
    u128 k_part = 0;
    vi remains;
    u128 mx = 0;

    for (i64 val : a) {
        i64 t = val / k;
        if (D <= t) {
            k_part += D;
        } else {
            k_part += t;
            if (val % k > 0) {
                remains.push_back(val % k);
            }
        }
    }

    u128 k_block = min(k_part, all);
    mx += k_block * k;

    u128 rem = all - k_block;

    if (rem > 0 && !remains.empty()) {
        if (rem >= remains.size()) {
            for (i64 r : remains) {
                mx += r;
            }
        } else {
            nth_element(remains.begin(), remains.begin() + rem - 1, remains.end(), greater<i64>());
            for (int i = 0; i < rem; ++i) {
                mx += remains[i];
            }
        }
    }

    return mx >= (u128)m;
}

void solve() {
    read(n, m, k, p);
    a.resize(n);
    for (int i = 0; i < n; ++i) {
        read(a[i]);
    }

    i64 l = 1, r = 1e10, ans = r;
    while (l <= r) {
        i64 mid = l + (r - l) / 2;
        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    write(ans, '\n');
}

signed main() {
    int _;
    read(_);
    while (_--) solve();
    return 0;
}