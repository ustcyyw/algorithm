/**
 * @Time : 2022/6/14-5:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.size() == 0 || matrix[0].size() == 0)
            return false;
        int x = matrix.size() - 1, y = 0, n = matrix[0].size();
        while (x <= 0 && y < n){
            if(matrix[x][y] == target) return true;
            else if(matrix[x][y] < target) y++;
            else x--;
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}