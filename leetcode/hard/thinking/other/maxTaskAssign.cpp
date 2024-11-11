/**
 * @Time : 2022/8/28-1:14 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你 n 个任务和 m 个工人。每个任务需要一定的力量值才能完成，需要的力量值保存在下标从 0 开始的整数数组 tasks 中，第 i 个任务需要 tasks[i] 的力量才能完成。每个工人的力量值保存在下标从 0 开始的整数数组 workers 中，第 j 个工人的力量值为 workers[j] 。每个工人只能完成 一个 任务，且力量值需要 大于等于 该任务的力量要求值（即 workers[j] >= tasks[i] ）。

除此以外，你还有 pills 个神奇药丸，可以给 一个工人的力量值 增加 strength 。你可以决定给哪些工人使用药丸，但每个工人 最多 只能使用 一片 药丸。

给你下标从 0 开始的整数数组tasks 和 workers 以及两个整数 pills 和 strength ，请你返回 最多 有多少个任务可以被完成。

 

示例 1：

输入：tasks = [3,2,1], workers = [0,3,3], pills = 1, strength = 1
输出：3
解释：
我们可以按照如下方案安排药丸：
- 给 0 号工人药丸。
- 0 号工人完成任务 2（0 + 1 >= 1）
- 1 号工人完成任务 1（3 >= 2）
- 2 号工人完成任务 0（3 >= 3）
示例 2：

输入：tasks = [5,4], workers = [0,0,0], pills = 1, strength = 5
输出：1
解释：
我们可以按照如下方案安排药丸：
- 给 0 号工人药丸。
- 0 号工人完成任务 0（0 + 5 >= 5）
示例 3：

输入：tasks = [10,15,30], workers = [0,10,10,10,10], pills = 3, strength = 10
输出：2
解释：
我们可以按照如下方案安排药丸：
- 给 0 号和 1 号工人药丸。
- 0 号工人完成任务 0（0 + 10 >= 10）
- 1 号工人完成任务 1（10 + 10 >= 15）
示例 4：

输入：tasks = [5,9,8,5,9], workers = [1,6,4,2,6], pills = 1, strength = 5
输出：3
解释：
我们可以按照如下方案安排药丸：
- 给 2 号工人药丸。
- 1 号工人完成任务 0（6 >= 5）
- 2 号工人完成任务 2（4 + 5 >= 8）
- 4 号工人完成任务 3（6 >= 5）
 

提示：

n == tasks.length
m == workers.length
1 <= n, m <= 5 * 104
0 <= pills <= m
0 <= tasks[i], workers[j], strength <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/maximum-number-of-tasks-you-can-assign
 */
class Solution {
public:
    /**
     * 如果可以完成k个任务，那么一定可以完成k-1个任务
     * 是否可以完成k+1个任务?这就需要额外的尝试
     * 这里存在单调性，且题目问最多完成的任务是多少
     * 因此可以对完成的任务数进行二分
     *
     * 假设要判断是否可以完成k个任务，肯定首选最简单的k个任务和最厉害的k个人
     * 就要求挑选出来的这k个人和任务，每个人都能完成与之对应的任务
     *
     * 朴素的想法之一：最强的人去做最难的任务，这样才能不浪费
     * 如果有一个人做不到，就应该给他吃药?
     * 可是会出现弱一点的人吃药来解决难一点的问题，强一点的人不吃药去解决稍弱的问题这样的组合
     * 可能会比让强者直接吃药更好
     * 如 s = 2, p = 1
     * t ： 4 5
     * w ： 3 4
     * 如果让w[1]直接吃药，4 + 2 > 5，解决了t[1]，但是t[0]无法解决 只能完成1个任务
     * 让w[0]吃药 3 + 2 >= 5，解决了t[1]，然后让w[1]去解决t[0]，能完成两个任务
     *
     * 于是另一种想法：让最弱的人去解决最简单的任务
     * 如果最弱的人解决不了最简单的任务，那么必须让他吃药，否则直接就判断无法完成全部k个任务了
     * 让这个人吃药之后，让他去解决最简单的任务显然不划算，应该让他去解决他能解决的任务中最难的一个
     * 由于人的能力一直从小往大计算，因此可解决的问题（小于worker能力+strength）也单调增大
     * 因此可以用队列来存储所有还没解决且当前的worker可以解决的问题
     * (因为涉及解决他能解决的最难任务，即队尾元素，因此要使用双端队列)
     */
    int maxTaskAssign(vector<int>& tasks, vector<int>& workers, int pills, int strength) {
        sort(tasks.begin(), tasks.end());
        sort(workers.begin(), workers.end());
        int lo = 0, hi = min(tasks.size(), workers.size());
        while (lo < hi){
            int mid = (lo + hi + 1) >> 1;
            if(check(tasks, workers, pills, strength, mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(vector<int>& tasks, vector<int>& workers, int pills, int s, int k){
        deque<int> queue;
        int n = workers.size();
        for(int i = 0, j = n - k; j < n; j++){
            while (i < k && tasks[i] <= workers[j] + s)
                queue.push_back(tasks[i++]);
            if(queue.empty()) return false; // 没有当前这个工人可以完成的工作了，直接判定完成不了k个工作
            if(workers[j] >= queue.front()) queue.pop_front();
            else if(pills > 0){
                pills--;
                queue.pop_back();
            } else return false;
        }
        return true;
    }
};

int main(){
    Solution s;
    vector<int> t = {10,15,30}, w = {0,10,10,10,10};
    s.maxTaskAssign(t, w, 3, 10);
    cout << 0 << endl;
}