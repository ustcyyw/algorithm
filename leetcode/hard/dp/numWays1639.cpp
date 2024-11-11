/**
 * @Time : 2022/11/9-11:23 AM
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
     * dp[i][j]表示截止words中的第i个字母，能匹配到target[j]的方案数
     * 如果 i < j 必然是无法匹配的，因为前i个字母全用上，也没有j那么多。所以 j <= i
     * 匹配到第i个字母，word中还剩的字母个数为n-i
     * 此时匹配到target[j]，还需要匹配m-j个字母
     * 那么就要求 n - i >= m - j。 j >= m - n + i
     */
    int numWays(vector<string>& words, string target) {
        int n = words[0].size(), m = target.size(), mod = 1e9 + 7;
        if(m > n) return 0;
        vector<vector<int>> count(n, vector(26, 0));
        for(string& word : words){
            for(int i = 0; i < n; i++)
                count[i][word[i] - 'a']++;
        }
        vector<vector<long long>> dp(n, vector(m, 0ll));
        dp[0][0] = count[0][target[0] - 'a'];
        for(int i = 1; i < n; i++){
            dp[i][0] = dp[i - 1][0] + count[i][target[0] - 'a'];
            for(int j = max(1, m - n - i); j < min(m, i + 1); j++){
                int c = target[j] - 'a';
                dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * count[i][c]) % mod;
            }
        }
        return (int)dp[n - 1][m - 1];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}