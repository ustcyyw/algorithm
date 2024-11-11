/**
 * @Time : 2024/1/24-3:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 举具体的例子看一下 分割变换的影响
  * 操作后的变化仅限于 字符串轮转 从某个位置开头 遍历一次 依旧能得到原字符串
  *
  * 一次变换 会让字符串变成b，也可能原本是b变成非b字符串 因此有两类状态
  * dp[i][0]: 经过i次操作 得到非b字符串的方案数
  * dp[i][1]: 经过i次操作 得到b字符串的方案数
  * 也是通过具体例子看
  * dp[i][0]可以由dp[i-1][0]和dp[i-1][1]转移过来 只是可选的分割点数量不一样 具体计算
  * dp[i][1]也是
  *
  * 如果k很大 还可以使用矩阵快速幂
  */
#include<bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
string a, b;
int k;

void solve() {
    string temp = a + a;
    int n = a.size(), c1 = 0;
    for(int i = 0; i < n; i++)
        if(temp.substr(i, n) == b) c1++;
    int c2 = n - c1, c3 = c1 - 1, c4 = c2 - 1;
    vector<vector<long long>> dp(k + 1, vector(2, 0ll));
    if(a == b) dp[0][1] = 1;
    else dp[0][0] = 1;
    for(int i = 1; i <= k; i++) {
        dp[i][0] = (dp[i - 1][1] * c2 + dp[i - 1][0] * c4) % mod;
        dp[i][1] = (dp[i - 1][0] * c1 + dp[i - 1][1] * c3) % mod;
    }
    cout << dp[k][1] << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> a >> b;
    cin >> k;
    solve();
}