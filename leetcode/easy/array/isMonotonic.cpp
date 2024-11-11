/**
 * @Time : 2022/5/12-12:01 AM
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
     * 执行用时：108 ms, 在所有 C++ 提交中击败了98.36%的用户
     * 内存消耗：94 MB, 在所有 C++ 提交中击败了89.60%的用户
     *
     * # 896
     */
    bool isMonotonic(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return true;
        int flag = nums[0] < nums[n - 1] ? 1 : -1;
        for(int i = 0; i < n - 1; i++){
            if(nums[i] * flag > nums[i + 1] * flag)
                return false;
        }
        return true;
    }
};

int main(){

}