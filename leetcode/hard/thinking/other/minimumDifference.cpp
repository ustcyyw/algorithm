/**
 * @Time : 2022/8/24-1:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的整数数组 nums ，它包含 3 * n 个元素。

你可以从 nums 中删除 恰好 n 个元素，剩下的 2 * n 个元素将会被分成两个 相同大小 的部分。

前面 n 个元素属于第一部分，它们的和记为 sumfirst 。
后面 n 个元素属于第二部分，它们的和记为 sumsecond 。
两部分和的 差值 记为 sumfirst - sumsecond 。

比方说，sumfirst = 3 且 sumsecond = 2 ，它们的差值为 1 。
再比方，sumfirst = 2 且 sumsecond = 3 ，它们的差值为 -1 。
请你返回删除 n 个元素之后，剩下两部分和的 差值的最小值 是多少。

 

示例 1：

输入：nums = [3,1,2]
输出：-1
解释：nums 有 3 个元素，所以 n = 1 。
所以我们需要从 nums 中删除 1 个元素，并将剩下的元素分成两部分。
- 如果我们删除 nums[0] = 3 ，数组变为 [1,2] 。两部分和的差值为 1 - 2 = -1 。
- 如果我们删除 nums[1] = 1 ，数组变为 [3,2] 。两部分和的差值为 3 - 2 = 1 。
- 如果我们删除 nums[2] = 2 ，数组变为 [3,1] 。两部分和的差值为 3 - 1 = 2 。
两部分和的最小差值为 min(-1,1,2) = -1 。
示例 2：

输入：nums = [7,9,5,8,1,3]
输出：1
解释：n = 2 。所以我们需要删除 2 个元素，并将剩下元素分为 2 部分。
如果我们删除元素 nums[2] = 5 和 nums[3] = 8 ，剩下元素为 [7,9,1,3] 。和的差值为 (7+9) - (1+3) = 12 。
为了得到最小差值，我们应该删除 nums[1] = 9 和 nums[4] = 1 ，剩下的元素为 [7,5,8,3] 。和的差值为 (7+5) - (8+3) = 1 。
观察可知，最优答案为 1 。
 

提示：

nums.length == 3 * n
1 <= n <= 105
1 <= nums[i] <= 105

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-difference-in-sums-after-removal-of-elements
 */
class Solution {
public:
    /**
     * 题目很明显要求将数组分为两个子序列
     * 每个子序列的的元素个数为n
     * 要求差值最小，那么就需要让前一个子序列最小，后一个子序列最大
     *
     * 无论我们从3n个元素中除去哪些n个元素
     * 可以假定被除去的元素对应的位置变为无效，但是位置没有被移走，还是长度为3n的数组
     * 那么要保证第一个子序列有n个有效元素，分割开两个子序列的切割线就会因不同的移除元素方案而变化
     *
     * 前n个元素都没被移除，那么切割线的位置在n，nums[0,n-1]的元素构成第一个子序列
     * 后面[n, 3n - 1]中的元素被移除n个元素，还剩的n个元素构成第2个子序列
     *
     * 前n个元素都被移除，那么切割线的位置在n，前[0, 2n - 1]中的元素被移除n个元素，还剩的n个元素构成第1个子序列
     * 后面[2n, 3n - 1]的元素第2个子序列
     *
     * 于是切割线的位置范围是[n,2 n]
     * 相应的分割开的两部分，要移除一定数量的数，保证两个部分只剩下n个元素
     * 怎么移除元素呢？"让前一个子序列最小，后一个子序列最大"，就是这个贪心的宗旨
     * 前一个序列留下最小的n个元素，后一个序列留下最大的n个元素
     * 可以预处理最大，最小值序列
     */
    int n, m;
    long long minimumDifference(vector<int>& nums) {
        m = nums.size(), n = m / 3;
        vector<long long> first = get_min_sub(nums), second = get_max_sub(nums);
        long long res = 1e10;
        for(int i = n; i <= 2 * n; i++) // 枚举分割线
            res = min(res, first[i - 1] - second[i]);
        return res;
    }

    vector<long long> get_min_sub(vector<int>& nums){
        vector<long long> arr(m, 0);
        priority_queue<int> pq;
        long long sum = 0;
        for(int i = 0; i < n * 2; i++){
            sum += nums[i];
            pq.push(nums[i]);
            if(pq.size() > n) {
                sum -= pq.top();
                pq.pop();
            }
            arr[i] = sum;
        }
        return arr;
    }

    vector<long long> get_max_sub(vector<int>& nums){
        vector<long long> arr(m, 0);
        priority_queue<int, vector<int>, greater<>> pq;
        long long sum = 0;
        for(int i = m - 1; i >= n; i--){
            sum += nums[i];
            pq.push(nums[i]);
            if(pq.size() > n) {
                sum -= pq.top();
                pq.pop();
            }
            arr[i] = sum;
        }
        return arr;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}