#include <bits/stdc++.h>
using namespace std;
#define int long long
constexpr int mod = 1000000007;

vector<int> fact;
vector<int> invFact;

int qpow(int base, int exp)
{
    int res = 1;
    base %= mod;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

void precompute_factorials(int max_val)
{
    fact.resize(max_val + 1);
    invFact.resize(max_val + 1);
    fact[0] = 1;
    for (int i = 1; i <= max_val; ++i)
    {
        fact[i] = (fact[i - 1] * i) % mod;
    }
    invFact[max_val] = qpow(fact[max_val], mod - 2);
    for (int i = max_val - 1; i >= 0; --i)
    {
        invFact[i] = (invFact[i + 1] * (i + 1)) % mod;
    }
}

int comb(int n, int k)
{
    if (k < 0 || k > n)
    {
        return 0;
    }
    return fact[n] * invFact[k] % mod * invFact[n - k] % mod;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
    }

    if (n == 1)
    {
        cout << __builtin_popcountll(a[0] + m) << '\n';
        return;
    }

    precompute_factorials(m);

    int ans = 0;
    int inv_n_minus_1 = qpow(n - 1, mod - 2);
    int current_pow_n_minus_1 = qpow(n - 1, m);

    for (int k = 0; k <= m; ++k)
    {
        int C_mk = comb(m, k);
        int ways_k = (C_mk * current_pow_n_minus_1) % mod;

        int popcount_sum_k = 0;
        for (int i = 0; i < n; ++i)
        {
            popcount_sum_k += __builtin_popcountll(a[i] + k);
        }

        ans = (ans + ways_k * popcount_sum_k) % mod;

        if (k < m)
        {
            current_pow_n_minus_1 = (current_pow_n_minus_1 * inv_n_minus_1) % mod;
        }
    }

    cout << ans << '\n';
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}