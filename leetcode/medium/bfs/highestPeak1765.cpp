/**
 * @Time : 2023/2/28-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int dx[4] = {0,0,-1,1}, dy[4] = {1,-1,0,0};
class Solution {
public:
    vector<vector<int>> highestPeak(vector<vector<int>>& isWater) {
        int n = isWater.size(), m = isWater[0].size(), height = 1;
        queue<vector<int>> queue;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(isWater[i][j]) queue.push({i, j});
                isWater[i][j] = isWater[i][j] ? 0 : -1;
            }
        }
        while (!queue.empty()){
            int sz = queue.size();
            for(int k = 0; k < sz; k++){
                vector<int> cur = queue.front();
                queue.pop();
                for(int i = 0; i < 4; i++){
                    int nx = cur[0] + dx[i], ny = cur[1] + dy[i];
                    if(nx < 0 || ny < 0 || nx >= n || ny >= m || isWater[nx][ny] != -1) continue;
                    isWater[nx][ny] = height;
                    queue.push({nx, ny});
                }
            }
            height++;
        }
        return isWater;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}