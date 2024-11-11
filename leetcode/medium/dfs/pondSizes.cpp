/**
 * @Time : 2022/6/21-4:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int dx[8] = {0,0,1,-1,1,1,-1,-1};
    int dy[8] = {1,-1,0,0,1,-1,1,-1};
    int n, m;
    vector<int> pondSizes(vector<vector<int>>& land) {
        vector<int> res;
        n = land.size(), m = land[0].size();
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                if(land[i][j] == 0) res.push_back(dfs(land,i, j));
        }
        sort(res.begin(), res.end());
        return res;
    }

    int dfs(vector<vector<int>>& land, int x, int y){
        land[x][y] = 1;
        int count = 1;
        for(int i = 0; i < 8; i++){
            int nx = x + dx[i], ny = y + dy[i];
            if(nx < 0 || ny < 0 || nx >= n || ny >= m || land[nx][ny] != 0) continue;
            count += dfs(land, nx, ny);
        }
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}