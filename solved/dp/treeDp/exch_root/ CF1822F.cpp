/**
 * @Time : 2024/5/28-11:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1822F 换根dp
 */
 /*
  * d1,d2记录到子结点的最大深度，s1，s2记录相应最大深度是走哪一个子结点得出的
  * 以便于换根时确定新的根的最远距离
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, d1[N], d2[N], s1[N], s2[N];
ll ans, k, c;
vector<vector<int>> graph;

void dfs1(int v, int f) {
    d1[v] = d2[v] = 0;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        if(d1[w] + 1 >= d1[v]) {
            d2[v] = d1[v], s2[v] = s1[v];
            d1[v] = d1[w] + 1, s1[v] = w;
        } else if(d1[w] + 1 > d2[v])
            d2[v] = d1[w] + 1, s2[v] = w;
    }
}

void dfs2(int v, int f, int dis, int cnt) {
    ans = max(ans, k * max(dis, d1[v]) - cnt * c);
    for(int w : graph[v]) {
        if(w == f) continue;
        int t = s1[v] == w ? d2[v] : d1[v]; // 除了w以外的其它树枝的最远距离 可能会成为以w为根的最远距离
        dfs2(w, v, max(dis, t) + 1, cnt + 1);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> c;
        ans = 0;
        graph.assign(n + 1, {});
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(1, -1);
        dfs2(1, -1, 0, 0);
        cout << ans << "\n";
    }
};