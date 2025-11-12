/**
 * @Time : 2023/5/12-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 优先级限制下 topol排序的顺序可能会是dp的计算顺序
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5, mod = 80112002;
int n, m;
long long cnt[N];
vector<int> order;
vector<vector<int>> graph;

void topol_sort(unordered_set<int>& start, unordered_set<int>& end){
    vector<int> degree(n + 3, 0);
    for(int v = 1; v <= n; v++) {
        if(graph[v].empty()) end.insert(v);
        for(int w : graph[v])
            degree[w]++;
    }
    queue<int> queue;
    for(int v = 1; v <= n; v++) {
        if(degree[v] == 0)
            queue.push(v), start.insert(v);
    }
    while (queue.size()) {
        int v = queue.front(); queue.pop();
        order.push_back(v);
        for(int w : graph[v])
            if(--degree[w] == 0) queue.push(w);
    }
}

void relax(int v) {
    for(int w : graph[v])
        cnt[w] = (cnt[w] + cnt[v]) % mod;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    memset(cnt, 0, sizeof(cnt));
    cin >> n >> m;
    graph.assign(n + 3, {});
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        graph[a].push_back(b);
    }
    unordered_set<int> start, end;
    topol_sort(start, end);
    for(int v : start)
        cnt[v] = 1;
    for(int v : order)
        relax(v);
    long long ans = 0;
    for(int v : end)
        ans += cnt[v];
    cout << ans % mod << endl;
}