/**
 * @Time : 2024/3/3-12:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 确定哪些格子属于y 枚举y格子和其它格子的值 找最小改动即可
 */
class Solution {
public:
    int minimumOperationsToWriteY(vector<vector<int>>& grid) {
        int val[3] = {0, 1, 2}, n = grid.size(), mid = n / 2;
        // 找到y的格子
        unordered_set<int> set;
        for(int i = 0, j = n - 1; i <= mid; i++, j--)
            set.insert(i * 1000 + i), set.insert(i * 1000 + j);
        for(int i = mid + 1, j = mid; i < n; i++)
            set.insert(i * 1000 + j);
        function<int(int, int)> fill = [&](int yv, int ov) -> int {
            int cnt = 0;
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    int key = i * 1000 + j;
                    if(set.count(key)) cnt += grid[i][j] != yv;
                    else cnt += grid[i][j] != ov;
                }
            }
            return cnt;
        };
        int res = INT_MAX;
        for(int yv : val) {
            for(int ov : val) {
                if(yv != ov) res = min(res, fill(yv, ov));
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}