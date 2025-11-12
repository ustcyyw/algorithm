/**
 * @Time : 2023/12/12-8:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 以2个格子为一组 有且仅有两个格子不同时 才能进行修改
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
int T, n;
string s;

void solve() {
    int cnt = 0, half = n / 2;
    vector<vector<int>> dp(1 + half, vector(2, N));
    dp[0][0] = dp[0][1] = 1;
    for(int i = 0; i < half; i++) {
        int j = 2 * i;
        if(s[j] != s[j + 1]) { // 可以任意修改这一段为0或者1
            cnt++;
            dp[i + 1][0] = min(dp[i][0], dp[i][1] + 1);
            dp[i + 1][1] = min(dp[i][1], dp[i][0] + 1);
        } else { // 不能修改的情况
            int e = s[j] - '0', ne = (e + 1) % 2;
            dp[i + 1][e] = min(dp[i][e], dp[i][ne] + 1);
        }
    }
    cout << cnt << " " << min(dp[half][0], dp[half][1]) << endl;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n, cin >> s;
        solve();
    }
};