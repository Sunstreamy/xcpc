#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pair<ll, ll>> vpll;
typedef vector<vector<ll>> vll;
typedef vector<string> vs;
typedef vector<char> vc;
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

// 1-based
struct fwt
{
    int n;
    vl tree;
    fwt(int size) : n(size), tree(size + 1, 0) {}

    // 单点更新：在位置 idx 加上 delta (idx 是 1-based)
    void update(int idx, int delta)
    {
        // 外部传入的 idx 已经是 1-based，直接使用
        for (; idx <= n; idx += idx & -idx)
            tree[idx] += delta;
    }

    // 前缀和查询：查询区间 [1, idx] 内的和 (idx 是 1-based)
    int query(int idx)
    {
        // 如果 idx < 1, 循环不会执行，自动返回 0
        int sum = 0;
        // 外部传入的 idx 已经是 1-based，直接使用
        for (; idx > 0; idx -= idx & -idx)
            sum += tree[idx];
        return sum;
    }

    // (可选的) 辅助函数：查询区间 [l, r] 的和
    int query_range(int l, int r)
    {
        if (l > r)
            return 0;
        return query(r) - query(l - 1);
    }
};

// 默认功能：区间求和，单点修改
// 使用 1-based 索引
struct segtrnode
{
    ll v;
    ll lenl;
    ll lenr;
    char lc;
    char rc;
    int len;
};
segtrnode merge(segtrnode &l, segtrnode &r)
{
    if (l.lc == 0)
        return r;
    if (r.lc == 0)
        return l;
    segtrnode res;
    res.len = l.len + r.len;
    res.lc = l.lc, res.rc = r.rc;
    res.lenl = l.lenl, res.lenr = r.lenr;
    res.v = max(l.v, r.v);
    if (r.lc == l.rc)
    {
        res.v = max(res.v, l.lenr + r.lenl);
        if (l.lenl == l.len)
            res.lenl += r.lenl;
        if (r.lenr == r.len)
            res.lenr += l.lenr;
    }
    return res;
}

struct segtr
{
    int n;
    vector<segtrnode> tree;
    vector<char> &arr;

    segtr(int size, vector<char> &data) : n(size), arr(data)
    {
        tree.resize(4 * n + 5);
        if (n > 0)
            build(1, 1, n);
    }

    void push_up(int u)
    {
        tree[u] = merge(tree[u << 1], tree[u << 1 | 1]); // 编号为 u 的员工，他的左侧直属下属的编号永远是 2*u，右侧直属下属的编号永远是 2*u+1”。
    }

    void build(int u, int l, int r)
    {
        tree[u].len = r - l + 1; // 初始化len
        if (l == r)
        {
            tree[u] = {1, 1, 1, arr[l], arr[l], 1};
            return;
        }
        int m = (l + r) >> 1;
        build(u << 1, l, m);
        build(u << 1 | 1, m + 1, r);
        push_up(u);
    }

    void update(int u, int l, int r, int pos, char val)
    {
        if (l == r)
        {
            tree[u] = {1, 1, 1, val, val, 1};
            arr[pos] = val; // 同步更新原数组
            return;
        }
        int m = (l + r) >> 1;
        if (pos <= m)
        {
            update(u << 1, l, m, pos, val);
        }
        else
        {
            update(u << 1 | 1, m + 1, r, pos, val);
        }
        push_up(u);
    }

    segtrnode query(int u, int l, int r, int ql, int qr)
    {
        if (ql <= l && r <= qr)
        {
            return tree[u];
        }
        int m = (l + r) >> 1;
        if (qr <= m)
        {
            return query(u << 1, l, m, ql, qr);
        }
        else if (ql > m)
        {
            return query(u << 1 | 1, m + 1, r, ql, qr);
        }
        else
        {
            segtrnode left_res = query(u << 1, l, m, ql, qr);
            segtrnode right_res = query(u << 1 | 1, m + 1, r, ql, qr);
            return merge(left_res, right_res);
        }
    }

    // 公共接口
    void update(int pos, char val)
    {
        update(1, 1, n, pos, val);
    }

    ll query(int l, int r)
    {
        if (l > r)
            return 0;
        return query(1, 1, n, l, r).v;
    }
};

//------------------------------------------------------------------
ll n, q;
string s;

void solve()
{
    cin >> n >> q;
    cin >> s;
    vc a(n + 1);
    for (int i = 0; i < n; i++)
    {
        a[i + 1] = s[i];
    }
    segtr tr(n, a);
    for (int i = 0; i < q; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
        {
            int pos;
            char c;
            cin >> pos >> c;
            tr.update(pos, c);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << tr.query(l, r) << '\n';
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
