/**
 * @Time : 2022/11/1-8:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n, vector(5, 0));
        dp[0].assign(5, 1);
        for(int i = 1; i < n; i++){
            for(int j = 0; j < 5; j++){
                for(int k = 0; k <= j; k++)
                    dp[i][j] += dp[i - 1][k];
            }
        }
        return accumulate(dp[n - 1].begin(), dp[n - 1].end(), 0);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}