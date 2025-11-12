/**
 * @Time : 2025/5/29-21:03
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2114E 1449 前缀和 dfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 998244353;
ll T, n, a[N], ans[N];
vector<vector<int>> graph;

void dfs(int v, int f, int depth, ll pre0, ll pre1, ll sum0, ll sum1) {
    if(depth % 2 == 1) sum1 += a[v], sum0 -= a[v];
    else sum1 -= a[v], sum0 += a[v];
    ans[v] = depth % 2 == 1 ? sum1 + pre0 : sum0 + pre1;
    pre0 = max(pre0, sum0), pre1 = max(pre1, sum1);
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v, depth + 1, pre0, pre1, sum0, sum1);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1, 1, 0, 0, 0, 0);
        for(int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << "\n";
    }
}