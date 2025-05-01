#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/**
 * 最长公共子序列 (Longest Common Subsequence, LCS)
 * 时间复杂度: O(m*n), 其中m和n分别是两个字符串的长度
 * 空间复杂度: O(m*n)
 */
class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.length();
        int n = text2.length();
        
        // dp[i][j] 表示 text1[0...i-1] 和 text2[0...j-1] 的最长公共子序列长度
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    // 如果当前字符相同，则最长公共子序列长度+1
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 否则取text1少一个字符或text2少一个字符的LCS的最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }
        return dp[m][n];
    }
};

// 空间优化版本，将空间复杂度优化到O(min(m,n))
class OptimizedSolution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // 确保text1是较短的字符串，以节省空间
        if (text1.length() > text2.length()) {
            swap(text1, text2);
        }
        
        int m = text1.length();
        int n = text2.length();
        
        // 只保留两行，滚动更新
        vector<int> prev(n + 1, 0);
        vector<int> curr(n + 1, 0);
        
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1]) {
                    curr[j] = prev[j - 1] + 1;
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            // 更新prev为当前行，准备计算下一行
            prev = curr;
        }
        
        return prev[n];
    }
};

// 测试函数
void testLCS() {
    Solution solution;
    
    // 测试用例1
    cout << "Example 1: " << solution.longestCommonSubsequence("abcde", "ace") << endl;  // 应输出3
    
    // 测试用例2
    cout << "Example 2: " << solution.longestCommonSubsequence("abc", "abc") << endl;  // 应输出3
    
    // 测试用例3
    cout << "Example 3: " << solution.longestCommonSubsequence("abc", "def") << endl;  // 应输出0
    
    // 额外测试用例
    cout << "Extra test: " << solution.longestCommonSubsequence("bsbininm", "jmjkbkjkv") << endl;
}

int main() {
    testLCS();
    return 0;
}

