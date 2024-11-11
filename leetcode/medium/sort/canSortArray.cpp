/**
 * @Time : 2024/1/21-4:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛122 t2
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 根据条件划分组别 然后分组排序 看当前组的最小值是否 >= 前一个组的最大值即可
     */
    bool canSortArray(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0, last = -1; i < n; ) {
            int j = i + 1;
            while(j < n && __builtin_popcount(nums[j]) == __builtin_popcount(nums[j - 1]))
                j++;
            int t1 = nums[i], t2 = nums[i];
            for(int k = i + 1; k < j; k++)
                t1 = min(t1, nums[k]), t2 = max(t2, nums[k]);
            if(t1 < last) return false;
            i = j, last = t2;
        }
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}