/**
 * @Time : 2023/10/12-2:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int N = strs.size();
        vector<vector<int>> dp(vector(m + 1, vector(n + 1, 0)));
        for(int i = 0; i < N; i++) {
            int zero = 0, one = 0;
            for(char c : strs[i]){
                if(c == '1') one++;
                else zero++;
            }
            for(int j = m; j >= 0; j--) {
                for(int k = n; k >= 0; k--) {
                    if(j - zero >= 0 && k - one >= 0)
                        dp[j][k] = max(dp[j][k], dp[j - zero][k - one] + 1);
                }
            }
        }
        return dp[m][n];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}