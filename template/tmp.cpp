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
    while (c == '\n' || c == '\r') {  // 吃掉行首的换行符
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
}  
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
#define fd(i, r, l) for (int i = (r); i >= (l); --i)

constexpr int M = 1e9 + 7;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------

void solve() {

}

int main() {
    int _;
    read(_);
    while (_--) solve();
    return 0;
}