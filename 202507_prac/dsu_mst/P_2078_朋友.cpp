#include <bits/stdc++.h>
namespace IO
{
    const int BUF_SIZE = 1 << 22;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE], *p_in = in_buf + BUF_SIZE, *p_out = out_buf;
    char stk[50];

#define gc() (p_in == in_buf + BUF_SIZE ? (fread(in_buf, 1, BUF_SIZE, stdin), p_in = in_buf, *p_in++) : *p_in++)
#define pc(x) (*p_out++ = (x), p_out == out_buf + BUF_SIZE ? (fwrite(out_buf, 1, BUF_SIZE, stdout), p_out = out_buf) : 0)

    template <typename T>
    inline void read(T &x)
    {
        x = 0;
        bool f = false;
        char c = gc();
        while (!isdigit(c))
        {
            if (c == '-')
                f = true;
            c = gc();
        }
        while (isdigit(c))
        {
            x = x * 10 + (c ^ 48);
            c = gc();
        }
        if (f)
            x = -x;
    }

    inline void read(char &c)
    {
        c = gc();
        while (!isgraph(c))
            c = gc();
    }
    inline void read(std::string &s)
    {
        s.clear();
        char c = gc();
        while (!isgraph(c))
            c = gc();
        while (isgraph(c))
        {
            s += c;
            c = gc();
        }
    }
    inline void getline(std::string &s)
    {
        s.clear();
        char c = gc();
        while (c == '\n' || c == '\r')
        { // 吃掉行首的换行符
            c = gc();
        }
        while (c != '\n' && c != '\r' && c != EOF)
        {
            s += c;
            c = gc();
        }
    }
    template <typename T, typename... Args>
    inline void read(T &x, Args &...args)
    {
        read(x);
        read(args...);
    }

    template <typename T>
    inline void write(T x)
    {
        if (x < 0)
        {
            pc('-');
            x = -x;
        }
        if (x == 0)
        {
            pc('0');
            return;
        }
        int top = 0;
        while (x)
        {
            stk[++top] = (x % 10) ^ 48;
            x /= 10;
        }
        while (top)
            pc(stk[top--]);
    }

    inline void write(char c) { pc(c); }
    inline void write(const char *s)
    {
        while (*s)
            pc(*s++);
    }
    inline void write(const std::string &s)
    {
        for (char c : s)
            pc(c);
    }

    template <typename T, typename... Args>
    inline void write(T x, Args... args)
    {
        write(x);
        write(args...);
    }

    struct Flusher
    {
        ~Flusher()
        {
            if (p_out != out_buf)
            {
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
using vpii = vector<pair<i64, i64>>;
#define fo(i, l, r) for (int i = (l); i <= (r); ++i)
#define fu(i, l, r) for (int i = (l); i < (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)

#define int long long

const int M = 1e9 + 7;
const i64 linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxm = 400005;
const int maxn = 40005;

inline pair<vector<int>, int> discretize(const vector<int> &a)
{
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    vector<int> c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    return {c, m};
}
//------------------------------------------------------------------
int fa[maxn], sz[maxn];
int n, m, p, q;
void init()
{
    fo(i, 0, n + m - 1)
    {
        fa[i] = i;
        sz[i] = 1;
    }
}
int find(int x)
{
    if (fa[x] == x)
        return x;
    return fa[x] = find(fa[x]);
}
void mg(int x, int y)
{
    int fx = find(x), fy = find(y);
    if (fx == fy)
        return;
    if (sz[fx] < sz[fy])
        swap(fx, fy);
    fa[fy] = fx;
    sz[fx] += sz[fy];
}
void solve()
{
    read(n, m, p, q);
    init();
    fo(i, 1, p)
    {
        int a, b;
        read(a, b);
        mg(a, b);
    }
    fo(i, 1, q)
    {
        int a, b;
        read(a, b);
        mg(abs(a) + n, abs(b) + n);
    }
    int siz1 = sz[find(1)];
    int siz2 = sz[find(n + 1)];
    write(min(siz1, siz2)), '\n';
}

signed main()
{
    solve();
    return 0;
}