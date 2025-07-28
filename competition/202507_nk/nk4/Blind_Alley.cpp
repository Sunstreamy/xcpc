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
const int linf = 0x3f3f3f3f3f3f3f3fLL;
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
int check(int x, int y)
{
    if (x == -1 || y == -1)
        return -1;
    if (x == -2 || y == -2)
        return -2;
    return max(x, y);
}
void solve()
{
    int n, m, k;
    read(n, m, k);
    vector<string> grid(n);
    fu(i, 0, n)
        read(grid[i]);
    vi dp(n, -2);
    fd(j, m - 2, 0)
    {
        fu(i, 0, n)
        {
            if (grid[i][j + 1] == '1')
            {
                // 如果右边是墙，那从水平方向看，此路不通。
                // 它的“连续右行距离”是0。我们先标记为 0。
                // 别担心，它等下还有机会被邻居拯救。
                dp[i] = 0;
            }
            else
            {
                // 如果右边不是墙，那它就有希望！
                // 我们看看右边格子的标签(dp[i]里现在存的是j+1列的标签)
                if (dp[i] >= 0)
                {
                    // 如果右边是一个“未决的好路”(>=0)，那从我这里出发，
                    // “连续右行距离”就比它多1。
                    dp[i]++;
                }
                // 如果右边是-1或-2，说明是陷阱或死路，那继承过来就行，状态不变。
            }
            // 关键的“审判时刻”！
            if (dp[i] == k)
            {
                dp[i] = -1;
            }
        }
        // --- 阶段二：最终裁决（上下求援，垂直传播）---
        // 现在，让 j 列内部的格子们开个会，共享一下信息
        // 我们需要一个辅助函数 check 来决定哪个消息更好
        fu(i, 0, n - 1)
        {
            if (grid[i][j] != '1')
            {
                // 让我的下邻居，更新成“它自己”和“我”的状态里，更好的那一个
                dp[i + 1] = check(dp[i + 1], dp[i]);
            }
        }
        fd(i, n - 1, 1)
        {
            if (grid[i][j] != '1')
            {
                // 让我的上邻居，更新成“它自己”和“我”的状态里，更好的那一个
                dp[i - 1] = check(dp[i - 1], dp[i]);
            }
        }
    }

    write((dp[0] == -1) ? "Yes\n" : "No\n");
}

signed main()
{
    int _;
    read(_);
    while (_--)
        solve();
    return 0;
}