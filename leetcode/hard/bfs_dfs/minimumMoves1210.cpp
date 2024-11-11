/**
 * @Time : 2022/11/24-9:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 用一个三元组 pos={flag, x, y}, 标识位1表示水平，0表示竖直。x y 表示头坐标
     */
    int n, t = 1e5;

    int minimumMoves(vector<vector<int>>& grid) {
        n = grid.size();
        vector<int> start_pos = {1,0,1}, end_pos = {1, n - 1, n - 1};
        int start = get_key(start_pos), target = get_key(end_pos);
        unordered_set<int> marked;
        marked.insert(start);
        queue<vector<int>> queue;
        queue.push(start_pos);
        int step = 0;
        while (!queue.empty()){
            int size = queue.size();
            for(int i = 0; i < size; i++){
                vector<int>& cur_pos = queue.front();
                if(get_key(cur_pos) == target) return step;
                int flag = cur_pos[0], x = cur_pos[1], y = cur_pos[2];
                queue.pop();
                if(move_right(grid, flag, x, y)) add(queue, marked, {flag, x, y + 1});
                if(move_down(grid, flag, x, y)) add(queue, marked, {flag, x + 1, y});
                if(rotate(grid, flag, x, y)) add(queue, marked, {!flag, x + 1, y - 1});
                if(reverse_rotate(grid, flag, x, y)) add(queue, marked, {!flag, x - 1, y + 1});
            }
            step++;
        }
        return -1;
    }
    void add(queue<vector<int>>& queue, unordered_set<int>& marked, vector<int> pos){
        int key = get_key(pos);
        if(!marked.count(key)){
            marked.insert(key);
            queue.push(pos);
        }
    }
    int get_key(vector<int>& pos){
        return pos[0] * t + pos[1] * 100 + pos[2];
    }
    bool move_right(vector<vector<int>>& grid, int flag, int x, int y){
        if(y + 1 == n || grid[x][y + 1] == 1) return false;
        if(flag == 0 && grid[x - 1][y + 1] == 1) return false;
        return true;
    }
    bool move_down(vector<vector<int>>& grid, int flag, int x, int y){
        if(x + 1 == n || grid[x + 1][y] == 1) return false;
        if(flag == 1 && grid[x + 1][y - 1] == 1) return false;
        return true;
    }
    // 顺时针旋转
    bool rotate(vector<vector<int>>& grid, int flag, int x, int y){
        if(flag == 0 || x + 1 == n) return false;
        return grid[x + 1][y] == 0 && grid[x + 1][y - 1] == 0;
    }
    // 逆时针旋转
    bool reverse_rotate(vector<vector<int>>& grid, int flag, int x, int y){
        if(flag == 1 || y + 1 == n) return false;
        return grid[x][y + 1] == 0 && grid[x - 1][y + 1] == 0;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}