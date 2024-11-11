/**
 * @Time : 2024/1/16-9:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * dp[i][0]: i位置 一个数都不拿
 * dp[i][1]: i位置 拿了第1行的数
 * dp[i][2]: i位置 拿了第2行的数
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, arr1[N], arr2[N];
long long dp[N][3];

int main(){
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr1[i];
    for(int i = 1; i <= n; i++)
        cin >> arr2[i];
    for(int i = 1; i <= n; i++) {
        dp[i][0] = max({dp[i - 1][0], dp[i - 1][1], dp[i - 1][2]});
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][2]) + arr1[i];
        dp[i][2] = max(dp[i - 1][0], dp[i - 1][1]) + arr2[i];
    }
    cout << max({dp[n][0], dp[n][1], dp[n][2]}) << endl;
}