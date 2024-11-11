/**
 * @Time : 2024/10/13-12:46 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2014F
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, c, a[N];
vector<vector<int>> graph;
vector<vector<ll>> cache;
// flag = 1表示结点v要加固
ll dfs(int v, int f, int flag) {
    if(cache[v][flag] != LONG_LONG_MIN) return cache[v][flag];
    if(f != -1 && graph[v].size() == 1) return flag ? a[v] : 0;
    ll ans = flag ? a[v] : 0;
    for(int w : graph[v]) {
        if(w == f) continue;
        ll t1 = dfs(w, v, 1), t2 = dfs(w, v, 0);
        if(flag) t1 -= 2 * c; // 如果子结点要加固 并且当前结点是加固点 那么要从当前结点扣除c
        ans += max(t1, t2);
    }
    return cache[v][flag] = ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> c;
        graph.assign(n + 1, {}), cache = vector(n + 1, vector(2, LONG_LONG_MIN));
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        cout << max(dfs(1, -1, 1), dfs(1, -1, 0)) << "\n";
    }
};