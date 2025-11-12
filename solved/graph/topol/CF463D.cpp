/**
 * @Time : 2024/1/6-11:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * dp[i]: 以数字i为结尾的最长公共序列长度
 *
 * 对于数字i，公共子序列下一个数字是j的条件为：在k个序列中j都出现在i的右边
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1005;
int n, k, nums[5][N], cnt[N];

void solve() {
    vector<vector<int>> graph(n + 1);
    for(int i = 1; i <= n; i++) {
        memset(cnt, 0, sizeof(cnt));
        for(int j = 0; j < k; j++) {
            for(int t = n - 1; nums[j][t] != i; t--)
                cnt[nums[j][t]]++;
        }
        for(int j = 1; j <= n; j++)
            if(cnt[j] == k) graph[i].push_back(j);
    }
    vector<int> dp(n + 1, 1), degree(n + 1, 0);
    for(int v = 1; v <= n; v++) {
        for(int w : graph[v])
            degree[w]++;
    }
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    int res = 1;
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        for(int w : graph[v]) {
            if(--degree[w] == 0) queue.push(w);
            dp[w] = max(dp[w], dp[v] + 1);
            res = max(dp[w], res);
        }
    }
    cout << res << endl;
}

int main(){
    cin >> n >> k;
    for(int i = 0; i < k; i++) {
        for(int j = 0; j < n; j++)
            cin >> nums[i][j];
    }
    solve();
}