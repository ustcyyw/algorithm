/**
 * @Time : 2022/8/22-7:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的二维整数数组 tires ，其中 tires[i] = [fi, ri] 表示第 i 种轮胎如果连续使用，第 x 圈需要耗时 fi * ri(x-1) 秒。

比方说，如果 fi = 3 且 ri = 2 ，且一直使用这种类型的同一条轮胎，那么该轮胎完成第 1 圈赛道耗时 3 秒，完成第 2 圈耗时 3 * 2 = 6 秒，完成第 3 圈耗时 3 * 22 = 12 秒，依次类推。
同时给你一个整数 changeTime 和一个整数 numLaps 。

比赛总共包含 numLaps 圈，你可以选择 任意 一种轮胎开始比赛。每一种轮胎都有 无数条 。每一圈后，你可以选择耗费 changeTime 秒 换成 任意一种轮胎（也可以换成当前种类的新轮胎）。

请你返回完成比赛需要耗费的 最少 时间。

 

示例 1：

输入：tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
输出：21
解释：
第 1 圈：使用轮胎 0 ，耗时 2 秒。
第 2 圈：继续使用轮胎 0 ，耗时 2 * 3 = 6 秒。
第 3 圈：耗费 5 秒换一条新的轮胎 0 ，然后耗时 2 秒完成这一圈。
第 4 圈：继续使用轮胎 0 ，耗时 2 * 3 = 6 秒。
总耗时 = 2 + 6 + 5 + 2 + 6 = 21 秒。
完成比赛的最少时间为 21 秒。
示例 2：

输入：tires = [[1,10],[2,2],[3,4]], changeTime = 6, numLaps = 5
输出：25
解释：
第 1 圈：使用轮胎 1 ，耗时 2 秒。
第 2 圈：继续使用轮胎 1 ，耗时 2 * 2 = 4 秒。
第 3 圈：耗时 6 秒换一条新的轮胎 1 ，然后耗时 2 秒完成这一圈。
第 4 圈：继续使用轮胎 1 ，耗时 2 * 2 = 4 秒。
第 5 圈：耗时 6 秒换成轮胎 0 ，然后耗时 1 秒完成这一圈。
总耗时 = 2 + 4 + 6 + 2 + 4 + 6 + 1 = 25 秒。
完成比赛的最少时间为 25 秒。
 

提示：

1 <= tires.length <= 105
tires[i].length == 2
1 <= fi, changeTime <= 105
2 <= ri <= 105
1 <= numLaps <= 1000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/minimum-time-to-finish-the-race
 */
class Solution {
public:
    /**
     * 对于每一个轮胎 如果 换胎时间 + 跑一圈的时间 <= 连续跑第k圈时，第k圈的用时
     * 就应该更换轮胎 如果取 changeTime 最大为10^5, fi最小为1, ri最小为2
     * 那么得到极限情况下，最多连跑k圈的不等式为 2 ^ (k - 1) <= 10^5  ->  k = log(10^5) + 1 <= 18
     *
     * 如果固定轮胎的连续使用圈数为一个值j
     * 那么所有轮胎中，连续跑j圈所有的时间有且仅有一个确定的最小值
     * 也就是说，如果轮胎要跑固定圈数，从时间最优的角度来讲，就应该使用特定的轮胎
     * 可以预处理出来所有指定圈数下不允许换轮胎的最短用时 con[j]（continuous[j]）
     *
     * 定义状态dp[i]的最小时间 dp[i] = min{dp[i - j] + con[j], j范围[0,k]} + changeTime
     * 注意边界条件：dp[0] = 0，表示一圈都不跑，耗时为0
     * 以及 一次性不换胎的跑圈的情况
     * for(int i = 1; i <= min(numLaps, k); i++)
            dp[i] = con[i];
     *
     * 执行用时：540 ms, 在所有 C++ 提交中击败了51.24%的用户
     * 内存消耗：174.9 MB, 在所有 C++ 提交中击败了33.89%的用户
     */
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        int k = 18, max_val = 0x7FFFFFFF;
        vector<int> con = vector(k + 1, max_val);
        for(auto& tire : tires){
            int f = tire[0], r = tire[1];
            for(int i = 1, total = 0; i <= k; i++){
                long time = f * pow(r, i - 1);
                if(time > changeTime + f) break; // 换胎时间 + 跑一圈的时间 <= 连续跑第k圈时，就应该换轮胎
                total += time;
                con[i] = min(con[i], total);
            }
        }
        while (con[k] == max_val) k--; // k取了理论上限，但实际可能取不到18，将k的范围精确
        vector<int> dp = vector(numLaps + 1, max_val);
        dp[0] = 0;
        for(int i = 1; i <= min(numLaps, k); i++) // 一次性不换胎的跑圈的情况
            dp[i] = con[i];
        for(int i = 1; i <= numLaps; i++){
            for(int j = 1; j <= k && i - j > 0; j++) // i - j != 0，因为从起点一次性不换胎跑的情况已经当作边界条件单独求了
                dp[i] = min(dp[i], dp[i - j] + con[j] + changeTime);
        }
        return dp[numLaps];
    }
};

int main(){
    Solution s;
    vector<vector<int>> t = {{2,3},{3,4}};
    s.minimumFinishTime(t, 5, 2);
    cout << 0 << endl;
}