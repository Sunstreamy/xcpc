#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef __int128_t i128;
const int M = 1e9 + 7;
#define N 200005

int s,n,m;
int ans;
int vis[105][105];

void dfs(int a,int b,int cnt)
{
    int c=s-a-b;
    if(c==s/2){
        ans=min(ans,cnt);
        return;
    }
    if(cnt>=ans) return;
    if(vis[a][b]!=-1 && vis[a][b]<=cnt) return;
        vis[a][b]=cnt;
    int cur[3]={a,b,c};
    int cap[3]={n,m,s};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(i==j) continue;
            if(cur[i]==0 || cur[j]==cap[j])continue;
            int vol=min(cur[i],cap[j]-cur[j]);
            int nxt[3];
            for(int k=0;k<3;k++){
                nxt[k]=cur[k];
            }
            nxt[i]-=vol;
            nxt[j]+=vol;
            dfs(nxt[0],nxt[1],cnt+1);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    while(cin>>s>>n>>m){
        if(s==0 && n==0 && m==0) break;
        if(s%2==1)
        {
            cout<<"NO"<<'\n';
            continue;
        } 
        ans=M;
        for(int i=0;i<105;i++)
        {
            for(int j=0;j<105;j++)
            {
                vis[i][j]=-1;
            }
        }
        dfs(0,0,0);
        if(ans==M) cout<<"NO"<<'\n';
        else cout<<ans<<'\n';
    }

    return 0;
}
