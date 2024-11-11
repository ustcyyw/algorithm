/**
 * @Time : 2024/5/30-7:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1850H
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, marked[N], ans = 1;
vector<vector<vector<int>>> graph;
map<int, ll> pos;

void dfs(int v) {
    if(ans == 0) return;
    marked[v] = 1;
    for(auto& e : graph[v]) {
        int w = e[0], d = e[1];
        ll wp = pos[v] + d;
        if(pos.count(w) && pos[w] != wp) {
            ans = 0;
            return;
        }
        if(marked[w]) continue;
        pos[w] = wp;
        dfs(w);
    }
}

void solve() {
    for(int i = 1; i <= n && ans == 1; i++) {
        if(marked[i]) continue;
        pos[i] = 0;
        dfs(i);
    }
    cout << (ans == 1 ? "YES" : "NO") << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        pos.clear();
        fill(marked, marked + n + 1, 0);
        ans = 1;
        graph.assign(n + 1, {});
        for(int i = 1, a, b, d; i <= m; i++) {
            cin >> a >> b >> d;
            graph[a].push_back({b, d}), graph[b].push_back({a, -d});
        }
        solve();
    }
};