/**
 * @Time : 2025/2/14-11:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF665C 1300 动态规划
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, dp[N][26], infos[N][26];
string s;

void solve() {
    int v1 = 0, c1 = 0, v2 = 0, c2 = 0;
    for(int i = 1; i < n; i++) {
        int cc = s[i] - 'a', vt1 = INT_MAX, ct1, vt2 = INT_MAX, ct2;
        for(int j = 0; j < 26; j++) {
            int add = cc != j;
            if(j != c1) dp[i][j] = v1 + add, infos[i][j] = c1;
            else dp[i][j] = v2 + add, infos[i][j] = c2;
            if(dp[i][j] < vt1) {
                vt2 = vt1, ct2 = ct1;
                vt1 = dp[i][j], ct1 = j;
            } else if(dp[i][j] < vt2) vt2 = dp[i][j], ct2 = j;
        }
        v1 = vt1, c1 = ct1, v2 = vt2, c2 = ct2;
    }
    int c = -1, v = INT_MAX;
    for(int j = 0; j < 26; j++)
        if(dp[n - 1][j] < v) v = dp[n - 1][j], c = j;
    for(int i = n - 1; i >= 1; i--) {
        s[i] = (char)(c + 'a');
        c = infos[i][c];
    }
    cout << s.substr(1);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> s;
        s = '.' + s, n = s.size();
        solve();
    }
};