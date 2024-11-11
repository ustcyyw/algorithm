/**
 * @Time : 2024/5/7-12:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * dp[i][j]: 截止第i个学生 且至多j只队伍的最大人数
  * dp[i][j]
  * = max{dp[t][j - 1] + (i - t), for nums[i] - nums[t + 1] <= 5}, dp[i - 1][j], dp[i][j - 1]
  * = max{dp[t][j - 1] - t + i, for nums[i] - nums[t + 1] <= 5}, dp[i - 1][j], dp[i][j - 1]
  * 单调队列优化
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5005;
int n, k, a[N], dp1[N][N];
deque<pair<int, int>> dq[N];

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    sort(a + 1, a + n + 1);
    vector<vector<int>> dp(n + 1, vector(k + 1, 0));
    dq[0].push_back({0, 0});
    for(int i = 1; i <= n; i++) {
        int num = a[i];
        for(int j = 0; j <= min(k, i); j++) {
            if(j >= 1) {
                deque<pair<int, int>> &q = dq[j - 1];
                while(!q.empty() && num - a[q.front().second + 1] > 5)
                    q.pop_front();
                if(q.empty()) dp[i][j] = max(1, dp[i - 1][j]);
                else dp[i][j] = max(q.front().first + i, dp[i - 1][j]);
                dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            }
            deque<pair<int, int>> &q = dq[j];
            while(!q.empty() && q.back().first <= dp[i][j] - i)
                q.pop_back();
            q.push_back({dp[i][j] - i, i});
        }
    }
    cout << dp[n][k];
};