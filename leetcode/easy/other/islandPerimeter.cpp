/**
 * @Time : 2022/5/23-10:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> dx = {0, 0, 1, -1}, dy = {1, -1, 0, 0};
    int islandPerimeter(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), p = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++)
                if(grid[i][j] == 1) p += countOne(grid,i, j, n, m);
        }
        return p;
    }

    int countOne(vector<vector<int>>& grid, int x, int y, int n, int m){
        int count = 0;
        for(int i = 0; i < 4; i++){
            int newX = x + dx[i], newY = y + dy[i];
            if(newX < 0 || newY < 0 || newX >= n || newY >= m || grid[newX][newY] == 0)
                count++;
        }
        return count;
    }
};

int main(){

}