/**
 * @Time : 2023/4/28-12:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector<vector<int>> grid(n, vector(n, 1));
        for(auto& mine : mines)
            grid[mine[0]][mine[1]] = 0;
        vector<vector<int>> left(n, vector(n, 0)), right(n, vector(n, 0));
        vector<vector<int>> up(n, vector(n, 0)), down(n, vector(n, 0));
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(!grid[i][j]) continue;
                left[i][j] = (j - 1 >= 0 ? left[i][j - 1] : 0) + 1;
                up[i][j] = (i - 1 >= 0 ? up[i - 1][j] : 0) + 1;
            }
        }
        for(int i = n - 1; i >= 0; i--) {
            for(int j = n - 1; j >= 0; j--) {
                if(!grid[i][j]) continue;
                right[i][j] = (j + 1 < n ? right[i][j + 1] : 0) + 1;
                down[i][j] = (i + 1 < n ? down[i + 1][j] : 0) + 1;
            }
        }
        int res = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                res = max(res, min({up[i][j], down[i][j], left[i][j], right[i][j]}));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}