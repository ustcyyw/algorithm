/**
 * @Time : 2024/12/5-4:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3336 动态规划 状态数量实际不多用map刷表
 */
 /*
  * dp[i][j][k]: 截止i位置 序列1的gcd为j，序列2的gcd为k的数量
1. num 不放入任何一个子序列 dp[i-1][j][k]
2. num 放入序列1，dp[i][num][k]++, 前置位置 gcd(pre, num) = j
3. num 放入序列2，dp[i][j][num]++, 前置位置 gcd(pre, num) = k
  但实际上算序列的公约数并不多，所以使用hashmap存实际存在的状态 从前往后刷表
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;

class Solution {
public:
    int get_gcd(int i, int num) {
        return i == 0 ? num : gcd(i, num); // 向空序列中放入num，序列的公约数变为num
    }

    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        unordered_map<int, unordered_map<int, ll>> pre, cur;
        pre[0][0] = 1; // 0表示对应的序列还是个空序列
        for(int num : nums) {
            cur.clear();
            for(auto& p1 : pre) {
                int i = p1.first, g1 = get_gcd(i, num);
                for(auto& p2 : p1.second) {
                    int j = p2.first, g2 = get_gcd(j, num);
                    ll cnt = p2.second;
                    cur[i][j] = (cur[i][j] + cnt) % mod;
                    cur[g1][j] = (cur[g1][j] + cnt) % mod;
                    cur[i][g2] = (cur[i][g2] + cnt) % mod;
                }
            }
            swap(cur, pre);
        }
        ll ans = 0;
        for(int i = 1; i <= 200; i++)
            ans = (pre[i][i] + ans) % mod;
        return ans;
    }
};
