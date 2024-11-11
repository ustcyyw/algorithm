/**
 * @Time : 2023/4/17-12:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 你有一台电脑，它可以 同时 运行无数个任务。给你一个二维整数数组 tasks ，其中 tasks[i] = [starti, endi, durationi] 表示第 i 个任务需要在 闭区间 时间段 [starti, endi] 内运行 durationi 个整数时间点（但不需要连续）。

当电脑需要运行任务时，你可以打开电脑，如果空闲时，你可以将电脑关闭。

请你返回完成所有任务的情况下，电脑最少需要运行多少秒。

 

示例 1：

输入：tasks = [[2,3,1],[4,5,1],[1,5,2]]
输出：2
解释：
- 第一个任务在闭区间 [2, 2] 运行。
- 第二个任务在闭区间 [5, 5] 运行。
- 第三个任务在闭区间 [2, 2] 和 [5, 5] 运行。
电脑总共运行 2 个整数时间点。
示例 2：

输入：tasks = [[1,3,2],[2,5,3],[5,6,2]]
输出：4
解释：
- 第一个任务在闭区间 [2, 3] 运行
- 第二个任务在闭区间 [2, 3] 和 [5, 5] 运行。
- 第三个任务在闭区间 [5, 6] 运行。
电脑总共运行 4 个整数时间点。
 

提示：

1 <= tasks.length <= 2000
tasks[i].length == 3
1 <= starti, endi <= 2000
1 <= durationi <= endi - starti + 1

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/minimum-time-to-complete-all-tasks
 */
class Solution {
public:
    /*
     * 区间 可以想到对区间进行排序
     * 按区间右端点排序
     * 1.如果两个区间不相交，那么前一个区间取点，取在任何地方都可以
     * 2.区间相交，为了同一个时间运行多个任务，应该将时间点取在前一个区间的后缀
     * 因为 两个区间的交集 交集一定是前一个区间的后缀
     * 综合上述两种情况，进行取点时，都取区间的后缀。
     * 首先计算[start,end]上已经运行了多少个时间点，不足duration，再进行额外的取点
     * 从区间右边往左取，直到该任务运行时间得到满足。
     */

    /*
     * 暴力法 本题的时间轴 长度只有2000 可以直接使用数组来模拟时间轴
     */
    int findMinimumTime(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(),
             [](auto& a, auto& b) -> bool {return a[1] < b[1];});
        vector<bool> picked(2002, false);
        for(auto& task : tasks){
            int s = task[0], e = task[1], d = task[2], cnt = 0;
            for(int i = s; i <= e; i++)
                cnt += picked[i];
            if(cnt >= d) continue; // 当前区间时间点已经大于当前任务所需 直接跳过
            for(int i = e, t = d - cnt; t; i--){
                if(picked[i]) continue;
                picked[i] = true;
                t--;
            }
        }
        return accumulate(picked.begin(), picked.end(), 0);
    }

    /*
     * 求时间轴上某区间取了多少个点 是区间求和的操作
     * 而时间轴上取点，则是区间上的区间修改：
     * 将某个区间上的点一次全取上，以保证该任务得以完成，并且区间的右端点就是任务的end
     *
     * 于是可以使用线段树来优化
     */

};

int main(){
    Solution s;
    
    cout << 0 << endl;
}