/**
 * @Time : 2023/3/14-9:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * dp[i][j] : s[0,i]与t[0,j]匹配所需的最少操作步骤
     */
    int minDistance(string s, string t) {
        int n = s.size(), m = t.size();
        s = " " + s, t = " " + t;
        vector<vector<int>> dp(n + 1, vector(m + 1, 1000));
        for(int i = 0; i <= n; i++) // 初始状态 t为空时，匹配所需步骤就是全删
            dp[i][0] = i;
        for(int i = 0; i <= m; i++) // 初始状态 s为空时，匹配所需步骤就是全增
            dp[0][i] = i;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                // 当前字母相同
                if(s[i] == t[j]) dp[i][j] = dp[i - 1][j - 1];
                // 不同，进行修改。但需要前置区间可以匹配成功，然后操作次数+1
                // 增加，相当于s[0,i]与t[0, j - 1]匹配
                // 删除当前字母能匹配，相当于s[0, i - 1]与t[j]匹配
                dp[i][j] = min(dp[i][j], min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1);
            }
        }
        return dp[n][m];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}