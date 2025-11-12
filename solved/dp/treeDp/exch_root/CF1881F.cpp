/**
 * @Time : 2024/9/23-10:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1881F 换根dp
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, k, ans, red[N], d1[N], son1[N], d2[N], son2[N];
vector<vector<int>> graph;
// 计算子从子结点获得的最大距离及次大距离
void dfs1(int v, int f) {
    if(red[v]) d1[v] = son1[v] = 0;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        if(d1[w] == -1) continue;
        if(d1[w] + 1 >= d1[v]) {
            d2[v] = d1[v], son2[v] = son1[v];
            d1[v] = d1[w] + 1, son1[v] = w;
        } else if(d1[w] + 1 > d2[v])
            d2[v] = d1[w] + 1, son2[v] = w;
    }
}
// 换根的时候维护从父亲结点得到的最大距离
void dfs2(int v, int f, int dis) {
    if(red[v]) dis = max(dis, 0);
    ans = min(ans, max(dis, d1[v]));
    for(int w : graph[v]) {
        if(w == f) continue;
        int td1 = son1[v] == w ? d2[v] : d1[v];
        if(td1 == -1) td1 = INT_MIN;
        int td2 = dis >= 0 ? dis : INT_MIN;
        dfs2(w, v, max(td2, td1) + 1);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        ans = INT_MAX;
        graph.assign(n + 1, {}), fill(red, red + n + 1, 0);
        fill(d1, d1 + n + 1, -1), fill(d2, d2 + n + 1, -1);
        fill(son1, son1 + n + 1, -1), fill(son2, son2 + n + 1, -1);
        for(int i = 1, node; i <= k; i++) {
            cin >> node;
            red[node] = 1;
        }
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(1, -1);
        dfs2(1, -1, -1);
        cout << ans << "\n";
    }
};