#include <bits/stdc++.h>

using ll = long long;
using namespace std;

int dx[] = {-1, 0, 1, 0};
int dy[] = {0, 1, 0, -1};

int n;
vector<string> grid(2);
char current_type;

void dfs(int x, int y) {
    if (x < 0 || x >= 2 || y < 0 || y >= n || grid[x][y] != current_type) {
        return;
    }

    grid[x][y] = '#';

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        dfs(nx, ny);
    }
}

void solve() {
    cin >> n;
    int cnt = 0;
    for (int i = 0; i < 2; i++) {
        cin >> grid[i];
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != '#') {
                current_type = grid[i][j];
                dfs(i, j);
                cnt++;
            }
        }
    }
    cout << cnt << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}