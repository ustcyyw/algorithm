/**
 * @Time : 2024/9/25-9:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1907E
 */
/*
  * a + b + c = n
  * ds(a) + ds(b) + ds(c) = ds(n)
  * 结论 a、b、c每个数位上的数字之和刚好等于n的数位上的数字
  * 于是每一位的分配方法就是将n分为3个自然数 每一位之间都是独立分配
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, ways[11];
string n;

int init = []() -> int {
    vector<vector<int>> dp(4, vector(10, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= 3; i++) {
        for(int j = 0; j <= 9; j++) {
            for(int k = 0; k <= j; k++)
                dp[i][j] += dp[i - 1][j - k];
        }
    }
    for(int i = 0; i <= 9; i++)
        ways[i] = dp[3][i];
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        ll ans = 1;
        for(char c : n)
            ans *= ways[c - '0'];
        cout << ans << "\n";
    }
};