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
constexpr int maxm = 400005;
constexpr int maxn = 200005;
//------------------------------------------------------------------
struct Dsu {
    vector<int> fa, sz, ed;
    vector<bool> cy;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1), ed(n + 1), cy(n + 1, false) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            ed[fx]++;
            cy[fx] = true;
            return false;
        }
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        ed[fx] += ed[fy];
        ed[fx]++;
        cy[fx] = cy[fx] || cy[fy];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool sc(int x) {
        return cy[find(x)];
    }
    int ecnt(int x) {
        return ed[find(x)];
    }
    int pcnt(int x) {
        return sz[find(x)];
    }
};

void solve() {
    int n, p1, p2;
    while (cin >> n >> p1 >> p2 && n + p1 + p2 != 0) {
        int pnum = p1 + p2;
        Dsu dt(pnum * 2);
        bool impo = false;

        for (int i = 0; i < n; ++i) {
            int u, v;
            string rep;
            cin >> u >> v >> rep;
            if (impo) continue;

            if (rep == "yes") {
                if (dt.find(u) == dt.find(v + pnum)) {
                    impo = true;
                } else {
                    dt.mg(u, v);
                    dt.mg(u + pnum, v + pnum);
                }
            } else {
                if (dt.find(u) == dt.find(v)) {
                    impo = true;
                } else {
                    dt.mg(u, v + pnum);
                    dt.mg(u + pnum, v);
                }
            }
        }

        if (impo) {
            cout << "no" << '\n';
            continue;
        }

        // 分组统计:groups代表一个组里的两个阵营（后面dp要确定每个组选择哪个阵营为神圣，哪个为邪恶）
        vector<pair<int, int>> groups;
        vector<bool> vis(pnum + 1, false);
        for (int i = 1; i <= pnum; ++i) {
            if (!vis[i]) {
                int rta = dt.find(i);
                int rtb = dt.find(i + pnum);
                // 统计这个组的所有成员，并一次性标记
                // 注意每一个group里记录的两个阵营集合的sz代表的是选择当前阵营能获得的天使的数量!!!因此不能直接使用dt.sz，因为dt.sz记录的是当前这个阵营的所有节点，比如可能是两个天使，一个恶魔，结果是3.但是希望的sz是2.
                vector<int> one_group;
                for (int j = 1; j <= pnum; ++j) {
                    if (!vis[j] && (dt.find(j) == rta || dt.find(j) == rtb)) {
                        one_group.push_back(j);
                        vis[j] = true;
                    }
                }

                int sza = 0;
                for (int t : one_group) {
                    if (dt.find(t) == rta) {
                        sza++;
                    }
                }
                int szb = one_group.size() - sza;
                groups.push_back({sza, szb});
            }
        }

        // dp[i][j]->考虑前i个组件（联通块），组成含j个神圣居民部落的方案数
        vector<vector<int>> dp(groups.size() + 1, vector<int>(p1 + 1, 0));
        dp[0][0] = 1;

        for (int i = 0; i < groups.size(); ++i) {
            int sza = groups[i].first;
            int szb = groups[i].second;
            for (int j = 0; j <= p1; ++j) {
                if (dp[i][j] > 0) {
                    if (j + sza <= p1) {
                        dp[i + 1][j + sza] += dp[i][j];
                    }
                    if (j + szb <= p1) {
                        dp[i + 1][j + szb] += dp[i][j];
                    }
                }
            }
        }

        if (dp[groups.size()][p1] != 1) {
            cout << "no" << '\n';
            continue;
        }

        // 回溯和输出阶段
        vector<int> choices;
        int cur = p1;
        for (int i = groups.size() - 1; i >= 0; --i) {
            int sza = groups[i].first, szb = groups[i].second;
            if (cur >= sza && dp[i][cur - sza] == 1) {
                choices.push_back(1);
                cur -= sza;
            } else {
                choices.push_back(2);
                cur -= szb;
            }
        }
        reverse(choices.begin(), choices.end());

        vector<bool> is_god_roots(2 * pnum + 1, false);
        vis.assign(pnum + 1, false);
        int group_index = 0;
        for (int i = 1; i <= pnum; ++i) {
            if (!vis[i]) {
                int rta = dt.find(i);
                int rtb = dt.find(i + pnum);

                if (choices[group_index] == 1) {
                    is_god_roots[rta] = true;
                } else {
                    is_god_roots[rtb] = true;
                }
                group_index++;

                for (int j = 1; j <= pnum; ++j) {
                    if (dt.find(j) == rta || dt.find(j) == rtb) {
                        vis[j] = true;
                    }
                }
            }
        }

        vector<int> gods;
        for (int i = 1; i <= pnum; ++i) {
            if (is_god_roots[dt.find(i)]) {
                gods.push_back(i);
            }
        }

        for (int god : gods) {
            cout << god << '\n';
        }
        cout << "end" << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}