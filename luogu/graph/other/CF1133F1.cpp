/**
 * @Time : 2024/5/7-9:31 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 生成树的度数最大 找相邻结点
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 3e5 + 5;
int n, m, root, md, marked[N] = {0};
vector<vector<int>> edge;
vector<int> graph[N];

void solve() {
    root = -1, md = 0;
    for(int i = 1; i <= n; i++) {
        if(graph[i].size() > md) {
            md = graph[i].size();
            root = i;
        }
    }
    queue<int> queue;
    marked[root] = 1, queue.push(root);
    while(queue.size()) {
        int v = queue.front();
        for(int w : graph[v]) {
            if(!marked[w]) {
                marked[w] = 1, queue.push(w);
                edge.push_back({v, w});
            }
        }
        queue.pop();
    }
    for(auto& e : edge) {
        cout << e[0] << " " << e[1] << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v;
        graph[v].push_back(u), graph[u].push_back(v);
    }
    solve();
};