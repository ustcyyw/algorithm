/**
 * @Time : 2024/1/16-7:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 拆位思考 优先看高位是不是1 与运算为1 需要所有分组的该位得是1
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 55;
int n, k;
long long nums[51], sum[52];
// 查看分组[lo,hi]能不能num的数位要求 num的位是1要求子数组和的该位也是1
bool check(long long num, int lo, int hi) {
    long long s = sum[hi + 1] - sum[lo];
    for(int i = N; i >= 0; i--) {
        long long t = 1ll << i;
        if((num & t) && !(s & t)) return false;
    }
    return true;
}
// 查看是否能拆分为k组 并且每个组的数位要求都满足num
bool split(long long num) {
    vector<vector<bool>> dp(n + 1, vector(k + 1, false));
    dp[0][0] = true;
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= i; j++) {
            if(check(num, j - 1, i - 1)) {
                for(int t = 1; t <= k; t++)
                    dp[i][t] = dp[i][t] || dp[j - 1][t - 1];
            }
        }
    }
    return dp[n][k];
}

void solve() {
    long long res = 0;
    for(int i = N; i >= 0; i--) { // 从高位尝试看 是否能在该位分配1
        long long t = res + (1ll << i);
        if(split(t)) res = t;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        cin >> nums[i];
        sum[i + 1] = sum[i] + nums[i];
    }
    solve();
}