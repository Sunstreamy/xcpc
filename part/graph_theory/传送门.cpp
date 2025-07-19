#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
typedef vector<vector<ll>> vii;
typedef vector<string> vs;
typedef vector<pair<ll, ll>> vpii;
typedef bitset<20> b20;
#define int long long
const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 100005;
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

inline vi discretize(const vi &a)
{
    vi b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    return b;
}

// 0-based
struct fwt
{
    int n;
    vi tree;
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

vpii adj[MAXN + MAXM];
int dist[MAXN + MAXM];
// 优先队列用于Dijkstra
priority_queue<pii, vpii, greater<pii>> pq;

map<int, vpii> edges_by_color;
map<int, vi> nodes_by_color;
map<int, bool> visited_in_color;
map<int, vi> color_adj;
int n, m;

inline void solve()
{
    rd(n), rd(m);

    for (int i = 1; i <= n + m; ++i)
    {
        adj[i].clear();
    }
    edges_by_color.clear();
    nodes_by_color.clear();

    // --- 2. 读取输入并按颜色分组 ---
    for (int i = 0; i < m; ++i)
    {
        int u, v, c;
        rd(u), rd(v), rd(c);
        edges_by_color[c].push_back({u, v});
        nodes_by_color[c].push_back(u);
        nodes_by_color[c].push_back(v);
    }

    // `aux_node_id` 是我们为“协会节点”分配的ID，从 n+1 开始
    int aux_node_id = n;

    // --- 3. 构建新图 ---
    // 遍历每一种颜色
    for (auto const &[color, edges] : edges_by_color)
    {
        // 清理当前颜色子图的数据结构
        color_adj.clear();
        visited_in_color.clear();

        // 构建当前颜色的子图
        for (auto const &edge : edges)
        {
            color_adj[edge.first].push_back(edge.second);
            color_adj[edge.second].push_back(edge.first);
        }

        // 遍历该颜色涉及的所有节点，找连通分量
        for (int start_node : nodes_by_color[color])
        {
            if (!visited_in_color[start_node])
            {
                // 发现一个新的连通分量
                aux_node_id++; // 分配一个新的协会节点ID

                // 用BFS/DFS找出这个连通分量的所有节点
                queue<int> q_component;
                q_component.push(start_node);
                visited_in_color[start_node] = true;

                while (!q_component.empty())
                {
                    int u = q_component.front();
                    q_component.pop();

                    // 建立新图的边
                    // 从遗迹节点 u -> 协会节点 aux_node_id，代价为 1
                    adj[u].push_back({aux_node_id, 1});
                    // 从协会节点 aux_node_id -> 遗迹节点 u，代价为 0
                    adj[aux_node_id].push_back({u, 0});

                    // 继续在颜色子图中扩展
                    for (int v : color_adj[u])
                    {
                        if (!visited_in_color[v])
                        {
                            visited_in_color[v] = true;
                            q_component.push(v);
                        }
                    }
                }
            }
        }
    }

    for (int i = 1; i <= aux_node_id; ++i)
    {
        dist[i] = INF;
    }

    dist[1] = 0;
    pq.push({0, 1}); // {cost, node}

    while (!pq.empty())
    {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u])
        {
            continue;
        }

        if (u == n)
        {
            // 已经找到了到终点的最短路，可以提前结束
            // 因为Dijkstra的性质，第一次从优先队列取出n时，其距离就是最短的
            break;
        }

        for (auto const &edge : adj[u])
        {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << dist[n] << '\n';

    // 清空优先队列，为下一个测试用例做准备
    while (!pq.empty())
    {
        pq.pop();
    }
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int _;
    rd(_);
    while (_--)
    {
        solve();
    }
    return 0;
}