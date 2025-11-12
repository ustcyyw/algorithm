/**
 * @Time : 2025/1/5-9:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3413 思维 暴力枚举 二分
 */
 /*
  * 假如说 所选择的连续k个袋子 跨了多个有金币的区间
  * 最左边和最右边的金币值分别为cl, cr
  * 如果cl = cr 将区间向左移动 不影响值
  * 如果cl > cr 将区间向左移动 值增大
  * 如果cr < cr 将区间向右移动 值增大
  * 以上移动方式都可以持续到将其中一个区间完全移除时 或者完全涵盖
  * 因此最终答案 肯定是以刚好取了一个完整的金币区间为开头或者结尾的
  * 枚举这个完整的金币区间 借助前缀和、二分快速计算答案即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

class Solution {
public:
    map<int, int> ls, rs;
    vector<ll> sum;
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        int n = coins.size();
        sort(coins.begin(), coins.end());
        sum.assign(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            vector<int> coin = coins[i - 1];
            ll li = coin[0], ri = coin[1], ci = coin[2];
            sum[i] = sum[i - 1] + (ri - li + 1) * ci;
            ls[li] = i, rs[ri] = i;
        }
        ll ans = 0;
        for(int i = 1; i <= n; i++) {
            ans = max(ans, cal(coins, i, k));
        }
        return ans;
    }

    ll cal(vector<vector<int>>& coins, int i, int k) {
        vector<int> coin = coins[i - 1];
        int li = coin[0], ri = coin[1];
        // 找到右边最远能覆盖到的区间
        int right = li + k - 1;
        auto it = --ls.upper_bound(right);
        int lj = it->first, j1 = it->second, rj1 = coins[j1 - 1][1];
        ll temp1 = sum[j1 - 1] - sum[i - 1] + (ll)coins[j1 - 1][2] * (min(right, rj1) - lj + 1);
        // 找到左边最远能覆盖到的距离
        int left = ri - k + 1;
        it = rs.lower_bound(left);
        int rj = it->first, j2 = it->second, lj2 = coins[j2 - 1][0];
        ll temp2 = sum[i] - sum[j2] + (ll)coins[j2 - 1][2] * (rj - max(left, lj2) + 1);
        return max(temp1, temp2);
    }
};