/**
 * @Time : 2022/10/10-8:23 PM
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
     * heights[i] : 一维数组，元素是每一列中以i开头的，向下的连续的1的长度
     */
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int n = matrix.size(), m = matrix[0].size();
        vector<vector<int>> heights(n, vector(0, 0));
        for(int j = 0; j < m; j++){
            for(int i = n - 1, len = 0; i >= 0; i--){
                len = matrix[i][j] ? len + 1 : 0;
                heights[i].push_back(len);
            }
        }
        for(auto& height : heights)
            sort(height.begin(), height.end());
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int j = m - 1; j >= 0 && heights[i][j] > 0; j--)
                res = max(res, (m - j) * heights[i][j]);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}