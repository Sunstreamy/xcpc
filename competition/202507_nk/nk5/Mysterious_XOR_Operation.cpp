#pragma GCC optimize(2)
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
const int maxn = 200005;

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
bool od(i64 num, int k)
{
    if (k == 0)
        return false;
    // 获取 num 低于 k 的所有位
    i64 mask = (1LL << k) - 1;
    i64 lower_k_bits = num & mask;

    // 计算这些位中 1 的数量
    int count = __builtin_popcountll(lower_k_bits);

    // 返回数量是否为奇数
    return (count % 2 != 0);
}

void solve()
{
    int n;
    read(n);
    vi a(n);
    int ans = 0;
    fo(i, 0, n - 1)
    {
        read(a[i]);
    }
    fo(k, 0, 30)
    {
        int cnt0_1 = 0, cnt0_2 = 0, cnt1_1 = 0, cnt1_2 = 0;

        for (auto x : a)
        {
            if ((x >> k) & 1)
            {
                if (od(x, k))
                    cnt1_1++;
                else
                    cnt1_2++;
            }
            else
            {
                if (od(x, k))
                    cnt0_1++;
                else
                    cnt0_2++;
            }
        }
        int nn = (cnt0_1 * cnt1_1) + (cnt0_2 * cnt1_2);
        ans += (1 << k) * nn;
    }
    write(ans, '\n');
}

signed main()
{
    solve();
    return 0;
}
