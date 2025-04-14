/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
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