/**
 * @Time : 2022/6/11-2:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 给定一个字符串 s，计算 s 的 不同非空子序列 的个数。因为结果可能很大，所以返回答案需要对 10^9 + 7 取余 。

字符串的 子序列 是经由原字符串删除一些（也可能不删除）字符但不改变剩余字符相对位置的一个新字符串。

例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是。

示例 1：

输入：s = "abc"
输出：7
解释：7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc"。
示例 2：

输入：s = "aba"
输出：6
解释：6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba"。
示例 3：

输入：s = "aaa"
输出：3
解释：3 个不同的子序列分别是 "a", "aa" 以及 "aaa"。
 

提示：

1 <= s.length <= 2000
s 仅由小写英文字母组成

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/distinct-subsequences-ii
 */
class Solution {
public:
    /**
     * 执行用时：16 ms, 在所有 C++ 提交中击败了8.87%的用户
     * 内存消耗：6.8 MB, 在所有 C++ 提交中击败了22.70%的用户
     * dp[i]表示以字母s[i]结尾的子串一共有多少个
     * 显然可以从[0, i - 1]上去拼接
     * 但是这里存在重复的问题，比如 cbaa
     * 第一个a可以和前面拼接出 a ca ba cba
     * 如果第二个a也从位置0开始拼接就会出现 a, ca, ba, cba, 这些重复
     * 所以它只应该从其前面最近一个相同字母那里开始拼接。
     *
     */
    int mod = 1000000007;
    int distinctSubseqII(string s) {
        vector<int> index = vector(26, -1);
        int n = s.size();
        vector<long> dp = vector(n, 0l);
        long res = 0;
        for(int i = 0; i < n; i++){
            int pre = index[s[i] - 'a'];
            if(pre == -1){
                dp[i]++;
                pre = 0;
            }
            for(int j = pre; j < i; j++)
                dp[i] = (dp[i] + dp[j]) % mod;
            index[s[i] - 'a'] = i;
            res = (res + dp[i]) % mod;
        }
        return (int)res;
    }
    /**
     * 前缀和优化
     * 执行用时：4 ms, 在所有 C++ 提交中击败了78.72%的用户
     * 内存消耗：7.6 MB, 在所有 C++ 提交中击败了5.32%的用户
     */
    int distinctSubseqII2(string s) {
        vector<int> index = vector(26, -1);
        int n = s.size();
        vector<long> dp = vector(n, 0l), sum = vector(n + 1, 0l);
        long res = 0;
        for(int i = 0; i < n; i++){
            int pre = index[s[i] - 'a'];
            if(pre == -1){
                dp[i]++;
                pre = 0;
            }
            dp[i] = dp[i] + (sum[i] - sum[pre] + mod) % mod;
            index[s[i] - 'a'] = i;
            sum[i + 1] += sum[i] + dp[i];
            res = (res + dp[i]) % mod;
        }
        return (int)res;
    }
};

int main(){
    Solution s;
    cout << s.distinctSubseqII("aaa") << ends;
}