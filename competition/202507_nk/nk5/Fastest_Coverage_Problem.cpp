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
int n, m;
vii dist_a;

bool check(int T)
{
    // 转换坐标系，变曼哈顿距离为切比雪夫距离，令u=x+y 和 v=x-y
    i64 min_sum = linf, max_sum = -linf;   // for x+y
    i64 min_diff = linf, max_diff = -linf; // for x-y
    bool flag = false;
    fo(i, 0, n - 1)
    {
        fo(j, 0, m - 1)
        {
            if (dist_a[i][j] > T)
            {
                flag = true;
                i64 u = i + j;
                i64 v = i - j;
                min_sum = min(min_sum, u);
                max_sum = max(max_sum, u);
                min_diff = min(min_diff, v);
                max_diff = max(max_diff, v);
            }
        }
    }
    if (!flag)
        return true;

    i64 L_u = max_sum - T;
    i64 R_u = min_sum + T;
    i64 L_v = max_diff - T;
    i64 R_v = min_diff + T;

    if (L_u > R_u || L_v > R_v)
        return false;

    // 遍历交集的所有可能的 (pu, pv)
    fo(pu, L_u, R_u)
    {
        //  pu 和 pv 的奇偶性必须相同，因为 pu+pv=2x, pu-pv=2y
        // 找到一个 pu，检查对应的 pv 区间内是否有奇偶性相同的数即可
        i64 start_v = L_v;
        if ((pu % 2 + 2) % 2 != (start_v % 2 + 2) % 2)
            start_v++;

        if (start_v <= R_v)
            return true;
    }
    return false;
}

void solve()
{
    read(n, m);

    vii grid(n, vi(m));
    vpii black_cells;

    fo(i, 0, n - 1)
    {
        fo(j, 0, m - 1)
        {
            read(grid[i][j]);
            if (grid[i][j] == 1)
            {
                black_cells.push_back({i, j});
            }
        }
    }

    if (black_cells.empty())
    {
        int best = n + m;
        fo(i, 0, n - 1)
        {
            fo(j, 0, m - 1)
            {
                int tt = 0;
                tt = max(tt, i + j);
                tt = max(tt, i + (m - 1 - j));
                tt = max(tt, (n - 1 - i) + j);
                tt = max(tt, (n - 1 - i) + (m - 1 - j));
                best = min(best, tt);
            }
        }
        write(best, '\n');
        return;
    }

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // 多源BFS计算每个位置到最近黑色单元格的距离
    auto bfs = [&](vpii sources) -> vii
    {
        vii dist(n, vi(m, -1));
        queue<pii> q;

        for (auto [x, y] : sources)
        {
            dist[x][y] = 0;
            q.push({x, y});
        }

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            fo(d, 0, 3)
            {
                int nx = x + dx[d];
                int ny = y + dy[d];

                if (nx >= 0 && nx < n && ny >= 0 && ny < m && dist[nx][ny] == -1)
                {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return dist;
    };

    dist_a = bfs(black_cells);

    int l = 0, r = n + m, ans = n + m;
    while (l <= r)
    {
        int mid = l + r >> 2;
        if (check(mid))
        {
            ans = mid;
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    write(ans, '\n');
}

signed main()
{
    solve();
    return 0;
}