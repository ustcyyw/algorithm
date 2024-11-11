/**
 * @Time : 2024/6/30-4:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1851E 拓扑排序
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, k, cost[N], degree[N], ans[N];
vector<vector<int>> graph;

void solve() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        ans[v] = min(cost[v], ans[v]);
        for(int w : graph[v]) {
            degree[w]--, ans[w] += ans[v];
            if(degree[w] == 0) queue.push(w);
        }
    }
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        graph.assign(n + 1, {});
        fill(degree + 1, degree + n + 1, 0), fill(ans + 1, ans + n + 1, 0);
        for(int i = 1; i <= n; i++)
            cin >> cost[i];
        for(int i = 1, p; i <= k; i++) {
            cin >> p;
            cost[p] = 0;
        }
        for(int i = 1, m; i <= n; i++) {
            cin >> m;
            if(m == 0) ans[i] = cost[i];
            for(int j = 1, p; j <= m; j++) {
                cin >> p;
                graph[p].push_back(i), degree[i]++;
            }
        }
        solve();
    }
};