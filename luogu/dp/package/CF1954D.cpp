/**
 * @Time : 2024/4/13-11:22 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 按照分组规则
 * 如果某种颜色的球是绝对多的（它的数量 >= 其它球的数量），那么分组数就是该颜色球的数量
 * 否则，总是可以两种不同颜色的球在一个组，最多有一个组仅一个球 因此球总数是sum，分组数量就是(sum + 1) / 2
 * 可以发现 最大数量的球很重要 可以进行排序 这样就保证在遍历某个球时 其前面的球任选都不会成为数量最大球
 * 并且 n <= 5000，所有球的数量和 <= 5000。 背包dp不会超时
 * dp[i][j]：截止i个颜色为序列最后一个颜色，且球总数为j的序列数
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 5005, mod = 998244353;
ll T, n, color[N], dp[N][N] = {0};

void solve() {
    ll ans = 0;
    sort(color + 1, color + n + 1);
    dp[0][0] = 1;
    for(int i = 1, sum = 0; i <= n; i++) {
        int c = color[i];
        sum += c;
        for(int j = 0; j <= sum; j++) {
            dp[i][j] = dp[i - 1][j];
            if(j >= c) {
                // 以第i个颜色结尾的序列的贡献
                ll group = c >= j - c ? c : (j + 1) / 2;
                ans = (ans + group * dp[i - 1][j - c] % mod) % mod;
                dp[i][j] = (dp[i - 1][j - c] + dp[i][j]) % mod;
            }
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> color[i];
    solve();
};