/**
 * @Time : 2024/6/16-11:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1324F 换根dp
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, color[N], val[N], ans[N];
vector<int> graph[N];

void dfs1(int v, int f) {
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v);
        if(val[w] > 0) val[v] += val[w];
    }
    if(color[v] == 0) val[v]--;
    else val[v]++;
}

void dfs2(int v, int f) {
    if(f == -1) ans[v] = val[v];
    else {
        // 计算父节点所在分支的影响
        int t = ans[f] - (val[v] < 0 ? 0 : val[v]);
        t = max(0, t);
        ans[v] = t + val[v];
    }
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs2(w, v);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> color[i];
    for(int i = 1, v, w; i <= n - 1; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    dfs1(1, -1), dfs2(1, -1);
    for(int i = 1; i <= n; i++)
        cout << ans[i] << " ";
};