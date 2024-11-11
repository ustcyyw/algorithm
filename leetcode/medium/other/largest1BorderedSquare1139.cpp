/**
 * @Time : 2022/11/30-12:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m;
    int largest1BorderedSquare(vector<vector<int>>& grid) {
        n = grid.size(), m = grid[0].size();
        vector<vector<int>> rowLen = getRowLen(grid), colLen = getColLen(grid);
        for(int l = min(n, m); l >= 1; l--)
            if(check(rowLen, colLen, l)) return l * l;
        return 0;
    }

    bool check(vector<vector<int>>& rowLen, vector<vector<int>>& colLen, int l){
        for(int i = 0; i + l - 1 < n; i++){
            for(int j = 0; j + l - 1 < m; j++)
                if(rowLen[i][j] >= l && colLen[j][i] >= l
                   && rowLen[i + l - 1][j] >= l && colLen[j + l - 1][i] >= l)
                    return true;
        }
        return false;
    }

    vector<vector<int>> getRowLen(vector<vector<int>>& grid){
        vector<vector<int>> res(n, vector(m, 0));
        for(int i = 0; i < n; i++){
            for(int j = m - 1, len = 0; j >= 0; j--){
                if(grid[i][j]) len++;
                else len = 0;
                res[i][j] = len;
            }
        }
        return res;
    }

    vector<vector<int>> getColLen(vector<vector<int>>& grid){
        vector<vector<int>> res(m, vector(n, 0));
        for(int i = 0; i < m; i++){
            for(int j = n - 1, len = 0; j >= 0; j--){
                if(grid[j][i]) len++;
                else len = 0;
                res[i][j] = len;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}