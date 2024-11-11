/**
 * @Time : 2022/9/1-4:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums 和一个目标值 goal 。

你需要从 nums 中选出一个子序列，使子序列元素总和最接近 goal 。也就是说，如果子序列元素和为 sum ，你需要 最小化绝对差 abs(sum - goal) 。

返回 abs(sum - goal) 可能的 最小值 。

注意，数组的子序列是通过移除原始数组中的某些元素（可能全部或无）而形成的数组。

 

示例 1：

输入：nums = [5,-7,3,5], goal = 6
输出：0
解释：选择整个数组作为选出的子序列，元素和为 6 。
子序列和与目标值相等，所以绝对差为 0 。
示例 2：

输入：nums = [7,-9,15,-2], goal = -5
输出：1
解释：选出子序列 [7,-9,-2] ，元素和为 -4 。
绝对差为 abs(-4 - (-5)) = abs(1) = 1 ，是可能的最小值。
示例 3：

输入：nums = [1,2,3], goal = -7
输出：7
 

提示：

1 <= nums.length <= 40
-107 <= nums[i] <= 107
-109 <= goal <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/closest-subsequence-sum
 */
class Solution {
public:
    /**
     * 将数组分为前后两个部分
     * 通过状态压缩的方式分别求出两个部分所有可能的子序列和
     * 分别记为left，right
     * 那么整个数组的子序列和就是 left[i] + right[j]，对i，j进行枚举
     * 要使子序列和于goal的差值为 left[i] + right[j] - goal，最小可能为0
     * 此时 right[j] = goal - left[i], 随着left[i]增大，right[j]减小
     *
     * 从小到大枚举left[i]，如果两个数组都是有序的，为使序列和最接近为goal
     * right[j] = goal - left[i] 减小，可以使用双指针
     * 让right[j]刚好比goal - left[i]小或者等于，此时 right[j] <= goal - left[i]
     * 也就是 right[j] + left[i] <= goal，能取到最接近goal且小于等于goal的子序和
     * 而right[j + 1] + left[i] > goal，能取到最接近goal且大于goal的子序和
     */
    int minAbsDifference(vector<int>& nums, int goal) {
        int n = nums.size();
        vector<int> a1, a2;
        for(int i = 0; i < n; i++){
            if(i < n / 2) a1.push_back(nums[i]);
            else a2.push_back(nums[i]);
        }
        vector<int> left = sub_sum(a1), right = sub_sum(a2);
        int max_val = 2e9, res = max_val;
        for(int i = 0, j = (int)right.size() - 1; i < left.size(); i++){
            while (j >= 0 && right[j] > goal - left[i]) j--;
            int t1 = j == -1 ? max_val : abs(left[i] + right[j] - goal);
            int t2 = j == (int)right.size() - 1 ? max_val : abs(left[i] + right[j + 1] - goal);
            res = min(res, min(t1, t2));
            if(res == 0) return 0;
        }
        return res;
    }

    vector<int> sub_sum(vector<int> nums){
        int n = nums.size(), u = (1 << n) - 1;
        vector<int> arr;
        arr.push_back(0);
        for(int s = u; s ; s = u & (s - 1)){
            int sum = 0;
            for(int j = 0; j < n; j++)
                if((1 << j) & s)
                    sum += nums[j];
            arr.push_back(sum);
        }
        sort(arr.begin(), arr.end());
        return arr;
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,2,3};
    s.minAbsDifference(arr, -7);
    cout << 0 << endl;
}