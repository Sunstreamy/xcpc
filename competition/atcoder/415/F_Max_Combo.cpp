#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pair<ll, ll>> vpll;
typedef vector<vector<ll>> vll;
typedef vector<string> vs;
typedef bitset<20> b20;
#define int long long

const int MOD = 1e9 + 7;
const int INF = 0x3f3f3f3f;
const int MAXN = 400005;
const int MAXM = 200005;
/**
    线段树（SegmentTree+Info+Merge 初始赋值+单点修改+区间合并）
**/
template <class Info, class Merge = plus<Info>>
struct SegmentTree
{
    const int n;
    const Merge merge;
    vector<Info> info;
    // merge(...) 看起来像在调用一个方法，但实际上是在使用一个成员变量（一个对象） 的 operator() 功能。
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size() - 1)
    {
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (l == r)
            {
                info[p] = init[l];
                return;
            }
            int m = (l + r) >> 1;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 1, n);
    }
    void pull(int p)
    {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (l == r)
        {
            info[p] = v;
            return;
        }
        int m = (l + r) >> 1;
        if (x <= m)
        {
            modify(2 * p, l, m, x, v);
        }
        else
        {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v)
    {
        modify(1, 1, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l > y || r < x)
        {
            return Info();
        }
        if (l >= x && r <= y)
        {
            return info[p];
        }
        int m = (l + r) >> 1;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m + 1, r, x, y));
    }
    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 1, n, l, r);
    }
};

//------------------------------------------------------------------
struct Node
{
    ll v = 0;
    ll l_len = 0, r_len = 0;
    char l_c = 0, r_c = 0;
    ll len = 0;

    Node() = default;
    Node(char c) : v(1), l_len(1), r_len(1), l_c(c), r_c(c), len(1) {};
};

struct nodemerge
{
    Node operator()(const Node &left, const Node &right) const
    {
        if (left.l_c == 0)
            return right;
        if (right.l_c == 0)
            return left;

        Node res;
        res.len = left.len + right.len;
        res.l_c = left.l_c;
        res.r_c = right.r_c;
        res.l_len = left.l_len;
        res.r_len = right.r_len;
        res.v = max(left.v, right.v);

        if (left.r_c == right.l_c)
        {
            res.v = max(res.v, left.r_len + right.l_len);
            if (left.l_len == left.len)
                res.l_len += right.l_len;
            if (right.r_len == right.len)
                res.r_len += left.r_len;
        }
        return res;
    }
};

int n, q;
string s;

void solve()
{
    cin >> n >> q;
    cin >> s;
    vector<Node> init(n + 1);
    for (int i = 0; i < n; i++)
    {
        init[i + 1] = Node(s[i]);
    }
    SegmentTree<Node, nodemerge> st(init);
    for (int i = 0; i < q; i++)
    {
        int tp;
        cin >> tp;
        if (tp == 1)
        {
            int pos;
            char c;
            cin >> pos >> c;
            st.modify(pos, Node(c));
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << st.rangeQuery(l, r).v << '\n';
        }
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    solve();

    return 0;
}
