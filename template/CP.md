# 算法模板库 


- [算法模板库](#算法模板库)
  - [基础算法](#基础算法)
    - [IO](#io)
    - [大整数](#大整数)
    - [进制转换](#进制转换)
    - [离散化](#离散化)
  - [数据结构](#数据结构)
    - [并查集 (DSU) - 路径压缩 + 按秩序合并](#并查集-dsu---路径压缩--按秩序合并)
    - [树状数组](#树状数组)
  - [字符串算法](#字符串算法)
  - [数论](#数论)
    - [快速幂](#快速幂)
    - [逆元](#逆元)
    - [组合数](#组合数)
      - [第一类斯特林数](#第一类斯特林数)
    - [容斥原理](#容斥原理)
  - [图论](#图论)
    - [Dijkstra](#dijkstra)
    - [最小生成树 (MST)](#最小生成树-mst)
      - [Kruskal](#kruskal)
      - [Prim](#prim)
  - [树算法](#树算法)
  - [动态规划](#动态规划)
  - [网络流](#网络流)
  - [匹配算法](#匹配算法)
  - [莫队算法](#莫队算法)
  - [高精度](#高精度)


## 基础算法

### IO
```cpp
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
}
using namespace IO;
```
### 大整数

 

### 进制转换

```cpp
struct converter {
    // mp:  用于将字符（'0'-'9', 'a'-'z', 'a'-'z'）映射为对应的整数（0-61）。
    // mp2: 用于将整数（0-61）映射回对应的字符。
    vector<int> mp;
    vector<char> mp2;

    Converter() : mp(123), mp2(62) {
        // 映射数字 '0' 到 '9'
        for (int i = 0; i < 10; ++i) {
            mp['0' + i] = i;
            mp2[i] = '0' + i;
        }
        // 映射大写字母 'A' 到 'Z'
        for (int i = 0; i < 26; ++i) {
            mp['A' + i] = i + 10;
            mp2[i + 10] = 'A' + i;
        }
        // 映射小写字母 'a' 到 'z'
        for (int i = 0; i < 26; ++i) {
            mp['a' + i] = i + 36;
            mp2[i + 36] = 'a' + i;
        }
    }

    // 转换前进制 转换后进制 要转换的数据
    string solve(int a, int b, const string &s) {
        vector<int> nums, ans;
        for (auto c : s) {
            nums.push_back(mp[c]);
        }
        reverse(nums.begin(), nums.end());
        while (nums.size()) {  // 短除法，将整个大数一直除 b ，取余数
            int remainder = 0;
            for (int i = nums.size() - 1; i >= 0; i--) {
                nums[i] += remainder * a;
                remainder = nums[i] % b;
                nums[i] /= b;
            }
            ans.push_back(remainder);  // 得到余数
            while (nums.size() && nums.back() == 0) {
                nums.pop_back();  // 去掉前导 0
            }
        }
        reverse(ans.begin(), ans.end());

        string restr;
        for (int i : ans) restr += mp2[i];
        return restr;
    }
};
// usage
void solve() {
    Converter con;

    // 16->10
    int ori = 16, tar = 10;
    string num = "1A";

    string ans = con.solve(ori, tar, num);
    cout << ans;
    // 16进制的 "1A" 是 1*16 + 10 = 26
}
```

### 离散化

```cpp
struct Disc {
    vi values; // 存储排序去重后的所有唯一值

    Disc(const vi& initial_data) {
        values = initial_data;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    int get_id(int x) const {
        return lower_bound(values.begin(), values.end(), x) - values.begin() + 1;
    }

    int get_val(int id) const {
        // 在竞赛中，可以不加 assert 以追求极致性能，但加上更安全
        // assert(id >= 1 && id <= values.size());
        return values[id - 1];
    }
    
    vi map_data(const vi& data_to_map) const {
        vi mapped;
        mapped.reserve(data_to_map.size());
        for (int val : data_to_map) {
            mapped.push_back(get_id(val));
        }
        return mapped;
    }

    int size() const {
        return values.size();
    }
};
```


## 数据结构

### 并查集 (DSU) - 路径压缩 + 按秩序合并

```cpp
struct dsu {
    vi fa, sz;

    dsu(int n) : fa(n + 1), sz(n + 1, 1) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        while (x != fa[x]) {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool mg(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        fa[y] = x;
        sz[x] += sz[y];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    int size(int x) {
        return sz[find(x)];
    }
};
```

### 树状数组

```cpp
template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n_) : n(n_), a(n_ + 1, T{}) {}

    void add(int x, const T &v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] = a[i] + v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i];
        }
        return ans;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (x + i <= n && cur + a[x + i] <= k) {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};
```


## 字符串算法
<!-- 在这里开始添加你的“字符串算法”模板，比如KMP、AC自动机、后缀数组等 -->


## 数论

### 快速幂

```cpp
//防爆mul
i64 hmul(i64 a, i64 b) {
    return (i128)a * b % mod;
}

i64 hmul(i64 a, i64 b, i64 m) {
    i64 ans= 0;
    a %= m;
    while (b > 0) {
        if (b & 1) {
            ans = (ans + a) % m;
        }
        a = (a * 2) % m;
        b >>= 1;
    }
    return ans;
}

i64 qpow(i64 a, int b) {
    i64 ans = 1 % mod;
    while (b) {
        if (b & 1) {
            ans = ans * a % mod;
        }
        a = a * a % mod;//a=hmul(a,a)
        b >>= 1;
    }
    return ans;
}
```

### 逆元

```cpp
//费马小定理求逆元（mod必须是质数，且需要满足 x 与nod互质
i64 inverse1(i64 a, i64 n) { 
    return qpow(a, n - 2);
}

//
```

### 组合数

#### 第一类斯特林数

### 容斥原理 

## 图论

### Dijkstra 

```cpp
// 堆优化O(M log N)
struct fdijkstra {
    int n;
    vvp grid;
    vi dist;
    vi fa;  // 存储最短路树中的父节点，用于路径回溯

    fdijkstra(int n_) : n(n_), grid(n_ + 1), dist(n_ + 1), fa(n_ + 1) {}
    // 添加单向边,小心无向图
    void add_edge(int u, int v, int w) {
        grid[u].emplace_back(v, w);
    }
    void run(int start_node) {
        fill(dist.begin(), dist.end(), linf);
        fill(fa.begin(), fa.end(), 0);
        dist[start_node] = 0;

        using Node = pii;  // {distance, vertex}
        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0, start_node});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;

            // 3. 遍历邻接点并松弛
            for (auto& edge : grid[u]) {
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
    vi get_path(int t) {
        vi path;
        if (dist[t] == linf) {
            return path;  // 不可达
        }
        for (; t != 0; t = fa[t]) {
            path.push_back(t);
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
// 朴素：o(n^2)，适用于 m 比较大，n(顶点) 很小的情况
struct sdijkstra {
    int n;
    vii adj;
    vi dist;
    vector<bool> vis;

    sdijkstra(int n_) : n(n_), adj(n_ + 1, vi(n_ + 1, linf)), dist(n_ + 1, linf), vis(n_ + 1, false) {
        fo(i, 1, n) adj[i][i] = 0;
    }
    void add_edge(int u, int v, int w) {
        adj[u][v] = min(adj[u][v], w);
    }
    void run(int st) {
        fill(dist.begin(), dist.end(), linf);
        fill(vis.begin(), vis.end(), false);
        dist[st] = 0;

        fo(i, 1, n) {
            int u = -1;
            fo(j, 1, n) {
                if (!vis[j] && (u == -1 || dist[j] < dist[u])) u = j;
            }

            if (u == -1 || dist[u] >= linf) break;
            vis[u] = true;

            fo(v, 1, n) {
                if (dist[v] > dist[u] + adj[u][v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
};

// usage
void solve() {
    int n, m, s;
    read(n, m, s);  // 读入点数、边数、源点
    fdijkstra dij(n);

    // 2. 添加所有边
    fu(i, 0, m) {
        int u, v, w;
        read(u, v, w);
        dij.add_edge(u, v, w);
        // 如果是无向图, 需额外添加: dij.add_edge(v, u, w);
    }

    dij.run(s);  // 3. 从源点 s 开始运行算法
    // 4. 输出到各个点的最短距离
    fo(i, 1, n) {
        if (dij.dist[i] == linf) {
            write(-1, ' ');
        } else {
            write(dij.dist[i], ' ');
        }
    }
    write('\n');

    // (可选) 打印从源点 s 到终点 n 的路径
    vi path = dij.get_path(n);
    if (!path.empty()) {
        write("Path to ", n, ": ");
        fu(i, 0, path.size()) {
            write(path[i], (i == path.size() - 1 ? "" : " -> "));
        }
        write('\n');
    }
}
```

### 最小生成树 (MST) 

[并查集 (DSU) - 路径压缩 + 按秩序合并](#并查集-dsu---路径压缩--按秩序合并)

#### Kruskal

```cpp
struct mstk {
    struct edge {
        int u, v, w;
        bool operator<(const edge& other) const {
            return w < other.w;
        }
    };

    int n;
    vector<edge> edges;

    mstk(int n_, int m_) : n(n_) {
        edges.reserve(m_);
    }

    void ad(int u, int v, int w) {
        edges.push_back({u, v, w});
    }

    i64 run() {
        sort(edges.begin(), edges.end());
        dsu dt(n);
        i64 totalw = 0;
        int cnt = 0;
        for (const auto& e : edges) {
            if (dt.mg(e.u, e.v)) {
                totalw += e.w;
                cnt++;
            }
        }
        return (cnt == n - 1) ? totalw : -1;
    }
};

// usage
void solve() {
    int n, m;
    read(n, m);

    mstk mst(n, m);

    fu(i, 0, m) {
        int u, v, w;
        read(u, v, w);
        mst.ad(u, v, w);
    }
    i64 ans = mst.run();
}
```

#### Prim
```cpp
struct mstp {
    int n;
    vii adj;
    vi dist;
    vector<bool> vis;

    mstp(int nn) : n(nn), adj(nn + 1, vi(n + 1, linf)), dist(n + 1, linf), vis(n + 1, false) {
        fo(i, 1, n) adj[i][i] = 0;
    }
    void ad(int u, int v, int w) {
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }

    i64 run(int st) {
        dist[st] = 0;
        i64 totalw = 0;
        int cnt = 0;
        fo(i, 1, n) {
            int u = -1;
            fo(j, 1, n) {
                if (!vis[j] && (u == -1 || dist[j] < dist[u])) u = j;
            }
            if (u == -1 || dist[u] >= linf) return -1;  // 不连通
            vis[u] = true;
            totalw += dist[u];
            cnt++;

            fo(v, 1, n) {
                if (!vis[v] && dist[v] > adj[u][v]) {
                    dist[v] = adj[u][v];
                }
            }
        }
        return (cnt == n) ? totalw : -1;
    }
};
```



## 树算法
<!-- 在这里开始添加你的“树算法”模板，比如LCA、点分治、树链剖分等 -->


## 动态规划
<!-- 在这里开始添加你的“动态规划”模板，比如背包DP、区间DP、插头DP等 -->


## 网络流
<!-- 在这里开始添加你的“网络流”模板，比如Dinic、MCMF等 -->


## 匹配算法
<!-- 在这里开始添加你的“匹配算法”模板，比如匈牙利算法、KM算法等 -->


## 莫队算法
<!-- 在这里开始添加你的“莫队算法”模板，比如普通莫队、带修改莫队等 -->


## 高精度
<!-- 在这里开始添加你的“高精度”模板，比如大整数类、分数类等 -->

