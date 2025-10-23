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
}  // namespace IO
using namespace IO;
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
// 堆优化O(M log N)
struct Fdijkstra {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<i64> dist;
    vector<int> fa;  // fa 存储最短路树中的父节点，用于路径回溯

    Fdijkstra(int n_) : n(n_), adj(n_ + 1), dist(n_ + 1), fa(n_ + 1) {}

    // 若无向图，需要为两个方向都添加边
    void ad(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    void run(int st) {
        // 初始化距离为无穷大，父节点为0,从不同起点跑一次都要fill一次
        fill(dist.begin(), dist.end(), linf);
        fill(fa.begin(), fa.end(), 0);
        dist[st] = 0;

        using Node = pair<i64, int>;  // {distance, vertex}

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0, st});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            for (const auto &edge : adj[u]) {
                auto [v, w] = edge;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    fa[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // 获取到终点 t 的最短路径
    vector<int> get_path(int t) {
        vector<int> path;

        if (dist[t] == linf) {
            return path;  // 不可达
        }

        // 通过 fa 数组从终点回溯到起点，构建路径
        // 循环在 t 变为 0 时终止（起点的父节点被初始化为0）
        for (; t != 0; t = fa[t]) {
            path.push_back(t);
        }

        // 因为路径是反向构建的（从终点到起点），所以需要反转
        reverse(path.begin(), path.end());
        return path;
    }
};

void solve() {
    int p, q;
    read(p, q);
    Fdijkstra dij1(p);
    Fdijkstra dij2(p);
    for (int i = 0; i < q; ++i) {
        int u, v, w;
        read(u, v, w);
        dij1.ad(u, v, w);
        dij2.ad(v, u, w);
    }
    dij1.run(1);
    dij2.run(1);
    int ans = 0;
    for (int i = 1; i <= p; ++i) {
        ans += dij1.dist[i];
        ans += dij2.dist[i];
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    read(_);
    while (_--) solve();

    return 0;
}