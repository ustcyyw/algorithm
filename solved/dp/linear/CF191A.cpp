/**
 * @Time : 2024/1/15-7:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * dp[i][c1][c2] 截止第i的字符串 以c1开头且以c2结尾的最长字符序列
 *
 * s[i] 以p开头 以c为结尾 长度为l
 * dp[i][c1][c] = max(dp[i][c1][c], dp[i-1][c1][p] + l)
 * 可以滚动优化
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;
int n, dp[26][26];
string s;

int main(){
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < 26; i++)
        memset(dp[i], 0, sizeof(dp[i]));
    int res = 0;
    for(int i = 0; i < n; i++) {
        cin >> s;
        int l = s.size(), p = s[0] - 'a', c = s[l - 1] - 'a';
        for(int j = 0; j < 26; j++) { // 枚举开头字符
            if(dp[j][p] != 0)
                dp[j][c] = max(dp[j][c], dp[j][p] + l);
        }
        dp[p][c] = max(dp[p][c], l);
        for(int j = 0; j < 26; j++)
            res = max(res, dp[j][j]);
    }
    cout << res << endl;
}