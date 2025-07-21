//
// 八数码问题求解：预处理所有状态，查表输出解
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
typedef pair<int, int> PII;
const int M = 1e9 + 7;
#define N 200005

// mp: 用于存储每个状态到目标状态的操作序列
map<string, string> mp;
// ans: 目标状态（最终排列）
string ans = "12345678x";
void bfs()
{
    queue<string> q;
    mp[ans] = "";
    q.push(ans);
    while (!q.empty())
    {
        string str = q.front();
        q.pop();
        string cur = str;
        size_t idx = str.find('x');
        int r = idx / 3, left = idx % 3, right = (idx + 1) % 3;

        if (left)
        {
            swap(str[idx], str[idx - 1]);
            if (mp.find(str) == mp.end())
            {
                mp[str] = mp[cur] + 'r';
                q.push(str);
            }
            swap(str[idx], str[idx - 1]);
        }
        if (right)
        {
            swap(str[idx], str[idx + 1]);
            if (mp.find(str) == mp.end())
            {
                mp[str] = mp[cur] + 'l';
                q.push(str);
            }
            swap(str[idx], str[idx + 1]);
        }
        if (r)
        {
            swap(str[idx], str[idx - 3]);
            if (mp.find(str) == mp.end())
            {
                mp[str] = mp[cur] + 'd';
                q.push(str);
            }
            swap(str[idx], str[idx - 3]);
        }
        if (r < 2)
        {
            swap(str[idx], str[idx + 3]);
            if (mp.find(str) == mp.end())
            {
                mp[str] = mp[cur] + 'u';
                q.push(str);
            }
            swap(str[idx], str[idx + 3]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    bfs();
    // 处理多组输入
    while (true)
    {
        char ch;
        string s = "";
        // 读取一组输入（9个字符）
        for (i64 i = 0; i < 9; i++)
        {
            if (!(cin >> ch))
                return 0; // 输入结束则退出
            s += ch;
        }

        // 查表输出结果
        if (mp.find(s) != mp.end())
        {
            string op = mp[s];             // 操作序列
            reverse(op.begin(), op.end()); // 逆向操作需反转
            cout << op << endl;            // 输出解
        }
        else
        {
            cout << "unsolvable" << endl; // 无解
        }
    }
}