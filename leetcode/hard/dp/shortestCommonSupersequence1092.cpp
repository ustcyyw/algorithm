/**
 * @Time : 2022/11/2-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给出两个字符串 str1 和 str2，返回同时以 str1 和 str2 作为子序列的最短字符串。如果答案不止一个，则可以返回满足条件的任意一个答案。

（如果从字符串 T 中删除一些字符（也可能不删除，并且选出的这些字符可以位于 T 中的 任意位置），可以得到字符串 S，那么 S 就是 T 的子序列）

 

示例：

输入：str1 = "abac", str2 = "cab"
输出："cabac"
解释：
str1 = "abac" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 的第一个 "c"得到 "abac"。
str2 = "cab" 是 "cabac" 的一个子串，因为我们可以删去 "cabac" 末尾的 "ac" 得到 "cab"。
最终我们给出的答案是满足上述属性的最短字符串。
 

提示：

1 <= str1.length, str2.length <= 1000
str1 和 str2 都由小写英文字母组成。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/shortest-common-supersequence
 */
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        vector<vector<int>> dp(n + 1, vector(m + 1, 0));
        vector<vector<vector<int>>> pos(n + 1, vector(m + 1, vector(2, -1)));
        // 求最长公共子序列，且标记转移的路线
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(dp[i - 1][j] > dp[i][j - 1])
                    pos[i][j][0] = i - 1, pos[i][j][1] = j;
                else
                    pos[i][j][0] = i, pos[i][j][1] = j - 1;
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                if(str1[i - 1] == str2[j - 1] && dp[i][j] < dp[i - 1][j - 1] + 1) {
                    pos[i][j][0] = i - 1, pos[i][j][1] = j - 1;
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
            }
        }
        // 标记出哪些字母是在最长公共子序列中的
        vector<bool> in1 = vector(n, false), in2 = vector(m, false);
        int i = n, j = m;
        while (i != 0 && j != 0){
            int t1 = pos[i][j][0], t2 = pos[i][j][1];
            // 注意第二个条件，要子序列长度+1时，才是一个公共子序列中的字母
            if(str1[i - 1] == str2[j - 1] && dp[i][j] > dp[t1][t2])
                in1[i - 1] = in2[j - 1] = true;
            i = t1, j = t2;
        }
        i = 0, j = 0;
        string res;
        while (i < n || j < m){
            while (i < n && !in1[i]) res.push_back(str1[i++]);
            while (j < m && !in2[j]) res.push_back(str2[j++]);
            if(i < n) res.push_back(str1[i]);
            i++, j++;
        }
        return res;
    }
};

int main(){
    Solution s;
    s.shortestCommonSupersequence("abcde", "ace");
    cout << 0 << endl;
}