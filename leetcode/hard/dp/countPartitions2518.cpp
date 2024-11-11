/**
 * @Time : 2022/12/26-4:16 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 总的分组方式有total种。所有元素的和为sum, 第1,2组的和分别为s1,s2
     * 如果 s1 < k，不满足条件
     * 如果 s2 < k，当然也不满足条件
     * 所以满足条件的分组方法为 total - cnt{s1 < k} - cnt{s2 < k}
     * （s1和s2是对称的）
     * 但是如果有s1 < k and s2 < k的情况存在，上述减法就存在重复
     * 因此先排除s1 < k and s2 < k存在的情形，也就是 sum < 2k时，直接返回0
     *
     * dp[i][j]：截止nums[i - 1], s1 < j的分配方案数
     * 初始状态：除了dp[0][0] = 0以外的所有dp[0][j] = 1
     * 意义为：一个元素都不拿的时候，和为0。因此和小于0的取法不存在，和小于任意正数的取法就是1
     */
    int countPartitions(vector<int>& nums, int k) {
        int mod = 1e9 + 7, n = nums.size();
        long sum = accumulate(nums.begin(), nums.end(), 0l);
        if(sum < 2 * k) return 0;
        vector<vector<long>> dp(n + 1, vector(k + 1, 0l));
        dp[0].assign(k + 1, 1l);
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            int num = nums[i - 1];
            for(int j = 0; j <= k; j++){
                dp[i][j] = dp[i - 1][j];
                if(j - num >= 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - num]) % mod;
            }
        }
        long total = 1l;
        for(int i = 0; i < n; i++)
            total = (2 * total) % mod;
        return (int)((total - 2 * dp[n][k] + mod) % mod);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}