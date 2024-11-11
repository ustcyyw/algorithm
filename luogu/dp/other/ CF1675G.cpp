/**
 * @Time : 2024/7/31-9:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1675G 动态规划
 */
/*
  * 在操作的过程中 如果有某个盆中的饼为负数 不影响结果 只要保证最终某个盆中饼都非负
  * 因为将a[i]中移动到a[j]中，a[i]为负，但是又从a[k]移动到a[i]中 等价于直接从a[k]移动到a[j]
  * 但是可以将问题简化为所有饼都只来源于相邻的盆
  *
  * n m 的数据量比较小 不像贪心 如果考虑动态规划
  * 第一个维度肯定是下标i
  * 由于要求数组非增 所以序列最后一个元素大小很重要 第二个维度考虑第i个盆放了k张饼
  * 第三个维度 考虑截止第i个盆 一共放了j个饼，这样结合第二个维度k 截止i-1个盆放的饼的数量就确定了，为j - k
  *
  * dp[i][j][k]: 截止第i个盆 已经放了j个饼 并且在第i个盆要放k个饼
  * dp[i][j][k] = min{dp[i-1][j-k][l] + abs(sum[i] - j)}
  * 第一项中l的取值范围是[k,m] 保证非递增
  * 第二项是因为 所有的操作都考虑向相邻位置取或者放，因此截止i位置原本总共有sum[i]个饼
  * 现在共有j个饼 就需要从相邻位置拿/放 abs(sum[i] - j) 个饼 因为位置相邻 所以代价就是饼的个数
  * 计算dp[i][j][k]，给定ijk的情况下 转移方程中有l需要枚举
  * dp[i][j][k] = min{dp[i-1][j-k][l], for l in [k,m]} + abs(sum[i] - j)
  * 随着k的减小，l也单调减小 因此可以预处理dp[i][j]的后缀最小值val[i][j] 这样在计算中可以直接使用
  *
  * 边界条件 dp[0][0][i] = 0
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, arr[255], sum[255];

void solve() {
    vector<vector<vector<int>>> dp(n + 1, vector(m + 1, vector(m + 1, N)));
    vector<vector<vector<int>>> val(n + 1, vector(m + 1, vector(m + 2, N)));
    for(int i = 0; i <= m; i++)
        val[0][0][i] = dp[0][0][i] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= m; j++) {
            for(int k = 0; k <= j; k++) { // i盆放的饼 不能超过截止i盆一共放的数量
                dp[i][j][k] = val[i - 1][j - k][k] + abs(sum[i] - j);
            }
        }
        for(int j = 0; j <= m; j++) {
            for(int k = j; k >= 0; k--)
                val[i][j][k] = min(val[i][j][k + 1], dp[i][j][k]);
        }
    }
    int ans = INT_MAX;
    for(int i = 0; i <= m; i++)
        ans = min(ans, dp[n][m][i]);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> arr[i];
        sum[i] = sum[i - 1] + arr[i];
    }
    solve();
};