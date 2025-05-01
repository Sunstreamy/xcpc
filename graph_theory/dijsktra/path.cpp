//https://www.lanqiao.cn/problems/1460/learning/
#include <bits/stdc++.h>
using namespace std;
#define int long long
const long long LINF = 1e18; // 一个足够大的值

struct edge
{
    int to;
    int weight;
};

int gcd(int a, int b)
{
    return b ? gcd(b, a % b) : a;
}

int lcm(int a, int b)
{
    return a / gcd(a, b) * b;
}

vector<int> dis(2022);
vector<bool> vis(2022);
vector<vector<edge>> adj(2022);

void dij(int sta)
{
    fill(dis.begin(), dis.end(), LINF);
    fill(vis.begin(), vis.end(), false);
    dis[sta] = 0;

    for (int i = 0; i < 2021; i++)
    {
        int u = -1;
        int mn = LINF;

        for (int j = 1; j <= 2021; j++)
        {
            if (!vis[j] && dis[j] < mn)
            {
                mn = dis[j];
                u = j;
            }
        }
        if (u == -1)
        {
            break;
        }

        vis[u] = true;
        for (auto &edge : adj[u])
        {
            int v = edge.to;
            int weight = edge.weight;
            if (dis[u] != LINF && !vis[v] && dis[u] + weight < dis[v])
            {
                dis[v] = dis[u] + weight;
            }
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    for (int u = 1; u <= 2021; u++)
    {
        int l = max(1LL, u - 21);
        int r = min(2021LL, u + 21);
        for (int v = l; v <= r; v++)
        {
            if (v == u)
                continue;
            int weight = lcm(u, v);
            adj[u].push_back({v, weight});
        }
    }

    dij(1);
    cout << dis[2021];

    // 请在此输入您的代码
    return 0;
}