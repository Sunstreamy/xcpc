#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
    // 请在此输入您的代码

    int r, c, k;
    cin >> r >> c >> k;
    vector<vector<int>> grid(r + 1, vector<int>(c + 1, 0));
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            cin >> grid[i][j];
            grid[i][j] += grid[i - 1][j] + grid[i][j - 1] - grid[i - 1][j - 1];
        }
    }

    int cnt = 0;
    for (int x1 = 1; x1 <= r; x1++)
    {
        for (int x2 = x1; x2 <= r; x2++)
        {
            int y1 = 1;
            for (int y2 = 1; y2 <= c; y2++)
            {
                int sum = grid[x2][y2] - grid[x1 - 1][y2] - grid[x2][y1 - 1] + grid[x1 - 1][y1 - 1];
                while (sum > k && y1 <= y2)
                {
                    y1++;
                    if (y1 <= y2)
                    {
                        sum = grid[x2][y2] - grid[x1 - 1][y2] - grid[x2][y1 - 1] + grid[x1 - 1][y1 - 1];
                    }
                }
                if (sum <= k)
                {
                    cnt += (y2 - y1 + 1);
                }
            }
        }
    }
    cout << cnt << '\n';

    return 0;
}