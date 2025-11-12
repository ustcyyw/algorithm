/**
 * @Time : 2025/1/16-5:19 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3240 贪心
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minFlips(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), ans = 0;
        int c1 = 0, c2 = 0;
        for(int u = 0, d = n - 1; u <= d; u++, d--) {
            for(int l = 0, r = m - 1; l <= r; l++, r--)
                ans += cal(grid, u, d, l, r, c1, c2);
        }
        // 中间单独列或者中间单独行产生的1的对 如果有奇数对 并且没有0-1对存在
        // 那么就只能将多的这1-1对全变为0
        if(c2 % 2 == 1 && c1 == 0) ans += 2;
        ans += c1; // 其余情况下 只需要调整0-1对就能满足对称要求和1的数量要求
        return ans;
    }

    int cal(vector<vector<int>>& grid, int u, int d, int l, int r, int& c1, int& c2) {
        if(u == d && l == r)
            return grid[u][l];
        int cnt = grid[u][l] + grid[d][l] + grid[u][r] + grid[d][r];
        if(u != d && l != r) {
            if(cnt == 2 || cnt == 0) return cnt;
            return cnt == 4 ? 0 : 1;
        }
        if(cnt == 2) c1++;
        if(cnt == 4) c2++;
        return 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}