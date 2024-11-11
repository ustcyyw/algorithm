/**
 * @Time : 2023/2/25-1:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给你一个整数数组 nums，请你找出并返回能被三整除的元素最大和。

 

示例 1：

输入：nums = [3,6,5,1,8]
输出：18
解释：选出数字 3, 6, 1 和 8，它们的和是 18（可被 3 整除的最大和）。
示例 2：

输入：nums = [4]
输出：0
解释：4 不能被 3 整除，所以无法选出数字，返回 0。
示例 3：

输入：nums = [1,2,3,4,4]
输出：12
解释：选出数字 1, 3, 4 以及 4，它们的和是 12（可被 3 整除的最大和）。
 

提示：

1 <= nums.length <= 4 * 10^4
1 <= nums[i] <= 10^4

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/greatest-sum-divisible-by-three
 */
class Solution {
public:
    int maxSumDivThree(vector<int>& nums) {
        vector<int> one, two;
        for(int num : nums){
            if(num % 3 == 1) one.push_back(num);
            if(num % 3 == 2) two.push_back(num);
        }
        sort(one.begin(), one.end()), sort(two.begin(), two.end());
        int sum = accumulate(nums.begin(), nums.end(), 0);
        return max(sum - pick(one, two), sum - pick(two, one));
    }

    int pick(vector<int>& arr1, vector<int>& arr2){
        int n = arr1.size(), m = arr2.size(), t = n % 3;
        int less = 0;
        if(t <= m){
            for(int i = 0; i < (m - t) % 3; i++) less += arr2[i];
        } else {
            for(int i = 0; i < t - m; i++) less += arr1[i];
        }
        return less;
    }
};

int main(){
    Solution s;
    vector<int> arr = {2,19,6,16,5,10,7,4,11,6};
    s.maxSumDivThree(arr);
    cout << 0 << endl;
}