/**
 * @Time : 2022/9/3-8:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：56 ms, 在所有 C++ 提交中击败了75.84%的用户
     * 内存消耗：9 MB, 在所有 C++ 提交中击败了85.46%的用户
     *
     * dp[i][j]表示p[0,i-1]与s[0,j-1]是否匹配
     * 如果p[i]是普通字母 dp[i][j] = dp[i - 1][j - 1] && p[i - 1] == s[j - 1]
     * 如果p[i]是'?',它必须匹配一个字母dp[i][j] = dp[i - 1][j - 1]
     * 如果p[i]是'*',它可以匹配任意多个字符
     *     考虑dp[i-1][k]是否有匹配成功，如果有，就让p[0,i-1]去匹配s[0,k],p[i]去匹配s[k+1,j]
     *     这里只要求k是小于j的，因此可以先找到dp[i-1][k]中为true的最小k，然后看这个k是否小于j
     *     特殊地，如果k等于j，取*号匹配空串也能让dp[i][j]匹配成功
     *     所以可以在遍历i的过程中记录每一层遍历中匹配的第一个j，在下一层这个值就是上述的k
     */
    bool isMatch(string s, string p) {
        if(!p.empty()) p = format_p(p);
        int n = s.size(), m = p.size();
        vector<vector<bool>> dp(m + 1, vector(n + 1, false));
        dp[0][0] = true;
        if(p[0] == '*') // 如果p以*开头，那其第一个字符就可以匹配s的空串，因为后续j都是从1开始计算，所以这里要补充
            dp[1][0] = true;
        int min_k = 0;
        for(int i = 1; i <= m; i++){
            int temp_k = dp[i][0] ? 0 : -1;
            for(int j = 1; j <= n; j++){
                if(p[i - 1] == '?') dp[i][j] = dp[i - 1][j - 1];
                else if(p[i - 1] == '*') dp[i][j] = min_k <= j;
                else dp[i][j] = dp[i - 1][j - 1] && (p[i - 1] == s[j - 1]);
                if(dp[i][j] && temp_k == -1)
                    temp_k = j;
            }
            // 如果temp_k == -1，就意味着当前轮次没有dp[i][j]匹配成功，那么下一轮次的k就应该是无穷大，取n + 10即可
            min_k = temp_k == -1 ? n + 10 : temp_k;
        }
        return dp[m][n];
    }
    // 多个*连在一起 其实等价于1个*
    string format_p(string& p){
        string res;
        res.push_back(p[0]);
        for(int i = 1; i < p.size(); i++){
            if(p[i] == '*' && res.back() == '*') continue;
            res.push_back(p[i]);
        }
        return res;
    }
};

int main(){
    Solution s;
    s.isMatch("abceb","*a*b");
    cout << 0 << endl;
}