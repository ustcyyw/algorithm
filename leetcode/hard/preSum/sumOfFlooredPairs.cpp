/**
 * @Time : 2022/7/26-7:13 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 nums ，请你返回所有下标对 0 <= i, j < nums.length 的 floor(nums[i] / nums[j]) 结果之和。由于答案可能会很大，请你返回答案对109 + 7 取余 的结果。

函数 floor() 返回输入数字的整数部分。

 

示例 1：

输入：nums = [2,5,9]
输出：10
解释：
floor(2 / 5) = floor(2 / 9) = floor(5 / 9) = 0
floor(2 / 2) = floor(5 / 5) = floor(9 / 9) = 1
floor(5 / 2) = 2
floor(9 / 2) = 4
floor(9 / 5) = 1
我们计算每一个数对商向下取整的结果并求和得到 10 。
示例 2：

输入：nums = [7,7,7,7,7,7,7]
输出：49
 

提示：

1 <= nums.length <= 105
1 <= nums[i] <= 105

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/sum-of-floored-pairs
 */
class Solution {
public:
    /**
     * 对于某个确定对数 a
     * 数组中落在区间[0, a - 1]的数与其组成的数对(b, a)的贡献值为0
     * 落在[a, 2 * a - 1]的与其组成的数对的贡献值为1
     * 落在[2 * a, 3 * a - 1]的与其组成的数对的贡献值为2
     * 因此对于某一个数，只要需要关注大于等于它自身的数，且知道区间长度为其自身的多段区间内有多少个数
     * 就可以算出以它为第二个数的数对 对 和的贡献
     * 考虑到题目给出的数据范围，就可以使用前缀和来完成
     * (关注的是大于等于自身的数，因此是后缀和)
     */
    int n = 1e5 + 2, mod = 1e9 + 7;
    int sumOfFlooredPairs(vector<int>& nums) {
        vector<int> counts = vector(n, 0), sum = vector(n, 0);
        int maxNum = 0;
        for(int& num : nums){
            counts[num]++;
            maxNum = max(maxNum, num);
        }
        long res = 0;
        for(int num = maxNum; num >= 0; num--){
            sum[num] = sum[num + 1] + counts[num];
            if(counts[num] == 0) continue;
            for(int k = 1; num * k <= maxNum; k++){
                long temp = (long)(sum[num * k] - sum[min(num * (k + 1), n - 1)]) * counts[num] * k;
                res = (res + temp) % mod;
            }
        }
        return (int) res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}