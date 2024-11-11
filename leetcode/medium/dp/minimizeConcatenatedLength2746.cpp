/**
 * @Time : 2023/7/21-10:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        int n = words.size();
        vector<vector<vector<int>>> dp(n, vector(26, vector(26, INT_MAX)));
        dp[0][words[0][0] - 'a'][words[0].back() - 'a'] = (int)words[0].size();
        for(int i = 1; i < n; i++) {
            string& word = words[i];
            int m = word.size(), c1 = word[0] - 'a', c2 = word[m - 1] - 'a';
            for(int j = 0; j < 26; j++) {
                for(int k = 0; k < 26; k++) {
                    if(dp[i - 1][j][k] == INT_MAX) continue;
                    int t1 = j == c2 ? m - 1 : m;
                    dp[i][c1][k] = min(dp[i][c1][k], dp[i - 1][j][k] + t1);
                    int t2 = k == c1 ? m - 1 : m;
                    dp[i][j][c2] = min(dp[i][j][c2], dp[i - 1][j][k] + t2);
                }
            }
        }
        int res = INT_MAX;
        for(int i = 0; i < 26; i++) {
            for(int j = 0; j < 26; j++)
                res = min(res, dp[n - 1][i][j]);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}