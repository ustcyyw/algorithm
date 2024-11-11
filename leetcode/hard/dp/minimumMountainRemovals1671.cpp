/**
 * @Time : 2022/10/1-8:09 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 我们定义 arr 是 山形数组 当且仅当它满足：

arr.length >= 3
存在某个下标 i （从 0 开始） 满足 0 < i < arr.length - 1 且：
arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
给你整数数组 nums​ ，请你返回将 nums 变成 山形状数组 的​ 最少 删除次数。

 

示例 1：

输入：nums = [1,3,1]
输出：0
解释：数组本身就是山形数组，所以我们不需要删除任何元素。
示例 2：

输入：nums = [2,1,1,5,6,2,3,1]
输出：3
解释：一种方法是将下标为 0，1 和 5 的元素删除，剩余元素为 [1,5,6,3,1] ，是山形数组。
 

提示：

3 <= nums.length <= 1000
1 <= nums[i] <= 109
题目保证 nums 删除一些元素后一定能得到山形数组。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-number-of-removals-to-make-mountain-array
 */
class Solution {
public:
    /**
     * n^2 log(n) 的做法
     */
//    int n;
//    int minimumMountainRemovals(vector<int>& nums) {
//        n = nums.size();
//        int res = INT_MAX;
//        for(int i = 1; i < n - 1; i++){
//            int t1 = leftRemove(nums, i);
//            if(t1 == -1) continue;
//            int t2 = rightRemove(nums, i);
//            if(t2 != -1) res = min(res, t1 + t2);
//        }
//        return res;
//    }
//
//    int leftRemove(vector<int>& nums, int top){
//        vector<int> dp; // dp[i]：长度为i的子序列的最小元素
//        dp.push_back(nums[top]);
//        for(int i = top - 1; i >= 0; i--)
//            add(dp, nums[i]);
//        return dp.size() == 1 ? - 1 : top + 1 - dp.size();
//    }
//
//    int rightRemove(vector<int>& nums, int top){
//        vector<int> dp; // dp[i]：长度为i的子序列的最小元素
//        dp.push_back(nums[top]);
//        for(int i = top + 1; i < n; i++)
//            add(dp, nums[i]);
//        return dp.size() == 1 ? - 1 : n - top - dp.size();
//    }
//
//    void add(vector<int>& dp, int num){
//        if(dp.back() > num) {
//            dp.push_back(num);
//            return;
//        }
//        int lo = 0, hi = dp.size() - 1;
//        while (lo < hi){
//            int mid = (lo + hi) >> 1;
//            if(dp[mid] <= num) hi = mid;
//            else lo = mid + 1;
//        }
//        dp[lo] = num;
//    }

    /**
     * 方法2：从左向右走到山顶是递增序列，从右向左走到山顶也是递增序列
     * 在枚举山顶的时候要保证左边，右边删去的最少，就要找到山顶为最大元素的LIS的长度
     *
     * 相比方法1，可以正着计算LIS的时候，记录每个数做为最大元素的LIS的长度
     * 再反着来一次，完成预处理。然后再枚举山顶即可
     */
    int n;
    int minimumMountainRemovals(vector<int>& nums){
        n = nums.size();
        int res = INT_MAX;
        vector<int> leftLen = leftLIS(nums), rightLen = rightLIS(nums);
        for(int i = 1; i < n - 1; i++){
            if(leftLen[i] != 1 && rightLen[i] != 1)
                res = min(res, n - (leftLen[i] + rightLen[i] - 1));
        }
        return res;
    }

    vector<int> leftLIS(vector<int>& nums){
        // dp[i]：长度为i的子序列的最小元素; len[i]：以nums[i]为结尾的LIS的长度
        vector<int> dp, len(n, 1);
        dp.push_back(nums[0]);
        for(int i = 1; i < n; i++)
            add(dp, nums[i], len, i);
        return len;
    }

    vector<int> rightLIS(vector<int>& nums){
        vector<int> dp, len(n, 1);
        dp.push_back(nums[n - 1]);
        for(int i = n - 2; i >= 0; i--)
            add(dp, nums[i], len, i);
        return len;
    }
    // 和方法1中的不等号方向相反，因为方法1找的是最长下降子序列，这里找最长上升子序列
    void add(vector<int>& dp, int num, vector<int>& len, int i){
        if(dp.back() < num) {
            dp.push_back(num);
            len[i] = dp.size();
            return;
        }
        int lo = 0, hi = dp.size() - 1;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(dp[mid] >= num) hi = mid;
            else lo = mid + 1;
        }
        len[i] = lo + 1; // 确定了num的位置，应该放在lo处，那么以它为最后一个元素的LIS的长度为lo + 1
        dp[lo] = num;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}