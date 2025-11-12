/**
 * @Time : 2025/1/8-11:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3276 动态规划 状态压缩 刷表法
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        vector<vector<int>> arr = init(grid);
        int n = grid.size(), m = arr.size(), full = (1 << n) - 1;
        vector<vector<int>> dp(m + 1, vector(full + 1, -1));
        dp[0][0] = 0;
        for(int i = 0; i < m - 1; i++) {
            int num = arr[i + 1][0], sz = arr[i + 1].size();
            for(int s = 0; s <= full; s++) {
                if(dp[i][s] == -1) continue;
                dp[i + 1][s] = max(dp[i + 1][s], dp[i][s]);
                for(int j = 1; j < sz; j++) {
                    int idx = arr[i + 1][j], t = 1 << idx;
                    if(t & s) continue;
                    int ns = t | s;
                    dp[i + 1][ns] = max(dp[i + 1][ns], dp[i][s] + num);
                }
            }
        }
        int ans = 0;
        for(int s = 0; s <= full; s++)
            ans = max(ans, dp[m - 1][s]);
        return ans;
    }

    vector<vector<int>> init(vector<vector<int>>& grid) {
        unordered_map<int, set<int>> map;
        for(int i = 0; i < grid.size(); i++) {
            for(int num : grid[i])
                map[num].insert(i);
        }
        vector<vector<int>> ans;
        ans.push_back({});
        for(auto& [num, idx] : map) {
            vector<int> temp(1, num);
            for(int i : idx)
                temp.push_back(i);
            ans.push_back(temp);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}