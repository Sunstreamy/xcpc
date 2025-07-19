#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pair<ll, ll>> vpll;
typedef vector<vector<ll>> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 400005;
const int MAXM = 200005;

inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}

inline vl discretize(const vl &a)
{
    vl b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    return b;
}
/**
 * @brief dijkstra 算法模板 (邻接表 + 优先队列)
 * @param n 节点总数 (最大节点的编号 + 1)
 * @param adj 邻接表，adj[u] 存储从 u 出发的所有边 {v, w}
 * @param start_node 起点
 * @return vector<long long> 包含从起点到所有节点的最短距离。如果某节点不可达，其距离为无穷大。
 */
vl dijkstra(int N, const vector<vector<pll>> &adj, int start_node)
{
    // 1. 初始化
    vl dist(N + 1, numeric_limits<int>::max());

    // 优先队列，用于找出当前已知路径中距离最短的节点
    // greater<> 使其成为一个小顶堆，每次都能取出距离最小的 State
    // 使用 pair 来存储优先队列中的状态，第一个元素是距离，第二个元素是节点编号
    priority_queue<pll, vector<pll>, greater<pll>> pq;

    // 2. 设置起点
    dist[start_node] = 0;
    pq.push({0, start_node}); // 将起点放入优先队列 {距离, 节点}

    // 3. 主循环
    while (!pq.empty())
    {
        // 取出当前最优节点（距离最短）
        int current_dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        // 如果当前取出的距离比已经记录的距离要大，说明这是一条被覆盖的、
        // 更长的旧路径。我们直接跳过，避免不必要的计算。
        if (current_dist > dist[u])
        {
            continue;
        }

        // 4. 松弛操作 (Relaxation)
        // 遍历从 u 出发的所有边
        for (const auto &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;

            // 如果通过 u 到达 v 的路径比已知的到 v 的路径更短
            if (dist[u] + weight < dist[v])
            {
                // 更新到 v 的最短距离
                dist[v] = dist[u] + weight;
                // 将这个更优的状态放入优先队列
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

// 0-based
struct fwt
{
    int n;
    vl tree;
    fwt(int size) : n(size), tree(size + 1, 0) {}

    // 单点更新：在位置 idx 加上 delta (idx 是 0-based)
    void update(int idx, int delta)
    {
        for (++idx; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }

    // 前缀和查询：查询区间 [0, idx] 内的和 (idx 是 0-based)
    int query(int idx)
    {
        if (idx < 0)
            return 0;
        int sum = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            sum += tree[idx];
        return sum;
    }
};

//------------------------------------------------------------------

void solve()
{
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
