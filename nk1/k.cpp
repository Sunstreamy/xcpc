#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <utility>
#include <algorithm>

int main()
{
    // 使用快速I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // 邻接表: adj[u][k-1] 代表从u房走k号门(1-based)到达的房间
    std::vector<std::vector<int>> adj(n + 1);
    for (int u = 1; u <= n; ++u)
    {
        int d;
        std::cin >> d;
        adj[u].resize(d);
        for (int i = 0; i < d; ++i)
        {
            std::cin >> adj[u][i];
        }
    }

    // --- 【关键修正】正确地构建反向查找表 ---
    // reverse_label_map[{v, u}] 的值是：在房间v，通往房间u的那扇门的门牌号(1-based)
    std::map<std::pair<int, int>, int> reverse_label_map;
    for (int v = 1; v <= n; ++v)
    { // 遍历每个房间 v
        for (size_t i = 0; i < adj[v].size(); ++i)
        {                      // 遍历 v 的所有门
            int u = adj[v][i]; // 从 v 通过 i+1 号门可以到达 u
            // 所以，在房间v，通往u的门是 i+1 号
            reverse_label_map[{v, u}] = i + 1;
        }
    }

    // 记忆化存储: 记录每条有向边 {u, v} 所在环的最终答案
    std::map<std::pair<int, int>, int> results;

    // 遍历所有可能的有向边，找出它们所在的环并计算结果
    for (int i = 1; i <= n; ++i)
    {
        for (int neighbor : adj[i])
        {

            // 如果这条边已经属于一个计算过的环，就跳过
            if (results.count({i, neighbor}))
            {
                continue;
            }

            // 发现一个新环的起点，开始追踪
            std::vector<std::pair<int, int>> cycle_path_edges;
            int current_u = i;
            int current_v = neighbor;

            while (!results.count({current_u, current_v}))
            {
                // 标记这条边正在访问
                results[{current_u, current_v}] = -1; // -1作为临时标记
                cycle_path_edges.push_back({current_u, current_v});

                // --- 核心行走逻辑 ---
                int prev_u = current_u;
                int next_u = current_v;

                // 1. 在当前房间(next_u)，找到我们刚进来的门(通往prev_u)的标签
                int incoming_label = reverse_label_map.at({next_u, prev_u});

                // 2. 根据规则确定下一扇要走的门的标签
                int num_doors = adj[next_u].size();
                int outgoing_label = (incoming_label == num_doors) ? 1 : incoming_label + 1;

                // 3. 找到下一个房间
                int next_v = adj[next_u][outgoing_label - 1]; // 标签-1得到0-based索引

                // 更新状态，准备下一次迭代
                current_u = next_u;
                current_v = next_v;
            }

            // --- 环已完整追踪 ---

            // 4. 计算环上【不同走廊】的数量
            std::set<std::pair<int, int>> unique_corridors;
            for (const auto &edge : cycle_path_edges)
            {
                int u1 = edge.first;
                int u2 = edge.second;
                // 将无向边标准化，方便去重 (例如 1-4 和 4-1 是同一条)
                if (u1 > u2)
                {
                    std::swap(u1, u2);
                }
                unique_corridors.insert({u1, u2});
            }
            int final_answer = unique_corridors.size();

            // 5. 将最终答案存入这个环上的每一条有向边
            for (const auto &edge : cycle_path_edges)
            {
                results[edge] = final_answer;
            }
        }
    }

    // 6. 输出所有结果
    for (int i = 1; i <= n; ++i)
    {
        // 从房间i出发，总是走1号门
        int neighbor_v = adj[i][0];
        // 直接从我们计算好的结果中查找并输出
        std::cout << results.at({i, neighbor_v}) << "\n";
    }

    return 0;
}