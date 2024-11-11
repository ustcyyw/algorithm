/**
 * @Time : 2024/4/1-8:10 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛127 t4
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7;
class Solution {
public:
    /*
     * 方法一 枚举子序列的最小差的绝对值 diff
     * 然后计算有多少个子序列的最小差绝对值为 diff
     * 定义
     * dp[i][j][0] : 以第i个元素结尾，选取了j个元素 并且元素之间差的绝对值还没有出现diff（都比diff大）
     * dp[i][j][1] : 以第i个元素结尾，选取了j个元素 并且元素之间差的绝对值出现diff（都比diff大）
     */
    ll dp[50][51][2];
    int n, k;
    vector<int> nums;
    int sumOfPowers(vector<int>& arr, int k) {
        n = arr.size(), this->k = k;
        this->nums = arr;
        sort(nums.begin(), nums.end());
        unordered_set<int> set;
        ll ans = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int diff = nums[j] - nums[i];
                if(set.count(diff)) continue;
                set.insert(diff);
                ans = (ans + count(diff)) % mod;
            }
        }
        return ans;
    }

    ll count(int diff) {
        ll cnt = 0;
        for(int i = 0; i < n; i++) {
            dp[i][1][0] = 1;
            for(int j = 2; j <= min(k, i + 1); j++) {
                dp[i][j][0] = dp[i][j][1] = 0;
                for(int p = max(0, j - 2); p < i; p++) {
                    int d = nums[i] - nums[p];
                    if(d == diff) dp[i][j][1] += dp[p][j - 1][0] + dp[p][j - 1][1];
                    if(d > diff) {
                        dp[i][j][1] += dp[p][j - 1][1];
                        dp[i][j][0] += dp[p][j - 1][0];
                    }
                }
                dp[i][j][1] %= mod, dp[i][j][0] %= mod;
            }
            cnt += dp[i][k][1];
        }
        return cnt * diff % mod;
    }

    /*
     * 方法二 考虑到 n = 50 可能出现的 元素差值 是离散的并且不多
     * 定义 dp[i][j][d]: 以第i个元素结尾，选取了j个数，且子序列 元素差的绝对值为d的子序列数量
     * 用map来存储差值维度的信息
     */
    int sumOfPowers2(vector<int>& nums, int k) {
        int n = nums.size(), mod = 1e9 + 7;
        sort(nums.begin(), nums.end());
        unordered_map<int, long long> dp[51][51];
        long long ans = 0;
        for(int i = 0; i < n; i++) {
            dp[i][1][INT_MAX] = 1;
            for(int j = 1; j <= min(k, i + 1); j++) {
                for(int p = max(0, j - 2); p < i; p++) {
                    for(auto& [d, cnt] : dp[p][j - 1]) {
                        int cd = min(d, nums[i] - nums[p]);
                        dp[i][j][cd] = (dp[i][j][cd] + dp[p][j - 1][d]) % mod;
                    }
                }
            }
            for(auto& [d, cnt] : dp[i][k])
                ans = (ans + cnt * d) % mod;
        }
        return ans;
    }
};