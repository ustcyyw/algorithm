/**
 * @Time : 2024/8/2-3:08 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1741G bfs 状态压缩 动态规划
 */
/*
  * 最多6个朋友没有车 状态压缩的话 最多64种状态
  * len[i]:到达结点i的最短路径长度
  * infos[i][s] = 1: 到达结点i的最短路径长度的情况下，到达该结点可能的状态为s
  *
  * 先bfs查看以最短路到各点的状态 然后根据有车的人的情况进行动态规划
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, f, k, arr[N], len[N], u;
vector<vector<int>> graph, infos;
set<int> noCar;
map<int, vector<int>> mp; // 记录某个结点没有车的人的编号

void bfs() {
    queue<vector<int>> queue; // {node, status}
    queue.push({1, 0}), len[1] = 0; // 没有人的家在起点1
    int step = 0;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            vector<int>& temp = queue.front();
            int v = temp[0], s = temp[1];
            for(int w : graph[v]) {
                if(step + 1 > len[w]) continue;
                int ns = s;
                for(int j : mp[w])
                    ns |= 1 << (j - 1);
                len[w] = step + 1;
                if(infos[w][ns] != 1)
                    infos[w][ns] = 1, queue.push({w, ns});
            }
            queue.pop();
        }
        step++;
    }
}

void solve() {
    bfs();
    vector<vector<int>> dp(f + 1, vector(u, 0));
    dp[0][0] = 1;
    for(int i = 1; i <= f; i++) {
        if(noCar.count(i)) {
            dp[i] = dp[i - 1];
            continue;
        }
        int node = arr[i]; // 第i个人家所在的结点
        dp[i][0] = 1;
        for(int ps = 0; ps < u; ps++) {
            if(dp[i - 1][ps] == 0) continue;
            for(int s = 0; s < u; s++) {
                if(infos[node][s]) dp[i][s | ps] = 1;
            }
        }
    }
    int pp = 0;
    for(int s = 0; s < u; s++) {
        if(dp[f][s]) pp = max(pp, __builtin_popcount(s));
    }
    cout << k - pp << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {}), noCar = {}, mp = {};
        fill(len, len + n + 1, 1e9);
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cin >> f;
        for(int i = 1; i <= f; i++) {
            cin >> arr[i]; // arr[i]: 索引为i的人所在的结点
        }
        cin >> k;
        u = 1 << k;
        infos.assign(n + 1, vector(u, 0));
        for(int i = 1, j; i <= k; i++) {
            cin >> j;
            int node = arr[j];
            noCar.insert(j), mp[node].push_back(i);
        }
        solve();
    }
};