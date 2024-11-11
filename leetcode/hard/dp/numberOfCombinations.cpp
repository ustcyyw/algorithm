/**
 * @Time : 2022/8/26-2:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 你写下了若干 正整数 ，并将它们连接成了一个字符串 num 。但是你忘记给这些数字之间加逗号了。你只记得这一列数字是 非递减 的且 没有 任何数字有前导 0 。

请你返回有多少种可能的 正整数数组 可以得到字符串 num 。由于答案可能很大，将结果对 109 + 7 取余 后返回。

 

示例 1：

输入：num = "327"
输出：2
解释：以下为可能的方案：
3, 27
327
示例 2：

输入：num = "094"
输出：0
解释：不能有数字有前导 0 ，且所有数字均为正数。
示例 3：

输入：num = "0"
输出：0
解释：不能有数字有前导 0 ，且所有数字均为正数。
示例 4：

输入：num = "9999999999999"
输出：101
 

提示：

1 <= num.length <= 3500
num 只含有数字 '0' 到 '9' 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-ways-to-separate-numbers
 */
class Solution {
public:
    /**
     * 定义dp[i][j]: 以s[i,j]为s[0,j]上最后一个数字的数组总数
     * 如果s[i] = 0, dp[i][j] = 0
     * 否则就需要求出 sum(dp[k][i-1], dp[k+1][i-1],...,dp[i-1][i-1])
     * 上述求和表达式就是固定i-1之后的后缀和，那么对每一个j求出来所有i的状态之后
     * 可以计算出sum[k][j]表示 sum(dp[k][j], dp[k+1][j],...,dp[i-1][j]), 用于之后的计算
     * 其中 j - i = i - 1 - k, 并且s[k,i-1]这个数 <= s[i,j]这个数
     * k = 2 * i - 1 - j, 随着i的减小，k也在减小
     */
    int numberOfCombinations(string s) {
        if(s[0] == '0') return 0;
        int n = s.size(), mod = 1e9 + 7;
        vector<vector<long>> dp = vector(n, vector(n, 0l)), sum = vector(n, vector(n, 0l));
        vector<vector<int>> lcp = get_lcp(s);
        dp[0].assign(n, 1), sum[0][0] = 1;
        for(int j = 1; j < n; j++){
            for(int i = j; i > 0; i--){
                if(s[i] == '0') {
                    dp[i][j] = 0;
                    continue;
                }
                int k = max(0, 2 * i - 1 - j);
                if(k == 2 * i - 1 - j){ // 两个数字长度一致，需要比较具体大小
                    int len = lcp[k][i]; // 最长公共前缀，要决定两个数的大小，就看字符串的下一位
                    // 如果k + len > i - 1表示s[k, i-1] == s[i, j]
                    // 如果s[k, i-1] > s[i - 1, j]，那么k这个位置就不能取，前缀和就只能取sum[k + 1][j]，所以k++
                    if(k + len <= i - 1 && s[k + len] > s[i + len])
                        k++;
                }
                dp[i][j] = sum[k][i - 1];
            }
            sum[j][j] = dp[j][j];
            for(int i = j - 1; i >= 0; i--)
                sum[i][j] = (sum[i + 1][j] + dp[i][j]) % mod;
        }
        return (int)sum[0][n - 1];
    }

    vector<vector<int>> get_lcp(string& s){
        int n = s.size();
        vector<vector<int>> lcp = vector(n, vector(n, 0));
        for(int j = n - 1; j >= 0; j--){
            for(int i = n - 1; i >= 0; i--){
                if(s[i] != s[j]) continue;
                if(i != n - 1 && j != n - 1)
                    lcp[i][j] = 1 + lcp[i + 1][j + 1];
                else lcp[i][j] = 1;
            }
        }
        return lcp;
    }
};

int main(){
    Solution s;
    s.numberOfCombinations("1107");
    cout << 0 << endl;
}