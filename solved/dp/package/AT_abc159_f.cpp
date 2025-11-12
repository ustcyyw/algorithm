/**
 * @Time : 2023/8/25-3:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 枚举右端点i 计算出该右端点所有的子区间中满足和为j的子序列数 记为dp[i][j]
 * 如果子序列不取该右端点 dp[i][j] += dp[i - 1][j]
 * 截止上一个位置 和为j的所有子序列 不管他们左端点在哪，右端点现在为i 依旧可以满足条件
 * 如果子序列取该右端点 dp[i][j] += dp[i - 1][j - arr[i]]
 * 截止上一个位置 和为j - arr[i]的所有子序列 不管他们左端点在哪 现在在子序列中添加arr[i]就满足条件
 * 当然 只有 t = j - arr[i] >= 0 才有这一项
 * 但是还要注意 t = 0 时，除了 [0, i - 1]上的i个空子序列和arr[i]构成满足条件的子序列
 * 还有arr[i]本身也是一个满足条件的子序列 因此 if(t == 0) dp[i][j]++
 *
 *
 * 因为求的是所有 f(L,R) 之和，枚举R，所以最终要将所有 dp[i][s] 求和
 * 但是左端点L要进行考虑 比如子序列是  ai,aj,ak
 * 在枚举R的时候 [k,n-1]上的点都可以为右端点，这里每一个右端点都可以取[0,i-1]上的点为左端点
 * 使得子区间[...ai,..,aj,...,ak...]的子序列 ai,aj,ak都符合题意
 * 因而在求 dp[i][s] 之和，每一个右端点 这个子序列都应该贡献 i
 * 这就需要 dp[i - 1][0] = i, 这样这个子序列对dp[i][ai],dp[j][ai + aj],dp[k][ai+aj+ak]的贡献才是i
 *
 * 另外一个角度 从dp的定义出发 dp[i - 1][0] 以i-1为右端点的所有子区间
 * 共有i个 [a0...ai-1], [a1 ... ai-1],...[ai-1]
 * 每一个子区间中和为0的子序列有且仅有一个 就是空序列 因此 dp[i-1][0] = i
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 3005;
int n, s, arr[N], mod = 998244353;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> s;
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    vector<vector<long long>> dp(n, vector(s + 1, 0ll));
    dp[0][0] = 1;
    if (arr[0] <= s) dp[0][arr[0]] = 1;
    long long res = dp[0][s];
    for(int i = 1; i < n; i++) {
        dp[i][0] = i + 1;
        for(int j = 1; j <= s; j++) {
            int t = j - arr[i];
            dp[i][j] = (dp[i - 1][j] + (t >= 0 ? dp[i - 1][t] : 0)) % mod;
            if(t == 0) dp[i][j] = (dp[i][j] + 1) % mod;
        }
        res = (res + dp[i][s]) % mod;
    }
    cout << res << endl;
}