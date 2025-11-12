/**
 * @Time : 2023/12/7-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 注意 可以重复经过结点任意次 那就变成了一个简单贪心题了
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, m, marked[N];
vector<vector<int>> graph;

void solve() {
    priority_queue<int, vector<int>, greater<>> pq;
    pq.push(1), marked[1] = 1;
    while(pq.size()) {
        int v = pq.top();
        pq.pop();
        for(int w : graph[v]) {
            if(!marked[w])
                pq.push(w), marked[w] = 1;
        }
        cout << v << " ";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(marked, 0, sizeof(marked));
    cin >> n >> m;
    graph.assign(n + 1, {});
    for(int i = 0, v, w; i < m; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
}