/**
 * @Time : 2023/10/16-2:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 选的物品价值v 共有m个 重量为w
可以取满m个物品的情况

dp[i][0] = max{dp[i-1][0]}

dp[i][w] = max{dp[i-1][w], dp[i-1][0] + v}
= max{dp[i-1][w] - v, dp[i-1][0]} + v

dp[i][2w] = max{dp[i-1][2w], dp[i-1][w] + v, dp[i-1][0] + 2v}
= max{dp[i-1][2w] - 2v, dp[i-1][w] - v, dp[i-1][0]} + 2v

dp[i][3w] = max{dp[i-1][3w], dp[i-1][2w] + v, dp[i-1][w] + 2v, dp[i-1][0] + 3v}
=  max{dp[i-1][3w] - 3v, dp[i-1][2w] - 2v, dp[i-1][w] - v, dp[i-1][0]} + 3v

dp[i][4w] = max{dp[i-1][4w] - 4v, dp[i-1][3w] - 3v, dp[i-1][2w] - 2v, dp[i-1][w] - v} + 4v

 可以单调队列优化
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 105;
int n, W, nums[N][3];

long long solve() {
    vector<vector<int>> dp(n + 1, vector(W + 1, 0));
    for(int i = 1; i <= n; i++) {
        int v = nums[i][0], w = nums[i][1], cnt = nums[i][2];
        unordered_map<int, deque<pair<int, int>>> map;
        for(int j = 0; j <= W; j++) {
            int mod = j % w, t = j / w;
            if(!map.count(mod)) map[mod] = {};
            deque<pair<int, int>>& queue = map[mod];
            int temp = dp[i - 1][j] - t * v;
            while(!queue.empty() && temp >= queue.back().second)
                queue.pop_back();
            queue.emplace_back(t, temp);
            while(t - queue.front().first > cnt)
                queue.pop_front();
            dp[i][j] = queue.front().second + t * v;
        }
    }
    return dp[n][W];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> W;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i][0] >> nums[i][1] >> nums[i][2];
    }
    cout << solve() << endl;
}