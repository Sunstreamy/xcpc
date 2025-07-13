//
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
typedef pair<int, int> PII;
const int M = 1e9 + 7;
#define N 200005
struct Node
{
    int l, x, y, dist;
};
int ll, rr, cc;

vector<vector<string>> grid;
int dx[] = {0, 1, 0, -1, 0, 0};
int dy[] = {1, 0, -1, 0, 0, 0};
int dl[] = {0, 0, 0, 0, 1, -1};

void solve()
{
    grid.assign(ll, vector<string>(rr));
    Node start;
    for (int i = 0; i < ll; i++)
    {
        for (int j = 0; j < rr; j++)
        {
            cin >> grid[i][j];
            for (int k = 0; k < cc; k++)
            {
                if (grid[i][j][k] == 'S')
                    start = {i, j, k, 0};
            }
        }
    }
    queue<Node> q;
    q.push(start);
    grid[start.l][start.x][start.y] = '#';
    int ans = -1;
    bool ok = false;
    while (!q.empty() && !ok)
    {
        Node cur = q.front();
        q.pop();

        for (int i = 0; i < 6; i++)
        {
            int nx = cur.x + dx[i], ny = cur.y + dy[i], nl = cur.l + dl[i];
            if (nx < 0 || nx >= rr || ny < 0 || ny >= cc || nl < 0 || nl >= ll)
                continue;
            if (grid[nl][nx][ny] == '#')
                continue;
            if (grid[nl][nx][ny] == 'E')
            {
                ans = cur.dist + 1;
                ok = true;
                break;
            }
            grid[nl][nx][ny] = '#';
            q.push({nl, nx, ny, cur.dist + 1});
        }
    }
    if (ok)
        cout << "Escaped in " << ans << " minute(s)." << "\n";
    else
        cout << "Trapped!" << '\n';
    return;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while (cin >> ll >> rr >> cc && cc)
    {
        solve();
    }

    return 0;
}
