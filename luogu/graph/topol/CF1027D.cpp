/**
 * @Time : 2025/4/27-9:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1027D 1700 图论 拓扑排序 dfs
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
int T, n, a[N], c[N], degree[N], marked[N];

void topol_bfs() {
    queue<int> queue;
    for(int i = 1; i <= n; i++)
        if(degree[i] == 0) queue.push(i);
    while (queue.size()) {
        int v = queue.front(), w = a[v]; queue.pop();
        marked[v] = 1;
        if(--degree[w] == 0) queue.push(w);
    }
}

int dfs(int v) {
    if(marked[v]) return INT_MAX;
    marked[v] = 1;
    return min(c[v], dfs(a[v]));
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> c[i];
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        degree[a[i]]++;
    }
    topol_bfs();
    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(marked[i]) continue;
        ans += dfs(i);
    }
    cout << ans << "\n";
}