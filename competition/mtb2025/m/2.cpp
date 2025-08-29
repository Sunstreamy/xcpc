#include <bits/stdc++.h>
using namespace std;
using i64 = long long; // 使用 i64 别名，虽然本题用不到 long long
constexpr int MOD[] = {998244353, 1000000007}; // 模板中的常量，本题用不到

void solve()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> grid[i];
    }

    // dist[i][j] 存储到达 (i, j) 所需的最小魔法次数
    vector<vector<int>> dist(n, vector<int>(m, 1e9));

    // 使用双端队列实现 0-1 BFS
    deque<pair<int, int>> dq;

    // 初始化起点
    dist[0][0] = 0;
    dq.push_front({0, 0});

    // 定义四个方向的移动：上, 下, 左, 右
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};
    char dir_char[] = {'U', 'D', 'L', 'R'};

    while (!dq.empty())
    {
        auto [r, c] = dq.front();
        dq.pop_front();

        // 尝试向四个方向移动
        for (int i = 0; i < 4; ++i)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            // 检查是否越界
            if (nr < 0 || nr >= n || nc < 0 || nc >= m)
            {
                continue;
            }

            // 计算移动代价 (cost)
            // 如果当前格子的方向就是我们要走的方向，代价为0，否则为1
            int cost = (grid[r][c] == dir_char[i]) ? 0 : 1;

            // 松弛操作：如果找到了更短的路径
            if (dist[r][c] + cost < dist[nr][nc])
            {
                dist[nr][nc] = dist[r][c] + cost;
                // 根据代价决定入队位置
                if (cost == 0)
                {
                    dq.push_front({nr, nc});
                }
                else
                {
                    dq.push_back({nr, nc});
                }
            }
        }
    }

    // 检查到达终点的最小魔法次数是否在 k 的限制内
    if (dist[n - 1][m - 1] <= k)
    {
        cout << "YES\n";
    }
    else
    {
        cout << "NO\n";
    }
}

int main()
{
    // 优化输入输出
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int _;
    cin >> _; // 读取测试数据组数
    while (_--)
        solve(); // 循环处理每组数据
    return 0;
}