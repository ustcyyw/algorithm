/**
 * @Time : 2024/7/25-7:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1650G bfs 广度优先
 */
/*
 * 到达某点再往回走1，再回到某点 这样的路径是无效的 至少相差了2的距离
 * 最短距离方案数 cnt1[], 次短距离cnt2[]
 * v-w边：v和w都已经走到过最短距离 才可能互相之间走出来次短距离
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, s, t, dis1[N];
ll cnt1[N], cnt2[N];
vector<vector<int>> graph;

void solve() {
    queue<int> queue;
    int step = 1;
    queue.push(s), cnt1[s] = 1, dis1[s] = 0;
    while(!queue.empty()) {
        int sz = queue.size();
        while(sz-- > 0) {
            int v = queue.front(); queue.pop();
            for(int w : graph[v]) {
                if(dis1[w] == -1 || step == dis1[w]) { // 第一次到该点 这是最短距离
                    if(cnt1[w] == 0 && (dis1[t] == -1 || step + 1 <= dis1[t] + 1))
                        queue.push(w); // 第一次访问此点时 添加到队列
                    dis1[w] = step;
                    cnt1[w] = (cnt1[w] + cnt1[v]) % mod;
                } else if(dis1[w] + 1 == step) { // 这是次短距离
                    if(cnt2[w] == 0 && (dis1[t] == -1 || step + 1 <= dis1[t] + 1))
                        queue.push(w); // 第一次访问此点次短距离 添加到队列
                    if(dis1[v] == step - 1) // v的最短距离走到w次短距离
                        cnt2[w] = (cnt2[w] + cnt1[v]) % mod;
                    if(dis1[v] + 1 == step - 1) // v的次短距离走到w次短距离
                        cnt2[w] = (cnt2[w] + cnt2[v]) % mod;
                }
            }
        }
        step++;
        if(dis1[t] != -1 && step > dis1[t] + 1) break;
    }
    cout << (cnt1[t] + cnt2[t]) % mod << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> s >> t;
        graph.assign(n + 1, {});
        fill(cnt1, cnt1 + n + 1, 0), fill(cnt2, cnt2 + n + 1, 0);
        fill(dis1, dis1 + n + 1, -1);
        for(int i = 1, a, b; i <= m; i++) {
            cin >> a >> b;
            graph[a].push_back(b), graph[b].push_back(a);
        }
        // 根据bfs访问的方式优化 在起点选择分支少的点走
        if(graph[s].size() > graph[t].size()) swap(s, t);
        solve();
    }
};