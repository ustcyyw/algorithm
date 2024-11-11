/**
 * @Time : 2022/11/24-9:20 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> goodIndices(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> left(n, 1), right(n, 1), res;
        for(int i = 1, len = 1; i < n; i++){
            if(nums[i] <= nums[i - 1]) len++;
            else len = 1;
            left[i] = len;
        }
        for(int i = n - 2, len = 1; i >= 0; i--){
            if(nums[i] >= nums[i + 1]) len++;
            else len = 1;
            left[i] = len;
        }
        for(int i = k; i < n - k; i++)
            if(left[i - 1] >= k && right[i + 1] >= k)
                res.push_back(i);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}