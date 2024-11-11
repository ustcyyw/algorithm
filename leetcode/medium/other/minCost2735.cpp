/**
 * @Time : 2023/7/24-10:59 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minCost(vector<int>& nums, int x) {
        int n = nums.size();
        vector<vector<int>> cost = vector(n, vector(n, 0));
        for(int i = 0; i < n; i++) {
            cost[i][0] = nums[i];
            for(int j = 1; j < n; j++)
                cost[i][j] = min(cost[i][j - 1], nums[(i + j) % n]);
        }
        long long res = LONG_LONG_MAX;
        for(int j = 0; j < n; j++) {
            long long t = (long long)x * j;
            for(int i = 0; i < n; i++)
                t += cost[i][j];
            res = min(res, t);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}