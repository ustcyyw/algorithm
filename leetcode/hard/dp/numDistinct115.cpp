/**
 * @Time : 2022/10/19-1:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个字符串 s 和一个字符串 t ，计算在 s 的子序列中 t 出现的个数。

字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）

题目数据保证答案符合 32 位带符号整数范围。

 

示例 1：

输入：s = "rabbbit", t = "rabbit"
输出：3
解释：
如下图所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
rabbbit
rabbbit
rabbbit
示例 2：

输入：s = "babgbag", t = "bag"
输出：5
解释：
如下图所示, 有 5 种可以从 s 中得到 "bag" 的方案。
babgbag
babgbag
babgbag
babgbag
babgbag
 

提示：

0 <= s.length, t.length <= 1000
s 和 t 由英文字母组成


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/21dk04
 */
class Solution {
public:
    /**
     * dp[i][j]: 截止字符串s的i位置，匹配了t[0,j]的数量
     *
     * 转移方程 dp[i][j] = dp[i - 1][j]，s的前置位完成匹配的，到i这个位置依然能够完成匹配
     * 另外在满足s[i] == t[j]时，让这两个字母匹配，那么dp[i][j]还应该加上dp[i - 1][j - 1]
     *
     * 在固定了i，枚举j时
     * j的下限：s到i这个位置，还剩余的字母有n-1-i+1=n-i个;t到j这个位置，还要匹配的字母有m-j个
     * 要保证 m - j <= n - i, j >= m - n + i。
     * 并且j=0这个边界单独计算了，因此从 j = max(1, m - n + i)开始枚举
     *
     * j的上限：s到i这个位置，最多能匹配i+1个字母；t到j这个位置已经匹配的字母有j+1个
     * i + 1 >= j + 1, j <= i。因此 j < min(m, i + 1)
     */
    int numDistinct(string s, string t) {
        int n = s.size(), m = t.size();
        vector<vector<long long>> dp(n, vector(m, 0ll));
        dp[0][0] = s[0] == t[0];
        for(int i = 1; i < n; i++){
            dp[i][0] = dp[i - 1][0] + (s[i] == t[0]);
            for(int j = max(1, m - n + i); j < min(m, i + 1); j++){
                dp[i][j] = dp[i - 1][j];
                if(s[i] == t[j]) dp[i][j] += dp[i - 1][j - 1];
            }
        }
        return dp[n - 1][m - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}