/**
 * @Time : 2024/12/16-1:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2044G1 图论 基环树 拓扑排序
 */
 /*
  * 找最长树枝
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, r[N], degree[N], cycle[N], dis[N];

void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(), w = r[v]; queue.pop();
        cycle[v] = 0;
        if(--degree[w] == 0) queue.push(w);
    }
}

int dfs(int v) {
    if(cycle[v]) return 1;
    if(dis[v] != 0) return dis[v];
    return dis[v] = 1 + dfs(r[v]);
}

void solve() {
    topol_bfs();
    int ans = 1;
    for(int i = 1; i <= n; i++) {
        ans = max(ans, dfs(i));
    }
    cout << ans + 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n;
        fill(degree, degree + n + 1, 0);
        fill(cycle, cycle + n + 1, 1);
        fill(dis, dis + n + 1, 0);
        for(int i = 1; i <= n; i++) {
            cin >> r[i];
            degree[r[i]]++;
        }
        solve();
    }
};