/**
 * @Time : 2022/7/27-5:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        if(grid[0][0] == ')') return false;
        int m = grid.size(), n = grid[0].size();
        vector<vector<unordered_set<int>>> dp;
        dp.assign(m, {});
        for(int i = 0; i < m; i++)
            dp[i].assign(n, {});
        dp[0][0].insert(1);
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                unordered_set<int>& cur = dp[i][j];
                int added = grid[i][j] == '(' ? 1 : -1;
                if(i > 0)
                    renew_bracket(cur, dp[i - 1][j], added);
                if(j > 0)
                    renew_bracket(cur, dp[i][j - 1], added);
                if(cur.empty()) cur.insert(-1);
            }
        }
        return dp[m - 1][n - 1].count(0);
    }

    void renew_bracket(unordered_set<int>& cur, unordered_set<int>& pre, int added){
        if(pre.count(-1)) return; // 含-1说明走到上一个位置，只存在右括号更多的情况，已经不可能通过这个方向得到合法字符
        for(int num : pre){
            int temp = num + added;
            if(temp >= 0)
                cur.insert(num + added);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}