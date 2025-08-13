#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int MOD[] = {998244353, 1000000007};
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr double dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------
// 堆优化O(M log N)
struct Fdijkstra {
    int n;
    vector<vector<pair<int, double>>> adj;
    vector<double> dist;
    vector<int> fa;  // fa 存储最短路树中的父节点，用于路径回溯

    Fdijkstra(int n_) : n(n_), adj(n_ + 1), dist(n_ + 1), fa(n_ + 1) {}

    // 若无向图，需要为两个方向都添加边
    void add_edge(int u, int v, double w) {
        adj[u].emplace_back(v, w);
    }

    void run(int start_node) {
        // 初始化距离为无穷大，父节点为0
        fill(dist.begin(), dist.end(), dinf);
        fill(fa.begin(), fa.end(), 0);
        dist[start_node] = 0.0;

        using Node = pair<double, int>;  // {distance, vertex}

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0.0, start_node});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                auto [v, w] = edge;
                double mnmx = max(dist[u], w);
                if (dist[v] > mnmx) {
                    dist[v] = mnmx;
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

struct Point {
    int x, y;
};
double cal(const Point& a, const Point& b) {
    int dx = a.x - b.x;
    int dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}

void solve() {
    int n;
    int cnt = 1;
    while (cin >> n && n) {
        vector<Point> points(n + 1);
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        Fdijkstra dij(n);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                double w = cal(points[i], points[j]);
                dij.add_edge(i, j, w);
                dij.add_edge(j, i, w);
            }
        }

        dij.run(1);
        cout << "Scenario #" << cnt << '\n';
        cnt++;
        cout << "Frog Distance = " << fixed << setprecision(3) << dij.dist[2] << '\n';
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}