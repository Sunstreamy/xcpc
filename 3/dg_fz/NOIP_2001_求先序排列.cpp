#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vpll;
typedef vector<vl> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int mod = 1e9 + 7;
const int linf = 0x3f3f3f3f3f3f3f3fLL;
const int maxm = 400005;
const int maxn = 200005;

inline void rd(int &rex) // 读入优化
{
    rex = 0;
    char c = getchar();
    while (c < '0' || c > '9')
        c = getchar();
    while (c >= '0' && c <= '9')
        rex = rex * 10 + c - '0', c = getchar();
}

inline pair<vl, int> discretize(const vl &a)
{
    vl b = a;
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    int m = b.size();
    vl c(a.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        c[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin() + 1;
    }
    return {c, m};
}
//------------------------------------------------------------------
// 向编译器承诺我们不会修改它们
void ppre(const string &in, const string &pos)
{
    if (in.empty())
        return;
    // 1. 根节点是后序遍历的最后一个字符
    char root = pos.back();

    // output first
    cout << root;

    // 3. 在中序遍历中找到根节点，以分割左右子树
    size_t in_root_idx = in.find(root);

    // 4. 根据根节点位置，递归处理左右子树
    // 左子树
    ppre(in.substr(0, in_root_idx), pos.substr(0, in_root_idx));

    // 后序遍历的前 in_root_idx 个字符是左子树，所以右子树从这个位置开始。
    // 总长度 - 左子树的长度 - 根节点的长度(1)
    ppre(in.substr(in_root_idx + 1), pos.substr(in_root_idx, pos.length() - in_root_idx - 1));
}

void solve()
{
    // 后：左-右-根
    // 中：左-根-右
    // 先：根-左-右
    string a, b;
    cin >> a >> b;
    ppre(a, b);
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
