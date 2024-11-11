/**
 * @Time : 2024/4/15-9:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 因为所有人对卡牌喜好的感知是一致的 也就是拿到相同张数的喜好牌 欢乐值h[t]是相同的
 * 每个人喜好什么数字不重要，重要的是拿到了几张喜欢的牌
 * 因此 可以将牌按数字分组 将人按喜欢的数字的牌分组
 * 并且每一组牌都应该分给喜欢这个数字的人 因为每张牌都是要分出去的 理由如下：
 * 1.如果这些人都不够分 再给不喜欢这个数字的人 没有意义
 * 2.如果这些人分完后 还剩 那么这种数字分给其它人 但不影响其它人的欢乐值
 * 因此每组数字都只用考虑如何分给喜欢它的哪些人，相互之间是独立的，也就是说等价的
 * 那么就不关注数字具体是多少 只关注它出现了几次
 * dp[i][j]: 对于某一组牌 截止第i个人，分配了j张牌的最大欢乐值
 * 进行预处理 可以假定喜欢某组牌的人数就是n个，并且所有牌都可以分配
 * 这样针对具体某种牌 一共有cc张牌 分给fc人 答案就是 dp[fc][min(cc, k * fc)]
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 505, M = 1e5 + 5;
int n, k, cc[M], fc[M], h[11], dp[N][N * 10];

void solve() {
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j <= i * k; j++) {
            dp[i][j] = dp[i - 1][j];
            for(int t = 1; t <= k && t <= j; t++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - t] + h[t]);
            }
        }
    }
    // 每一组牌都是地位等价且独立的 因此枚举所有出现的牌组
    int ans = 0;
    for(int f = 1; f < M; f++) {
        if(cc[f] && fc[f])
            ans += dp[fc[f]][min(cc[f], k * fc[f])];
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1, num; i <= n * k; i++) {
        cin >> num;
        cc[num]++; // 卡牌按其数字分组
    }
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        fc[num]++; // 玩家按喜好的卡牌统计人数
    }
    for(int i = 1; i <= k; i++)
        cin >> h[i];
    solve();
};