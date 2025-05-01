// https://www.lanqiao.cn/problems/1457/learning/
// 暴力
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N;
    cin >> N;

    // 特判，杨辉三角最开始的数字就是1
    if (N == 1)
    {
        cout << 1 << "\n";
        return 0;
    }

    ll flatIndex = 0; // 平铺序号，从1开始计数
    vector<ll> prev;  // 上一行
    vector<ll> curr;  // 当前行

    // 从第一行开始生成
    for (int row = 1;; row++)
    {
        curr.resize(row);
        if (row == 1)
        {
            curr[0] = 1;
        }
        else
        {
            // 每行两端都是1
            curr[0] = 1;
            curr[row - 1] = 1;
            // 如果中间不止一个数字则由上一行构造
            for (int j = 1; j < row - 1; j++)
            {
                curr[j] = prev[j - 1] + prev[j];
            }
        }
        // 检查当前这一行的每个数字（从左到右），并更新平铺下标
        for (int j = 0; j < row; j++)
        {
            flatIndex++;
            if (curr[j] == N)
            {
                cout << flatIndex << "\n";
                return 0;
            }
        }
        prev = curr;
    }

    return 0;
}