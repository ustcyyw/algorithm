/**
 * @Time : 2024/3/21-10:30 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, cnt[N], val[N], ans;
vector<vector<int>> graph;

void dfs1(int v, int f) {
    cnt[v] = 1;
    for(int w : graph[v]) {
        if(w != f) {
            dfs1(w, v);
            cnt[v] += cnt[w], val[v] += val[w];
        }
    }
    val[v] += cnt[v];
}

void dfs2(int v, int f) {
    if(f != -1) {
        // 除了第一次放置f这个点获取的值n，f的值还有两类，一类是从v获得的，一类是从其它儿子结点o获得的
        ll vfo = val[f] - val[v];
        // f如果作为v的儿子 其子树结点个数为 n - cnt[v]
        ll cf = n - cnt[v];
        val[v] = vfo + cf + val[v] - cnt[v];
        ans = max(ans, val[v]);
    }
    for(int w : graph[v]) {
        if(w != f) dfs2(w, v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    graph.assign(n + 1, {});
    for(int i = 1, v, w; i < n; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1);
    ans = val[1];
    dfs2(1, -1);
    cout << ans << "\n";
};