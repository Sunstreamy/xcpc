### 一、 模板代码 (Template Code / "板子")

这些是通用的数据结构和算法实现，可以被复制到各种不同的问题中去使用。


2.  **数学函数模板 (Math Function Templates)**
    *   `power(T a, u64 b, T res = 1)`: **快速幂**模板。用于计算 `a` 的 `b` 次方，可以配合模运算使用。适用于任何支持乘法的数据类型 `T`。
    *   `mulMod<u32 P>(u32 a, u32 b)`: **32位无符号整数模乘**。使用 `u64` 来防止乘法溢出。
    *   `mulMod<u64 P>(u64 a, u64 b)`: **64位无符号整数模乘**。这是一个更高级的板子，使用 `long double` 来模拟 `__int128`，以在不使用 `__int128` 的情况下防止 `a*b` 溢出。
    *   `safeMod(i64 x, i64 m)`: **安全取模**。确保结果始终在 `[0, m-1]` 范围内，即使 `x` 是负数。
    *   `invGcd(i64 a, i64 b)`: **扩展欧几里得算法**模板。用于计算 `ax + by = gcd(a, b)` 的一组解 `(x, y)`，通常用来求模逆元。

3.  **模运算类 (Modular Arithmetic Classes)**
    *   `ModIntBase<U, P>`: **静态模数 `ModInt` 类**。这是最核心的板子之一。它将整数封装成一个类，并重载了 `+`, `-`, `*`, `/` 等运算符，使得所有运算都能自动在模 `P` 的意义下进行。`P` 必须在编译时确定。
    *   `Barrett`: **Barrett Reduction** 算法实现。这是一种用于快速模乘的优化技术，当模数固定但需要在运行时设置时非常有用。它通过预计算来将昂贵的除法/取模运算转换成更快的乘法和位移运算。
    *   `DynModInt<Id>`: **动态模数 `ModInt` 类**。与 `ModIntBase` 类似，但模数可以通过 `setMod()` 在运行时设置。它内部使用了 `Barrett` 优化来提高乘法效率。`Id` 模板参数是为了区分不同的动态模数实例。

4.  **线性代数模板 (Linear Algebra Template)**
    *   `det(std::vector<std::vector<Z>> a)`: **矩阵求行列式**的模板。它使用高斯消元法（Gaussian Elimination）将矩阵转换为上三角矩阵，然后将对角线元素相乘得到行列式的值。这里的 `Z` 是 `ModInt` 类型，意味着它是在模意义下计算行列式。
    *   **注意**: 在你提供的代码中，`det` 函数虽然被定义了，但在 `main` 函数中**并未被调用**。这说明它只是作者个人代码库里的一个标准板子，虽然带上了，但这个问题用不着。

