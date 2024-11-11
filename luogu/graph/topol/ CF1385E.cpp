/**
 * @Time : 2024/7/2-7:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1385E 拓扑排序
 */
 /*
  * 有无环 想到了拓扑排序
  * 只要在选定边的方向时 让拓扑序号小的指向大的 就不会出现环
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
ll T, n, m, degree[N], order[N], cnt;
vector<vector<int>> indEdges, ans;
vector<vector<int>> graph;

bool topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        cnt++;
        order[v] = cnt * N;
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
    return cnt == n;
}

bool solve() {
    if(!topol_bfs()) return false;
    for(auto& e : indEdges) {
        int v = e[0], w = e[1];
        if(order[v] > order[w]) ans.push_back({w, v});
        else ans.push_back({v, w});
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m;
        fill(degree + 1, degree + n + 1, 0), fill(order + 1, order + n + 1, -1);
        graph.assign(n + 1, {});
        indEdges = {}, ans = {}, cnt = 0;
        for(int i = 1, t, x, y; i <= m; i++) {
            cin >> t >> x >> y;
            if(t == 0) indEdges.push_back({x, y});
            else {
                ans.push_back({x, y});
                graph[x].push_back(y), degree[y]++;
            }
        }
        if(!solve()) cout << "NO\n";
        else {
            cout << "YES\n";
            for(auto& e : ans)
                cout << e[0] << " " << e[1] << "\n";
        }
    }
};