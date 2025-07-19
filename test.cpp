#include<bits/stdc++.h>
using namespace std;

// n: 房间数量
int n;
// d[i][j]: 从房间i走j号门(0-indexed)到达的房间
// num[i]: 房间i的总门数
int d[200001][3], num[200001];
// ans[i][j]: 记忆化数组，存储从房间i走j号门出发的最终答案
int ans[200001][3];
// vis[i][j]: 在单次DFS中，标记状态{i, j}是否被访问过，用于检测环
bool vis[200001][3];
// mp: 在单次DFS中，标记无向边{u, v}是否被计入过，用于统计不同走廊数
map<int, map<int, bool>> mp; 

/**
 * @brief 深度优先搜索，计算并填充答案
 * @param p 当前所在房间
 * @param x 准备从房间p的x号门离开 (0-indexed)
 * @param depp 到目前为止，路径上不同走廊的数量累加值
 * @return 整个环路的不同走廊总数
 */
int dfs(int p, int x, int depp) {
    // 1. 标记当前状态 {p, x} 在本次DFS中已被访问
    vis[p][x] = 1;

    // 2. 确定下一个房间 q
    int q = d[p][x];
    
    // 3. 确定从 q 离开时应该走几号门
    int s; // s 将会是下一扇门的索引 (0-indexed)
    // 遍历 q 的所有门，找到通往 p 的那扇门（索引为j），则下一扇门为 (j+1)
    for (int j = 0; j < num[q]; ++j) {
        if (d[q][j] == p) {
            s = (j + 1) % num[q]; // 取模操作优雅地处理了 j+1 等于门总数时绕回0的情况
            break;
        }
    }

    // 4. 检查 p-q 这条走廊是否是新走廊，并更新计数器
    int tt = mp[p][q]; // 如果 mp[p][q] 不存在，tt为0 (false)；存在则为1 (true)
    mp[p][q] = mp[q][p] = 1; // 标记无向边 p-q 已被统计过

    // 5. 检查是否到达环的闭合点
    if (vis[q][s]) {
        // 如果下一个状态 {q, s} 已经访问过，说明环路闭合
        // 计算整个环的答案：depp (之前累积的) + !tt (当前这一步的贡献，新边为1，旧边为0)
        // 将答案存入 ans[p][x] 并返回
        return ans[p][x] = (!tt) + depp;
    } else {
        // 如果下一个状态是新的，继续递归
        // 递归计算后续路径的答案，并把当前这一步的贡献 (!tt) 加入累加器 depp
        // 递归返回的结果就是整个环的答案，将其存入 ans[p][x] 并继续向上层返回
        return ans[p][x] = dfs(q, s, depp + !tt);
    }
}

int main() {
    scanf("%d", &n);

    // 读入所有房间的连接信息
    for (int i = 1; i <= n; ++i) {
        scanf("%d", num + i); // 读入i房间的门数
        for (int j = 0; j < num[i]; ++j)
            scanf("%d", d[i] + j); // 读入i房间的j号门通向的房间
    }

    // 遍历每个房间作为可能的起点
    for (int i = 1; i <= n; ++i) {
        // 检查从房间i的0号门出发这个状态是否已经计算过答案
        if (!ans[i][0]) { // ans初始为0，如果为0说明这个状态所在的环还没被探索
            // 探索一个全新的环，需要清空上一个环的边计数器
            mp.clear(); 
            // 启动DFS，这将计算并填充该环上所有状态的答案
            dfs(i, 0, 0); 
        }
        // 打印结果。此时 ans[i][0] 必然已经有正确的值
        printf("%d\n", ans[i][0]);
    }

    return 0;
}