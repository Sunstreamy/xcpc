//
#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef bitset<20> b20; // 或者 using Bits = bitset<20>;
const int M = 1e9 + 7;
#define N 200005
#define int long long

b20 b;
int board[20][20], k, tmp[20][20];
int n, m, ans[20][20];
inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}
inline void work(int x, int y) // 进行翻转操作
{
    board[x][y] ^= 1;
    board[x - 1][y] ^= 1;
    board[x + 1][y] ^= 1;
    board[x][y - 1] ^= 1;
    board[x][y + 1] ^= 1;
}
inline void print() // 输出
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            printf("%d ", ans[i][j]); // 修改为 ans 数组
        puts("");
    }
    exit(0); // 非主函数中使用exit(0)直接结束程序 ，因为判断字典序时，\
	优先第一行，	所以只要有序枚举第一行， 第一次得到的答案就是最优解
}
inline void check()
{
    int sum = 0;
    for (int i = 1; i < n; i++)
        for (int j = 1; j <= m; j++)
            if (board[i][j] == 1)
            {
                work(i + 1, j);
                ans[i + 1][j] = 1; // 修改为 ans 数组
            } // 若board[i][j]当前为1，那么将第i+1行第j列翻转
    for (int i = 1; i <= m; i++)
        if (board[n][i] == 1)
            return;
    print();
}
signed main()
{
    rd(n);
    rd(m);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            rd(board[i][j]);
    memcpy(tmp, board, sizeof(tmp));
    while (b[m] == 0)
    {
        b = k++;
        for (int i = 0; i < m; i++)
        {
            if (b[i] == 1)
                work(1, i + 1), ans[1][i + 1] = 1;
            // 因为bitset从0开始存储，board, ans从1开始存储，所以此处要加1
        }
        check();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
            {
                board[i][j] = tmp[i][j];
                ans[i][j] = 0;
            }
    }
    puts("IMPOSSIBLE"); // 若找到最优解则直接退出，否则输出
    return 0;
}
