/**
 * @Time : 2024/4/9-10:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 完全背包问题的变形
  * 如果求的是拿到总价值为x 最少需要拿多少个物品
  * 可以定义 dp[i][j]:截止第i类物品 总价值为j的最少物品数量
  * dp[i][j] = min{dp[i - 1][j], dp[i][j - ai] + 1} for j - ai >= 0
  * 但是题目问 恰好拿k个物品 能拿到的总价值可能有哪些
  * 因为 ai <= 1000, k <= 1000，所以总价值可取的区间上[1, 1e6]
  * 那么考虑总价值val是否可能时
  * 如果有dp[n][val] == k 刚好可以拿到
  * 如果有dp[n][val] > k 总数超过了k 不可能
  * 如果有dp[n][val] < k 最少只需要小于k个物品 但是刚好k个是否可能呢? 不好确定
  *
  * 但是可以对物品的总价值进行一个变形 假设物品最小价值为ma
  * 所有物品价值都先减去ma，作为当前价值来参与计算dp[i][j] 那么
  * 在dp[n][val] == k时，就相当于k个商品拿到的原本总价值是 val + k * ma
  * 在dp[n][val] > k时，相当于拿val + dp[n][val] * ma的价值，最少也 > k个
  * 在dp[n][val] < k时，就再拿相应的最小价值商品（价值为0）
  * 拿足到k个，现价值不变还是val 于是对应的原价val + k * ma就刚好通过k个商品拿到
  * 因此 dp[n][val] <= k，即代表了原价值val + k * ma可拿到
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1005;
int n, k, a[N], dp[N * N]; // dp进行滚动压缩

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    int ma = a[1];
    for(int i = 1; i <= n; i++)
        a[i] -= ma;
    // dp[i][j] = min{dp[i - 1][j], dp[i][j - ai] + 1} 滚动压缩
    fill(dp, dp + a[n] * k + 1, 1e9);
    dp[0] = 0;
    for(int i = 2; i <= n; i++) {
        for(int j = a[i]; j <= a[n] * k; j++)
            dp[j] = min(dp[j], dp[j - a[i]] + 1);
    }
    for(int val = 0; val <= a[n] * k; val++) {
        if(dp[val] <= k) cout << val + k * ma << " ";
    }
};