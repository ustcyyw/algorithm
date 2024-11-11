/**
 * @Time : 2023/10/1-5:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 与运算 是个单调递减的过程 所以最小值一定是所有数字的与
     * 算出最小值min_val
     * 如果 min_val != 0，假设可以有分为两个或以上的子数组
     * 其中任何一个子数组的与 都 >= min_val
     * 假定第一个子数组的与值就是min_val，因为大于min_val的压根不能分割出来
     * 那么剩下的子数组的与值就必须是0，这样其和才不会超过min_val
     * 但是另外的子数组的与值是0，那么整体的与值min_val=0，矛盾
     * 因此在min_val != 0的时候，是不可以分成多个子数组的 直接返回0
     *
     * 当min_val = 0时，就看子数组的与值是0，并且其后续整体的与值是0就能切分
     */
    int maxSubarrays(vector<int>& nums) {
        int n = nums.size(), min_val = nums[0], res = 0;
        for(int num : nums) min_val &= num;
        if(min_val != 0) return 1;
        vector<int> aux(n, 0);
        aux[n - 1] = nums[n - 1];
        for(int i = n - 2; i >= 0; i--)
            aux[i] = nums[i] & aux[i + 1];
        for(int i = 0, cur = nums[0]; i < n - 1; i++) {
            cur &= nums[i];
            if(cur == 0 && aux[i + 1] == 0) {
                res++;
                cur = nums[i + 1];
            }
        }
        return res + 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}