/**
 * @Time : 2022/8/18-8:40 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个正整数数组 nums，请你帮忙从该数组中找出能满足下面要求的 最长 前缀，并返回该前缀的长度：

从前缀中 恰好删除一个 元素后，剩下每个数字的出现次数都相同。
如果删除这个元素后没有剩余元素存在，仍可认为每个数字都具有相同的出现次数（也就是 0 次）。

 

示例 1：

输入：nums = [2,2,1,1,5,3,3,5]
输出：7
解释：对于长度为 7 的子数组 [2,2,1,1,5,3,3]，如果我们从中删去 nums[4] = 5，就可以得到 [2,2,1,1,3,3]，里面每个数字都出现了两次。
示例 2：

输入：nums = [1,1,1,2,2,2,3,3,3,4,4,4,5]
输出：13
 

提示：

2 <= nums.length <= 105
1 <= nums[i] <= 105


来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-equal-frequency
 */
class Solution {
public:
    /**
     * 执行用时：100 ms, 在所有 C++ 提交中击败了72.39%的用户
     * 内存消耗：41.8 MB, 在所有 C++ 提交中击败了89.55%的用户
     */
    int maxEqualFreq(vector<int>& nums) {
        unordered_map<int, int> map; // 记录每个元素出现的次数
        // max_freq:元素出现的最大频率；max_count：最大频率的元素有几个；min_count：最小频率（1）的元素有几个
        int max_freq = 0, max_count = 0, min_count = 0, res = 0;
        for(int i = 0; i < nums.size(); i++){
            int num = nums[i];
            map[num] = map.count(num) ? map[num] + 1 : 1;
            if(map[num] == 1) min_count++;
            if(map[num] == 2) min_count--;
            if(map[num] > max_freq){
                max_freq = map[num];
                max_count = 1;
            } else if(map[num] == max_freq)
                max_count++;
            if(check(map.size(), max_freq, max_count, min_count, i))
                res = i;
        }
        return res + 1;
    }
    // count : nums[0,i]上的元素出现了多少种
    bool check(int count, int max_freq, int max_count, int min_count, int i){
        // 只出现一种元素；或者所有元素都是只出现了一次的，那么随意移除一个都正确
        if(count == 1 || min_count == count) return true;
        // 出现一次的元素只有一个时，才应该考虑移除最小元素
        // 移除最小频率元素，那么剩下的只应该有同频率的最大同频元素
        if(min_count == 1) {
            return max_count == count - 1;
        } else {
            // 最小频率的元素有至少2种或者没有，那么只能移除最大频率的元素中的一个
            // 最大频率元素的频率是1的情况在min_count == count的分支中已返回，
            // 这里最大频率大于1，因此如果最大频率的数超过1个，移除一个元素，就会出现不同频
            // 剩余元素的最大频率是max_freq - 1，只有所有元素都是这个频率，频率*元素种类数才会等于元素数量i
            if(max_count != 1) return false;
            return (max_freq - 1) * count == i;
        }
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,1,1,4,2,2,2,3,3,3,4,4,4,5,2,2,1,1,5,3,3,5};
    s.maxEqualFreq(arr);
    cout << 0 << endl;
}