```cpp
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
using u32 = unsigned;

using u128 = unsigned __int128;
using i128 = __int128;

template<class T>
constexpr T power(T a, u64 b, T res = 1) {
    for (; b != 0; b /= 2, a *= a) {
        if (b & 1) {
            res *= a;
        }
    }
    return res;
}

template<u32 P>
constexpr u32 mulMod(u32 a, u32 b) {
    return u64(a) * b % P;
}

template<u64 P>
constexpr u64 mulMod(u64 a, u64 b) {
    u64 res = a * b - u64(1.L * a * b / P - 0.5L) * P;
    res %= P;
    return res;
}

constexpr i64 safeMod(i64 x, i64 m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}

constexpr std::pair<i64, i64> invGcd(i64 a, i64 b) {
    a = safeMod(a, b);
    if (a == 0) {
        return {b, 0};
    }
    
    i64 s = b, t = a;
    i64 m0 = 0, m1 = 1;

    while (t) {
        i64 u = s / t;
        s -= t * u;
        m0 -= m1 * u;
        
        std::swap(s, t);
        std::swap(m0, m1);
    }
    
    if (m0 < 0) {
        m0 += b / s;
    }
    
    return {s, m0};
}

template<std::unsigned_integral U, U P>
struct ModIntBase {
public:
    constexpr ModIntBase() : x(0) {}
    template<std::unsigned_integral T>
    constexpr ModIntBase(T x_) : x(x_ % mod()) {}
    template<std::signed_integral T>
    constexpr ModIntBase(T x_) {
        using S = std::make_signed_t<U>;
        S v = x_ % S(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }
    
    constexpr static U mod() {
        return P;
    }
    
    constexpr U val() const {
        return x;
    }
    
    constexpr ModIntBase operator-() const {
        ModIntBase res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }
    
    constexpr ModIntBase inv() const {
        return power(*this, mod() - 2);
    }
    
    constexpr ModIntBase &operator*=(const ModIntBase &rhs) & {
        x = mulMod<mod()>(x, rhs.val());
        return *this;
    }
    constexpr ModIntBase &operator+=(const ModIntBase &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator-=(const ModIntBase &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr ModIntBase &operator/=(const ModIntBase &rhs) & {
        return *this *= rhs.inv();
    }
    
    friend constexpr ModIntBase operator*(ModIntBase lhs, const ModIntBase &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator+(ModIntBase lhs, const ModIntBase &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator-(ModIntBase lhs, const ModIntBase &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr ModIntBase operator/(ModIntBase lhs, const ModIntBase &rhs) {
        lhs /= rhs;
        return lhs;
    }
    
    friend constexpr std::istream &operator>>(std::istream &is, ModIntBase &a) {
        i64 i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const ModIntBase &a) {
        return os << a.val();
    }
    
    friend constexpr bool operator==(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr std::strong_ordering operator<=>(const ModIntBase &lhs, const ModIntBase &rhs) {
        return lhs.val() <=> rhs.val();
    }
    
private:
    U x;
};

template<u32 P>
using ModInt = ModIntBase<u32, P>;
template<u64 P>
using ModInt64 = ModIntBase<u64, P>;

struct Barrett {
public:
    Barrett(u32 m_) : m(m_), im((u64)(-1) / m_ + 1) {}

    constexpr u32 mod() const {
        return m;
    }

    constexpr u32 mul(u32 a, u32 b) const {
        u64 z = a;
        z *= b;
        
        u64 x = u64((u128(z) * im) >> 64);
        
        u32 v = u32(z - x * m);
        if (m <= v) {
            v += m;
        }
        return v;
    }

private:
    u32 m;
    u64 im;
};

template<u32 Id>
struct DynModInt {
public:
    constexpr DynModInt() : x(0) {}
    template<std::unsigned_integral T>
    constexpr DynModInt(T x_) : x(x_ % mod()) {}
    template<std::signed_integral T>
    constexpr DynModInt(T x_) {
        int v = x_ % int(mod());
        if (v < 0) {
            v += mod();
        }
        x = v;
    }
    
    constexpr static void setMod(u32 m) {
        bt = m;
    }
    
    static u32 mod() {
        return bt.mod();
    }
    
    constexpr u32 val() const {
        return x;
    }
    
    constexpr DynModInt operator-() const {
        DynModInt res;
        res.x = (x == 0 ? 0 : mod() - x);
        return res;
    }
    
    constexpr DynModInt inv() const {
        auto v = invGcd(x, mod());
        assert(v.first == 1);
        return v.second;
    }
    
    constexpr DynModInt &operator*=(const DynModInt &rhs) & {
        x = bt.mul(x, rhs.val());
        return *this;
    }
    constexpr DynModInt &operator+=(const DynModInt &rhs) & {
        x += rhs.val();
        if (x >= mod()) {
            x -= mod();
        }
        return *this;
    }
    constexpr DynModInt &operator-=(const DynModInt &rhs) & {
        x -= rhs.val();
        if (x >= mod()) {
            x += mod();
        }
        return *this;
    }
    constexpr DynModInt &operator/=(const DynModInt &rhs) & {
        return *this *= rhs.inv();
    }
    
    friend constexpr DynModInt operator*(DynModInt lhs, const DynModInt &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator+(DynModInt lhs, const DynModInt &rhs) {
        lhs += rhs;
        return lhs;
    }
    friend constexpr DynModInt operator-(DynModInt lhs, const DynModInt &rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend constexpr DynModInt operator/(DynModInt lhs, const DynModInt &rhs) {
        lhs /= rhs;
        return lhs;
    }
    
    friend constexpr std::istream &operator>>(std::istream &is, DynModInt &a) {
        i64 i;
        is >> i;
        a = i;
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const DynModInt &a) {
        return os << a.val();
    }
    
    friend constexpr bool operator==(const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr std::strong_ordering operator<=>(const DynModInt &lhs, const DynModInt &rhs) {
        return lhs.val() <=> rhs.val();
    }
    
private:
    u32 x;
    static Barrett bt;
};

template<u32 Id>
Barrett DynModInt<Id>::bt = 998244353;

using Z = ModInt<1000000007>;

Z det(std::vector<std::vector<Z>> a) {
    int n = a.size();
    Z ans = 1;
    for (int i = 0; i < n; i++) {
        int j = i;
        while (j < n && a[j][i] == 0) {
            j++;
        }
        if (j == n) return 0;
        if (i != j) {
            std::swap(a[i], a[j]);
            ans *= -1;
        }
        ans *= a[i][i];
        auto v = Z(a[i][i]).inv();
        for (int j = i; j < n; j++) {
            a[i][j] *= v;
        }
        for (int j = i + 1; j < n; j++) {
            Z v = a[j][i];
            for (int k = i; k < n; k++) {
                a[j][k] -= a[i][k] * v;
            }
        }
    }
    return ans;
}
```
### 总结

| 代码部分                               | 类型             | 作用                                                                  |
| -------------------------------------- | ---------------- | --------------------------------------------------------------------- |
| `power`, `mulMod`, `safeMod`, `invGcd` | **数学板子**     | 实现快速幂、模乘、安全取模、求逆元等基础数学运算                      |
| `ModIntBase`, `Barrett`, `DynModInt`   | **核心板子**     | 封装模运算，使代码更简洁、不易出错                                    |
| `det`                                  | **算法板子**     | 计算矩阵行列式（在此问题中未被使用）                                  |
