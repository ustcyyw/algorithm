/**
 * @Time : 2022/9/1-10:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个长度为 2 * n 的整数数组。你需要将 nums 分成 两个 长度为 n 的数组，分别求出两个数组的和，并 最小化 两个数组和之 差的绝对值 。nums 中每个元素都需要放入两个数组之一。

请你返回 最小 的数组和之差。

 

示例 1：



输入：nums = [3,9,7,3]
输出：2
解释：最优分组方案是分成 [3,9] 和 [7,3] 。
数组和之差的绝对值为 abs((3 + 9) - (7 + 3)) = 2 。
示例 2：

输入：nums = [-36,36]
输出：72
解释：最优分组方案是分成 [-36] 和 [36] 。
数组和之差的绝对值为 abs((-36) - (36)) = 72 。
示例 3：



输入：nums = [2,-1,0,4,-2,-9]
输出：0
解释：最优分组方案是分成 [2,4,-9] 和 [-1,0,-2] 。
数组和之差的绝对值为 abs((2 + 4 + -9) - (-1 + 0 + -2)) = 0 。
 

提示：

1 <= n <= 15
nums.length == 2 * n
-107 <= nums[i] <= 107


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/partition-array-into-two-arrays-to-minimize-sum-difference
 */
class Solution {
public:
    /**
     * 执行用时：736 ms, 在所有 C++ 提交中击败了51.08%的用户
     * 内存消耗：68.6 MB, 在所有 C++ 提交中击败了57.56%的用户
     *
     * 总共只有30个元素，看起来可以状态压缩，但是2^30太大了
     * 如果能分为两个组别（刚好本题也是要求分组）
     * 每个组别只有15个元素，则每个组别内的分类情况就可以用状态压缩来全求出来
     * 将前15个元素一个组别，后15个元素一个组别
     *
     * 用1表示某个元素分给了子数组a
     * 前n个元素，可以分给a的元素数量是0～n
     * 如果前n个元素分了i个给a，那么后n就只能分n - i个元素给a
     *
     * 所以关于元素分配的信息，应该按a分得几个元素来分组
     * 比如a获得2个元素的，放在一个组，a获得1个元素的又放在另外一个组
     *
     * 关于元素分配的信息，具体是什么信息呢?
     * 题目要求两个 <子数组和> 的差值，那就是要存 <数组和> 相关的信息
     *
     * 由于2n个元素被我们分成两半，
     * sum_a = sum_a1 + sum_a2
     * sum_b = sum_b1 + sum_b2
     * diff = sum_a - sum_b = sum_a1 - sum_b1 + sum_a2 - sum_b2
     * = diff1 + diff2
     * 其中diff1 = sum_a1 - sum_b1，就是前n个元素分给a和b两个子数组后的差值
     *
     * 对于前n个（后n个）元素，根据状态可以求出分给了a的和，总和也可求，就能得出分给b的和
     * 于是也可以知道diff1（diff2）
     *
     * diff最小是0，假设就取diff = 0， 此时 diff2 = -diff1
     * 随着diff1的增大，-diff1减小，diff2要减小
     * 如果每一对分组存放的是数组和之差，并且每一对分组中的<数组和>是排序的，就可以使用双指针
     * 减小diff2至 diff2 <= -diff1，此时 diff2 + diff1 <= 0，且能取到最接近0的负值
     * 而前一个diff2 + diff1 > 0，并且能取到最接近0的正值
     *
     * 枚举所有的diff1，枚举diff1的同时，diff2在单调变化
     * 求出这一对分组下的最小差
     * 再枚举所有的分组对就能得出最终答案。
     */
    int n, max_val = 1e9;
    int minimumDifference(vector<int>& nums) {
        n = nums.size() / 2;
        vector<int> t1, t2;
        for(int i = 0; i < nums.size(); i++){
            if(i < n) t1.push_back(nums[i]);
            else t2.push_back(nums[i]);
        }
        vector<vector<int>> left = combination(t1), right = combination(t2);
        int res = max_val;
        for(int i = 0; i <= n; i++){
            if(res == 0) return 0;
            res = min(res, min_diff(left[i], right[n - i]));
        }
        return res;
    }

    int min_diff(vector<int>& arr1, vector<int>& arr2){
        int res = max_val, m = arr2.size();
        for(int i = 0, j = m - 1; i < arr1.size() ; i++){
            int a = arr1[i];
            while (j > 0 && arr2[j] > -a) j--;
            int t1 = j < m - 1 ? abs(arr2[j + 1] + a) : max_val;
            int t2 = j >= 0 ? abs(arr2[j] + a) : max_val;
            res = min(res, min(t1, t2));
            if(res == 0) return res;
        }
        return res;
    }

    vector<vector<int>> combination(vector<int>& nums){
        vector<vector<int>> res(n + 1, vector(0, 0));
        int u = (1 << n) - 1, sum = accumulate(nums.begin(), nums.end(), 0);
        res[0].push_back(-sum);
        for(int s = u; s ; s = u & (s - 1)){
            int a_sum = 0;
            for(int j = 0; j < n; j++){
                if((1 << j) & s)
                    a_sum += nums[j];
            }
            res[bit_count(s)].push_back(a_sum - (sum - a_sum));
        }
        for(auto& arr : res)
            sort(arr.begin(), arr.end());
        return res;
    }

    int bit_count(int i) {
        i = i - ((i >> 1) & 0x55555555);
        i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
        i = (i + (i >> 4)) & 0x0f0f0f0f;
        i = i + (i >> 8);
        i = i + (i >> 16);
        return i & 0x3f;
    }
};

int main(){
    Solution s;
    vector<int> arr = {-36,36};
    s.minimumDifference(arr);
    cout << 0 << endl;
}