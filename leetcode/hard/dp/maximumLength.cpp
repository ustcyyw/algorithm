/**
 * @Time : 2024/6/9-9:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛132 t4 动态规划
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 根据题目描述 允许有k个位置 前后两个元素不同
     * 也就是说子序列中最多允许有k+1段 每一段中的元素数值相同
     * （当然了相邻两段也可以元素相同 这样就更加不会超过限制条件了）
     *
     * dp[j][i]:以第i个位置为结尾 且已经分了j段的最大子序列长度
     * 1.接在上一个相同元素的后面 dp[j][pre] + 1
     * 2.nums[i]是一个新的数 它接在另外一个数nums[k]的后面 那么截止k 已经分了j-1段
     * 现在这个数就是第j段，前面也提到了nums[i]与nums[k]无所谓是否相同
     * max{dp[j-1][k]}, k属于[0,i-1] 这一项的维护记录前缀的最大值即可。
     */
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre(n, -1);
        vector<vector<int>> dp(k + 2, vector(n, 0));
        unordered_map<int, int> map, temp;
        for(int i = 0; i < n; i++) {
            int num = nums[i];
            dp[1][i] = ++map[num];
            if(temp.count(num)) pre[i] = temp[num];
            temp[num] = i;
        }
        for(int j = 2; j <= k + 1; j++) {
            for(int pm = 0, i = 0; i < n; i++) {
                dp[j][i] = pm + 1;
                if(pre[i] != -1) dp[j][i] = max(dp[j][i], dp[j][pre[i]] + 1);
                pm = max(pm, dp[j - 1][i]);
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++)
            ans = max(ans, dp[k + 1][i]);
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}