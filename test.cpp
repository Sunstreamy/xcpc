#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 第一步：最终的节点设计
struct SegTreeNode {
    ll v = 0;       // 区间最长连续长度
    ll l_len = 0;   // 左起连续长度
    ll r_len = 0;   // 右起连续长度
    char l_char = 0;  // 左端点字符 (0 作为无效/空标记)
    char r_char = 0;  // 右端点字符
    int len = 0;    // 区间总长度
};

// 第二步：将合并逻辑封装成一个独立的函数
SegTreeNode merge(const SegTreeNode& left, const SegTreeNode& right) {
    if (left.l_char == 0) return right;
    if (right.l_char == 0) return left;

    SegTreeNode res;
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

// 第三步：填充到我们熟悉的线段树模板中
struct SegTree {
    int n;
    vector<SegTreeNode> tree;
    vector<char>& arr; // 注意类型是 char

    SegTree(int size, vector<char>& data) : n(size), arr(data) {
        tree.resize(4 * n + 5);
        if (n > 0) build(1, 1, n);
    }

    void push_up(int u) {
        tree[u] = merge(tree[u << 1], tree[u << 1 | 1]);
    }

    void build(int u, int l, int r) {
        tree[u].len = r - l + 1; // 别忘了初始化 len
        if (l == r) {
            tree[u] = {1, 1, 1, arr[l], arr[l], 1};
            return;
        }
        int m = (l + r) >> 1;
        build(u << 1, l, m);
        build(u << 1 | 1, m + 1, r);
        push_up(u);
    }

    void update(int u, int l, int r, int pos, char val) {
        if (l == r) {
            tree[u] = {1, 1, 1, val, val, 1};
            arr[pos] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (pos <= m) update(u << 1, l, m, pos, val);
        else update(u << 1 | 1, m + 1, r, pos, val);
        push_up(u);
    }

    SegTreeNode query(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tree[u];
        
        int m = (l + r) >> 1;
        if (qr <= m) return query(u << 1, l, m, ql, qr);
        if (ql > m) return query(u << 1 | 1, m + 1, r, ql, qr);
        
        SegTreeNode left_res = query(u << 1, l, m, ql, qr);
        SegTreeNode right_res = query(u << 1 | 1, m + 1, r, ql, qr);
        return merge(left_res, right_res);
    }

    // 公共接口
    void update(int pos, char val) { update(1, 1, n, pos, val); }
    ll query(int l, int r) {
        if (l > r) return 0;
        return query(1, 1, n, l, r).v;
    }
};

// 第四步：编写主函数来使用这个强大的工具
void solve() {
    ll n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    
    vector<char> a(n + 1);
    for(int i = 0; i < n; ++i) a[i + 1] = s[i];

    SegTree st(n, a);

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            int pos;
            char c;
            cin >> pos >> c;
            st.update(pos, c);
        } else {
            int l, r;
            cin >> l >> r;
            cout << st.query(l, r) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}