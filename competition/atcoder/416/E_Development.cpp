#pragma GCC optimize(2)
#include <bits/stdc++.h>
namespace IO
{
    const int BUF_SIZE = 1 << 22;
    char in_buf[BUF_SIZE], out_buf[BUF_SIZE], *p_in = in_buf + BUF_SIZE, *p_out = out_buf;
    char stk[25];

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
using vi = vector<int>;
using vii = vector<vector<int>>;
using pii = pair<int, int>;
using vpii = vector<pair<int, int>>;
#define fo(i, l, r) for (int i = (l); i <= (r); ++i)
#define fu(i, l, r) for (int i = (l); i < (r); ++i)
#define fd(i, r, l) for (int i = (r); i >= (l); --i)

#define int long long

const int mod = 1e9 + 7;
const int lnf = 0x3f3f3f3f3f3f3f3fLL;
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
int n, m;
int dist[505][505];
int k, t;
int ans = 0;
void upd(int u, int v, int &old, int nw)
{
    if (nw < old)
    {
        if (u < n && v < n)
        {
            if (old == lnf)
                ans += nw;
            else
                ans -= old - nw;
        }
        old = nw;
    }
}

void solve()
{
    read(n, m);
    ++n;

    fo(i, 1, n)
        fo(j, 1, n)
    {
        dist[i][j] = (i == j) ? 0 : lnf;
    }
    fo(i, 1, m)
    {
        int u, v, w;
        read(u, v, w);
        dist[u][v] = min(dist[u][v], 2 * w);
        dist[v][u] = min(dist[v][u], 2 * w);
    }

    read(k, t);
    fo(i, 1, k)
    {
        int d;
        read(d);
        dist[d][n] = min(dist[d][n], t);
        dist[n][d] = min(dist[n][d], t);
    }
    // floyd
    fo(k, 1, n) fo(i, 1, n) fo(j, 1, n)
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);

    fo(i, 1, n - 1) fo(j, 1, n - 1)
    {
        if (dist[i][j] < lnf)
            ans += dist[i][j];
    }
    int q;
    read(q);
    while (q--)
    {
        int op;
        read(op);
        if (op == 1)
        {
            int x, y;
            int tt;
            read(x, y, tt);
            upd(x, y, dist[x][y], tt * 2);
            upd(x, y, dist[y][x], tt * 2);

            fo(i, 1, n) fo(j, 1, n) upd(i, j, dist[i][j], dist[i][x] + dist[x][j]);
            fo(i, 1, n) fo(j, 1, n) upd(i, j, dist[i][j], dist[i][y] + dist[y][j]);
        }
        else if (op == 2)
        {
            int x;
            read(x);
            // 把城市x加入到“可通过最近机场中转达的城市中（以t为记录）”
            upd(x, n, dist[x][n], t);
            upd(n, x, dist[n][x], t);

            // 因为刚加入新机场，机场网络更新（与城市x可以通过飞机到达的）
            fo(i, 1, n) fo(j, 1, n) upd(i, j, dist[i][j], dist[i][n] + dist[n][j]);

            // 更新有关城市x的所有路径（因为城市x不一定与所有城市都是可以通过机场抵达的）
            fo(i, 1, n) fo(j, 1, n) upd(i, j, dist[i][j], dist[i][x] + dist[x][j]);
        }
        else
            write(ans / 2, '\n');
    }
}

signed main()
{
    solve();
    return 0;
}