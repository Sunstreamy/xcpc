#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string largestNumber(vector<int> &cost, int target)
    {
        // dp[i] 表示成本为i时能够得到的最大位数
        vector<int> dp(target + 1, INT_MIN);
        dp[0] = 0; // 成本为0时，位数为0

        // 完全背包
        for (int i = 0; i < 9; ++i)
        {
            for (int j = cost[i]; j <= target; ++j)
            {
                dp[j] = max(dp[j], dp[j - cost[i]] + 1);
            }
        }

        // 如果无法凑出target成本，返回"0"
        if (dp[target] < 0)
            return "0";
        string result;
        // 从最大的数字开始构造结果
        for (int i = 8; i >= 0; --i)
        {
            // 贪心：尽可能使用最大的数字
            while (target >= cost[i] && dp[target] == dp[target - cost[i]] + 1)
            {
                result.push_back('1' + i); // 数字从1开始，所以是'1'+i
                target -= cost[i];
            }
        }

        return result;
    }
};
