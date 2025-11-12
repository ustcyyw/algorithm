/**
 * @Time : 2025/4/24-10:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1027E 2100 动态规划 思维
 */
/*
  * 画几个例子可以发现 在忽略k的影响下
  * 第一行任意一种颜色安排，剩下的行只要遵守相邻行的颜色规则排布后
  * 列自动满足相邻列的颜色规则
  * 对于相邻行/列的颜色规则，行和列是对称的，只管行即可
  *
  * 有k的约束，所以要考虑一行中的最大连续颜色长度
  * 确定了第一行后，排列下面的行 要么"相同"，要么"取反色"
  * 会导致列也会出现连续的颜色，也要考虑一列中的最大连续颜色长度
  * maxCol * maxRow < k
  * 对于最大连续颜色长度，行和列是对称的，所以计算其中之一即可
  *
  * 用cnt[i]表示n*n的矩形中，一行中最大连续颜色为i的方案数
  * 选定了第一行的样式，这一行的最大连续颜色长度为i
  * 从一列的角度来看，就是将这第一行视为一个整体（颜色），考虑怎么安排这个整体
  * 如果列的最大连续颜色长度为j
  * 在 i * j < k 时，就能保证限制条件，方案数为 cnt[i] * cnt[j]
  */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 998244353;
int T, n, k;
ll g[N], dp[N][N]; // g[i]: 表示连续颜色的长度 <= i的可能方案数

// cal函数计算最大长度为limit的方案数 并且不考虑开头是什么颜色
ll cal(int limit) {
    dp[0][1] = 1;
    ll sum = 1;
    for (int i = 1; i < n; i++) {
        dp[i][1] = sum;
        for (int j = 2; j <= min(limit, i + 1); j++) {
            dp[i][j] = dp[i - 1][j - 1], sum = (sum + dp[i][j]) % mod;
        }
    }
    return sum % mod;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int len = 1; len <= n; len++)
        g[len] = cal(len);
    // 经过这个计算 g[i]就表示连续颜色最大长度为i的方案数
    for (int i = n; i >= 1; i--)
        g[i] = (g[i] - g[i - 1] + mod) % mod;
    ll ans = 0;
    for (int a = 1; a < min(k, n + 1); a++) {
        for (int b = 1; a * b < k && b <= n; b++)
            ans = (g[a] * g[b] % mod + ans) % mod;
    }
    // 因为计算第一行（第一列）的排列方案时 没有考虑是什么颜色开头，但是开头可以是黑/白两种颜色，因此答案*2
    cout << ans * 2 % mod << "\n";
}