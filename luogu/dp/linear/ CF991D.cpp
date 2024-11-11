/**
 * @Time : 2024/1/18-3:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int minV = -(int)1e9;
string s1, s2;

int status(int i) {
    if(s1[i] == '0')
        return s2[i] == '0' ? 0 : 2;
    return s2[i] == '0' ? 1 : 3;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s1 >> s2;
    int n = s1.size();
    vector<vector<int>> dp(n, vector(4, minV));
    dp[0][status(0)] = 0;
    for(int i = 1; i < n; i++) {
        int s = status(i);
        dp[i][s] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2], dp[i-1][3]});
        if(s == 0) {
            dp[i][1] = dp[i - 1][0] + 1;
            dp[i][2] = dp[i - 1][0] + 1;
            dp[i][3] = max({dp[i-1][0], dp[i-1][1], dp[i-1][2]}) + 1;
        } else if(s == 1 || s == 2) dp[i][3] = dp[i - 1][0] + 1;
    }
    cout << max({dp[n - 1][0], dp[n - 1][1], dp[n - 1][2], dp[n - 1][3]}) << endl;
}