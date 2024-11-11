/**
 * @Time : 2022/7/17-1:36 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/**
 * 作为国王的统治者，你有一支巫师军队听你指挥。

给你一个下标从 0 开始的整数数组 strength ，其中 strength[i] 表示第 i 位巫师的力量值。对于连续的一组巫师（也就是这些巫师的力量值是 strength 的 子数组），总力量 定义为以下两个值的 乘积 ：

巫师中 最弱 的能力值。
组中所有巫师的个人力量值 之和 。
请你返回 所有 巫师组的 总 力量之和。由于答案可能很大，请将答案对 109 + 7 取余 后返回。

子数组 是一个数组里 非空 连续子序列。

 

示例 1：

输入：strength = [1,3,1,2]
输出：44
解释：以下是所有连续巫师组：
- [1,3,1,2] 中 [1] ，总力量值为 min([1]) * sum([1]) = 1 * 1 = 1
- [1,3,1,2] 中 [3] ，总力量值为 min([3]) * sum([3]) = 3 * 3 = 9
- [1,3,1,2] 中 [1] ，总力量值为 min([1]) * sum([1]) = 1 * 1 = 1
- [1,3,1,2] 中 [2] ，总力量值为 min([2]) * sum([2]) = 2 * 2 = 4
- [1,3,1,2] 中 [1,3] ，总力量值为 min([1,3]) * sum([1,3]) = 1 * 4 = 4
- [1,3,1,2] 中 [3,1] ，总力量值为 min([3,1]) * sum([3,1]) = 1 * 4 = 4
- [1,3,1,2] 中 [1,2] ，总力量值为 min([1,2]) * sum([1,2]) = 1 * 3 = 3
- [1,3,1,2] 中 [1,3,1] ，总力量值为 min([1,3,1]) * sum([1,3,1]) = 1 * 5 = 5
- [1,3,1,2] 中 [3,1,2] ，总力量值为 min([3,1,2]) * sum([3,1,2]) = 1 * 6 = 6
- [1,3,1,2] 中 [1,3,1,2] ，总力量值为 min([1,3,1,2]) * sum([1,3,1,2]) = 1 * 7 = 7
所有力量值之和为 1 + 9 + 1 + 4 + 4 + 4 + 3 + 5 + 6 + 7 = 44 。
示例 2：

输入：strength = [5,4,6]
输出：213
解释：以下是所有连续巫师组：
- [5,4,6] 中 [5] ，总力量值为 min([5]) * sum([5]) = 5 * 5 = 25
- [5,4,6] 中 [4] ，总力量值为 min([4]) * sum([4]) = 4 * 4 = 16
- [5,4,6] 中 [6] ，总力量值为 min([6]) * sum([6]) = 6 * 6 = 36
- [5,4,6] 中 [5,4] ，总力量值为 min([5,4]) * sum([5,4]) = 4 * 9 = 36
- [5,4,6] 中 [4,6] ，总力量值为 min([4,6]) * sum([4,6]) = 4 * 10 = 40
- [5,4,6] 中 [5,4,6] ，总力量值为 min([5,4,6]) * sum([5,4,6]) = 4 * 15 = 60
所有力量值之和为 25 + 16 + 36 + 36 + 40 + 60 = 213 。
 

提示：

1 <= strength.length <= 105
1 <= strength[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/sum-of-total-strength-of-wizards
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    /**
     * 本题有两类思路，都是锁定某个元素，看某一个元素的贡献
     * 1.使用单调栈，找到某个元素前一个，后一个更小的元素。
     * 锁定该元素，以该元素为数组最小元素，得到子数组的范围边界，将边界内包含该元素的所有子数组之和再次求和
     * 乘以该元素，就是该元素贡献的力量
     *
     * 2.考虑某元素，将包含它的所有子数组中的最小元素求和(sum of min_val:som)
     * 用som乘以该元素，就是该元素贡献的力量
     */

    /**
     * 首先来分析第二种方法
     * 以数组[1,3,1,2]为例子 关注3所在的所有子数组贡献的力量
     * [1,3] : min(1,3) * (1 + 3)
     * [1,3,1]: min(1,3,1) * (1 + 3 + 1)
     * [1,3,1,2]: min(1,3,1,2) * (1 + 3 + 1 + 2)
     * [3]:min(3) * 3
     * [3,1]: min(3,1) * (1 + 3)
     * [3,1,2]: min(3,1,2) * (3 + 1 + 2)
     * 将含有3的项合并
     *  [min(1,3) + min(1,3,1) + min(1,3,1,2) + min(3) + min(3,1) + min(3,1,2)] * 3
     *  3贡献的力量
     *  = 3 * 所有3在的子数组的som
     *  = 所有子数组的som - 3不在的所有子数字的som
     *  = 所有子数字的som - (以3左边元素为结尾的子数组som + 以3右边为开头的子数组som)
     *
     *  推广到一般，记left[i]为所有以i为结尾的子数组的som，right[i]为所有以i为开头的子数组的som
     *  那么left数组的前缀和leftSum[i - 1]就表示所有以arr[i]左边元素为结尾的子数组som
     *  right数组的后缀和rightSum[i + 1]就表示所有以arr[i]右边元素为开头的子数组som
     *  arr[i]贡献的力量为
     *  arr[i] * (total_som - leftSum[i - 1] - rightSum[i + 1])
     *  并且total_som = sum(left[i]) = left[n - 1]
     *
     *  计算left[i]
     *  left[i] = a[i] + min{a[i],a[i-1]} + min{a[i],a[i-1],a[i-2]} + .. + min{a[i],a[i-1],a[i-2],..,a[0]}
     *  如果i的前面第一个小于等于a[i]的数是a[j],那么
     *  left[i] = a[i] + min{a[i],a[i-1]} + .. + min{a[i],a[i-1],...,a[j],..,a[0]}
     *  min{a[i],a[i-1]} = a[i], 因为第一个小于等于a[i]的数是a[j], a[j + 1, i - 1]上的数都比a[i]大
     *  min{a[i],a[i-1],...,a[j],..,a[0]} = min{a[j],..,a[0]}
     *  于是left[i] = a[i] + a[i] + ... + a[j] + min{a[j],a[j - 1]} + ... + min{a[j],a[j - 1],...,a[0]}
     *  = a[i] * (i - (j + 1) + 1) + left[j]
     *
     */
    int mod = 1e9 + 7;
    int totalStrength(vector<int>& strength) {
        int n = strength.size();
        if(n == 1) return (int)((long long)strength[0] * (long long)strength[0] % mod);
        vector<long long> left = vector(n, 0ll), right = vector(n, 0ll);
        // 计算left[i]
        stack<int> stack1;
        for(int i = 0; i < n; i++) {
            int cur = strength[i];
            while (!stack1.empty() && strength[stack1.top()] > cur)
                stack1.pop();
            if(stack1.empty()) left[i] = (long long)cur * (i + 1);
            else left[i] = (left[stack1.top()] + (long long)cur * (i - stack1.top())) % mod;
            stack1.push(i);
        }
        // 计算right[i]
        stack<int> stack2;
        for(int i = n - 1; i >= 0; i--) {
            int cur = strength[i];
            while (!stack2.empty() && strength[stack2.top()] > cur)
                stack2.pop();
            if(stack2.empty()) right[i] = (long long)cur * (n - i);
            else right[i] = (right[stack2.top()] + (long long)cur * (stack2.top() - i)) % mod;
            stack2.push(i);
        }
        // 计算leftSum, rightSum
        vector<long long> leftSum = vector(n, 0ll), rightSum = vector(n, 0ll);
        leftSum[0] = left[0], rightSum[n - 1] = right[n - 1];
        for(int i = 1; i < n; i++)
            leftSum[i] = (leftSum[i - 1] + left[i]) % mod;
        for(int i = n - 2; i >= 0; i--)
            rightSum[i] = (rightSum[i + 1] + right[i]) % mod;

        long long total_som = leftSum[n - 1] + 2 * mod, res = 0;
        res = strength[0] * right[0] + strength[n - 1] * left[n - 1];
        for(int i = 1; i < n - 1; i++){
            long long temp = (total_som - leftSum[i - 1] - rightSum[i + 1]) % mod;
            res = (res + (long long)strength[i] * temp) % mod;
        }
        return (int)(res % mod);
    }
};

int main(){
    Solution s;
    vector<int> strength = {1,1000000000};
    s.totalStrength(strength);
    cout << 0 << endl;
}