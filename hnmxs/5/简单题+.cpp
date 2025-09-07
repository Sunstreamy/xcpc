#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using f64 = double;
using u64 = unsigned long long;
using u32 = unsigned;
using u128 = unsigned __int128;
using i128 = __int128;
using b20 = bitset<20>;

constexpr int inf = 0x3f3f3f3f;
constexpr i64 linf = 0x3f3f3f3f3f3f3f3fLL;
constexpr f64 dinf = 1e18;
constexpr int maxm = 400005;
constexpr int maxn = 200005;
constexpr int MOD[] = {998244353, 1000000007};
//------------------------------------------------------------------
constexpr int mod = MOD[0];

struct Matrix {
    i64 mat[2][2];

    // 构造函数，默认初始化为零矩阵
    Matrix() {
        memset(mat, 0, sizeof(mat));
    }
};

// 重载矩阵乘法运算符
Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
            }
        }
    }
    return c;
}

// 矩阵快速幂函数
Matrix matrix_pow(Matrix base, i64 exp) {
    Matrix res;
    // 初始化结果矩阵为单位矩阵
    res.mat[0][0] = res.mat[1][1] = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            res = res * base;
        }
        base = base * base;
        exp /= 2;
    }
    return res;
}

void solve() {
    i64 n;
    cin >> n;
    Matrix base;
    base.mat[0][0] = 1;
    base.mat[0][1] = 1;
    base.mat[1][0] = 1;
    base.mat[1][1] = 0;

    Matrix res_ma = matrix_pow(base, n + 1);

    i64 ans = res_ma.mat[0][0];
    ans = (ans - 1 + mod) % mod;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}