/**
 * @Time : 2023/12/14-4:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 数位dp
 *
 * 18位的 数位的乘积 最多会有不到4e4个结果
 * 前置位的乘积 再乘单前选择的数字（最多10个数字） 最多也才4e5次计算
 *
 * 因为需要考虑最终乘积小于k，因此还需要一个状态mul表示截止i-1的数位乘积
 * 对于mul的记忆化 可以使用map
 */
#include<bits/stdc++.h>

typedef unsigned long long ull;
using namespace std;
ull N, K, n;
string s;
unordered_map<ull, ull> dp[20];
ull dfs(int i, bool limit, bool is_num, ull mul) {
    if (i == n) return mul <= K && is_num;
    if (!limit && is_num && dp[i].count(mul))
        return dp[i][mul];
    ull cnt = 0;
    if (!is_num) cnt += dfs(i + 1, false, false, 1);
    int down = is_num ? 0 : 1, up = limit ? s[i] - '0' : 9;
    for (int j = down; j <= up; j++) // 当前位的数字
        cnt += dfs(i + 1, limit && j == up, true, mul * j);
    if (!limit && is_num) dp[i][mul] = cnt;
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> N >> K;
    s = to_string(N), n = s.size();
    // 考虑第0位的数字选择时 前置乘积设为1 这样第0位选任何数字相乘都是它本身
    ull res = dfs(0, true, false, 1);
    cout << res << endl;
}