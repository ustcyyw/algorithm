/**
 * @Time : 2022/9/16-10:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个整数数组 jobs ，其中 jobs[i] 是完成第 i 项工作要花费的时间。

请你将这些工作分配给 k 位工人。所有工作都应该分配给工人，且每项工作只能分配给一位工人。工人的 工作时间 是完成分配给他们的所有工作花费时间的总和。请你设计一套最佳的工作分配方案，使工人的 最大工作时间 得以 最小化 。

返回分配方案中尽可能 最小 的 最大工作时间 。

 

示例 1：

输入：jobs = [3,2,3], k = 3
输出：3
解释：给每位工人分配一项工作，最大工作时间是 3 。
示例 2：

输入：jobs = [1,2,4,7,8], k = 2
输出：11
解释：按下述方式分配工作：
1 号工人：1、2、8（工作时间 = 1 + 2 + 8 = 11）
2 号工人：4、7（工作时间 = 4 + 7 = 11）
最大工作时间是 11 。
 

提示：

1 <= k <= jobs.length <= 12
1 <= jobs[i] <= 107

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-minimum-time-to-finish-all-jobs
 */
class Solution {
public:
    int n, u;
    int minimumTimeRequired(vector<int>& jobs, int k) {
        n = jobs.size(), u = (1 << n) - 1;
        vector<int> times(u + 1, 0);
        for(int s = u; s; s = (s - 1) & u){
            for(int i = 0; i < n; i++)
                if((1 << i) & s) times[s] += jobs[i];
        }
        int lo = *max_element(jobs.begin(), jobs.end());
        int hi = accumulate(jobs.begin(), jobs.end(), 0);
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(minWorkNum(jobs, times, mid) <= k) hi = mid;
            else lo = mid + 1;
        }
        return lo;
    }
    // dp[s]表示状态s最少需要多少工人
    int minWorkNum(vector<int>& jobs, vector<int>& times, int time){
        vector<int> dp(u + 1, INT_MAX / 2);
        dp[0] = 0;
        for(int i = 1; i <= u; i++){
            for(int s = i; s; s = (s - 1) & i){
                // 将工作s分给同一个人，如果没有超最大时间，就可以进行这样的分配
                if(times[s] <= time)
                    dp[i] = min(dp[i], dp[i - s] + 1);
            }
        }
        return dp[u];
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,2,3};
    s.minimumTimeRequired(arr, 3);
    cout << 0 << endl;
}