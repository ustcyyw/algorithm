/**
 * @Time : 2023/2/24-10:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        s = '!' + s, p = '!' + p; // 设置哨兵
        string temp;
        vector<bool> flag;
        for(char c : p){ // 去除*号。并且标记哪些字符属于*匹配
            if(c == '*') flag.back() = true;
            else temp.push_back(c), flag.push_back(false);
        }
        p = temp;
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(n, vector(m, false));
        dp[0][0] = true;
        // 可能会出现前缀有多个带*的字符 这些字符都可以只匹配0个，那么就等价于s[0,0],p[0,i]都是空串，是匹配的
        for(int i = 1; i < m && flag[i]; i++)
            dp[0][i] = true;
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(!flag[j]){
                    dp[i][j] = dp[i - 1][j - 1];
                    if(p[j] != '.') dp[i][j] = dp[i][j] && p[j] == s[i];
                } else {
                    dp[i][j] = dp[i][j - 1]; // *字符匹配0次的情况
                    if(p[j] == '.'){ // .匹配任意字符，只要存在 dp[k][j - 1]是匹配的，那么可以用p[j]去匹配s[k + 1, i]
                        for(int k = 0; k <= i && !dp[i][j]; k++)
                            dp[i][j] = dp[k][j - 1];
                    } else { // 只能匹配任意多个相同字母，需要保证p[j]与s[k, i]上的字符都是同一个,并且dp[k - 1][j - 1]匹配
                        for(int k = i; k > 0 && s[k] == p[j] && !dp[i][j]; k--){
                            dp[i][j] = dp[k - 1][j - 1];
                        }
                    }
                }
            }
        }
        return dp[n - 1][m - 1];
    }
};

int main(){
    Solution s;
    s.isMatch("aab", "c*a*b");
    cout << 0 << endl;
}