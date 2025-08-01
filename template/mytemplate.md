# 算法模板库 


- [算法模板库](#算法模板库)
  - [基础算法](#基础算法)
    - [离散化](#离散化)
  - [数据结构](#数据结构)
    - [并查集 (DSU) - 路径压缩 + 按秩序合并](#并查集-dsu---路径压缩--按秩序合并)
    - [树状数组](#树状数组)
  - [字符串算法](#字符串算法)
  - [数论](#数论)
    - [快速幂](#快速幂)
    - [逆元](#逆元)
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
  - [人工智能](#人工智能)


## 基础算法

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
i64 qmul(i64 a, i64 b) {
    return (i128)a * b % mod;
}

i64 mulh(i64 a, i64 b) {//手写乘法
    i64 ans = 0;
    a %= mod;
    while (b > 0) {
        if (b & 1) {
            ans = (ans + a) % mod;
        }
        a = (a * 2) % mod;
        b >>= 1;
    }
    return ans;
}
i64 qpow(i64 a, int m) {
    i64 ans = 1;
    while (m) {
        if (m & 1) ans = ans * a % mod;
        a = a * a % mod;//a=mulh(a,a)
        m >>= 1;
    }
    return ans;
}
```

### 逆元
```cpp
//费马小定理求逆元（MOD$ 必须是质数，且需要满足 x 与nod互质
i64 inverse1(i64 a, i64 n) { 
    return qpow(a, n - 2);
}

//
```

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

    mstk(int n_,int m_):n(n_){
        edges.reserve(m_);
    }

    void ad(int u, int v, int w) {
        edges.emplace_back(u, v, w);
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

    fu(i,0,m){
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


## 人工智能
<!-- 在这里开始添加你的“人工智能”模板，比如Alpha-Beta剪枝、K-Means等 -->