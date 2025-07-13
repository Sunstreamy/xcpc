
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1e18;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T, a0, a1, a2, a3;
    cin >> T >> a0 >> a1 >> a2 >> a3;

    // 预处理：枚举9种基本操作的子集
    // 用 4 位表示 2×2 状态，顺序：(0,0)->bit0, (0,1)->bit1, (1,0)->bit2, (1,1)->bit3
    // 操作列表：4 个单格，2 个行，2 个列，1 个全盘
    vector<pair<int, int>> ops;
    // 单个单元格（cost = a0）
    ops.push_back({a0, 1 << 0});
    ops.push_back({a0, 1 << 1});
    ops.push_back({a0, 1 << 2});
    ops.push_back({a0, 1 << 3});
    // 行操作（cost = a1）
    ops.push_back({a1, (1 << 0) | (1 << 1)}); // 第一行
    ops.push_back({a1, (1 << 2) | (1 << 3)}); // 第二行
    // 列操作（cost = a2）
    ops.push_back({a2, (1 << 0) | (1 << 2)}); // 第一列
    ops.push_back({a2, (1 << 1) | (1 << 3)}); // 第二列
    // 全盘操作（cost = a3）
    ops.push_back({a3, 15}); // 15 = 0b1111

    const int opsCount = (int)ops.size(); // 9
    const int totalState = 16;            // 状态范围0~15
    vector<ll> opCost(totalState, INF);
    // 注意：空操作对应的变换为 0，但不允许使用空序列作为起始
    opCost[0] = 0;
    // 枚举 2^9=512 个子集，求出每种 2×2 变换的最小花费（注意空子集也会被枚举，但后面取 min 会优化掉）
    for (int mask = 0; mask < (1 << opsCount); mask++)
    {
        int effect = 0;
        ll cost = 0;
        for (int i = 0; i < opsCount; i++)
        {
            if (mask & (1 << i))
            {
                cost += ops[i].first;
                effect ^= ops[i].second;
            }
        }
        opCost[effect] = min(opCost[effect], cost);
    }

    // 构造 16 个状态的完全图
    // 状态转移：从 u 转换到 v 的花费等于 opCost[u XOR v]
    const int V = 16;
    // TSP 状态 DP：dp[mask][v] 表示从初始 0 状态出发，
    // 使用若干操作使得累计变换出现的状态集合为 mask，且最后状态为 v 的最小总花费
    int full = 1 << V;
    vector<vector<ll>> dp(full, vector<ll>(V, INF));
    // 初始化：从 0 状态出发“直接”到 v，空操作不允许作为开头
    for (int v = 0; v < V; v++)
    {
        dp[1 << v][v] = (v == 0 ? INF : opCost[v]);
    }

    // 状态转移
    for (int mask = 0; mask < full; mask++)
    {
        for (int u = 0; u < V; u++)
        {
            if (!(mask & (1 << u)))
                continue;
            ll cur = dp[mask][u];
            if (cur == INF)
                continue;
            for (int v = 0; v < V; v++)
            {
                if (mask & (1 << v))
                    continue;
                int nmask = mask | (1 << v);
                ll costTrans = opCost[u ^ v];
                dp[nmask][v] = min(dp[nmask][v], cur + costTrans);
            }
        }
    }

    // best[mask]：覆盖 mask 中所有状态的最小花费（不关心最后停在哪个状态）
    vector<ll> best(full, INF);
    for (int mask = 0; mask < full; mask++)
    {
        for (int v = 0; v < V; v++)
        {
            if (mask & (1 << v))
                best[mask] = min(best[mask], dp[mask][v]);
        }
    }

    // 对于每个游戏：
    // 每个游戏给出 m 个可能的初始 2×2 网格，每个网格转为 4 位表示
    // 若初始状态为 X，则需要存在前缀累计变换 Y 满足：X XOR Y = 15，
    // 即 Y = 15 XOR X （非空序列，所以 Y 不能直接为 0，但可以在后续步骤中达到 0）
    // 将所有 m 个所需 Y 合并成目标 mask
    while (T--)
    {
        int m;
        cin >> m;
        int targetMask = 0; // 目标 mask：用 0~15 的位表示需要出现的累计状态
        for (int i = 0; i < m; i++)
        {
            string line1, line2;
            cin >> line1 >> line2;
            int init = 0;
            if (line1[0] == '1')
                init |= (1 << 0);
            if (line1[1] == '1')
                init |= (1 << 1);
            if (line2[0] == '1')
                init |= (1 << 2);
            if (line2[1] == '1')
                init |= (1 << 3);
            int req = 15 ^ init; // 需要的累计变换
            targetMask |= (1 << req);
        }
        // 注意：答案可能出现在覆盖 targetMask 的超集中
        ll ans = INF;
        for (int mask = 0; mask < full; mask++)
        {
            if ((mask & targetMask) == targetMask)
            {
                ans = min(ans, best[mask]);
            }
        }
        cout << ans << "\n";
    }

    return 0;
}