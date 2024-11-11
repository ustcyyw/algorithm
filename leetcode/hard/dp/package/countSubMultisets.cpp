/**
 * @Time : 2023/10/15-10:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛115 t4
 */
#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
class Solution {
public:
    /**
     * dp[i][j]：截止第i个元素，子序列的和为j的方案数
     * 其中第i个元素出现了cnt次，该元素值为a
     * dp[i][a-1] = dp[i-1][a-1]
     *
     * dp[i][a] = dp[i-1][a] + dp[i-1][0]
     * dp[i][a+1] = dp[i-1][a+1] + dp[i-1][1]
     *
     * dp[i][j-a] = dp[i-1][j-a] + dp[i-1][j-2a] + ... + dp[i-1][max(j - (cnt+1) * a, 0)]
     * dp[i][j] = dp[i-1][j] + dp[i-1][j-a] + dp[i-1][j-2a] + ... dp[i-1][max(j - cnt * a, 0)]
     * 也就是说 如果 j >= (cnt + 1) * a
     * dp[i][j-a] = dp[i-1][j-a] + dp[i-1][j-2a] + ... + dp[i-1][j - (cnt+1) * a]
     * dp[i][j] = dp[i-1][j] + dp[i-1][j-a] + ... dp[i-1][j - cnt * a]
     *          = dp[i-1][j] + dp[i][j-a] - dp[i-1][j - (cnt+1) * a]
     * 否则 dp[i][j] = dp[i-1][j] + dp[i][j-a]
     *
     * 注意0的特判
     */
    int countSubMultisets(vector<int>& nums, int l, int r) {
        unordered_map<int, int> map;
        for(int num : nums)
            map[num]++;
        vector<pair<int, int>> infos;
        for(auto& p : map)
            infos.emplace_back(p);
        int n = infos.size();
        vector<vector<long>> dp(n + 1, vector(r + 1, 0l));
        dp[0][0] = 1;
        for(int i = 1; i <= n; i++) {
            int a = infos[i-1].first, cnt = infos[i-1].second;
            for(int j = 0; j <= r; j++) {
                if(a == 0) {
                    dp[i][j] = (cnt + 1) * dp[i - 1][j] % mod;
                    continue;
                }
                dp[i][j] = dp[i - 1][j];
                if(j - a >= 0) dp[i][j] += dp[i][j-a];
                if(j >= (cnt + 1) * a) dp[i][j] -= dp[i-1][j - (cnt + 1) * a];
                dp[i][j] = dp[i][j] % mod + mod;
            }
        }
        long res = 0;
        for(int i = l; i <= r; i++)
            res = (res + dp[n][i]) % mod;
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {0,0,1,2,3};
    s.countSubMultisets(arr, 2, 3);
    cout << 0 << endl;
}