/**
 * @Time : 2023/5/15-8:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 5e3 + 5;
int n, k, p, r, degree[N];
vector<vector<int>> graph;

int topol_sort(){
    for(int v = 1; v <= n + 1; v++) {
        for(int w : graph[v])
            degree[w]++;
    }
    int step = -1;
    queue<int> queue;
    queue.push(n + 1);
    while (queue.size()) {
        int sz = queue.size();
        for(int i = 0; i < sz; i++) {
            int v = queue.front(); queue.pop();
            if(v == k) return step;
            for(int w : graph[v])
                if(--degree[w] == 0) queue.push(w);
        }
        step++;
    }
    return -1;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> k >> p;
    fill(degree, degree + n + 1, 0);
    graph.assign(n + 2, {});
    for(int i = 1, s = n + 1, t; i <= p; i++){
        cin >> t;
        graph[s].push_back(t);
    }
    cin >> r;
    for(int i = 1, v, s, w; i <= r; i++) {
        cin >> v >> s;
        for(int j = 1; j <= s; j++) {
            cin >> w;
            graph[w].push_back(v);
        }
    }
    cout << topol_sort() << endl;
}
