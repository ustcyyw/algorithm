/**
 * @Time : 2022/11/2-10:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个正整数数组 nums，你需要从中任选一些子集，然后将子集中每一个数乘以一个 任意整数，并求出他们的和。

假如该和结果为 1，那么原数组就是一个「好数组」，则返回 True；否则请返回 False。

 

示例 1：

输入：nums = [12,5,7,23]
输出：true
解释：挑选数字 5 和 7。
5*3 + 7*(-2) = 1
示例 2：

输入：nums = [29,6,10]
输出：true
解释：挑选数字 29, 6 和 10。
29*1 + 6*(-3) + 10*(-1) = 1
示例 3：

输入：nums = [3,6]
输出：false
 

提示：

1 <= nums.length <= 10^5
1 <= nums[i] <= 10^9

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/check-if-it-is-a-good-array
 */
class Solution {
public:
    /**
     * 裴蜀定理(重要推论) : a,b互质的充分必要条件是存在整数x,y使ax+by=1。
     * 因此只要数组中存在两个互质的数，将他们取出，就可以通过ax+by=1。
     * 是否存在互质的数，求gcd即可。gcd = 1，就是有互质的数
     */
    bool isGoodArray(vector<int>& nums) {
        int num = nums[0];
        for(int i = 1; i < nums.size(); i++)
            num = gcd(num, nums[i]);
        return num == 1;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}