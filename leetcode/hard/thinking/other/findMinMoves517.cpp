/**
 * @Time : 2023/2/26-9:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 假设有 n 台超级洗衣机放在同一排上。开始的时候，每台洗衣机内可能有一定量的衣服，也可能是空的。

在每一步操作中，你可以选择任意 m (1 <= m <= n) 台洗衣机，与此同时将每台洗衣机的一件衣服送到相邻的一台洗衣机。

给定一个整数数组 machines 代表从左至右每台洗衣机中的衣物数量，请给出能让所有洗衣机中剩下的衣物的数量相等的 最少的操作步数 。如果不能使每台洗衣机中衣物的数量相等，则返回 -1 。

 

示例 1：

输入：machines = [1,0,5]
输出：3
解释：
第一步:    1     0 <-- 5    =>    1     1     4
第二步:    1 <-- 1 <-- 4    =>    2     1     3
第三步:    2     1 <-- 3    =>    2     2     2
示例 2：

输入：machines = [0,3,0]
输出：2
解释：
第一步:    0 <-- 3     0    =>    1     2     0
第二步:    1     2 --> 0    =>    1     1     1
示例 3：

输入：machines = [0,2,0]
输出：-1
解释：
不可能让所有三个洗衣机同时剩下相同数量的衣物。
 

提示：

n == machines.length
1 <= n <= 104
0 <= machines[i] <= 105

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/super-washing-machines
 */
class Solution {
public:
    /*
     * 可以类比水流，在任意两个位置之间，放置一个滤网，滤网左边第一个位置记为i
     * 每1秒，有1升的水可以从高的那边流入另一边
     * 至于左边和右边是哪一个位置的水流过来 不必关心
     * 因为，假如是i的左边水更多
     * 选择一个位置j < i, 然后将[j, i]上的水都往右流动1个位置
     * 效果就是j这个地方的水少了1，其它位置的水量不变
     * 也就是说向右边流入1升的水，由哪一个位置来流都可以，那么当然是选则还高于avg的来流即可
     *
     * 每个位置水量一样多，那么左右两边必然水量相等
     * 左边的水量应该等于 avg * num_left，此时右边的水量必然等于 sum - avg * num_left = avg * num_right
     * 需要的时间为: t1 = abs(现有水量 - 理论水量),也就是abs(sum_left - avg * num_left)
     *
     * 但是还有2种特殊情况
     * 如果某个位置的水量很多，水量记为max_val，如果左边流出，优先流出该位置的水
     * 左右两边平衡，平衡时间为t1，该位置还剩余的水为 max_val - t1
     * 如果 max_val - t1 > avg，要让左边还需要变为相等，它还要往内部低的地方流;
     * 从高往低流，一次只能流1升，剩下还要流的时间是 max_val - t1 - avg
     * 整体的时间为 t2 = t1 + max_val - t1 - avg = max_val - t1
     *
     * 或者某个位置水很少，水量记为min_val，如果左边流入，优先流入该位置，平衡时间为t1
     * 低洼点，可以由左右两边同时流入，一次可以注入2升，t1的时间可以流入 2 * t1 升水
     * 该位置还需要的水为 avg - (2 * t1 + min_val)，如果 avg - (2 * t1 + min_val) > 0,它还要等内部的水注入
     * 剩下还要流的时间是 (avg - (2 * t1 + min_val)) / 2
     * 总时间就是 t2 = (avg - (2 * t1 + min_val)) / 2 + t1
     *
     * 最终状态需要的时间就取决于t1，或者存在t2的情况下，取决于max(t1, t2);
     */
    int findMinMoves(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), n = nums.size();
        if(sum % n != 0) return -1;
        int res = 0, avg = sum / n, max_val = nums[0], min_val = nums[0];
        for(int i = 0, sum = 0; i < n; i++){
            int num = nums[i];
            max_val = max(max_val, num), min_val = min(min_val, num);
            sum += num;
            int diff = sum - avg * (i + 1) ; // 计算 现有水量 - 理论水量
            if(diff > 0 && max_val - diff > avg)  // 左边流出 且存在一个高点需要继续向外流的情况
                res = max(res, max_val - avg);
            if(diff < 0 && min_val - 2 * diff < avg) // 左边流入，且存在一个低洼点还需要被注入
                res = max(res, (avg - (min_val - 2 * diff)) / 2 - diff);
            res = max(res, abs(diff));
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}