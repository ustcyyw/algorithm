/**
 * @Time : 2022/12/8-9:34 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> maxScoreIndices(vector<int>& nums) {
        int n = nums.size();
        vector<int> preSum(n + 1, 0), res;
        for(int i = 1; i <= n; i++)
            preSum[i] = preSum[i - 1] + nums[i - 1];
        for(int i = 0, point = -1; i < n; i++){
            int cur = i - preSum[i] + preSum[n] - preSum[i];
            if(cur == point) res.push_back(i);
            else if(cur > point){
                res.resize(0);
                res.push_back(i);
                point = cur;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}