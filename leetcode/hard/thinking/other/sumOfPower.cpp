/**
 * @Time : 2023/5/14-11:47 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你一个下标从 0 开始的整数数组 nums ，它表示英雄的能力值。如果我们选出一部分英雄，这组英雄的 力量 定义为：

i0 ，i1 ，... ik 表示这组英雄在数组中的下标。那么这组英雄的力量为 max(nums[i0],nums[i1] ... nums[ik])2 * min(nums[i0],nums[i1] ... nums[ik]) 。
请你返回所有可能的 非空 英雄组的 力量 之和。由于答案可能非常大，请你将结果对 109 + 7 取余。

 

示例 1：

输入：nums = [2,1,4]
输出：141
解释：
第 1 组：[2] 的力量为 22 * 2 = 8 。
第 2 组：[1] 的力量为 12 * 1 = 1 。
第 3 组：[4] 的力量为 42 * 4 = 64 。
第 4 组：[2,1] 的力量为 22 * 1 = 4 。
第 5 组：[2,4] 的力量为 42 * 2 = 32 。
第 6 组：[1,4] 的力量为 42 * 1 = 16 。
第​ ​​​​​​7 组：[2,1,4] 的力量为 42​​​​​​​ * 1 = 16 。
所有英雄组的力量之和为 8 + 1 + 64 + 4 + 32 + 16 + 16 = 141 。
示例 2：

输入：nums = [1,1,1]
输出：7
解释：总共有 7 个英雄组，每一组的力量都是 1 。所以所有英雄组的力量之和为 7 。
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 109


来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/power-of-heroes
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    /*
     * 贡献法 计算每个数做为最小值的贡献，并且枚举最大值
     */
    int sumOfPower(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        long long res = 0, sum = 0;
        for(int i = 0; i < nums.size(); i++) { // 枚举最大值
            long long num = nums[i];
            // 集合只有当前数的情况 直接+ num ^ 3
            res = (res + num * num % mod * num % mod) % mod;
            // 选与不选nums[i-1]，nums[0, i-2]的数依然可以做为最小值进行贡献
            // 于是前面每个数做为最小值的子序列数 * 2
            sum = sum * 2 % mod;
            // 以nums[i-1]为最小值的子序列，前置nums[0, i-2]的数一个都不选 因此只有一种方案，贡献为nums[i-1]
            if(i > 0) sum = (sum + nums[i - 1]) % mod;
            res = (res + sum * num % mod * num % mod) % mod;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}