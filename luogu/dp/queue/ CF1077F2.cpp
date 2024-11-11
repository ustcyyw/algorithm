/**
 * @Time : 2024/4/23-3:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 和cf1077f1比起来 只有数据范围变了 可以使用单调队列优化
  * 参照着cf1077f1的代码改写即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
int n, k, m, nums[N];

ll pick(deque<pair<int, ll>>& dq, int i) {
    while(!dq.empty() && dq.front().first < i - k)
        dq.pop_front();
    return dq.empty() ? -1 : dq.front().second;
}

void add(deque<pair<int, ll>>& dq, int i, ll val) {
    while(!dq.empty() && dq.back().second <= val)
        dq.pop_back();
    dq.push_back({i, val});
}

void solve() {
    vector<vector<ll>> dp(n + 1, vector(m + 1, -1ll));
    vector<deque<pair<int, ll>>> queue(m + 1);
    dp[0][0] = 0, add(queue[0], 0, 0);
    ll ans = -1;
    for(int i = 1; i <= n; i++) {
        if(i < k) dp[i][0] = 0;
        if(i <= k) dp[i][1] = nums[i];
        for(int j = max(2, m - n + i); j <= min(m, i); j++) {
            ll t = pick(queue[j - 1], i);
            if(t != -1) dp[i][j] = t + nums[i];
        }
        for(int j = 0; j <= min(m, i); j++)
            if(dp[i][j] != -1) add(queue[j], i, dp[i][j]);
        if(i >= n - k + 1) ans = max(ans, dp[i][m]);
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k >> m;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};