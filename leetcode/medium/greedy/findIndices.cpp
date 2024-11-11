/**
 * @Time : 2023/10/15-12:21 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛367 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findIndices(vector<int>& nums, int id, int vd) {
        int n = nums.size();
        if(id >= n) return {-1, -1};
        vector<int> max_val(n, -1), min_val(n, -1);
        max_val[n - 1] = min_val[n - 1] = n - 1;
        for(int i = n - 2; i >= 0; i--) {
            int num = nums[i];
            max_val[i] = num >= nums[max_val[i + 1]] ? i : max_val[i + 1];
            min_val[i] = num <= nums[min_val[i + 1]] ? i : min_val[i + 1];
        }
        for(int i = 0, j = i + id; j < n; i++, j++) {
            int num = nums[i];
            if(num - nums[min_val[j]] >= vd)
                return {i, min_val[j]};
            if(nums[max_val[j]] - num >= vd)
                return {i, max_val[j]};
        }
        return {-1, -1};
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}