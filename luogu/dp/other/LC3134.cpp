/**
 * @Time : 2025/1/5-9:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3134 动态规划 求特定方案
 */
 /*
  * 涉及到区间到覆盖情况 按右端点排序
  * 那么枚举区间的时候就可以用二分直接确定有哪些区间是可以放在其前面的
  *
  * dp[i][j]: 截止到i元素 最多拿j个的最大值
  * 拿i元素 dp[pre][j-1] + v[i]
  * 不拿i元素 dp[i][j - 1], dp[i - 1][j]
  *
  * 注意求字典序最小的方案 就把转移过程中涉及到取的序号都放进去比较
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        vector<vector<int>> arr;
        arr.push_back({0, 0, 0, -1});
        for(int i = 0; i < n; i++) {
            vector<int> temp = intervals[i];
            temp.push_back(i);
            arr.push_back(temp);
        }
        sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
            return a[1] < b[1];
        });
        vector<vector<ll>> dp(n + 1, vector(5, 0ll));
        vector<vector<vector<int>>> infos(n + 1, vector(5, vector(0, 0)));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= 4; j++) {
                int pre = find(arr, i);
                ll pick = dp[pre][j - 1] + arr[i][2];
                vector<int> temp = infos[pre][j - 1];
                temp.push_back(arr[i][3]);
                sort(temp.begin(), temp.end());
                infos[i][j] = temp, dp[i][j] = pick;
                change(dp, infos, i, j, i - 1, j);
                change(dp, infos, i, j, i, j - 1);
            }
        }
        return infos[n][4];
    }

    void change(vector<vector<ll>>& dp, vector<vector<vector<int>>>& infos,
                int i1, int j1, int i2, int j2) {
        if(dp[i2][j2] > dp[i1][j1] ||
           (dp[i2][j2] == dp[i1][j1] && infos[i2][j2] < infos[i1][j1])) {
            dp[i1][j1] = dp[i2][j2];
            infos[i1][j1] = infos[i2][j2];
        }
    }

    // 找到idx左边的第一个右边界小于idx的区间
    int find(vector<vector<int>>& arr, int idx) {
        int lo = 0, hi = idx - 1, l = arr[idx][0];
        while(lo < hi) {
            int mid = (lo + hi + 1) >> 1, right = arr[mid][1];
            if(right < l) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }
};