/**
 * @Time : 2024/7/20-8:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1611E2 树型dp
 */
/*
 * dfs(v): 要挡住所需的结点数目，-1表示挡不住
 * 如果有一个枝条上的阻碍点早于或者等于根到达此结点 那肯定能挡住 并且使用一个结点即可
 * 如果没有一个纸条上阻碍点早于或者等于根到达此结点
 *      有枝条返回-1 那就直接返回-1
 *      没有枝条返回-1 那就累加 因为靠这个点阻挡不了 就只能靠后续结点分别阻挡
 *
 *  简单版本 CF1611E1 只需要改下输出格式即可
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, obs[N], depth[N], near[N];
vector<vector<int>> graph;

void dfs1(int v, int f, int d) {
    depth[v] = d;
    near[v] = obs[v] ? 0 : INT_MAX;
    for(int w : graph[v]) {
        if(w == f) continue;
        dfs1(w, v, d + 1);
        if(near[w] != INT_MAX)
            near[v] = min(near[v], near[w] + 1);
    }
}

int dfs(int v, int f) {
    if(near[v] <= depth[v]) return 1;
    if(graph[v].size() == 1 && f != -1) return -1;
    int cnt = 0;
    for(int w : graph[v]) {
        if(w == f) continue;
        int temp = dfs(w, v);
        if(temp == -1) return -1;
        cnt += temp;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        graph.assign(n + 1, {});
        fill(obs, obs + n + 1, 0);
        for(int i = 1, node; i <= m; i++) {
            cin >> node;
            obs[node] = 1;
        }
        for(int i = 1, v, w; i < n; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(1, -1, 0);
        cout << dfs(1, -1) << "\n";
    }
};