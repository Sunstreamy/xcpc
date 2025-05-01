//快速幂
#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
#define N 200005

i64 quick_pow(i64 a,i64 n, i64 p)
{
    i64 res = 1;
    while(n)
    {
        if(n&1)
            res = res * a % p;
        a = a * a % p;
        n >>= 1;
    }
    return res;

}