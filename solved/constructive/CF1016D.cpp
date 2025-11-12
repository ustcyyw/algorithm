/**
 * @Time : 2025/4/13-11:35 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 位运算的每一位独立 因此只考虑单独的一位
  * d位上，行和列的异或和中 为1的数分别有cnt1, cnt2个
  * 如果cnt1 = cnt2，每次在相应的行和列放1个1，其它行列就都是0即可
  * 但是cnt1 != cnt2，那先将min(cnt1, cnt2)个1放置完后
  * 行或者列还有需要放置1的，如果剩奇数个1，不管放在哪行哪列 都会导致异或值不对
  * 如果列剩偶数个1，行已经安排好了，将这些1都放在第一行相应还需要放的列上
  * （因为是偶数个1 所以不影响第一行的结果）
  * 如果行剩偶数个1，列已经安排好了，同理操作即可。
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e2 + 15, M = 30;
ll n, m, a[N], b[N], ans[N][N];

bool digit(int d) {
    int temp = 1 << d;
    vector<int> row, col;
    for(int i = 1; i <= n; i++)
        if(a[i] & temp) row.push_back(i);
    for(int i = 1; i <= m; i++)
        if(b[i] & temp) col.push_back(i);
    int cnt1 = row.size(), cnt2 = col.size(), cnt = max(cnt1, cnt2);
    if(abs(cnt1 - cnt2) % 2 != 0) return false;
    for(int k = 0, i = 0, j = 0; k < cnt; k++) {
        if(i == cnt1) ans[1][col[j]] |= temp, j++;
        else if(j == cnt2) ans[row[i]][1] |= temp, i++;
        else ans[row[i]][col[j]] |= temp, i++, j++;
    }
    return true;
}

void solve() {
    for(int i = 0; i <= 31; i++) {
        if(!digit(i)) {
            cout << "NO";
            return;
        }
    }
    cout << "YES\n";
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++)
            cout << ans[i][j] << " ";
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= m; i++)
        cin >> b[i];
    solve();
}