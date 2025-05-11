#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005

class Solution
{
public:
    int numSquares(int n)
    {
        // dp[i] 表示和为 i 的完全平方数最少数量
        static std::vector<int> dp{0}; // 使用静态缓存，提高多次调用效率

        // 如果 dp 已经计算到 n，就直接返回
        while (dp.size() <= static_cast<size_t>(n))
        {
            int i = dp.size();
            int minCount = INT_MAX;
            // 尝试所有平方数
            for (int j = 1; j * j <= i; ++j)
            {
                minCount = std::min(minCount, dp[i - j * j] + 1);
            }
            dp.push_back(minCount);
        }
        return dp[n];
    }
};