#include <bits/stdc++.h>
using namespace std;
#define int long long

struct edge
{
    int to;
    int w;
};

int n, k;
vector<vector<edge>> adj;

int dis(int u, int v)
{
    vector<bool> vis(n + 1, false);
    function<int(int)> dfs = [&](int cur) -> int
    {
        if (cur == v)
            return 0;
        vis[cur] = true;
        for (auto &edge : adj[cur])
        {
            if (!vis[edge.to])
            {
                int d = dfs(edge.to);
                if (d != -1)
                    return d + edge.w;
            }
        }
        return -1;
    };
    return dfs(u);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> k;
    adj.resize(n + 1);
    for (int i = 1; i < n; i++)
    {
        int u, v, t;
        cin >> u >> v >> t;
        adj[u].push_back({v, t});
        adj[v].push_back({u, t});
    }

    vector<int> plan(k);
    for (int i = 0; i < k; i++)
    {
        cin >> plan[i];
    }
    int total = 0;
    vector<int> seg(k - 1);
    for (int i = 0; i < k - 1; i++)
    {
        seg[i] = dis(plan[i], plan[i + 1]);
        total += seg[i];
    }
    vector<int> ans(k);
    ans[0] = total - seg[0];
    ans[k - 1] = total - seg[k - 2];
    for (int i = 1; i < k - 1; i++)
    {
        ans[i] = total - seg[i - 1] - seg[i] + dis(plan[i - 1], plan[i + 1]);
    }
    for (auto t : ans)
    {
        cout << t << " ";
    }
    cout << "\n";

    // 请在此输入您的代码
    return 0;
}
//https://www.lanqiao.cn/problems/3516/learning/
//50%