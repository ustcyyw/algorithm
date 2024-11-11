/**
 * @Time : 2023/12/7-12:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 注意横纵坐标是独立的 而且是地位一致的 分开计算
 */
#include<bits/stdc++.h>
using namespace std;

int n, m, num;
vector<vector<int>> grid1, grid2;

long long count(vector<vector<int>>& grid) {
    long long res = 0;
    int cn = grid.size(), cm = grid[0].size();
    unordered_map<int, vector<long long>> map;
    for(int i = 0; i < cn; i++) {
        for(int j = 0; j < cm; j++) {
            int num = grid[i][j];
            if(!map.count(num)) map[num] = {1, i};
            else {
                vector<long long>& info = map[num];
                res += info[0] * i - info[1];
                info[0]++, info[1] += i;
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    grid1.assign(n, vector(m, 0));
    grid2.assign(m, vector(n, 0));
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> num;
            grid1[i][j] = num;
            grid2[j][i] = num;
        }
    }
    cout << (count(grid1) + count(grid2)) << endl;
}