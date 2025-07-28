const int N = 100010;
/// sz 表示节点的秩，这里定义为节点的元素个数
int fa[N], sz[N], n;
void init() {
    // 初始化
    for (int i = 0; i <= n; i++) {
        fa[i] = i;
        sz[i] = 1;
    }
}
// find 操作，使用「路径压缩」+「按秩合并」，时间复杂度为反阿克曼函数，可以认为是常数
int find(int x) {
    if (x == fa[x]) return x;
    // 路径压缩，fa 直接赋值为代表元素
    return fa[x] = find(fa[x]);
}
// Merge 操作，同上，可以认为时间复杂度为常数
void merge(int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return;
    if (sz[fx] < sz[fy]) {
        fa[fx] = fy;
        sz[fy] += sz[fx];
    } else {
        fa[fy] = fx;
        sz[fx] += sz[fy];
    }
}
