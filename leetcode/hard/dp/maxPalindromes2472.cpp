/**
 * @Time : 2022/11/16-10:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    int maxPalindromes(string s, int k) {
        n = s.size();
        vector<vector<bool>> valid(n, vector(n, false));
        for(int i = 0; i < n; i++){
            check(s, valid, i, i);
            check(s, valid, i, i + 1);
        }
        vector<int> dp(n + 1, 0); // 截止s[0, i - 1]的子字符串的最大数目
        for(int i = 1; i <= n; i++){
            dp[i] = dp[i - 1];
            for(int j = i - k + 1; j >= 1; j--){
                if(valid[j - 1][i - 1]) {
                    dp[i] = max(dp[i], dp[j - 1] + 1);
                    break;
                }
            }
        }
        return dp[n];
    }

    void check(string& s, vector<vector<bool>>& valid, int lo, int hi){
        while (lo >= 0 && hi < n && s[lo] == s[hi]){
            valid[lo][hi] = true;
            lo--; hi++;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}