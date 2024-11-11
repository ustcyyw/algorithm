/**
 * @Time : 2023/12/17-2:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛376 t2 模拟
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for(int i = 0; i < nums.size(); i += 3) {
            if(nums[i + 2] - nums[i] > k)
                return {};
            res.push_back({nums[i], nums[i + 1], nums[i + 2]});
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}