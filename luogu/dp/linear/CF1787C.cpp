/**
 * @Time : 2024/3/11-3:03 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 贪心+dp
  * 贪心：要让式子最小 相乘项中其中一个因子大，就想让另外一个因子小
  * 因此猜想 将ai拆分为 xi + yi时，要在满足限制条件的情况下，让其中一个尽可能的小
  * 另外一个打的则后续和小的因子相乘
  *
  * 确定了拆分方式之后 剩下的就是线性dp
  * dp[i][0]：当前位置选择小因子与前面相乘
  * dp[i][1]：当前位置选择大因子与前面相乘
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n, s, nums[N];
ll f[N][2], dp[N][2] = {0};

void solve() {
    f[1][0] = f[1][1] = nums[1];
    f[n][0] = f[n][1] = nums[n];
    for(int i = 2; i <= n - 1; i++) {
        int num = nums[i], t1, t2;
        if(num <= s) t1 = 0, t2 = num;
        else t1 = s, t2 = num - s;
        if(t1 > t2) swap(t1, t2);
        f[i][0] = t1, f[i][1] = t2;
    }
    for(int i = 2; i <= n; i++) {
        dp[i][0] = min(dp[i-1][0] + f[i-1][1] * f[i][0], dp[i-1][1] + f[i-1][0] * f[i][0]);
        dp[i][1] = min(dp[i-1][0] + f[i-1][1] * f[i][1], dp[i-1][1] + f[i-1][0] * f[i][1]);
    }
    cout << min(dp[n][0], dp[n][1]) << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> s;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};