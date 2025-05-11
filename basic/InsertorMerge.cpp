//https://pintia.cn/problem-sets/994805342720868352/exam/problems/type/7?problemSetProblemId=994805377432928256&page=0

#include <bits/stdc++.h>
using namespace std;
typedef __int128_t i128;
const int m = 1e9 + 7;
#define int long long
int a[105], b[105], aa[105], temparr[105];
int n;
bool issame(int a[], int b[])
{
  for (int i = 0; i < n; i++)
    if (a[i] != b[i])
      return false;
  return true;
}

void msort()
{
  bool flag = false;
  for (int step = 2; step / 2 <= n; step *= 2)
  {
    if (step!=2 && issame(a, aa))
    {
      flag = true;
    }
    
    // 正确的归并排序应该是每隔step个元素作为起点
    for (int i = 0; i < n; i += step)
    {
      sort(a + i, a + min(i + step, n));
    }
    if (flag)
    {
      return;
    }
  }
}

bool insertion_sort()
{
  bool flag = false;
  for (int i = 1; i < n; i++)
  {
    if (i!=1 && issame(temparr, aa))
    {
      flag = true;
    }
    int t = temparr[i];
    int j = i - 1;
    while (j >= 0 && temparr[j] > t)
    {
      temparr[j + 1] = temparr[j];
      j--;
    }
    temparr[j + 1] = t;
    if (flag)
    {
      return true;
    }
  }
  return false;
}
void solve()
{
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    temparr[i] = a[i];
  }
  for (int i = 0; i < n; i++)
    cin >> aa[i];
  if (insertion_sort())
  {
    cout << "Insertion Sort" << endl;
    cout << temparr[0];
    for (int i = 1; i < n; i++)
      cout << " " << temparr[i];
    return;
  }
  else
  {
    cout << "Merge Sort" << endl;
    msort();
    cout << a[0];
    for (int i = 1; i < n; i++)
      cout << " " << a[i];
  }
}

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  solve();
  return 0;
}