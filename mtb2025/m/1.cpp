#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Interval {
    int l, r;
};

bool compareIntervals(const Interval& a, const Interval& b) {
    return a.l < b.l;
}

void solve() {
    int n;
    cin >> n;
    vector<Interval> intervals(n);
    for (int i = 0; i < n; i++) {
        cin >> intervals[i].l >> intervals[i].r;
    }

    sort(intervals.begin(), intervals.end(), compareIntervals);

    long long total_length = 0;
    if (n == 0) {
        cout << 0 << endl;
        return;
    }

    int current_l = intervals[0].l;
    int current_r = intervals[0].r;

    for (int i = 1; i < n; i++) {
        if (intervals[i].l <= current_r) {
            current_r = max(current_r, intervals[i].r);
        } else {
            total_length += (long long)current_r - current_l + 1;
            // 开始一个新的合并区间
            current_l = intervals[i].l;
            current_r = intervals[i].r;
        }
    }

    // 别忘了加上最后一个合并的区间
    total_length += (long long)current_r - current_l + 1;

    cout << total_length << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}