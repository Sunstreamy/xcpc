#include <iostream>
#include <queue>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005
#define row 5
#define col 5

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
// int row, col;
int grid[1010][1010];
pair<int, int> pre[1010][1010];
void solve(int x, int y)
{
    queue<pair<int, int>> q;
    q.push({x, y});
    grid[x][y] = 1;
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();
        for (int i = 0; i < 4; i++)
        {
            int xx = u.first + dx[i], yy = u.second + dy[i];
            if (xx < 0 || xx >= row || yy < 0 || yy >= col)
                continue;
            if (grid[xx][yy])
                continue;
            grid[xx][yy] = 1;
            pre[xx][yy] = u;
            q.push({xx, yy});
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    //    cin >> row >> col;
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
            cin >> grid[i][j];
    }
    solve(row - 1, col - 1);
    pair<int, int> cur = {0, 0};
    while (true)
    {
        cout << "(" << cur.first << ", " << cur.second << ")" << endl;
        if (cur.first == row - 1 && cur.second == col - 1)
            break;
        cur = pre[cur.first][cur.second];
    }
    return 0;
}
