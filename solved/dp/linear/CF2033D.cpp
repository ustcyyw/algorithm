/**
 * @Time : 2024/11/29-10:25 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2033D 1300 动态规划 前缀和 hash表
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
ll T, n, sum[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        map<ll, int> map;
        vector<int> dp(n + 1, 0);
        map[0] = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            sum[i] = sum[i - 1] + num;
            dp[i] = max(dp[i - 1], map.count(sum[i]) ? dp[map[sum[i]]] + 1: 0);
            map[sum[i]] = i;
        }
        cout << dp[n] << "\n";
    };
};