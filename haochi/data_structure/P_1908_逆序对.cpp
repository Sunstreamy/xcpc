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

inline pair<vl, int> discretize(const vl &a)
{
    vl b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    vl c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    return {c, m};
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

template <typename T>
struct Fenwick
{
    int n;
    std::vector<T> a;

    Fenwick(int n_ = 0)
    {
        init(n_);
    }

    void init(int n_)
    {
        n = n_;
        a.assign(n + 1, T{});
    }

    void add(int x, const T &v)
    {
        for (int i = x; i <= n; i += i & -i)
        {
            a[i] = a[i] + v;
        }
    }

    T sum(int x)
    {
        T ans{};
        for (int i = x; i > 0; i -= i & -i)
        {
            ans = ans + a[i];
        }
        return ans;
    }

    T rangeSum(int l, int r)
    {
        return sum(r) - sum(l - 1);
    }

    int select(const T &k)
    {
        int x = 0;
        T cur{};
        for (int i = 1 << std::__lg(n); i; i >> 1)
        {
            if (x + i <= n && cur + a[x + i] <= k)
            {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};
//------------------------------------------------------------------

int n;
vl a;
void solve()
{
    rd(n);
    a.resize(n);
    for (int i = 0; i < n; i++)
        rd(a[i]);
    auto [tmp, sz] = discretize(a);
    Fenwick<int> ft(sz);
    int ans = n * (n - 1) / 2;
    for (int i = 0; i < n; i++)
    {
        ans -= ft.sum(tmp[i]);
        ft.add(tmp[i], 1);
    }
    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
