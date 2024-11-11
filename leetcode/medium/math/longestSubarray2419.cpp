/**
 * @Time : 2022/11/23-5:27 PM
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
     * 与操作只会让数不变或者变小
     */
    int longestSubarray(vector<int>& nums) {
        int max_val = 0, res = 0, n = nums.size();
        for(int num : nums)
            max_val = max(max_val, num);
        for(int i = 0; i < n; i++){
            if(nums[i] == max_val){
                int j = i + 1;
                while (j < n && nums[j] == max_val) j++;
                res = max(res, j - i);
                i = j;
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}