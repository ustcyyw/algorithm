/**
 * @Time : 2022/9/30-5:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个任务数组 tasks ，其中 tasks[i] = [actuali, minimumi] ：

actuali 是完成第 i 个任务 需要耗费 的实际能量。
minimumi 是开始第 i 个任务前需要达到的最低能量。
比方说，如果任务为 [10, 12] 且你当前的能量为 11 ，那么你不能开始这个任务。如果你当前的能量为 13 ，你可以完成这个任务，且完成它后剩余能量为 3 。

你可以按照 任意顺序 完成任务。

请你返回完成所有任务的 最少 初始能量。

 

示例 1：

输入：tasks = [[1,2],[2,4],[4,8]]
输出：8
解释：
一开始有 8 能量，我们按照如下顺序完成任务：
    - 完成第 3 个任务，剩余能量为 8 - 4 = 4 。
    - 完成第 2 个任务，剩余能量为 4 - 2 = 2 。
    - 完成第 1 个任务，剩余能量为 2 - 1 = 1 。
注意到尽管我们有能量剩余，但是如果一开始只有 7 能量是不能完成所有任务的，因为我们无法开始第 3 个任务。
示例 2：

输入：tasks = [[1,3],[2,4],[10,11],[10,12],[8,9]]
输出：32
解释：
一开始有 32 能量，我们按照如下顺序完成任务：
    - 完成第 1 个任务，剩余能量为 32 - 1 = 31 。
    - 完成第 2 个任务，剩余能量为 31 - 2 = 29 。
    - 完成第 3 个任务，剩余能量为 29 - 10 = 19 。
    - 完成第 4 个任务，剩余能量为 19 - 10 = 9 。
    - 完成第 5 个任务，剩余能量为 9 - 8 = 1 。
示例 3：

输入：tasks = [[1,7],[2,8],[3,9],[4,10],[5,11],[6,12]]
输出：27
解释：
一开始有 27 能量，我们按照如下顺序完成任务：
    - 完成第 5 个任务，剩余能量为 27 - 5 = 22 。
    - 完成第 2 个任务，剩余能量为 22 - 2 = 20 。
    - 完成第 3 个任务，剩余能量为 20 - 3 = 17 。
    - 完成第 1 个任务，剩余能量为 17 - 1 = 16 。
    - 完成第 4 个任务，剩余能量为 16 - 4 = 12 。
    - 完成第 6 个任务，剩余能量为 12 - 6 = 6 。
 

提示：

1 <= tasks.length <= 105
1 <= actual​i <= minimumi <= 104

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-initial-energy-to-finish-tasks
 */
class Solution {
public:
    /**
     * 假设完成任务的执行顺序是(a1,w1),(a2,w2)...(ai,wi)...(an,wn)
     * 执行任务需要的能量为 e
     * 那么一定有
     * e >= w1
     * e - a1 >= w2
     * e - a1 - a2 >= w3
     * ...
     * e - (a1 + ... + an-1) >= wn
     * 均成立，也就是对于任意的i,均有 e >= (a1 + ... + ai-1) + wi 成立
     * 要让e最小，就是让 max{(a1 + ... + ai-1) + wi}最小
     *
     * 考虑任务i和i+1的顺利执行条件
     * e >= (a1 + ... + a[i-1]) + wi = t1
     * e >= (a1 + ... + ai) + w[i+1] = t2
     * 如果交换两个任务的执行顺序，先执行i+1，再执行i，顺利执行的条件就变为
     * e >= (a1 + ... + a[i - 1]) + w[i + 1] = t3
     * e >= (a1 + ... + a[i - 1] + a[i + 1]) + wi = t4
     * 只考虑交换这两个任务的顺序时，不影响其它不等式
     * 因此交换之后可以让e不变或者变小的可能就是
     * max{t3, t4} <= max{t1, t2}
     * t2 - t3 = ai > 0, t2 > t3
     * 因此 max{t3,t4} = t3的话，不等式 max{t3, t4} = t3 < t2 <= max{t1, t2}一定成立
     * 不等式就等价于 t4 <= max{t1, t2}
     * 又因为 t4 > t1，因此要使不等式成立，就要求 t4 <= t2
     * 也就是  (a1 + ... + a[i - 1] + a[i + 1]) + wi <= (a1 + ... + ai) + w[i+1]
     * a[i+1] - w[i+1] <= ai - wi
     *
     * 于是可以得出结论，只要 a[i+1] - w[i+1] <= ai - wi
     * 就应该交换两个任务的执行顺序，可以让e变小或者至少不变，因此应该将task按a-w排序
     */
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(),
             [](auto & a, auto  & b) -> bool {return (a[0] - a[1]) < (b[0] - b[1]);});
        int res = 0, sum = 0;
        for(auto & task : tasks){
            int diff = res - sum - task[1];
            if(diff < 0) res += -diff;
            sum += task[0];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}