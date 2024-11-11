/**
 * @Time : 2022/7/19-11:32 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 对数组 nums 执行 按位与 相当于对数组 nums 中的所有整数执行 按位与 。

例如，对 nums = [1, 5, 3] 来说，按位与等于 1 & 5 & 3 = 1 。
同样，对 nums = [7] 而言，按位与等于 7 。
给你一个正整数数组 candidates 。计算 candidates 中的数字每种组合下 按位与 的结果。 candidates 中的每个数字在每种组合中只能使用 一次 。

返回按位与结果大于 0 的 最长 组合的长度。

 

示例 1：

输入：candidates = [16,17,71,62,12,24,14]
输出：4
解释：组合 [16,17,62,24] 的按位与结果是 16 & 17 & 62 & 24 = 16 > 0 。
组合长度是 4 。
可以证明不存在按位与结果大于 0 且长度大于 4 的组合。
注意，符合长度最大的组合可能不止一种。
例如，组合 [62,12,24,14] 的按位与结果是 62 & 12 & 24 & 14 = 8 > 0 。
示例 2：

输入：candidates = [8,8]
输出：2
解释：最长组合是 [8,8] ，按位与结果 8 & 8 = 8 > 0 。
组合长度是 2 ，所以返回 2 。
 

提示：

1 <= candidates.length <= 105
1 <= candidates[i] <= 107

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/largest-combination-with-bitwise-and-greater-than-zero
 */
class Solution {
public:
    /**
     * 要保证位与最终结果大于0，就要求至少有一个二进制位上是1
     * 一个最大1e7的数的二进制位上最多有24位可能有1
     * 如果一个大于0的数有两个二进制位上是1，如入0010010
     * 那么其要求一定比0010000和0000010更严格
     * 如果说第5位上是1的集合为a，第2位上是1的集合为b
     * 那么能与操作得到0010010的，是a和b的交集，这个集合的大小会小于等于min{a,b}
     *
     * 因此要找到最大集合，只需要关注某一位为1，其它是1是0无所谓的数。
     * 于是将candidates中的数按某一个二进制为1进行分类即可。
     */
    int largestCombination(vector<int>& candidates) {
        vector<int> counts = vector(24, 0);
        for(int num : candidates){
            for(int i = 0, mask = 1; i < 24; i++, mask <<= 1){
                if(mask & num)
                    counts[i]++;
            }
        }
        int res = 0;
        for(int num : counts)
            res = max(res, num);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}