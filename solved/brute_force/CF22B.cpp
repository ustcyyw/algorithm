/**
 * @Time : 2025/1/27-3:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF22B 1500 暴力枚举
 */
 /*
  * 暴力枚举矩形的左上端点
  * 对于每个左上端点 枚举其高 其底就由高所涉及的行1的位置确定
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, n, m;
string grid[26];

void cal(vector<int>& row, string& s) {
    for(int i = m - 1, j = m; i >= 0; i--) {
        if(s[i] == '1') j = i;
        row[i] = j;
    }
}

void solve() {
    vector<vector<int>> rows(n, vector(m, m));
    for(int i = 0; i < n; i++)
        cal(rows[i], grid[i]);
    int ans = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '1') continue;
            int d = INT_MAX;
            for(int k = i; k < n && grid[k][j] != '1'; k++) {
                d = min(d, rows[k][j]);
                int l1 = k - i + 1, l2 = d - j;
                ans = max(ans, l1 * 2 + l2 * 2);
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> m;
        for(int i = 0; i < n; i++)
            cin >> grid[i];
        solve();
    }
};