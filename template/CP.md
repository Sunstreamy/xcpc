# 算法模板库 


- [算法模板库](#算法模板库)
  - [基础算法](#基础算法)
    - [简易IO](#简易io)
    - [准IO](#准io)
    - [取模运算](#取模运算)
    - [大整数](#大整数)
      - [学习版](#学习版)
      - [完全体](#完全体)
    - [进制转换](#进制转换)
    - [离散化](#离散化)
  - [数据结构](#数据结构)
    - [ST表](#st表)
    - [并查集 (DSU) - 路径压缩 + 按秩序合并](#并查集-dsu---路径压缩--按秩序合并)
    - [树状数组](#树状数组)
  - [字符串算法](#字符串算法)
  - [数论](#数论)
    - [质因子分解](#质因子分解)
      - [筛法](#筛法)
    - [快速幂](#快速幂)
    - [逆元](#逆元)
    - [组合数](#组合数)
      - [逆元+预处理](#逆元预处理)
        - [学习版](#学习版-1)
        - [铁板](#铁板)
      - [lucas定理](#lucas定理)
      - [质因数分解](#质因数分解)
      - [杨辉三角（精确计算）](#杨辉三角精确计算)
    - [矩阵快速幂](#矩阵快速幂)
    - [常见结论](#常见结论)
  - [图论](#图论)
    - [Dijkstra](#dijkstra)
      - [堆优化版](#堆优化版)
      - [朴素版](#朴素版)
      - [usage](#usage)
    - [最小生成树 (MST)](#最小生成树-mst)
      - [Kruskal](#kruskal)
      - [Prim](#prim)
    - [Bellman-Ford](#bellman-ford)
  - [动态规划](#动态规划)


## 基础算法

### 简易IO

```cpp
template <typename T>
inline void read(T &x) {
    x = 0;
    bool f = false;
    char c = getchar();
    while (!isdigit(c)) {
        if (c == '-') f = true;
        c = getchar();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = getchar();
    }
    if (f) x = -x;
}
template <typename T>
inline void write(T x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
    return;
}
```

### 准IO

```cpp
#pragma GCC optimize(2)
#include <bits/stdc++.h>
namespace IO {
constexpr int BUF_SIZE = 1 << 22;
char in_buf[BUF_SIZE], out_buf[BUF_SIZE], *p_in = in_buf + BUF_SIZE, *p_out = out_buf;
char stk[50];

#define gc() (p_in == in_buf + BUF_SIZE ? (fread(in_buf, 1, BUF_SIZE, stdin), p_in = in_buf, *p_in++) : *p_in++)
#define pc(x) \
    (*p_out++ = (x), p_out == out_buf + BUF_SIZE ? (fwrite(out_buf, 1, BUF_SIZE, stdout), p_out = out_buf) : 0)

template <typename T>
inline void read(T &x) {
    x = 0;
    bool f = false;
    char c = gc();
    while (!isdigit(c)) {
        if (c == '-') f = true;
        c = gc();
    }
    while (isdigit(c)) {
        x = x * 10 + (c ^ 48);
        c = gc();
    }
    if (f) x = -x;
}
inline void read(char &c) {
    c = gc();
    while (!isgraph(c)) c = gc();
}
inline void read(std::string &s) {
    s.clear();
    char c = gc();
    while (!isgraph(c)) c = gc();
    while (isgraph(c)) {
        s += c;
        c = gc();
    }
}
inline void getline(std::string &s) {
    s.clear();
    char c = gc();
    while (c == '\n' || c == '\r') {  // 吃掉行首的换行符
        c = gc();
    }
    while (c != '\n' && c != '\r' && c != EOF) {
        s += c;
        c = gc();
    }
}
template <typename T, typename... Args>
inline void read(T &x, Args &...args) {
    read(x);
    read(args...);
}
template <typename T>
inline void write(T x) {
    if (x < 0) {
        pc('-');
        x = -x;
    }
    if (x == 0) {
        pc('0');
        return;
    }
    int top = 0;
    while (x) {
        stk[++top] = (x % 10) ^ 48;
        x /= 10;
    }
    while (top) pc(stk[top--]);
}
inline void write(char c) {
    pc(c);
}
inline void write(const char *s) {
    while (*s) pc(*s++);
}
inline void write(const std::string &s) {
    for (char c : s) pc(c);
}
template <typename T, typename... Args>
inline void write(T x, Args... args) {
    write(x);
    write(args...);
}
struct Flusher {
    ~Flusher() {
        if (p_out != out_buf) {
            fwrite(out_buf, 1, p_out - out_buf, stdout);
            p_out = out_buf;
        }
    }
} flusher;

#undef gc
#undef pc
}
using namespace IO;
```

### 取模运算

```cpp
template <typename T> constexpr T mypow(T n, i64 k) {
    T r = 1;
    for (; k; k /= 2, n *= n) {
        if (k & 1) {
            r *= n;
        }
    }
    return r;
}

template<class T> constexpr T power(int n) {
    return mypow(T(2), n);
}

template<int MOD> struct Zmod {
    int x;
    Zmod(signed x = 0) : x(norm(x % MOD)) {}
    Zmod(i64 x) : x(norm(x % MOD)) {}

    constexpr int norm(int x) const noexcept {
        if (x < 0) [[unlikely]] {
            x += MOD;
        }
        if (x >= MOD) [[unlikely]] {
            x -= MOD;
        }
        return x;
    }
    explicit operator int() const {
        return x;
    }
    constexpr int val() const {
        return x;
    }
    constexpr Zmod operator-() const {
        Zmod val = norm(MOD - x);
        return val;
    }
    constexpr Zmod inv() const {
        assert(x != 0);
        return mypow(*this, MOD - 2);
    }
    friend constexpr auto &operator>>(istream &in, Zmod &j) {
        int v;
        in >> v;
        j = Zmod(v);
        return in;
    }
    friend constexpr auto &operator<<(ostream &o, const Zmod &j) {
        return o << j.val();
    }
    constexpr Zmod &operator++() {
        x = norm(x + 1);
        return *this;
    }
    constexpr Zmod &operator--() {
        x = norm(x - 1);
        return *this;
    }
    constexpr Zmod operator++(signed) {
        Zmod res = *this;
        ++*this;
        return res;
    }
    constexpr Zmod operator--(signed) {
        Zmod res = *this;
        --*this;
        return res;
    }
    constexpr Zmod &operator+=(const Zmod &i) {
        x = norm(x + i.x);
        return *this;
    }
    constexpr Zmod &operator-=(const Zmod &i) {
        x = norm(x - i.x);
        return *this;
    }
    constexpr Zmod &operator*=(const Zmod &i) {
        x = i64(x) * i.x % MOD;
        return *this;
    }
    constexpr Zmod &operator/=(const Zmod &i) {
        return *this *= i.inv();
    }
    constexpr Zmod &operator%=(const int &i) {
        return x %= i, *this;
    }
    friend constexpr Zmod operator+(const Zmod i, const Zmod j) {
        return Zmod(i) += j;
    }
    friend constexpr Zmod operator-(const Zmod i, const Zmod j) {
        return Zmod(i) -= j;
    }
    friend constexpr Zmod operator*(const Zmod i, const Zmod j) {
        return Zmod(i) *= j;
    }
    friend constexpr Zmod operator/(const Zmod i, const Zmod j) {
        return Zmod(i) /= j;
    }
    friend constexpr Zmod operator%(const Zmod i, const int j) {
        return Zmod(i) %= j;
    }
    friend constexpr bool operator==(const Zmod i, const Zmod j) {
        return i.val() == j.val();
    }
    friend constexpr bool operator!=(const Zmod i, const Zmod j) {
        return i.val() != j.val();
    }
    friend constexpr bool operator<(const Zmod i, const Zmod j) {
        return i.val() < j.val();
    }
    friend constexpr bool operator>(const Zmod i, const Zmod j) {
        return i.val() > j.val();
    }
};

constexpr int M = MOD[1];
using Z = Zmod<M>;
```

### 大整数

#### 学习版

```cpp
constexpr int base = 1000000000;
constexpr int base_digits = 9;

struct BigInt {
    vector<int> a;
    int sign;

    /* --- 核心构造与赋值 --- */
    BigInt() : sign(1) {}

    void operator=(i64 v) {
        sign = 1;
        a.clear();
        if (v < 0) { sign = -1; v = -v; }
        for (; v > 0; v = v / base) {
            a.push_back(v % base);
        }
    }

    BigInt(i64 v) {
        *this = v;
    }

    void read(const string& s) {
        sign = 1;
        a.clear();
        int pos = 0;
        if (s.size() > 0 && s[0] == '-') {
            sign = -1;
            pos = 1;
        } else if (s.size() > 0 && s[0] == '+') {
            pos = 1;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++) {
                x = x * 10 + s[j] - '0';
            }
            a.push_back(x);
        }
        trim();
    }

    BigInt(const string& s) {
        read(s);
    }
    
    /* --- 核心辅助函数 --- */
    void trim() {
        while (!a.empty() && !a.back()) {
            a.pop_back();
        }
        if (a.empty()) {
            sign = 1;
        }
    }

    BigInt operator-() const {
        BigInt res = *this;
        if (!a.empty()) {
            res.sign = -sign;
        }
        return res;
    }

    BigInt abs() const {
        BigInt res = *this;
        res.sign = 1;
        return res;
    }

    /* --- 关系运算符 (基于<) --- */
    bool operator<(const BigInt& v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * v.sign;
        return false;
    }
    bool operator>(const BigInt& v) const { return v < *this; }
    bool operator<=(const BigInt& v) const { return !(v < *this); }
    bool operator>=(const BigInt& v) const { return !(*this < v); }
    bool operator==(const BigInt& v) const { return !(*this < v) && !(v < *this); }
    bool operator!=(const BigInt& v) const { return *this < v || v < *this; }

    /* --- 基础加减法 --- */
    BigInt operator+(const BigInt& v) const {
        if (sign == v.sign) {
            BigInt res = *this;
            int carry = 0;
            for (size_t i = 0; i < max(a.size(), v.a.size()) || carry; ++i) {
                if (i == res.a.size()) res.a.push_back(0);
                res.a[i] += carry + (i < v.a.size() ? v.a[i] : 0);
                carry = res.a[i] >= base;
                if (carry) res.a[i] -= base;
            }
            return res;
        }
        return *this - (-v);
    }

    BigInt operator-(const BigInt& v) const {
        if (sign == v.sign) {
            if (abs() < v.abs()) return -(v - *this);
            BigInt res = *this;
            int carry = 0;
            for (size_t i = 0; i < v.a.size() || carry; ++i) {
                res.a[i] -= carry + (i < v.a.size() ? v.a[i] : 0);
                carry = res.a[i] < 0;
                if (carry) res.a[i] += base;
            }
            res.trim();
            return res;
        }
        return *this + (-v);
    }

    /* --- 高频乘除模 (大数-小数) --- */
    BigInt operator*(int v) const {
        BigInt res = *this;
        if (v < 0) { res.sign = -res.sign; v = -v; }
        i64 carry = 0;
        for (size_t i = 0; i < res.a.size() || carry; ++i) {
            if (i == res.a.size()) res.a.push_back(0);
            i64 cur = res.a[i] * (i64)v + carry;
            carry = cur / base;
            res.a[i] = cur % base;
        }
        res.trim();
        return res;
    }

    BigInt operator/(int v) const {
        BigInt res = *this;
        if (v < 0) { res.sign = -res.sign; v = -v; }
        i64 rem = 0;
        for (int i = res.a.size() - 1; i >= 0; --i) {
            i64 cur = res.a[i] + rem * base;
            res.a[i] = cur / v;
            rem = cur % v;
        }
        res.trim();
        return res;
    }

    int operator%(int v) const {
        if (v < 0) v = -v;
        i64 m = 0;
        for (int i = a.size() - 1; i >= 0; --i) {
            m = (a[i] + m * (i64)base) % v;
        }
        return m * sign;
    }

    /* --- 大数乘大数 (o(n^2) "小刀"版) --- */
    BigInt operator*(const BigInt& v) const {
        BigInt res;
        res.sign = sign * v.sign;
        vector<i64> temp(a.size() + v.a.size(), 0);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < v.a.size(); j++)
                temp[i + j] += (i64)a[i] * v.a[j];
        
        i64 carry = 0;
        for (size_t i = 0; i < temp.size() || carry; ++i) {
            i64 cur = (i < temp.size() ? temp[i] : 0) + carry;
            if (i >= res.a.size()) res.a.push_back(0);
            res.a[i] = cur % base;
            carry = cur / base;
        }
        res.trim();
        return res;
    }
};

// 输出流
ostream& operator<<(ostream& stream, const BigInt& v) {
    if (v.sign == -1) stream << '-';
    stream << (v.a.empty() ? 0 : v.a.back());
    for (int i = (int)v.a.size() - 2; i >= 0; --i)
        stream << setw(base_digits) << setfill('0') << v.a[i];
    return stream;
}

// 输入流
istream& operator>>(istream& stream, BigInt& v) {
    string s;
    stream >> s;
    v.read(s);
    return stream;
}
```

#### 完全体
```cpp
constexpr int base = 1000000000;
constexpr int base_digits = 9; // 分解为九个数位一个数字
struct BigInt {
    vector<int> a;
    int sign;

    BigInt() : sign(1) {}
    BigInt operator-() const {
        BigInt res = *this;
        res.sign = -sign;
        return res;
    }
    BigInt(i64 v) {
        *this = v;
    }
    BigInt(const string &s) {
        read(s);
    }
    void operator=(const BigInt &v) {
        sign = v.sign;
        a = v.a;
    }
    void operator=(i64 v) {
        a.clear();
        sign = 1;
        if (v < 0) sign = -1, v = -v;
        for (; v > 0; v = v / base) {
            a.push_back(v % base);
        }
    }

    // 基础加减乘除
    BigInt operator+(const BigInt &v) const {
        if (sign == v.sign) {
            BigInt res = v;
            for (int i = 0, carry = 0; i < (int)max(a.size(), v.a.size()) || carry; ++i) {
                if (i == (int)res.a.size()) {
                    res.a.push_back(0);
                }
                res.a[i] += carry + (i < (int)a.size() ? a[i] : 0);
                carry = res.a[i] >= base;
                if (carry) {
                    res.a[i] -= base;
                }
            }
            return res;
        }
        return *this - (-v);
    }
    BigInt operator-(const BigInt &v) const {
        if (sign == v.sign) {
            if (abs() >= v.abs()) {
                BigInt res = *this;
                for (int i = 0, carry = 0; i < (int)v.a.size() || carry; ++i) {
                    res.a[i] -= carry + (i < (int)v.a.size() ? v.a[i] : 0);
                    carry = res.a[i] < 0;
                    if (carry) {
                        res.a[i] += base;
                    }
                }
                res.trim();
                return res;
            }
            return -(v - *this);
        }
        return *this + (-v);
    }
    void operator*=(int v) {
        check(v);
        for (int i = 0, carry = 0; i < (int)a.size() || carry; ++i) {
            if (i == (int)a.size()) {
                a.push_back(0);
            }
            i64 cur = a[i] * (i64)v + carry;
            carry = (int)(cur / base);
            a[i] = (int)(cur % base);
        }
        trim();
    }
    void operator/=(int v) {
        check(v);
        for (int i = (int)a.size() - 1, rem = 0; i >= 0; --i) {
            i64 cur = a[i] + rem * (i64)base;
            a[i] = (int)(cur / v);
            rem = (int)(cur % v);
        }
        trim();
    }
    int operator%(int v) const {
        if (v < 0) {
            v = -v;
        }
        int m = 0;
        for (int i = a.size() - 1; i >= 0; --i) {
            m = (a[i] + m * (i64)base) % v;
        }
        return m * sign;
    }

    void operator+=(const BigInt &v) {
        *this = *this + v;
    }
    void operator-=(const BigInt &v) {
        *this = *this - v;
    }
    BigInt operator*(int v) const {
        BigInt res = *this;
        res *= v;
        return res;
    }
    BigInt operator/(int v) const {
        BigInt res = *this;
        res /= v;
        return res;
    }
    void operator%=(const int &v) {
        *this = *this % v;
    }

    bool operator<(const BigInt &v) const {
        if (sign != v.sign) return sign < v.sign;
        if (a.size() != v.a.size()) return a.size() * sign < v.a.size() * v.sign;
        for (int i = a.size() - 1; i >= 0; i--)
            if (a[i] != v.a[i]) return a[i] * sign < v.a[i] * sign;
        return false;
    }
    bool operator>(const BigInt &v) const {
        return v < *this;
    }
    bool operator<=(const BigInt &v) const {
        return !(v < *this);
    }
    bool operator>=(const BigInt &v) const {
        return !(*this < v);
    }
    bool operator==(const BigInt &v) const {
        return !(*this < v) && !(v < *this);
    }
    bool operator!=(const BigInt &v) const {
        return *this < v || v < *this;
    }

    BigInt abs() const {
        BigInt res = *this;
        res.sign *= res.sign;
        return res;
    }
    void check(int v) { // 检查输入的是否为负数
        if (v < 0) {
            sign = -sign;
            v = -v;
        }
    }
    void trim() { // 去除前导零
        while (!a.empty() && !a.back()) a.pop_back();
        if (a.empty()) sign = 1;
    }
    bool isZero() const { // 判断是否等于零
        return a.empty() || (a.size() == 1 && !a[0]);
    }
    friend BigInt gcd(const BigInt &a, const BigInt &b) {
        return b.isZero() ? a : gcd(b, a % b);
    }
    friend BigInt lcm(const BigInt &a, const BigInt &b) {
        return a / gcd(a, b) * b;
    }
    void read(const string &s) {
        sign = 1;
        a.clear();
        int pos = 0;
        while (pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
            if (s[pos] == '-') sign = -sign;
            ++pos;
        }
        for (int i = s.size() - 1; i >= pos; i -= base_digits) {
            int x = 0;
            for (int j = max(pos, i - base_digits + 1); j <= i; j++) x = x * 10 + s[j] - '0';
            a.push_back(x);
        }
        trim();
    }
    friend istream &operator>>(istream &stream, BigInt &v) {
        string s;
        stream >> s;
        v.read(s);
        return stream;
    }
    friend ostream &operator<<(ostream &stream, const BigInt &v) {
        if (v.sign == -1) stream << '-';
        stream << (v.a.empty() ? 0 : v.a.back());
        for (int i = (int)v.a.size() - 2; i >= 0; --i)
            stream << setw(base_digits) << setfill('0') << v.a[i];
        return stream;
    }

    /* 大整数乘除大整数部分 */
    typedef vector<i64> vll;
    BigInt operator*(const BigInt &v) const { // 大整数乘大整数
        vector<int> a6 = convert_base(this->a, base_digits, 6);
        vector<int> b6 = convert_base(v.a, base_digits, 6);
        vll a(a6.begin(), a6.end());
        vll b(b6.begin(), b6.end());
        while (a.size() < b.size()) a.push_back(0);
        while (b.size() < a.size()) b.push_back(0);
        while (a.size() & (a.size() - 1)) a.push_back(0), b.push_back(0);
        vll c = karatsubaMultiply(a, b);
        BigInt res;
        res.sign = sign * v.sign;
        for (int i = 0, carry = 0; i < (int)c.size(); i++) {
            i64 cur = c[i] + carry;
            res.a.push_back((int)(cur % 1000000));
            carry = (int)(cur / 1000000);
        }
        res.a = convert_base(res.a, 6, base_digits);
        res.trim();
        return res;
    }
    friend pair<BigInt, BigInt> divmod(const BigInt &a1,
                                       const BigInt &b1) { // 大整数除大整数，同时返回答案与余数
        int norm = base / (b1.a.back() + 1);
        BigInt a = a1.abs() * norm;
        BigInt b = b1.abs() * norm;
        BigInt q, r;
        q.a.resize(a.a.size());
        for (int i = a.a.size() - 1; i >= 0; i--) {
            r *= base;
            r += a.a[i];
            int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
            int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
            int d = ((i64)base * s1 + s2) / b.a.back();
            r -= b * d;
            while (r < 0) r += b, --d;
            q.a[i] = d;
        }
        q.sign = a1.sign * b1.sign;
        r.sign = a1.sign;
        q.trim();
        r.trim();
        return make_pair(q, r / norm);
    }
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
        vector<i64> p(max(old_digits, new_digits) + 1);
        p[0] = 1;
        for (int i = 1; i < (int)p.size(); i++) p[i] = p[i - 1] * 10;
        vector<int> res;
        i64 cur = 0;
        int cur_digits = 0;
        for (int i = 0; i < (int)a.size(); i++) {
            cur += a[i] * p[cur_digits];
            cur_digits += old_digits;
            while (cur_digits >= new_digits) {
                res.push_back((int)(cur % p[new_digits]));
                cur /= p[new_digits];
                cur_digits -= new_digits;
            }
        }
        res.push_back((int)cur);
        while (!res.empty() && !res.back()) res.pop_back();
        return res;
    }
    static vll karatsubaMultiply(const vll &a, const vll &b) {
        int n = a.size();
        vll res(n + n);
        if (n <= 32) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    res[i + j] += a[i] * b[j];
                }
            }
            return res;
        }

        int k = n >> 1;
        vll a1(a.begin(), a.begin() + k);
        vll a2(a.begin() + k, a.end());
        vll b1(b.begin(), b.begin() + k);
        vll b2(b.begin() + k, b.end());

        vll a1b1 = karatsubaMultiply(a1, b1);
        vll a2b2 = karatsubaMultiply(a2, b2);

        for (int i = 0; i < k; i++) a2[i] += a1[i];
        for (int i = 0; i < k; i++) b2[i] += b1[i];

        vll r = karatsubaMultiply(a2, b2);
        for (int i = 0; i < (int)a1b1.size(); i++) r[i] -= a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++) r[i] -= a2b2[i];

        for (int i = 0; i < (int)r.size(); i++) res[i + k] += r[i];
        for (int i = 0; i < (int)a1b1.size(); i++) res[i] += a1b1[i];
        for (int i = 0; i < (int)a2b2.size(); i++) res[i + n] += a2b2[i];
        return res;
    }

    void operator*=(const BigInt &v) {
        *this = *this * v;
    }
    BigInt operator/(const BigInt &v) const {
        return divmod(*this, v).first;
    }
    void operator/=(const BigInt &v) {
        *this = *this / v;
    }
    BigInt operator%(const BigInt &v) const {
        return divmod(*this, v).second;
    }
    void operator%=(const BigInt &v) {
        *this = *this % v;
    }
};
```
 

### 进制转换

```cpp
//$$O(L^2 \cdot \log_b(a))$$
struct Converter {
    // mp:  用于将字符（'0'-'9', 'a'-'z', 'a'-'z'）映射为对应的整数（0-61）。
    // mp2: 用于将整数（0-61）映射回对应的字符。
    vector<int> mp;
    vector<char> mp2;

    Converter() : mp(123), mp2(62) {
        // 映射数字 '0' 到 '9'
        for (int i = 0; i < 10; ++i) {
            mp['0' + i] = i;
            mp2[i] = '0' + i;
        }
        // 映射大写字母 'A' 到 'Z'
        for (int i = 0; i < 26; ++i) {
            mp['A' + i] = i + 10;
            mp2[i + 10] = 'A' + i;
        }
        // 映射小写字母 'a' 到 'z'
        for (int i = 0; i < 26; ++i) {
            mp['a' + i] = i + 36;
            mp2[i + 36] = 'a' + i;
        }
    }

    // 转换前进制 转换后进制 要转换的数据
    string solve(int a, int b, const string &s) {
        vector<int> nums, ans;
        for (auto c : s) {
            nums.push_back(mp[c]);
        }
        reverse(nums.begin(), nums.end());
        while (nums.size()) {  // 短除法，将整个大数一直除 b ，取余数
            int remainder = 0;
            for (int i = nums.size() - 1; i >= 0; i--) {
                nums[i] += remainder * a;
                remainder = nums[i] % b;
                nums[i] /= b;
            }
            ans.push_back(remainder);  // 得到余数
            while (nums.size() && nums.back() == 0) {
                nums.pop_back();  // 去掉前导 0
            }
        }
        reverse(ans.begin(), ans.end());

        string restr;
        for (int i : ans) restr += mp2[i];
        return restr;
    }
};
// usage
void solve() {
    Converter con;

    // 16->10
    int ori = 16, tar = 10;
    string num = "1A";

    string ans = con.solve(ori, tar, num);
    cout << ans;
    // 16进制的 "1A" 是 1*16 + 10 = 26
}
```

### 离散化

```cpp
struct Disc {
    vi values; // 存储排序去重后的所有唯一值

    Disc(const vi& initial_data) {
        values = initial_data;
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    int get_id(int x) const {
        return lower_bound(values.begin(), values.end(), x) - values.begin() + 1;
    }

    int get_val(int id) const {
        // 在竞赛中，可以不加 assert 以追求极致性能，但加上更安全
        // assert(id >= 1 && id <= values.size());
        return values[id - 1];
    }
    
    vi map_data(const vi& data_to_map) const {
        vi mapped;
        mapped.reserve(data_to_map.size());
        for (int val : data_to_map) {
            mapped.push_back(get_id(val));
        }
        return mapped;
    }

    int size() const {
        return values.size();
    }
};
```


## 数据结构

### ST表

```cpp
template <typename T>
T myGcd(T a, T b) {
    return b == T(0) ? a : myGcd(b, a % b);
}

template <typename T>
struct ST {
    const int n, k;
    vector<vector<T>> Max, Min, Gcd;

    ST(int size) : n(size), k(size > 0 ? __lg(size) : 0) {
        Max.resize(k + 1, vector<T>(n + 1));
        Min.resize(k + 1, vector<T>(n + 1));
        Gcd.resize(k + 1, vector<T>(n + 1));
    }

    void init(const vector<T>& arr) {
        for (int i = 1; i <= n; ++i) {
            Max[0][i] = arr[i];
            Min[0][i] = arr[i];
            Gcd[0][i] = arr[i];
        }

        for (int i = 0; i < k; ++i) {
            int t = (1 << i);
            for (int j = 1; j + (t << 1) - 1 <= n; ++j) {
                Max[i + 1][j] = max(Max[i][j], Max[i][j + t]);
                Min[i + 1][j] = min(Min[i][j], Min[i][j + t]);
                // 调用模板化的 gcd 函数
                Gcd[i + 1][j] = myGcd(Gcd[i][j], Gcd[i][j + t]);
            }
        }
    }

    // 5. 查询函数的返回值变为 T
    T getMax(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return max(Max[len_log][l], Max[len_log][r - (1 << len_log) + 1]);
    }

    T getMin(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return min(Min[len_log][l], Min[len_log][r - (1 << len_log) + 1]);
    }

    T getGcd(int l, int r) {
        if (l > r) swap(l, r);
        int len_log = __lg(r - l + 1);
        return myGcd(Gcd[len_log][l], Gcd[len_log][r - (1 << len_log) + 1]);
    }
};
```

### 并查集 (DSU) - 路径压缩 + 按秩序合并

```cpp
struct Dsu {
    vector<int> fa, sz, ed;
    vector<bool> cy;

    Dsu(int n) : fa(n + 1), sz(n + 1, 1), ed(n + 1), cy(n + 1, false) {
        iota(fa.begin(), fa.end(), 0);
    }
    int find(int x) {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    }
    bool mg(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx == fy) {
            ed[fx]++;
            cy[fx] = true;
            return false;
        }
        if (sz[fx] < sz[fy]) {
            swap(fx, fy);
        }
        fa[fy] = fx;
        sz[fx] += sz[fy];
        ed[fx] += ed[fy];
        ed[fx]++;
        cy[fx] = cy[fx] || cy[fy];
        return true;
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool sc(int x) {
        return cy[find(x)];
    }
    int ecnt(int x) {
        return ed[find(x)];
    }
    int pcnt(int x) {
        return sz[find(x)];
    }
};
```

### 树状数组

```cpp
template <typename T>
struct Fenwick {
    int n;
    vector<T> a;

    Fenwick(int n_) : n(n_), a(n_ + 1, T{}) {}

    void add(int x, const T &v) {
        for (int i = x; i <= n; i += i & -i) {
            a[i] = a[i] + v;
        }
    }

    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i];
        }
        return ans;
    }

    T rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    int select(const T &k) {
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i >>= 1) {
            if (x + i <= n && cur + a[x + i] <= k) {
                x += i;
                cur = cur + a[x];
            }
        }
        return x;
    }
};
```


## 字符串算法
<!-- 在这里开始添加你的“字符串算法”模板，比如KMP、AC自动机、后缀数组等 -->


## 数论


### 质因子分解

#### 筛法

```cpp
vector<int> prime, minp, maxp;
/**
 * @brief 线性筛 (欧拉筛)
 * @param n 筛选的上限，默认为 10^7
 * @note  该函数用于预处理 1 到 n 范围内所有数的最小和最大质因子。
 *  预处理时间复杂度为 O(n)
 *  查询复杂度	O(log n）
 *  空间复杂度 O(n)
 */
void sieve(int n = 1e7) {
    minp.resize(n + 1);
    maxp.resize(n + 1);

    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            maxp[i] = i;
            prime.push_back(i);
        }

        for (auto p : prime) {
            if (p > minp[i] || p > n / i) break;

            minp[i * p] = p;
            maxp[i * p] = maxp[i];
        }
    }
}

/**
 * @brief 对整数 n 进行质因数分解
 * @param n 需要分解的整数
 * @return  一个 vector, 包含 {质因子, 次数} 的 array 对。
 * @note    时间复杂度为 O(log n)。
 */
vector<array<int, 2>> factorize(int n) {
    vector<array<int, 2>> ans;
    // 循环直到 n 被分解为 1
    while (n > 1) {
        // 获取 n 当前的最小质因子
        int now = minp[n];
        int cnt = 0;  // 用于计算该质因子的出现次数

        // 不断从 n 中除去这个最小质因子, 并计数
        while (n > 1 && n % now == 0) {  // n>1 的检查是可选的, 但更稳健
            n /= now;
            cnt++;
        }
        // 将 {质因子, 次数} 这个数对存入结果
        ans.push_back({now, cnt});
    }
    return ans;
}
```

### 快速幂

```cpp
//防爆mul
i64 hmul(i64 a, i64 b) {
    return (i128)a * b % mod;
}

i64 hmul(i64 a, i64 b) {
    i64 ans= 0;
    a %= mod;
    while (b) {
        if (b & 1) {
            ans = (ans + a) % mod;
        }
        a = a * 2 % mod;
        b >>= 1;
    }
    return ans;
}

i64 qpow(i64 n, i64 k) {
    i64 ans = 1;
    n %= mod;
    while (k) {
        if (k & 1) {
            ans = ans * n % mod;
        }
        n = n * n % mod;
        k >>= 1;
    }
    return ans;
}
```

### 逆元

```cpp
//费马小定理求逆元（mod必须是质数，且需要满足 x 与mod互质
i64 inv(i64 a) { 
    return qpow(a, mod- 2);
}

//
```

### 组合数

#### 逆元+预处理

##### 学习版

[快速幂](#快速幂)
[逆元](#逆元)

```cpp
i64 fac[maxm], invfac[maxm];

void init(int n) {
    fac[0] = 1;
    for (int i = 1; i <= n; ++i) {
        fac[i] = (fac[i - 1] * i) % mod;
    }
    // 计算最大阶乘的逆元，然后递推
    invfac[n] = inv(fac[n]);
    for (int i = n - 1; i >= 0; --i) {
        invfac[i] = (invfac[i + 1] * (i + 1)) % mod;
    }
}

i64 comb(int n, int m) {
    return (((fac[n] * invfac[m]) % mod) * invfac[n - m]) % mod;
}
```

##### 铁板

[取模运算](#取模运算)

```cpp

// 场景: n, m 较小 (< 10^7), 模数 P 是一个大质数。
// O(N) 预处理, O(1) 查询。
struct Comb {
    int n_mx;
    vector<Z> _fac, _invfac;
 
    Comb() : n_mx{0}, _fac{1}, _invfac{1} {}
    
    //init函数实现增量式初始化, 避免重复计算
    void init(int m) {
        if (m <= n_mx) return;
        int prev_n = n_mx;
        n_mx = m;
        _fac.resize(n_mx + 1);
        _invfac.resize(n_mx + 1);
        for (int i = prev_n + 1; i <= n_mx; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[n_mx] = _fac[n_mx].inv();
        for (int i = n_mx; i > prev_n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
        }
    }
    
    //C 和 P 函数内部增加自动初始化
    Z C(int n, int m) {
        if (m < 0 || m > n) return 0;
        if (n > n_mx) init(n);
        return _fac[n] * _invfac[m] * _invfac[n - m];
    }
    
    Z P(int n, int m) {
        if (m < 0 || m > n) return 0;
        if (n > n_mx) init(n); 
        return _fac[n] * _invfac[n - m];
    }
};
```
#### lucas定理

#### 质因数分解

#### 杨辉三角（精确计算）

```cpp
//<60,i64 <130,i128
vector C(n + 1, vector<i64>(n + 1));
C[0][0] = 1;
for (int i = 1; i <= n; i++) {
    C[i][0] = 1;
    for (int j = 1; j <= n; j++) {
        C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
}
cout << C[n][m] << endl;
```
### 矩阵快速幂

```cpp
struct Matrix {
    int n;
    vector<vector<i64>> mat;

    Matrix(int n_) : n(n_), mat(n_, vector<i64>(n_, 0)) {}
};

Matrix operator*(const Matrix& a, const Matrix& b) {
    Matrix c(a.n); 
    for (int i = 0; i < a.n; i++) {
        for (int j = 0; j < a.n; j++) {
            for (int k = 0; k < a.n; k++) {
                c.mat[i][j] = (c.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % mod;
            }
        }
    }
    return c;
}

Matrix matrix_pow(Matrix base, i64 exp) {
    Matrix res(base.n); 
    for (int i = 0; i < base.n; i++) {
        res.mat[i][i] = 1;
    }

    while (exp > 0) {
        if (exp % 2 == 1) {
            res = res * base;
        }
        base = base * base;
        exp /= 2;
    }
    return res;
}

//usage
void solve() {
    int n;
    i64 k;
    cin >> n >> k;

    Matrix base(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> base.mat[i][j];
        }
    }

    Matrix result = matrix_pow(base, k);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << result.mat[i][j] << (j == n - 1 ? "" : " ");
        }
        cout << '\n';
    }
}

```


### 常见结论
*   **曲棍球棒恒等式：**

$$\begin{cases}
\sum_{i = r}^{n} C_{i}^{r} = C_{r}^{r} + C_{r + 1}^{r} + \cdots + C_{n}^{r} = C_{n + 1}^{r + 1} & \text{(形式一: 下标固定)} \\
\sum_{i = k}^{n} C_{i}^{i - k} = C_{k}^{0} + C_{k + 1}^{1} + \cdots + C_{n}^{n - k} = C_{n + 1}^{k + 1} & \text{(形式二: 差值固定)}
\end{cases}$$

*   **容斥原理：**
    $$\left|\bigcup_{i = 1}^{N} P_{i}\right| = \sum_{i}\left|P_{i}\right| - \sum_{i < j}\left|P_{i} \cap P_{j}\right| + \sum_{i < j < k}\left|P_{i} \cap P_{j} \cap P_{k}\right| - \cdots + (-1)^{N - 1}\left|P_{1} \cap \cdots \cap P_{N}\right| \quad \text{(求并集大小：至少满足一个性质)}$$



## 图论

### Dijkstra 

#### 堆优化版

```cpp
// 堆优化O(M log N)
struct Fdijkstra {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<i64> dist;
    vector<int> fa;  // fa 存储最短路树中的父节点，用于路径回溯

    Fdijkstra(int n_) : n(n_), adj(n_ + 1), dist(n_ + 1), fa(n_ + 1) {}

    // 若无向图，需要为两个方向都添加边
    void ad(int u, int v, int w) {
        adj[u].emplace_back(v, w);
    }

    void run(int st) {
        // 初始化距离为无穷大，父节点为0,从不同起点跑一次都要fill一次
        fill(dist.begin(), dist.end(), linf);
        fill(fa.begin(), fa.end(), 0);
        dist[st] = 0;

        using Node = pair<i64, int>;  // {distance, vertex}

        priority_queue<Node, vector<Node>, greater<Node>> pq;
        pq.push({0, st});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) {
                continue;
            }

            for (const auto& edge : adj[u]) {
                auto [v, w] = edge;
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    fa[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // 获取到终点 t 的最短路径
    vector<int> get_path(int t) {
        vector<int> path;

        if (dist[t] == linf) {
            return path;  // 不可达
        }

        // 通过 fa 数组从终点回溯到起点，构建路径
        // 循环在 t 变为 0 时终止（起点的父节点被初始化为0）
        for (; t != 0; t = fa[t]) {
            path.push_back(t);
        }

        // 因为路径是反向构建的（从终点到起点），所以需要反转
        reverse(path.begin(), path.end());
        return path;
    }
};
```
#### 朴素版

```cpp
// 朴素：o(n^2)，适用于 m 比较大，n(顶点) 很小的情况
struct Sdijkstra {
    int n;
    vector<vector<int>> adj;
    vector<i64> dist;
    vector<bool> vis;

    Sdijkstra(int n_) : n(n_), adj(n_ + 1, vector<int>(n_ + 1, inf)), dist(n_ + 1, linf), vis(n_ + 1, false) {
        for (int i = 1; i <= n; ++i) {
            adj[i][i] = 0;
        }
    }

    void ad(int u, int v, int w) {
        adj[u][v] = min(adj[u][v], w);
    }
    void run(int st) {
        fill(dist.begin(), dist.end(), linf);
        fill(vis.begin(), vis.end(), false);
        dist[st] = 0;

        for (int i = 1; i <= n; ++i) {
            int u = -1;
            for (int j = 1; j <= n; ++j) {
                if (!vis[j] && (u == -1 || dist[j] < dist[u])) u = j;
            }

            if (u == -1 || dist[u] >= linf) {
                break;
            }
            vis[u] = true;

            for (int v = 1; v <= n; ++v) {
                if (adj[u][v] != inf && dist[v] > dist[u] + adj[u][v]) {
                    dist[v] = dist[u] + adj[u][v];
                }
            }
        }
    }
};
```

#### usage

```cpp
void solve() {
    int n, m, s;
    cin >> n >> m >> s;
    Fdijkstra dij(n);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        dij.ad(u, v, w);
        // 无向图att
    }

    dij.run(s);  // 3. 从源点 s 开始运行算法
    // 4. 输出到各个点的最短距离
    for (int i = 1; i <= n; ++i) {
        if (dij.dist[i] == linf) {
            cout << -1 << ' ';
        } else {
            cout << dij.dist[i] << ' ';
        }
    }
    cout << '\n';

    // (可选) 打印从源点 s 到终点 n 的路径
    vector<int> path = dij.get_path(n);
    if (!path.empty()) {
        cout << "Path to " << n << ": ";
        for (int i = 0; i < path.size(); ++i) {
            cout << path[i] << (i == path.size() - 1 ? "" : " -> ");
        }
        cout << '\n';
    }
}
```

### 最小生成树 (MST) 

[并查集 (DSU) - 路径压缩 + 按秩序合并](#并查集-dsu---路径压缩--按秩序合并)

#### Kruskal

```cpp
struct Mstk {
    struct Edge {
        int u, v, w;
        bool operator<(const Edge& other) const {
            return w < other.w;
        }
    };
    int n;
    vector<Edge> edges;
    Mstk(int n_, int m_) : n(n_) {
        edges.reserve(m_);
    }
    void ad(int u, int v, int w) {
        edges.push_back({u, v, w});
    }
    i64 run() {
        sort(edges.begin(), edges.end());
        Dsu dt(n);
        i64 mnw = 0;

        int cnt = 0;
        for (const auto& t : edges) {
            if (dt.mg(t.u, t.v)) {
                mnw += t.w;
                ++cnt;
            }
        }
        return (cnt == n - 1) ? mnw : -1;
    }
};

// usage
void solve() {
    int n, m;
    read(n, m);

    Mstk mst(n, m);

    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        mst.ad(u, v, w);
    }
    i64 ans = mst.run();
}
```

#### Prim
```cpp
struct mstp {
    int n;
    vii adj;
    vi dist;
    vector<bool> vis;

    mstp(int nn) : n(nn), adj(nn + 1, vi(n + 1, linf)), dist(n + 1, linf), vis(n + 1, false) {
        fo(i, 1, n) adj[i][i] = 0;
    }
    void ad(int u, int v, int w) {
        adj[u][v] = min(adj[u][v], w);
        adj[v][u] = min(adj[v][u], w);
    }

    i64 run(int st) {
        dist[st] = 0;
        i64 totalw = 0;
        int cnt = 0;
        fo(i, 1, n) {
            int u = -1;
            fo(j, 1, n) {
                if (!vis[j] && (u == -1 || dist[j] < dist[u])) u = j;
            }
            if (u == -1 || dist[u] >= linf) return -1;  // 不连通
            vis[u] = true;
            totalw += dist[u];
            cnt++;

            fo(v, 1, n) {
                if (!vis[v] && dist[v] > adj[u][v]) {
                    dist[v] = adj[u][v];
                }
            }
        }
        return (cnt == n) ? totalw : -1;
    }
};
```

### Bellman-Ford
```cpp
struct Bellman_Ford {
    int n;
    vector<tuple<int, int, i64>> edges;
    vector<i64> dist;

    Bellman_Ford(int n_) : n(n_), dist(n_ + 1) {}

    void ad(int u, int v, i64 w) {
        edges.emplace_back(u, v, w);
    }

    // 判断是否存在从起点可达的负权环
    bool run(int st) {
        fill(dist.begin(), dist.end(), linf);
        dist[st] = 0;

        // 核心：进行 n-1 轮松弛
        for (int i = 1; i < n; ++i) {
            bool upd = false;
            for (const auto& edge : edges) {
                auto [u, v, w] = edge;
                if (dist[u] != linf && dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    upd = true;
                }
            }
            if (!upd) break;
        }

        // 检测负权环：进行第 n 轮检查
        for (const auto& edge : edges) {
            auto [u, v, w] = edge;
            if (dist[u] != linf && dist[v] > dist[u] + w) {
                // 如果在第 n 轮仍然可以松弛，说明存在负权环
                return false;
            }
        }

        return true;
    }
};
```


## 动态规划
<!-- 在这里开始添加你的“动态规划”模板，比如背包DP、区间DP、插头DP等 -->

jk