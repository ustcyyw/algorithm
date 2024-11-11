/**
 * @Time : 2023/8/21-2:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumOperations(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> sum(4, vector(n + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j < 4; j++)
                sum[j][i] = sum[j][i - 1];
            sum[nums[i - 1]][i]++;
        }
        int res = INT_MAX;
        for(int i = -1; i < n; i++) {
            for(int j = i; j < n; j++) {
                int t = sum[1][i + 1] + (sum[2][j + 1] - sum[2][i + 1])
                        +  (sum[3][n] - sum[3][j + 1]);
                res = min(res, n - t);
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}