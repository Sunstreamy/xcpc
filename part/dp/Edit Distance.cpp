#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        int m = word1.size(), n = word2.size();

        // 创建DP表
        vector<vector<int>> f(m + 1, vector<int>(n + 1, 0));

        // 初始化边界条件
        for (int i = 0; i <= m; i++)
        {
            f[i][0] = i; // 将word1的前i个字符转换为空串需要i次删除
        }

        for (int j = 0; j <= n; j++)
        {
            f[0][j] = j; // 将空串转换为word2的前j个字符需要j次插入
        }

        // DP状态转移
        for (int i = 1; i <= m; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                if (word1[i - 1] == word2[j - 1])
                {
                    f[i][j] = f[i - 1][j - 1]; // 如果字符相同，不需要操作
                }
                else
                {
                    f[i][j] = 1 + min({f[i - 1][j], f[i - 1][j - 1], f[i][j - 1]}); // 修正：应该是f[i][j]而不是f[i-1][j-1]
                }
            }
        }

        return f[m][n];
    }
};