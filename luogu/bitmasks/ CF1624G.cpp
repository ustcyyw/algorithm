/**
 * @Time : 2024/7/25-2:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1624G 位运算 试填法 深度优先搜索
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, marked[N], cnt = 0;
vector<vector<vector<int>>> graph;

void dfs(int s, int v) {
    cnt++;
    marked[v] = 1;
    for(auto& edge : graph[v]) {
        if(marked[edge[0]] || (edge[1] | s) != s) continue;
        dfs(s, edge[0]);
    }
}

void solve() {
    int base = (1 << 30) - 1;
    for(int i = 29; i >= 0; i--) {
        int s = base ^ (1 << i);
        fill(marked, marked + n + 1, 0), cnt = 0;
        dfs(s, 1);
        if(cnt == n) base ^= 1 << i;
    }
    cout << base << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        for(int i = 1, a, b, w; i <= m; i++) {
            cin >> a >> b >> w;
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        solve();
    }
};