/**
 * @Time : 2023/10/15-9:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n, m, nums[N];

long mod(long num) {
    return ((num % 10) + 10) % 10;
}

long solve(int sign) {
    vector<vector<vector<long>>> dp(n, vector(n, vector(m + 1, -sign * (long)1e11)));
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            for(int k = i, sum = 0; k <= j; k++) {
                sum += nums[k];
                dp[i][j][1] = mod(sum);
            }
        }
    }
    if(m == 1) return dp[0][n - 1][1];
    for(int t = 2; t <= m; t++) {
        for(int i = 0; i < n; i++) {
            for(int l = t; i + l - 1 < n; l++) {
                int j = i + l - 1;
                for(int k = i; k <= j + 1 - t; k++) { // 两个部分[i,k]分为1份 [k + 1, j]份为t-1份
                    dp[i][j][t] = sign * max(sign * dp[i][j][t],
                                             sign * dp[i][k][1] * dp[k+1][j][t-1]);
                }
            }
        }
    }
    long res = dp[0][n-1][m];
    for(int sz = 2; sz <= n - m + 1; sz++) { // 枚举横跨头尾的情况
        long sum = nums[0];
        for(int i = n - sz + 1; i < n; i++)
            sum += nums[i];
        res = sign * max(sign * res, sign * mod(sum) * dp[1][n - sz][m - 1]);
        for(int i = n - sz + 2, j = 1; i < n; i++, j++) {
            sum = sum - nums[i - 1] + nums[j];
            res = sign * max(sign * res, sign * mod(sum) * dp[j + 1][i - 1][m - 1]);
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    cout << solve(-1) << endl;
    cout << solve(1) << endl;
}