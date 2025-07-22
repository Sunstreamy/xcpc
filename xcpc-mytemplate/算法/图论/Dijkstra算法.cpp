#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int mod = 1e9 + 7;
const int linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxm = 400005;
const int maxn = 200005;

/**
 * @brief 快速 Dijkstra (优先队列优化, O(m log n))
 * @details 适用于稀疏图 (m 与 n 的数量级相近)。这是大多数问题的默认选择。
 */
/**
 * @brief 快速 Dijkstra (优先队列优化, O(m log n))
 * @details 适用于稀疏图 (m 与 n 的数量级相近)。这是大多数问题的默认选择。
 */
namespace FastDijkstra {
    const int MAXN_FAST = 400005; // 最大顶点数

    vpll G[MAXN_FAST];    // 邻接表
    int d[MAXN_FAST];     // d[i]: 从源点到 i 的最短距离
    int p[MAXN_FAST];     // p[i]: 用于路径回溯，记录 i 的前驱节点

    // 初始化函数，用于处理多组测试数据
    void init(int n) {
        // 清理范围可以稍大以确保安全
        for (int i = 0; i <= n + 1; ++i) { G[i].clear(); }
    }

    // 添加单向边
    void add_edge(int u, int v, int w) {
        G[u].emplace_back(v, w);
    }

    // 执行 Dijkstra 算法
    void run(int s, int n) {
        for (int i = 0; i <= n + 1; ++i) { d[i] = linf; p[i] = 0; }
        d[s] = 0;

        priority_queue<pll, vpll, greater<pll>> pq; // 小顶堆
        pq.emplace(0, s);

        while (!pq.empty()) {
            auto [dist, u] = pq.top(); pq.pop();
            if (dist > d[u]) continue; // 如果是旧的、更长的路径，则跳过
            for (auto& edge : G[u]) {
                auto [v, w] = edge;
                if (d[v] > d[u] + w) {
                    d[v] = d[u] + w;
                    p[v] = u;
                    pq.emplace(d[v], v);
                }
            }
        }
    }
} // namespace FastDijkstra


/**
 * @brief 朴素 Dijkstra (邻接矩阵, O(n^2))
 * @details 适用于稠密图 (m 接近 n^2) 且 n 较小 (例如 n <= 2000)。
 */
namespace SimpleDijkstra {
    const int MAXN_SIMPLE = 2005; // 此版本最大顶点数

    int w[MAXN_SIMPLE][MAXN_SIMPLE]; // 邻接矩阵
    int d[MAXN_SIMPLE];              // 最短距离数组
    bool vis[MAXN_SIMPLE];           // 标记数组

    // 注意: 初始化逻辑已包含在 run 函数内部，但需要手动填充邻接矩阵 w
    void run(int s, int n) {
        for (int i = 0; i <= n + 1; ++i) { d[i] = linf; vis[i] = false; }
        d[s] = 0;
        for (int i = 1; i <= n; ++i) {
            int u = -1;
            // 找到未访问节点中距离最小的
            for (int j = 1; j <= n; ++j) {
                if (!vis[j] && (u == -1 || d[j] < d[u])) u = j;
            }
            if (u == -1 || d[u] == linf) break; // 找不到可达节点，退出
            vis[u] = true;
            // 用找到的节点 u 去更新其他节点
            for (int v = 1; v <= n; ++v) {
                d[v] = min(d[v], d[u] + w[u][v]);
            }
        }
    }
} // namespace SimpleDijkstra

// =================== 用法示例 ===================
// 在解题时，可以将对应的函数复制到主文件的 solve 函数中，或直接修改使用。

/**
 * @brief FastDijkstra (稀疏图) 的使用示例
 */
void solve_fast() {
    int n, m, s;
    scanf("%lld %lld %lld", &n, &m, &s); // 推荐使用您自己的快速读入 `rd()`

    // 对于多组测试数据，初始化是必须的
    FastDijkstra::init(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        FastDijkstra::add_edge(u, v, w);
        // 如果是无向图，请取消下面这行代码的注释
        // FastDijkstra::add_edge(v, u, w);
    }

    FastDijkstra::run(s, n);

    for (int i = 1; i <= n; ++i) {
        // 如果不可达，通常输出 -1
        printf("%lld ", (FastDijkstra::d[i] == linf) ? -1 : FastDijkstra::d[i]);
    }
    printf("\n");
}


/**
 * @brief SimpleDijkstra (稠密图) 的使用示例
 */
void solve_simple() {
    int n, m, s;
    scanf("%lld %lld %lld", &n, &m, &s);

    // 第1步: 初始化邻接矩阵
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= n; ++j) {
            SimpleDijkstra::w[i][j] = (i == j) ? 0 : linf;
        }
    }

    // 第2步: 读入边并填充邻接矩阵
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        // 处理重边，取权值最小的
        SimpleDijkstra::w[u][v] = min(SimpleDijkstra::w[u][v], (int)w);
        // 如果是无向图，请取消下面这行代码的注释
        // SimpleDijkstra::w[v][u] = min(SimpleDijkstra::w[v][u], (int)w);
    }

    // 第3步: 运行算法
    SimpleDijkstra::run(s, n);

    // 第4步: 输出结果
    for (int i = 1; i <= n; ++i) {
        printf("%lld ", (SimpleDijkstra::d[i] == linf) ? -1 : SimpleDijkstra::d[i]);
    }
    printf("\n");
}

// =================== 模块结束 ===================