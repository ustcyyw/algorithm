/**
 * @Time : 2023/4/19-10:23 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m, res = INT_MAX;
    vector<vector<bool>> grid;
    int tilingRectangle(int n, int m) {
        if(m == n) return 1;
        this->n = n, this->m = m;
        grid = vector(n, vector(m, false));
        backTrack(0);
        return res;
    }

    void backTrack(int cnt){
        if(cnt >= res) return;
        vector<int> pos = first_pos();
        int x = pos[0], y = pos[1];
        if(x == -1) {
            res = cnt;
            return;
        }
        // 铺设的瓷砖大小逐渐+1，在循环 覆盖的面积每次只扩展最外一层。
        // 在循环结束后，需要恢复状态，将尝试覆盖的最大矩形区域恢复为未覆盖。
        int i = x;
        for(; i < n && y + i - x < m && !grid[i][y] && !grid[x][y + i - x]; i++) {
            for(int j = x; j <= i; j++) grid[j][y + i - x] = true;
            for(int j = y; j <= y + i - x - 1; j++) grid[i][j] = true;
            backTrack(cnt + 1);
        }
        fill(x, y, i - 1, y + i - 1 - x, false);
    }

    vector<int> first_pos(){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                if(!grid[i][j]) return {i, j};
        }
        return {-1, -1};
    }

    void fill(int x1, int y1, int x2, int y2, bool flag){
        for(int i = x1; i <= x2; i++){
            for(int j = y1; j <= y2; j++)
                grid[i][j] = flag;
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}