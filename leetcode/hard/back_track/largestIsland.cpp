/**
 * @Time : 2022/4/24-12:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    int largestIsland(vector<vector<int>> &grid) {
        n = grid.size();
        marked = vector(n, vector(n, false));
        ids = vector(n, vector(n, 0));
        vector<int> posX, posY;
        int id = 1;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != 1) continue;
                backTrack(grid, posX, posY, i, j);
                int size = posX.size();
                for (int k = 0; k < size; k++) {
                    int x = posX[k], y = posY[k];
                    grid[x][y] = size;
                    ids[x][y] = id;
                }
                posX.clear();
                posY.clear();
                id++;
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0)
                    res = max(res, areaAfterModify(grid, i, j));
            }
        }
        return res == 0 ? n * n : res;
    }

private:
    int n;
    vector<vector<int>> dires = {{0,  1},
                                 {1,  0},
                                 {0,  -1},
                                 {-1, 0}};
    vector<vector<int>> ids;
    vector<vector<bool>> marked;

    void backTrack(vector<vector<int>> &grid, vector<int> &posX, vector<int> &posY, int x, int y) {
        marked[x][y] = true;
        posX.push_back(x);
        posY.push_back(y);
        for (vector<int> &dire: dires) {
            int newX = x + dire[0], newY = y + dire[1];
            if (newX < 0 || newY < 0 || newX >= n || newY >= n
                || marked[newX][newY] || grid[newX][newY] == 0)
                continue;
            backTrack(grid, posX, posY, newX, newY);
        }
    }

    int areaAfterModify(vector<vector<int>> &grid, int x, int y) {
        int area = 1;
        unordered_set<int> set;
        for (vector<int> &dire: dires) {
            int newX = x + dire[0], newY = y + dire[1];
            if (newX < 0 || newY < 0 || newX >= n || newY >= n
                || set.find(ids[newX][newY]) == set.end())
                continue;
            set.insert(ids[newX][newY]);
            area += grid[newX][newY];
        }
        return area;
    }

};

int main() {

}