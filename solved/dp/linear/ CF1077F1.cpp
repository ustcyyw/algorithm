/**
 * @Time : 2024/4/23-1:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * dp[i][j] 以第i个元素结尾 且拿了j个物品的最大和
  * 第i个物品拿了 就允许 i-1,i-2,...,i-k上取物品
  * dp[i][j] = max{dp[i-1][j-1], dp[i-2][j-1] ... dp[i-k][j-1]} + nums[i]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205;
int n, k, m, nums[N];

void solve() {
    vector<vector<ll>> dp(n + 1, vector(m + 1, -1ll));
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        if(i < k) dp[i][0] = 0; // 由于连续k个必须选一个 因此可以一个不拿的区间 截止到k-1
        if(i <= k) dp[i][1] = nums[i]; // 同样 必须在k及k之前选1个
        for(int j = max(2, m - n + i); j <= min(m, i); j++) {
            for(int l = max(0, i - k); l < i; l++) {
                if(dp[l][j - 1] != -1)
                    dp[i][j] = max(dp[i][j], dp[l][j - 1] + nums[i]);
            }
        }
    }
    ll ans = -1;
    for(int i = n - k + 1; i <= n; i++)
        ans = max(ans, dp[i][m]);
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};