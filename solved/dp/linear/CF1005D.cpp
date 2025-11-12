/**
 * @Time : 2024/11/19-8:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1005D 动态规划 前缀和 1500
 */
/*
  * 以i结尾最多的次数 当前段不被3整除 dp[i-1]
  * 当前段能被3整除 找最短的一段进行切割
  * 计算最短的一段切割 可以使用前缀和 并且求同余的思路
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, dp[N] = {0};
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    T = 1;
    while(T--) {
        cin >> s;
        n = s.size();
        s = '.' + s;
        vector<int> pre(3, -1);
        pre[0] = 0;
        for(int i = 1, sum = 0; i <= n; i++) {
            sum += s[i] - '0';
            int mod = sum % 3;
            dp[i] = dp[i - 1];
            if(pre[mod] != -1) dp[i] = max(dp[i], dp[pre[mod]] + 1);
            pre[mod] = i;
        }
        cout << dp[n];
    }
};