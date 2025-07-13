#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll computeParity(const vector<ll>& p) {
    // 使用循环分解法计算逆序数奇偶性：sign = (–1)^(n - cycle_count)
    // p 是 1-indexed排列，长度为 n+1, p[1..n] 有效
    ll n = p.size()-1;
    vector<bool> vis(n+1, false);
    ll cycles = 0;
    for (ll i = 1; i <= n; i++){
        if (!vis[i]){
            cycles++;
            ll cur = i;
            while (!vis[cur]){
                vis[cur] = true;
                cur = p[cur];
            }
        }
    }
    // 奇数当且仅当 (n - cycles) % 2 == 1 
    return (n - cycles) & 1;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int t; cin >> t;
    while(t--){
        ll n; 
        cin >> n;
        vector<ll> A(n+1), B(n+1);
        for (ll i = 1; i <= n; i++) cin >> A[i];
        for (ll i = 1; i <= n; i++) cin >> B[i];
        
        // 计算 A，B 的逆序数奇偶性（即置换符号）
        ll pA = computeParity(A);
        ll pB = computeParity(B);
        
        string ans = "";
        // 第一局：根据两个逆序数奇偶比较决定胜者
        ans.push_back( ((pA ^ pB)&1) ? 'A':'B' );
        
        // 对 n-1 次修改操作，每次只更新对应排列的逆序数奇偶性
        for (ll i = 2; i <= n; i++){
            char t;
            ll l, r, d;
            cin >> t >> l >> r >> d;
            ll L = r - l + 1;
            d %= L;
            // 求 gcd，注意 d==0 时不会改变排列，也不改变符号
            if(d != 0){
                ll g = std::gcd(d, L);
                // 左循环移动 d 后置换的符号为 (–1)^(L - g)
                // 若 (L - g) 为奇数，则对应排列的逆序奇偶性翻转
                if((L - g) & 1){
                    if(t == 'A'){
                        pA ^= 1;
                    } else {
                        pB ^= 1;
                    }
                }
            }
            ans.push_back( ((pA ^ pB) & 1) ? 'A' : 'B' );
        }
        cout << ans << "\n";
    }
    return 0;
}