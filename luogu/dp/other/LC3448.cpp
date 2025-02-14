/**
 * @Time : 2025/2/13-9:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3448 动态规划 余数相关
 */
 /*
  * 枚举结尾的数字x
  * dp[i][j]：以i为末尾位置 余数为j的子串的数目
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
ll dp[N][10];

class Solution {
public:
    long long countSubstrings(string s) {
        int n = s.size();
        ll ans = 0;
        function<void(int)> cal = [&](int m) -> void {
            memset(dp, 0, sizeof(dp));
            for(int i = 1; i <= n; i++) {
                int num = s[i - 1] - '0';
                for(int j = 0; j < m; j++)
                    dp[i][(j * 10 + num) % m] += dp[i - 1][j];
                dp[i][num % m] += 1; // 当前字符作为子串开头
                if(num == m) ans += dp[i][0];
            }
        };
        for(int i = 1; i <= 9; i++)
            cal(i);
        return ans;
    }
};