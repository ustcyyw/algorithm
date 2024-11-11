/**
 * @Time : 2022/6/28-10:09 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的整数数组 nums 。一次操作中，选择 任意 非负整数 x 和一个下标 i ，更新 nums[i] 为 nums[i] AND (nums[i] XOR x) 。

注意，AND 是逐位与运算，XOR 是逐位异或运算。

请你执行 任意次 更新操作，并返回 nums 中所有元素 最大 逐位异或和。

 

示例 1：

输入：nums = [3,2,4,6]
输出：7
解释：选择 x = 4 和 i = 3 进行操作，num[3] = 6 AND (6 XOR 4) = 6 AND 2 = 2 。
现在，nums = [3, 2, 4, 2] 且所有元素逐位异或得到 3 XOR 2 XOR 4 XOR 2 = 7 。
可知 7 是能得到的最大逐位异或和。
注意，其他操作可能也能得到逐位异或和 7 。
示例 2：

输入：nums = [1,2,3,9,2]
输出：11
解释：执行 0 次操作。
所有元素的逐位异或和为 1 XOR 2 XOR 3 XOR 9 XOR 2 = 11 。
可知 11 是能得到的最大逐位异或和。
 

提示：

1 <= nums.length <= 105
0 <= nums[i] <= 108


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-xor-after-operations
 */
class Solution {
public:
    /**
     * 因为与操作的存在，所以没有办法在原来是0的地方增加1
     * x可以任选，因此对于某一个具体的数，可以将任何一个位的1变为0
     *
     * 最后都要进行异或操作，因此要让出现过1的二进制位，有且仅有一个1
     * 那只需要知道哪些位置出现过1即可（不需要关注怎么去将多余的变为0，只需要知道一次操作就可以实现将某个数多余的1全变0）
     */
//    int maximumXOR(vector<int>& nums) {
//        vector<bool> hasOne = vector(32, false);
//        for(int num : nums){
//            bitset<32> set(num);
//            for(int i = 0; i < 32; i++)
//                if(set[i]) hasOne[i] = true;
//        }
//        int res = 0;
//        long temp = 1;
//        for(int i = 0; i < 32; i++, temp <<= 1)
//            res += hasOne[i] * temp;
//        return res;
//    }
    /**
     * 保留每一位出现的1，进行位或运算即可
     */
    int maximumXOR(vector<int>& nums){
        int res = 0;
        for(int num : nums)
            res |= num;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}