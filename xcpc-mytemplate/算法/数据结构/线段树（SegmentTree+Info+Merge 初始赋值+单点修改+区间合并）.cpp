/**
    线段树（SegmentTree+Info+Merge 初始赋值+单点修改+区间合并）
**/
#include <bits/stdc++.h>
using namespace std;

struct Node
{
};
struct Nodemerge
{
    Node res;
    Node operator()() const
    {
        return res;
    }
};
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