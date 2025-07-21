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
template <class Info, class Merge = plus<Info>>
struct SegmentTree
{
    const int n;
    const Merge merge;
    vector<Info> info;
    SegmentTree(int n) : n(n), merge(Merge()), info(4 << __lg(n)) {}
    SegmentTree(vector<Info> init) : SegmentTree(init.size())
    {
        function<void(int, int, int)> build = [&](int p, int l, int r)
        {
            if (r - l == 1)
            {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p)
    {
        info[p] = merge(info[2 * p], info[2 * p + 1]);
    }
    void modify(int p, int l, int r, int x, const Info &v)
    {
        if (r - l == 1)
        {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m)
        {
            modify(2 * p, l, m, x, v);
        }
        else
        {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v)
    {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y)
    {
        if (l >= y || r <= x)
        {
            return Info();
        }
        if (l >= x && r <= y)
        {
            return info[p];
        }
        int m = (l + r) / 2;
        return merge(rangeQuery(2 * p, l, m, x, y), rangeQuery(2 * p + 1, m, r, x, y));
    }
    Info rangeQuery(int l, int r)
    {
        return rangeQuery(1, 0, n, l, r);
    }
};

// 1. 定义我们复杂的 Info 类型 (Node)
struct Node {
    ll v = 0;
    ll l_len = 0, r_len = 0;
    char l_char = 0, r_char = 0;
    int len = 0;
    // 必须有一个默认构造函数，供 rangeQuery 在不相交时返回
    Node() = default; 
    // 方便叶子节点初始化的构造函数
    Node(char c) : v(1), l_len(1), r_len(1), l_char(c), r_char(c), len(1) {}
};

// 2. 定义我们的 Merge 操作
struct NodeMerge {
    Node operator()(const Node& left, const Node& right) const {
        if (left.l_char == 0) return right;
        if (right.l_char == 0) return left;

        Node res;
        res.len = left.len + right.len;
        res.l_char = left.l_char;
        res.r_char = right.r_char;
        res.l_len = left.l_len;
        res.r_len = right.r_len;
        res.v = max(left.v, right.v);

        if (left.r_char == right.l_char) {
            res.v = max(res.v, left.r_len + right.l_len);
            if (left.l_len == left.len) res.l_len += right.l_len;
            if (right.r_len == right.len) res.r_len += left.r_len;
        }
        return res;
    }
};

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    // 准备初始化的 vector<Node>
    vector<Node> initial_nodes;
    for (char c : s) {
        initial_nodes.emplace_back(c); // 使用 Node(char) 构造函数
    }
    
    // 实例化终极线段树！
    SegmentTree<Node, NodeMerge> st(initial_nodes);
    
    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos;
            char c;
            cin >> pos >> c;
            // 注意模板是 0-based，题目可能是 1-based
            st.modify(pos - 1, Node(c)); 
        } else {
            int l, r;
            cin >> l >> r;
            // 查询 [l-1, r)
            cout << st.rangeQuery(l - 1, r).v << "\n";
        }
    }
}