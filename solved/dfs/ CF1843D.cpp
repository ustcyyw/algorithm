/**
 * @Time : 2024/9/6-5:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1843D
 */
 /*
  * 就是计算叶子结点数目 普通dfs
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q;
ll cnt[N];
vector<vector<int>> graph;

void dfs(int v, int f) {
    if(graph[v].size() == 1 && f != -1) {
        cnt[v] = 1;
        return;
    }
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs(w, v);
        cnt[v] += cnt[w];
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        fill(cnt, cnt + n + 1, 0);
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs(1, -1);
        cin >> q;
        for(int i = 1, v, w; i <= q; i++) {
            cin >> v >> w;
            cout << cnt[v] * cnt[w] << "\n";
        }
    }
};