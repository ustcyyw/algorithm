/**
 * @Time : 2023/1/3-2:18 PM
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
     * dp[i][j] 截止word1[0, i]与word2[j, m - 1]的最长偶数长度的回文子串
     * 这部分长度只是word1的左部分与word2的右部分够成的回文子串
     * 但是如 word1 = baaa 和 word2 = a这样的两个字符串，还需要加上 word1中间的部分"aaa"
     * 当然word2也可能贡献出中间的部分
     * 因此还需要知道infos[lo][hi]表示word[lo, hi]上的最长回文子序列
     * 在枚举(i,j)的时候，回文串还要加上word1或者word2中间部分贡献的max(infos1[i + 1][n - 1], infos2[0][j - 1])
     * 求max(infos1[i + 1][n - 1], infos2[0][j - 1])时，注意数组越界问题
     *
     * 另外，题目要求word1和word2都要贡献非空的子序列
     * 所以在dp[i][j] = 0的时候，二者都时空子序列，此时不记答案
     */
    int longestPalindrome(string word1, string word2) {
        int n = word1.size(), m = word2.size(), res = 0;
        vector<vector<int>> dp(n, vector(m, 0));
        if(word1[0] == word2[m - 1]) dp[0][m - 1] = 2;
        for(int i = 1; i < n; i++){
            if(word1[i] == word2[m - 1]) dp[i][m - 1] = 2;
            else dp[i][m - 1] = dp[i - 1][m - 1];
        }
        for(int i = m - 2; i >= 0; i--){
            if(word1[0] == word2[i]) dp[0][i] = 2;
            else dp[0][i] = dp[0][i + 1];
        }
        for(int i = 1; i < n; i++){
            for(int j = m - 2; j >= 0; j--){
                if(word1[i] == word2[j]) dp[i][j] = 2 + dp[i - 1][j + 1];
                else dp[i][j] = max(dp[i - 1][j], dp[i][j + 1]);
            }
        }
        vector<vector<int>> infos1 = selfPalindrome(word1), infos2 = selfPalindrome(word2);
        for(int i = 0; i < n; i++) {
            for (int j = m - 1; j >= 0; j--){
                int t1 = i + 1 < n ? infos1[i + 1][n - 1] : 0, t2 = j > 0 ? infos2[0][j - 1] : 0;
                if(dp[i][j] != 0)
                    res = max(res, max(t1, t2) + dp[i][j]);
            }
        }
        return res;
    }

    // infos[lo][hi] s[lo, hi]上的最长回文子序列 类似于区间dp，只是不用枚举分割点
    vector<vector<int>> selfPalindrome(string& s){
        int n = s.size();
        vector<vector<int>> infos(n, vector(n, 0));
        for(int i = 0; i < n; i++)
            infos[i][i] = 1;
        for(int l = 2; l <= n; l++){
            for(int lo = 0; lo + l - 1 < n; lo++){
                int hi = lo + l - 1;
                if(s[lo] == s[hi]) infos[lo][hi] = infos[lo + 1][hi - 1] + 2;
                else infos[lo][hi] = max(infos[lo + 1][hi], infos[lo][hi - 1]);
            }
        }
        return infos;
    }

    /**
     * 方法2 转换思路
     * 求的是 subsequence1 + subsequence2 的最长回文
     * 那么可以将word1和word2拼接起来，求整体的最长回文
     * 求word[lo][hi]上的最长回文，参考方法1中的selfPalindrome方法
     * 只有在s[lo] == s[hi]时，才可能贡献更长的长度（更新答案）
     * 但是题目要求word1和word2都要贡献非空的子序列
     * 因此不是所有的s[lo] == s[hi]时，都进行答案更新
     * 得保证i在word1的范围，j在word2的范围，这样才保证了word1和word2都贡献了非空的子序列
     */
    int longestPalindrome2(string word1, string word2){
        string s = word1 + word2;
        int n1 = word1.size(), n = s.size(), res = 0;
        vector<vector<int>> dp(n, vector(n, 0));
        for(int i = 0; i < n; i++)
            dp[i][i] = 1;
        for(int l = 2; l <= n; l++){
            for(int lo = 0; lo + l - 1 < n; lo++){
                int hi = lo + l - 1;
                if(s[lo] == s[hi]) {
                    dp[lo][hi] = dp[lo + 1][hi - 1] + 2;
                    if(lo < n1 && hi >= n1) res = max(res, dp[lo][hi]);
                }
                else dp[lo][hi] = max(dp[lo + 1][hi], dp[lo][hi - 1]);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    s.longestPalindrome("cacb", "cbba");
    cout << 0 << endl;
}