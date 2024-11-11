/**
 * @Time : 2023/12/6-3:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/*
 * 数据范围4e4 + 5，此范围内经过计算只有499个回文数字
 * dp[i][j] 拼接出i 最大可以用的数是pal[j]的方案数
 * 1.不取当前pal[j] dp[i][j - 1]
 * 2.要取当前pal[j], 那么前面要拼接的和为i - pal[j],
 * 并且已经使用了pal[j]，那么也允许拼前面的数时使用pal[j]，因此前置状态是dp[i - pal[j]][j]
 *
 * 也可以视为 完全背包问题
 * dp[i][j]: 截止第i个元素，拼接不超过j的方案数
 * dp[i][j] = dp[i-1][j] + dp[i][j - pal[j]]
 */
const int N = 4e4 + 5, mod = 1e9 + 7;
int T, m;
vector<int> pal;
vector<vector<long long>> dp;

bool check(int num) {
    string str = to_string(num);
    for(int i = 0, j = str.size() - 1; i < j; i++, j--)
        if(str[i] != str[j]) return false;
    return true;
}

int init = []() -> int {
    for(int i = 1; i < N; i++)
        if(check(i)) pal.push_back(i);
    m = pal.size();
    dp = vector(N, vector(m, 0ll));
    for(int j = 0; j < m; j++)
        dp[0][j] = 1;
    for(int i = 1; i < N; i++)
        dp[i][0] = 1;
    for(int i = 1; i < N; i++) {
        for(int j = 1; j < m; j++) {
            dp[i][j] = dp[i][j - 1];
            if(i - pal[j] >= 0) dp[i][j] += dp[i - pal[j]][j];
            dp[i][j] %= mod;
        }
    }
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int i = 1, a; i <= T; i++) {
        cin >> a;
        cout << dp[a][m - 1] << endl;
    }
}