#include <bits/stdc++.h>
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

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i) {
        cin >> grid[i];
    }

    vector<vector<int>> dist(n, vector<int>(m, inf));
    dist[0][0] = 0;

    // 0 - 1 BFS 使用双端队列 std::deque 来巧妙地维持节点的“代价顺序”。 回顾一下规则：
    //         如果移动代价是 0，将新节点加入队头。 如果移动代价是 1，将新节点加入队尾。
    //         这相当于创建了一个隐式的优先级。
    //             加入队头（代价0）：
    //                 就像让这个节点“插队”一样。我们告诉算法：“嘿，这个节点非常‘近’，代价很低，请立刻处理它，以及从它出发的其他代价为0的路径。”
    //                     加入队尾（代价1）：
    //                     就像正常排队。我们说：“这个节点需要花费代价才能到达，优先级较低，把它放到后面，等我们处理完所有更优的节点再说。”

    deque<pair<int, int>> dq;
    dq.push_front({0, 0});

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    char dir[] = {'U', 'D', 'L', 'R'};

    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                continue;
            }
            int cost = (grid[x][y] == dir[i]) ? 0 : 1;
            if (dist[x][y] + cost < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + cost;
                if (cost == 0) {
                    dq.push_front({nx, ny});
                } else {
                    dq.push_back({nx, ny});
                }
            }
        }
    }

    if (dist[n - 1][m - 1] <= k) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while (_--) solve();

    return 0;
}