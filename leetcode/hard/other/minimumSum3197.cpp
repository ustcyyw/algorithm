/**
 * @Time : 2024/6/30-3:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : lc3197 周赛403 T4 分类讨论
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> grid;
    int area(int x1, int y1, int x2, int y2) {
        int l = INT_MAX, r = -1, u = INT_MAX, d = -1;
        for(int i = x1; i <= x2; i++) {
            for(int j = y1; j <= y2; j++) {
                if(grid[i][j] == 0) continue;
                l = min(l, j), r = max(r, j);
                u = min(u, i), d = max(d, i);
            }
        }
        if(l == INT_MAX) return 0;
        return (r - l + 1) * (d - u + 1);
    }

    int minimumSum(vector<vector<int>>& grid) {
        this->grid = grid;
        int n = grid.size(), m = grid[0].size(), ans = INT_MAX;
        // 枚举第一条竖直分界线(左)
        for(int i = 0; i < m; i++) {
            int s1 = area(0, 0, n - 1, i);
            if(s1 == 0) continue;
            // 枚举第二条竖直分界线
            for(int j = i + 1; j < m; j++) {
                int s2 = area(0, i + 1, n - 1, j);
                int s3 = area(0, j + 1, n - 1, m - 1);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
            // 枚举右侧水平分界线
            for(int j = 0; j < n; j++) {
                int s2 = area(0, i + 1, j, m - 1);
                int s3 = area(j + 1, i + 1, n - 1, m - 1);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
        }
        // 枚举第一条竖直分界线(右)
        for(int i = 0; i < m; i++) {
            int s1 = area(0, i + 1, n - 1, m - 1);
            if(s1 == 0) continue;
            // 枚举左侧水平分界线
            for(int j = 0; j < n; j++) {
                int s2 = area(0, 0, j, i);
                int s3 = area(j + 1, 0, n - 1, i);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
        }
        // 枚举第一条水平分界线(上)
        for(int i = 0; i < n; i++) {
            int s1 = area(0, 0, i, m - 1);
            if(s1 == 0) continue;
            // 枚举第二条水平分界线
            for(int j = i + 1; j < n; j++) {
                int s2 = area(i + 1, 0, j, m - 1);
                int s3 = area(j + 1, 0, n - 1, m - 1);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
            // 枚举下侧竖直分界线
            for(int j = 0; j < m; j++) {
                int s2 = area(i + 1, 0, n - 1, j);
                int s3 = area(i + 1, j + 1, n - 1, m - 1);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
        }
        // 枚举第一条水平分界线(下)
        for(int i = 0; i < m; i++) {
            int s1 = area(i + 1, 0, n - 1, m - 1);
            if(s1 == 0) continue;
            // 枚举上侧竖直分界线
            for(int j = 0; j < m; j++) {
                int s2 = area(0, 0, i, j);
                int s3 = area(0, j + 1, i, m - 1);
                if(s2 != 0 && s3 != 0) ans = min(ans, s1 + s2 + s3);
            }
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}