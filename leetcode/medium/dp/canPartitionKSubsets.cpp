/**
 * @Time : 2022/6/6-9:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 超时
//    int n;
//    bool canPartitionKSubsets(vector<int>& nums, int k) {
//        int sum = accumulate(nums.begin(), nums.end(), 0);
//        if(sum % k != 0) return false;
//        this->n = nums.size();
//        sort(nums.begin(), nums.end());
//        return backTrack(nums, 0, sum / k, sum / k);
//    }
//
//    bool backTrack(vector<int>& nums, int cur, int left, int len){
//        if(cur == n) return true;
//        if(left == 0) left = len;
//        for(int i = n - 1, pre = -1; i >= 0; i--){
//            int temp = nums[i];
//            if(temp == -1 || temp == pre) continue;
//            if(left - temp < 0) break;
//            pre = temp;
//            nums[i] = -1;
//            if(backTrack(nums, cur + 1, left - temp, len)) return true;
//            nums[i] = temp;
//        }
//        return false;
//    }

/**
 * nums.length <= 16 可以用一个int来表示数的选取状态
 * （为什么要进行状态压缩，因为在暴力回溯的时候有重复计算，会超时，通过状态来进行记忆化搜索）
 * 用二进制的1表示该位置的数已经被选取了。
 * 那么所有数字能分成k个和相等的分组就意味着，最终状态全为1
 */
    int n, final_state;
    vector<int> cache;
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        this->n = nums.size();
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if(sum % k != 0) return false;
        sort(nums.begin(), nums.end());
        int len = sum / k;
        final_state = (1 << n) - 1;
        cache.assign(final_state + 1, -1);
        return partition(nums, 0, len, len);
    }


    bool partition(vector<int>& nums, int state, int left, int len){
        if(state == final_state) return true;
        if(cache[state] != -1) return cache[state];
        if(left == 0) left = len;
        for(int i = n; i > 0; i--){
            int mask = 1 << (i - 1);
            if(state & mask) continue; // 该位的数字已经被选取了，跳过
            if(left < nums[i - 1]) break;
            if(partition(nums, state | mask, left - nums[i - 1], len)){
                cache[state] = 1;
                return true;
            }
        }
        cache[state] = 0;
        return false;
    }
};

int main(){
    Solution s;
    vector<int> nums = {5309,7138,779,8949,8568,2250,1794,6539,4948,7189,4270,9866,5867,2112,9176,3162};
    cout << s.canPartitionKSubsets(nums, 2) << endl;
}